CC = $(CXX) 
CPP_SOURCES = ax_q1.cpp ax_q2.cpp ax_q3.cpp ax_q4.cpp ax_q5_0.cpp ax_q5_1.cpp ax_q5_2.cpp ax_q5_3.cpp ax_q6_0.cpp ax_q6_1.cpp ax_q6_2.cpp ax_q6_3.cpp ax_q6_4.cpp ax_tot_ax.cpp 
OBJECTS := $(CPP_SOURCES:.cpp=.o)

my_edit.exe: $($CPP_SOURCES) $(OBJECTS)
	echo "dummy my_edit.exe target for now"

%.o: %.cpp %.h
	$(CC) -c $(CFLAGS) $<

%.dep : %.cpp
	@set -e; rm -f $@; \
		$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ :,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$


