/*
 *  xtcc/xtcc/qscript/stubs/simple_compiler/AbstractStatement.h

 *
 *  Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Neil Xavier D'Souza
 */

/*! \file
    \brief The classes for the statements parsed in the input
            language "qscript" are contained in this file
*/


#ifndef stmt_h
#define stmt_h
#include <sys/types.h>
#include <string>
//#include <sstream>
#include <iosfwd>
#include "xtcc_set.h"
#include "symtab.h"
#include "stub_pair.h"
#include "scope.h"
//#include "common.h"
#include "compiled_code.h"
#include "AbstractStatement.h"

using std::string;
using std::ostringstream;




struct named_range;


//!ExpressionStatement Parsed expressions statements become object instanstiations of this class
/*!
  an example of an expression statement is the assignment statement below:
  	a=5*10;
  This class contains an AbstractExpression* pure virutal base class pointer as a member.
  The AbstractExpression* expr generates its own
  code through the print_expr(ostringstream& code_bef_expr, ostringstream& code_expr)
  pure virtual function - which is over-ridden in each of the expression classes
*/
struct ExpressionStatement: public AbstractStatement
{
	struct AbstractExpression* expression_;
	ExpressionStatement(DataType l_type, int32_t l_line_number
			    , int32_t l_nest_level, int32_t l_for_nest_level
			    , struct AbstractExpression* e)
		: AbstractStatement(l_type, l_line_number, l_nest_level, l_for_nest_level), expression_(e)
	{ }
	//void GenerateCode(ostringstream & quest_defns
	//		, ostringstream& program_code);
	virtual void GenerateCode(StatementCompiledCode & code);
	virtual ~ExpressionStatement();
	private:
	ExpressionStatement& operator=(const ExpressionStatement&);
	ExpressionStatement(const ExpressionStatement&);
};



//! DeclarationStatement  parsed variable declarations become object instanstiations of this class
struct DeclarationStatement: public AbstractStatement
{
	struct SymbolTableEntry* symbolTableEntry_;
	DeclarationStatement( DataType dtype, int32_t lline_number,
				  int32_t l_nest_level, int32_t l_for_nest_level)
		: AbstractStatement(dtype, lline_number, l_nest_level, l_for_nest_level), symbolTableEntry_(0)
	{ }
	~DeclarationStatement();
	//void GenerateCode(ostringstream & quest_defns
	//		, ostringstream& program_code);
	virtual void GenerateCode(StatementCompiledCode & code);
	private:
	DeclarationStatement& operator=(const DeclarationStatement&);
	DeclarationStatement(const DeclarationStatement&);
};

//! CompoundStatement parsed compound statements become object instanstiations of this class
/*!
  important notes for this class(CompoundStatement):
  <p>1. function definitions have a compound statement as the body
     of the class. The compound Scope is not allocated in the
     constructor of the CompoundStatement initialiser list because
     we need to determine if this statement is a part
     of a function definition or a normal compound statement.
     If the CompoundStatement is a part of a func_defn it will get its Scope
     from the declaration of the function which is stored in the
     func_info_table vector array. Otherwise the constructor will
     allocate a Scope for the variable
  <p>2. The other case for a compound statement is when it is the body of
     a for loop. There are certain restrictions on the language because
     the questionnaire is stored on disk. Consider the following .

        We need to create a map file of the questionnaire.
        This means that the map file has to be fixed for each and every single
	questionnaire. Hence if a "for" loop contains questions in the body
	we cannot have a variable number of questions being asked to the respondent.

	for example below is not allowed:
	int32_t v1=v2*v3;
	for(int32_t i=0; i<v1; i++){
		q1 ask "q1" ...
		q2 ask "q2" ...
	}
	This would not allow us to create a fixed map file for the location
	of data on the disk

	on the other hand the following is allowed
	const int32_t n_iters=10;
	for(int32_t i=0; i<n_iters*5; ++i){
		q1 ask "q1" ...
		q2 ask "q2" ...
	}
	as this => that the loop will run 50 times and so
	q1, q2 are arrays of size 50.

	Hence the compound_stmt needs to determine if it contains questions
	and if so set a flag. Then when parsing a for statement - and note that
	a for statement has been forced by the grammar to have only a CompoundStatement
	as the body - we check if the CompoundStatement has questions and run additional
	checks on the testExpression_ index of the for loop to ensure it is an integral value
	(i.e. countable and determinable)



	When parsing a compound statement the parser it will push the
	cmpd_stmt_ptr object onto the stack named stack_cmpd_stmt. This is
	done in the ^open_curly rule in q.y
	Everytime the parser encounters a AbstractQuestion in the body of the CompoundStatement
	it will increment the counter "counterContainsQuestions_" CompoundStatement
	member variable by 1. You can see this happening in the ^AbstractQuestion rule
	in q.y
	This way we can determine if the compound body has a AbstractQuestion. Once this has
	been determined we put addition restrictions on the loop index of the for
	statement

*/

struct IfStatement;
struct ForStatement;

struct CompoundStatement: public AbstractStatement
{
	static int32_t counter_;
	//! pointer to the first chain of statements
	//! in the CompoundStatement
	struct AbstractStatement* compoundBody_;
	//! The Scope for the CompoundStatement will contain all
	//! the variables declared in the body of the
	//! CompoundStatement. This variable is set in 2 ways.
	//! 1. If it is the body of a func_defn then
	//     it is assigned to the Scope variable in the function
	//     declaration
	//  2. Otherwise a new Scope object is allocated
	struct Scope * scope_;
	//! this flag variable is set in the grammar type.y
	//! in the xtcc compiler sources and not used in
	//! the qscript compiler as yet.
	//! The rule used to set the variable is ^func_defn
	//! The variable is used in the ^open_curly rule when deciding
	//! if a Scope is to be allocated or pulled from the function
	//! declaration
	int32_t flagIsAFunctionBody_;
	//! this flag variable is set in the ^for_loop_stmt in
	//! q.y in an inline action in the grammar
	int32_t flagIsAForBody_;

	//! this counter variable is set in the ^AbstractQuestion rule in
	//! q.y in an inline action in the grammar
	int32_t counterContainsQuestions_;
	int32_t compoundStatementNumber_;
	bool flagGeneratedQuestionDefinitions_;
	vector<AbstractExpression*> for_bounds_stack;
	vector<AbstractQuestion*> questionsInBlock_;
	vector<CompoundStatement*> nestedCompoundStatementStack_;
	vector<string> ConsolidatedForLoopIndexStack_;
	int32_t flagIsAIfBody_;

	struct IfStatement  * ifStatement_;
	struct IfStatement  * elseStatement_;
	struct ForStatement * forStatement_;
	int nestLevel_;
	public:
	CompoundStatement(DataType dtype, int32_t lline_number
			  , int32_t l_nest_level, int32_t l_for_nest_level
			  , int32_t l_flag_cmpd_stmt_is_a_func_body
			  , int32_t l_flag_cmpd_stmt_is_a_for_body
			  , vector<AbstractExpression*>& l_for_bounds_stack
		);
	//void GenerateCode(ostringstream & quest_defns
	//		, ostringstream& program_code);
	virtual void GenerateCode(StatementCompiledCode & code);
	virtual ~CompoundStatement();
	void GetQuestionNames(vector<string> & question_list,
			      AbstractStatement * endStatement);

	void GetQuestionsInBlock(vector<AbstractQuestion*> & question_list
				 , AbstractStatement * stop_at);
	void GenerateQuestionArrayInitLoopOpen(StatementCompiledCode &code);
	void GenerateQuestionArrayInitLoopClose(StatementCompiledCode &code);
	void GenerateConsolidatedForLoopIndexes();
	virtual void Generate_ComputeFlatFileMap(StatementCompiledCode & code);
	//static void Init();
	private:
	CompoundStatement& operator=(const CompoundStatement&);
	CompoundStatement(const CompoundStatement&);
};

//! ForStatement: A parsed for statement in the language becomes an object instanstiation of this class
/*! Refer to point 2. in the documentation for CompoundStatement about for loop index
    restrictions when you have a AbstractQuestion statement in the body
    of a for statement
 */
struct ForStatement: public AbstractStatement
{
	AbstractExpression * initializationExpression_
		, * testExpression_, *incrementExpression_;
	CompoundStatement * forBody_;
	ForStatement(DataType dtype, int32_t lline_number
		     , int32_t l_nest_level, int32_t l_for_nest_level
		     , AbstractExpression* l_init
		     , AbstractExpression* l_test
		     , AbstractExpression* l_incr
		     , CompoundStatement * lfor_body);
	void GenerateConsolidatedForLoopIndexes();
//	void GenerateCode(ostringstream & quest_defns
//			, ostringstream& program_code);
	virtual void GenerateCode(StatementCompiledCode & code);
	virtual void Generate_ComputeFlatFileMap(StatementCompiledCode & code);
	virtual void GetQuestionsInBlock(vector<AbstractQuestion*> & question_list
					 , AbstractStatement* stop_at);
	virtual ~ForStatement();
	void GenerateQuestionArrayInitLoopOpen(StatementCompiledCode &code);
	void GenerateQuestionArrayInitLoopClose(StatementCompiledCode &code);
	void GetQuestionNames(vector<string> & question_list,
			      AbstractStatement * endStatement);
	private:
	ForStatement& operator=(const ForStatement&);
	ForStatement(const ForStatement&);
	void DoExtraForLoopChecks();
	void CheckForIndexUsageConsistency();
	void CheckNestedIndexUsage();
};

//! IfStatement if statements in the language become object instantiations of this class
struct IfStatement : public AbstractStatement
{
	protected:
	public:
	struct AbstractExpression * ifCondition_;
	struct AbstractStatement * ifBody_;
	struct AbstractStatement * elseBody_;
	IfStatement( DataType dtype, int32_t lline_number
		     , int32_t l_nest_level, int32_t l_for_nest_level
		     , AbstractExpression * lcondition
		     , AbstractStatement * lif_body
		     , AbstractStatement * lelse_body=0);
//	void GenerateCode(ostringstream & quest_defns
//			, ostringstream& program_code);
	void GenerateConsolidatedForLoopIndexes();
	virtual void GenerateCode(StatementCompiledCode & code);
	virtual void Generate_ComputeFlatFileMap(StatementCompiledCode & code);
	virtual ~IfStatement();
	void GetQuestionNames(vector<string> & question_list,
			AbstractStatement* endStatement);

	virtual void GetQuestionsInBlock(vector<AbstractQuestion*> & question_list
					 , AbstractStatement* stop_at);
	std::string PrintIdentity ();
	private:
	IfStatement& operator=(const IfStatement&);
	IfStatement(const IfStatement&);

};

using std::string;
struct VariableList
{
	DataType variableType_;
	string variableName_;
	int32_t arrayLength_;
	struct VariableList * prev_, *next_;
	VariableList(DataType type, char * name);
	VariableList(DataType type, char * name, int32_t len);
	void print(FILE * edit_out);
	~VariableList();
	private:
		VariableList& operator=(const VariableList&);
		VariableList(const VariableList&);
};

struct Parameter
{
	struct AbstractExpression* e;
	char * text;
	struct Parameter * prev_;
	struct Parameter * next_;
};

struct AbstractQuestion;
AbstractQuestion* find_in_question_list(string name);
struct Unary2Expression;

struct named_range;
struct StubManipStatement: public AbstractStatement
{
	string questionName_;
	string namedStub_;
	named_range * namedRange_;
	AbstractQuestion * lhs_;
	AbstractQuestion * rhs_;
	XtccSet xtccSet_;
	AbstractExpression * arrIndex_;
	AbstractExpression * arrLIndex_;
	AbstractExpression * maskExpr_;
	//StubManipStatement( DataType dtype, int32_t lline_number
	//		    , string l_named_stub, string l_question_name);
	//StubManipStatement( DataType dtype, int32_t lline_number
	//		    , string l_named_stub, string l_question_name, AbstractExpression * arr_index);
	StubManipStatement( DataType dtype, int32_t lline_number
			    , int32_t l_nest_level, int32_t l_for_nest_level
			    , string l_named_stub);

	//StubManipStatement(DataType dtype, int32_t lline_number
	//			       , named_range * l_named_range
	//			       , AbstractQuestion * l_question);
	StubManipStatement (DataType dtype, int32_t lline_number
			   , int32_t l_nest_level, int32_t l_for_nest_level
			   , named_range * l_named_range
			   , AbstractQuestion * l_question
			   , AbstractExpression * larr_index = 0);
	StubManipStatement (DataType dtype, int32_t lline_number
			   , int32_t l_nest_level, int32_t l_for_nest_level
			   , AbstractQuestion * l_question_lhs
			   , AbstractExpression * l_l_arr_index
			   , AbstractQuestion * l_question_rhs
			   , AbstractExpression * l_r_arr_index
			   );

	StubManipStatement(DataType dtype, int32_t lline_number
			   , int32_t l_nest_level, int32_t l_for_nest_level
			   , named_range * l_named_range
			   , XtccSet & xs);
	StubManipStatement(DataType dtype, int32_t lline_number
			   , int32_t l_nest_level, int32_t l_for_nest_level
			   , AbstractQuestion * l_question_lhs
			   , XtccSet & xs);

	StubManipStatement(DataType dtype, int32_t lline_number
			   , int32_t l_nest_level, int32_t l_for_nest_level
			   , AbstractQuestion * l_question_lhs
			   , AbstractExpression * l_arr_index
			   , XtccSet & xs);

	StubManipStatement(DataType dtype, int32_t lline_number
		, int32_t l_nest_level, int32_t l_for_nest_level
		, named_range * l_named_range
		, Unary2Expression * p_name_expr
		);

	StubManipStatement(DataType dtype, int32_t lline_number
		, int32_t l_nest_level, int32_t l_for_nest_level
		, AbstractQuestion * l_named_range
		, Unary2Expression * p_arr_index
		, Unary2Expression * p_name_expr
		);


//	void GenerateCode(ostringstream & quest_defns
//			, ostringstream& program_code);
	virtual void GenerateCode(StatementCompiledCode & code);
	virtual ~StubManipStatement();
	private:
		StubManipStatement& operator=(const StubManipStatement&);
		StubManipStatement(const StubManipStatement&);
};

struct FunctionArgument
{
	struct expr* e;
	char * text;
	struct FunctionArgument * prev_;
	struct FunctionArgument * next_;
};


struct FunctionParameter
{
	DataType var_type;
	string var_name;
	int32_t arr_len;
	struct FunctionParameter * prev_, *next_;
	FunctionParameter(DataType type, char * name);
	FunctionParameter(DataType type, char * name, int32_t len);

	//void print(FILE * edit_out);
	void print(ostringstream & program_code);

	~FunctionParameter();
	private:
		FunctionParameter& operator=(const FunctionParameter&);
		FunctionParameter(const FunctionParameter&);

};

struct FunctionDeclarationStatement: public AbstractStatement
{
	struct FunctionInformation * funcInfo_;

	FunctionDeclarationStatement( DataType dtype
				      , int32_t lline_number
				      , int32_t l_nest_level
				      , int32_t l_for_nest_level
				      , char * & name
				      , FunctionParameter* & v_list
				      , DataType returnType_);
	//void GenerateCode(FILE * & fptr);
//	void GenerateCode(ostringstream & quest_defns
//			, ostringstream& program_code);
	virtual void GenerateCode(StatementCompiledCode & code);
	~FunctionDeclarationStatement();
	private:
	FunctionDeclarationStatement& operator=
		(const FunctionDeclarationStatement&);
	FunctionDeclarationStatement(const FunctionDeclarationStatement&);
};

struct FunctionStatement: public AbstractStatement
{
	struct FunctionInformation * funcInfo_;
	struct AbstractStatement *functionBody_;
	DataType returnType_;

	FunctionStatement ( DataType dtype, int32_t lline_number
			    , int32_t l_nest_level, int32_t l_for_nest_level
			    , struct Scope * &scope_
			    , struct FunctionParameter * & v_list
			    , struct AbstractStatement* & lfunc_body
			    , string func_name
			    , DataType lreturn_type);
	//void GenerateCode(FILE * & fptr);
//	void GenerateCode(ostringstream & quest_defns
//			, ostringstream& program_code);
	virtual void GenerateCode(StatementCompiledCode & code);
	~FunctionStatement();
	private:
	FunctionStatement& operator=(const FunctionStatement&);
	FunctionStatement(const FunctionStatement&);
};

//!FunctionInformation : parsed function declarations and definitions become object instantiations of this class
/*!
  Important notes for the FunctionInformation class:

  <p>
  When a function declaration is parsed all the variables
  which are function parameters become should available in the Scope of this
  function.

  On the other hand the function body (which is a compound statement)
  will appear at a later stage, i.e. the declaration of the function.

  The implementation of compound statements is that each compound statement contains
  a Scope variable of its own. Hence to bring the function parameter
  declarations into the Scope of the compound statement the following is done:

  <p>1. FunctionInformation has a Scope called functionScope_ - this Scope is allocated
     at the time of declaration of the function. This declaration is then
     stored in the func_info_table vector array
  <p>2. The grammar has a inline rule when detecting a function
  	definition - it sets the variable : flagIsAForBody_
	to the index of the function in the func_info_table vector array
	or -1 on failure. This grammar rule can be seen
	by searching for the pattern ^FunctionInformation in the "type.y" grammar
	file in the xtcc compiler sources. The simple compiler in qscript
	does not use functions as yet
  <p>3. When a compound body is being parsed (the ^open_curly rule in
  	type.y in the xtcc compiler - it checks if flagIsAFunctionBody_
	has been set and if so loads the Scope from the function declaration
	found in the  func_info_table array - by using the variable
	flagIsAFunctionBody_ - to index into the func_info_table

	Note that flagIsAFunctionBody_ is initialized to -1 as the 1st function
	will be in index 0 of func_info_table vector.
	Also lookup_func searches the func_info_table for the function name and returns -1 on failure
	this is naturally compatible with the initial value of flagIsAFunctionBody_
	if the flag is not set -> we need to allocate a new Scope - else we will crash

*/

struct FunctionInformation
{
	string functionName_;
	struct FunctionParameter * parameterList_;
	DataType returnType_;
	struct AbstractStatement * functionBody_;
	struct Scope * functionScope_;
	FunctionInformation(string name, FunctionParameter* elist
			    , DataType myreturn_type);
	void print(ostringstream & program_code);
	~FunctionInformation();
private:
	FunctionInformation& operator=(const FunctionInformation&);
	FunctionInformation(const FunctionInformation&);
};


struct ErrorStatement: public AbstractStatement
{
	ErrorStatement( int lline_number
			, int32_t l_nest_level, int32_t l_for_nest_level
			);
	void GenerateCode(StatementCompiledCode & code);
	private:
	ErrorStatement& operator=(const ErrorStatement&);
	ErrorStatement(const ErrorStatement&);
};

struct GotoStatement: public AbstractStatement
{
	string gotoLabel_;
	GotoStatement(DataType l_type, int32_t l_line_number
		      , int32_t l_nest_level, int32_t l_for_nest_level
		      , string l_gotoLabel);
	void GenerateCode(StatementCompiledCode & code);
	private:
	GotoStatement& operator=(const GotoStatement&);
	GotoStatement(const GotoStatement&);
};

struct ClearStatement: public AbstractStatement 
{
	/* 
	ClearStatement(DataType l_type, int32_t l_line_number
		       , int32_t l_nest_level, int32_t l_for_nest_level
		       , string l_question_name);
	ClearStatement(DataType l_type, int32_t l_line_number
			    , int32_t l_nest_level, int32_t l_for_nest_level
			, string l_question_name, string err_msg);
	ClearStatement(DataType l_type, int32_t l_line_number
		       , int32_t l_nest_level, int32_t l_for_nest_level
		       , string l_array_question_name
		       , AbstractExpression *e);
	ClearStatement(DataType l_type, int32_t l_line_number
		       , int32_t l_nest_level, int32_t l_for_nest_level
		       , string l_array_question_name
		       , AbstractExpression *e, string err_msg);
	*/
	ClearStatement(DataType l_type, int32_t l_line_number,
		        int32_t l_nest_level, int32_t l_for_nest_level,
			const vector <Unary2Expression *> & expr_vec, string err_msg);
	void GenerateCode(StatementCompiledCode & code);
	//bool VerifyForClearStatement(string l_question_name, AbstractExpression * arr_index);
	vector<bool> VerifyForClearStatement(const vector<Unary2Expression*> expr_vec);
	//SymbolTableEntry* symbolTableEntry_ ;
	//AbstractExpression * arrIndex_;
	vector <Unary2Expression*> questionExprVec_;
	string errorMessage_;
	private:
	ClearStatement& operator=(const ClearStatement&);
	ClearStatement(const ClearStatement&);
};

struct ColumnStatement;
bool RunColumnExpressionChecks(ColumnStatement * col_stmt);
struct ColumnStatement: public AbstractStatement
{
	AbstractExpression * columnExpression_;

	ColumnStatement(DataType l_type, int32_t l_line_number
			, int32_t l_nest_level, int32_t l_for_nest_level
			, AbstractExpression * expr);
	void GenerateCode(StatementCompiledCode & code);
	virtual void Generate_ComputeFlatFileMap(StatementCompiledCode & code);
	friend bool RunColumnExpressionChecks();
	private:
	ColumnStatement& operator=(const ColumnStatement&);
	ColumnStatement(const ColumnStatement&);
};

struct NewCardStatement;
bool RunNewCardExpressionChecks(NewCardStatement * col_stmt);
struct NewCardStatement: public AbstractStatement
{
	AbstractExpression * cardExpression_;

	NewCardStatement(DataType l_type, int32_t l_line_number
			 , int32_t l_nest_level, int32_t l_for_nest_level
			 , AbstractExpression * expr);
	void GenerateCode(StatementCompiledCode & code);
	virtual void Generate_ComputeFlatFileMap(StatementCompiledCode & code);
	friend bool RunColumnExpressionChecks();
	private:
	NewCardStatement& operator=(const NewCardStatement&);
	NewCardStatement(const NewCardStatement&);
};

struct FixAndRecodeStatement: public AbstractStatement
{
	vector <string> recode_vec,
			driver_vec;
	FixAndRecodeStatement(DataType l_type, int32_t l_line_number,
			      int32_t l_nest_level, int32_t l_for_nest_level,
			vector <string> l_recode_name_vec,
			vector <string> l_driver_vec)
		: AbstractStatement (l_type, l_line_number, l_nest_level, l_for_nest_level),
		  recode_vec (l_recode_name_vec),
		  driver_vec (l_driver_vec)
	{ }
	void GenerateCode(StatementCompiledCode & code)
	{
		if (next_) {
			next_->GenerateCode (code);
		}
	}
};


struct BrandRankRecodeStatement: public AbstractStatement
{
	vector <string> recode_vec,
			driver_vec;
	int32_t nRanks_;
	BrandRankRecodeStatement(DataType l_type, int32_t l_line_number,
			      int32_t l_nest_level, int32_t l_for_nest_level,
			vector <string> l_recode_name_vec,
			vector <string> l_driver_vec,
			int32_t p_n_ranks)
		: AbstractStatement (l_type, l_line_number, l_nest_level, l_for_nest_level),
		  recode_vec (l_recode_name_vec),
		  driver_vec (l_driver_vec),
		  nRanks_(p_n_ranks)
	{ }
	void GenerateCode(StatementCompiledCode & code)
	{
		if (next_) {
			next_->GenerateCode (code);
		}
	}
};

struct Create_1_0_DataEditStatement: public AbstractStatement
{
	string questionName_;
	Create_1_0_DataEditStatement(DataType l_type,
				     int32_t l_line_number,
				     int32_t l_nest_level, int32_t l_for_nest_level,
				     string question_name
				     )
		: AbstractStatement (l_type, l_line_number, l_nest_level, l_for_nest_level),
		  questionName_(question_name)
	{ }
	void GenerateCode(StatementCompiledCode & code)
	{
		if (next_) {
			next_->GenerateCode (code);
		}
	}
};

struct PageStatement: public AbstractStatement
{
	PageStatement (DataType dtype, int32_t lline_number,
			int32_t l_nest_level, int32_t l_for_nest_level,
			string l_page_name, CompoundStatement * l_page_body,
			int l_page_size = 0);
	// PageStatement(DataType dtype, int32_t lline_number,
	// 		string l_page_name,
	// 		int l_page_size,
	// 		CompoundStatement * l_page_body);
	std::string pageName_;
	int pageSize_;
	CompoundStatement * pageBody_;
	void GenerateConsolidatedForLoopIndexes();
	void GenerateCode(StatementCompiledCode & code);
	virtual void Generate_ComputeFlatFileMap(StatementCompiledCode & code);
	void GetQuestionNames(vector<string> & question_list,
			AbstractStatement* endStatement);
	void GetQuestionsInBlock( vector<AbstractQuestion*> & question_list
				, AbstractStatement * stop_at);
	private:
	PageStatement& operator=(const PageStatement&);
	PageStatement(const PageStatement&);
};




string helper_GenerateArrayInitLoopOpen (vector<AbstractExpression*> & for_bounds_stack);


struct named_attribute_list;
struct RandomizeStatement: public AbstractStatement
{
	RandomizeStatement(DataType dtype, int32_t lline_number,
			int32_t l_nest_level, int32_t l_for_nest_level,
			named_attribute_list * p_n_attr_list);
	// RandomizeStatement(DataType dtype, int32_t lline_number,
	// 		string l_page_name,
	// 		int l_page_size,
	// 		CompoundStatement * l_page_body);
	named_attribute_list * namedAttributeList_;
	void GenerateCode(StatementCompiledCode & code);
	private:
	RandomizeStatement& operator=(const RandomizeStatement&);
	RandomizeStatement(const RandomizeStatement&);

};


#endif /* stmt_h */
