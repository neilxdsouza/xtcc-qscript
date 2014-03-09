/*
 *  Copyright (C)  2011
 *	Neil Xavier D'Souza
 */

#ifndef QuestionAttributes_h
#define QuestionAttributes_h
#include <string>
#include "dom_manip_funcs.h"

struct QuestionAttributes
{
	bool hidden_;
	bool allowBlank_;
	std::string helpText_;
	int minLength_;
	int maxLength_;
	void Reset();
	QuestionAttributes();
	QuestionAttributes(const QuestionAttributes & qa);
	QuestionAttributes(bool p_Hidden, bool p_allowBlank, const std::string & p_help_text,
			int p_min_length, int p_max_length);
	void setHelpText(const std::string & p_help_text );
	void setHidden();
	void setAllowBlank();
	bool isAllowBlank();
	bool isHidden();
	std::string Print();
	void setMinLength(int length);
	void setMaxLength(int length);
};

#endif /* QuestionAttributes_h */
