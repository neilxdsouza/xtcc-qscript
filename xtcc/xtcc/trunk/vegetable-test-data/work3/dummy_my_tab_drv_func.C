#include "global.h"
#include "my_axes.h"
#include "dummy_my_table.C"



void tab_compute(TableGroup & tg, EditDataStruct & ed, AxesGroup & ag)
{
	printf("computing tabs\n");
	printf ("ag.ax_q1.q1_data: %d\n", ag.ax_q1.q1_data);
	printf ("ag.ax_q2.q2_arr[0]: %d\n", ag.ax_q2.q2_arr[0]);
	printf ("ag.ax_q2.q2_arr[1]: %d\n", ag.ax_q2.q2_arr[1]);
	printf ("ag.ax_q2.q2_arr[2]: %d\n", ag.ax_q2.q2_arr[2]);
	printf ("ag.ax_q2.q2_arr[3]: %d\n", ag.ax_q2.q2_arr[3]);
	printf ("ag.ax_q2.q2_arr[4]: %d\n", ag.ax_q2.q2_arr[4]);
	printf ("ag.ax_q2.q2_arr[5]: %d\n", ag.ax_q2.q2_arr[5]);
	tg.tab_q2_q1.compute();
}

void tab_summ(TableGroup & tg)
{
	tg.tab_q2_q1.print();
//	tg.tab_q2_tot_ax.print();
//	tg.tab_q3_tot_ax.print();
//	tg.tab_q4_tot_ax.print();
//	tg.tab_q6_0_tot_ax.print();
//	tg.tab_q6_1_tot_ax.print();
//	tg.tab_q6_2_tot_ax.print();
//	tg.tab_q6_3_tot_ax.print();
//	tg.tab_q6_4_tot_ax.print();
//	tg.tab_q5_0_tot_ax.print();
//	tg.tab_q5_1_tot_ax.print();
//	tg.tab_q5_2_tot_ax.print();
//	tg.tab_q5_3_tot_ax.print();
}
