#pragma once

#include <stdint.h>

typedef unsigned int size_t;
void* operator new (size_t size);

void CleanArray(char array[]);
int GetArraySize(char array[]);

void StringCopy(char* a , char* b);
int StringMatches(char* Str1 , const char* Str2);