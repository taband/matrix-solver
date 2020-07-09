#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
//#include <windows.h>
using namespace std;

char __message[128]; // used by error message
void print_error(); // used to print error

#include "matrix.h"
#include "sparse.h"
#include "linear_solver.h"

void print_error()
{
	//MessageBox(NULL, __message, "Error", MB_OK | MB_ICONERROR);
	cout << __message << endl;
	system("pause");
	exit(0);
}