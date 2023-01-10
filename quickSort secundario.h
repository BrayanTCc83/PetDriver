#ifndef QUICKSORT
#define QUICKSORT

#include <stdlib.h>
#include <stdio.h>
#include "createJason.h"
#include <stdbool.h>

#define MAX_TRABAJADORES 5

bool Product_IsLower_By_ID(Empleado *p1, Empleado *p2);
bool Product_IsGreater_By_ID(Empleado *p1, Empleado *p2);
void quicksort(Empresa empresa);
void QuickSort(Empresa *empresa, int first, int last);
void swap(Empleado *x1,Empleado *x2);

#endif
