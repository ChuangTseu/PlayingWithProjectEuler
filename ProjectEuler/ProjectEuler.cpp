// ProjectEuler.cpp : Defines the entry point for the console application.
//

#include "config.h"

#define PROBLEM_N_FN_DECL_EXPAND2(n) extern void problem##n();
#define PROBLEM_N_FN_CALL_EXPAND2(n) problem##n();

#define PROBLEM_N_FN_DECL_EXPAND(n) PROBLEM_N_FN_DECL_EXPAND2(n)
#define PROBLEM_N_FN_CALL_EXPAND(n) PROBLEM_N_FN_CALL_EXPAND2(n)

#define PROBLEM_N_FN_DECL PROBLEM_N_FN_DECL_EXPAND(CURRENT_PROBLEM)
#define PROBLEM_N_FN_CALL PROBLEM_N_FN_CALL_EXPAND(CURRENT_PROBLEM)

#define CURRENT_PROBLEM 23

PROBLEM_N_FN_DECL;

int main()
{
	PROBLEM_N_FN_CALL;

    return 0;
}

