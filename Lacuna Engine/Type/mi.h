#pragma once
#include <iostream>

namespace LE
{
    // minus (-1) int (size_t)
    struct mi {
        int value;

        mi() : value(-1) {} // default constructor

        mi(int val) {
            if (val < -1) value = -1;
            else value = val;
        } // constructor with parameter

        operator int() const {
            return value;
        } // type conversion operator to int

        mi& operator++() {
            ++value;
            return *this;
        } // pre-increment operator

        mi operator++(int) {
            mi temp = *this;
            ++value;
            return temp;
        } // post-increment operator

        mi& operator--() {
            if (value > -1) --value;
            return *this;
        } // prefix decrement operator

        mi operator--(int) {
            mi temp(*this);
            if (value > -1) --value;
            return temp;
        } // postfix decrement operator
    };
    // for + exit condition (return var increment result or exitValue)
    #define for_er(cycleVar, varValue, condition, increment, exitCondition, exitValue) \
	    for (auto cycleVar = varValue; condition; increment) \
	    { \
		    if (exitCondition) \
		    { \
				return exitValue; \
		    } \
	    }// \
        //return exitValue; \
    // for + exit condition (get lambda result)
    #define for_el(cycleVar, varValue, condition, increment, exitCondition, exitValue) \
        [&]() { \
	        for_er(cycleVar, varValue, condition, increment, exitCondition, exitValue); \
        }()
}