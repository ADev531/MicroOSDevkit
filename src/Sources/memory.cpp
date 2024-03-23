#include "../Library/memory.h"
#include "../Library/stdint.h"

void* operator new(size_t size) {
    void* buf[size];
    return buf;
}

void CleanArray(char array[]) {
	for (int i = 0; i < GetArraySize(array); i++) {
		array[i] = 0;
	}
}

int GetArraySize(char array[]) {
	return sizeof(array)/sizeof(char);
}

void StringCopy(char* a , char* b) {
	for(int i = 0; a[i] != '\0'||b[i] != '\0'; i++) {
		a[i] = b[i];
	}
}

int StringMatches(char* Str1 , const char* Str2) {
	for(int i = 0; Str1[i] != '\0'||Str2[i] != '\0'; i++) {
		if(Str1[i] != Str2[i]) {
			return 1;
		}
	}
	return 0;
}
