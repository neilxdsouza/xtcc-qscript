/*
 * Copyright (C) 2008 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#include "xtcc_wt_ui.h"
#include "rest_get_hello.h"
#include "CsvUtil.h"
#include "ChartConfig.h"


#include <iostream>
#include <boost/lexical_cast.hpp>
#include <cstdlib>
#include <cstdio>
#include <sstream>

#include <Wt/WApplication>
#include <Wt/WSelectionBox>
#include <Wt/WAnchor>
#include <Wt/WResource>
#include <Wt/WContainerWidget>
#include <Wt/WEnvironment>
#include <Wt/WPanel>
#include <Wt/WLabel>
#include <Wt/WText>
#include <Wt/WScrollArea>
#include <Wt/WScrollArea>
#include <Wt/WFitLayout>
#include <Wt/Ext/Panel>
#include <Wt/WPushButton>
#include <Wt/WStandardItem>
#include <Wt/WStandardItemModel>
#include <Wt/WItemDelegate>
#include <Wt/WText>
#include <Wt/WTreeView>
#include <Wt/WTableView>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/Http/Response>
#include <Wt/Chart/WCartesianChart>
#include <Wt/Chart/WPieChart>


#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>
#include "expr.h"
//#include "tree.h"
#include "debug_mem.h"
#include "stmt.h"
#include "Tab.h"
#include "code_output_files.h"
#include "generate_code.hpp"

std:: string read_file_contents (string file_name_with_path);
extern map <string, Table::ax*> ax_map;
using namespace Wt;
int	compile( char * const XTCC_HOME, char * const work_dir);
int	run(char * data_file_name, int rec_len);
extern char * XTCC_HOME;
extern char * data_file ;
extern int rec_len;
extern char * work_dir;
void loadDataIntoModel (WStandardItemModel * & m, TableData & tbl);


XtccWtUI::XtccWtUI (Wt::WStandardItemModel * & model,
			 Wt::WStandardItemModel * & side_model,
			 Wt::WStandardItemModel * & top_model,
			 std::set<string> & p_side_axes_set,
			 std::set<string> & p_top_axes_set,
			 WObject * parent)

	: 	
		filteredAxes (0), regexpFilter (0), w (0),
		vbl1 (0), hbl (0),
		main_axes_model (model), main_axes_tree (0), 
		side_axes_model (side_model), side_axes_tree (0),
		top_axes_model (top_model), top_axes_tree (0),
		side_axes_set (p_side_axes_set),
		top_axes_set (p_top_axes_set),
		messages_container (0), mesg_cont_layout (0),
		wt_tbl_cont(0), wt_tbl (0)
		
{
	w  = new WContainerWidget (this);
	vbl1 = new WVBoxLayout ();

	WText * txt = new WText("axes name here : regular expressions (example q.*) work");
	regexpFilter = new WLineEdit();
	regexpFilter -> setText(".*");
	regexpFilter -> enterPressed().
		connect(this, &XtccWtUI::changeRegexp);
	WPushButton *filter = new WPushButton ("Apply");
	filter -> clicked().
		connect (this, &XtccWtUI::changeRegexp);

	hbl = new WHBoxLayout ();
	hbl -> addWidget (txt, AlignLeft);
	hbl -> addWidget (regexpFilter, AlignLeft);
	hbl -> addWidget (filter, AlignLeft);
	vbl1 -> addLayout (hbl);

	WPanel *panel1 = new WPanel();
	panel1->resize(150, 300);
	panel1->setCentralWidget(main_axes_tree = new WTreeView());
	main_axes_tree->setSelectionMode (ExtendedSelection);
	main_axes_tree->setAlternatingRowColors (true);
	main_axes_tree->setRowHeight (25);
	main_axes_tree->setModel (main_axes_model);
	/*
	 * Expand the first (and single) top level node
	 */
	main_axes_tree->setExpanded(main_axes_model->index(0, 0), true);



	//main_axes_tree->setExpanded(main_axes_model->index(0, 0, main_axes_model->index(0, 0)), true);
	hbl = new WHBoxLayout ();
	hbl->addWidget (panel1 );
	//
	// now the filtered selection box

	filteredAxes = new WSortFilterProxyModel();
	filteredAxes->setSourceModel(main_axes_model);
	filteredAxes->setDynamicSortFilter(true);
	filteredAxes->setFilterKeyColumn(0);
	filteredAxes->setFilterRole(Wt::DisplayRole);
	filteredAxes->setFilterRegExp(regexpFilter->text());

	selected_axes_view = new WSelectionBox();
	selected_axes_view -> setModel (filteredAxes);
	selected_axes_view -> setVerticalSize (10);
	selected_axes_view -> setSelectionMode (ExtendedSelection);
	hbl -> addWidget (selected_axes_view);

	// ======================
	WContainerWidget * wc = new WContainerWidget(this);
	WVBoxLayout * vbl = new WVBoxLayout (wc);
	WPushButton *b;

	b = new WPushButton("Side =>" );
	b->clicked().connect(this, &XtccWtUI::add_axes);
	b->setToolTip("Add axes to side");
	vbl->addWidget (b);

	b = new WPushButton("<= Side");
	b->clicked().connect(this, &XtccWtUI::remove_axes_from_side);
	b->setToolTip("Remove axes from side");
	vbl->addWidget (b);

	b = new WPushButton("Top =>");
	b->clicked().connect(this, &XtccWtUI::add_axes_to_top);
	b->setToolTip("Add axes to banner");
	vbl->addWidget (b);

	b = new WPushButton("<= Top");
	b->clicked().connect(this, &XtccWtUI::remove_axes_from_top);
	b->setToolTip("Remove axes from banner");
	vbl->addWidget (b);

	b = new WPushButton("Run");
	b->clicked().connect(this, &XtccWtUI::run_tables);
	b->setToolTip("Run the tables");
	vbl->addWidget (b);
	wc->setLayout (vbl, AlignTop);
	hbl->addWidget (wc);
	// ======================


	WPanel *panel2 = new WPanel();
	panel2->resize(150, 300);
	panel2->setCentralWidget(side_axes_tree = new WTreeView());
	side_axes_tree->setModel(side_axes_model);
	side_axes_tree->setSelectionMode (ExtendedSelection);
	hbl->addWidget (panel2);

	WPanel *panel3 = new WPanel();
	panel3->resize(150, 300);
	panel3->setCentralWidget(top_axes_tree = new WTreeView());
	top_axes_tree->setModel(top_axes_model);
	top_axes_tree->setSelectionMode (ExtendedSelection);
	hbl->addWidget (panel3);

	WPanel *panel4 = new WPanel();
	panel4->resize(300, 300);
	panel4->setCentralWidget (messages_container = new WContainerWidget());
	messages_container->setStyleClass("chat-msgs");

	mesg_cont_layout = new WVBoxLayout ();
	messages_container->setLayout (mesg_cont_layout);
	messages_container->setOverflow (WContainerWidget::OverflowAuto);
	hbl->addWidget (panel4);

	if (!WApplication::instance()->environment().ajax()) {
		main_axes_tree->resize (WLength::Auto, 90);
		side_axes_tree->resize (WLength::Auto, 90);
	}
#if 0
#endif /*  0  */
	vbl1->addLayout (hbl);
	//vbl1->addWidget (wt_tbl_cont = new WContainerWidget());
	//wt_tbl_cont ->addWidget (wt_tbl = new WTable(wt_tbl_cont));
	WContainerWidget * tmp1 = new WContainerWidget();
	tmp1->setLayout (vbl1, AlignTop|AlignJustify);
	w->addWidget(tmp1);
	w->addWidget (wt_tbl_cont = new WContainerWidget());
	//wt_tbl_cont ->addWidget (wt_tbl = new WTable(wt_tbl_cont));
	//w->setLayout (vbl1, AlignTop|AlignJustify);
	//wt_tbl_element_count = 0;
}

WStandardItemModel *XtccWtUI::create_main_axes_model(bool useInternalPath
		//, WStandardItemModel * & model
						 , WObject *parent )
{
	WStandardItemModel *model = new WStandardItemModel (0, 1, parent);
	model->setHeaderData (0, Horizontal, std::string("Axes"));
	for (Table::CMAPITER it = ax_map.begin(); it != ax_map.end(); ++it) {
		WStandardItem * data = new WStandardItem(it->first);
		data->setColumnCount(1);
		model -> appendRow (data);
	}
	return model;
}

WStandardItemModel *XtccWtUI::create_side_axes_model(bool useInternalPath ,
						 WObject *parent, string text)
{
	WStandardItemModel *result = new WStandardItemModel(0, 1 , parent);
	result->setHeaderData (0, Horizontal, text);
	return result;
}

void XtccWtUI::toggleRowHeight()
{
  if (main_axes_tree->rowHeight() == WLength(31))
    main_axes_tree->setRowHeight(25);
  else
    main_axes_tree->setRowHeight(31);
}

void XtccWtUI::add_axes()
{
	WModelIndexSet sel_indx = main_axes_tree->selectedIndexes();
	if (sel_indx.begin () != sel_indx.end()) {
		int n_axes = 0;
		for (set<WModelIndex>::iterator it = sel_indx.begin();
				it != sel_indx.end(); ++it) {
			WStandardItem *data = main_axes_model->itemFromIndex(*it);
			std::cout << data->text() << std::endl;
			if (side_axes_set.find( data->text().toUTF8()) == side_axes_set.end()) {
				WStandardItem * data2 = new WStandardItem (data->text());
				side_axes_model -> appendRow ( data2) ;
				side_axes_set.insert (data->text().toUTF8());
			} else {
				std::cout << data->text() << "already exists in side axes" << std::endl;
			}
			++ n_axes;
		}
		std::cout << "selectedIndexes: " << n_axes << std::endl;
	} else {
		set <int> sel_indxs = selected_axes_view->selectedIndexes();
		WAbstractItemModel * abs_model	= selected_axes_view->model();
		//WSortFilterProxyModel * model  = static_cast <WSortFilterProxyModel*> (abs_model);
		for (set <int>::iterator it = sel_indxs.begin(); it != sel_indxs.end(); ++it) {
			if (filteredAxes->hasIndex (*it, 0)) {
				WModelIndex midx = filteredAxes->index (*it, 0);
				WModelIndex midx2 = filteredAxes->mapToSource (midx);
				WStandardItem *data = main_axes_model->itemFromIndex(midx2);
				std::cout << data->text() << std::endl;
				if (side_axes_set.find( data->text().toUTF8()) == side_axes_set.end()) {
					WStandardItem * data2 = new WStandardItem (data->text());
					side_axes_model -> appendRow ( data2) ;
					side_axes_set.insert (data->text().toUTF8());
				} else {
					std::cout << data->text() << "already exists in side axes" << std::endl;
				}
				//boost::any my_data = filteredAxes->data (*it, 0);
				cerr << "reached here" << endl;
				//std::cerr << boost::any_cast<std::string> (my_data) << std::endl;

			} else {
				cerr << "undrlying model does not have index: " << *it << endl;
			}
		}
	}
}

void XtccWtUI::remove_axes_from_side()
{
	WModelIndexSet sel_indx = side_axes_tree->selectedIndexes();
	int n_axes = 0;
	vector <WModelIndex> vec_indxes;
	for (set<WModelIndex>::iterator it = sel_indx.begin();
			it != sel_indx.end(); ++it) {
		WStandardItem *data = side_axes_model -> itemFromIndex(*it);
		std::cout << data->text() << std::endl;
		if (side_axes_set.find (data->text().toUTF8()) != side_axes_set.end()) {
			vec_indxes.push_back (*it);
			side_axes_set.erase (data->text().toUTF8());
		} else {
			std::cout << data->text() << "does not exists in side axes" << std::endl;
		}
		++ n_axes;
	}
	std::cout << "selectedIndexes: " << n_axes << std::endl;
	using namespace std;
	if (vec_indxes.size() > 0) {
		for (int i = vec_indxes.size()-1; i >= 0; --i) {
			cout << "row no to be removed: " << vec_indxes[i].row() << endl;
			side_axes_model->removeRow (vec_indxes[i].row());
		}
	}
}

void XtccWtUI::remove_axes_from_top()
{
	WModelIndexSet sel_indx = top_axes_tree->selectedIndexes();
	int n_axes = 0;
	vector <WModelIndex> vec_indxes;
	for (set<WModelIndex>::iterator it = sel_indx.begin();
			it != sel_indx.end(); ++it) {
		WStandardItem *data = top_axes_model -> itemFromIndex(*it);
		std::cout << data->text() << std::endl;
		if (top_axes_set.find (data->text().toUTF8()) != top_axes_set.end()) {
			vec_indxes.push_back (*it);
			top_axes_set.erase (data->text().toUTF8());
			//WStandardItem * data2 = new WStandardItem (data->text());
			//top_axes_model -> appendRow ( data2) ;
			//top_axes_set.insert (data->text().toUTF8());
		} else {
			std::cout << data->text() << "does not exists in top axes" << std::endl;
		}
		++ n_axes;
	}
	std::cout << "selectedIndexes: " << n_axes << std::endl;
	using namespace std;
	if (vec_indxes.size() > 0) {
		for (int i = vec_indxes.size()-1; i >= 0; --i) {
			cout << "row no to be removed: " << vec_indxes[i].row() << endl;
			top_axes_model->removeRow (vec_indxes[i].row());
		}
	}
}


void XtccWtUI::add_axes_to_top()
{
	WModelIndexSet sel_indx = main_axes_tree->selectedIndexes();
	if (sel_indx.begin () != sel_indx.end()) {
		int n_axes = 0;
		for (set<WModelIndex>::iterator it = sel_indx.begin();
				it != sel_indx.end(); ++it) {
			WStandardItem *data = main_axes_model->itemFromIndex(*it);
			std::cout << data->text() << std::endl;
			if (top_axes_set.find( data->text().toUTF8()) == top_axes_set.end()) {
				WStandardItem * data2 = new WStandardItem (data->text());
				top_axes_model -> appendRow ( data2) ;
				top_axes_set.insert (data->text().toUTF8());
			} else {
				std::cout << data->text() << "already exists in top axes" << std::endl;
			}
			++ n_axes;
		}
		std::cout << "n selected axes: " << n_axes << std::endl;
	} else {
		set <int> sel_indxs = selected_axes_view->selectedIndexes();
		WAbstractItemModel * abs_model	= selected_axes_view->model();
		//WSortFilterProxyModel * model  = static_cast <WSortFilterProxyModel*> (abs_model);
		for (set <int>::iterator it = sel_indxs.begin(); it != sel_indxs.end(); ++it) {
			if (filteredAxes->hasIndex (*it, 0)) {
				WModelIndex midx = filteredAxes->index (*it, 0);
				WModelIndex midx2 = filteredAxes->mapToSource (midx);
				WStandardItem *data = main_axes_model->itemFromIndex(midx2);
				std::cout << data->text() << std::endl;
				if (top_axes_set.find( data->text().toUTF8()) == top_axes_set.end()) {
					WStandardItem * data2 = new WStandardItem (data->text());
					top_axes_model -> appendRow ( data2) ;
					top_axes_set.insert (data->text().toUTF8());
				} else {
					std::cout << data->text() << "already exists in top axes" << std::endl;
				}
				//boost::any my_data = filteredAxes->data (*it, 0);
				cerr << "reached here" << endl;
				//std::cerr << boost::any_cast<std::string> (my_data) << std::endl;

			} else {
				cerr << "undrlying model does not have index: " << *it << endl;
			}
		}
	}
}

void XtccWtUI::toggleStripes()
{
	main_axes_tree->setAlternatingRowColors(!main_axes_tree->alternatingRowColors());
}

void XtccWtUI::toggleRoot()
{
	if (main_axes_tree->rootIndex() == WModelIndex())
		main_axes_tree->setRootIndex(main_axes_model->index(0, 0));
	else
		main_axes_tree->setRootIndex(WModelIndex());
}



void XtccWtUI:: run_tables ()
{
	using std::cout;
	using std::endl;
	using std::cerr;
	cout << "side row count: " << side_axes_model->rowCount()
		<< endl;
	cout << "top row count: " << top_axes_model->rowCount()
		<< endl;
	vector <string> side_axes;
	for (int i=0; i < side_axes_model->rowCount(); ++i) {
		WStandardItem * item = side_axes_model->item (i);
		side_axes.push_back (item->text().toUTF8());
	}
	vector <string> ban_axes;
	for (int i=0; i < top_axes_model->rowCount(); ++i) {
		WStandardItem * item = top_axes_model->item (i);
		ban_axes.push_back (item->text().toUTF8());
	}
	if (side_axes.size() == 0) {
		cout << "No axes in side: \n";
	} else if (ban_axes.size() == 0) {
		cout << "No axes in banner: \n";
	} else {
		cout <<  "Ok to tabulate: \n";
		vector<Table::table*>	table_list;
		for (int i=0; i < side_axes.size(); ++i) {
			for (int j=0; j < ban_axes.size(); ++j) {
				Table::table * tbl = new Table::table (side_axes[i], ban_axes[j], 0);
				table_list.push_back (tbl);
			}
		}
		cout <<  "work_dir: %s\n"  << work_dir << endl;
		string fname = string(work_dir) + string("/my_table.C");
		FILE * table_op = fopen (fname.c_str(), "wb");
		fname = string (work_dir) + string("/my_tab_drv_func.C");
		FILE * tab_drv_func = fopen (fname.c_str(), "wb");	
		fname = string (work_dir) + string("/my_tab_summ.C");
		FILE * tab_summ_func = fopen (fname.c_str(), "wb");	
		if (! (table_op && tab_drv_func && tab_summ_func) ) {
			std::cerr << "Unable to open file for output of table classes" << std::endl;
			exit(1);
		}
		struct tm utc_time_result;
		time_t current_time_in_epoch_secs;
		time (&current_time_in_epoch_secs);

		gmtime_r (&current_time_in_epoch_secs, &utc_time_result); 
		char fname_date_time_buff[100];
		memset (fname_date_time_buff, 0, sizeof(fname_date_time_buff));
		strftime (fname_date_time_buff, sizeof(fname_date_time_buff),
				"tab_UTC_Y-M-D_H-M-S_%Y-%m-%d_%H-%M-%S.csv", &utc_time_result);
		print_table_code (table_op, tab_drv_func, tab_summ_func, table_list, string(fname_date_time_buff));
		fclose (table_op);
		fclose (tab_drv_func);
		fclose (tab_summ_func);
		if (!compile(XTCC_HOME, work_dir)) {
			using namespace std;
			string output = read_file_contents ( "command_output.log");
			cout << "command output" << endl
				<< output 
				<< endl;
			int rval = run (data_file, rec_len);
			cout << "xtcc run complete" << endl;
			// WLabel * info_label = new WLabel (output, messages_container);
			WText * info_label = new WText (output, messages_container);
			info_label->setStyleClass ("chat-msg");
			mesg_cont_layout -> addWidget (info_label);

			//WAnchor * a = new WAnchor(this);
			//a->setRefInternalPath("/hello");
			//   and listen to the corresponding change in internal path
			//WApplication::instance()->internalPathChanged().connect(this, &DocsListWidget::onInternalPathChange);

			ifstream csv_file(fname_date_time_buff);
			vector <TableData> tbl_data_vec;
			if (csv_file) {
				for (int i = 0; i < table_list.size(); ++i) {
					tbl_data_vec.push_back (TableData());
					readFromCsv (csv_file, tbl_data_vec[tbl_data_vec.size()-1]);
					cout << "nRows: " << tbl_data_vec[tbl_data_vec.size()-1].nRows << endl;
					WStandardItemModel * wsm = new WStandardItemModel (tbl_data_vec[i].nRows, tbl_data_vec[i].nCols + 1, w);
					loadDataIntoModel (wsm, tbl_data_vec[i]);
					WTableView * tbl = new WTableView ();
					tbl->setModel (wsm);
					tbl->resize (800, 20 + (tbl_data_vec[i].nRows + 1) * 22 );
					WItemDelegate *delegate = new WItemDelegate(tbl);
					delegate->setTextFormat("%.2f");
					tbl->setItemDelegate(delegate);
					//wt_tbl->elementAt (wt_tbl_element_count++, 0)->addWidget (tbl);
					//wt_tbl->elementAt (wt_tbl_element_count++, 0)->addWidget (tbl);
					WContainerWidget * w1 = new WContainerWidget();
					WText * title = new WText (tbl_data_vec[i].side_ttl);
					w1->addWidget (title);
					w1->addWidget (tbl);
					wt_tbl_cont->addWidget (w1);
					//wt_tbl->elementAt (wt_tbl_element_count++, 0)->addWidget (new WText("dummy"));


					//vbl1->addWidget (tbl, 1);
					cout << "Looping i:" << i << endl;
					using namespace Wt::Chart;
					//Wt::WHBoxLayout * myhbl3 = new WHBoxLayout ();
					//myhbl3->addWidget (tbl, 1);
					//vbl1->addLayout (myhbl3, 1);

					WCartesianChart *chart = new WCartesianChart();
					// chart->setPreferredMethod(WPaintedWidget::PngImage);
					chart->setModel(wsm);        // set the model
					chart->setXSeriesColumn(0);    // set the column that holds the categories
					chart->setLegendEnabled(true); // enable the legend

					// Provide space for the X and Y axis and title. 
					chart->setPlotAreaPadding(80, Left);
					chart->setPlotAreaPadding(40, Top | Bottom);
					//chart->setTitle (tbl_data_vec[i].side_ttl);

					/*
					* Add all (but first) column as bar series
					*/
					for (int i = 1; i < wsm->columnCount(); ++i) {
						WDataSeries s(i, BarSeries);
						s.setShadow(WShadow(3, 3, WColor(0, 0, 0, 127), 3));
						chart->addSeries(s);
					}

					chart->resize(800, 600);
					chart->setMargin(50, Top | Bottom);
					chart->setMargin(WLength::Auto, Left | Right);
					//WPanel * pan = new WPanel();
					//pan->resize (600, 400);
					//pan->setCentralWidget (chart);
					//myhbl->addWidget (chart);
					//vbl1->addWidget (pan, 1);
					//Wt::WHBoxLayout * myhbl1 = new WHBoxLayout ();
					//myhbl1->addWidget (chart, 1);
					//wt_tbl->elementAt (wt_tbl_element_count++, 0)->addWidget (chart);
					WContainerWidget * w2 = new WContainerWidget();
					w2->addWidget (chart);
					wt_tbl_cont->addWidget (w2);
					
					//myhbl->addWidget (new ChartConfig (chart, w));
					//Wt::WHBoxLayout * myhbl2 = new WHBoxLayout ();
					//myhbl2 -> addWidget(new ChartConfig (chart), 1);
					//vbl1->addLayout (myhbl2, 1);
					//vbl1->addLayout (myhbl1, 1);
					//wt_tbl->elementAt (wt_tbl_element_count++, 0)->addWidget (new ChartConfig(chart));
					WContainerWidget * w3 = new WContainerWidget();
					w3->addWidget (new ChartConfig(chart));
					wt_tbl_cont->addWidget (w3);
				}
			}

			Wt::WResource *r = new RestGetHello (fname_date_time_buff); // serializes to a PDF file.
			WAnchor *  a = new WAnchor(r, fname_date_time_buff, messages_container);
			a->setTarget(TargetNewWindow);
			mesg_cont_layout -> addWidget (a);

			//Wt::Http::Response resp;
			//resp.addHeader ("Content-Type", "binary/octet-stream");
			//ostringstream  size_str ;
		}
		for (int i=0; i < table_list.size(); ++i) {
			delete table_list[i];
		}
#if 0
#endif /*  0 */
	}
}

void loadDataIntoModel (WStandardItemModel * & m, TableData & tbl)
{
	for (int i = 0; i < tbl.nCols; ++i) {
		m->setHeaderData (i+1, boost::any (Wt::WString::fromUTF8 (tbl.column_text[i])));
	}
#if 1
	for (int i = 0; i < tbl.nRows-1; ++i) {		
		cout << "setting row text: " <<(Wt::WString::fromUTF8 (tbl.row_text[i])) << endl;
		boost::any data = boost::any (Wt::WString::fromUTF8 (tbl.row_text[i]));
		m->setData (i, 0, data);
		for (int j = 0; j < tbl.nCols ; ++j) {
			boost::any data2 = boost::any (tbl.row_pc[i*tbl.nCols+j]);
			cout << "(" << i << ", " << j << ")"
				<< ": " << (tbl.row_pc[i*tbl.nCols+j]);
			m->setData (i, j+1, data2);
		}
		cout << endl;
	}
#endif /*  0  */
	cout << "EXIT " << __PRETTY_FUNCTION__ << endl;
}
