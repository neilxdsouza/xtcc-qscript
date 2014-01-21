/*
 *
 *         Neil Xavier DSouza
 *
 */

#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

#include "new_simple_merge.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;





SequentialFileIterator::SequentialFileIterator(FILE * fptr, string file_name_pattern)
	: all_files(0), file_name_regex_pattern (file_name_pattern)
{
	if (regcomp(&file_name_regex,
		file_name_pattern.c_str(), REG_EXTENDED | REG_NOSUB)) {
		fprintf (stderr, "Bad regex pattern ... exiting\n");
		exit (WALK_BADPATTERN);
	}
	string cmd = "find . -name \"*.dat\" > find_command_op";
	cout << "executing cmd: " << cmd << endl;

	int ret_val = system (cmd.c_str());
	if (ret_val !=0 ) {
		cout << "Error executing command: " << cmd 
			<< " exiting ... "
			<< endl;
		exit(1);
	}
	all_files = fopen ("find_command_op", "rb");
	if (!all_files) {
		cout << "Failed to open |op| for reading, ... exiting" << endl;
		exit (1);
	}
}


string SequentialFileIterator::get_next_data_file ()
{
	int r_val = 0;
	char buffer[1001];

	while ( (r_val = fscanf (all_files, "%500s\n", buffer)) != EOF) {
		string file_name (buffer);
		cerr << "file_path: " << file_name << endl;

		struct stat st;
		if (lstat(file_name.c_str(), &st) == -1) {
			warn("Can't stat %s", file_name.c_str());
			continue;
		}

		if (S_ISREG(st.st_mode) &&
			(!regexec(&file_name_regex, file_name.c_str(), 0, 0, 0))
				) {
			//cout << "Exit: " << __PRETTY_FUNCTION__ << " file_name:" << file_name << endl;
			//return file_name;
			//cout <<  " regexec match file_name:" << file_name << endl;
			split_name_into_filename_and_dir (file_name);
			
			return file_name;
		}

	}
	return string();
}

#if 0
int main()
{
	string cmd = "find . -name \"*.txt\" > op";
	cout << "executing cmd: " << cmd << endl;

	int ret_val = system (cmd.c_str());
	if (ret_val == 0) {
		FILE * fptr = fopen ("op", "rb");

		//string file_name_pattern = ".*/.*/.*/.*/.*txt$";
		string file_name_pattern = "^[^/]*/[^/]*/[^/]*/[^/]*/[^./]*\.txt$";
		SequentialFileIterator sfi (fptr, file_name_pattern);
		//process_files (fptr, file_name_pattern);
		string s1 = sfi.get_next_data_file();
		while (s1.length()>0) {
			cout << "found: " << s1 << endl;
			s1 = sfi.get_next_data_file();
		}
		//cout << sfi.get_next_data_file() << endl;
		//cout << sfi.get_next_data_file() << endl;
		//cout << sfi.get_next_data_file() << endl;
	}
}
#endif /*  0 */

void SequentialFileIterator::split_name_into_filename_and_dir (const string & file_path)
{
	cout << __PRETTY_FUNCTION__ << endl;
	string::size_type last_slash = file_path.find_last_of('/');
	dir_part = file_path.substr (0, last_slash + 1);
	filename_part = file_path.substr (last_slash + 1, file_path.length() - (last_slash + 1) );
	cerr << "filename_part: " << filename_part << endl;
	cerr << "dir_part: " << dir_part << endl;

}
