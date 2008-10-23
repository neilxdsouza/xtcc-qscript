#ifndef STMT_H
#define STMT_H

#include <cstdio>
#include "expr.h"
#include <sstream>
#include <iostream>
using namespace std;

struct stmt {
	public:
	struct stmt * prev;
	struct stmt * next;
	int line_number;
	virtual void print_stmt_lst(FILE * & fptr)=0;
	bool exists_next(){
		return prev;
	}
	bool exists_prev(){
		return next;
	}
	stmt* move_next(){
		return prev;
	}
	stmt(int lline_number=0):prev(0), next(0), line_number(lline_number){}
	virtual ~stmt();
	private:
		stmt(const stmt&);
		stmt& operator=(const stmt&);
};

struct expr_stmt: public stmt{
	struct expr* expr;
	expr_stmt(int lline_number, struct expr* e): stmt(lline_number), expr(e) {}
	void print_stmt_lst(FILE * & fptr){
		cout << "expr_stmt::print_stmt_lst()" << endl;
		fflush(fptr);
		if(fptr){
			//print_expr(fptr, expr);
			ostringstream code_bef_expr, code_expr;
			expr->print_expr(code_bef_expr, code_expr);
			fprintf(fptr, "%s\n", code_bef_expr.str().c_str());
			fprintf(fptr, "%s\n", code_expr.str().c_str());
			fprintf(fptr,";\n");
			if(next) next->print_stmt_lst(fptr);
		}
	}
	virtual ~expr_stmt();
	private:
	expr_stmt& operator=(const expr_stmt&);	
	expr_stmt(const expr_stmt&);	
};

#endif /* STMT_H */
