%{
#define MY_STR_MAX 50
#include "stmt.h"
#include "expr.h"
//#include "range_set.h"
#include "symtab.h"
#include <iostream>
#include "xtcc_set.h"
	//range_data r_data;
	xtcc_set xs;
	extern int line_no;
	int yylex();
	int no_errors=0;
	void yyerror(char * s);
	struct stmt* tree_root;
	string get_temp_name();



%}


%union {
	datatype dt;
	int ival ;
	char name[MY_STR_MAX];
	struct expr * expr;
	struct stmt * stmt;
};

%token <ival> INUMBER
%type <expr> expr
%type <stmt> stmt
%type <stmt> stmt_list
%token <name> NAME
%nonassoc IN
%left LOGAND

%type <dt> range_allowed_values

%%

prog: stmt_list {
	tree_root=$1;
		while(tree_root->prev){
			tree_root=tree_root->prev;
		}
	}

stmt_list: stmt { 
		$$=$1;
		cout << "got stmt" << endl;
	}
	| stmt_list stmt {
		$1->next =$2;
		$2->prev=$1;
		cout << "chaining" << endl;
		$$=$2;
	}
	;

stmt: expr ';' {
		$$ = new expr_stmt(line_no, $1);
	}
	;



expr: expr LOGAND expr {
		$$=new bin_expr($1, $3, oper_and);
	}
	| NAME IN range_allowed_values {
		$$=new bin2_expr($1, xs, oper_in);
		xs.reset();
		//r_data.icount=0;
		//r_data.rcount=0;
	}
	;

range_allowed_values: '(' number_range_list ')' { 
		$$=UNNAMED_RANGE;
	}
	;


number_range_list: number_range {
	}
	| number_range_list ',' number_range {
	}
	;

number_range: INUMBER '-' INUMBER {
                if( $3 <=$1 ) {
                        cout << "error on lineno: " << line_no
                                << "2nd number in range <= 1st number"
                                << endl;
                } else {
#if 0
			if(r_data.rcount<MAX_RANGE_ELEMENTS/2){
				r_data.ran_start_end[r_data.rcount*2  ]=$1;
				r_data.ran_start_end[r_data.rcount*2+1]=$3;
				++r_data.rcount;
			} else {
				cerr << "range_list: ran_start_end rcount : buffer overflow:\n";
				cerr << " I should use vector and get rid of this restriction\n";
			}
#endif /* 0 */
			xs.add_range($1, $3);
                }
        }
	| INUMBER {
#if 0
                if(r_data.icount<MAX_RANGE_ELEMENTS){
                        r_data.ran_indiv[r_data.icount]=$1;
			++r_data.icount;
		} else {
                        cerr << "range_list: ran_indiv : buffer overflow:\n";
				cerr << " I should use vector and get rid of this restriction\n";
                }
#endif /* 0 */
		xs.add_indiv($1);
        }
	;

%%

void generate_code();

int main(){
	int no_errors=yyparse();
	if(!no_errors){
		generate_code();
		return 0;
	} else return no_errors;
	/*
	for(int i=0; i<1000; i++){
		cout << get_temp_name() << endl;
	}
	*/

}


string get_temp_name(){
	// about a billion temporaries before we run out
	const int max_temp=10;
	static int count=0;
	char buffer[max_temp];
	char op_buf[max_temp];
	int dividend=count;

	buffer[0]='0'; buffer[1]='\0';

	int j=0;
	do {
		int rem = dividend%10;
		dividend=dividend/10;
		buffer[j++]='0' + rem;
	} while(dividend>0);
	/*
	for(int i=0 ; dividend/10>0; dividend=dividend/10,++i,++j){
		//int quot = dividend/10;
		int rem = dividend%10;
		buffer[j]='0' + rem;
	}
	*/
	buffer[j]='\0';
	for(int i=j-1; i>=0; --i){
		op_buf[j-1-i]=buffer[i];
	}
	op_buf[j]='\0';
	string s(op_buf);
	++count;
	//cout << s << endl;
	string s1="temp_"+s;
	return s1;
}


void generate_code(){
	FILE * op=fopen("expr_oper_in_output.C", "w");
	struct stmt* st_ptr=tree_root;
	st_ptr->print_stmt_lst(op);
	fclose(op);
}
