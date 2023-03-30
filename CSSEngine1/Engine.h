#pragma once
#include "Structures.h"

#define END_LINE '\n'
#define SELECTOR_SEPARATOR ','
#define SPACE ' '
#define BLOCK_OPEN '{'
#define BLOCK_CLOSE '}'
#define ATTRIBUTE_COLON ':'
#define ATTRIBUTE_SEMICOLON ';'
#define COMMAND_BEGIN '?'
#define COMMAND_END '*'
#define COMMAND_BEGIN_STR "???"
#define COMMAND_END_STR "***"
#define EOS '\0'

class Engine
{
private:
	DLList DLList;
	int nOfBlocks;
public:
	Engine();
	DLLNode* findFirstFreeNode();
	Block* findFirstFreeBlock(DLLNode* ptr = nullptr);
	DLLNode* getNodeByBlockId(int block_id);
	Block* getBlockByBlockId(int block_id);
	bool addCSS(int block_id, const char* name, const char* content = nullptr);
	bool addBlock(const Block& block);

	int getNumberOfSelectorsByBlockId(int block_id);
	int getNumberOfAttributesByBlockId(int block_id);
	int getNumberOfBlocks();
	char* getSelectorByBlockId(int block_id, int selector_id);
	char* getContentByBlockId(int block_id, const char* nameOfAttribute);
	int getNumberOfAttributesNamed(const char* nameOfAttribute);
	int getNumberOfSelectorsNamed(const char* nameOfSelector);
	char* getContentOfAttributeBySelector(const char* nameOfSelector, const char* nameOfAttribute);
	int removeBlockByBlockId(int block_id);
	int removeAttributeByBlockId(int block_id, const char* nameOfAttribute);
	void getInput();
	void handleCommand(String* arg);
};

