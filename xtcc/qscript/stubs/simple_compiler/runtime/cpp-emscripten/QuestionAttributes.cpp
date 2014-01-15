
#include <sstream>
#include <string>
#include "QuestionAttributes.h"
#include "dom_manip_funcs.h"

using std::string;
using std::stringstream;


void QuestionAttributes::Reset()
{ hidden_ = false; allowBlank_ = false; }

QuestionAttributes::QuestionAttributes()
	: hidden_(false), allowBlank_(false), helpText_()
{ }

QuestionAttributes::QuestionAttributes(bool p_Hidden, bool p_allowBlank, const std::string & p_help_text  )
	: hidden_(p_Hidden), allowBlank_(p_allowBlank), helpText_ (p_help_text)
{ }

QuestionAttributes::QuestionAttributes(const QuestionAttributes & qa)
	: hidden_(qa.hidden_ ), allowBlank_(qa.allowBlank_), helpText_ (qa.helpText_)
{ 
	//hidden_ = qa.hidden_;
	//allowBlank_ = qa.allowBlank_;
	//helpText_ = qa.helpText_;
	//my_log_from_cpp ("helpText_:");
	//my_log_from_cpp (helpText_.c_str());
}

string QuestionAttributes::Print()
{
	stringstream s;
	s << " QuestionAttributes(";
	if (hidden_ == false) {
		s << "false ";
	} else {
		s << "true ";
	}
	s << ", ";
	if (allowBlank_ == false) {
		s << "false";
	} else {
		s << "true";
	}
	s << ", string(\""  << helpText_ << "\")";

	s << ")";
	return s.str();
}

void QuestionAttributes::setHidden() { hidden_ = true; }

void QuestionAttributes::setAllowBlank() { allowBlank_ = true; }

void QuestionAttributes::setHelpText(const string & p_help_text )
{
	helpText_ = p_help_text;
}

bool QuestionAttributes::isAllowBlank() { return allowBlank_; }
 
bool QuestionAttributes::isHidden() { return hidden_; }
