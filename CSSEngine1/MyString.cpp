#include "MyString.h"
#define MIN_ASCII '!'
#define MAX_ASCII '~'
bool String::hasAChar()
{
	if (this->str == nullptr) return 0;
	int l = 0;
	while (this->str[l] != '\0') 
	{
		if (this->str[l] >= MIN_ASCII && this->str[l++] <= MAX_ASCII) return true;
	}
	return false;
}
void String::clear()
{
	if (this->str != nullptr) delete[] str;
	this->str = nullptr;
	this->blocks = 0;
}
int String::getLength() const
{
	if (this->str == nullptr) return 0;
	int l = 0;
	while (this->str[l++] != '\0') {}
	return l;
}
int String::getBlocks() const
{
	return this->blocks;
}
void String::allocate(int length)
{
	if (length < 0) return;
	this->blocks = (length - 1) / STR_BLOCK_SIZE + 1;
	if (this->str != nullptr)
	{
		char* temp = new char[this->blocks * STR_BLOCK_SIZE];
		for (int i = 0; i < length; i++)
		{
			temp[i] = this->str[i];
			if (str[i] == '\0') break;
		}
		delete[] this->str;
		this->str = temp;
		return;
	}
	this->str = new char[this->blocks * STR_BLOCK_SIZE];
}
String::String()
{
	this->str = nullptr;
	this->blocks = 0;
}
String::String(const String& other)
{
	this->str = nullptr;
	this->blocks = 0;
	int l = other.blocks * STR_BLOCK_SIZE;
	this->str = new char[l];
	for (int i = 0; i < l; i++)
		this->str[i] = other.str[i];
}
String::String(const char* str)
{
	this->str = nullptr;
	this->blocks = 0;
	this->SetStr(str);
}
String& String::operator=(const String& right)
{
	std::swap(str, ((String&)right).str);
	this->blocks = right.blocks;
	return *this;
}
void String::SetStr(const char* str)
{
	int l;
	if (str != nullptr)
	{
		l = 0;
		while (str[l++] != '\0') {}
		this->allocate(l);
		for (int i = 0; i < l; i++)
			this->str[i] = str[i];
	}
}
char* String::GetStr() const
{
	return this->str;
}
String& String::operator+(const String& right)
{
	if (this->str == nullptr)
	{
		this->SetStr(right.str);
		return *this;
	}
	int a = this->getLength(), b = right.getLength();
	if (a + b - 1 < this->blocks * STR_BLOCK_SIZE)
	{
		for (int i = 0; i < b; i++)
		{
			this->str[i+a-1] = right.str[i];
		}
		return *this;
	}

	this->allocate(a + b - 1);
	for (int i = 0; i < b; i++)
	{
		this->str[a - 1 + i] = right.str[i];
	}
	return *this;
}
String& String::operator+(const char* right)
{
	if (this->str == nullptr)
	{
		this->SetStr(right);
		return *this;
	}
	int a = this->getLength(), b = 0;
	while (right[b++] != '\0') {}
	if (a + b - 1 < this->blocks * STR_BLOCK_SIZE)
	{
		for (int i = 0; i < b; i++)
		{
			this->str[i + a - 1] = right[i];
		}
		return *this;
	}

	this->allocate(a + b - 1);
	for (int i = 0; i < b; i++)
	{
		this->str[a - 1 + i] = right[i];
	}
	return *this;
}
String::~String()
{
	if (str != nullptr)
	{
		delete[] str;
	}
}
std::ostream& operator<<(std::ostream& os, const String& string) {
	return os << string.GetStr();
}