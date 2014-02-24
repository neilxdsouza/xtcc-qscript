
package com.qscript.runtime;
import java.util.*;
//import com.qscript.runtime.Pair;
public class named_range_test
{
	public static void main(String[] args)
	{
		named_range a_nr;
		ArrayList <stub_pair> qscript_temp_2023;
		named_range yn;
		qscript_temp_2023 = new ArrayList <stub_pair>();
		qscript_temp_2023.add( new stub_pair("Yes", 1, false, false, ""));
		qscript_temp_2023.add( new stub_pair("No", 2, false, false, ""));
		yn = new named_range();
		yn.set_range_data("yn", qscript_temp_2023);
	}
}
