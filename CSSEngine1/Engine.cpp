#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include "Engine.h"
#include "MyString.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
enum class Engine::Type
{
	selector,
	attribute
};
Engine::Engine()
{
	this->nOfBlocks = 0;
}
DLLNode* Engine::findFirstFreeNode()
{
	if (this->DLList.head == nullptr) this->DLList.initHead();
	DLLNode* ptr = this->DLList.head;
	int firstFreeBlock = ptr->isFull();
	if (ptr == nullptr) return nullptr;
	while (firstFreeBlock == NodeSize)
	{
		if (ptr->next == nullptr)
		{
			ptr->next = new DLLNode;
			ptr->next->prev = ptr;
		}
		ptr = ptr->next;
		firstFreeBlock = ptr->isFull();
	}
	return ptr;
}
Block* Engine::findFirstFreeBlock(DLLNode* ptr)
{
	if (ptr == nullptr)
	{
		DLLNode* ptr = this->findFirstFreeNode();
	}
	if (ptr == nullptr) return nullptr;
	int firstFreeBlock = ptr->isFull();
	return &(ptr->Data[firstFreeBlock]);

}
LLNode* Engine::findNodeWithName(LList* list, const char* str, LLNode** prev)
{
	if (list == nullptr || str == nullptr) return nullptr;
	LLNode* node = list->head;
	if (prev != nullptr) *prev = node;
	while (node != nullptr)
	{
		char* name = node->Data.GetName();
		if (name != nullptr
			&& strcmp(name, str) == 0)
		{
			return node;
		}
		if (prev != nullptr) *prev = node;
		node = node->next;
	}
	return nullptr;

}
bool Engine::addBlock(const Block& block)
{
	DLLNode* node = findFirstFreeNode();
	Block* firstFree = findFirstFreeBlock(node);
	int cellNumber = node->isFull();
	if (firstFree != nullptr)
	{
		*firstFree = block;
		this->nOfBlocks++;
		node->flag[cellNumber] = true;
		return true;
	}
	return false;
}
Block* Engine::getBlockByBlockId(int block_id, DLLNode** ptrToUpdate, int* interCounter)
{
	if (block_id <= 0) return nullptr;
	DLLNode* node = this->DLList.head;
	Block* block = nullptr;
	int i = 0;
	while (node != nullptr)
	{
		for (i = 0; i < NodeSize; i++)
		{
			if (node->flag[i]) block_id--;
			if (block_id == 0)
			{
				block = &(node->Data[i]);
				break;
			}
		}
		if (block == nullptr) node = node->next;
		else break;
	}
	if (block == nullptr || node == nullptr) return nullptr;
	if (ptrToUpdate != nullptr) *ptrToUpdate = node;
	if (interCounter != nullptr) *interCounter = i;
	return block;
}
int Engine::getNumberOfBlocks()
{
	/*DLLNode* ptr = this->DLList.head;
	if (ptr == nullptr) return 0;
	int n = 0;
	for (; ptr->next != nullptr; ptr = ptr->next)
	{
		n += ptr->isFull();
	}
	return n;*/
	return this->nOfBlocks;
}
int Engine::getNumberOfSelectorsByBlockId(int block_id) //
{
	Block* block = this->getBlockByBlockId(block_id);
	if (block == nullptr) return 0;
	return block->selectors.getLength();
}
int Engine::getNumberOfAttributesByBlockId(int block_id) //
{
	Block* block = this->getBlockByBlockId(block_id);
	if (block == nullptr) return 0;
	return block->attributes.getLength();
}
char* Engine::getSelectorByBlockIdBySelectorId(int block_id, int selector_id) //
{
	if (selector_id <= 0) return nullptr;
	Block* block = this->getBlockByBlockId(block_id);
	if (block == nullptr) return nullptr;
	LLNode* list = block->selectors.head;
	while (--selector_id > 0)
	{
		if (list == nullptr) return nullptr;
		list = list->next;
	}
	if (list == nullptr) return nullptr;
	return list->Data.GetName();
}
char* Engine::getContentByBlockIdByAttName(int block_id, const char* nameOfAttribute) //
{
	if (nameOfAttribute == nullptr) return nullptr;
	Block* block = this->getBlockByBlockId(block_id);
	LList* list = &(block->attributes);
	LLNode* node = this->findNodeWithName(list, nameOfAttribute);
	if (node == nullptr) return nullptr;
	return node->Data.GetContent();
}
int Engine::getNumberOfCSSDataNamed(const char* name, Type type) //
{
	if (name == nullptr) return 0;
	DLLNode* ptr = this->DLList.head;
	int n = 0;
	for (; ptr != nullptr; ptr = ptr->next)
	{
		for (int i = 0; i < NodeSize; i++)
		{
			if (ptr->flag[i] == false) continue;
			LLNode* node = nullptr;
			if (type == Type::selector) node = ptr->Data[i].selectors.head;
			else if (type == Type::attribute) node = ptr->Data[i].attributes.head;
			for (; node != nullptr; node = node->next)
			{
				char* dataName = node->Data.GetName();
				if (dataName != nullptr
					&& strcmp(dataName, name) == 0) n++;
			}
		}
	}
	return n;
}
char* Engine::getContentOfAttributeBySelector(const char* nameOfSelector, const char* nameOfAttribute)
{
	if (nameOfSelector == nullptr || nameOfAttribute == nullptr) return nullptr;
	DLLNode* ptr = this->DLList.head;
	if (ptr == nullptr) return nullptr;
	for (; ptr->next != nullptr; ptr = ptr->next)
	{
	}
	for (; ptr != nullptr; ptr = ptr->prev)
	{
		for (int i = NodeSize - 1; i >= 0; i--)
		{
			if (ptr->flag[i] == false) continue;
			LLNode* selectors = ptr->Data[i].selectors.head;
			for (; selectors != nullptr; selectors = selectors->next)
			{
				char* name = selectors->Data.GetName();
				if (name != nullptr
					&& strcmp(name, nameOfSelector) == 0)
				{
					LLNode* attributes = ptr->Data[i].attributes.head;
					for (; attributes != nullptr; attributes = attributes->next)
					{
						char* name = attributes->Data.GetName();
						if (name != nullptr
							&& strcmp(name, nameOfAttribute) == 0)
						{
							return attributes->Data.GetContent();
						}
					}
				}
			}
		}
	}
	return nullptr;
}
int Engine::removeBlockByBlockId(int block_id)
{
	DLLNode* node;
	int flagId;
	Block* block = getBlockByBlockId(block_id, &node, &flagId);
	if (block == nullptr || node == nullptr) return -1;
	node->flag[flagId] = false;
	block->selectors.emptyList();
	block->attributes.emptyList();
	this->nOfBlocks--;
	if (node->isEmpty())
	{
		this->DLList.removeNode(node);
	}
	return 1;
}
int Engine::removeAttributeByBlockIdByAttName(int block_id, const char* nameOfAttribute)
{
	DLLNode* node;
	int flagId;
	Block* block = getBlockByBlockId(block_id, &node, &flagId);
	if (block == nullptr || node == nullptr) return -1;
	LLNode* prevAtt;
	LLNode* attListNode = findNodeWithName(&(block->attributes), nameOfAttribute, &prevAtt);
	if (attListNode == nullptr) return -1;
	if (prevAtt == attListNode) prevAtt = nullptr;
	if (prevAtt != nullptr) prevAtt->next = attListNode->next;
	else block->attributes.head = attListNode->next;
	attListNode->next = nullptr;
	delete attListNode;
	if (block->attributes.getLength() == 0)
	{
		block->attributes.emptyList();
		block->selectors.emptyList();
		node->flag[flagId] = false;
		this->nOfBlocks--;
	}
	if (node->isEmpty())
	{
		this->DLList.removeNode(node);
	}
	return 1;
}



template <class T>
void freePtr(T** ptr)
{
	if (ptr != nullptr)
	{
		if (*ptr != nullptr)
		{
			delete* ptr;
			*ptr = nullptr;
		}
	}
}
void emptyBlock(Block** ptr)
{
	if (ptr != nullptr)
	{
		if (*ptr != nullptr)
		{
			(*ptr)->selectors.head = nullptr;
			(*ptr)->attributes.head = nullptr;
			delete* ptr;
			*ptr = nullptr;
		}
	}
}
/*int pow(int a, int n)
{
	if (a == 0) return 0;
	if (a == 1) return 1;
	if (n < 0) return 0;
	if (a == 2) return a << n;
	int pow = a;
	for (int i = 1; i < n; i++) pow *= a;
}*/
int Engine::strToNumber(String& str)
{
	int sum = -1;
	if (str.isNumber())
	{
		sum = 0;
		int l = str.getLength() - 1;
		char* strTab = str.getStr();
		for (int i = 1; i <= l; i++)
		{
			sum += (strTab[i - 1] - '0') * pow(10, l - i);
		}
		if (sum < 0) return -1;
	}
	return sum;
}
enum argument
{
	FIRST,
	SECOND,
	THIRD
};
void Engine::printCommand(String* arg)
{
	cout << arg[FIRST] << SELECTOR_SEPARATOR
		<< arg[SECOND] << SELECTOR_SEPARATOR
		<< arg[THIRD];
}

void Engine::handleCommand(String* arg) // -,-,-
{
	if (arg == nullptr) return;
	int result = -1;
	char* resultStr = nullptr;
	if (arg[FIRST].isNumber()) // i,-,-
	{
		int blockId = strToNumber(arg[FIRST]);
		if (arg[SECOND] == COMMAND_SELECTOR_SIGN) // i,S,-
		{
			if (arg[THIRD] == COMMAND_ASK_SIGN) // i,S,?
			{
				result = getNumberOfSelectorsByBlockId(blockId);
				if (result <= 0) result = -1;
			}
			else // i,S,X
			{
				int selectorId = strToNumber(arg[THIRD]);
				resultStr = getSelectorByBlockIdBySelectorId(blockId, selectorId);
			}
		}
		else if (arg[SECOND] == COMMAND_ATTRIBUTE_SIGN) // i,A,-
		{
			if (arg[THIRD] == COMMAND_ASK_SIGN) // i,A,?
			{
				result = getNumberOfAttributesByBlockId(blockId);
				if (result <= 0) result = -1;
			}
			else
			{
				resultStr = getContentByBlockIdByAttName(blockId, arg[THIRD].getStr()); //i,A,X
			}
		}
		else if (arg[SECOND] == COMMAND_DELETE_SIGN) // i,D,-
		{
			if (arg[THIRD] == COMMAND_DELETE_ALL) // i,D,*
			{
				result = removeBlockByBlockId(blockId);
				if (result == 1)
				{
					result = -1;
					resultStr = new char[COMMAND_DELETE_INFO_LENGTH];
					strncpy(resultStr, COMMAND_DELETE_INFO, COMMAND_DELETE_INFO_LENGTH);
				}
			}
			else
			{
				result = removeAttributeByBlockIdByAttName(blockId, arg[THIRD].getStr());
				if (result == 1)
				{
					result = -1;
					resultStr = new char[COMMAND_DELETE_INFO_LENGTH];
					strncpy(resultStr, COMMAND_DELETE_INFO, COMMAND_DELETE_INFO_LENGTH);
				}
			}
		}
	}
	else
	{
		if (arg[SECOND] == COMMAND_ATTRIBUTE_SIGN) // n,A,?
		{
			result = getNumberOfCSSDataNamed(arg[FIRST].getStr(), Type::attribute);
		}
		else if (arg[SECOND] == COMMAND_SELECTOR_SIGN) // z,S,?
		{
			result = getNumberOfCSSDataNamed(arg[FIRST].getStr(), Type::selector);
		}
		else if (arg[SECOND] == COMMAND_E_SIGN) // z,E,n
		{
			resultStr = getContentOfAttributeBySelector(arg[FIRST].getStr(), arg[THIRD].getStr());
		}
	}

	if (result == -1 && resultStr == nullptr) return;

	this->printCommand(arg);
	cout << RESULT_EQUAL;
	if (result != -1) cout << result;
	if (resultStr != nullptr) cout << resultStr;
	cout << EOL;
}

enum mode
{
	SEARCH_SELECTORS,
	SEARCH_ATT_NAMES,
	SEARCH_ATT_CONTENT,
	SEARCH_COMMANDS
};

void Engine::getInput()
{
	//TODO
	// Odrzucanie powrotzen przy dodawaniu CSSdata do bloku

	int mode = SEARCH_SELECTORS;
	// 0 - looking for selectors
	// 1 - looking for attribute names
	// 2 - looking for attribute content
	// 3 - looking for commands

	Block* tempBlock = new Block;
	CSSData* tempData = nullptr;
	String text = "";
	char ch;
	while (scanf("%c", &ch) != EOF)
	{
	    if (ch == '\t') continue;
		if (ch == EOL && mode != SEARCH_COMMANDS) continue;
		if (mode == SEARCH_SELECTORS)
		{
			if (ch == SPACE) continue;
			if (ch == BLOCK_CLOSE) continue;
			if (ch == SELECTOR_SEPARATOR || ch == BLOCK_OPEN)
			{
				if (ch == BLOCK_OPEN)
				{
					mode = SEARCH_ATT_NAMES;
				}
				if (text.getLength() > 1)
				{
					tempBlock->addCSS(text.getStr());
				}
				text.clear();
				continue;
			}
			if (ch == COMMAND_BEGIN)
			{
				if (text.getStr() != nullptr && text == COMMAND_BEGIN_STR)
				{
					mode = SEARCH_COMMANDS;
					text.clear();
					continue;
				}
			}
		}
		else if (mode == SEARCH_ATT_NAMES)
		{
			if (ch == BLOCK_OPEN) continue;
			if (ch == BLOCK_CLOSE)
			{
				if (text.getLength() <= 1)
				{
					if (tempBlock != nullptr)
					{
						this->addBlock(*tempBlock);
						emptyBlock(&tempBlock);////////////////////////////////////////winowajca
						tempBlock = new Block;
					}
				}
				mode = SEARCH_SELECTORS;
				freePtr<CSSData>(&tempData);
				text.clear();
				continue;
			}
			if (ch == ATTRIBUTE_COLON)
			{
				if (text.getLength() <= 1) continue;
				tempData = new CSSData(text.getStr());
				mode = SEARCH_ATT_CONTENT;
				text.clear();
				continue;
			}
			if (ch == SPACE && !text.hasAChar()) continue;
		}
		else if (mode == SEARCH_ATT_CONTENT)
		{
			if (ch == BLOCK_OPEN) continue;
			if (ch == ATTRIBUTE_SEMICOLON || ch == BLOCK_CLOSE)
			{
				if (tempData == nullptr && ch != BLOCK_CLOSE) continue;
				mode = SEARCH_ATT_NAMES;
				tempData->SetContent(text.getStr());
				tempBlock->addCSS(*tempData);
				freePtr<CSSData>(&tempData);
				text.clear();
				if (ch == BLOCK_CLOSE)
				{
					// END OF BLOCK
					mode = SEARCH_SELECTORS;
					this->addBlock(*tempBlock);
					emptyBlock(&tempBlock);
					tempBlock = new Block;
				}
				continue;
			}
			if (ch == SPACE && !text.hasAChar()) continue;

		}
		else if (mode == SEARCH_COMMANDS)
		{
			if (ch == COMMAND_END)
			{
				if (text == COMMAND_END_STR)
				{
					mode = SEARCH_SELECTORS;
					text.clear();
					continue;
				}
			}
			int l = text.getLength();
			if (ch == COMMAND_BEGIN && l <= 1)
			{
				cout << COMMAND_ASK_SIGN << RESULT_EQUAL << getNumberOfBlocks() << EOL;
				text.clear();
				continue;
			}
			if (ch == EOL && l >= 1)
			{
				String arg[] = { "","","" };
				String* currentArg = arg;
				char* textStr = text.getStr();
				for (int i = 0; i < l; i++)
				{
					if (textStr[i] == SELECTOR_SEPARATOR)
					{
						currentArg++;
						continue;
					}
					if (textStr == nullptr) break;
					char stringToAppend[] = { textStr[i], EOS };
					*currentArg = *currentArg + stringToAppend;
				}
				this->handleCommand(arg);
				text.clear();
				continue;
			}
			else if (ch == EOL)
			{
				continue;
			}
		}

		char stringToAppend[] = { ch, EOS };
		text = text + stringToAppend;
	}
	if (tempBlock != nullptr) delete tempBlock;
	if (tempData != nullptr) delete tempData;

	return;
}
