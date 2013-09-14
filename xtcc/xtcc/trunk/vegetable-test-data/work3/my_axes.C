#include <cstdio>
#include "global.h"
#include "my_axes.h"

void axis_q1::reset()
{
	//flag.reset();
	for (int i=0; i<3; ++i) { flag[i] = 0; }
}

void axis_q1::compute()
{
	printf ("Enter: %s\n", __PRETTY_FUNCTION__);
	//flag.reset();
	for (int i=0; i<3; ++i) { flag[i] = 0; }
	flag[0]=true;
	if ( ed.q1_data==1 ){
		flag[1]=true;
	}
	if ( ed.q1_data==2 ){
		flag[2]=true;
	}
	for (int i=0; i < 3; ++i) {
		int v = flag[i];
		printf ("flag[%d]:%d\n", i, v);
	}
	printf ("flag address: %x\n", flag);
	printf ("Exit: %s\n", __PRETTY_FUNCTION__);
} /* close compute func */

const char * q1_ttl_stmt_arr[] = {
	"q1.Eat veg?",
	(const char *) 0 
};



//struct axis_q1 ax_q1(q1_data, q1_ttl_stmt_arr);


axis_q1::axis_q1( /* int32_t & p_q1_data, */ const char * p_text_ttls[], EditDataStruct & p_ed)
	: ed(p_ed), ttl_stmt_text (), count_stmt_text (3),
	axis_stmt_type_print (), axis_stmt_type_count (3) 
	, q1_data (ed.q1_data)
{
	for (const char ** a_ptr = p_text_ttls; *a_ptr != (char *) 0; ++a_ptr) {
		ttl_stmt_text.push_back (string(*a_ptr));
		axis_stmt_type_print.push_back (Table::txt_axstmt);
	}
	count_stmt_text[0]="Total";
	tot_elem_pos_vec.push_back(0);
	axis_stmt_type_count[0]=Table::tot_axstmt;
	count_stmt_text[1]="Yes";
	axis_stmt_type_count[1]=Table::cnt_axstmt;
	count_stmt_text[2]="No";
	axis_stmt_type_count[2]=Table::cnt_axstmt;
	for (int i=0; i<3; ++i) { flag[i] = 0; }
} 	/*  close constructor */


	void axis_q2::reset(){
		//flag.reset();

		for (int i=0; i<6; ++i) { flag[i] = 0; }
	}
void axis_q2::compute()
{
	printf ("Enter: %s\n", __PRETTY_FUNCTION__);
	//flag.reset();
	for (int i=0; i<6; ++i) { flag[i] = 0; }
	flag[0]=true;
	if ( q2_arr[1]>0 ){
		flag[1]=true;
	}
	if ( q2_arr[2]>0 ){
		flag[2]=true;
	}
	if ( q2_arr[3]>0 ){
		flag[3]=true;
	}
	if ( q2_arr[4]>0 ){
		flag[4]=true;
	}
	if ( q2_arr[5]>0 ){
		flag[5]=true;
	}
	for (int i=0; i < 6; ++i) {
		int v = flag[i];
		printf ("flag[%d]:%d\n", i, v);
	}
	printf ("flag address: %x\n", flag);
	printf ("Exit: %s\n", __PRETTY_FUNCTION__);
} /* close compute func */

const char * q2_ttl_stmt_arr[] = {
	"q2.Which veg u r aware of?",
	(const char *) 0 
};

//struct axis_q2 ax_q2(q2_arr, q2_ttl_stmt_arr);
axis_q2::axis_q2 (/* int32_t (& p_q2_arr) [6], */ const char * p_text_ttls[], EditDataStruct & p_ed)
	: ed (p_ed),
	  ttl_stmt_text (), count_stmt_text (6), axis_stmt_type_print (), axis_stmt_type_count (6),
	  q2_arr (ed.q2_arr)
{
	for (const char ** a_ptr = p_text_ttls; *a_ptr != (char *) 0; ++a_ptr) {
		ttl_stmt_text.push_back (string(*a_ptr));
		axis_stmt_type_print.push_back (Table::txt_axstmt);
	}
	count_stmt_text[0]="Total";
	tot_elem_pos_vec.push_back(0);
	axis_stmt_type_count[0]=Table::tot_axstmt;
	count_stmt_text[1]="Tomates";
	axis_stmt_type_count[1]=Table::cnt_axstmt;
	count_stmt_text[2]="Potatoes";
	axis_stmt_type_count[2]=Table::cnt_axstmt;
	count_stmt_text[3]="Capsicum";
	axis_stmt_type_count[3]=Table::cnt_axstmt;
	count_stmt_text[4]="Brinjal/Egg plant";
	axis_stmt_type_count[4]=Table::cnt_axstmt;
	count_stmt_text[5]="Okra/Lady Finger";
	axis_stmt_type_count[5]=Table::cnt_axstmt;
	for (int i=0; i<6; ++i) { flag[i] = 0; }
	//printf ("flag address: %x\n", flag);
	printf ("Exit: %s\n", __PRETTY_FUNCTION__);
}/*  close constructor */

#if 0

const char * q3_ttl_stmt_arr[] = {
"q3.Which veg dou eat?",

	(const char *) 0 };
 struct axis_q2 ax_q3(q3_arr, q3_ttl_stmt_arr);
	void axis_q4::reset(){
		flag.reset();
	}
	void axis_q4::compute(){
		flag.reset();
		flag[0]=true;
	if ( q4_data==1 ){
		flag[1]=true;
	}
	if ( q4_data==2 ){
		flag[2]=true;
	}
	if ( q4_data==3 ){
		flag[3]=true;
	}
	if ( q4_data==4 ){
		flag[4]=true;
	}
	if ( q4_data==5 ){
		flag[5]=true;
	}
	} /* close compute func */
const char * q4_ttl_stmt_arr[] = {
"q4.Which is ur fav veg?",
"",

	(const char *) 0 };
struct axis_q4 ax_q4(q4_data, q4_ttl_stmt_arr);
axis_q4::axis_q4(int32_t & p_q4_data, const char * p_text_ttls[])
:ttl_stmt_text (), count_stmt_text (6), axis_stmt_type_print (), axis_stmt_type_count (6) 
, q4_data (p_q4_data){
	for (const char ** a_ptr = p_text_ttls; *a_ptr != (char *) 0; ++a_ptr) {
		ttl_stmt_text.push_back (string(*a_ptr));
		axis_stmt_type_print.push_back (Table::txt_axstmt);
	}
		count_stmt_text[0]="Total";
	tot_elem_pos_vec.push_back(0);
		 axis_stmt_type_count[0]=Table::tot_axstmt;
		count_stmt_text[1]="Tomates";
		 axis_stmt_type_count[1]=Table::cnt_axstmt;
		count_stmt_text[2]="Potatoes";
		 axis_stmt_type_count[2]=Table::cnt_axstmt;
		count_stmt_text[3]="Capsicum";
		 axis_stmt_type_count[3]=Table::cnt_axstmt;
		count_stmt_text[4]="Brinjal/Egg plant";
		 axis_stmt_type_count[4]=Table::cnt_axstmt;
		count_stmt_text[5]="Okra/Lady Finger";
		 axis_stmt_type_count[5]=Table::cnt_axstmt;
	}/*  close constructor */


	void axis_q5_0::reset(){
		flag.reset();
	}
	void axis_q5_0::compute(){
		flag.reset();
		flag[0]=true;
	if ( q5_0_data==5 ){
		flag[1]=true;
	}
	if ( q5_0_data==4 ){
		flag[2]=true;
	}
	if ( q5_0_data==3 ){
		flag[3]=true;
	}
	if ( q5_0_data==2 ){
		flag[4]=true;
	}
	if ( q5_0_data==1 ){
		flag[5]=true;
	}
	if ( q5_0_data==5||q5_0_data==4 ){
		flag[6]=true;
	}
	if ( q5_0_data==1||q5_0_data==2 ){
		flag[7]=true;
	}
	if ( q5_0_data>=1&&q5_0_data<=5 ){
		flag[8]=true;
	}
	} /* close compute func */
const char * q5_0_ttl_stmt_arr[] = {
"q5.Please state your agreement with these statements",
" Vegetables are good for health",

	(const char *) 0 };
struct axis_q5_0 ax_q5_0(q5_0_data, q5_0_ttl_stmt_arr);
axis_q5_0::axis_q5_0(int32_t & p_q5_0_data, const char * p_text_ttls[])
:ttl_stmt_text (), count_stmt_text (9), axis_stmt_type_print (), axis_stmt_type_count (9) 
, q5_0_data (p_q5_0_data){
	for (const char ** a_ptr = p_text_ttls; *a_ptr != (char *) 0; ++a_ptr) {
		ttl_stmt_text.push_back (string(*a_ptr));
		axis_stmt_type_print.push_back (Table::txt_axstmt);
	}
		count_stmt_text[0]="Total";
	tot_elem_pos_vec.push_back(0);
		 axis_stmt_type_count[0]=Table::tot_axstmt;
		count_stmt_text[1]="5 agree strongly";
		 axis_stmt_type_count[1]=Table::cnt_axstmt;
		count_stmt_text[2]="4 agree somewhat";
		 axis_stmt_type_count[2]=Table::cnt_axstmt;
		count_stmt_text[3]="3 Neutral";
		 axis_stmt_type_count[3]=Table::cnt_axstmt;
		count_stmt_text[4]="2 Disagree ";
		 axis_stmt_type_count[4]=Table::cnt_axstmt;
		count_stmt_text[5]="1 Disagree strongly";
		 axis_stmt_type_count[5]=Table::cnt_axstmt;
		count_stmt_text[6]="Top 2 Box (Net)";
		 axis_stmt_type_count[6]=Table::cnt_axstmt;
		count_stmt_text[7]="Bottom 2 Box (Net)";
		 axis_stmt_type_count[7]=Table::cnt_axstmt;
		count_stmt_text[8]="inc_ax_stmt";
		 axis_stmt_type_count[8]=Table::inc_axstmt;
	}/*  close constructor */


const char * q5_1_ttl_stmt_arr[] = {
"q5.Please state your agreement with these statements",
" I buy fresh vegetables often",

	(const char *) 0 };
 struct axis_q5_0 ax_q5_1(q5_1_data, q5_1_ttl_stmt_arr);
const char * q5_2_ttl_stmt_arr[] = {
"q5.Please state your agreement with these statements",
" Greens are good source of dietary fibre",

	(const char *) 0 };
 struct axis_q5_0 ax_q5_2(q5_2_data, q5_2_ttl_stmt_arr);
const char * q5_3_ttl_stmt_arr[] = {
"q5.Please state your agreement with these statements",
" I would like to be vegetarian some day",

	(const char *) 0 };
 struct axis_q5_0 ax_q5_3(q5_3_data, q5_3_ttl_stmt_arr);
	void axis_q6_0::reset(){
		flag.reset();
	}
	void axis_q6_0::compute(){
		flag.reset();
		flag[0]=true;
	if ( q6_0_data>=0&&q6_0_data<=100 ){
		flag[1]=true;
	}
	} /* close compute func */
const char * q6_0_ttl_stmt_arr[] = {
"q6.In a week what perc of your veggies are : ",
"Tomates",

	(const char *) 0 };
struct axis_q6_0 ax_q6_0(q6_0_data, q6_0_ttl_stmt_arr);
axis_q6_0::axis_q6_0(int32_t & p_q6_0_data, const char * p_text_ttls[])
:ttl_stmt_text (), count_stmt_text (2), axis_stmt_type_print (), axis_stmt_type_count (2) 
, q6_0_data (p_q6_0_data){
	for (const char ** a_ptr = p_text_ttls; *a_ptr != (char *) 0; ++a_ptr) {
		ttl_stmt_text.push_back (string(*a_ptr));
		axis_stmt_type_print.push_back (Table::txt_axstmt);
	}
		count_stmt_text[0]="Total";
	tot_elem_pos_vec.push_back(0);
		 axis_stmt_type_count[0]=Table::tot_axstmt;
		count_stmt_text[1]="0 - 100";
		 axis_stmt_type_count[1]=Table::cnt_axstmt;
	}/*  close constructor */


	void axis_q6_1::reset(){
		flag.reset();
	}
	void axis_q6_1::compute(){
		flag.reset();
		flag[0]=true;
	if ( q6_1_data>=0&&q6_1_data<=100 ){
		flag[1]=true;
	}
	} /* close compute func */
const char * q6_1_ttl_stmt_arr[] = {
"q6.In a week what perc of your veggies are : ",
"Potatoes",

	(const char *) 0 };
struct axis_q6_1 ax_q6_1(q6_1_data, q6_1_ttl_stmt_arr);
axis_q6_1::axis_q6_1(int32_t & p_q6_1_data, const char * p_text_ttls[])
:ttl_stmt_text (), count_stmt_text (2), axis_stmt_type_print (), axis_stmt_type_count (2) 
, q6_1_data (p_q6_1_data){
	for (const char ** a_ptr = p_text_ttls; *a_ptr != (char *) 0; ++a_ptr) {
		ttl_stmt_text.push_back (string(*a_ptr));
		axis_stmt_type_print.push_back (Table::txt_axstmt);
	}
		count_stmt_text[0]="Total";
	tot_elem_pos_vec.push_back(0);
		 axis_stmt_type_count[0]=Table::tot_axstmt;
		count_stmt_text[1]="0 - 100";
		 axis_stmt_type_count[1]=Table::cnt_axstmt;
	}/*  close constructor */


	void axis_q6_2::reset(){
		flag.reset();
	}
	void axis_q6_2::compute(){
		flag.reset();
		flag[0]=true;
	if ( q6_2_data>=0&&q6_2_data<=100 ){
		flag[1]=true;
	}
	} /* close compute func */
const char * q6_2_ttl_stmt_arr[] = {
"q6.In a week what perc of your veggies are : ",
"Capsicum",

	(const char *) 0 };
struct axis_q6_2 ax_q6_2(q6_2_data, q6_2_ttl_stmt_arr);
axis_q6_2::axis_q6_2(int32_t & p_q6_2_data, const char * p_text_ttls[])
:ttl_stmt_text (), count_stmt_text (2), axis_stmt_type_print (), axis_stmt_type_count (2) 
, q6_2_data (p_q6_2_data){
	for (const char ** a_ptr = p_text_ttls; *a_ptr != (char *) 0; ++a_ptr) {
		ttl_stmt_text.push_back (string(*a_ptr));
		axis_stmt_type_print.push_back (Table::txt_axstmt);
	}
		count_stmt_text[0]="Total";
	tot_elem_pos_vec.push_back(0);
		 axis_stmt_type_count[0]=Table::tot_axstmt;
		count_stmt_text[1]="0 - 100";
		 axis_stmt_type_count[1]=Table::cnt_axstmt;
	}/*  close constructor */


	void axis_q6_3::reset(){
		flag.reset();
	}
	void axis_q6_3::compute(){
		flag.reset();
		flag[0]=true;
	if ( q6_3_data>=0&&q6_3_data<=100 ){
		flag[1]=true;
	}
	} /* close compute func */
const char * q6_3_ttl_stmt_arr[] = {
"q6.In a week what perc of your veggies are : ",
"Brinjal/Egg plant",

	(const char *) 0 };
struct axis_q6_3 ax_q6_3(q6_3_data, q6_3_ttl_stmt_arr);
axis_q6_3::axis_q6_3(int32_t & p_q6_3_data, const char * p_text_ttls[])
:ttl_stmt_text (), count_stmt_text (2), axis_stmt_type_print (), axis_stmt_type_count (2) 
, q6_3_data (p_q6_3_data){
	for (const char ** a_ptr = p_text_ttls; *a_ptr != (char *) 0; ++a_ptr) {
		ttl_stmt_text.push_back (string(*a_ptr));
		axis_stmt_type_print.push_back (Table::txt_axstmt);
	}
		count_stmt_text[0]="Total";
	tot_elem_pos_vec.push_back(0);
		 axis_stmt_type_count[0]=Table::tot_axstmt;
		count_stmt_text[1]="0 - 100";
		 axis_stmt_type_count[1]=Table::cnt_axstmt;
	}/*  close constructor */


	void axis_q6_4::reset(){
		flag.reset();
	}
	void axis_q6_4::compute(){
		flag.reset();
		flag[0]=true;
	if ( q6_4_data>=0&&q6_4_data<=100 ){
		flag[1]=true;
	}
	} /* close compute func */
const char * q6_4_ttl_stmt_arr[] = {
"q6.In a week what perc of your veggies are : ",
"Okra/Lady Finger",

	(const char *) 0 };
struct axis_q6_4 ax_q6_4(q6_4_data, q6_4_ttl_stmt_arr);
axis_q6_4::axis_q6_4(int32_t & p_q6_4_data, const char * p_text_ttls[])
:ttl_stmt_text (), count_stmt_text (2), axis_stmt_type_print (), axis_stmt_type_count (2) 
, q6_4_data (p_q6_4_data){
	for (const char ** a_ptr = p_text_ttls; *a_ptr != (char *) 0; ++a_ptr) {
		ttl_stmt_text.push_back (string(*a_ptr));
		axis_stmt_type_print.push_back (Table::txt_axstmt);
	}
		count_stmt_text[0]="Total";
	tot_elem_pos_vec.push_back(0);
		 axis_stmt_type_count[0]=Table::tot_axstmt;
		count_stmt_text[1]="0 - 100";
		 axis_stmt_type_count[1]=Table::cnt_axstmt;
	}/*  close constructor */


	void axis_tot_ax::reset(){
		flag.reset();
	}
	void axis_tot_ax::compute(){
		flag.reset();
	if ( all==1 ){
		flag[0]=true;
	}
	} /* close compute func */
const char * tot_ax_ttl_stmt_arr[] = {
"Total",

	(const char *) 0 };
struct axis_tot_ax ax_tot_ax(all, tot_ax_ttl_stmt_arr);
axis_tot_ax::axis_tot_ax(int32_t & p_all, const char * p_text_ttls[])
:ttl_stmt_text (), count_stmt_text (1), axis_stmt_type_print (), axis_stmt_type_count (1) 
, all (p_all){
	for (const char ** a_ptr = p_text_ttls; *a_ptr != (char *) 0; ++a_ptr) {
		ttl_stmt_text.push_back (string(*a_ptr));
		axis_stmt_type_print.push_back (Table::txt_axstmt);
	}
		count_stmt_text[0]="All";
		 axis_stmt_type_count[0]=Table::cnt_axstmt;
	}/*  close constructor */
#endif /*  0  */


AxesGroup::AxesGroup(EditDataStruct & p_ed): 
	 ed (p_ed),
	 ax_q1(q1_ttl_stmt_arr, ed),
	 ax_q2(/* q2_arr, */ q2_ttl_stmt_arr, ed)
	 //ax_q3(q3_arr, q3_ttl_stmt_arr),
	 //ax_q4(q4_data, q4_ttl_stmt_arr),
	 //ax_q5_0(q5_0_data, q5_0_ttl_stmt_arr),
	 //ax_q5_1(q5_1_data, q5_1_ttl_stmt_arr),
	 //ax_q5_2(q5_2_data, q5_2_ttl_stmt_arr),
	 //ax_q5_3(q5_3_data, q5_3_ttl_stmt_arr),
	 //ax_q6_0(q6_0_data, q6_0_ttl_stmt_arr),
	 //ax_q6_1(q6_1_data, q6_1_ttl_stmt_arr),
	 //ax_q6_2(q6_2_data, q6_2_ttl_stmt_arr),
	 //ax_q6_3(q6_3_data, q6_3_ttl_stmt_arr),
	 //ax_q6_4(q6_4_data, q6_4_ttl_stmt_arr),
	 //ax_tot_ax(all, tot_ax_ttl_stmt_arr)
{
	printf ("ax_q1.q1_data : %d\n", ax_q1.q1_data);
}
