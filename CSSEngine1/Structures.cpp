#include "Structures.h"
#include <cstring>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
using namespace std;

int getLength(const char* str)
{
	if (str == nullptr) return 0;
	int l = 0;
	while (str[l++] != '\0') {}
	return l;
}
CSSData::CSSData()
{
	this->name = nullptr;
	this->content = nullptr;
}
CSSData::CSSData(const char* name, const char* content)
{
	this->name = nullptr;
	this->content = nullptr;
	this->SetName(name);
	this->SetContent(content);
}
CSSData& CSSData::operator=(const CSSData& right)
{
	std::swap(name, ((CSSData&)right).name);
	std::swap(content, ((CSSData&)right).content);

	return *this;
}
CSSData::CSSData(const CSSData& other)
{
	int l;
	this->name = nullptr;
	this->content = nullptr;
	if (other.name != nullptr)
	{
		l = 0;
		while (other.name[l++] != '\0') {}
		this->name = new char[l];
		for (int i = 0; i < l; i++)
			this->name[i] = other.name[i];
	}
	if (other.content != nullptr)
	{
		l = 0;
		while (other.content[l++] != '\0') {}
		this->content = new char[l];
		for (int i = 0; i < l; i++)
			this->content[i] = other.content[i];
	}
}
char* CSSData::GetName() const
{
	return this->name;
}
void CSSData::SetName(const char* name)
{
	if (name == nullptr) return;
	int l = 0;
	while (name[l++] != '\0') {}
	this->name = new char[l];
	strncpy(this->name, name, l);
}
char* CSSData::GetContent() const
{
	return this->content;
}
void CSSData::SetContent(const char* content)
{
	if (content == nullptr) return;
	int l = 0;
	while (content[l++] != '\0') {}
	this->content = new char[l];
	strncpy(this->content, content, l);
}
CSSData::~CSSData()
{
	if (this->name != nullptr)
		delete[] this->name;
	if (this->content != nullptr)
		delete[] this->content;
}
void CSSData::print()
{
	if (this->name == nullptr)
	{
		//cout << this << ": name field empty\n";
		//return;
	}
	else cout << this->name;
	if (this->content == nullptr)
	{
		//cout << this << ": content field empty\n";
	}
	else cout << ": " << this->content;
	cout << "\n";
}


Block::~Block()
{

}
void Block::printBlock()
{
	if (this->selectors.isEmpty())
	{
		cout << "Block " << this << ": empty selector list\n";
	}
	else this->selectors.printList();
	if (this->attributes.isEmpty())
	{
		cout << "Block " << this << ": empty attribute list\n";
	}
	else this->attributes.printList();
}
void Block::addCSS(const char* name, const char* content)
{
	CSSData tmp(name, content);
	this->addCSS(tmp);
}
void Block::addCSS(const CSSData& structure)
{
	if (structure.GetContent() == nullptr)
	{
		this->selectors.addAtEnd(structure);
		return;
	}
	this->attributes.addAtEnd(structure);
}


LList::LList()
{
	this->head = nullptr;
}
LList::LList(const CSSData& structure)
{
	this->initHead(structure);
}
LList::~LList()
{
	if (this->head != nullptr)
	{
		delete head;
	}
	//this->emptyList();
}
void LList::initHead(const CSSData& structure)
{
	this->head = new LLNode(structure);
}
void LList::printList()
{
	LLNode* ptr = this->head;
	while (ptr != nullptr)
	{
		ptr->Data.print();
		ptr = ptr->next;
	}
}

void LList::addAtEnd(const CSSData& structure)
{
	LLNode* ptr = this->head;
	if (ptr == nullptr)
	{
		this->initHead(structure);
		return;
	}
	while (ptr->next != nullptr)
	{
		ptr = ptr->next;
	}
	ptr->next = new LLNode(structure);
}
int LList::getLength()
{
	int l = 0;
	LLNode* ptr = this->head;
	while (ptr != nullptr)
	{
		l++;
		ptr = ptr->next;
	}
	return l;
}
void LList::emptyList()
{
	if (this->head != nullptr)
	{
		delete this->head;
		this->head = nullptr;
	}
}
bool LList::isEmpty()
{
	if (this->head == nullptr) return true;
	return false;
}

LLNode::LLNode()
{
	this->next = nullptr;
}
LLNode::LLNode(const CSSData& structure)
{
	this->next = nullptr;
	this->Data = structure;
}
void LLNode::letItGo()
{
	if (this->next != nullptr)
	{
		this->next->letItGo();
	}
	this->next = nullptr;
}
LLNode::~LLNode()
{
	if (this->next != nullptr)
	{
		delete this->next;
	}
	this->next = nullptr;
}

DLList::DLList()
{
	this->head = nullptr;
}
void DLList::initHead()
{
	this->head = new DLLNode;
}
void DLList::printList()
{
	//this->Data[0].printBlock();
}
void DLList::removeNode(DLLNode* node)
{
	if (node->prev == nullptr) this->head = node->next;
	else
	{
		if (node->prev != nullptr) node->prev->next = node->next;
		if (node->next != nullptr) node->next->prev = node->prev;
		node->next = nullptr;
		node->prev = nullptr;
		delete node;
		if (this->head == node) this->head = nullptr;
	}
}
DLList::~DLList()
{
	if (this->head != nullptr)
	{
		delete head;
	}
}
bool DLLNode::isEmpty()
{
	for (int i = 0; i < NodeSize; i++)
	{
		if (this->flag[i] == true) return false;
	}
	return true;
}
int DLLNode::isFull()
{
	for (int i = 0; i < NodeSize; i++)
	{
		if (this->flag[i] == false) return i;
	}
	return NodeSize;
}
DLLNode::DLLNode()
{
	this->next = nullptr;
	this->prev = nullptr;
	for (int i = 0; i < NodeSize; i++)
	{
		this->flag[i] = false;
	}
};
DLLNode::~DLLNode()
{
	if (this->next != nullptr)
	{
		delete this->next;
	}
	this->next = nullptr;
}
void DLLNode::addCSS(int block_id, const char* name, const char* content)
{
	this->flag[block_id] = true;
	this->Data[block_id].addCSS(name, content);
}
