#include "expr.h"
#include "stmt.h"
#include "log_mesg.h"

//struct AbstractStatement;
//struct table;
//struct ax;
extern Statement::AbstractStatement * tree_root;
extern char* work_dir;
extern int rec_len;
extern CodeOutputFiles code_output_files;

#include "Tab.h"
#include "ax_stmt_type.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <cstdlib>

using std::vector;
using std::map;
using std::string;
using std::cout;
using std::endl;
using std::cerr;
extern int no_errors;
extern int line_no;
extern vector<Table::table*>	table_list;
extern map <string, Table::ax*> ax_map;
FILE * global_vars;
#include <cstdio>
//void print_table_code(FILE * op, FILE *tab_drv_func, FILE * tab_summ_func, vector<Table::table*> & table_list);
//void print_latex_print(FILE* op, int table_index);

enum VariableDefnMode { FUNCTION_PARAMETER, ACTUAL_DEFNITION };
string print_variable_defn (map<string, SymbolTableEntry*>::iterator it1,
		VariableDefnMode mode)
{
	std::stringstream res;
	std::stringstream part2;
	std::stringstream part3;
	
	if (mode == FUNCTION_PARAMETER) {
		part2 << "p_";
	} else {
		// empty 
	}
	
	if (it1 -> second -> type_ == INT32_TYPE) {
		res << "int32_t & ";
		part3 <<  it1 -> first;
	} else if (it1 -> second -> type_ == INT32_ARR_TYPE) {
		res << "int32_t (& ";
		part3 << it1 -> first
				<< ") ["
				<< it1 -> second -> n_elms
				<< "]";
	} else if (it1 -> second -> type_ == FLOAT_TYPE) {
		res << "float & ";
		part3 	<< it1 -> first;
	} else if (it1 -> second -> type_ == FLOAT_ARR_TYPE) {
		res << "float (& ";
		part3 		<< it1 -> first
				<< ") ["
				<< it1 -> second -> n_elms
				<< "]";
	} else if (it1 -> second -> type_ == DOUBLE_TYPE) {
		res << "double & ";
		part3		<< it1 -> first;
	} else if (it1 -> second -> type_ == DOUBLE_ARR_TYPE) {
		res << "double (& ";
		part3		<< it1 -> first
				<< ") ["
				<< it1 -> second -> n_elms
				<< "]";
	} else if (it1 -> second -> type_ == INT8_TYPE) {
		res << "int8_t & ";
		part3		<< it1 -> first;
	} else if (it1 -> second -> type_ == INT8_ARR_TYPE) {
		res << "int8_t (& ";
		part3		<< it1 -> first
				<< ") ["
				<< it1 -> second -> n_elms
				<< "]";
	} else if (it1 -> second -> type_ == INT16_TYPE) {
		res << "int16_t & ";
		part3		<< it1 -> first;
	} else if (it1 -> second -> type_ == INT16_ARR_TYPE) {
		res << "int16_t (& ";
		part3		<< it1 -> first
				<< ") ["
				<< it1 -> second -> n_elms
				<< "]";
	} else {
		res << "unknown/unhandled variable type - this will cause a compile error - which is exactly what we want";
	}
	return res.str() + part2.str() + part3.str();
}

string print_variable_defns (map<string, SymbolTableEntry*> & name_list,
		VariableDefnMode mode)
{
	std::stringstream s;
	int iter_count = 0;
	for (map<string, SymbolTableEntry*>::iterator it1 = name_list.begin();
			it1 != name_list.end(); ++it1, ++iter_count) {
		if (mode == FUNCTION_PARAMETER && iter_count > 0) {
			s << ", ";
		} 
		if (mode == FUNCTION_PARAMETER) {
			s << print_variable_defn (it1, mode);
		}
		if (mode == ACTUAL_DEFNITION) {
			s << "\t" << print_variable_defn (it1, mode)
			  << ";" << endl;
		}
	}
	return s.str();
}

string print_mean_variable_defns (Table::CMAPITER map_iter_s, Table::CMAPITER map_iter_b)
{
	std::stringstream res;
	Table::AbstractCountableAxisStatement* side_stmt = 
		map_iter_s->second->count_ax_stmt_start;
	int cols=map_iter_b->second->no_count_ax_elems;

	int inc_ax_count = 0;
	//for (; side_stmt; side_stmt = side_stmt -> next_) {
	//	if (inc_ax_stmt * inc_st_ptr = 
	//		dynamic_cast<inc_ax_stmt*> (side_stmt)) {
	if (map_iter_s->second->no_inc_ax_elems > 0) {
		res << "vector<MeanStdDevInc> mean_inc_"
			<< map_iter_s->first
			<< "_"
			<< map_iter_b->first
			// << "("
			// <<  cols * map_iter_s->second->no_inc_ax_elems
			// << ")"
			//<< ";\n"
			;
	}
		//}
	//}
	return res.str();
}

/* 
void print_mean_variable_defns (Table::CMAPITER map_iter_s, Table::CMAPITER map_iter_b)
{
	string global_vars_fname_C = work_dir + string("/global.C");
	FILE * global_vars_C = fopen (global_vars_fname_C.c_str(), "a+b");
	string global_vars_fname = work_dir + string("/global.h");
	FILE * global_vars_h = fopen (global_vars_fname.c_str(), "a+b");
	if (! (global_vars_h||global_vars_C) ) {
		cerr << "Unable to open file: " << global_vars_fname 
			<< " or " << global_vars_fname_C
			<< " for writing ... exiting \n"
			<< endl;
		exit(1);
	}
	int rows=map_iter_s->second->no_count_ax_elems;
	int cols=map_iter_b->second->no_count_ax_elems;
	cerr << LOG_MESSAGE("fix mean_inc_ defn - there should be one for each table or maybe one for each axis")
		<< endl;
	fprintf (global_vars_h, "extern vector<MeanStdDevInc> mean_inc_%s_%s;\n",
			map_iter_s->first.c_str(), map_iter_b->first.c_str());
	fprintf (global_vars_C, "vector<MeanStdDevInc> mean_inc_%s_%s(%d);\n",
			map_iter_s->first.c_str(), map_iter_b->first.c_str(), cols * map_iter_s->second->no_inc_ax_elems);
	//printf  ("vector<MeanStdDevInc> mean_inc_%s_%s(%d);\n",
	//		map_iter_s->first.c_str(), map_iter_b->first.c_str(), cols * map_iter_s->second->no_inc_ax_elems);
	fclose (global_vars_h);
	fclose (global_vars_C);
}
*/


	map <string, string> stubname_axis_map;
void print_table_code (FILE * table_h, FILE * table_cpp, FILE * tab_drv_func, FILE * tab_summ_func, vector<Table::table*> & table_list, string tab_fname,
		string session_id)
{
	using namespace Table;
	fprintf (table_h, "#ifndef MY_TABLE_H\n");
	fprintf (table_h, "#define MY_TABLE_H\n");
	fprintf (table_h, "#include <iostream>\n");
	fprintf (table_h, "#include <fstream>\n");
	fprintf (table_h, "#include <sstream>\n");
	fprintf (table_h, "#include <vector>\nusing namespace std;\n");
	fprintf (table_h, "#include \"global.h\"\n");
	fprintf (table_h, "#include \"my_axes.h\"\n");
	fprintf (table_cpp, "#include \"%s_my_table.h\"\n", session_id.c_str());
	fprintf (tab_drv_func, "#include \"global.h\"\n");
	fprintf (tab_drv_func, "#include \"my_axes.h\"\n");
	fprintf (tab_drv_func, "#include \"%s_my_table.C\"\n", session_id.c_str());
	fprintf (tab_drv_func, "void tab_compute(){\n");
	// specifying no of threads - end result was much slower
	// seemed optimum at 4 - which is how many cores I have = 4
	// at 8 - the number of context switches went up exponentially
	//fprintf (tab_drv_func, "#pragma omp parallel sections num_threads(8)\n");
	fprintf (tab_drv_func, "#pragma omp parallel sections\n");
	fprintf (tab_drv_func, "{\n");
	set <string> ax_defns;
	for (unsigned int i=0; i<table_list.size(); i++) {
		CMAPITER map_iter_s= ax_map.find(table_list[i]->side);
		CMAPITER map_iter_b= ax_map.find (table_list[i]->banner);
		string s1 = "ax_" + map_iter_b->first;
		if (ax_defns.find (s1) == ax_defns.end()) {
			if (map_iter_b->second->stub_hint_axis == string()) {
				//fprintf (table_h, "#include \"ax_%s.h\"\n",
				//			map_iter_b->first.c_str ());
				fprintf (table_h, "extern struct axis_%s ax_%s;\n",
						map_iter_b->first.c_str(),
						map_iter_b->first.c_str());
			} else {
				fprintf (table_h, "extern struct axis_%s ax_%s;\n",
						map_iter_b->second->stub_hint_axis.c_str(),
						map_iter_b->first.c_str()
						);
			}
			ax_defns.insert(s1);
		}
		string s2 = "ax_" + map_iter_s->first;
		if (ax_defns.find (s2) == ax_defns.end()) {
			if (map_iter_s->second->stub_hint_axis == string()) {
				//fprintf (table_h, "#include \"ax_%s.h\"\n",
				//			map_iter_s->first.c_str());
				fprintf (table_h, "/* stub_hint_axis is empty  */\n");
				fprintf (table_h, "extern struct axis_%s ax_%s;\n",
						map_iter_s->first.c_str(),
						map_iter_s->first.c_str());
			} else {
				fprintf (table_h, "/* stub_hint_axis has data : %s*/\n",
						map_iter_s->second->stub_hint_axis.c_str());
				fprintf (table_h, "extern struct axis_%s ax_%s;\n",
						map_iter_s->second->stub_hint_axis.c_str(),
						map_iter_s->first.c_str()
						);
			}
			ax_defns.insert(s2);
		}
	}
	int total_no_of_cells = 0;
	int n_tables = table_list.size();
	int n_tables_div_by_4 = n_tables / 4;
	int n_tables_output_counter = 0;
	for (unsigned int i=0; i<table_list.size(); i++, ++n_tables_output_counter) {
		CMAPITER map_iter_s= ax_map.find(table_list[i]->side);
		CMAPITER map_iter_b= ax_map.find(table_list[i]->banner);
		if (map_iter_s==ax_map.end() || map_iter_b==ax_map.end()) {
			cerr << "Error: axis name " 
				<< table_list[i]->side << " or " 
				<< table_list[i]->banner << "not pres in axes defn"
				<< " line_no: " << line_no 
				<< endl;
			++ no_errors;
		} else {
			Expression::AbstractExpression * f = table_list[i] -> filter;
			// cout << "table: " <<
			// 	map_iter_b->first << " by " <<
			// 	map_iter_s->first << endl;
			//if ( f ){
			//	cout << " Filter: " ;
			//}
			// Handle the Banner by Banner case 
			if (map_iter_s -> second -> stub_hint_axis != string()
					&& map_iter_s -> second -> stub_hint != string("RangeQuestion") ) {
					fprintf (table_cpp, "\t/* stub_hint: %s */\n", map_iter_s->second->stub_hint_axis.c_str());
				if (map_iter_s->first != map_iter_b->first) {
					fprintf (table_cpp, "struct table_%s_%s tab_%s_%s(ax_%s, ax_%s",
							map_iter_s->second->stub_hint_axis.c_str(),
							map_iter_b->first.c_str(),
							map_iter_s->first.c_str(),
							map_iter_b->first.c_str(),
							map_iter_s->first.c_str(),
							map_iter_b->first.c_str()
							);
					{
						int counter = 0;
						std::stringstream s;
						for (map<string, SymbolTableEntry*>::iterator it1 = map_iter_s->second->name_list.begin();
								it1 != map_iter_s->second->name_list.end(); ++it1, ++counter) {
								//fprintf (op, ", ");
							s << ", ";
							//fprintf (op, "%s",
							//		it1 -> first.c_str());
							s << it1->first;
						}
						fprintf (table_cpp, "%s", s.str().c_str());
					}
					{
						int counter = 0;
						std::stringstream s;
						for (map<string, SymbolTableEntry*>::iterator it1 = map_iter_b->second->name_list.begin();
								it1 != map_iter_b->second->name_list.end(); ++it1, ++counter) {
								//fprintf (op, ", ");
							s << ", ";
							//fprintf (op, "%s",
							//		it1 -> first.c_str());
							s << it1->first;
						}
						fprintf (table_cpp, "%s", s.str().c_str());
					}
					fprintf (table_cpp, ");\n");
				} else {
					fprintf (table_cpp, "struct table_%s_%s tab_%s_%s(ax_%s",
							map_iter_s->second->stub_hint_axis.c_str(),
							map_iter_b->first.c_str(),
							map_iter_s->first.c_str(),
							map_iter_b->first.c_str(),
							map_iter_s->first.c_str()
							);
					{
						int counter = 0;
						std::stringstream s;
						for (map<string, SymbolTableEntry*>::iterator it1 = map_iter_s->second->name_list.begin();
								it1 != map_iter_s->second->name_list.end(); ++it1, ++counter) {
								//fprintf (op, ", ");
							s << ", ";
							//fprintf (op, "%s",
							//		it1 -> first.c_str());
							s << it1->first;
						}
						fprintf (table_cpp, "%s", s.str().c_str());
					}
					fprintf (table_cpp, ");\n");
				}
				//cout << "table : tab_" << map_iter_s->first 
				//	<< "_" << map_iter_b->first 
				//	<< " has " << 
				//		map_iter_s->second->no_count_ax_elems *
				//			map_iter_b->second->no_count_ax_elems
				//	<< " cells" 
				//	<< endl;
				total_no_of_cells += 	map_iter_s->second->no_count_ax_elems *
							map_iter_b->second->no_count_ax_elems;
				/* 
				{
					AbstractCountableAxisStatement* side_stmt=map_iter_s->second->count_ax_stmt_start;
					int rows=map_iter_s->second->no_count_ax_elems;
					for (int i=0; i<rows; ++i) {
						if (inc_ax_stmt * inc_st_ptr = dynamic_cast<inc_ax_stmt*>(side_stmt)) {
							print_mean_variable_defns (map_iter_s, map_iter_b);
						}
						if (side_stmt) {
							side_stmt=side_stmt->next_;
						}
					}
				} */
			} else {
				fprintf(table_h, "struct table_%s_%s {\n",
						map_iter_s->first.c_str(), map_iter_b->first.c_str ());
				fprintf(table_h, "\tstruct axis_%s & ax_%s;\n", map_iter_s->first.c_str(), map_iter_s->first.c_str());
#if 0
				{
					map<string, SymbolTableEntry*> & name_list = map_iter_s->second->name_list;
					stringstream s;
					for (map<string, SymbolTableEntry*>::iterator it1 = name_list.begin();
							it1 != name_list.end(); ++it1) {
						s 	<< "\t" << print_variable_defn (it1, ACTUAL_DEFNITION)
							<< ";" << endl;
					}
					fprintf (table_h, "%s\n", s.str().c_str());
				}
#endif /* 0 */

				if (map_iter_s->first != map_iter_b->first) {
					fprintf(table_h, "\tstruct axis_%s & ax_%s;\n", map_iter_b->first.c_str(), map_iter_b->first.c_str());
				}
				fprintf (table_h, "%s", (print_variable_defns (map_iter_s->second->name_list,
								ACTUAL_DEFNITION)).c_str());
				if (map_iter_s->first != map_iter_b->first) {
					fprintf (table_h, "%s", (print_variable_defns (map_iter_b->second->name_list,
								ACTUAL_DEFNITION)).c_str());
				}
				fprintf (table_h, "\tconst int rows, cols;\n");
				fprintf (table_h, "\t//vector <int> counter;\n");
				fprintf (table_h, "\tint counter[%d*%d];\n",
						map_iter_s->second->no_count_ax_elems,
						map_iter_b->second->no_count_ax_elems
						);
				fprintf (table_h, "\tconst int counter_size;\n");
				string mean_score_defns = print_mean_variable_defns (map_iter_s, map_iter_b);
				if (map_iter_s->second->no_inc_ax_elems > 0) {
					fprintf (table_h, "\t%s;\n", mean_score_defns.c_str());
				}
				fprintf (table_h, "\ttable_%s_%s (struct axis_%s & p_ax_%s",
						map_iter_s->first.c_str(), map_iter_b->first.c_str (),
						map_iter_s->first.c_str(), map_iter_s->first.c_str ());
				if (map_iter_s->first != map_iter_b->first) {
					fprintf (table_h, ", struct axis_%s & p_ax_%s",
						map_iter_b->first.c_str(), map_iter_b->first.c_str ());
				}
				fprintf (table_h, ", %s", (print_variable_defns (map_iter_s->second->name_list,
								FUNCTION_PARAMETER)).c_str());
				if (map_iter_s->first != map_iter_b->first) {
					fprintf (table_h, ", %s", (print_variable_defns (map_iter_b->second->name_list,
								FUNCTION_PARAMETER)).c_str());
				}
				fprintf (table_h, ")\n\t: rows(%d), cols(%d), ax_%s(p_ax_%s), counter_size(%d*%d)\n",
						map_iter_s->second->no_count_ax_elems,
						map_iter_b->second->no_count_ax_elems,
						//map_iter_s->second->no_count_ax_elems,
						//map_iter_b->second->no_count_ax_elems,
						map_iter_s->first.c_str(), map_iter_s->first.c_str (),
						map_iter_s->second->no_count_ax_elems,
						map_iter_b->second->no_count_ax_elems
						);

				total_no_of_cells += 	map_iter_s->second->no_count_ax_elems *
							map_iter_b->second->no_count_ax_elems;
				if (map_iter_s->first != map_iter_b->first) {
					fprintf (table_h, "\t, ax_%s(p_ax_%s)",
						map_iter_b->first.c_str(), map_iter_b->first.c_str ());
				}

#if 1
				{
					std::stringstream s;
					for (map<string, SymbolTableEntry*>::iterator it1 = 
							map_iter_s->second->name_list.begin();
							it1 != map_iter_s->second->name_list.end(); ++it1 ) {
						s 	<< ", ";
						s 	<< it1 -> first
							<< " (p_"
							<< it1 -> first
							<< ")";
					}
					fprintf (table_h, " %s", s.str().c_str());
				}
#endif /*  0 */
#if 1
				if (map_iter_s->first != map_iter_b->first) {
					std::stringstream s;
					for (map<string, SymbolTableEntry*>::iterator it1 = 
							map_iter_b->second->name_list.begin();
							it1 != map_iter_b->second->name_list.end(); ++it1 ) {
						s 	<< ", ";
						s 	<< it1 -> first
							<< " (p_"
							<< it1 -> first
							<< ")";
					}
					fprintf (table_h, " %s", s.str().c_str());
				}
#endif /*  0 */
				if (map_iter_s->second->no_inc_ax_elems > 0) {
					fprintf (table_h, ", mean_inc_%s_%s (%d)"
						, map_iter_s->first.c_str()
						, map_iter_b->first.c_str()
						, map_iter_b->second->no_count_ax_elems 
						  * map_iter_s->second->no_inc_ax_elems
					);
				}


				fprintf (table_h, "\n\t{\n\t\tfor (int i=0;i<counter_size;++i) counter[i]=0; \n");
				if (map_iter_s->second->no_inc_ax_elems > 0 || 
							map_iter_b->second->no_inc_ax_elems > 0) {
					fprintf(table_h, "\t\tfor (int i=0; i<mean_inc_%s_%s.size(); ++i) {\n\t\t\tmean_inc_%s_%s[i].sum_n=0.0; mean_inc_%s_%s[i].n=0.0;\n\t\t}\n",
							map_iter_s->first.c_str(), map_iter_b->first.c_str (),
							map_iter_s->first.c_str(), map_iter_b->first.c_str (),
							//map_iter_s->first.c_str(), map_iter_b->first.c_str (),
							//map_iter_s->first.c_str(), map_iter_b->first.c_str (),
							//map_iter_s->first.c_str(), map_iter_b->first.c_str (),
							map_iter_s->first.c_str(), map_iter_b->first.c_str ()
							);
				}
				fprintf(table_h, "\t}\n");

				/*
				fprintf(table_h, "\tvoid compute(){\n");
				fprintf(table_h, "\t\tfor(int i=0; i<rows; ++i){\n");
				fprintf(table_h, "\t\t\tfor(int j=0; j<cols; ++j){\n");
				fprintf(table_h, "\t\t\t\tif(");
				fprintf(table_h, "ax_%s.flag[i]", map_iter_s->first.c_str());
				fprintf(table_h, " && " );
				fprintf(table_h, "ax_%s.flag[j]){\n", map_iter_b->first.c_str());
				fprintf(table_h, "\t\t\t\t\t++counter[i*cols+j];\n");
				fprintf(table_h, "\t\t\t\t} \n");
				fprintf(table_h, "\t\t\t} \n");
				fprintf(table_h, "\t\t}\n");
				fprintf(table_h, "\t} \n");
				*/

				fprintf(table_h, "\tvoid compute(){\n");

				int rows=map_iter_s->second->no_count_ax_elems;
				int cols=map_iter_b->second->no_count_ax_elems;
				AbstractCountableAxisStatement* side_stmt=map_iter_s->second->count_ax_stmt_start;
				int inc_stmt_count=0;
				//for (int i=0; i<rows; ++i) 
				{
					fprintf (table_h, "\t\tfor(int i=0; i<rows; ++i) {\n");
					//cout << "generate_code: i: " << i << endl;
					AbstractCountableAxisStatement* banner_stmt = map_iter_b->second->count_ax_stmt_start;
					if (inc_ax_stmt * inc_st_ptr = dynamic_cast<inc_ax_stmt*>(side_stmt)) {
						print_mean_variable_defns (map_iter_s, map_iter_b);
						++inc_stmt_count;
					}
					fprintf(table_h, "\t\t\tif (ax_%s.flag[i]) {\n", map_iter_s->first.c_str());
					for (int j = 0; j < cols; ++j) {
						//cout << "generate_code: j: " << j << endl;
						// old fprintf(table_h, "\t\t\t\tif(");
						//fprintf(table_h, "ax_%s.flag[%d]", map_iter_s->first.c_str(), i);
						//fprintf(table_h, " && " );
						// old
						// old fprintf(table_h, "ax_%s.flag[%d]) {\n", map_iter_b->first.c_str(), j);
						if (!banner_stmt || ! side_stmt) {
							// handles the case of fld_stmt
							// old
							// old fprintf(table_h, "\t\t\t++counter[%d*cols+%d];\n",
							// old 		i, j);

							// new
							fprintf(table_h, "\t\t\t\t\t++counter[i*cols+%d] += ax_%s.flag[%d];\n",
									 j, map_iter_b->first.c_str(), j);
						} else if(side_stmt->CustomCountExpression() == false
							&& banner_stmt->CustomCountExpression() == false) {
							// old
							// old fprintf(table_h, "\t\t\t++counter[%d*cols+%d];\n",
							// old 		i, j);
							fprintf(table_h, "\t\t\t\t\tcounter[i*cols+%d] += ax_%s.flag[%d];\n",
									 j, map_iter_b->first.c_str(), j);
						} else if(side_stmt->CustomCountExpression() == true
							&& banner_stmt->CustomCountExpression() == false) {
							// Temporarily comment this out for now 
#if 0
							// cout << "side is inc_axstmt" << endl;
							// fprintf(table_h, "\t\t\tcounter[%d*cols+%d]+=",
							// 		i, j);
							inc_ax_stmt * inc_st_ptr = static_cast<inc_ax_stmt*>(side_stmt);
							//inc_st_ptr->PrintIncrExpression(table_h);
							//fprintf(table_h, ";\n");

							fprintf(table_h, "\t\t\t mean_inc_%s_%s[%d*cols+%d].sum_n +=",
									map_iter_s->first.c_str(), map_iter_b->first.c_str(),
									inc_stmt_count-1, j);
							//inc_ax_stmt * inc_st_ptr = static_cast<inc_ax_stmt*>(side_stmt);
							stringstream code;
							inc_st_ptr->PrintIncrExpression (table_h, code);
							fprintf(table_h, ";\n");
							fprintf(table_h, "\t\t\t mean_inc_%s_%s[%d*cols+%d].n +=1",
									map_iter_s->first.c_str(), map_iter_b->first.c_str(), 
									inc_stmt_count-1, j);
							fprintf(table_h, ";\n");
#endif /*  0 */
							cerr << "mean scores are temporarily commented out for the moment" 
								<< __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
								<< endl;
						} else if ( side_stmt->CustomCountExpression() == false
								&& banner_stmt->CustomCountExpression() == true) {
							// comment out mean score in the banner for the moment
							//cout << "banner is inc_axstmt" << endl;
							//fprintf(table_h, "\t\t\tcounter[%d*cols+%d]+=",
							//		i, j);
							//inc_ax_stmt * inc_st_ptr = static_cast<inc_ax_stmt*>(banner_stmt);
							//stringstream code;
							//inc_st_ptr->PrintIncrExpression (table_h, code);
							//fprintf(table_h, ";\n");
							cerr << "mean score in the banner is commented out for the moment" 
								<< __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
								<< endl;
						} else if (side_stmt == banner_stmt && 
								side_stmt->CustomCountExpression() == true) {
							cout << "  axis by axis -> diagonal table" << endl;
							// axis by axis -> diagonal table
							//fprintf(table_h, "\t\t\tcounter[%d*cols+%d]+=",
							//		i, j);
							//inc_ax_stmt * inc_st_ptr = static_cast<inc_ax_stmt*>(side_stmt);
							//stringstream code;
							//inc_st_ptr->PrintIncrExpression (table_h, code);
							//fprintf(table_h, ";\n");
							cerr << "axis by axis diagonal table with mean score in the banner is commented out for the moment" 
								<< __FILE__ << ", " << __LINE__ << ", " << __PRETTY_FUNCTION__
								<< endl;
						} else {
							print_err(Util::compiler_sem_err, "Error: trying to tabulate inc axis statement with inc axis statement"
								, line_no, __LINE__, __FILE__);
						}
						// handles the case of fld_stmt
						if (banner_stmt)
							banner_stmt=banner_stmt->next_;
						// old fprintf(table_h, "\t\t\t\t}\n");
					}
					fprintf(table_h, "\t\t\t}\n", map_iter_s->first.c_str(), i);
					// handles the case of fld_stmt
					if (side_stmt) {
						side_stmt=side_stmt->next_;
					}
					fprintf(table_h, "\t\t}\n");
				}
				fprintf(table_h, "\t} /*  close compute */\n");


#if 0
				ax * side_ax = map_iter_s->second;
				if( side_ax->ax_stmt_start && side_ax->fld_stmt==0) {
					fprintf(table_h, "ax_%s.flag[i]", map_iter_s->first.c_str());
				} else if ( side_ax->ax_stmt_start==0 && side_ax->fld_stmt) {
					fprintf(table_h, "ax_%s.fld_flag[i]", map_iter_s->first.c_str());
				}
				fprintf(table_h, " && " );
				ax * banner_ax = map_iter_b->second;
				if( banner_ax->ax_stmt_start && banner_ax->fld_stmt==0) {
					fprintf(table_h, "ax_%s.flag[i]){", map_iter_b->first.c_str());
				} else if ( banner_ax->ax_stmt_start==0 && banner_ax->fld_stmt) {
					fprintf(table_h, "ax_%s.fld_flag[i]){", map_iter_b->first.c_str());
				}
#endif /* 0 */
				fprintf(table_h, "\tvoid print(){\n\t\tint rci=0, cci=0; /* row counter index , col ... */\n");
				fprintf(table_h, "\t\tofstream tab_op(\"%s\", ios_base::out|ios_base::app);\n", tab_fname.c_str());
				fprintf(table_h, "\t\ttab_op << \"rows\" << \",\" << rows << \",cols\" << \",\" << cols << endl;\n");
				fprintf(table_h, "\t\ttab_op << \"\\\"\" << ax_%s.ttl_stmt_text[0] << \"\\\"\" << \",\" <<  \"\\\"\" << ax_%s.ttl_stmt_text[0] << \"\\\"\"  << endl;\n",
						map_iter_s->first.c_str(), map_iter_b->first.c_str()
						);
				fprintf(table_h, "\t\ttab_op << \",,\";\n");
				fprintf(table_h, "\t\tfor(int j=0; j<ax_%s.count_stmt_text.size(); ++j){\n", 
						map_iter_b->first.c_str());
				fprintf(table_h, "\t\t\t tab_op << \"\\\"\" << ax_%s.count_stmt_text[j] << \"\\\"\"  << \",\" ;\n", 
						map_iter_b->first.c_str()); 
				fprintf(table_h, "\t\t}\n");

#if 0
				if( banner_ax->ax_stmt_start && banner_ax->fld_stmt==0) {
					fprintf(table_h, "\t\tfor(int j=0; j<ax_%s.stmt_text.size(); ++j){\n", 
							map_iter_b->first.c_str());
					fprintf(table_h, "\t\t\tif(ax_%s.is_a_count_text[j]){\n", map_iter_b->first.c_str());
					fprintf(table_h, "\t\t\t\t tab_op << ax_%s.stmt_text[j] << \",\" ;\n", 
							map_iter_b->first.c_str()); 
					fprintf(table_h, "\t\t\t}\n");
					fprintf(table_h, "\t\t}\n");
				} else if ( banner_ax->ax_stmt_start==0 && banner_ax->fld_stmt) {
					fprintf(table_h, "\t\tfor(int j=0; j<ax_%s.bit_stmt_text.size(); ++j){\n", map_iter_b->first.c_str());
					fprintf(table_h, "\t\t\t tab_op << ax_%s.bit_stmt_text[j] << \",\" ;\n", 
							map_iter_b->first.c_str()); 
					fprintf(table_h, "\t\t}\n");
				}
#endif /* 0 */

				fprintf(table_h, "\t\ttab_op << endl;\n");
				fprintf(table_h, "\t\tint inc_counter=0;\n");
				fprintf(table_h, "\t\tfor (int i=0; i<ax_%s.count_stmt_text.size(); ++i) {\n",
						map_iter_s->first.c_str());
				fprintf(table_h, "\t\t\ttab_op << \",\";\n");
				fprintf(table_h, "\t\t\tstringstream col_perc_str;\n");
				fprintf(table_h, "\t\t\tstringstream row_perc_str;\n");
				fprintf(table_h, "\t\t\tcol_perc_str << \",,\";\n");
				fprintf(table_h, "\t\t\trow_perc_str << \",,\";\n");
				fprintf(table_h, "\t\t\tcci=0;\n");
				fprintf(table_h, "\t\t\ttab_op << \"\\\"\" << ax_%s.count_stmt_text[i] << \"\\\"\" << \",\";\n", map_iter_s->first.c_str()); 
				fprintf(table_h, "\t\t\t\tif (ax_%s.axis_stmt_type_count[rci] == Table::inc_axstmt) {\n", map_iter_s->first.c_str());
				fprintf(table_h, "\t\t\t\t\t++inc_counter;\n");
				fprintf(table_h, "\t\t\t\t}\n");
				fprintf(table_h, "\t\t\tfor (int j=0; j<ax_%s.count_stmt_text.size(); ++j) {\n",
					map_iter_b->first.c_str());
				fprintf(table_h, "\t\t\t\tif (ax_%s.axis_stmt_type_count[rci] == Table::cnt_axstmt) {\n", map_iter_s->first.c_str());
				fprintf(table_h, "\t\t\t\t\ttab_op << counter[cci+rci*cols]<<\",\";\n");
				fprintf(table_h, "\t\t\t\t\tif (ax_%s.tot_elem_pos_vec.size()>0) {\n", map_iter_s->first.c_str() );
				fprintf(table_h, "\t\t\t\t\t\tcol_perc_str << (((double) counter[cci+rci*cols]) / counter[cci+ax_%s.tot_elem_pos_vec[0]*cols]) * 100 <<\",\";\n", map_iter_s->first.c_str() );
				//fprintf(table_h, "\t\t\t\t\tcol_perc_str << ( counter[cci+ax_%s.tot_elem_pos_vec[0]*cols]) <<\",\";\n", map_iter_s->first.c_str() );
				fprintf(table_h, "\t\t\t\t\t}\n");
				fprintf(table_h, "\t\t\t\t\tif (ax_%s.tot_elem_pos_vec.size()>0) {\n", map_iter_b->first.c_str() );
				//fprintf(table_h, "\t\t\t\t\trow_perc_str << ax_%s.tot_elem_pos_vec[0] << \"|\" << ( counter[ax_%s.tot_elem_pos_vec[0]+cols*rci]) <<\",\";\n", map_iter_b->first.c_str(), map_iter_b->first.c_str() );
				fprintf(table_h, "\t\t\t\t\t\trow_perc_str << (((double) counter[cci+rci*cols]) / counter[ax_%s.tot_elem_pos_vec[0]+cols*rci]) * 100 <<\",\";\n", map_iter_b->first.c_str() );
				fprintf(table_h, "\t\t\t\t\t}\n");
				fprintf(table_h, "\t\t\t\t}\n");
				fprintf(table_h, "\t\t\t\tif (ax_%s.axis_stmt_type_count[rci] == Table::tot_axstmt) {\n", map_iter_s->first.c_str());
				fprintf(table_h, "\t\t\t\t\ttab_op << counter[cci+rci*cols]<<\",\";\n");
				fprintf(table_h, "\t\t\t\t}\n");

				if (map_iter_s->second->no_inc_ax_elems > 0 || 
							map_iter_b->second->no_inc_ax_elems > 0) {
					fprintf(table_h, "\t\t\t\tif (ax_%s.axis_stmt_type_count[rci] == Table::inc_axstmt) {\n", map_iter_s->first.c_str());
					fprintf(table_h, "\t\t\t\t\ttab_op << mean_inc_%s_%s[(inc_counter-1)*cols+cci].sum_n / mean_inc_%s_%s[(inc_counter-1)*cols+cci].n  << \",\";\n", map_iter_s->first.c_str(), map_iter_b->first.c_str(), map_iter_s->first.c_str(), map_iter_b->first.c_str() );
				fprintf(table_h, "\t\t\t\t}\n");
				}
				fprintf(table_h, "\t\t\t\t++cci;\n");
				fprintf(table_h, "\t\t\t}\n");
				fprintf(table_h, "\t\t\t++rci;\n");
				fprintf(table_h, "\t\t\ttab_op << endl;\n");
				fprintf(table_h, "\t\t\ttab_op << col_perc_str.str() << endl;\n");
				fprintf(table_h, "\t\t\ttab_op << row_perc_str.str() << endl;\n");
				fprintf(table_h, "\t\t}\n");
				fprintf(table_h, "\t\ttab_op << endl;\n");
				//fprintf(table_h, "\t\t}\n");
				fprintf(table_h, "\t\ttab_op.close();\n");
				fprintf(table_h, "\t} /*  close print */\n");



				//print_latex_print(table_h, i);
				fprintf (table_h, "} ;\n");
				//fprintf (table_cpp, "table_%s_%s tab_%s_%s (ax_%s, ax_%s);\n",
				//	 map_iter_s->first.c_str(), map_iter_b->first.c_str(),
				//	 map_iter_s->first.c_str(), map_iter_b->first.c_str(),
				//	 map_iter_s->first.c_str(), map_iter_b->first.c_str()
				//	 );
				// Handle the Banner by Banner case - above code doesnt
				if (map_iter_s->first != map_iter_b->first) {
					fprintf (table_cpp, "struct table_%s_%s tab_%s_%s(ax_%s, ax_%s",
							map_iter_s->first.c_str(),
							map_iter_b->first.c_str(),
							map_iter_s->first.c_str(),
							map_iter_b->first.c_str(),
							map_iter_s->first.c_str(),
							map_iter_b->first.c_str()
							);
					{
						int counter = 0;
						std::stringstream s;
						for (map<string, SymbolTableEntry*>::iterator it1 = map_iter_s->second->name_list.begin();
								it1 != map_iter_s->second->name_list.end(); ++it1, ++counter) {
								//fprintf (op, ", ");
							s << ", ";
							//fprintf (op, "%s",
							//		it1 -> first.c_str());
							s << it1->first;
						}
						fprintf (table_cpp, "%s", s.str().c_str());
					}
					{
						int counter = 0;
						std::stringstream s;
						for (map<string, SymbolTableEntry*>::iterator it1 = map_iter_b->second->name_list.begin();
								it1 != map_iter_b->second->name_list.end(); ++it1, ++counter) {
								//fprintf (op, ", ");
							s << ", ";
							//fprintf (op, "%s",
							//		it1 -> first.c_str());
							s << it1->first;
						}
						fprintf (table_cpp, "%s", s.str().c_str());
					}
					fprintf (table_cpp, ");\n");

				} else {
					fprintf (table_cpp, "struct table_%s_%s tab_%s_%s(ax_%s",
							map_iter_s->first.c_str(),
							map_iter_b->first.c_str(),
							map_iter_s->first.c_str(),
							map_iter_b->first.c_str(),
							map_iter_s->first.c_str()
							);
					{
						int counter = 0;
						std::stringstream s;
						for (map<string, SymbolTableEntry*>::iterator it1 = map_iter_s->second->name_list.begin();
								it1 != map_iter_s->second->name_list.end(); ++it1, ++counter) {
								//fprintf (op, ", ");
							s << ", ";
							//fprintf (op, "%s",
							//		it1 -> first.c_str());
							s << it1->first;
						}
						fprintf (table_cpp, "%s", s.str().c_str());
					}
					fprintf (table_cpp, ");\n");
				}
				//cout << "table : tab_" << map_iter_s->first 
				//	<< "_" << map_iter_b->first 
				//	<< " has " << 
				//		map_iter_s->second->no_count_ax_elems *
				//			map_iter_b->second->no_count_ax_elems
				//	<< " cells" 
				//	<< endl;

			}
			if (n_tables_output_counter == 0) {
				fprintf (tab_drv_func, "#pragma omp section\n");
				fprintf (tab_drv_func, "{\n");
			}


			if (map_iter_s->second->filter && map_iter_b->second->filter) {
				ostringstream code_bef_expr1, code_expr1;
				map_iter_s->second->filter->PrintExpressionCode (code_bef_expr1, code_expr1);
				
				ostringstream code_bef_expr2, code_expr2;
				map_iter_b->second->filter->PrintExpressionCode (code_bef_expr2, code_expr2);
				fprintf (tab_drv_func, "\tif ( %s && %s ) { \n", code_expr1.str().c_str(), code_expr2.str().c_str());
				fprintf (tab_drv_func, "\t\ttab_%s_%s.compute();\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str()
					);
				fprintf (tab_drv_func, "}\n");
			} else if (map_iter_s->second->filter) {
				ostringstream code_bef_expr1, code_expr1;
				map_iter_s->second->filter->PrintExpressionCode (code_bef_expr1, code_expr1);
				fprintf (tab_drv_func, "\tif ( %s ) { \n", code_expr1.str().c_str());
				fprintf (tab_drv_func, "\t\ttab_%s_%s.compute();\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str()
					);
				fprintf (tab_drv_func, "\t}\n");
			} else if (map_iter_b->second->filter) {
				ostringstream code_bef_expr1, code_expr1;
				map_iter_b->second->filter->PrintExpressionCode (code_bef_expr1, code_expr1);
				fprintf (tab_drv_func, "\tif ( %s ) { \n", code_expr1.str().c_str());
				fprintf (tab_drv_func, "\t\ttab_%s_%s.compute();\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str()
					);
				fprintf (tab_drv_func, "\t}\n");
			} else {
				fprintf (tab_drv_func, "\ttab_%s_%s.compute();\n",
					map_iter_s->first.c_str(), map_iter_b->first.c_str()
					);
			}

			if (n_tables_output_counter == n_tables_div_by_4) {
				fprintf (tab_drv_func, "\t}\n");
				fprintf (tab_drv_func, "#pragma omp section\n");
				fprintf (tab_drv_func, "{\n");
			} 
			else if (n_tables_output_counter == 2 * n_tables_div_by_4) {
				fprintf (tab_drv_func, "\t}\n");
				fprintf (tab_drv_func, "#pragma omp section\n");
				fprintf (tab_drv_func, "{\n");
			}
			else if (n_tables_output_counter == 3 * n_tables_div_by_4) {
				fprintf (tab_drv_func, "\t}\n");
				fprintf (tab_drv_func, "#pragma omp section\n");
				fprintf (tab_drv_func, "{\n");
			}

		}
	}

	fprintf (tab_drv_func, "\t} // close last omp section \n");
	fprintf (tab_drv_func, "}// close the sections pragma curly brace\n");
	fprintf(tab_drv_func, "}\n");
	cout << "total_no_of_cells: " << total_no_of_cells << endl;

	fprintf(tab_drv_func, "void tab_summ(){\n");
	for (unsigned int i=0; i<table_list.size(); i++) {
		CMAPITER map_iter_s= ax_map.find(table_list[i]->side);
		CMAPITER map_iter_b= ax_map.find(table_list[i]->banner);
		if(map_iter_s==ax_map.end()||map_iter_b==ax_map.end()){
			cerr << "Error: axis name " 
				<< table_list[i]->side << " or " 
				<< table_list[i]->banner << "not pres in axes defn"
				<< " line_no: " << line_no 
				<< endl;
			++ no_errors;
		} else {
			fprintf (tab_drv_func, "\ttab_%s_%s.print();\n",
				map_iter_s->first.c_str(), map_iter_b->first.c_str()
				);
			/*
			fprintf(tab_drv_func, "\ttab_%s_%s.print_latex();\n",
			map_iter_s->first.c_str(), map_iter_b->first.c_str()
			);
			*/
		}
	}
	fprintf(tab_drv_func, "}\n");
	fprintf(table_h, "#endif /*  MY_TABLE_H */\n");
	fflush (table_h);
	fflush (table_cpp);
}

void print_latex_print(FILE* op, int table_index)
{
	using namespace Table;
	CMAPITER map_iter_s= ax_map.find(table_list[table_index]->side);
	CMAPITER map_iter_b= ax_map.find(table_list[table_index]->banner);
	fprintf(op, "\tvoid print_latex(){\n\t\tint rci=0, cci=0; /* row counter index , col ... */\n");
	fprintf(op, "\t\t\tofstream tab_op(\"tab_.tex\", ios_base::out|ios_base::app);\n");
	fprintf(op, "\t\ttab_op << \"\\\\documentclass{article}\" << endl;\n");
	fprintf(op, "\t\ttab_op << \"\\\\usepackage{supertabular}\" << endl;\n");
	fprintf(op, "\t\ttab_op <<\"\\\\begin{document}\" << endl;\n");
	fprintf(op, "\t\ttab_op << \"\\\\tablecaption{\" << ax_%s.stmt_text[0] << \" x \" << ax_%s.stmt_text[0] << \"}\"<< endl;\n",
			map_iter_s->first.c_str(), map_iter_b->first.c_str()
			);
	fprintf(op, "\t\ttab_op << \"\\\\tablehead\" << endl;\n");
	fprintf(op, "\t\ttab_op << \"\t{\";\n");
	fprintf(op, "\t\tfor(int j=0; j<ax_%s.stmt_text.size(); ++j){\n", map_iter_b->first.c_str());
	fprintf(op, "\t\t\tif(ax_%s.is_a_count_text[j]){\n", map_iter_b->first.c_str());
	fprintf(op, "\t\t\t\t tab_op << \"\\\\bfseries \" << ax_%s.stmt_text[j] << \"&\" ;\n", map_iter_b->first.c_str()); 
	fprintf(op, "\t\t\t}\n");
	fprintf(op, "\t\ttab_op << \"\\\\\\\\ \\\\hline}\"<< endl ;\n");
	fprintf(op, "\t\ttab_op << \"\\\\tabletail\\n\";\n");
	fprintf(op, "\t\ttab_op << \"{\\\\hline \\\\multicolumn{3}{r}{\\\\emph{Continued on next_ page}}\\\\\\\\}\\\\n\";\n");
	fprintf(op, "\t\t}\n");
	fprintf(op, "\t\ttab_op << endl;\n");
	fprintf(op, "\t\t\tfor(int i=1; i<ax_%s.stmt_text.size(); ++i){\n",
			map_iter_s->first.c_str());
	fprintf(op, "\t\t\t\tcci=0;\n");
	fprintf(op, "\t\t\t\ttab_op << ax_%s.stmt_text[i] << \"&\";\n", map_iter_s->first.c_str()); 
	fprintf(op, "\t\t\t\tif(ax_%s.is_a_count_text[i]){\n", map_iter_s->first.c_str());
	fprintf(op, "\t\t\t\t\tfor(int j=0; j<ax_%s.stmt_text.size(); ++j){\n",
			map_iter_b->first.c_str());
	fprintf(op, "\t\t\t\t\tif(ax_%s.is_a_count_text[j]){\n", map_iter_b->first.c_str());
	fprintf(op, "\t\t\t\t\t\t//tab_op << \"rci:\" << rci << \"cci:\" << cci << endl;\n");
	fprintf(op, "\t\t\t\t\t\ttab_op << counter[cci+rci*cols]<<\"&\";\n");
	fprintf(op, "\t\t\t\t\t\t++cci;\n");
	fprintf(op, "\t\t\t\t\t}\n");
	fprintf(op, "\t\t\t\t}\n");
	fprintf(op, "\t\t\t\t++rci;\n");
	fprintf(op, "\t\t\t}\n");
	fprintf(op, "\t\ttab_op << endl;\n");
	fprintf(op, "\t\t}\n");
	fprintf(op, "\ttab_op.close();\n");
	fprintf(op, "\t}\n");
}


void print_ttl_defn_code ( string ax_name,  Table::ax* axis
		, std::stringstream & ttl_defns
		)
{
	int my_counter=0;
	ttl_defns << "const char * " << ax_name << "_ttl_stmt_arr[] = {\n";

	for (Table::AbstractPrintableAxisStatement* ax_stmt_iter = axis->ttl_ax_stmt_start; 
			ax_stmt_iter; ax_stmt_iter = ax_stmt_iter->next_,
			++my_counter) {
		ttl_defns
			<< ax_stmt_iter->ax_text()
			<< ",\n"; 
		if (ax_stmt_iter->axtype == Table::txt_axstmt) {
		} else {
			ttl_defns 
				<< "]= cause a compile error;\n";
			print_err (Util::compiler_internal_error, "Error generating code for axes - unknown type for print stmt"
						, line_no, __LINE__, __FILE__);
			++no_errors;
		}

	}
	ttl_defns << endl
		<< "\t(const char *) 0 };" << endl; 
}



//using namespace Table;
void print_constructor_code ( string ax_name,  Table::ax* axis, FILE * op, FILE * axes_drv_func
		, std::stringstream & constructor_header
		, std::stringstream & constructor_body
		, std::stringstream & ttl_defns
		, map <string, SymbolTableEntry*> name_list
		)
{

	// ===================================
	//fprintf (op, "\taxis_%s(",
	//		ax_name.c_str());
	print_ttl_defn_code ( ax_name,  axis
		, ttl_defns
		);
	constructor_header 
		//<<  "\taxis_"
		//<< ax_name 
		<<  "axis_"
		<< ax_name 
		<< "(";
			

	{
		int count = 0;
		for (map<string, SymbolTableEntry*>::iterator it1 = name_list.begin();
				it1 != name_list.end(); ++it1, ++count) {
			//fprintf (op, "/* generate reference defn for  %s \n",
					//it1 -> first.c_str());
			if (count > 0) {
				//fprintf (op, ", ");
				constructor_header << ", ";
			}
			constructor_header << print_variable_defn (it1, FUNCTION_PARAMETER);
		}
		constructor_header << ", const char * p_text_ttls[]";
			
	//fprintf (op, ")\n");
		constructor_header << ")\n";
	}

	//fprintf (op, "\t:ttl_stmt_text(%d),count_stmt_text(%d), axis_stmt_type_print(%d), axis_stmt_type_count(%d) \n"
	//		, axis->no_tot_ax_elems - axis->no_count_ax_elems
	//		, axis->no_count_ax_elems
	//		, axis->no_tot_ax_elems - axis->no_count_ax_elems
	//		, axis->no_count_ax_elems
	//		) ;

	constructor_body 
		//<< "axis_" << ax_name
		//<< "::axis_" << ax_name
		<<	":ttl_stmt_text (" 
		//<< 		/* axis->no_tot_ax_elems - axis->no_count_ax_elems */ 
		<< 		")"
		<<	    ", count_stmt_text (" << axis->no_count_ax_elems << ")"
		<<	    ", axis_stmt_type_print (" 
		//<< 		/* axis->no_tot_ax_elems - axis->no_count_ax_elems */ 
		<< 		")"
		<<	    ", axis_stmt_type_count (" << axis->no_count_ax_elems
		<<	    ") \n";

	{
		for (map<string, SymbolTableEntry*>::iterator it1 = name_list.begin();
				it1 != name_list.end(); ++it1 ) {
			//fprintf (op, "/* generate reference defn for  %s \n",
					//it1 -> first.c_str());
			//fprintf (op, ", ");
			constructor_body << ", ";
			//fprintf (op, "%s (p_%s)",
			//		it1 -> first.c_str(),
			//		it1 -> first.c_str()
			//		);
			constructor_body 
				<< it1 -> first
				<< " (p_"
				<< it1 -> first
				<< ")";
		}
	}
	//fprintf (op, "{\n");
	constructor_body <<  "{\n";

	//constructor_header << "\taxis_" << ax_name << "();" << endl;

	constructor_body
		<< "\tfor (const char ** a_ptr = p_text_ttls; *a_ptr != (char *) 0; ++a_ptr) {\n"
		<< "\t\tttl_stmt_text.push_back (string(*a_ptr));\n"
		<< "\t\taxis_stmt_type_print.push_back (Table::txt_axstmt);\n"
		<< "\t}\n";


	int my_counter=0;
	for (Table::AbstractCountableAxisStatement* ax_stmt_iter = axis->count_ax_stmt_start; 
			ax_stmt_iter; ax_stmt_iter = ax_stmt_iter->next_,
			++my_counter){
		//fprintf(op, "\tcount_stmt_text[%d]=%s;\n", my_counter, ax_stmt_iter->ax_text().c_str());
		ax_stmt_iter->print_axis_constructor_text (op, constructor_body, my_counter);
		if (Table::tot_ax_stmt * my_tot_ax_stmt = dynamic_cast<Table::tot_ax_stmt*> (ax_stmt_iter)) {
			//fprintf (op, "\ttot_elem_pos_vec.push_back(%d);\n", ax_stmt_iter->position_);
			constructor_body 
				<< "\ttot_elem_pos_vec.push_back("
				<< ax_stmt_iter->position_
				<< ");\n";
		}
		if (ax_stmt_iter->axtype == Table::tot_axstmt) {
			//fprintf (op, "\t\t axis_stmt_type_count[%d]=Table::tot_axstmt;\n", my_counter);
			constructor_body 
				<< "\t\t axis_stmt_type_count["
				<< my_counter << "]=Table::tot_axstmt;\n";
		} else if (ax_stmt_iter->axtype == Table::cnt_axstmt) {
			//fprintf (op, "\t\t axis_stmt_type_count[%d]=Table::cnt_axstmt;\n", my_counter);
			constructor_body
				<< "\t\t axis_stmt_type_count["
				<< my_counter 
				<< "]=Table::cnt_axstmt;\n";
		} else if (ax_stmt_iter->axtype == Table::fld_axstmt) {
			//fprintf (op, "\t\t axis_stmt_type_count[%d]=Table::fld_axstmt;\n", my_counter);
			constructor_body 
				<< "\t\t axis_stmt_type_count["
				<< my_counter 
				<< "]=Table::fld_axstmt;\n";
		} else if (ax_stmt_iter->axtype == Table::inc_axstmt) {
			//fprintf (op, "\t\t axis_stmt_type_count[%d]=Table::inc_axstmt;\n", my_counter);
			constructor_body
				<< "\t\t axis_stmt_type_count["
				<< my_counter 
				<< "]=Table::inc_axstmt;\n";
		} else {
			//fprintf (op, "\t\tttl_stmt_text[%d]= cause a compile error;\n", my_counter);
			constructor_body 
				<< "\t\tttl_stmt_text["
				<< my_counter 
				<< "]= cause a compile error;\n";
			print_err (Util::compiler_internal_error, "Error generating code for axes - unknown type for print stmt"
						, line_no, __LINE__, __FILE__);
			++no_errors;
		}
		
	}

	constructor_body <<  "\t}/*  close constructor */\n";
	// ===================================

}

void print_axis_class_includes (std::stringstream & _h, std::stringstream & _cpp)
{
	_h 	<<  "#include <bitset>\n"
		<<  "#include <string>\n"
		<<  "#include <vector>\n"
		<<  "#include <sys/types.h>\n"
		<<  "#include \"ax_stmt_type.h\"\n"
		<<  "using namespace std;\n";
	_cpp 	<< "#include \"my_table.h\"\n";
}


void print_axes_object_defn_with_constructor (std::stringstream & _cpp, std::string axis_struct_name,
		Table::CMAPITER  current_axis_iter,
		Table::CMAPITER  hint_axis_iter,
		std::stringstream & ttl_defns)
{
	//if (hint_axis_iter->first == "qc4a") {
	//	_cpp << "/*  hint axis == qc4a */" << endl;
	//}
	//if (current_axis_iter->first == "qc6a_Al_Inma_Bank") {
	//	_cpp << "/*  current_axis_iter axis == qc6a_Al_Inma_Bank */" << endl;
	//}

	// note: SIDE EFFECT on ttl_defns
	print_ttl_defn_code ( current_axis_iter->first,  current_axis_iter->second
		, ttl_defns
		);
	// note: SIDE EFFECT
	if (hint_axis_iter != ax_map.end()) {
		current_axis_iter->second->stub_hint_axis = hint_axis_iter->first;
	}
	//fprintf (op, "/* set stub_hint_axis for: %s to %s: found in stubname_axis_map */\n",
	//		current_axis_iter->first.c_str(), current_axis_iter->second->stub_hint_axis.c_str()
	//		);
	//fprintf (op, "struct axis_%s ax_%s(", axis_struct_name->second.c_str()
	//		, current_axis_iter->first.c_str() 
	//		);
	_cpp << "struct axis_" << axis_struct_name
		<< " ax_" <<  current_axis_iter->first.c_str()  << "(";
	//		
	Table::AbstractCountableAxisStatement* iter = current_axis_iter->second->count_ax_stmt_start;
	int counter = 0;
	map <string, SymbolTableEntry*> name_list ;
	while (iter) {
		//iter -> generate_code (op, axis_code_str_cpp, counter);
		Table::tot_ax_stmt * tot_stmt = dynamic_cast <Table::tot_ax_stmt*> (iter);
		Table::count_ax_stmt * cnt_stmt = dynamic_cast <Table::count_ax_stmt*> (iter);
		if (tot_stmt || cnt_stmt) {
			 hunt_for_names_in_expression (iter->condn, name_list);
		}
		++ counter;
		iter = iter -> next_;
	}
	// store current_axis_iter - as we need current_axis_iter 
	// for other axes that have the same
	// stub list generated using stub_hint(s)
	// Note: SIDE EFFECT
	current_axis_iter->second->name_list = name_list;
	//CMAPITER axis_iter2 = ax_map.find (axis_struct_name->second);
	//if (axis_iter2 != ax_map.end())
	//{
	//ax * axis_1 = axis_iter2->second;
	counter = 0;
	for (map<string, SymbolTableEntry*>::iterator it1 = name_list.begin();
			it1 != name_list.end(); ++it1, ++counter) {
		if (counter) {
			//fprintf (op, ", ");
			_cpp << ", ";
		}
		//fprintf (op, "%s",
		//		it1 -> first.c_str());
		_cpp << it1->first;
	}
	//}
	//fprintf (op, ");\n");
	_cpp  << ", " 
		<< current_axis_iter->first
		<< "_ttl_stmt_arr";
	_cpp << ");\n";

	//fflush (op);
}

void print_axis_struct_h (std::stringstream & _h,
		Table::CMAPITER  current_axis_iter,
		std::stringstream & constructor_h
		)
{

	//fprintf (op, "struct  axis_%s{\n", current_axis_iter->first.c_str() );
	_h << "struct axis_" << current_axis_iter->first << " {\n";
	//fprintf (op, "\tbitset<%d> flag;\n", current_axis_iter->second->no_count_ax_elems );
	_h << "\tbitset<" << current_axis_iter->second->no_count_ax_elems  << "> flag;\n" ;
	//fprintf (op, "\tvector<string> ttl_stmt_text;\n");
	//fprintf (op, "\tvector<string> count_stmt_text;\n");
	//fprintf (op, "\tvector<int> tot_elem_pos_vec;\n");
	_h 
		<<  "\tvector<string> ttl_stmt_text;\n"
		<<  "\tvector<string> count_stmt_text;\n"
		<<  "\tvector<int> tot_elem_pos_vec;\n";
	//fprintf (op, "\tbitset<%d> is_a_count_text;\n", current_axis_iter->second->no_tot_ax_elems);
	_h <<  "\tbitset<" 
		<< current_axis_iter->second->no_tot_ax_elems
		<< "> is_a_count_text;\n";
	//fprintf (op, "\tvector<Table::axstmt_type> axis_stmt_type_print;\n");
	//fprintf (op, "\tvector<Table::axstmt_type> axis_stmt_type_count;\n");
	_h << "\tvector<Table::axstmt_type> axis_stmt_type_print;\n"
			<< "\tvector<Table::axstmt_type> axis_stmt_type_count;\n";
	//string ax_name (current_axis_iter->first);
	//fprintf (op, "\tvoid reset(){\n\t\tflag.reset();\n\t}\n");
	_h << "\tvoid reset();\n";
	_h << "\tvoid compute();\n";

	map<string, SymbolTableEntry*> & name_list = current_axis_iter->second->name_list;
	for (map<string, SymbolTableEntry*>::iterator it1 = name_list.begin();
			it1 != name_list.end(); ++it1) {
		_h << print_variable_defn (it1, ACTUAL_DEFNITION)
			<< ";" << endl;
	}
	_h << "\t" << constructor_h.str() << ";" << endl;
	//fprintf (op, "} ax_%s(", it->first.c_str()) ;
	_h << "};\n";
}


void print_axis_code (FILE * axes_h, FILE * axes_cpp, FILE * axes_drv_func)
{
	using namespace Table;

	//fprintf (axes_h, "#include <bitset>\n" );
	//fprintf (axes_h, "#include <string>\n" );
	//fprintf (axes_h, "#include <vector>\n" );
	//fprintf (axes_h, "#include \"ax_stmt_type.h\"\n");
	//fprintf (axes_h, "using namespace std;\n" );
	stringstream h_includes, cpp_includes;
	print_axis_class_includes (h_includes, cpp_includes);
	fprintf (axes_h, "#ifndef MY_AXES_H\n");
	fprintf (axes_h, "#define MY_AXES_H\n");
	fprintf (axes_h, "%s", h_includes.str().c_str());

	fprintf (axes_drv_func, "#include \"global.h\"\n");
	fprintf (axes_drv_func, "#include \"my_axes.C\"\n");
	fprintf (axes_drv_func, "void ax_compute() {\n");
	fprintf (axes_drv_func, "#pragma omp parallel sections\n{\n");
	// too lazy to capture in the grammar for now - shift this there
	int n_axes = 0;
	for (CMAPITER it = ax_map.begin(); it != ax_map.end(); ++it, ++ n_axes) {
	}
	int n_axes_div_by_4 = n_axes / 4;
	int n_axes_output_counter = 0;
	for (CMAPITER it = ax_map.begin(); it != ax_map.end(); ++it, ++n_axes_output_counter) {
		//struct ax* l_ax = *it;
		//cout << "Processing axis: " << it->first.c_str() << endl;
		//bool found_stub_hint = false;
		bool can_use_stub_hint = false;
		map<string, string>::iterator stubname_axis_map_iter = stubname_axis_map.end();
		stringstream obj_defn;
		CMAPITER axmap_it2 = ax_map.end();
		//if (it->first == "qb3b_0") {
		//	obj_defn << "qb3b_0: stub_hint: " << it->second->stub_hint;
		//}

		if (it->second->stub_hint != string() && 
				it->second->stub_hint != string("RangeQuestion") ) {
			stubname_axis_map_iter 
				=  stubname_axis_map.find (it->second->stub_hint);
			if (stubname_axis_map_iter != stubname_axis_map.end()) {
				//fprintf (axes_h, "/* searching for axis: %s  */\n",
				//	stubname_axis_map_iter->second.c_str());
				axmap_it2 = ax_map.find (stubname_axis_map_iter->second);
				if (axmap_it2 != ax_map.end()) {
					if ( (axmap_it2->second->no_mpn == 1
						&& it->second->no_mpn == 1)
							||
					      (axmap_it2->second->no_mpn > 1
						&& it->second->no_mpn > 1)) {
						can_use_stub_hint = true;
					}
				}
			}
		}
		if (can_use_stub_hint == true) {

			//stringstream obj_defn;
			//if (it->first == string("qc6a_Al_Inma_Bank")) {
			//	obj_defn << "/*  processing qc6a_Al_Inma_Bank right now */" 
			//		<< endl;
			//}
			stringstream ttl_defns;
			print_axes_object_defn_with_constructor (obj_defn, 
					stubname_axis_map_iter->second,
					it, axmap_it2, ttl_defns);
			fprintf (axes_cpp, "%s %s"
					, ttl_defns.str().c_str()
					, obj_defn.str().c_str());
		} else {

			stringstream axis_code_str_h;
			//stringstream axes_code_str_h;
			stringstream axis_code_str_cpp;
			axis_code_str_h 
				<< "#ifndef xtcc_ax_" << it->first << "_h" << endl
				<< "#define xtcc_ax_" << it->first << "_h" << endl
				<< "#include <bitset>\n" 
				<< "#include <string>\n"
				<< "#include <vector>\n"
				<< "#include \"ax_stmt_type.h\"\n"
				<< "#include \"global.h\"\n"
				<< "using namespace std;\n";


			axis_code_str_cpp 
				<< "\tvoid axis_" 
				<< it->first
				<< "::reset(){\n\t\tflag.reset();\n\t}\n";
			axis_code_str_cpp 
				<< "\tvoid axis_" 
				<< it->first
				<< "::compute(){\n\t\tflag.reset();\n";

			AbstractCountableAxisStatement* iter = it->second->count_ax_stmt_start;
			map <string, SymbolTableEntry*> name_list ;
			while (iter) {
				tot_ax_stmt * tot_stmt = dynamic_cast <tot_ax_stmt*> (iter);
				count_ax_stmt * cnt_stmt = dynamic_cast <count_ax_stmt*> (iter);
				if (tot_stmt || cnt_stmt) {
					 hunt_for_names_in_expression (iter->condn, name_list);
				}
				iter = iter -> next_;
			}
			// store it - as we need it 
			// for other axes that have the same
			// stub list generated using stub_hint(s)
			it->second->name_list = name_list;
			bool has_single_named_var = false;
			if (name_list.size() == 1 && it->second->no_mpn == 1) {
				has_single_named_var = true;
				axis_code_str_cpp << "/*" << it->first <<   " :is single coded */" << endl;
			}
			int counter = 0;
			iter = it->second->count_ax_stmt_start;
			if (has_single_named_var) {
				axis_code_str_cpp << " switch ("
					<< name_list.begin()->first
					<< ") {" 
					<< "default:"
					<< endl;
			}


			while (iter) {
				iter -> generate_code (axes_h, axis_code_str_cpp, counter, has_single_named_var);
				//tot_ax_stmt * tot_stmt = dynamic_cast <tot_ax_stmt*> (iter);
				//count_ax_stmt * cnt_stmt = dynamic_cast <count_ax_stmt*> (iter);
				//if (tot_stmt || cnt_stmt) {
				//	 hunt_for_names_in_expression (iter->condn, name_list);
				//}
				++ counter;
				iter = iter -> next_;
			}
			if (has_single_named_var) {
				axis_code_str_cpp << "} /* close  switch */" << endl;
			}


			//fprintf (axes_h, "\t} /* close compute func */\n");
			axis_code_str_cpp << "\t} /* close compute func */\n";

			std::stringstream  constructor_header;
			std::stringstream  constructor_body;
			std::stringstream  ttl_defns;
			string ax_name (it->first);
			print_constructor_code ( ax_name,  it->second, axes_h, axes_drv_func
					, constructor_header, constructor_body
					, ttl_defns
					, name_list
					);
			stringstream axis_struct_h;
			print_axis_struct_h (axis_struct_h, it, constructor_header);
			fprintf (axes_h, "%s\n", axis_struct_h.str().c_str());
			std::stringstream  ttl_defns2;
			print_axes_object_defn_with_constructor (obj_defn, 
					//stubname_axis_map_iter->second,
					it->first,
					it, ax_map.end(), ttl_defns2);
			axis_code_str_cpp 
				<< ttl_defns.str()
				<< obj_defn.str()
				<< "axis_" << it->first << "::" 
				<< constructor_header.str() 
				<< constructor_body.str()
				<< endl;
			fprintf (axes_cpp, "%s\n", axis_code_str_cpp.str().c_str() );



			axis_code_str_h
				<< "} " 
				//<< "ax_" << it->first
				<< ";\n"
				<< "#endif /*  xtcc_ax_" << it->first << "_h */ " 
				<< endl;

			//string ax_file_h_name = work_dir + string("/ax_") + it->first + string(".h");
			//FILE * ax_file_h = fopen (ax_file_h_name.c_str(), "wb");
			//fprintf (ax_file_h, "%s\n", axis_code_str_h.str().c_str());
			//fclose (ax_file_h);
			//string ax_file_cpp_name = work_dir + string("/ax_") + it->first + string(".cpp");
			//FILE * ax_file_cpp = fopen (ax_file_cpp_name.c_str(), "wb");
			//fprintf (ax_file_cpp, "#include \"ax_%s.h\"\n", it->first.c_str());
			//fprintf (ax_file_cpp, "%s\n", axis_code_str_cpp.str().c_str());
			//fclose (ax_file_cpp);
			if (it->second->stub_hint != string()) {
				stubname_axis_map [it -> second -> stub_hint] = it->first;
			}
		// re-enable this section after demo with Gita Zhankar
#if 1
		}
		if (n_axes_output_counter == 0) {
			fprintf (axes_drv_func, "#pragma omp section\n");
			fprintf (axes_drv_func, "{\n");
		}
		if (it->second->filter) {
			//fprintf (axes_drv_func, "/* axis HAS a filter  \n");
			ostringstream code_bef_expr, code_expr;
			it -> second -> filter -> PrintExpressionCode (code_bef_expr, code_expr);
			fprintf (axes_drv_func, "if ( %s ) { \n", code_expr.str().c_str());
			fprintf (axes_drv_func, "\tax_%s.compute();\n",it->first.c_str());
			fprintf (axes_drv_func, "} else { ax_%s.reset(); }\n", it->first.c_str());
			fprintf (axes_drv_func, "\n");
		} else {
			fprintf (axes_drv_func, "/* axis DOES NOT have a filter  */\n");
			fprintf (axes_drv_func, "\tax_%s.compute();\n",it->first.c_str());
		}

		if (n_axes_output_counter == n_axes_div_by_4) {
			fprintf (axes_drv_func, "\t}\n");
			fprintf (axes_drv_func, "#pragma omp section\n");
			fprintf (axes_drv_func, "{\n");
		} 
		else if (n_axes_output_counter == 2 * n_axes_div_by_4) {
			fprintf (axes_drv_func, "\t}\n");
			fprintf (axes_drv_func, "#pragma omp section\n");
			fprintf (axes_drv_func, "{\n");
		}
		else if (n_axes_output_counter == 3 * n_axes_div_by_4) {
			fprintf (axes_drv_func, "\t}\n");
			fprintf (axes_drv_func, "#pragma omp section\n");
			fprintf (axes_drv_func, "{\n");
		}

#endif /*  0 */
	}
	fprintf (axes_drv_func, "\t} /*  close last omp section */\n");
	fprintf (axes_drv_func, "} /*  omp sections end */\n");
	fprintf (axes_drv_func, "}\n");
	fprintf (axes_h, "#endif /* MY_AXES_H */\n");
	fflush (axes_h);
	fflush (axes_cpp);
}


void	generate_edit_section_code();
void	generate_edit_section_code()
{
	string global_vars_fname = work_dir+string("/global.h");
	global_vars = fopen(global_vars_fname.c_str(), "wb");
	if (!global_vars) {
		cerr << "Unable to open file: " << global_vars_fname << " for writing ... exiting \n";
		exit(1);
	}
	fprintf (global_vars, "#ifndef __NxD_GLOB_VARS_H\n#define __NxD_GLOB_VARS_H\n");
	fprintf (global_vars, "#include <sys/types.h>\n");
	fprintf (global_vars, "#include <map>\n#include <vector>\nusing namespace std;\n");
	fprintf (global_vars, "#include \"mean_stddev_struct.h\"\n");
	fprintf (global_vars, "#include <cstdlib>\n");
	fprintf (global_vars, "#include <cstdio>\n");
	fprintf (global_vars, "extern FILE * runtime_errors ;\n");
	fprintf (global_vars, "void print_list_counts();\n");
	fprintf (global_vars, "void tab_compute();\n");
	fprintf (global_vars, "void tab_summ();\n");
	fprintf (global_vars, "void ax_compute();\n");
	string list_counts_fname = work_dir + string("/print_list_counts.C");
	FILE * print_list_counts=fopen(list_counts_fname.c_str(), "wb");
	fprintf(print_list_counts, "#include \"global.h\"\n");
	fprintf(print_list_counts, "#include <map>\n");
	fprintf(print_list_counts, "#include <string>\n");
	fprintf(print_list_counts, "template <class T>\nvoid print_list_summ(std::map<T,int> &m, std::string var_name, std::string text);\n");
	fprintf(print_list_counts, "void print_list_counts(){\n");
	fclose(print_list_counts);
	string edit_out_fname=work_dir+string( "/edit_out.c");
	FILE * edit_out= fopen(edit_out_fname.c_str(), "w+b");
	if(edit_out==0){
		printf("could not open edit_out.c for writing\n");
		exit(1);
	}
#if __WIN32__
	fprintf (edit_out, "#include \"stubs/iso_types.h\"\n" );
	fprintf (edit_out, "#include \"ax_stmt_type.h\"\n" );
#endif /* __WIN32__ */
	fprintf(edit_out, "#include <cstdio>\n#include <iostream>\n#include <string>\n#include <vector>\nusing namespace std;\n" );

	fprintf (edit_out, "string xtcc_stdout_fname(\"xtcc_stdout.log\");\n");
	fprintf (edit_out, "FILE * xtcc_stdout=0;\n");
	fprintf (edit_out, "#include <sys/types.h>\n" );
	fprintf (edit_out, "#include \"global.h\"\n" );
	cout << "printing edit:" << endl;
	fprintf (edit_out, "struct EditDataStruct {\n", rec_len );
	fprintf (edit_out, "int8_t c[%d];\n", rec_len );
	tree_root->GenerateCode(edit_out);
	fprintf (edit_out, "};\n");
	fclose (edit_out);

	string list_fname = work_dir + string("/print_list_counts.C");
	print_list_counts = fopen (list_fname.c_str(), "a+");
	fprintf (print_list_counts, "}\n");
	fclose (print_list_counts);
	fclose (global_vars);

}

void generate_make_file();
void generate_make_file()
{
	using namespace Table;
	string makefile_name=work_dir+string("/") + string("Makefile");
	FILE * makefile =fopen(makefile_name.c_str(), "wb");
	stringstream source_cpp_str;
	stringstream source_h_str;
	stringstream individual_dep_str;
	stringstream makefile_str;

	for (CMAPITER it=ax_map.begin(); it!=ax_map.end(); ++it) {
		source_cpp_str << "ax_" << it->first << ".cpp ";
		source_h_str << "ax_" << it->first << ".h ";
	}

	makefile_str << "CC = $(CXX) " << endl;
	makefile_str << "CPP_SOURCES = "
		<< source_cpp_str.str() << endl;
	makefile_str << "OBJECTS := $(CPP_SOURCES:.cpp=.o)\n";
	makefile_str << endl
		<< "my_edit.exe: $($CPP_SOURCES) $(OBJECTS)\n"
		<< "\techo \"dummy my_edit.exe target for now\"\n"
		<< endl;

	makefile_str << "%.o: %.cpp %.h\n"
			<< "\t$(CC) -c $(CFLAGS) $<\n"
			<< endl;

	makefile_str 
	<< "%.dep : %.cpp\n"
	<< "	@set -e; rm -f $@; \\\n"
	<< "		$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \\\n"
	<< "		sed 's,\\($*\\)\\.o[ :]*,\\1.o $@ :,g' < $@.$$$$ > $@; \\\n"
	<< "		rm -f $@.$$$$\n" 
	<< endl;




	fprintf(makefile, "%s\n", makefile_str.str().c_str());
	fclose(makefile);

}


std::string print_session_makefile (std::string session_id) 
{
	
	std::stringstream s;
	s << "CC=g++ -O3 -msse4.2 " << endl;
	s << "OBJS = "
		//<< session_id 
		<< "main_loop.o "
		//<< session_id 
		<< "my_axes_drv_func.o "
		<< session_id << "_my_tab_drv_func.o "
		<< "edit_out.o "
		<< "global.o"
		<< endl
		<< endl
		<< session_id << "_test.exe: $(OBJS)" << endl
		<< "\t$(CC)  -o $@ $(OBJS)" << endl << endl
		<< "main_loop.o: main_loop.C" << endl
		<< "\t$(CC)  -c $<" << endl << endl
		<< "my_axes_drv_func.o: my_axes_drv_func.C" << endl
		<< "\t$(CC)  -c $<"  << endl << endl
		<< session_id << "_my_tab_drv_func.o: " << session_id << "_my_tab_drv_func.C" << endl
		<< "\t$(CC)  -c $<" << endl << endl
		<< "edit_out.o: "   << "edit_out.c" << endl
		<< "\t$(CC)  -c $<" << endl << endl
		<< "global.o: " << "global.C" << endl
		<< "\t$(CC)  -c $<" << endl << endl;
	return s.str();
}
