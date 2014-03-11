/*
 * =====================================================================================
 *
 *       Filename:  CsvFlatFileQuestionDiskMap.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 26 December 2013 01:28:35  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <sstream>
#include <iostream>
#include <cstdlib>

#include "CsvFlatFileQuestionDiskMap.h"
#include "ArrayQuestion.h"
#include "named_range.h"

using std::cout;
using std::cerr;
using std::endl;
using std::stringstream;

extern int32_t verbatim_mode_flag;
extern std::string  jno;
extern int32_t  ser_no;

void csv_escape (string & sample_string)
{
	cerr << __PRETTY_FUNCTION__ <<" received string: " << sample_string << endl;
	int found = sample_string.find ('"');
	int n_rplc = 0;
	while (found != string::npos) {
		string escaped_dq("\"\"");
		sample_string.replace (found, 1, escaped_dq);
		found = sample_string.find ('"', found+2);
		++ n_rplc;
	}
	cerr << "EXIT " <<  __PRETTY_FUNCTION__ << "n_rplc: " << n_rplc << "str: " << sample_string << endl;
}

string print_data_as_csv (const set<int32_t> & the_input_data, const int no_mpn, AbstractQuestion * q)
{
	stringstream output_buffer;
	int n_inputs = 0;
	for (
		//std::set<int>::iterator it = q->input_data.begin(); it != q->input_data.end(); ++it
		std::set<int>::iterator it = the_input_data.begin(); it != the_input_data.end(); ++it,
		++n_inputs
		) {
		const int & code = *it;
		output_buffer << "," << code;
	}

	stringstream complete_name ;
	complete_name << q->questionName_;
	for (int32_t i = 0; i < q->loop_index_values.size(); ++i) {
		complete_name << "_" << q->loop_index_values[i] + 1;
	}

	for (int i=0; i < no_mpn - n_inputs; ++i) {
		//output_buffer << "," << complete_name.str();
		output_buffer << "," ;
	}
	return output_buffer.str();
}

extern int32_t verbatim_mode_flag;
void CsvFlatFileQuestionDiskMap::write_csv_header (std::stringstream & output_buffer)
{
	stringstream complete_name ;
	complete_name << q->questionName_;
	for (int32_t i = 0; i < q->loop_index_values.size(); ++i) {
		complete_name << "_" << q->loop_index_values[i] + 1;
	}
	if (GeocodeGMapV3Question * gq = dynamic_cast<GeocodeGMapV3Question*> (q)) {
		output_buffer
			<< "," << complete_name.str() << "_geocode"
			<< "," << complete_name.str() << "_address";
	} else if (RangeQuestion * rq = dynamic_cast<RangeQuestion*> (q)) {
		if (rq->no_mpn == 1) {
			output_buffer 
				<< ", " << complete_name.str();
		} else {
			if (verbatim_mode_flag) {
				output_buffer
					<< ", " << complete_name.str();
			} else {
				for (int32_t i = 0; i < q->no_mpn; ++i) {
					output_buffer << "," << complete_name.str() << "_" << i + 1;
				}
			}
		}
	} else if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*> (q)) {
		for (int32_t i = 0; i < q->no_mpn; ++i) {
			output_buffer << "," << complete_name.str() << "_" << i + 1;
		}
	} else if (VideoCaptureQuestion * vq = dynamic_cast<VideoCaptureQuestion*> (q)) {
			output_buffer << "," << complete_name.str();
	} else {
		output_buffer << "," << "unhandled question type";
	}
}

void CsvFlatFileQuestionDiskMap::write_data (std::stringstream & output_buffer, SequentialFileIterator & data_file_iterator)
{
	cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
	stringstream complete_name ;
	complete_name << q->questionName_;
	for (int32_t i = 0; i < q->loop_index_values.size(); ++i) {
		complete_name << "_" << q->loop_index_values[i] + 1;
	}

	//char * ptr = output_buffer + start_pos;
	//*ptr++ = ',';
	int no_responses_written = 0;
	bool has_named_attribute = false;
	bool named_attribute_is_randomized = false;
	int text_na_index = -1;
	// warning - the code below will only work if there is
	// exactly 1 named attribute in the question which is randomized
	//
	//extern SequentialFileIterator data_file_iterator;
	if (q->textExprVec_.size() > 0 ) {
		cout << __PRETTY_FUNCTION__ << ", q->textExprVec_.size() > 0" << endl;
		for (int i=0; i< q->textExprVec_.size(); ++i) {
			if (q->textExprVec_[i]->teType_ == TextExpression::named_attribute_type) {
				has_named_attribute = true;
				if (q->textExprVec_[i]->naPtr_->isRandomized_) {
					named_attribute_is_randomized = true;
					text_na_index = i;
					cout << "named_attribute_is_randomized : text_na_index: " << text_na_index
						<< endl;
				}
			}
		}
	}

	set<int32_t> the_input_data;
	if (text_na_index > 0 && has_named_attribute && named_attribute_is_randomized) {
		cout << "q->textExprVec_[" << text_na_index << "]->naIndex_:"
			<< q->textExprVec_[text_na_index]->naIndex_
			<< endl;
		if (q->textExprVec_[text_na_index]->naPtr_ -> randomized_order.size() > 0 ) {
			vector <int> & rnd_order = q->textExprVec_[text_na_index]->naPtr_ -> randomized_order;
			int na_index =  q->textExprVec_[text_na_index]->naIndex_;
			int na_rnd_index = -1;
			for (int i=0; i < rnd_order.size(); ++i) {
				if (rnd_order[i] == na_index) {
					na_rnd_index = i;
					break;
				}
			}
			the_input_data = q->array_q_ptr_ -> questionList[na_rnd_index]->input_data;
		} else {
			the_input_data = q->array_q_ptr_ -> questionList[q->textExprVec_[text_na_index]->naIndex_]->input_data;
		}
	}  else {
		the_input_data = q->input_data;
	}

#if 0
	for (
		//std::set<int>::iterator it = q->input_data.begin(); it != q->input_data.end(); ++it
		std::set<int>::iterator it = the_input_data.begin(); it != the_input_data.end(); ++it
		) {
		int code = *it;
		std::stringstream code_str;
		code_str << code;
		cerr << "writing code: " << code << " to output_buffer: length: " << code_str.str().length() << "\n";
		int jump_delta = width;
		if (code_str.str().length() > width)
		{
			cerr << " internal programming error - width of code exceeds width allocated ... exiting\n";
			exit(1);
		}
		else if (code_str.str().length() < width) {
			// csv file  pad with space
			int diff = width - code_str.str().length();
			for (int i=0; i<diff; ++i) {
				ptr[i]=' ';
			}
			ptr += diff;
			jump_delta -= diff;
		}
		// int bytes_written = snprintf(ptr, code_str.str().length(), "%s", code_str.str().c_str());
		// int bytes_written = snprintf(ptr, code_str.str().length(), "%d", code);
		for (int i=0; i<code_str.str().length(); ++i)
		{
			ptr[i] = (code_str.str())[i];
		}
		//ptr[code_str.str().length()] = ',';
		//*(output_buffer + start_pos+ width - 1)=',';
		// ptr[bytes_written] = ' ';
		//if (bytes_written > width) {
		//	cerr << "impossible internal programming error - width of code exceeds width allocated ... exiting\n";
		//	exit(1);
		//}
		ptr += jump_delta;
		++no_responses_written;
		if (no_responses_written > q->no_mpn)
		{
			cerr << " no of responses in question : " << q->questionName_ << " exceeds no allocated ... exiting\n";
			exit(1);
		}
	}
#endif /* 0 */
	if (NamedStubQuestion * nq = dynamic_cast<NamedStubQuestion*> (q)) {
		//output_buffer << ",nq";
		output_buffer <<  print_data_as_csv ( the_input_data, q->no_mpn, q);
	} else if (RangeQuestion * rq = dynamic_cast<RangeQuestion*> (q)) {
		cerr << " case rq: " << endl;
		if (rq->no_mpn > 1) {
			//output_buffer << ",rq";
			cerr << " case rq->no_mpn > 1" << endl;
			//output_buffer << " case rq->no_mpn > 1 verbatim_mode_flag nxd: " << verbatim_mode_flag;
			if (verbatim_mode_flag) {
				stringstream verb_file_name;
				verb_file_name
					<< data_file_iterator.dir_part 
					<< q->questionName_;
				for (int i=0; i< q->loop_index_values.size(); ++i) {
					verb_file_name << "-" << q->loop_index_values[i];
				}
				verb_file_name 
					<< "." 
					//<< jno << "_" << ser_no 
					<< data_file_iterator.filename_part
					//<< ".dat" 
					;
				cerr << "trying to open verb_file: " 
					<< verb_file_name.str()
					<< endl;
				std::fstream verb_file(verb_file_name.str().c_str());
				//cerr << "reached here - verb_file";
				if (verb_file) {
					cerr << "successfully opned file" << endl;
					//output_buffer << "OPENED : " << verb_file_name << ":"  ;
					char buffer[257];
					buffer[255]=buffer[256]=0;
					string entire_text;
					while (verb_file) {
						verb_file.getline (buffer, 255);
						string part_read(buffer);
						entire_text += part_read;
						//cerr << "part_read: " << part_read << endl;
					}
					cerr << "entire_text: " << entire_text << endl;
					csv_escape(entire_text);
					output_buffer << ", \"" << entire_text << "\"";
				} else {
					cerr << "unable to open : " << verb_file << endl;
					//output_buffer << ", \"could not open : " << verb_file_name.str() << "\"" ;
					output_buffer << ", ";
				}
			} else {
				output_buffer <<  print_data_as_csv ( the_input_data, q->no_mpn, q);
			}
		} else {
			output_buffer <<  print_data_as_csv ( the_input_data, q->no_mpn, q);
		}
	} else if (VideoCaptureQuestion * mcq = dynamic_cast<VideoCaptureQuestion*> (q)) {
		stringstream media_data_file_name;
		media_data_file_name
			<< data_file_iterator.dir_part 
			<< q->questionName_;
		for (int i=0; i< q->loop_index_values.size(); ++i) {
			media_data_file_name << "-" << q->loop_index_values[i];
		}
		media_data_file_name
			<< "." 
			<< data_file_iterator.filename_part
			;
		if (mcq->q_type == video_capture) {
			output_buffer << ",\"video_capture\" : ";
		} else if (mcq->q_type == audio_capture) {
			output_buffer << ",\"audio_capture\" : ";
		} else if (mcq->q_type == image_capture) {
			output_buffer << ",\"image_capture\" : ";
		}
		cerr << "media_data_file_name: " << media_data_file_name.str() << endl;
		std::fstream media_data_file(media_data_file_name.str().c_str());
		if (media_data_file) {
			char buffer[257];
			buffer[255]=buffer[256]=0;
			string entire_text;
			while (media_data_file) {
				media_data_file.getline (buffer, 255);
				entire_text += string(buffer);
			}
			output_buffer << entire_text ;
		} else {
			//output_buffer << complete_name;
			output_buffer << "{ }";
		}

	} else if (GeocodeGMapV3Question * gq = dynamic_cast<GeocodeGMapV3Question*> (q)) {
		cerr << " case GeocodeGMapV3Question: " << endl;
		if (verbatim_mode_flag) {
			// read geo data from current folder.

			stringstream geocode_data_file_name;
			geocode_data_file_name
				<< data_file_iterator.dir_part 
				<< q->questionName_;
			for (int i=0; i< q->loop_index_values.size(); ++i) {
				geocode_data_file_name << "-" << q->loop_index_values[i];
			}
			geocode_data_file_name
				<< "_geocode"
				<< "." 
				<< data_file_iterator.filename_part
				;
			cerr << "GeocodeGMapV3Question: trying to read data from file: "
				<< geocode_data_file_name.str()
				<< endl;
			std::fstream geocode_data_file(geocode_data_file_name.str().c_str());
			if (geocode_data_file) {
				//output_buffer << ",\"GeocodeGMapV3Question\" : ";
				string entire_text ("\"GeocodeGMapV3Question\" : ");
				char buffer[257];
				buffer[255]=buffer[256]=0;
				while (geocode_data_file) {
					geocode_data_file.getline (buffer, 255);
					entire_text += string(buffer);
				}
				csv_escape(entire_text);
				output_buffer << ",\"" << entire_text << "\"";
			} else {
				//output_buffer << ", \"GeocodeGMapV3Question\" : \"empty\"";
				output_buffer << ", \"GeocodeGMapV3Question\" : {}";
			}

			stringstream address_data_file_name;
			address_data_file_name
				<< data_file_iterator.dir_part 
				<< q->questionName_;
			for (int i=0; i< q->loop_index_values.size(); ++i) {
				address_data_file_name << "-" << q->loop_index_values[i];
			}
			address_data_file_name
				<< "_address"
				<< "." 
				<< data_file_iterator.filename_part ;
			cerr << "GeocodeGMapV3Question: trying to read data from file: "
				<< address_data_file_name.str()
				<< endl;
			std::fstream address_data_file(address_data_file_name.str().c_str());
			if (address_data_file) {
				char buffer[257];
				buffer[255]=buffer[256]=0;
				string entire_text("\"geocoded_address\":");
				while (address_data_file) {
					address_data_file.getline (buffer, 255);
					entire_text += string(buffer);
				}
				//output_buffer << ", \"geocoded_address\" : "<< entire_text ;
				csv_escape(entire_text);
				output_buffer << ",\"" << entire_text << "\"";
			} else {
				output_buffer << ", \"geocoded_address\" : {}";
			}

		} else {

		}
	} else {
		output_buffer << "none of nq/rq, unhandled question type" << endl;
	}

#if 0
	int n_inputs = 0;
	for (
		//std::set<int>::iterator it = q->input_data.begin(); it != q->input_data.end(); ++it
		std::set<int>::iterator it = the_input_data.begin(); it != the_input_data.end(); ++it,
		++n_inputs
		) {
		const int & code = *it;
		output_buffer << "," << code;
	}
	for (int i=0; i < q->no_mpn - n_inputs; ++i) {
		output_buffer << ",";
	}
#endif /*  0 */

	//cerr << "ptr: " << ptr << endl;
	cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
}



CsvFlatFileQuestionDiskMap::CsvFlatFileQuestionDiskMap(AbstractQuestion * p_q, int32_t p_start_pos
								)						 
			:
		q(p_q), start_pos(p_start_pos)
		/*, width(p_width),
				total_length(p_total_length)*/
{
	if (GeocodeGMapV3Question * gq = dynamic_cast<GeocodeGMapV3Question*> (q)) {
		total_length = 1;
	} else {
		int max_code = q->GetMaxCode();
		if (max_code < 10)
		{
			width = 1;
		}
		else if (max_code < 100)
		{
			width = 2;
		}
		else if (max_code < 1000)
		{
			width = 3;
		}
		else if (max_code < 10000)
		{
			width = 4;
		}
		else if (max_code < 100000)
		{
			width = 5;
		}
		else if (max_code < 1000000)
		{
			width = 6;
		}
		else if (max_code < 10000000)
		{
			width = 7;
		}
		else if (max_code < 100000000)
		{
			width = 8;
		}
		else if (max_code < 1000000000)
		{
			width = 9;
		}
		else
		{
			cout << " max_code " << max_code << " for question: " << q->questionName_ << " exceeds max length = 9 we are programmed to handled ... exiting " << __FILE__ << ","  << __LINE__ << ","  << __PRETTY_FUNCTION__ << endl;
			exit(1);
		}
		width += 1; // to account for the comma
		total_length = width  * q->no_mpn;
	}
}


void CsvFlatFileQuestionDiskMap::write_spss_pull_data(std::fstream & spss_syn_file)
{
	std::stringstream var_name;
	var_name << q->questionName_;
	if (q->loop_index_values.size())
	{
		for (int i=0; i< q->loop_index_values.size(); ++i)
		{
			var_name << "_" << q->loop_index_values[i];
		}
	}
	if (q->no_mpn>1) {
		spss_syn_file << var_name.str() << "_1 to " 
			<< var_name.str() << "_" << q->no_mpn ;
	} else {
		spss_syn_file << var_name.str();
	}

	spss_syn_file << "\t\t\t\t";
	spss_syn_file << start_pos+1 << "-";
	spss_syn_file << start_pos + total_length  << "\n";
	//spss_syn_file << ",			";
	//spss_syn_file << width << ",	";
	//spss_syn_file << q->no_mpn << ",	";
}

		void CsvFlatFileQuestionDiskMap::write_spss_variable_labels(std::fstream & spss_syn_file)
{
	stringstream var_name;

	var_name << q->questionName_;
	if (q->loop_index_values.size())
	{
		for (int i=0; i< q->loop_index_values.size(); ++i)
		{
			var_name << "_" << q->loop_index_values[i];
		}
	}
	if (q->no_mpn>1) {
		for(int i=0; i<q->no_mpn; ++i) {
			spss_syn_file << "variable label ";
			spss_syn_file << var_name.str() << "_" << i+1;
			spss_syn_file << " \"" 
				<< q->AxPrepareQuestionTitleSPSS() 
				//<< "FIX me dummy questionText_ " << __FILE__ << ", " << __LINE__
				//<< ", " << __PRETTY_FUNCTION__ 
				<< "\"." << endl;
		}
	} else {
		spss_syn_file << "variable label ";
		spss_syn_file << var_name.str();
		spss_syn_file << " \"" 
			<< q->AxPrepareQuestionTitleSPSS() 
			//<< "FIX me dummy questionText_ " << __FILE__ << ", " << __LINE__
			//<< ", " << __PRETTY_FUNCTION__ 
			<< "\"." << endl;
	}

}

		void CsvFlatFileQuestionDiskMap::write_spss_value_labels(std::fstream & spss_syn_file)
{
	stringstream var_name;
	if (NamedStubQuestion * n_q = dynamic_cast<NamedStubQuestion*>(q)) {
		
		var_name << q->questionName_;
		if (q->loop_index_values.size())
		{
			for (int i=0; i< q->loop_index_values.size(); ++i)
			{
				var_name << "_" << q->loop_index_values[i];
			}
		}
		if (q->no_mpn>1) {
			spss_syn_file << "value label ";
			spss_syn_file << var_name.str() << "_1 to " 
				<< var_name.str() << "_" << q->no_mpn ;
		} else {
			spss_syn_file << "value label ";
			spss_syn_file << var_name.str();
		}
		spss_syn_file << endl;
		for (int i=0; i<n_q->nr_ptr->stubs.size(); ++i) {
			spss_syn_file 
				<< n_q->nr_ptr->stubs[i].code
				<< " \""
				<< n_q->nr_ptr->stubs[i].stub_text
				<< " \""
				<< endl;
		}
		spss_syn_file << "." << endl; 

	}
}
