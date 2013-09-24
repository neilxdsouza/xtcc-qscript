#include <sys/types.h>
#include <iostream>
#include "named_attributes.h"
#include "simple_rng.h"

using std::cout;
using std::endl;

using std::vector;
using std::string;



named_attribute_list::named_attribute_list(DataType dt, int32_t lline_no
					   , const string & l_name
					   , const vector<string> & l_attr)
	: //AbstractStatement(dt, lline_no),
	  name(l_name), attribute(l_attr), symbolTableEntry_(0), isRandomized_ (0)
{ }

named_attribute_list::named_attribute_list()
	: //AbstractStatement(NAMED_ATTRIBUTE_TYPE, 0),
	name(), attribute(), symbolTableEntry_(0), isRandomized_ (0)
{ }

named_attribute_list::~named_attribute_list()
{ }

#if 0
void named_attribute_list::GenerateCode(StatementCompiledCode & code)
{
	code.program_code << "/* "
		<< __PRETTY_FUNCTION__ << ", " << __FILE__ << ", " << __LINE__
		<< "*/" << endl;
	code.quest_defns << "named_attribute_list "
		<<  name << ";\n";
	code.quest_defns_init_code
		<< name << ".name = \"" << name << "\";\n";
	for (int i=0; i<attribute.size(); ++i) {
		code.quest_defns_init_code
			<<  name << ".attribute.push_back (string(\"" << attribute[i]
				<< "\"));\n";
	}
	code.quest_defns_init_code
		<< "\tif (write_messages_flag) {\n"
		<< "\tfor (int i=0; i<"
		<< name << ".attribute.size(); ++i) {\n"
		<< "\tmessages << \"<message id=\\\"\" << \"" << name  << "\" << \"_\" << i << \"\\\">\""
		<<	" << "
		<< name
		<< ".attribute[i] << \"</message>\\n\" << endl;\n"
		<< "\t}\n"
		<< "}\n";
	if (next_) {
		next_->GenerateCode(code);
	}
}
#endif /* 0 */

void shuffle(/* int *array */vector<int> & array)
{    
	//struct timeval tv;
	//gettimeofday(&tv, NULL);
	//int usec = tv.tv_usec;
	//srand48(usec);
	const size_t n = array.size();

	if (n > 1) {
		for (size_t i = n - 1; i > 0; i--) {
		    size_t j = (unsigned int) (drand48()*(i+1));
		    int t = array[j];
		    array[j] = array[i];
		    array[i] = t;
		}
	}
}

void named_attribute_list::randomize()
{
	if (randomized_order.size() == 0) {
		randomized_order.resize(attribute.size());
		for (int i = 0; i < attribute.size(); ++i) {
			//randomized_order.push_back(i);
			randomized_order[i] = i;
		}
	}
	//MyRNG my_rng;
	//random_shuffle ( randomized_order.begin(), randomized_order.end(), my_rng);
	shuffle (randomized_order);
	isRandomized_  = 1;
}
