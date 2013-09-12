#include "global.h"
#include "my_axes.C"
#include "edit_out.h"
void ax_compute( AxesGroup & ag, EditDataStruct & ed) {
#pragma omp parallel sections
{
#pragma omp section
{
if ( ed.q1_data>0 ) { 
	ag.ax_q1.compute();
} else { ax_q1.reset(); }

if ( ed.q2_arr[0]>0 ) { 
	ag.ax_q2.compute();
} else { ax_q2.reset(); }

if ( ed.q3_arr[0]>0 ) { 
	ag.ax_q3.compute();
} else { ag.ax_q3.reset(); }

if ( ed.q4_data>0 ) { 
	ag.ax_q4.compute();
} else { ag.ax_q4.reset(); }

	}
#pragma omp section
{
if ( ed.q5_0_data>0 ) { 
	ag.ax_q5_0.compute();
} else { ag.ax_q5_0.reset(); }

if ( ed.q5_1_data>0 ) { 
	ag.ax_q5_1.compute();
} else { ag.ax_q5_1.reset(); }

if ( ed.q5_2_data>0 ) { 
	ag.ax_q5_2.compute();
} else { ag.ax_q5_2.reset(); }

	}
#pragma omp section
{
if ( ed.q5_3_data>0 ) { 
	ag.ax_q5_3.compute();
} else { ag.ax_q5_3.reset(); }

if ( ed.q6_0_data>0 ) { 
	ag.ax_q6_0.compute();
} else { ag.ax_q6_0.reset(); }

if ( ed.q6_1_data>0 ) { 
	ag.ax_q6_1.compute();
} else { ag.ax_q6_1.reset(); }

	}
#pragma omp section
{
if ( ed.q6_2_data>0 ) { 
	ag.ax_q6_2.compute();
} else { ag.ax_q6_2.reset(); }

if ( ed.q6_3_data>0 ) { 
	ag.ax_q6_3.compute();
} else { ag.ax_q6_3.reset(); }

if ( ed.q6_4_data>0 ) { 
	ag.ax_q6_4.compute();
} else { ag.ax_q6_4.reset(); }

/* axis DOES NOT have a filter  */
	ag.ax_tot_ax.compute();
	} /*  close last omp section */
} /*  omp sections end */
}
