#include "global.h"
#include "my_axes.h"
#include "dummy_my_table.C"



void tab_compute(TableGroup & tg, EditDataStruct & ed){
#pragma omp parallel sections
{
#pragma omp section
{
	if ( ed.q1_data>0 ) { 
		tg.tab_q1_tot_ax.compute();
	}
	if ( ed.q2_arr[0]>0 ) { 
		tg.tab_q2_tot_ax.compute();
	}
	if ( ed.q3_arr[0]>0 ) { 
		tg.tab_q3_tot_ax.compute();
	}
	if ( ed.q4_data>0 ) { 
		tg.tab_q4_tot_ax.compute();
	}
	}
#pragma omp section
{
	if ( ed.q6_0_data>0 ) { 
		tg.tab_q6_0_tot_ax.compute();
	}
	if ( ed.q6_1_data>0 ) { 
		tg.tab_q6_1_tot_ax.compute();
	}
	if ( ed.q6_2_data>0 ) { 
		tg.tab_q6_2_tot_ax.compute();
	}
	}
#pragma omp section
{
	if ( ed.q6_3_data>0 ) { 
		tg.tab_q6_3_tot_ax.compute();
	}
	if ( ed.q6_4_data>0 ) { 
		tg.tab_q6_4_tot_ax.compute();
	}
	if ( ed.q5_0_data>0 ) { 
		tg.tab_q5_0_tot_ax.compute();
	}
	}
#pragma omp section
{
	if ( ed.q5_1_data>0 ) { 
		tg.tab_q5_1_tot_ax.compute();
	}
	if ( ed.q5_2_data>0 ) { 
		tg.tab_q5_2_tot_ax.compute();
	}
	if ( ed.q5_3_data>0 ) { 
		tg.tab_q5_3_tot_ax.compute();
	}
	} // close last omp section 
}// close the sections pragma curly brace
}
void tab_summ(TableGroup & tg){
	tg.tab_q1_tot_ax.print();
	tg.tab_q2_tot_ax.print();
	tg.tab_q3_tot_ax.print();
	tg.tab_q4_tot_ax.print();
	tg.tab_q6_0_tot_ax.print();
	tg.tab_q6_1_tot_ax.print();
	tg.tab_q6_2_tot_ax.print();
	tg.tab_q6_3_tot_ax.print();
	tg.tab_q6_4_tot_ax.print();
	tg.tab_q5_0_tot_ax.print();
	tg.tab_q5_1_tot_ax.print();
	tg.tab_q5_2_tot_ax.print();
	tg.tab_q5_3_tot_ax.print();
}
