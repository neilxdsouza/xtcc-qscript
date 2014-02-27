/*
 * ========================================================================
 *
 *       Filename:  simple_rng.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Monday 23 September 2013 03:49:51  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * ========================================================================
 */

#ifndef qscript_simple_rng_h
#define qscript_simple_rng_h
#include <cstdlib>
#include <ctime>

struct MyRNG
{
	unsigned int random_seed;
	MyRNG() : random_seed (time(0))
	{ }
	int operator () (ptrdiff_t i);

};

#endif /*  qscript_simple_rng_h */
