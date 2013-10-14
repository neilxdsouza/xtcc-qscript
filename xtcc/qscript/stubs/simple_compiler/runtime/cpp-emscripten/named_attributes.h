/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/named_attributes.h
 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

#ifndef xtcc_named_attributes_h
#define xtcc_named_attributes_h


#include <sys/types.h>
#include <string>
#include <vector>
#include <iostream>
#include "datatype.h"
//#include "stmt.h"
//#include "AbstractStatement.h"

//using std::string;
//using std::vector;
struct named_attribute_list
	//: public AbstractStatement
{
	std::string name;
	std::vector<std::string> attribute;
	std::vector <int> randomized_order;
	bool isRandomized_;
	struct SymbolTableEntry* symbolTableEntry_;

	named_attribute_list(DataType dt, int32_t lline_no,  const std::string & l_name, const std::vector<std::string> & l_attr);
	named_attribute_list();
	virtual ~named_attribute_list();
	void randomize();
	void load_randomized_order (const std::vector <int> & p_randomized_order);
	std::string save_randomized_order ();

	int WriteNamedAttributeOrderToBuffer (char * & buffer_start, int & n_left);
	//virtual void GenerateCode(StatementCompiledCode & code);
	private:
		named_attribute_list& operator=(const named_attribute_list&);
		named_attribute_list (const named_attribute_list&);

};

#endif /* xtcc_named_attributes_h */
