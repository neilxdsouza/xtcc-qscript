#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>

#include "new_named_range-v2.h"
#include "utils.h"
int main()
{
NamedRangeGroup leafy("leafy",1);
leafy.AddStub( "Cabbage", 101, 1);
leafy.AddStub( "Lettuce", 102, 2);
leafy.AddStub( "Rocket", 103, 3);

NamedRangeGroup potato_family("potato_family",8);
potato_family.AddStub( "Potato", 401, 1);
potato_family.AddStub( "Sweet Potato", 402, 2);
potato_family.AddStub( "Yam/Arbi", 403, 3);

NamedRangeGroup cauli_flower_like("cauli_flower_like",9);
cauli_flower_like.AddStub( "Cauli-Flower", 201, 1);
cauli_flower_like.AddStub( "Broccoli", 202, 2);

NamedRangeGroup roots("roots",12);
roots.AddStub( "carrot", 501, 1);
roots.AddStub( "radish", 502, 2);
roots.AddStub( "turnip", 503, 3);

NamedRangeGroup top_lev_group("top_lev_group",12);
top_lev_group.AddGroup(leafy,leafy.index_in_group);
top_lev_group.AddStub( "Tomato", 301, 2);
top_lev_group.AddStub( "Green Peas", 302, 3);
top_lev_group.AddStub( "Okra", 303, 4);
top_lev_group.AddStub( "Arti-chokes", 305, 5);
top_lev_group.AddStub( "Pumpkin", 306, 6);
top_lev_group.AddStub( "Butternut Squash", 307, 7);
top_lev_group.AddGroup(potato_family,potato_family.index_in_group);
top_lev_group.AddGroup(cauli_flower_like,cauli_flower_like.index_in_group);
top_lev_group.AddStub( "Egg plant", 304, 10);
top_lev_group.AddStub( "Snow Peas", 308, 11);
top_lev_group.AddGroup(roots,roots.index_in_group);


top_lev_group.Vectorize(&top_lev_group, top_lev_group.stub_grp_vec);
top_lev_group.VectorizePrintNormalOrder(&top_lev_group,1);
top_lev_group.Randomize();
vector<stub_pair> flat_display_nr_after_rnd;
//top_lev_group.VectorizePrint(1, &top_lev_group, flat_display_nr_after_rnd);
top_lev_group.VectorizePrint(1, &top_lev_group, top_lev_group.flat_display_nr_after_rnd);
display_flat_named_range ("flat_display_nr_after_rnd", top_lev_group.flat_display_nr_after_rnd);
std::string the_random_stubs_order = top_lev_group.SaveFlatRandomizedOrderToDisk (1);
display_flat_named_range ("flat_display_nr_normal_order", top_lev_group.flat_display_nr_normal_order);
cout << "randomized_order: " << the_random_stubs_order << endl;
cout << "Enter: a serial no: " << endl;
int ser_no;
cin >> ser_no;
	stringstream fname_str;
	fname_str << "randomized_data_" << ser_no;
	FILE * randomized_data_fptr = fopen (fname_str.str().c_str(), "w");
	fprintf (randomized_data_fptr, "%s", the_random_stubs_order.c_str());
	fclose (randomized_data_fptr);

}
