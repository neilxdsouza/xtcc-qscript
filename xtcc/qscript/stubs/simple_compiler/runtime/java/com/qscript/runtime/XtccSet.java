package com.qscript.runtime;

import com.qscript.runtime.Pair;

import java.util.*;

public class XtccSet {
	ArrayList <Pair <Integer, Integer> > range;
	Set <Integer> indiv;

	XtccSet()
	{
		indiv = new TreeSet<Integer>();
		range = new ArrayList<Pair <Integer, Integer> >();
	}
	//XtccSet(DataType dt, std::string name, XtccSet& xs1);
	XtccSet(final XtccSet xs1)
	{
		indiv = xs1.indiv;
		range = xs1.range;
	}
	//XtccSet& operator=(final XtccSet& xs1);

	void reset() {
		range.clear();
		indiv.clear();
	}
	void add_range(Integer n1, Integer n2)
	{
		//using std::endl;
		//using std::stringstream;
		//using std::cerr;
		//cerr << "XtccSet::add_range: n1=" << n1 << ", n2=" << n2 << endl;
		//cerr << "range.size(): " << range.size() << endl;

		//for(set<int>::iterator it = indiv.begin(); it != indiv.end(); ++it)
		//for(Set<Integer>::iterator it = indiv.begin(); it != indiv.end(); ++it){
		//	int v = *it;
		//	if(v >= n1 && v <= n2){
		//		//stringstream err_msg;
		//		//err_msg << "range given: " << n1 << " - " << n2
		//		//	<< " makes the individual entry: "  << v << " redundant";
		//		//print_err(compiler_sem_err, err_msg.str().c_str()
		//		//		, qscript_parser::line_no
		//		//		, __LINE__, __FILE__);
		//	}
		//}
		Iterator<Integer> iter = indiv.iterator();
		while (iter.hasNext()) {
			Integer v = iter.next();
			if (v >= n1 && v <= n2) {
			}
		}

		if (range.size() == 0) {
			//cerr << "range.size()==0 pushing back: "  << n1 << "-" << n2 << endl;
			Pair <Integer, Integer> p1 = new Pair <Integer, Integer> (n1, n2);
			range.add(p1);
			//range.push_back(pair<int,int>(n1, n2));
			return;
		}

		//for(int i = 0; i < range.size(); ++i)
		Iterator <Pair <Integer, Integer> >  range_iter = range.iterator();
		while (range_iter.hasNext()) {
			//Pair<Integer, Integer> p1 = (Pair <Integer, Integer>) range_iter.next();
			Pair<Integer, Integer> p1 =  range_iter.next();
			if(n1 <= p1.first && n2 >= p1.second){
				//stringstream err_msg;
				//err_msg << "range given: " << n1 << " - " << n2
				//	<< " completely contains an earlier range:"
				//	<< range[i].first << " - " << range[i].second
				//	<< " and makes it redundant."
				//	<< endl;
				//print_err(compiler_sem_err, err_msg.str().c_str()
				//		, qscript_parser::line_no
				//		, __LINE__, __FILE__);
			} else if ( n1 >= p1.first && n2 <= p1.second){
				//stringstream err_msg;
				//err_msg << "range given: " << n1 << " - " << n2
				//	<< " is completely contained in an earlier range:"
				//	<< range[i].first << " - " << range[i].second << endl;
				//print_err(compiler_sem_err, err_msg.str().c_str()
				//		, qscript_parser::line_no
				//		, __LINE__, __FILE__);
			} else if (n1 <= p1.first
				   && n2 >= p1.first && n2 <= p1.second) {
				//stringstream err_msg;
				//err_msg << "range given: " << n1 << " - " << n2
				//	<< " is partially contained in an earlier range:"
				//	<< range[i].first << " - " << range[i].second << endl;
				//print_err(compiler_sem_err, err_msg.str().c_str()
				//		, qscript_parser::line_no
				//		, __LINE__, __FILE__);
			} else if (n2 > p1.second
				   && n1 >= p1.first && n1 <= p1.second) {
				//stringstream err_msg;
				//err_msg << "range given: " << n1 << " - " << n2
				//	<< " is partially contained in an earlier range:"
				//	<< range[i].first << " - " << range[i].second << endl;
				//print_err(compiler_sem_err, err_msg.str().c_str()
				//		, qscript_parser::line_no
				//		, __LINE__, __FILE__);
			} else if ( (n1 < p1.first && n2 < p1.first)
				    ||	(n1 > p1.second && n2 > p1.second)){
				// this is the allowed case
			} else {
				//stringstream err_msg;
				//err_msg << "internal compiler programming error. Contact maintainer";
				//print_err(compiler_internal_error, err_msg.str().c_str()
				//		, qscript_parser::line_no
				//		, __LINE__, __FILE__);
			}
		}

		//range.push_back(pair<int,int>(n1, n2));
		range.add(new Pair<Integer,Integer>(n1, n2));
	}
	
	void add_indiv(Integer n1)
	{
		if (exists(n1)) {
		} else {
			indiv.add(n1);
		}
	}

	boolean exists(Integer key)
	{
		//for (Integer i = 0; i < range.size(); ++i) {
		//	if (key >= range[i].first && key <= range[i].second) {
		//		return true;
		//	}
		//}
		Iterator < Pair<Integer, Integer> > range_iter = range.iterator();
		while (range_iter.hasNext()) {
			//Pair <Integer, Integer> p1 = (Pair <Integer, Integer>) range_iter.next();
			Pair <Integer, Integer> p1 =  range_iter.next();
			if (key > p1.first && key < p1.second) {
				return true;
			}
		}
		/*
		for(	set<int>::iterator it = indiv.begin(); it!=indiv.end(); ++it){
			if (key == *it) {
				return true;
			}
		}
		*/
		//set<Integer>::iterator it = indiv.find(key);
		//if(it != indiv.end()){
		//	return true;
		//}
		if (indiv.contains (key) ) {
			return true;
		}
		return false;
	}
	boolean contains_subset(Set<Integer>  set_data)
	{
		//empty question - could be blank -
		// if it wasnt for this we return true - a bug
		if (set_data.size() == 0) {
			return false;
		}
		Iterator <Integer> iter = set_data.iterator();
		//for (; it != set_data.end(); ++it) {
		//	val_exists = exists(*it);
		//	if (!val_exists) {
		//		return false;
		//	}
		//}
		while (iter.hasNext()) {
			//Integer v = (Integer) iter.next();
			Integer v =  iter.next();
			boolean val_exists = exists(v);
			if (!val_exists) {
				return false;
			}
		}
		return true;
	}
	boolean contains_value(Integer v) {
		boolean val_exists = false;
		val_exists = exists(v);
		return val_exists;
	}
	//std::string print_replicate_code(std::string set_name);
	Integer GetMax()
	{
		//Set<Integer>::iterator it = indiv.begin();
		Iterator<Integer> iter = indiv.iterator();
		Integer max_code =  iter.next();
		while (iter.hasNext()) {
			Integer next_code = iter.next();
			if (max_code < next_code) {
				max_code = next_code;
			}
		}
		Iterator < Pair<Integer, Integer> > iter2 = range.iterator();
		while (iter2.hasNext()) {
			//Pair <Integer, Integer> p1 =  (Pair <Integer, Integer>) iter2.next();
			Pair <Integer, Integer> p1 =  iter2.next();
			if (max_code < p1.second) {
				max_code = p1.second;
			}
		}
		return max_code;
	}

}
