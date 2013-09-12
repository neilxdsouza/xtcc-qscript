/*
 * =====================================================================================
 *
 *       Filename:  edit_out.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 12 September 2013 
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef edit_out_h
#define edit_out_h
#include <iostream>

using std::cerr;
using std::endl;

struct EditDataStruct {
int8_t c[89];
int32_t all; /*  nest_lev:  0 */
int32_t ser_no; /*  nest_lev:  0 */
int32_t q1_data; /*  nest_lev:  0 */
int32_t q2_arr [ 6 ]; /*  nest_lev:  0 */
int32_t q3_arr [ 6 ]; /*  nest_lev:  0 */
int32_t q4_data; /*  nest_lev:  0 */
int32_t q6_0_data; /*  nest_lev:  0 */
int32_t q6_1_data; /*  nest_lev:  0 */
int32_t q6_2_data; /*  nest_lev:  0 */
int32_t q6_3_data; /*  nest_lev:  0 */
int32_t q6_4_data; /*  nest_lev:  0 */
int32_t q5_0_data; /*  nest_lev:  0 */
int32_t q5_1_data; /*  nest_lev:  0 */
int32_t q5_2_data; /*  nest_lev:  0 */
int32_t q5_3_data; /*  nest_lev:  0 */
int32_t edit_data/* comment */
(){

all /* oper_assgn */ = 1
;

/* DATA CONVERSION */
{const int tmp1=0;
const int tmp2=3;
if(tmp2-tmp1==sizeof(int)-1){
	char buff[sizeof(int)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	int *i_ptr = static_cast<int *>(v_ptr);
	ser_no=*i_ptr;
}else { 
	cerr << "runtime error: line_no : AbstractExpression out of bounds" <<39 ;}
}

;

/* DATA CONVERSION */
{const int tmp1=4;
const int tmp2=7;
if(tmp2-tmp1==sizeof(int)-1){
	char buff[sizeof(int)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	int *i_ptr = static_cast<int *>(v_ptr);
	q1_data=*i_ptr;
}else { 
	cerr << "runtime error: line_no : AbstractExpression out of bounds" <<39 ;}
}

;
/* FieldStatement  code will be generated here */
{
	for (int i=0; i<6; ++i) q2_arr[i]=0;
const int start_col=8,end_col=27,width=4;
if( start_col > end_col){
	printf("start_col evaluated > end_col -> runtime error");
}
if( (end_col-start_col +1) % width!=0 ){
		printf("expr value:%d", end_col-start_col +1 % width );	printf("please check your start_col=%d ,  end_col=%d, width=%d for fld statement-> runtime error\n", start_col, end_col, width);
}
for (int i=start_col; i<= end_col+1-width; i+=width){
		char buff[4];
		for(int s=i,j=0;s<i+width;++s,++j){
				buff[j]=c[s];
		}
	void * v_ptr = buff;
		int  *i_ptr = static_cast<int *>(v_ptr);
		int tmp=*i_ptr;
		if(tmp>=1 && tmp <=6){
			++q2_arr[tmp];
			++q2_arr[0];
		} else if (tmp == 0) {
		} else {
			fprintf(runtime_errors, " runtime warning: code: %d at variable: q2_arr too big to fit in array. ser_no: %d \n", tmp, ser_no);
		}
;}} 
/* FieldStatement  code will be generated here */
{
	for (int i=0; i<6; ++i) q3_arr[i]=0;
const int start_col=28,end_col=47,width=4;
if( start_col > end_col){
	printf("start_col evaluated > end_col -> runtime error");
}
if( (end_col-start_col +1) % width!=0 ){
		printf("expr value:%d", end_col-start_col +1 % width );	printf("please check your start_col=%d ,  end_col=%d, width=%d for fld statement-> runtime error\n", start_col, end_col, width);
}
for (int i=start_col; i<= end_col+1-width; i+=width){
		char buff[4];
		for(int s=i,j=0;s<i+width;++s,++j){
				buff[j]=c[s];
		}
	void * v_ptr = buff;
		int  *i_ptr = static_cast<int *>(v_ptr);
		int tmp=*i_ptr;
		if(tmp>=1 && tmp <=6){
			++q3_arr[tmp];
			++q3_arr[0];
		} else if (tmp == 0) {
		} else {
			fprintf(runtime_errors, " runtime warning: code: %d at variable: q3_arr too big to fit in array. ser_no: %d \n", tmp, ser_no);
		}
;}} 

/* DATA CONVERSION */
{const int tmp1=48;
const int tmp2=51;
if(tmp2-tmp1==sizeof(int)-1){
	char buff[sizeof(int)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	int *i_ptr = static_cast<int *>(v_ptr);
	q4_data=*i_ptr;
}else { 
	cerr << "runtime error: line_no : AbstractExpression out of bounds" <<39 ;}
}

;

/* DATA CONVERSION */
{const int tmp1=52;
const int tmp2=55;
if(tmp2-tmp1==sizeof(int)-1){
	char buff[sizeof(int)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	int *i_ptr = static_cast<int *>(v_ptr);
	q6_0_data=*i_ptr;
}else { 
	cerr << "runtime error: line_no : AbstractExpression out of bounds" <<39 ;}
}

;

/* DATA CONVERSION */
{const int tmp1=56;
const int tmp2=59;
if(tmp2-tmp1==sizeof(int)-1){
	char buff[sizeof(int)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	int *i_ptr = static_cast<int *>(v_ptr);
	q6_1_data=*i_ptr;
}else { 
	cerr << "runtime error: line_no : AbstractExpression out of bounds" <<39 ;}
}

;

/* DATA CONVERSION */
{const int tmp1=60;
const int tmp2=63;
if(tmp2-tmp1==sizeof(int)-1){
	char buff[sizeof(int)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	int *i_ptr = static_cast<int *>(v_ptr);
	q6_2_data=*i_ptr;
}else { 
	cerr << "runtime error: line_no : AbstractExpression out of bounds" <<39 ;}
}

;

/* DATA CONVERSION */
{const int tmp1=64;
const int tmp2=67;
if(tmp2-tmp1==sizeof(int)-1){
	char buff[sizeof(int)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	int *i_ptr = static_cast<int *>(v_ptr);
	q6_3_data=*i_ptr;
}else { 
	cerr << "runtime error: line_no : AbstractExpression out of bounds" <<39 ;}
}

;

/* DATA CONVERSION */
{const int tmp1=68;
const int tmp2=71;
if(tmp2-tmp1==sizeof(int)-1){
	char buff[sizeof(int)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	int *i_ptr = static_cast<int *>(v_ptr);
	q6_4_data=*i_ptr;
}else { 
	cerr << "runtime error: line_no : AbstractExpression out of bounds" <<39 ;}
}

;

/* DATA CONVERSION */
{const int tmp1=72;
const int tmp2=75;
if(tmp2-tmp1==sizeof(int)-1){
	char buff[sizeof(int)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	int *i_ptr = static_cast<int *>(v_ptr);
	q5_0_data=*i_ptr;
}else { 
	cerr << "runtime error: line_no : AbstractExpression out of bounds" <<39 ;}
}

;

/* DATA CONVERSION */
{const int tmp1=76;
const int tmp2=79;
if(tmp2-tmp1==sizeof(int)-1){
	char buff[sizeof(int)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	int *i_ptr = static_cast<int *>(v_ptr);
	q5_1_data=*i_ptr;
}else { 
	cerr << "runtime error: line_no : AbstractExpression out of bounds" <<39 ;}
}

;

/* DATA CONVERSION */
{const int tmp1=80;
const int tmp2=83;
if(tmp2-tmp1==sizeof(int)-1){
	char buff[sizeof(int)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	int *i_ptr = static_cast<int *>(v_ptr);
	q5_2_data=*i_ptr;
}else { 
	cerr << "runtime error: line_no : AbstractExpression out of bounds" <<39 ;}
}

;

/* DATA CONVERSION */
{const int tmp1=84;
const int tmp2=87;
if(tmp2-tmp1==sizeof(int)-1){
	char buff[sizeof(int)];int i,j;
	for(i=tmp1,j=0;i<=tmp2;++i,++j){
		buff[j]=c[i];
	}
	void * v_ptr = buff;
	int *i_ptr = static_cast<int *>(v_ptr);
	q5_3_data=*i_ptr;
}else { 
	cerr << "runtime error: line_no : AbstractExpression out of bounds" <<39 ;}
}

;
}
};

#endif /* edit_out_h  */
