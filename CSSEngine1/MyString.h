#pragma once
#include <iostream>
#define STR_BLOCK_SIZE 8

class String
{
private:
	char* str;
	int blocks;
public:
	String();
	String(const char* str);
	String(const String& other);
	~String();
	int getLength() const;
	int getBlocks() const;
	void clear();
	void allocate(int length);
	void setStr(const char* str);
	char* getStr() const;
	bool isNumber();
	//Checks if the string contains an alphanumeric character
	bool hasAChar();
	bool operator==(const String& right);
	String& operator=(const String& right);
	String& operator+(const String& right);
	String& operator+(const char* right);
};
std::ostream& operator<<(std::ostream& os, const String& string);