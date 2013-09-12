/*
 * =====================================================================================
 *
 *       Filename:  split_defn_into_decl_plus_constructor.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Wednesday 11 September 2013 11:26:57  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */


#include <string>
#include <iostream>

using namespace std;

void split_defn_into_decl_plus_constructor (/* const string & defn, vector & <string> decl, vector<string> & constructor_init */)
{
	string test(" struct axis_q5_0 ax_q5_1(q5_1_data, q5_1_ttl_stmt_arr);");

	int pos_left_paren = test.find ("(");
	string decl = test.substr(0, pos_left_paren);
	cout << "decl: " << decl << endl;
	int pos_2nd_space = test.rfind (' ', pos_left_paren);
	string constructor_initializer = test.substr (pos_2nd_space, (test.length() - pos_2nd_space - 1)); 
	cout << "constructor_initializer: " << constructor_initializer << endl;

}

int main()
{
	split_defn_into_decl_plus_constructor();
}

