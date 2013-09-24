/*
 * ========================================================================
 *
 *       Filename:  simple_rng.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Monday 23 September 2013 03:52:06  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =======================================================================
 */

#include "simple_rng.h"

int MyRNG::operator () (ptrdiff_t i)
{
	return rand_r(&random_seed) % i;
}
