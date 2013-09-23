/*
 *  Copyright (C) 2011 Neil Xavier D'Souza
 */

#ifndef xtcc_named_range_h
#define xtcc_named_range_h
#include <sys/types.h>
//#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "stub_pair.h"
//#include "stmt.h"
#include "AbstractStatement.h"

using namespace std;
struct NamedRangeList;
struct NamedRangeGroup;
struct NamedRangeStub;

struct MyRNG
{
	unsigned int random_seed;
	MyRNG() : random_seed (time(0))
	{ }
	int operator () (ptrdiff_t i);

};

struct AbstractNamedRange: public AbstractStatement
{
	struct AbstractNamedRange *next_nr, *prev_nr;
	AbstractNamedRange():
		AbstractStatement (NAMED_RANGE, 0),
		next_nr(0), prev_nr(0)
	{ }
	virtual void GenerateCode(StatementCompiledCode & code) = 0;
	//{ }
	virtual void Print (int nest_level)=0;
	virtual void SimplePrint (int nest_level)=0;
	virtual void AddStub (string p_text, int p_code, int p_index_in_group)=0;
	virtual void AddGroup (NamedRangeGroup & p_group, int p_index_in_group)=0;
	virtual void Vectorize (AbstractNamedRange * invoker, vector <AbstractNamedRange*> & p_stub_grp_vec) = 0;
	virtual void VectorizePrint (int nest_level, AbstractNamedRange * invoker,
			vector<stub_pair> & flat_display_nr_after_rnd) = 0;
	virtual void TransferRandomizationOrder(vector<int> & p_randomized_order) = 0;
};


struct NamedRangeList: public AbstractNamedRange
{
	std::vector <stub_pair> stubs;
	NamedRangeList():
		AbstractNamedRange()
	{ }
	void Print(int nest_level) {
		for (int i=0; i<stubs.size(); ++i) {
			printf("%*d|", nest_level, nest_level);
			cout << stubs[i].stub_text << ", " << stubs[i].code
				<< ", index_in_group: " << stubs[i].index_in_group
				<< endl;
		}
		if (next_nr) {
			next_nr->Print(nest_level+1);
		}
	}

	void TransferRandomizationOrder(vector<int> & p_randomized_order)
	{
		cout << "ENTER: " << __PRETTY_FUNCTION__ << endl;
		for (int i=0; i<stubs.size(); ++i) {
			cout << stubs[i].stub_text << ", " << stubs[i].code
				<< ", index_in_group: " << stubs[i].index_in_group
				<< endl;
			p_randomized_order.push_back(stubs[i].code);
		}
		if (next_nr) {
			next_nr->TransferRandomizationOrder(p_randomized_order);
		}
		cout << "EXIT: " << __PRETTY_FUNCTION__ << endl;
	}

	//void Vectorize (vector <AbstractNamedRange*> & p_stub_grp_vec);
	void Vectorize (AbstractNamedRange * invoker, vector <AbstractNamedRange*> & p_stub_grp_vec) ;

	void AddStub (string p_text, int p_code, int p_index_in_group);
	void AddGroup (NamedRangeGroup & p_group, int p_index_in_group);
	void SimplePrint(int nest_level)
	{
		for (int i=0; i<stubs.size(); ++i) {
			cout << stubs[i].stub_text << ", " << stubs[i].code
				<< ", index_in_group: " << stubs[i].index_in_group
				<< endl;
		}
		if (next_nr) {
			next_nr->SimplePrint(nest_level+1);
		}
	}
	void VectorizePrint (int nest_level, AbstractNamedRange * invoker,
			vector<stub_pair> & flat_display_nr_after_rnd)
	{
		cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
		for (int i=0; i<stubs.size(); ++i) {
			printf("%*d|", nest_level, nest_level);
			cout << stubs[i].stub_text << ", " << stubs[i].code
				<< ", index_in_group: " << stubs[i].index_in_group
				<< endl;
		}
		cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
	}
	void GenerateCode(StatementCompiledCode & code);

};

struct NamedRangeGroup: public AbstractNamedRange
{
	string groupName_;
	AbstractNamedRange * groupPtr_;
	vector <AbstractNamedRange *> stub_grp_vec;
	vector <int> randomized_order;
	vector <stub_pair> flat_display_nr_after_rnd;
	vector <stub_pair> flat_display_nr_normal_order;
	int index_in_group;
	NamedRangeGroup(string p_groupName, int p_index_in_group):
		AbstractNamedRange(),
		groupName_(p_groupName), groupPtr_(0),
		index_in_group (p_index_in_group)
	{ }
	void Print(int nest_level) {
		printf("%*d|", nest_level, nest_level);
		cout << groupName_
			<< ", index_in_group: " << index_in_group
			<< endl;
		if (groupPtr_) {
			groupPtr_->Print(nest_level+1);
		}
		cout << "======" << endl;
		if (next_nr) {
			next_nr->Print(nest_level+1);
		}
	}

	void TransferRandomizationOrder(vector<int> & p_randomized_order)
	{
		cout << "ENTER: " << __PRETTY_FUNCTION__ << endl;
		if (groupPtr_) {
			groupPtr_->TransferRandomizationOrder(p_randomized_order);
		}
		cout << "======" << endl;
		if (next_nr) {
			next_nr->TransferRandomizationOrder(p_randomized_order);
		}
		cout << "EXIT: " << __PRETTY_FUNCTION__ << endl;
	}

	void SimplePrint(int nest_level)
	{
		cout << groupName_ << endl;
		if (next_nr) {
			next_nr->SimplePrint(nest_level+1);
		}
	}
	void AddStub (string p_text, int p_code, int p_index_in_group);
	void AddGroup (NamedRangeGroup & p_group, int p_index_in_group);

	//void Vectorize (vector <AbstractNamedRange*> & p_stub_grp_vec);
	void Vectorize (AbstractNamedRange * invoker, vector <AbstractNamedRange*> & p_stub_grp_vec) ;
	void VectorizePrintNormalOrder (AbstractNamedRange * invoker, int nest_level)
	{
		for (int i=0; i < stub_grp_vec.size(); ++i) {
			stub_grp_vec[i]->VectorizePrint(nest_level+1,invoker, flat_display_nr_normal_order);
		}
	}

	void VectorizePrint (int nest_level, AbstractNamedRange * invoker,
			vector<stub_pair> & flat_display_nr_after_rnd)
	{
		cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
		printf("%*d|", nest_level, nest_level);
		cout << groupName_ ;
		cout << ", stub_grp_vec.size(): " << stub_grp_vec.size() << endl;
		//if (invoker == this) {
			if (randomized_order.size() == 0) {
				for (int i=0; i < stub_grp_vec.size(); ++i) {
					stub_grp_vec[i]->VectorizePrint(nest_level+1,invoker, flat_display_nr_after_rnd);
				}
			} else {
				for (int i=0; i < randomized_order.size(); ++i) {
					stub_grp_vec[randomized_order[i]]->VectorizePrint(nest_level+1, invoker, flat_display_nr_after_rnd);
				}
				//flat_display_nr_after_rnd.push_back
				//	(stub_pair (string("Group:") + groupName_,
				//		    flat_display_nr_after_rnd.size()));
			}
		//}
		cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
	}
	// Warning : this function should only be called
	// after calling Vectorize on the group
	void Randomize();
	void SaveRandomizedOrderToDisk(int nest_level);
	void GenerateCode(StatementCompiledCode & code);
	string SaveFlatRandomizedOrderToDisk (int nest_level);

};

struct NamedRangeStub : public AbstractNamedRange
{
	stub_pair stub;
	void Print(int nest_level)
	{
		printf("%*d|", nest_level, nest_level);
		cout << stub.code << ": " <<  stub.stub_text << endl;
	}
	void SimplePrint (int nest_level)
	{
		Print(nest_level+1);
	}
	void AddStub(string p_text, int p_code, int p_index_in_group)
	{
		stub.stub_text = p_text;
		stub.code = p_code;
	}
	NamedRangeStub (string p_text, int p_code):
		stub(p_text, p_code)
	{}
	void AddGroup (NamedRangeGroup & p_group, int p_index_in_group)
	{
	}
	void Vectorize (AbstractNamedRange * invoker, vector <AbstractNamedRange*> & p_stub_grp_vec)
	{
	}
	void VectorizePrint (int nest_level, AbstractNamedRange * invoker,
			vector<stub_pair> & flat_display_nr_after_rnd)
	{
		//cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
		Print(nest_level+1);
		flat_display_nr_after_rnd.push_back (stub_pair(stub.stub_text, stub.code));
		//cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
	}
	void TransferRandomizationOrder(vector<int> & p_randomized_order)
	{

	}
	void GenerateCode(StatementCompiledCode & code);

};

void PrintNamedRange (AbstractNamedRange * nr, vector <string> & group_str,
	vector <string> & group_list, stringstream & final_answer,
	vector<stub_pair> & flat_display_nr
	);

void PrintNamedRange2 (AbstractNamedRange * nr, vector <string> & group_str,
	vector <NamedRangeGroup*> & group_list, stringstream & final_answer,
	vector<stub_pair> & flat_display_nr
	);

#endif /* xtcc_named_range_h */
