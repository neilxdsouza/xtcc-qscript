/*
 * =====================================================================================
 *
 *       Filename:  new_named_range.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Friday 30 September 2011 09:55:22  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Neil Xavier D'Souza
 *
 * =====================================================================================
 */

#include <algorithm>
#include <functional>
#include "new_named_range-v2.h"

//ptrdiff_t (*p_myrandom)(ptrdiff_t) = myrandom;
//ptrdiff_t myrandom (ptrdiff_t i)
//{
//	int random_seed = time (0);
//	return rand()%i;
//}

/*
struct MyRNG
{
	int random_seed;
	MyRNG(): 	random_seed (time(0))
	{ }
	int MyRNG(ptrdiff_t i)
	{
		return rand_r(&random_seed) % i;
	}
};
*/

void NamedRangeGroup::AddStub (string p_text, int p_code, int p_index_in_group)
{
	if (groupPtr_) {
		AbstractNamedRange * ptr_AbstractNamedRange = groupPtr_;
		while (ptr_AbstractNamedRange->next_nr) {
			ptr_AbstractNamedRange = ptr_AbstractNamedRange->next_nr;
		}
		if (NamedRangeGroup * ng = dynamic_cast<NamedRangeGroup*> (ptr_AbstractNamedRange)) {
			NamedRangeList * nl = new NamedRangeList();
			struct stub_pair pair1 (p_text, p_code, true, p_index_in_group);
			nl->stubs.push_back (pair1);
			ptr_AbstractNamedRange->next_nr  = nl;
			cout << "adding stub: " << p_text << " to group: " << groupName_ << endl;
		} else if (NamedRangeList * nl = dynamic_cast<NamedRangeList*> (ptr_AbstractNamedRange)) {
			struct stub_pair pair1 (p_text, p_code, true, p_index_in_group);
			nl->stubs.push_back (pair1);
			cout << "adding stub: " << p_text << " to group: " << groupName_ << endl;
		}
	} else {
		NamedRangeList * nl = new NamedRangeList();
		struct stub_pair pair1 (p_text, p_code, true, p_index_in_group);
		nl->stubs.push_back (pair1);
		//next_nr  = nl;
		groupPtr_ = nl;
		cout << "adding stub: " << p_text << " to group: " << groupName_ << endl;
	}
}

void NamedRangeGroup::AddGroup (NamedRangeGroup & p_group, int p_index_in_group)
{
	cout << __PRETTY_FUNCTION__ << "groupName_: "
		<< groupName_
		<< ", p_group: "
		<< p_group.groupName_
		<< endl;
	if (next_nr== 0 && groupPtr_==0) {
		//groupPtr_ = & p_group;
		NamedRangeGroup * nrg = new NamedRangeGroup (p_group.groupName_, p_index_in_group);
		nrg->groupPtr_ = p_group.groupPtr_;
		//groupPtr_ = p_group.groupPtr_;
		groupPtr_ = nrg;
		//groupName_ = p_group.groupName_;
		//groupPtr_ = p_group.groupPtr_;
	} else {
		AbstractNamedRange * ptr_AbstractNamedRange = groupPtr_;
		while (ptr_AbstractNamedRange->next_nr) {
			ptr_AbstractNamedRange = ptr_AbstractNamedRange->next_nr;
		}
		//ptr_AbstractNamedRange->next_nr = & p_group;
		NamedRangeGroup * nrg = new NamedRangeGroup (p_group.groupName_, p_index_in_group);
		nrg->groupPtr_ = p_group.groupPtr_;
		ptr_AbstractNamedRange->next_nr = nrg;
	}
}

void NamedRangeList::AddStub (string p_text, int p_code, int p_index_in_group)
{
	cout << "Enter: " << __FILE__ << ", " << __PRETTY_FUNCTION__ << endl;
	if (next_nr) {
		AbstractNamedRange * ptr_AbstractNamedRange = next_nr;
		while (ptr_AbstractNamedRange->next_nr) {
			ptr_AbstractNamedRange = ptr_AbstractNamedRange->next_nr;
		}
		if (NamedRangeGroup * ng = dynamic_cast<NamedRangeGroup*> (next_nr)) {
			NamedRangeList * nl = new NamedRangeList();
			struct stub_pair pair1 (p_text, p_code, true, p_index_in_group);
			nl->stubs.push_back (pair1);
			ptr_AbstractNamedRange->next_nr = nl;
		} else {
			cerr << "unhandled case: " << __FILE__ << ", "
				<< __LINE__ << ", "
				<< __PRETTY_FUNCTION__
				<< endl;
			exit(1);
		}
	} else {
		struct stub_pair pair1 (p_text, p_code, true, p_index_in_group);
		stubs.push_back (pair1);
	}
	cout << "Exit: " << __FILE__ << ", " << __PRETTY_FUNCTION__ << endl;
}

void NamedRangeList::AddGroup (NamedRangeGroup & p_group, int p_index_in_group)
{
	cout << __PRETTY_FUNCTION__ << endl;
	if (next_nr == NULL) {
		next_nr = & p_group;
	} else {
		AbstractNamedRange * ptr_AbstractNamedRange = next_nr;
		while (ptr_AbstractNamedRange->next_nr) {
			ptr_AbstractNamedRange = ptr_AbstractNamedRange->next_nr;
		}
		ptr_AbstractNamedRange->next_nr = & p_group;
	}
}


void NamedRangeList::Vectorize (AbstractNamedRange * invoker, vector <AbstractNamedRange*> & p_stub_grp_vec)
{
	for (int i=0; i<stubs.size(); ++i) {
		p_stub_grp_vec.push_back (new NamedRangeStub (stubs[i].stub_text, stubs[i].code));
	}
	if (next_nr) {
		next_nr -> Vectorize (invoker, p_stub_grp_vec);
	}
}


void NamedRangeGroup::Vectorize (AbstractNamedRange * invoker, vector <AbstractNamedRange*> & p_stub_grp_vec)
{
	if (this != invoker)
		p_stub_grp_vec.push_back (this);
	if (groupPtr_) {
		groupPtr_->Vectorize (invoker, stub_grp_vec);
		//p_stub_grp_vec.push_back (groupPtr_);
	}
	if (next_nr) {
		next_nr->Vectorize (invoker, p_stub_grp_vec);
	}
}

// Warning : this function should only be called
// after calling Vectorize on the group
void NamedRangeGroup::Randomize()
{
	randomized_order.resize (stub_grp_vec.size());
	for (int i=0; i < randomized_order.size(); ++i) {
		randomized_order[i] = i;
		NamedRangeGroup * nrg = dynamic_cast<NamedRangeGroup*> (stub_grp_vec[i]);
		if (nrg) {
			nrg->Randomize();
		}
	}

	MyRNG my_rng;
	random_shuffle ( randomized_order.begin(), randomized_order.end(), my_rng);
}


int MyRNG::operator () (ptrdiff_t i)
{
	return rand_r(&random_seed) % i;
}


void NamedRangeGroup::SaveRandomizedOrderToDisk(int nest_level)
{
	//printf("%*d|", nest_level, nest_level);
	printf("%*c", nest_level, ' ');
	if (nest_level == 1) {
		cout << groupName_ << "| 0 -> 0" << endl;
	}
	cout << "{ " << groupName_ << ": " << endl;
	printf("%*c", nest_level, ' ');
	bool last_item_was_nrg = true; // I am the last Item and I am an NRG
	//{ grp_2: { grp_23:  2 0 1; }  { grp_21:  1 0; }  { grp_22:  1 0; }   }   }
	// other wise the output would be like this
	//{ grp_2: ; { grp_23:  2 0 1; }  { grp_21:  1 0; }  { grp_22:  1 0; }   }   }
	//         ^
	//         | ---- this is wrong
	for (int i=0; i<randomized_order.size(); ++i) {
		NamedRangeGroup * nrg = dynamic_cast<NamedRangeGroup*> (stub_grp_vec[randomized_order[i]]);
		if (nrg) {
			if (last_item_was_nrg) {
				cout << endl;
			} else {
				cout << ";  " << endl;
			}
			printf("%*c", nest_level, ' ');
			cout <<  nrg->groupName_ << "|"
				<< " " << randomized_order[i]
				<< " -> "
				<< i << endl;
			nrg->SaveRandomizedOrderToDisk(nest_level+1);
			last_item_was_nrg = true;
		} else {
			NamedRangeStub * nr = dynamic_cast<NamedRangeStub*> (stub_grp_vec[randomized_order[i]]);
			if (nr) {
				cout << nr->stub.stub_text << ":"
					<< nr->stub.code << "| "
					<< " " << randomized_order[i]
					<< " ->";
				cout
					<< i
					<< endl;
				printf("%*c", nest_level, ' ');
			} else {
				cout	<< endl;
				printf("%*c", nest_level, ' ');
				cout
					<< " " << randomized_order[i]
					<< endl;
			}
			last_item_was_nrg = false;
		}
	}
	if (last_item_was_nrg) {
		printf("%*c", nest_level, ' ');
		cout << "}  " << endl;
	} else {
		cout << "; }  " << endl;
	}
}

void NamedRangeList::GenerateCode(StatementCompiledCode & code)
{
}

void NamedRangeGroup::GenerateCode(StatementCompiledCode & code)
{
	vector <string> group_str;
	vector <string> group_list;
	stringstream final_answer;
	vector<stub_pair> flat_display_nr;

	PrintNamedRange (this, group_str, group_list, final_answer, flat_display_nr);
	code.program_code << final_answer.str();
}

void NamedRangeStub::GenerateCode(StatementCompiledCode & code)
{

}


string NamedRangeGroup::SaveFlatRandomizedOrderToDisk (int nest_level)
{
	stringstream randomized_order_str;
	randomized_order_str
			<< "randomized_order "
			<< groupName_
			<< ":";
	randomized_order_str << " size " << flat_display_nr_after_rnd.size()
		<< " : ";
	for (int i=0; i<flat_display_nr_after_rnd.size(); ++i) {
		//randomized_order_str << " " << flat_display_nr_after_rnd[i].code;
		if (i > 0) {
			randomized_order_str << ", ";
		}
		for (int j=0; j < flat_display_nr_normal_order.size(); ++j) {
			if (flat_display_nr_after_rnd[i].code == flat_display_nr_normal_order[j].code) {
				randomized_order_str << j << " -> " << i;
			}
		}
	}
	//for (int i = 0; i < randomized_order.size(); ++i) {
	//	randomized_order_str << " " << randomized_order[i];
	//}
	randomized_order_str << endl;
	return randomized_order_str.str();
}
