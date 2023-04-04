#pragma once
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#define NodeSize 8

class CSSData
{
private:
	char* name;
	char* content;
public:
	char* GetName() const;
	void SetName(const char* name);
	char* GetContent() const;
	void SetContent(const char* content);
	CSSData();
	CSSData(const char* name, const char* content = nullptr);
	CSSData& operator=(const CSSData& right);
	CSSData(const CSSData& other);
	~CSSData();
};



class LLNode
{
public:
	CSSData Data;
	LLNode* next;
	LLNode();
	LLNode(const CSSData& structure);
	void letItGo();
	~LLNode();
};
class LList
{
public:
	LLNode* head;
	void initHead(const CSSData& structure);
	void addAtEnd(const CSSData& structure);
	int getLength();
	void emptyList();
	bool isEmpty();
	LList();
	LList(const CSSData& structure);
	~LList();
};
class Block
{
public:
	LList selectors;
	LList attributes;
	void addCSS(const char* name, const char* content = nullptr);
	void addCSS(const CSSData& structure);
	~Block();
};


class DLLNode
{
public:
	Block Data[NodeSize];
	bool flag[NodeSize];
	DLLNode* next;
	DLLNode* prev;
	void addCSS(int block_id, const char* name, const char* content = nullptr);
	bool isEmpty();
	DLLNode();
	~DLLNode();
};
class DLList : public LList
{
public:
	DLLNode* head;
	void initHead();
	void printList();
	void removeNode(DLLNode* node);
	DLList();
	~DLList();
};
