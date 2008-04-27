/*
 * The main grammar for the xtcc parser
 * Copyright (C) 2003,2004, 2005,2006,2007  Neil Xavier D'Souza <nxd_in@yahoo.com>
 * Postal MAil address
 * Neil Xavier D'Souza
 * 502, Premier Park
 * 1st Tank Lane,
 * Orlem, Malad(W),
 * Mumbai India. 400064.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * The Free Software Foundation, 
 * 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

%{
#include "const_defs.h"
#include "symtab.h"
#include "tree.h"
#include "expr.h"
#include "stmt.h"
#include "Tab.h"
#include <cstring>
#include <iostream>
#include <vector>
#include "scope.h"
#include <map>
#include <sys/types.h>
#include <limits.h>

	using namespace std;

	const bool XTCC_DEBUG_MEM_USAGE=1;
	xtcc_set xs;

//	struct symtab symtab;
	extern int if_line_no;
	int no_errors=0;
	int no_warn=0;
	int yylex();
	void yyerror(char * s);
	extern int line_no;
	extern char * yytext;
	bool check_type_compat(datatype typ1, datatype typ2);
	vector <func_info*> func_info_table;
	int check_parameters(struct expr* e, struct var_list* v);
	vector <scope*> active_scope_list;
	scope* active_scope;
	map<string, symtab_ent*>::iterator find_in_symtab(string id);
	//struct stmt * load_func_into_symbol_table( char * & name,  struct var_list* & v_list, datatype int_type);
	bool skip_func_type_check(const char * fname);
	//void	add_func_params_to_cmpd_sc(struct scope * & sc, struct var_list * & v_list, string & fname);
	int search_for_func(string& search_for);
	int check_func_decl_with_func_defn(struct var_list*& v_list, int & index, string func_name);
	struct stmt* make_func_defn_stmt( struct scope *& sc,
		struct var_list * & v_list,
		struct stmt* & func_body,
		string search_for,
		datatype return_type
		);
	struct stmt * tree_root=0;
	bool 	void_check( datatype & type1, datatype & type2, datatype& result_type);
	template<class T> T* link_chain(T* & elem1, T* & elem2);
	template<class T> T* trav_chain(T* & elem1);

	int flag_cmpd_stmt_is_a_func_body=-1;
	int lookup_func(string func_name_index);
	vector<table*>	table_list;
	map <string, ax*> ax_map;

	int no_count_ax_elems=0;
	int no_tot_ax_elems=0;
	int in_a_loop=0;
	int nest_lev=0;
	int rec_len;
	bool flag_next_stmt_start_of_block=false;
	//struct stmt* start_of_blk=0;
	vector <stmt*> blk_heads;
	vector<bool> blk_start_flag;

	noun_list_type noun_list[]= {
			{	"void"	, VOID_TYPE},
			{	"int8_t" ,INT8_TYPE},
			{	"int16_t" ,INT16_TYPE},
			{	"int32_t" ,INT32_TYPE},
			{	"float", FLOAT_TYPE},
			{	"double", DOUBLE_TYPE}
		};
	vector<mem_addr_tab>  mem_addr;

	void flex_finish();

%}

%union {
	double dval;
	int ival ;
	struct symtab *symp;
	char * name;
	struct expr * expr;
	struct stmt * stmt;
	struct cmpd_stmt * c_stmt;
	int column_no;
	int code_list;
	char text_buf[MY_STR_MAX];
	struct var_list * v_list;
	datatype dt;
	struct ax * ax;
	struct table * tbl;
	class basic_ax_stmt * basic_ax_stmt;
};

%token CONVERT
%token	TOT AX ';' CNT '{' '}' TTL
%type <dt> xtcc_type
%type <tbl> tab_list
%type <tbl> tab_defn
%type <v_list> var_decl
%type <v_list> decl_comma_list
%type <expr> expression
%type <expr> expr_list
%type <stmt> top_level_item_list
%type <stmt> prog
%type <stmt> statement
%type <stmt> statement_list
%type <stmt> list_stmt
// %type <stmt> decl_list
%type <stmt> decl
%type <stmt> func_decl	
%type <c_stmt> compound_stmt	
%type <c_stmt> open_curly	
%type <stmt> top_level_item 
%type <stmt> func_defn 
%type <stmt> if_stmt 
%type <stmt> fld_stmt 
%token  FOR
%token FLD
%token <text_buf> TEXT
%token <name> NAME
%token DEFINELIST 
%token <dval> FNUMBER
%token <ival> INUMBER
//%token <column_no> SCOLUMN
%token <code_list> CODELIST
%token LISTA
%token IF
%token ELSE
%token IN
%token '['
%token ']'
%token '('
%token ')'
%token '='
 /*%token <dt> INT*/
 /*%token <dt> CHAR*/
%token <dt> VOID_T
%token <dt> INT8_T
%token <dt> INT16_T
%token <dt> INT32_T
%token <dt> FLOAT_T
%token <dt> DOUBLE_T

%token AXSTART
%token TABSTART
%token ED_START
%token DATA_STRUCT
%token REC_LEN
%token ED_END
%token TAB
%token COND_START
%type <ax>	ax_list
%type <ax>	ax_defn
%type <basic_ax_stmt> ax_stmt_list
%type <basic_ax_stmt> ax_stmt

%token CONTINUE BREAK





%left ','
%right '='
%left LOGOR
%left LOGAND
%left ISEQ NOEQ 
%left LEQ GEQ '<' '>' 
%left '-' '+'
%left '*' '/' '%'
%nonassoc NOT
%nonassoc UMINUS
%nonassoc FUNC_CALL




%%

prog: DATA_STRUCT ';' REC_LEN '=' INUMBER ';' 
	{	const char * c_arr="c";  
		rec_len=$5; 
		active_scope->insert(c_arr, INT8_ARR_TYPE, rec_len, 0);
	} 
	ED_START top_level_item_list ED_END {
		tree_root = trav_chain($9);
		if(tree_root==0){
			cerr << "tree_root =0 : core dump expected" << endl;
		}
		return 0;
	}
	| AXSTART '{' ax_list 	'}'	{
		return 0;
	}
	| TABSTART '{' tab_list '}' {
		return 0;
	}
	;

top_level_item_list: top_level_item {
		$$=$1;
	}
	| top_level_item_list top_level_item {
		$$=link_chain($1,$2);
	}
	;

top_level_item: decl{
			$$=$1;
	}
	| func_defn	{
		$$=$1;
	}
	;

xtcc_type: VOID_T
	|INT8_T
	|INT16_T
	|INT32_T  	
	|FLOAT_T
	|DOUBLE_T
	;


func_defn:	
	xtcc_type NAME '(' decl_comma_list ')' {
		string func_name_index($2);
		flag_cmpd_stmt_is_a_func_body=lookup_func(func_name_index);
		if(flag_cmpd_stmt_is_a_func_body==-1){
			++ no_errors;
			cerr << "Function name not found in list of declared functions: "
				<< "You will see another error on this same function name: " << func_name_index
				<< "line_no: " << line_no  << endl;
		}
	} compound_stmt {
		struct cmpd_stmt* c_stmt= $7;
		if(c_stmt==0){
			cerr << "INTERNAL COMPILER ERROR: c_stmt==0" << endl;
		} else {
			//cout << "func_body: is valid " << endl;
		}
		struct scope *sc=c_stmt->sc;
		struct var_list * v_list=trav_chain($4);
		struct stmt* func_body=$7;
		string search_for=$2;
		datatype return_type=$1;
		$$=new func_stmt(FUNC_DEFN, line_no, sc, v_list, func_body, search_for, return_type);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		// Note that the declaration already has a parameter list
		// the constructor uses the parameter list - name and type to verify everything
		// but doesnt need the parameter list any more - so we should delete it 
		// - took me a while to figure out this memory leak
		delete v_list;
		free($2);
	}
	;


decl:	xtcc_type NAME ';' {
		$$ = active_scope->insert($2, $1/*, line_no*/);
		free($2);
	} 
	| xtcc_type NAME '=' expression ';'{
		$$ = active_scope->insert($2, $1, $4);

	}
	|	xtcc_type NAME '[' INUMBER ']' ';' {
		/* NxD: I have ordered the types in datatype so that this hack is possible I hope */
		datatype dt=datatype(INT8_ARR_TYPE+($1-INT8_TYPE));
		$$ = active_scope->insert($2, dt, $4/*, line_no*/);
		free($2);
	}
	/*
	NxD I only want to allow references in function parameter lists 
	|	xtcc_type '&' NAME {
		cout << "creating ref var of type: " << $1 << endl;
		datatype dt=datatype(INT8_REF_TYPE+($1-INT8_TYPE));
		$$ = active_scope->insert($3, dt, line_no);
	}
	*/
	| DEFINELIST NAME '=' range_list ';' {
		$$ = active_scope->insert($2, RANGE_DECL_STMT, &xs);
		//$$ = new decl_stmt($2, RANGE_DECL_STMT, &xs );
	}
	| func_decl	{
		$$=$1;
	}
	;


func_decl:	xtcc_type NAME '(' decl_comma_list ')' ';'{
		char *name=$2;
		struct var_list* v_list=trav_chain($4);
		datatype return_type=$1;
		$$=new func_decl_stmt( FUNC_TYPE, line_no, name,  v_list, return_type);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	;


decl_comma_list: var_decl	{
		 $$=$1;
		 //cout << "got decl_comma_list : " << endl;
	}
	| decl_comma_list ',' var_decl {
		$$=link_chain($1,$3);
		//cout << "chaining var_decl : " << endl;
	}
	;


var_decl:	xtcc_type NAME 	{
		$$=new var_list($1, $2);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($2);
	}
	| xtcc_type NAME '[' INUMBER ']'  {
		/* Neil - I need to fix this */
		datatype dt=datatype(INT8_ARR_TYPE+($1-INT8_TYPE));
		$$=new var_list(dt, $2, $4);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($2);
	}
	|	xtcc_type '&' NAME {
		datatype dt=datatype(INT8_REF_TYPE+($1-INT8_TYPE));
		$$=new var_list(dt, $3);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($3);
	}
	|	/* empty */
		{
		$$=0;
		}
	;

statement_list: statement {
		$$=$1; 
		if(flag_next_stmt_start_of_block){
			blk_heads.push_back($1);
			//cout << "blk_heads.size(): " << blk_heads.size() << endl;
			//start_of_blk=$1;
			flag_next_stmt_start_of_block=false;
			blk_start_flag.pop_back();
		}
	}
	|	statement_list statement {
		$$=link_chain($1,$2);
	}
	;

statement: FOR '(' expression ';' expression ';' expression ')' { ++in_a_loop;} statement {
		$$ = new struct for_stmt(FOR_STMT, line_no, $3, $5, $7, $10);
		--in_a_loop;
	}
	| if_stmt
	| expression ';' { 
		if($1->isvalid()){
			$$ = new expr_stmt(TEXPR_STMT, line_no, $1);
			if(XTCC_DEBUG_MEM_USAGE){
				mem_log($$, __LINE__, __FILE__, line_no);
			}
		} else {
			$$ = new expr_stmt(ERROR_TYPE, line_no, $1);
			if(XTCC_DEBUG_MEM_USAGE){
				mem_log($$, __LINE__, __FILE__, line_no);
			}
		}
	}
	|	compound_stmt {
		$$=$1;
	}
	|	decl {
		$$=$1;
	}
	|	list_stmt
	|	BREAK ';'{
		$$=new break_stmt(BREAK_STMT, line_no, in_a_loop);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| 	CONTINUE ';' {
		$$=new continue_stmt(CONTINUE_STMT, line_no, in_a_loop);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	fld_stmt
	|	error ';' {
		print_err(compiler_sem_err, "statement missing ';' around line_no: ", 
			line_no, __LINE__, __FILE__);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		$$ = new struct err_stmt(line_no);
		yyerrok;
	}
	;

list_stmt:	 LISTA NAME TEXT ';'{
		$$=new list_stmt(LISTA_BASIC_TYPE_STMT, $2, $3);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($2);
	}
	| LISTA NAME '[' expression ']' TEXT ';'{
		$$=new list_stmt( LISTA_BASIC_ARRTYPE_STMT_1INDEX, $2, string($6), $4);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($2);
	}
	| LISTA NAME '[' expression ',' expression ']' TEXT ';'{
		$$=new list_stmt( LISTA_BASIC_ARRTYPE_STMT_1INDEX, $2, string($8), $4, $6);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($2);	
	}
	;

if_stmt: IF '(' expression ')' statement{
		$$=new if_stmt(IFE_STMT,if_line_no,$3,$5,0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| IF '(' expression ')' statement ELSE statement{
		$$=new if_stmt(IFE_STMT, if_line_no,$3,$5,$7);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	;

fld_stmt:	FLD NAME '=' NAME '(' expression ',' expression ')' ':' INUMBER ';'{
		expr* start_col=$6;
		expr* end_col=$8;
		int width=$11;
		$$ = new fld_stmt($2, $4, start_col, end_col, width);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($2), free($4);
	}
	;

compound_stmt: open_curly statement_list '}'	{
		active_scope_list.pop_back();
		int tmp=active_scope_list.size()-1;
		if(tmp==-1) { 
			active_scope = 0;
			cerr << "Error: active_scope = NULL: should not happen: line_no:" << line_no
				<< endl;
			++no_errors;
			$$=new struct cmpd_stmt(ERROR_TYPE, line_no, 0);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		} else { active_scope = active_scope_list[tmp]; }
		struct stmt* head_of_this_chain=blk_heads.back();
		if(blk_start_flag.size() > 0){
			flag_next_stmt_start_of_block = blk_start_flag[blk_start_flag.size()-1];
		}
		if(  head_of_this_chain==0){
			cerr << "Error in compiler : cmpd_bdy:  " << __FILE__ << __LINE__ << endl;
			++no_errors;
		} else {
			$1->cmpd_bdy = head_of_this_chain;
			blk_heads.pop_back();
		}
		
		$$=$1;
	}
	;
	/* Very important point to note
	 * The scope for a function is created at the time of declaration
	 * and all the variables are dumped into it. This is loaded here if we are a function scope
	 * - otherwise if we are the scope of a for / while / if/else stmt - we create a new one
	 */

open_curly:	'{' {
		++nest_lev;
		$$ = new cmpd_stmt(CMPD_STMT, line_no, flag_cmpd_stmt_is_a_func_body);
		void *ptr=$$;
		mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
		mem_addr.push_back(m1);
		if(flag_cmpd_stmt_is_a_func_body>=0){
			$$->sc=func_info_table[flag_cmpd_stmt_is_a_func_body]->func_scope;
			// reset the flag
			flag_cmpd_stmt_is_a_func_body=-1;
		} else {
			$$->sc= new scope();
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		}
		flag_next_stmt_start_of_block=true;
		blk_start_flag.push_back(flag_next_stmt_start_of_block);
		active_scope_list.push_back($$->sc);
		active_scope = $$->sc;
	}
	;


expr_list: expression { $$=$1; }
	| expr_list ',' expression {
		$$=link_chain($1,$3);
	}
	;

expression: expression '+' expression {
		$$=new bin_expr($1, $3, oper_plus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '-' expression {
		$$=new bin_expr($1, $3, oper_minus);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '*' expression {
		$$=new bin_expr($1, $3, oper_mult);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '/' expression {
		$$=new bin_expr($1, $3, oper_div);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '%' expression {
		$$=new bin_expr($1, $3, oper_mod);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	'-' expression %prec UMINUS {
		$$ = new un_expr($2, oper_umin);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '<' expression {
		$$=new bin_expr($1, $3, oper_lt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression '>' expression {
		$$=new bin_expr($1, $3, oper_gt);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression LEQ expression {
		$$=new bin_expr($1, $3, oper_le);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression GEQ expression {
		$$=new bin_expr($1, $3, oper_ge);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression ISEQ expression {
		$$=new bin_expr($1, $3, oper_iseq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	expression NOEQ expression {
		$$=new bin_expr($1, $3, oper_isneq);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}	
	| expression LOGOR expression {
		$$=new bin_expr($1, $3, oper_or);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}	
	| expression LOGAND expression {
		$$=new bin_expr($1, $3, oper_and);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| expression '=' expression {
		$$ = new bin_expr($1, $3, oper_assgn);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	NOT expression {
		$$ = new un_expr($2, oper_not);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	INUMBER	{
		$$ = new un2_expr($1);
		//cout << "got INUMBER: " << $1 << " type : " << $$->type << endl;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	FNUMBER {
		$$ = new un2_expr($1);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	NAME	{
		$$ = new un2_expr($1, oper_name );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| 	NAME '[' expression ']' %prec FUNC_CALL {
		$$ = new un2_expr(oper_arrderef, /*nametype,  se,*/ $1,$3);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($1);
	}
	| NAME '[' expression ',' expression ']'  %prec FUNC_CALL {
		$$ = new un2_expr(oper_blk_arr_assgn, $1,$3,$5);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($1);
	}
	| NAME '(' expr_list ')' %prec FUNC_CALL{
		//cout << "parsing Function call: name: " << $1 << endl;
		string search_for=$1;
		bool found=false;
		int index=search_for_func(search_for);
		if(index!=-1) found=true;
		bool skip_type_check=skip_func_type_check(search_for.c_str());
		if( skip_type_check==false  && found==false ) {
			cerr << "ERROR: function call Error on line_no: " << line_no << endl;
			cerr << "function : " << search_for << " used without decl" << endl;
			++ no_errors;
			$$=new un2_expr(ERROR_TYPE);
			void *ptr=$$;
			mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
			mem_addr.push_back(m1);
		} else {
			datatype my_type=func_info_table[index]->return_type;
			expr* e_ptr=trav_chain($3);
			var_list* fparam=func_info_table[index]->param_list;
			bool match=false;
			if(skip_type_check==false){
				match=check_parameters(e_ptr, fparam);
			}
			if(match || skip_type_check){
				//$$=new un2_expr(oper_func_call, my_type, $3, index, line_no);
				$$=new un2_expr(oper_func_call, my_type, e_ptr, index, line_no);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);

			} else {
				$$=new un2_expr(ERROR_TYPE);
				void *ptr=$$;
				mem_addr_tab m1(ptr, line_no, __FILE__, __LINE__);
				mem_addr.push_back(m1);
			}
		}
		free($1);
	}
	|	TEXT {
		$$ = new un2_expr(strdup($1), oper_text_expr);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| 	'(' expression ')' %prec UMINUS{ 
		$$ = new un_expr($2, oper_parexp );
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| NAME IN NAME {
		$$ = new bin2_expr($1, $3, oper_in);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	;

range_list: range
	| range_list ',' range
	;

range: 	INUMBER '-' INUMBER {
		if($3<=$1){
			print_err(compiler_sem_err, "2nd number in range <= 1st number",
					line_no, __LINE__, __FILE__  );

		} else {
			xs.range.push_back( pair<int,int>($1,$3));
		}
	}
	|	INUMBER {
		xs.indiv.insert($1);
	}
	;

tab_list: tab_defn	{ 
#ifdef DEBUG_GRAM
	printf("got table defn\n"); 
#endif
	}
	| tab_list tab_defn { 
#ifdef DEBUG_GRAM
		printf("recursive tab_defn\n"); 
#endif
	}
	;

tab_defn:
	TAB NAME NAME';'	{
		$$=new table($2,$3, line_no);
		table_list.push_back($$);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($2); free($3);
	}
	| TAB NAME NAME';'COND_START expression';'{
		$$=new table($2,$3, line_no, $6);
		table_list.push_back($$);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		free($2); free($3);
	}
	| error ';' {
		cerr << "Error in tab section line: " <<
			line_no << endl;
		++no_errors;
	}
	;

ax_list:	ax_defn	{
	}	
	|	ax_list ax_defn	{
	}
	;

ax_defn:	AX NAME ';' ax_stmt_list {
		basic_ax_stmt* bptr= trav_chain($4);
		$$ = new ax(bptr,no_count_ax_elems, no_tot_ax_elems, 0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		
		ax_map[$2]=$$;
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		free($2);
	}
	|	AX NAME ';'COND_START expression ';' ax_stmt_list {
		basic_ax_stmt* bptr= trav_chain($7);
		$$ = new ax(bptr,no_count_ax_elems, no_tot_ax_elems, $5);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
		ax_map[$2]=$$;
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		free($2);
	}
	| error ';'	{
		cerr << "Error in axis section line: " <<
			line_no << endl;
		no_count_ax_elems=0;	
		no_tot_ax_elems=0;
		++no_errors;
	}
	;


ax_stmt_list: 	
	ax_stmt	{
		$$ = $1;
	}
	|	ax_stmt_list ax_stmt	{
		$$=link_chain($1, $2);
	}
	;

ax_stmt:	TOT ';' TEXT ';' {
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		$$ = new tot_ax_stmt (tot_axstmt,$3, 0);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| TOT ';' TEXT ';' COND_START expression ';'	{
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		$$ = new tot_ax_stmt (tot_axstmt,$3, $6);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	|	CNT ';'	TEXT ';' COND_START expression ';' 	{
		++no_count_ax_elems;	
		++no_tot_ax_elems;
		$$ = new count_ax_stmt (cnt_axstmt,$3, $6);
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	| 	TTL ';' TEXT ';'	{
		$$ = new ttl_ax_stmt (txt_axstmt,$3);
		++no_tot_ax_elems;
		if(XTCC_DEBUG_MEM_USAGE){
			mem_log($$, __LINE__, __FILE__, line_no);
		}
	}
	;

%%


template<class T> T* link_chain(T* &elem1, T* &elem2){
	elem2->prev=elem1;
	elem1->next=elem2;
	return elem2;
}

template<class T> T* trav_chain(T* & elem1){
	if(elem1){
		while (elem1->prev) elem1=elem1->prev;
		return elem1;
	} else return 0;
}

