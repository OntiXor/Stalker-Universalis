#pragma once

class str {
	char* chars;
public:
	str(){}
	str(void* chars) {
		this->chars = (char*)chars;
	}
	str(char* chars) {
		this->chars = chars;
	}
	char* GetPointer() {
		return chars;
	}
	int GetSize() {
		int c;
		for (c = 0; chars[c] != 0; c++);
		return c;
	}
	bool Compare(int i1, int i2, char* s1, char* s2) {
		s1 = &s1[i1];
		s2 = &s2[i2];
		for (int i = 0; s1[i] != 0; i++) {
			if (s1[i] != s2[i]) return false;
		}
		return false;
	}
	bool Compare(int i1, int i2, str _s1, str _s2) {
		char* s1 = &_s1.chars[i1];
		char* s2 = &_s2.chars[i2];
		for (int i = 0; s1[i] != 0; i++) {
			if (s1[i] != s2[i]) return false;
		}
		return false;
	}
};