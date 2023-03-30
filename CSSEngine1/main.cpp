#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Structures.h"
#include "Engine.h"
#include "MyString.h"
using namespace std;

int main()
{
	Engine engine;
	engine.getInput();

	String a = "abkjlc";
	a = a + "ab";
	a = a + "abhfghfghfhjfghgfhjfgkhj";
	cout << a;
	//engine.getInput();
	//b.head->Data[0].addCSS("margin", "2px");

	/*CSSData attr;
	attr.name = new char[32];
	strcpy(attr.name, "margin");
	attr.content = new char[32];
	strcpy(attr.content, "4px");*/

	//b.head->Data[0].attributes.addAtEnd(attr);

	/*/b->Data[0].attributes->next = new LLNode<Attribute>;
	b->Data[0].attributes->next->data.name = new char[32];
	b->Data[0].attributes->next->data.content = new char[32];
	strcpy(b->Data[0].attributes->next->data.name, "h2");
	strcpy(b->Data[0].attributes->next->data.content, "7px");*/

	//b.head->Data[0].printBlock();
	return 0;
}