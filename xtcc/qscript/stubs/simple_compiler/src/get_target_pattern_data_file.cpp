/*
 * =====================================================================
 *
 *       Filename:  get_target_pattern_data_file.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 26 September 2013 12:43:34  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <err.h>
#include <string>
#include <cstdlib>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

struct DataFileIterator {
	regex_t file_name_regex;
	string regex_pattern;
	string start_directory;

	string get_a_potential_data_file();


	string get_a_potential_data_file_from_subdir ();
	DataFileIterator (const string & file_name_pattern,
			const string & start_directory);
	void set_new_subdir (string  subdir_name);
	
	struct dirent * root_data_directory_entry;
	struct dirent * current_sub_directory_data_repository_entry;
	DIR * root_dir;
	DIR * current_sub_directory_data_repository;
	string current_sub_directory;
};


enum {
	WALK_OK = 0,
	WALK_BADPATTERN,
	WALK_NAMETOOLONG,
	WALK_BADIO,
};
 
#define WS_NONE		0
#define WS_RECURSIVE	(1 << 0)
#define WS_DEFAULT	WS_RECURSIVE
#define WS_FOLLOWLINK	(1 << 1)	/* follow symlinks */
#define WS_DOTFILES	(1 << 2)	/* per unix convention, .file is hidden */
#define WS_MATCHDIRS	(1 << 3)	/* if pattern is used on dir names too */

DataFileIterator::DataFileIterator
	(const string & file_name_pattern, const string & p_start_directory)
	: regex_pattern (file_name_pattern),
	  start_directory (p_start_directory),
	  root_dir (0),
	  current_sub_directory_data_repository_entry(0),
	  current_sub_directory_data_repository(0),
	  current_sub_directory()
{
	if (regcomp(&file_name_regex,
		regex_pattern.c_str(), REG_EXTENDED | REG_NOSUB)) {
		fprintf (stderr, "Bad regex pattern ... exiting\n");
		exit (WALK_BADPATTERN);
	}
 
	if (!(root_dir = opendir(start_directory.c_str()))) {
		warn("can't open root dir %s, ... exiting\n",
				start_directory.c_str());
		exit (WALK_BADIO);
	}
}

string DataFileIterator::get_a_potential_data_file_from_subdir ()
{
	cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
	while (current_sub_directory_data_repository_entry = readdir (current_sub_directory_data_repository)) {
		if (current_sub_directory_data_repository_entry->d_name[0] == '.') {
			cout << "skipping leading '.' file" << endl;
			continue;
		}
		if (!strcmp(current_sub_directory_data_repository_entry->d_name, ".")
			|| !strcmp(current_sub_directory_data_repository_entry->d_name, "..")) {
			cout << "skipping dirs '.' or '..' " << endl;
			continue;
		}
		
		string file_name = current_sub_directory + current_sub_directory_data_repository_entry->d_name;
		struct stat st;
		if (lstat(file_name.c_str(), &st) == -1) {
			warn("Can't stat %s", file_name.c_str());
			continue;
		}
		if (S_ISREG(st.st_mode) &&
			(!regexec(&file_name_regex, file_name.c_str(), 0, 0, 0))
				) {
			//cout << "Exit: " << __PRETTY_FUNCTION__ << " file_name:" << file_name << endl;
			return file_name;
		}
	}

	//cout << "Exit: " << __PRETTY_FUNCTION__ << endl;
	return string();
}

void DataFileIterator::set_new_subdir (string  subdir_name)
{
	//cout << "Enter: " << __PRETTY_FUNCTION__
	//	<< "subdir_name: " << subdir_name
	//	<< endl;
	if ( //(current_sub_directory.length() == 0) &&
		! (current_sub_directory_data_repository = opendir (subdir_name.c_str())) ) {
		warn("can't open subdir  %s ... exiting", subdir_name.c_str());
		exit(1);
	} 
	current_sub_directory = subdir_name + "/";
	
	//cout << "Exit: " << __PRETTY_FUNCTION__
	//	<< " current_sub_directory : " << current_sub_directory
	//	<< endl;
}

string DataFileIterator::get_a_potential_data_file()
{
	//cout << "Enter: " << __PRETTY_FUNCTION__ << endl;
	if (current_sub_directory.length() > 0) {
		string potential_file =  get_a_potential_data_file_from_subdir ();
		if (potential_file.length() > 0) {
			return potential_file;
		}
	}
	while (root_data_directory_entry = readdir (root_dir) ) {
		if (root_data_directory_entry->d_name[0] == '.') {
			cout << "skipping leading '.' file" << endl;
			continue;
		}
		if (!strcmp(root_data_directory_entry->d_name, ".")
			|| !strcmp(root_data_directory_entry->d_name, "..")) {
			cout << "skipping dirs '.' or '..' " << endl;
			continue;
		}
		string file_name = start_directory + string("/")
				+ string(root_data_directory_entry->d_name);
		//cout << "file_name: " << file_name << endl;
		
		struct stat st;
		if (lstat(file_name.c_str(), &st) == -1) {
			warn("Can't stat %s", file_name.c_str());
			continue;
		}

		if (S_ISDIR(st.st_mode)) {
			//return get_a_potential_data_file_from_subdir (file_name);
			set_new_subdir (file_name);
			cout << "set_new_subdir: " << file_name << endl;
			string potential_file = get_a_potential_data_file_from_subdir ();
			if (potential_file.length() > 0) {
				cout << "Enter: " << __PRETTY_FUNCTION__
					<< ":potential_file: " << potential_file << endl;
				return potential_file;
			}
		}
	}
	cout << "Enter: " << __PRETTY_FUNCTION__
		<< ":potential_file: empty()" << endl;
	return string();
}

/* 
int main()
{
	DataFileIterator data_file_iterator (".\\.dat$", ".");

	string potential_file;
	do {
		potential_file = data_file_iterator.get_a_potential_data_file();
		cout << "potential_file : " << potential_file << endl;
	} while (potential_file.length() > 0) ;
	//cout << "data_file_iterator.get_a_potential_data_file (): "
	//	<< data_file_iterator.get_a_potential_data_file ()
	//	<< endl;

	//cout << "data_file_iterator.get_a_potential_data_file (): "
	//	<< data_file_iterator.get_a_potential_data_file ()
	//	<< endl;
}
 */
