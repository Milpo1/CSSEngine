#include <cstdio>
#include "Engine.h"
#include "MyString.h"
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
bool Engine::addCSS(int block_id, const char* name, const char* content)
{
	DLLNode* node = getNodeByBlockId(block_id);
	if (node == nullptr)
	{
		cout << "Error: addCSS(" << "block_id: " << block_id;
		return false;
	}
	block_id = (block_id-1) % NodeSize;
	node->addCSS(block_id, name, content);
	return true;
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
DLLNode* Engine::getNodeByBlockId(int block_id)
{
	if (block_id <= 0) return nullptr;
	int node_id = (block_id-1) / NodeSize;
	if (this->DLList.head == nullptr) this->DLList.initHead();
	DLLNode* ptr = this->DLList.head;
	if (ptr == nullptr) return nullptr;
	while (node_id-- > 0)
	{
		if (ptr->next == nullptr)
		{
			return nullptr;
		}
		ptr = ptr->next;
	}
	return ptr;
}
Block* Engine::getBlockByBlockId(int block_id)
{
	DLLNode* node = getNodeByBlockId(block_id);
	if (node == nullptr) return nullptr;
	block_id = (block_id-1) % NodeSize;
	if (node->flag[block_id] == false) return nullptr;
	Block* block = &(node->Data[block_id]);
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
int Engine::getNumberOfSelectorsByBlockId(int block_id)
{
	Block* block = getBlockByBlockId(block_id);
	if (block == nullptr) return 0;
	return block->selectors.getLength();
}
int Engine::getNumberOfAttributesByBlockId(int block_id)
{
	Block* block = getBlockByBlockId(block_id);
	if (block == nullptr) return 0;
	return block->attributes.getLength();
}
char* Engine::getSelectorByBlockId(int block_id, int selector_id)
{
	Block* block = getBlockByBlockId(block_id);
	if (block == nullptr) return 0;
	LLNode* list = block->selectors.head;
	while (selector_id-- > 0)
	{
		if (list == nullptr) return nullptr;
		list = list->next;
	}
	return list->Data.GetName();
}
char* Engine::getContentByBlockId(int block_id, const char* nameOfAttribute)
{
	if (nameOfAttribute == nullptr) return nullptr;
	Block* block = getBlockByBlockId(block_id);
	LLNode* list = block->attributes.head;
	while (list != nullptr)
	{
		char* name = list->Data.GetName();
		if (name == nullptr) continue;
		if (strcmp(name, nameOfAttribute) == 0)
		{
			return list->Data.GetContent();
		}
		list = list->next;
	}
	return nullptr;
}
int Engine::getNumberOfAttributesNamed(const char* nameOfAttribute)
{
	if (nameOfAttribute == nullptr) return 0;
	DLLNode* ptr = this->DLList.head;
	if (ptr == nullptr) return 0;
	int n = 0;
	for (; ptr->next != nullptr; ptr = ptr->next)
	{
		for (int i = 0; i < NodeSize; i++)
		{
			LLNode* attributes = ptr->Data[i].attributes.head;
			for (; attributes != nullptr; attributes = attributes->next)
			{
				char* name = attributes->Data.GetName();
				if (name == nullptr) break;
				if (strcmp(name, nameOfAttribute) == 0) n++;
			}
		}
	}
	return 0;
}
int Engine::getNumberOfSelectorsNamed(const char* nameOfSelector)
{
	if (nameOfSelector == nullptr) return 0;
	DLLNode* ptr = this->DLList.head;
	if (ptr == nullptr) return 0;
	int n = 0;
	for (; ptr->next != nullptr; ptr = ptr->next)
	{
		for (int i = 0; i < NodeSize; i++)
		{
			LLNode* attributes = ptr->Data[i].attributes.head;
			for (; attributes != nullptr; attributes = attributes->next)
			{
				char* name = attributes->Data.GetName();
				if (name == nullptr) break;
				if (strcmp(name, nameOfSelector) == 0) n++;
			}
		}
	}
	return 0;
}
char* Engine::getContentOfAttributeBySelector(const char* nameOfSelector, const char* nameOfAttribute)
{
	if (nameOfSelector == nullptr || nameOfAttribute == nullptr) return nullptr;
	DLLNode* ptr = this->DLList.head;
	if (ptr == nullptr) return nullptr;
	for (; ptr->next != nullptr; ptr = ptr->next)
	{
	}
	for (; ptr->prev != nullptr; ptr = ptr->prev)
	{
		for (int i = NodeSize - 1; i >= 0; i--)
		{
			LLNode* selectors = ptr->Data[i].selectors.head;
			for (; selectors != nullptr; selectors = selectors->next)
			{
				char* name = selectors->Data.GetName();
				if (name == nullptr) break;
				if (strcmp(name, nameOfSelector) == 0)
				{
					LLNode* attributes = ptr->Data[i].attributes.head;
					for (; attributes != nullptr; attributes = attributes->next)
					{
						char* content = attributes->Data.GetContent();
						if (content == nullptr) break;
						if (strcmp(content, nameOfAttribute) == 0)
						{
							return content;
						}
					}
				}
			}
		}
	}
	return nullptr;
}
template <class T>
void freePtr(T** ptr)
{
	if (ptr != nullptr)
	{
		if (*ptr != nullptr)
		{
			delete *ptr;
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
		int l = str.getLength()-1;
		char* strTab = str.getStr();
		for (int i = 1; i <= l; i++)
		{
			sum += (strTab[i-1]-'0') * pow(10, l - i);
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

void Engine::handleCommand(String* arg)
{
	if (arg == nullptr) return;
	if (arg[FIRST].isNumber()) // i,X,X
	{
		int blockNumber = strToNumber(arg[FIRST]);
		if (arg[SECOND] == COMMAND_SELECTOR_SIGN) // i,S,X
		{
			if (arg[THIRD] == COMMAND_ASK_SIGN) // i,S,?
			{
				cout << getNumberOfSelectorsByBlockId(blockNumber) << EOL;
			}
		}
		else if (arg[SECOND] == COMMAND_ATTRIBUTE_SIGN) // i,A,X
		{
			if (arg[THIRD] == COMMAND_ASK_SIGN) // i,A,?
			{
				cout << getNumberOfAttributesByBlockId(blockNumber) << EOL;
			}
		}
	}
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
	while (scanf_s("%c", &ch) != EOF)
	{
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
						freePtr<Block>(&tempBlock);
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
					freePtr<Block>(&tempBlock);
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
				cout << getNumberOfBlocks() << EOL;
				text.clear();
				continue;
			}
			if (ch == EOL && l >= 1)
			{
				String arg[] = { "","","" };
				String* currentArg=arg;
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