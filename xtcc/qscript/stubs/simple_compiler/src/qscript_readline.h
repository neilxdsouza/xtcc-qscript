#ifndef QSCRIPT_READLINE_H
#define QSCRIPT_READLINE_H
#include <curses.h>
#include <string>

class NCursesReadline
{
	const int MAX_BUFF;
	char * buffer_;
	int insertionPoint_, lastBufPointer_;
	WINDOW * dataEntryWindow_;
	public:
	// We expect an already allocated window to be passed to us
	NCursesReadline(WINDOW * l_data_entry_window);
	char * ReadLine();
	int SetBuffer(const std::string & re_arranged_buffer, int l_new_insertionPoint);
	void Reset();
};


void read_data( const char * prompt);
void read_data_from_window(WINDOW * data_entry_window, const char * prompt
	, bool clear_buffer_flag, std::string & re_arranged_buffer, int & pos_1st_invalid_data);
/*
char * qscript_readline(WINDOW * data_entry_window, const char * prompt
	, bool clear_buffer_flag, std::string & re_arranged_buffer, int & pos_1st_invalid_data);
*/
#endif /* QSCRIPT_READLINE_H */
