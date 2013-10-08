#ifndef QSCRIPT_ASCIIFLATFILEQUESTIONDISKMAP
#define QSCRIPT_ASCIIFLATFILEQUESTIONDISKMAP

#include <set>
#include <sstream>
#include <string>
#include "question.h"

class AsciiFlatFileQuestionDiskMap
{
	public:
		AbstractQuestion *q;
		int32_t start_pos;
		int32_t width;
		int32_t total_length;
		AsciiFlatFileQuestionDiskMap(AbstractQuestion * p_q, int32_t p_start_pos
		/*,
								int32_t p_width, int32_t p_total_length*/
								)						 
			:
		q(p_q), start_pos(p_start_pos)
		/*, width(p_width),
				total_length(p_total_length)*/
		{
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
			total_length = width * q->no_mpn;
		}

		int GetTotalLength() { return total_length; }
		void write_data (char * output_buffer)
		{
			cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
			char * ptr = output_buffer + start_pos;
			int no_responses_written = 0;
			bool has_named_attribute = false;
			bool named_attribute_is_randomized = false;
			int text_na_index = -1;
			// warning - the code below will only work if there is
			// exactly 1 named attribute in the question which is randomized
			//
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

			for (
				//std::set<int>::iterator it = q->input_data.begin(); it != q->input_data.end(); ++it
				std::set<int>::iterator it = the_input_data.begin(); it != the_input_data.end(); ++it
				) {
				int code = *it;
				std::stringstream code_str;
				code_str << code;
				//cout << "writing code: " << code << " to output_buffer: length: " << code_str.str().length() << "\n";
				int jump_delta = width;
				if (code_str.str().length() > width)
				{
					cerr << " internal programming error - width of code exceeds width allocated ... exiting\n";
					exit(1);
				}
				else if (code_str.str().length() < width) {
					// zero pad 
					int diff = width - code_str.str().length();
					for (int i=0; i<diff; ++i) {
						ptr[i]='0';
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
			cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
		}
		void print_map(fstream & map_file)
		{
			map_file << q->questionName_;
			if (q->loop_index_values.size())
			{
				for (int i=0; i< q->loop_index_values.size(); ++i)
				{
					map_file << "." << q->loop_index_values[i];
				}
			}
			map_file << ",			";
			map_file << width << ",	";
			map_file << q->no_mpn << ",	";
			map_file << start_pos+1 << ",	";
			map_file << start_pos + total_length  << "\n";
		}
		void write_spss_pull_data(fstream & spss_syn_file)
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
		void write_spss_variable_labels(fstream & spss_syn_file)
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
		void write_spss_value_labels(fstream & spss_syn_file)
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
};

#endif  /* */
