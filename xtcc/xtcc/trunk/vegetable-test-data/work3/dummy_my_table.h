#ifndef MY_TABLE_H
#define MY_TABLE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
#include "global.h"
#include "my_axes.h"
#include "edit_out.h"
extern struct axis_tot_ax ax_tot_ax;
/* stub_hint_axis is empty  */
extern struct axis_q1 ax_q1;
/* stub_hint_axis is empty  */
extern struct axis_q2 ax_q2;
/* stub_hint_axis has data : q2*/
extern struct axis_q2 ax_q3;
/* stub_hint_axis is empty  */
extern struct axis_q4 ax_q4;
/* stub_hint_axis is empty  */
extern struct axis_q6_0 ax_q6_0;
/* stub_hint_axis is empty  */
extern struct axis_q6_1 ax_q6_1;
/* stub_hint_axis is empty  */
extern struct axis_q6_2 ax_q6_2;
/* stub_hint_axis is empty  */
extern struct axis_q6_3 ax_q6_3;
/* stub_hint_axis is empty  */
extern struct axis_q6_4 ax_q6_4;
/* stub_hint_axis is empty  */
extern struct axis_q5_0 ax_q5_0;
/* stub_hint_axis has data : q5_0*/
extern struct axis_q5_0 ax_q5_1;
/* stub_hint_axis has data : q5_0*/
extern struct axis_q5_0 ax_q5_2;
/* stub_hint_axis has data : q5_0*/
extern struct axis_q5_0 ax_q5_3;
struct table_q1_tot_ax {
	struct axis_q1 & ax_q1;
	struct axis_tot_ax & ax_tot_ax;
	int32_t & q1_data;
	int32_t & all;
	const int rows, cols;
	vector <int> counter;
	table_q1_tot_ax (struct axis_q1 & p_ax_q1, struct axis_tot_ax & p_ax_tot_ax, int32_t & p_q1_data, int32_t & p_all)
	: rows(3), cols(1),counter(3*1), ax_q1(p_ax_q1)
	, ax_tot_ax(p_ax_tot_ax) , q1_data (p_q1_data) , all (p_all)
	{
		for (int i=0;i<counter.size();++i) counter[i]=0; 
	}
	void compute(){
		if(ax_q1.flag[0] && ax_tot_ax.flag[0]){
			++counter[0*cols+0];
		}
		if(ax_q1.flag[1] && ax_tot_ax.flag[0]){
			++counter[1*cols+0];
		}
		if(ax_q1.flag[2] && ax_tot_ax.flag[0]){
			++counter[2*cols+0];
		}
	} /*  close compute */
	void print(){
		int rci=0, cci=0; /* row counter index , col ... */
		ofstream tab_op("tab_.csv", ios_base::out|ios_base::app);
		tab_op << "rows" << "," << rows << ",cols" << "," << cols << endl;
		tab_op << "\"" << ax_q1.ttl_stmt_text[0] << "\"" << "," <<  "\"" << ax_tot_ax.ttl_stmt_text[0] << "\""  << endl;
		tab_op << ",,";
		for(int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j){
			 tab_op << "\"" << ax_tot_ax.count_stmt_text[j] << "\""  << "," ;
		}
		tab_op << endl;
		int inc_counter=0;
		for (int i=0; i<ax_q1.count_stmt_text.size(); ++i) {
			tab_op << ",";
			stringstream col_perc_str;
			stringstream row_perc_str;
			col_perc_str << ",,";
			row_perc_str << ",,";
			cci=0;
			tab_op << "\"" << ax_q1.count_stmt_text[i] << "\"" << ",";
				if (ax_q1.axis_stmt_type_count[rci] == Table::inc_axstmt) {
					++inc_counter;
				}
			for (int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j) {
				if (ax_q1.axis_stmt_type_count[rci] == Table::cnt_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
					if (ax_q1.tot_elem_pos_vec.size()>0) {
						col_perc_str << (((double) counter[cci+rci*cols]) / counter[cci+ax_q1.tot_elem_pos_vec[0]*cols]) * 100 <<",";
					}
					if (ax_tot_ax.tot_elem_pos_vec.size()>0) {
						row_perc_str << (((double) counter[cci+rci*cols]) / counter[ax_tot_ax.tot_elem_pos_vec[0]+cols*rci]) * 100 <<",";
					}
				}
				if (ax_q1.axis_stmt_type_count[rci] == Table::tot_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
				}
				++cci;
			}
			++rci;
			tab_op << endl;
			tab_op << col_perc_str.str() << endl;
			tab_op << row_perc_str.str() << endl;
		}
		tab_op << endl;
		tab_op.close();
	} /*  close print */
} ;
struct table_q2_tot_ax {
	struct axis_q2 & ax_q2;
	struct axis_tot_ax & ax_tot_ax;
	int32_t (& q2_arr) [6];
	int32_t & all;
	const int rows, cols;
	vector <int> counter;
	table_q2_tot_ax (struct axis_q2 & p_ax_q2, struct axis_tot_ax & p_ax_tot_ax, int32_t (& p_q2_arr) [6], int32_t & p_all)
	: rows(6), cols(1),counter(6*1), ax_q2(p_ax_q2)
	, ax_tot_ax(p_ax_tot_ax) , q2_arr (p_q2_arr) , all (p_all)
	{
		for (int i=0;i<counter.size();++i) counter[i]=0; 
	}
	void compute(){
		if(ax_q2.flag[0] && ax_tot_ax.flag[0]){
			++counter[0*cols+0];
		}
		if(ax_q2.flag[1] && ax_tot_ax.flag[0]){
			++counter[1*cols+0];
		}
		if(ax_q2.flag[2] && ax_tot_ax.flag[0]){
			++counter[2*cols+0];
		}
		if(ax_q2.flag[3] && ax_tot_ax.flag[0]){
			++counter[3*cols+0];
		}
		if(ax_q2.flag[4] && ax_tot_ax.flag[0]){
			++counter[4*cols+0];
		}
		if(ax_q2.flag[5] && ax_tot_ax.flag[0]){
			++counter[5*cols+0];
		}
	} /*  close compute */
	void print(){
		int rci=0, cci=0; /* row counter index , col ... */
		ofstream tab_op("tab_.csv", ios_base::out|ios_base::app);
		tab_op << "rows" << "," << rows << ",cols" << "," << cols << endl;
		tab_op << "\"" << ax_q2.ttl_stmt_text[0] << "\"" << "," <<  "\"" << ax_tot_ax.ttl_stmt_text[0] << "\""  << endl;
		tab_op << ",,";
		for(int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j){
			 tab_op << "\"" << ax_tot_ax.count_stmt_text[j] << "\""  << "," ;
		}
		tab_op << endl;
		int inc_counter=0;
		for (int i=0; i<ax_q2.count_stmt_text.size(); ++i) {
			tab_op << ",";
			stringstream col_perc_str;
			stringstream row_perc_str;
			col_perc_str << ",,";
			row_perc_str << ",,";
			cci=0;
			tab_op << "\"" << ax_q2.count_stmt_text[i] << "\"" << ",";
				if (ax_q2.axis_stmt_type_count[rci] == Table::inc_axstmt) {
					++inc_counter;
				}
			for (int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j) {
				if (ax_q2.axis_stmt_type_count[rci] == Table::cnt_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
					if (ax_q2.tot_elem_pos_vec.size()>0) {
						col_perc_str << (((double) counter[cci+rci*cols]) / counter[cci+ax_q2.tot_elem_pos_vec[0]*cols]) * 100 <<",";
					}
					if (ax_tot_ax.tot_elem_pos_vec.size()>0) {
						row_perc_str << (((double) counter[cci+rci*cols]) / counter[ax_tot_ax.tot_elem_pos_vec[0]+cols*rci]) * 100 <<",";
					}
				}
				if (ax_q2.axis_stmt_type_count[rci] == Table::tot_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
				}
				++cci;
			}
			++rci;
			tab_op << endl;
			tab_op << col_perc_str.str() << endl;
			tab_op << row_perc_str.str() << endl;
		}
		tab_op << endl;
		tab_op.close();
	} /*  close print */
} ;
struct table_q4_tot_ax {
	struct axis_q4 & ax_q4;
	struct axis_tot_ax & ax_tot_ax;
	int32_t & q4_data;
	int32_t & all;
	const int rows, cols;
	vector <int> counter;
	table_q4_tot_ax (struct axis_q4 & p_ax_q4, struct axis_tot_ax & p_ax_tot_ax, int32_t & p_q4_data, int32_t & p_all)
	: rows(6), cols(1),counter(6*1), ax_q4(p_ax_q4)
	, ax_tot_ax(p_ax_tot_ax) , q4_data (p_q4_data) , all (p_all)
	{
		for (int i=0;i<counter.size();++i) counter[i]=0; 
	}
	void compute(){
		if(ax_q4.flag[0] && ax_tot_ax.flag[0]){
			++counter[0*cols+0];
		}
		if(ax_q4.flag[1] && ax_tot_ax.flag[0]){
			++counter[1*cols+0];
		}
		if(ax_q4.flag[2] && ax_tot_ax.flag[0]){
			++counter[2*cols+0];
		}
		if(ax_q4.flag[3] && ax_tot_ax.flag[0]){
			++counter[3*cols+0];
		}
		if(ax_q4.flag[4] && ax_tot_ax.flag[0]){
			++counter[4*cols+0];
		}
		if(ax_q4.flag[5] && ax_tot_ax.flag[0]){
			++counter[5*cols+0];
		}
	} /*  close compute */
	void print(){
		int rci=0, cci=0; /* row counter index , col ... */
		ofstream tab_op("tab_.csv", ios_base::out|ios_base::app);
		tab_op << "rows" << "," << rows << ",cols" << "," << cols << endl;
		tab_op << "\"" << ax_q4.ttl_stmt_text[0] << "\"" << "," <<  "\"" << ax_tot_ax.ttl_stmt_text[0] << "\""  << endl;
		tab_op << ",,";
		for(int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j){
			 tab_op << "\"" << ax_tot_ax.count_stmt_text[j] << "\""  << "," ;
		}
		tab_op << endl;
		int inc_counter=0;
		for (int i=0; i<ax_q4.count_stmt_text.size(); ++i) {
			tab_op << ",";
			stringstream col_perc_str;
			stringstream row_perc_str;
			col_perc_str << ",,";
			row_perc_str << ",,";
			cci=0;
			tab_op << "\"" << ax_q4.count_stmt_text[i] << "\"" << ",";
				if (ax_q4.axis_stmt_type_count[rci] == Table::inc_axstmt) {
					++inc_counter;
				}
			for (int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j) {
				if (ax_q4.axis_stmt_type_count[rci] == Table::cnt_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
					if (ax_q4.tot_elem_pos_vec.size()>0) {
						col_perc_str << (((double) counter[cci+rci*cols]) / counter[cci+ax_q4.tot_elem_pos_vec[0]*cols]) * 100 <<",";
					}
					if (ax_tot_ax.tot_elem_pos_vec.size()>0) {
						row_perc_str << (((double) counter[cci+rci*cols]) / counter[ax_tot_ax.tot_elem_pos_vec[0]+cols*rci]) * 100 <<",";
					}
				}
				if (ax_q4.axis_stmt_type_count[rci] == Table::tot_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
				}
				++cci;
			}
			++rci;
			tab_op << endl;
			tab_op << col_perc_str.str() << endl;
			tab_op << row_perc_str.str() << endl;
		}
		tab_op << endl;
		tab_op.close();
	} /*  close print */
} ;
struct table_q6_0_tot_ax {
	struct axis_q6_0 & ax_q6_0;
	struct axis_tot_ax & ax_tot_ax;
	int32_t & q6_0_data;
	int32_t & all;
	const int rows, cols;
	vector <int> counter;
	table_q6_0_tot_ax (struct axis_q6_0 & p_ax_q6_0, struct axis_tot_ax & p_ax_tot_ax, int32_t & p_q6_0_data, int32_t & p_all)
	: rows(2), cols(1),counter(2*1), ax_q6_0(p_ax_q6_0)
	, ax_tot_ax(p_ax_tot_ax) , q6_0_data (p_q6_0_data) , all (p_all)
	{
		for (int i=0;i<counter.size();++i) counter[i]=0; 
	}
	void compute(){
		if(ax_q6_0.flag[0] && ax_tot_ax.flag[0]){
			++counter[0*cols+0];
		}
		if(ax_q6_0.flag[1] && ax_tot_ax.flag[0]){
			++counter[1*cols+0];
		}
	} /*  close compute */
	void print(){
		int rci=0, cci=0; /* row counter index , col ... */
		ofstream tab_op("tab_.csv", ios_base::out|ios_base::app);
		tab_op << "rows" << "," << rows << ",cols" << "," << cols << endl;
		tab_op << "\"" << ax_q6_0.ttl_stmt_text[0] << "\"" << "," <<  "\"" << ax_tot_ax.ttl_stmt_text[0] << "\""  << endl;
		tab_op << ",,";
		for(int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j){
			 tab_op << "\"" << ax_tot_ax.count_stmt_text[j] << "\""  << "," ;
		}
		tab_op << endl;
		int inc_counter=0;
		for (int i=0; i<ax_q6_0.count_stmt_text.size(); ++i) {
			tab_op << ",";
			stringstream col_perc_str;
			stringstream row_perc_str;
			col_perc_str << ",,";
			row_perc_str << ",,";
			cci=0;
			tab_op << "\"" << ax_q6_0.count_stmt_text[i] << "\"" << ",";
				if (ax_q6_0.axis_stmt_type_count[rci] == Table::inc_axstmt) {
					++inc_counter;
				}
			for (int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j) {
				if (ax_q6_0.axis_stmt_type_count[rci] == Table::cnt_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
					if (ax_q6_0.tot_elem_pos_vec.size()>0) {
						col_perc_str << (((double) counter[cci+rci*cols]) / counter[cci+ax_q6_0.tot_elem_pos_vec[0]*cols]) * 100 <<",";
					}
					if (ax_tot_ax.tot_elem_pos_vec.size()>0) {
						row_perc_str << (((double) counter[cci+rci*cols]) / counter[ax_tot_ax.tot_elem_pos_vec[0]+cols*rci]) * 100 <<",";
					}
				}
				if (ax_q6_0.axis_stmt_type_count[rci] == Table::tot_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
				}
				++cci;
			}
			++rci;
			tab_op << endl;
			tab_op << col_perc_str.str() << endl;
			tab_op << row_perc_str.str() << endl;
		}
		tab_op << endl;
		tab_op.close();
	} /*  close print */
} ;
struct table_q6_1_tot_ax {
	struct axis_q6_1 & ax_q6_1;
	struct axis_tot_ax & ax_tot_ax;
	int32_t & q6_1_data;
	int32_t & all;
	const int rows, cols;
	vector <int> counter;
	table_q6_1_tot_ax (struct axis_q6_1 & p_ax_q6_1, struct axis_tot_ax & p_ax_tot_ax, int32_t & p_q6_1_data, int32_t & p_all)
	: rows(2), cols(1),counter(2*1), ax_q6_1(p_ax_q6_1)
	, ax_tot_ax(p_ax_tot_ax) , q6_1_data (p_q6_1_data) , all (p_all)
	{
		for (int i=0;i<counter.size();++i) counter[i]=0; 
	}
	void compute(){
		if(ax_q6_1.flag[0] && ax_tot_ax.flag[0]){
			++counter[0*cols+0];
		}
		if(ax_q6_1.flag[1] && ax_tot_ax.flag[0]){
			++counter[1*cols+0];
		}
	} /*  close compute */
	void print(){
		int rci=0, cci=0; /* row counter index , col ... */
		ofstream tab_op("tab_.csv", ios_base::out|ios_base::app);
		tab_op << "rows" << "," << rows << ",cols" << "," << cols << endl;
		tab_op << "\"" << ax_q6_1.ttl_stmt_text[0] << "\"" << "," <<  "\"" << ax_tot_ax.ttl_stmt_text[0] << "\""  << endl;
		tab_op << ",,";
		for(int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j){
			 tab_op << "\"" << ax_tot_ax.count_stmt_text[j] << "\""  << "," ;
		}
		tab_op << endl;
		int inc_counter=0;
		for (int i=0; i<ax_q6_1.count_stmt_text.size(); ++i) {
			tab_op << ",";
			stringstream col_perc_str;
			stringstream row_perc_str;
			col_perc_str << ",,";
			row_perc_str << ",,";
			cci=0;
			tab_op << "\"" << ax_q6_1.count_stmt_text[i] << "\"" << ",";
				if (ax_q6_1.axis_stmt_type_count[rci] == Table::inc_axstmt) {
					++inc_counter;
				}
			for (int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j) {
				if (ax_q6_1.axis_stmt_type_count[rci] == Table::cnt_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
					if (ax_q6_1.tot_elem_pos_vec.size()>0) {
						col_perc_str << (((double) counter[cci+rci*cols]) / counter[cci+ax_q6_1.tot_elem_pos_vec[0]*cols]) * 100 <<",";
					}
					if (ax_tot_ax.tot_elem_pos_vec.size()>0) {
						row_perc_str << (((double) counter[cci+rci*cols]) / counter[ax_tot_ax.tot_elem_pos_vec[0]+cols*rci]) * 100 <<",";
					}
				}
				if (ax_q6_1.axis_stmt_type_count[rci] == Table::tot_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
				}
				++cci;
			}
			++rci;
			tab_op << endl;
			tab_op << col_perc_str.str() << endl;
			tab_op << row_perc_str.str() << endl;
		}
		tab_op << endl;
		tab_op.close();
	} /*  close print */
} ;
struct table_q6_2_tot_ax {
	struct axis_q6_2 & ax_q6_2;
	struct axis_tot_ax & ax_tot_ax;
	int32_t & q6_2_data;
	int32_t & all;
	const int rows, cols;
	vector <int> counter;
	table_q6_2_tot_ax (struct axis_q6_2 & p_ax_q6_2, struct axis_tot_ax & p_ax_tot_ax, int32_t & p_q6_2_data, int32_t & p_all)
	: rows(2), cols(1),counter(2*1), ax_q6_2(p_ax_q6_2)
	, ax_tot_ax(p_ax_tot_ax) , q6_2_data (p_q6_2_data) , all (p_all)
	{
		for (int i=0;i<counter.size();++i) counter[i]=0; 
	}
	void compute(){
		if(ax_q6_2.flag[0] && ax_tot_ax.flag[0]){
			++counter[0*cols+0];
		}
		if(ax_q6_2.flag[1] && ax_tot_ax.flag[0]){
			++counter[1*cols+0];
		}
	} /*  close compute */
	void print(){
		int rci=0, cci=0; /* row counter index , col ... */
		ofstream tab_op("tab_.csv", ios_base::out|ios_base::app);
		tab_op << "rows" << "," << rows << ",cols" << "," << cols << endl;
		tab_op << "\"" << ax_q6_2.ttl_stmt_text[0] << "\"" << "," <<  "\"" << ax_tot_ax.ttl_stmt_text[0] << "\""  << endl;
		tab_op << ",,";
		for(int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j){
			 tab_op << "\"" << ax_tot_ax.count_stmt_text[j] << "\""  << "," ;
		}
		tab_op << endl;
		int inc_counter=0;
		for (int i=0; i<ax_q6_2.count_stmt_text.size(); ++i) {
			tab_op << ",";
			stringstream col_perc_str;
			stringstream row_perc_str;
			col_perc_str << ",,";
			row_perc_str << ",,";
			cci=0;
			tab_op << "\"" << ax_q6_2.count_stmt_text[i] << "\"" << ",";
				if (ax_q6_2.axis_stmt_type_count[rci] == Table::inc_axstmt) {
					++inc_counter;
				}
			for (int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j) {
				if (ax_q6_2.axis_stmt_type_count[rci] == Table::cnt_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
					if (ax_q6_2.tot_elem_pos_vec.size()>0) {
						col_perc_str << (((double) counter[cci+rci*cols]) / counter[cci+ax_q6_2.tot_elem_pos_vec[0]*cols]) * 100 <<",";
					}
					if (ax_tot_ax.tot_elem_pos_vec.size()>0) {
						row_perc_str << (((double) counter[cci+rci*cols]) / counter[ax_tot_ax.tot_elem_pos_vec[0]+cols*rci]) * 100 <<",";
					}
				}
				if (ax_q6_2.axis_stmt_type_count[rci] == Table::tot_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
				}
				++cci;
			}
			++rci;
			tab_op << endl;
			tab_op << col_perc_str.str() << endl;
			tab_op << row_perc_str.str() << endl;
		}
		tab_op << endl;
		tab_op.close();
	} /*  close print */
} ;
struct table_q6_3_tot_ax {
	struct axis_q6_3 & ax_q6_3;
	struct axis_tot_ax & ax_tot_ax;
	int32_t & q6_3_data;
	int32_t & all;
	const int rows, cols;
	vector <int> counter;
	table_q6_3_tot_ax (struct axis_q6_3 & p_ax_q6_3, struct axis_tot_ax & p_ax_tot_ax, int32_t & p_q6_3_data, int32_t & p_all)
	: rows(2), cols(1),counter(2*1), ax_q6_3(p_ax_q6_3)
	, ax_tot_ax(p_ax_tot_ax) , q6_3_data (p_q6_3_data) , all (p_all)
	{
		for (int i=0;i<counter.size();++i) counter[i]=0; 
	}
	void compute(){
		if(ax_q6_3.flag[0] && ax_tot_ax.flag[0]){
			++counter[0*cols+0];
		}
		if(ax_q6_3.flag[1] && ax_tot_ax.flag[0]){
			++counter[1*cols+0];
		}
	} /*  close compute */
	void print(){
		int rci=0, cci=0; /* row counter index , col ... */
		ofstream tab_op("tab_.csv", ios_base::out|ios_base::app);
		tab_op << "rows" << "," << rows << ",cols" << "," << cols << endl;
		tab_op << "\"" << ax_q6_3.ttl_stmt_text[0] << "\"" << "," <<  "\"" << ax_tot_ax.ttl_stmt_text[0] << "\""  << endl;
		tab_op << ",,";
		for(int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j){
			 tab_op << "\"" << ax_tot_ax.count_stmt_text[j] << "\""  << "," ;
		}
		tab_op << endl;
		int inc_counter=0;
		for (int i=0; i<ax_q6_3.count_stmt_text.size(); ++i) {
			tab_op << ",";
			stringstream col_perc_str;
			stringstream row_perc_str;
			col_perc_str << ",,";
			row_perc_str << ",,";
			cci=0;
			tab_op << "\"" << ax_q6_3.count_stmt_text[i] << "\"" << ",";
				if (ax_q6_3.axis_stmt_type_count[rci] == Table::inc_axstmt) {
					++inc_counter;
				}
			for (int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j) {
				if (ax_q6_3.axis_stmt_type_count[rci] == Table::cnt_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
					if (ax_q6_3.tot_elem_pos_vec.size()>0) {
						col_perc_str << (((double) counter[cci+rci*cols]) / counter[cci+ax_q6_3.tot_elem_pos_vec[0]*cols]) * 100 <<",";
					}
					if (ax_tot_ax.tot_elem_pos_vec.size()>0) {
						row_perc_str << (((double) counter[cci+rci*cols]) / counter[ax_tot_ax.tot_elem_pos_vec[0]+cols*rci]) * 100 <<",";
					}
				}
				if (ax_q6_3.axis_stmt_type_count[rci] == Table::tot_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
				}
				++cci;
			}
			++rci;
			tab_op << endl;
			tab_op << col_perc_str.str() << endl;
			tab_op << row_perc_str.str() << endl;
		}
		tab_op << endl;
		tab_op.close();
	} /*  close print */
} ;
struct table_q6_4_tot_ax {
	struct axis_q6_4 & ax_q6_4;
	struct axis_tot_ax & ax_tot_ax;
	int32_t & q6_4_data;
	int32_t & all;
	const int rows, cols;
	vector <int> counter;
	table_q6_4_tot_ax (struct axis_q6_4 & p_ax_q6_4, struct axis_tot_ax & p_ax_tot_ax, int32_t & p_q6_4_data, int32_t & p_all)
	: rows(2), cols(1),counter(2*1), ax_q6_4(p_ax_q6_4)
	, ax_tot_ax(p_ax_tot_ax) , q6_4_data (p_q6_4_data) , all (p_all)
	{
		for (int i=0;i<counter.size();++i) counter[i]=0; 
	}
	void compute(){
		if(ax_q6_4.flag[0] && ax_tot_ax.flag[0]){
			++counter[0*cols+0];
		}
		if(ax_q6_4.flag[1] && ax_tot_ax.flag[0]){
			++counter[1*cols+0];
		}
	} /*  close compute */
	void print(){
		int rci=0, cci=0; /* row counter index , col ... */
		ofstream tab_op("tab_.csv", ios_base::out|ios_base::app);
		tab_op << "rows" << "," << rows << ",cols" << "," << cols << endl;
		tab_op << "\"" << ax_q6_4.ttl_stmt_text[0] << "\"" << "," <<  "\"" << ax_tot_ax.ttl_stmt_text[0] << "\""  << endl;
		tab_op << ",,";
		for(int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j){
			 tab_op << "\"" << ax_tot_ax.count_stmt_text[j] << "\""  << "," ;
		}
		tab_op << endl;
		int inc_counter=0;
		for (int i=0; i<ax_q6_4.count_stmt_text.size(); ++i) {
			tab_op << ",";
			stringstream col_perc_str;
			stringstream row_perc_str;
			col_perc_str << ",,";
			row_perc_str << ",,";
			cci=0;
			tab_op << "\"" << ax_q6_4.count_stmt_text[i] << "\"" << ",";
				if (ax_q6_4.axis_stmt_type_count[rci] == Table::inc_axstmt) {
					++inc_counter;
				}
			for (int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j) {
				if (ax_q6_4.axis_stmt_type_count[rci] == Table::cnt_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
					if (ax_q6_4.tot_elem_pos_vec.size()>0) {
						col_perc_str << (((double) counter[cci+rci*cols]) / counter[cci+ax_q6_4.tot_elem_pos_vec[0]*cols]) * 100 <<",";
					}
					if (ax_tot_ax.tot_elem_pos_vec.size()>0) {
						row_perc_str << (((double) counter[cci+rci*cols]) / counter[ax_tot_ax.tot_elem_pos_vec[0]+cols*rci]) * 100 <<",";
					}
				}
				if (ax_q6_4.axis_stmt_type_count[rci] == Table::tot_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
				}
				++cci;
			}
			++rci;
			tab_op << endl;
			tab_op << col_perc_str.str() << endl;
			tab_op << row_perc_str.str() << endl;
		}
		tab_op << endl;
		tab_op.close();
	} /*  close print */
} ;
struct table_q5_0_tot_ax {
	struct axis_q5_0 & ax_q5_0;
	struct axis_tot_ax & ax_tot_ax;
	int32_t & q5_0_data;
	int32_t & all;
	const int rows, cols;
	vector <int> counter;
	vector<MeanStdDevInc> mean_inc_q5_0_tot_ax;
	table_q5_0_tot_ax (struct axis_q5_0 & p_ax_q5_0, struct axis_tot_ax & p_ax_tot_ax, int32_t & p_q5_0_data, int32_t & p_all)
	: rows(9), cols(1),counter(9*1), ax_q5_0(p_ax_q5_0)
	, ax_tot_ax(p_ax_tot_ax) , q5_0_data (p_q5_0_data) , all (p_all), mean_inc_q5_0_tot_ax (1)
	{
		for (int i=0;i<counter.size();++i) counter[i]=0; 
		for (int i=0; i<mean_inc_q5_0_tot_ax.size(); ++i) {
			mean_inc_q5_0_tot_ax[i].sum_n=0.0; mean_inc_q5_0_tot_ax[i].n=0.0;
		}
	}
	void compute(){
		if(ax_q5_0.flag[0] && ax_tot_ax.flag[0]){
			++counter[0*cols+0];
		}
		if(ax_q5_0.flag[1] && ax_tot_ax.flag[0]){
			++counter[1*cols+0];
		}
		if(ax_q5_0.flag[2] && ax_tot_ax.flag[0]){
			++counter[2*cols+0];
		}
		if(ax_q5_0.flag[3] && ax_tot_ax.flag[0]){
			++counter[3*cols+0];
		}
		if(ax_q5_0.flag[4] && ax_tot_ax.flag[0]){
			++counter[4*cols+0];
		}
		if(ax_q5_0.flag[5] && ax_tot_ax.flag[0]){
			++counter[5*cols+0];
		}
		if(ax_q5_0.flag[6] && ax_tot_ax.flag[0]){
			++counter[6*cols+0];
		}
		if(ax_q5_0.flag[7] && ax_tot_ax.flag[0]){
			++counter[7*cols+0];
		}
		if(ax_q5_0.flag[8] && ax_tot_ax.flag[0]){
			 mean_inc_q5_0_tot_ax[0*cols+0].sum_n += q5_0_data ;
			 mean_inc_q5_0_tot_ax[0*cols+0].n +=1;
		}
	} /*  close compute */
	void print(){
		int rci=0, cci=0; /* row counter index , col ... */
		ofstream tab_op("tab_.csv", ios_base::out|ios_base::app);
		tab_op << "rows" << "," << rows << ",cols" << "," << cols << endl;
		tab_op << "\"" << ax_q5_0.ttl_stmt_text[0] << "\"" << "," <<  "\"" << ax_tot_ax.ttl_stmt_text[0] << "\""  << endl;
		tab_op << ",,";
		for(int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j){
			 tab_op << "\"" << ax_tot_ax.count_stmt_text[j] << "\""  << "," ;
		}
		tab_op << endl;
		int inc_counter=0;
		for (int i=0; i<ax_q5_0.count_stmt_text.size(); ++i) {
			tab_op << ",";
			stringstream col_perc_str;
			stringstream row_perc_str;
			col_perc_str << ",,";
			row_perc_str << ",,";
			cci=0;
			tab_op << "\"" << ax_q5_0.count_stmt_text[i] << "\"" << ",";
				if (ax_q5_0.axis_stmt_type_count[rci] == Table::inc_axstmt) {
					++inc_counter;
				}
			for (int j=0; j<ax_tot_ax.count_stmt_text.size(); ++j) {
				if (ax_q5_0.axis_stmt_type_count[rci] == Table::cnt_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
					if (ax_q5_0.tot_elem_pos_vec.size()>0) {
						col_perc_str << (((double) counter[cci+rci*cols]) / counter[cci+ax_q5_0.tot_elem_pos_vec[0]*cols]) * 100 <<",";
					}
					if (ax_tot_ax.tot_elem_pos_vec.size()>0) {
						row_perc_str << (((double) counter[cci+rci*cols]) / counter[ax_tot_ax.tot_elem_pos_vec[0]+cols*rci]) * 100 <<",";
					}
				}
				if (ax_q5_0.axis_stmt_type_count[rci] == Table::tot_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
				}
				if (ax_q5_0.axis_stmt_type_count[rci] == Table::inc_axstmt) {
					tab_op << mean_inc_q5_0_tot_ax[(inc_counter-1)*cols+cci].sum_n / mean_inc_q5_0_tot_ax[(inc_counter-1)*cols+cci].n  << ",";
				}
				++cci;
			}
			++rci;
			tab_op << endl;
			tab_op << col_perc_str.str() << endl;
			tab_op << row_perc_str.str() << endl;
		}
		tab_op << endl;
		tab_op.close();
	} /*  close print */
} ;


struct TableGroup {

	EditDataStruct ed;
	AxesGroup ag;
	TableGroup(AxesGroup & p_ag, EditDataStruct & p_ed);


struct table_q1_tot_ax tab_q1_tot_ax;
struct table_q2_tot_ax tab_q2_tot_ax;
struct table_q2_tot_ax tab_q3_tot_ax;
struct table_q4_tot_ax tab_q4_tot_ax;
struct table_q6_0_tot_ax tab_q6_0_tot_ax;
struct table_q6_1_tot_ax tab_q6_1_tot_ax;
struct table_q6_2_tot_ax tab_q6_2_tot_ax;
struct table_q6_3_tot_ax tab_q6_3_tot_ax;
struct table_q6_4_tot_ax tab_q6_4_tot_ax;
struct table_q5_0_tot_ax tab_q5_0_tot_ax;
struct table_q5_0_tot_ax tab_q5_1_tot_ax;
struct table_q5_0_tot_ax tab_q5_2_tot_ax;
struct table_q5_0_tot_ax tab_q5_3_tot_ax;

	/* ====================================== */
//struct table_q1_tot_ax tab_q1_tot_ax(ag.ax_q1, ax_tot_ax, ed.q1_data, all);
//struct table_q2_tot_ax tab_q2_tot_ax(ax_q2, ax_tot_ax, q2_arr, all);
//	/* stub_hint: q2 */
//struct table_q2_tot_ax tab_q3_tot_ax(ax_q3, ax_tot_ax, q3_arr, all);
//struct table_q4_tot_ax tab_q4_tot_ax(ax_q4, ax_tot_ax, q4_data, all);
//struct table_q6_0_tot_ax tab_q6_0_tot_ax(ax_q6_0, ax_tot_ax, q6_0_data, all);
//struct table_q6_1_tot_ax tab_q6_1_tot_ax(ax_q6_1, ax_tot_ax, q6_1_data, all);
//struct table_q6_2_tot_ax tab_q6_2_tot_ax(ax_q6_2, ax_tot_ax, q6_2_data, all);
//struct table_q6_3_tot_ax tab_q6_3_tot_ax(ax_q6_3, ax_tot_ax, q6_3_data, all);
//struct table_q6_4_tot_ax tab_q6_4_tot_ax(ax_q6_4, ax_tot_ax, q6_4_data, all);
//	/* stub_hint: q5_0 */
//struct table_q5_0_tot_ax tab_q5_0_tot_ax(ax_q5_0, ax_tot_ax, q5_0_data, all);
//	/* stub_hint: q5_0 */
//struct table_q5_0_tot_ax tab_q5_1_tot_ax(ax_q5_1, ax_tot_ax, q5_1_data, all);
//	/* stub_hint: q5_0 */
//struct table_q5_0_tot_ax tab_q5_2_tot_ax(ax_q5_2, ax_tot_ax, q5_2_data, all);
//	/* stub_hint: q5_0 */
//struct table_q5_0_tot_ax tab_q5_3_tot_ax(ax_q5_3, ax_tot_ax, q5_3_data, all);

};

#endif /*  MY_TABLE_H */
