#this makefile tries to build the program to use the new
#way to read data from the disk

vegetable-new.exe: get_target_pattern_data_file.cpp get_target_pattern_data_file.h vegetable-mod.C
	g++ -I$(QSCRIPT_HOME)/include -L$(QSCRIPT_HOME)/lib vegetable-mod.C get_target_pattern_data_file.cpp -lqscript_runtime  -lncurses -lpanel 
