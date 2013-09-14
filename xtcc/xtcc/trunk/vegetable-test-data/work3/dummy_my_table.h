#ifndef MY_TABLE_H
#define MY_TABLE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
using namespace std;
#include "global.h"
#include "my_axes.h"
//extern struct axis_q1 ax_q1;
/* stub_hint_axis is empty  */
//extern struct axis_q2 ax_q2;
struct table_q2_q1 {
	struct axis_q2 & ax_q2;
	struct axis_q1 & ax_q1;
	int32_t (& q2_arr) [6];
	int32_t & q1_data;
	const int rows, cols;
	vector <int> counter;
	table_q2_q1 (struct axis_q2 & p_ax_q2, struct axis_q1 & p_ax_q1, int32_t (& p_q2_arr) [6], int32_t & p_q1_data)
	: rows(6), cols(3),counter(6*3), ax_q2(p_ax_q2)
	, ax_q1(p_ax_q1) , q2_arr (p_q2_arr) , q1_data (p_q1_data)
	{
		printf ("Enter: %s\n", __PRETTY_FUNCTION__);
		for (int i=0;i<counter.size();++i) counter[i]=0;
		printf ("ax_q1.flag address: %x\n", ax_q1.flag);
		printf ("ax_q2.flag address: %x\n", ax_q2.flag);
		printf ("Exit: %s\n", __PRETTY_FUNCTION__);
	}
	void compute(){
		printf ("Entered : %s\n" , __PRETTY_FUNCTION__);

		printf ("ax_q1.q1_data: %d\n",   ax_q1.q1_data);
		printf ("ax_q2.q2_arr[0]: %d\n", ax_q2.q2_arr[0]);
		printf ("ax_q2.q2_arr[1]: %d\n", ax_q2.q2_arr[1]);
		printf ("ax_q2.q2_arr[2]: %d\n", ax_q2.q2_arr[2]);
		printf ("ax_q2.q2_arr[3]: %d\n", ax_q2.q2_arr[3]);
		printf ("ax_q2.q2_arr[4]: %d\n", ax_q2.q2_arr[4]);
		printf ("ax_q2.q2_arr[5]: %d\n", ax_q2.q2_arr[5]);

		printf ("=====\n");
		for (int i=0; i < 3; ++i) {
			int v = ax_q1.flag[i];
			printf ("ax_q1: flag[%d]:%d\n", i, v);
		}
		printf ("=====\n");

		for (int i=0; i < 6; ++i) {
			int v = ax_q2.flag[i];
			printf ("ax_q2: flag[%d]:%d\n", i, v);
		}
		printf ("=====\n");

		if(ax_q2.flag[0] && ax_q1.flag[0]){
			++counter[0*cols+0];
			printf ("counter incremented[0,0]: \n");
		}
		if(ax_q2.flag[0] && ax_q1.flag[1]){
			++counter[0*cols+1];
			printf ("counter incremented[0,1]: \n");
		}
		if(ax_q2.flag[0] && ax_q1.flag[2]){
			++counter[0*cols+2];
			printf ("counter incremented[0,2]: \n");
		}
		if(ax_q2.flag[1] && ax_q1.flag[0]){
			++counter[1*cols+0];
			printf ("counter incremented[1,0]: \n");
		}
		if(ax_q2.flag[1] && ax_q1.flag[1]){
			++counter[1*cols+1];
			printf ("counter incremented[1,1]: \n");
		}
		if(ax_q2.flag[1] && ax_q1.flag[2]){
			++counter[1*cols+2];
			printf ("counter incremented[1,2]: \n");
		}
		if(ax_q2.flag[2] && ax_q1.flag[0]){
			++counter[2*cols+0];
		}
		if(ax_q2.flag[2] && ax_q1.flag[1]){
			++counter[2*cols+1];
		}
		if(ax_q2.flag[2] && ax_q1.flag[2]){
			++counter[2*cols+2];
		}
		if(ax_q2.flag[3] && ax_q1.flag[0]){
			++counter[3*cols+0];
		}
		if(ax_q2.flag[3] && ax_q1.flag[1]){
			++counter[3*cols+1];
		}
		if(ax_q2.flag[3] && ax_q1.flag[2]){
			++counter[3*cols+2];
		}
		if(ax_q2.flag[4] && ax_q1.flag[0]){
			++counter[4*cols+0];
		}
		if(ax_q2.flag[4] && ax_q1.flag[1]){
			++counter[4*cols+1];
		}
		if(ax_q2.flag[4] && ax_q1.flag[2]){
			++counter[4*cols+2];
		}
		if(ax_q2.flag[5] && ax_q1.flag[0]){
			++counter[5*cols+0];
		}
		if(ax_q2.flag[5] && ax_q1.flag[1]){
			++counter[5*cols+1];
		}
		if(ax_q2.flag[5] && ax_q1.flag[2]){
			++counter[5*cols+2];
		}
	} /*  close compute */
	void print(){
		int rci=0, cci=0; /* row counter index , col ... */
		ofstream tab_op("tab_.csv", ios_base::out|ios_base::app);
		tab_op << "rows" << "," << rows << ",cols" << "," << cols << endl;
		tab_op << "\"" << ax_q2.ttl_stmt_text[0] << "\"" << "," <<  "\"" << ax_q1.ttl_stmt_text[0] << "\""  << endl;
		tab_op << ",,";
		for(int j=0; j<ax_q1.count_stmt_text.size(); ++j){
			 tab_op << "\"" << ax_q1.count_stmt_text[j] << "\""  << "," ;
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
			for (int j=0; j<ax_q1.count_stmt_text.size(); ++j) {
				if (ax_q2.axis_stmt_type_count[rci] == Table::cnt_axstmt) {
					tab_op << counter[cci+rci*cols]<<",";
					if (ax_q2.tot_elem_pos_vec.size()>0) {
						col_perc_str << (((double) counter[cci+rci*cols]) / counter[cci+ax_q2.tot_elem_pos_vec[0]*cols]) * 100 <<",";
					}
					if (ax_q1.tot_elem_pos_vec.size()>0) {
						row_perc_str << (((double) counter[cci+rci*cols]) / counter[ax_q1.tot_elem_pos_vec[0]+cols*rci]) * 100 <<",";
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

struct TableGroup {
	EditDataStruct & ed;
	AxesGroup & ag;
	struct table_q2_q1 tab_q2_q1; 
	TableGroup(AxesGroup & p_ag, EditDataStruct & p_ed);
};

#endif /*  MY_TABLE_H */
