#include <sys/types.h>
#include <cstdio>
#include "edit_out.h"
#include "my_axes.h"
#include "dummy_my_table.h"

//struct table_q2_q1 tab_q2_q1(ax_q2, ax_q1, q2_arr, q1_data);

TableGroup::TableGroup(AxesGroup & p_ag, EditDataStruct & p_ed)
	: ed (p_ed), ag (p_ag),
	tab_q2_q1 (ag.ax_q2, ag.ax_q1, ed.q2_arr, ed.q1_data)
{

}
