#ifndef UTILS_H_
#define UTILS_H_
#include <stdint.h>
#include <ctype.h>

int checkSum(const char* src, int length);
int c2i(char ch);
bool validPreference(const char* preference);
#endif