#ifndef __NxD_GLOB_VARS_H
#define __NxD_GLOB_VARS_H
#include <sys/types.h>
#include <map>
#include <vector>
using namespace std;
#include "mean_stddev_struct.h"
#include <cstdlib>
#include <cstdio>
extern FILE * runtime_errors ;
void print_list_counts();
void tab_compute();
void tab_summ();
void ax_compute();
extern int32_t all;
extern int32_t ser_no;
extern int32_t q1_data;
extern int32_t q2_arr [ 6 ];
extern int32_t q3_arr [ 6 ];
extern int32_t q4_data;
extern int32_t q6_0_data;
extern int32_t q6_1_data;
extern int32_t q6_2_data;
extern int32_t q6_3_data;
extern int32_t q6_4_data;
extern int32_t q5_0_data;
extern int32_t q5_1_data;
extern int32_t q5_2_data;
extern int32_t q5_3_data;
#endif /* __NxD_GLOB_VARS_H--*/
