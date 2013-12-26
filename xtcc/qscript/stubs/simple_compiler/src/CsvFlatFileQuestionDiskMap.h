#ifndef QSCRIPT_CSVFLATFILEQUESTIONDISKMAP
#define QSCRIPT_CSVFLATFILEQUESTIONDISKMAP

#include <set>
#include <sstream>
#include <string>
#include <fstream>
#include "question.h"

class CsvFlatFileQuestionDiskMap
{
	public:
		AbstractQuestion *q;
		int32_t start_pos;
		int32_t width;
		int32_t total_length;
		CsvFlatFileQuestionDiskMap(AbstractQuestion * p_q, int32_t p_start_pos);
		int GetTotalLength() { return total_length; }
		//void write_data (char * output_buffer)
		void write_data (std::stringstream & output_buffer);
		void write_csv_header (std::stringstream & output_buffer);
#if 0
		{
			cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
			//char * ptr = output_buffer + start_pos;
			//*ptr++ = ',';
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
				output_buffer << ",nq";
			} else if (RangeQuestion * rq = dynamic_cast<RangeQuestion*> (q)) {
				output_buffer << ",rq";
			} else {
				output_buffer << "none of nq/rq,";
			}
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

			//cerr << "ptr: " << ptr << endl;
			cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
		}
#endif /* 0 */
		void print_map(std::fstream & map_file)
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

		void write_spss_pull_data(std::fstream & spss_syn_file);

		void write_spss_variable_labels(std::fstream & spss_syn_file);
		void write_spss_value_labels(std::fstream & spss_syn_file);
};

#endif  /* */
