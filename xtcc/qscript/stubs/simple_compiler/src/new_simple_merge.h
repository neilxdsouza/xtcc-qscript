/*
 *         Neil Xavier DSouza
 */

#ifndef new_simple_merge_h
#define new_simple_merge_h

#include <string>
#include <cstdio>
#include <regex.h>

enum {
	WALK_OK = 0,
	WALK_BADPATTERN,
	WALK_NAMETOOLONG,
	WALK_BADIO,
};



struct SequentialFileIterator {
	FILE * all_files;
	std::string file_name_regex_pattern;
	regex_t file_name_regex;
	std::string filename_part;
	std::string dir_part;

	SequentialFileIterator (FILE * fptr, std::string file_name_pattern);
	std::string get_next_data_file ();
	void split_name_into_filename_and_dir(const std::string & file_path);
};


#endif /*  new_simple_merge_h */
