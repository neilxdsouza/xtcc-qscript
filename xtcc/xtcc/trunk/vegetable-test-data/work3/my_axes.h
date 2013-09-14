#ifndef MY_AXES_H
#define MY_AXES_H
#include <bitset>
#include <string>
#include <vector>
#include <sys/types.h>
#include "ax_stmt_type.h"
#include "edit_out.h"
using namespace std;
struct axis_q1 {
	EditDataStruct & ed;
	//bitset<3> flag;
	char flag[3];
	vector<string> ttl_stmt_text;
	vector<string> count_stmt_text;
	vector<int> tot_elem_pos_vec;
	bitset<4> is_a_count_text;
	vector<Table::axstmt_type> axis_stmt_type_print;
	vector<Table::axstmt_type> axis_stmt_type_count;
	void reset();
	void compute();
	int32_t & q1_data;
	axis_q1(/* int32_t & p_q1_data, */ const char * p_text_ttls[], EditDataStruct & ed)
;
};

struct axis_q2 {
	EditDataStruct & ed;
	//bitset<6> flag;
	char flag[6];
	vector<string> ttl_stmt_text;
	vector<string> count_stmt_text;
	vector<int> tot_elem_pos_vec;
	bitset<7> is_a_count_text;
	vector<Table::axstmt_type> axis_stmt_type_print;
	vector<Table::axstmt_type> axis_stmt_type_count;
	void reset();
	void compute();
int32_t (& q2_arr) [6];
	axis_q2(/* int32_t (& p_q2_arr) [6], */ const char * p_text_ttls[], EditDataStruct & ed)
;
};

struct axis_q4 {
	bitset<6> flag;
	vector<string> ttl_stmt_text;
	vector<string> count_stmt_text;
	vector<int> tot_elem_pos_vec;
	bitset<8> is_a_count_text;
	vector<Table::axstmt_type> axis_stmt_type_print;
	vector<Table::axstmt_type> axis_stmt_type_count;
	void reset();
	void compute();
int32_t & q4_data;
	axis_q4(int32_t & p_q4_data, const char * p_text_ttls[])
;
};

struct axis_q5_0 {
	bitset<9> flag;
	vector<string> ttl_stmt_text;
	vector<string> count_stmt_text;
	vector<int> tot_elem_pos_vec;
	bitset<11> is_a_count_text;
	vector<Table::axstmt_type> axis_stmt_type_print;
	vector<Table::axstmt_type> axis_stmt_type_count;
	void reset();
	void compute();
int32_t & q5_0_data;
	axis_q5_0(int32_t & p_q5_0_data, const char * p_text_ttls[])
;
};

struct axis_q6_0 {
	bitset<2> flag;
	vector<string> ttl_stmt_text;
	vector<string> count_stmt_text;
	vector<int> tot_elem_pos_vec;
	bitset<4> is_a_count_text;
	vector<Table::axstmt_type> axis_stmt_type_print;
	vector<Table::axstmt_type> axis_stmt_type_count;
	void reset();
	void compute();
int32_t & q6_0_data;
	axis_q6_0(int32_t & p_q6_0_data, const char * p_text_ttls[])
;
};

struct axis_q6_1 {
	bitset<2> flag;
	vector<string> ttl_stmt_text;
	vector<string> count_stmt_text;
	vector<int> tot_elem_pos_vec;
	bitset<4> is_a_count_text;
	vector<Table::axstmt_type> axis_stmt_type_print;
	vector<Table::axstmt_type> axis_stmt_type_count;
	void reset();
	void compute();
int32_t & q6_1_data;
	axis_q6_1(int32_t & p_q6_1_data, const char * p_text_ttls[])
;
};

struct axis_q6_2 {
	bitset<2> flag;
	vector<string> ttl_stmt_text;
	vector<string> count_stmt_text;
	vector<int> tot_elem_pos_vec;
	bitset<4> is_a_count_text;
	vector<Table::axstmt_type> axis_stmt_type_print;
	vector<Table::axstmt_type> axis_stmt_type_count;
	void reset();
	void compute();
int32_t & q6_2_data;
	axis_q6_2(int32_t & p_q6_2_data, const char * p_text_ttls[])
;
};

struct axis_q6_3 {
	bitset<2> flag;
	vector<string> ttl_stmt_text;
	vector<string> count_stmt_text;
	vector<int> tot_elem_pos_vec;
	bitset<4> is_a_count_text;
	vector<Table::axstmt_type> axis_stmt_type_print;
	vector<Table::axstmt_type> axis_stmt_type_count;
	void reset();
	void compute();
int32_t & q6_3_data;
	axis_q6_3(int32_t & p_q6_3_data, const char * p_text_ttls[])
;
};

struct axis_q6_4 {
	bitset<2> flag;
	vector<string> ttl_stmt_text;
	vector<string> count_stmt_text;
	vector<int> tot_elem_pos_vec;
	bitset<4> is_a_count_text;
	vector<Table::axstmt_type> axis_stmt_type_print;
	vector<Table::axstmt_type> axis_stmt_type_count;
	void reset();
	void compute();
int32_t & q6_4_data;
	axis_q6_4(int32_t & p_q6_4_data, const char * p_text_ttls[])
;
};

struct axis_tot_ax {
	bitset<1> flag;
	vector<string> ttl_stmt_text;
	vector<string> count_stmt_text;
	vector<int> tot_elem_pos_vec;
	bitset<2> is_a_count_text;
	vector<Table::axstmt_type> axis_stmt_type_print;
	vector<Table::axstmt_type> axis_stmt_type_count;
	void reset();
	void compute();
int32_t & all;
	axis_tot_ax(int32_t & p_all, const char * p_text_ttls[])
;
};

/* ======================================  */
struct AxesGroup {
/* =============== DECL ==================  */
EditDataStruct & ed;
struct axis_q1 ax_q1;
struct axis_q2 ax_q2;
//struct axis_q2 ax_q3;
//struct axis_q4 ax_q4;
//struct axis_q5_0 ax_q5_0;
//struct axis_q5_0 ax_q5_1;
//struct axis_q5_0 ax_q5_2;
//struct axis_q5_0 ax_q5_3;
//struct axis_q6_0 ax_q6_0;
//struct axis_q6_1 ax_q6_1;
//struct axis_q6_2 ax_q6_2;
//struct axis_q6_3 ax_q6_3;
//struct axis_q6_4 ax_q6_4;
//struct axis_tot_ax ax_tot_ax;
/* =============== CONS INIT ==================  */
AxesGroup(EditDataStruct & p_ed);


};

#endif /* MY_AXES_H */
