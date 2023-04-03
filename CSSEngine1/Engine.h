#pragma once
#include "Structures.h"
#include "MyString.h"
#define EOL '\n'
#define TAB_KEY '\t'
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
#define COMMAND_SELECTOR_SIGN "S"
#define COMMAND_ATTRIBUTE_SIGN "A"
#define COMMAND_E_SIGN "E"
#define COMMAND_ASK_SIGN "?"
#define COMMAND_DELETE_SIGN "D"
#define COMMAND_DELETE_INFO "deleted"
#define COMMAND_DELETE_INFO_LENGTH 8
#define COMMAND_DELETE_ALL "*"
#define RESULT_EQUAL " == "

#define EOS '\0'


class Engine
{
private:
	DLList DLList;
	int nOfBlocks;
public:
	enum class Type;
	Engine();
	DLLNode* findFirstFreeNode();
	Block* findFirstFreeBlock(DLLNode** ptr = nullptr, int* interCounter = nullptr);
	DLLNode* getNodeByBlockId(int block_id);
	Block* getBlockByBlockId(int block_id, DLLNode** ptrToUpdate = nullptr, int* interCounter = nullptr);
	LLNode* findNodeWithName(LList* list, const char* str, LLNode** prev = nullptr);
	bool addCSS(int block_id, const char* name, const char* content = nullptr);
	bool addBlock(const Block& block);

	int getNumberOfSelectorsByBlockId(int block_id);
	int getNumberOfAttributesByBlockId(int block_id);
	int getNumberOfBlocks();
	char* getSelectorByBlockIdBySelectorId(int block_id, int selector_id);
	char* getContentByBlockIdByAttName(int block_id, const char* nameOfAttribute);
	int getNumberOfCSSDataNamed(const char* name, Type type);
	char* getContentOfAttributeBySelector(const char* nameOfSelector, const char* nameOfAttribute);
	int removeBlockByBlockId(int block_id);
	int removeAttributeByBlockIdByAttName(int block_id, const char* nameOfAttribute);
	void handleCommand(String* arg);
	int strToNumber(String& str);
	void printCommand(String* arg);
	void getInput();
};


