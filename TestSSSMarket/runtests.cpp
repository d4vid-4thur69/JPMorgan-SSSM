//============================================================================
// Name        : runtests.cpp
// Author      : David Ashford
// Version     :
//============================================================================
#include "CppUTest/CommandLineTestRunner.h"

#include <iostream>

using namespace std;

int main(int ac, char** av)
{
	CommandLineTestRunner::RunAllTests(ac, av);
}
