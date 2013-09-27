/*
 * ======================================================================
 *
 *       Filename:  get_target_pattern_data_file.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 27 September 2013 07:34:07  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * ======================================================================
 */

#ifndef get_target_pattern_data_file_h
#define get_target_pattern_data_file_h

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

struct DataFileIterator {
	regex_t file_name_regex;
	std::string regex_pattern;
	std::string start_directory;

	std::string get_a_potential_data_file();


	std::string get_a_potential_data_file_from_subdir ();
	DataFileIterator (const std::string & file_name_pattern,
			const std::string & start_directory);
	void set_new_subdir (std::string  subdir_name);
	
	struct dirent * root_data_directory_entry;
	struct dirent * current_sub_directory_data_repository_entry;
	DIR * root_dir;
	DIR * current_sub_directory_data_repository;
	std::string current_sub_directory;
};

#endif /* get_target_pattern_data_file_h */ 
