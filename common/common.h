#ifndef COMMON_H
#define COMMON_H

#include <iostream>

namespace Common {

int max ( int a, int b );
int min ( int a, int b );
int max ( const int *array, int length );
bool is_equal ( const int *array1, const int *array2, int length );
int length ( const char *cString );
void print ( const int *array, int length );
bool is_sorted ( const int *array, int length, bool ascending = true );
void swap ( int &a, int &b );
}

#endif // COMMON_H
