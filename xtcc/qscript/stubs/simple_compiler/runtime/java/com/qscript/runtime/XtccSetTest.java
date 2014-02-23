package com.qscript.runtime;

import com.qscript.runtime.Pair;
import com.qscript.runtime.XtccSet;

import java.io.*;
import java.util.*;

public class XtccSetTest {

	public static void main (String[] args)
	{
		XtccSet s1 = new XtccSet();
		s1.add_indiv (1);
		s1.add_range (11,20);
		if (s1.exists(1) ) {
			System.out.println("s1 contains 1");
		} else {
			System.out.println("s1 does not contain 1");
		}
		if (s1.exists(2) ) {
			System.out.println("s1 contains 2");
		} else {
			System.out.println("s1 does not contain 2");
		}
		if (s1.exists(13) ) {
			System.out.println("s1 contains 13");
		} else {
			System.out.println("s1 does not contain 13");
		}
		{
			Set<Integer> s2 = new TreeSet<Integer>();
			s2.add(1);
			s2.add(14);
			s2.add(16);
			if (s1.contains_subset (s2)) {
				System.out.println("s1 contains s1= 1,14,16");
			} else {
				System.out.println("s1 does not contains 1,14,16");
			}
		}
		{
			Set<Integer> s2 = new TreeSet<Integer>();
			s2.add(1);
			s2.add(9);
			s2.add(16);
			if (s1.contains_subset (s2)) {
				System.out.println("s1 contains s1= 1,9,16");
			} else {
				System.out.println("s1 does not contains 1,9,16");
			}
		}

	}
}
