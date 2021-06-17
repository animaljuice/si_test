#include "List.h"
#include <functional>
#include <map>
#include <iostream>

#define VALID_READ_CHECK(x) if(!x) break;

void List::initList(const InitStruct& initStruct)
{
	clear();

	if (initStruct.size() == 0) return;

	std::vector<ListNode*> NodesPool(initStruct.size());
	for (size_t nodeIndex = 0; nodeIndex < NodesPool.size(); nodeIndex++)
	{
		NodesPool[nodeIndex] = new ListNode;
		NodesPool[nodeIndex]->data = initStruct[nodeIndex].first;
		NodesPool[nodeIndex]->next = nullptr;
		NodesPool[nodeIndex]->prev = nullptr;
		NodesPool[nodeIndex]->rand = nullptr;
	}

	head = NodesPool.front();
	tail = NodesPool.back();
	count = NodesPool.size();
	for (size_t nodeIndex = 0; nodeIndex < NodesPool.size(); nodeIndex++)
	{
		if (nodeIndex == 0)
		{
			NodesPool[nodeIndex]->next = NodesPool[nodeIndex + 1];
		}
		else if (nodeIndex == NodesPool.size() - 1)
		{
			NodesPool[nodeIndex]->prev = NodesPool[nodeIndex - 1];
		}
		else
		{
			NodesPool[nodeIndex]->next = NodesPool[nodeIndex + 1];
			NodesPool[nodeIndex]->prev = NodesPool[nodeIndex - 1];
		}
		if (initStruct[nodeIndex].second >= 0)
		{
			NodesPool[nodeIndex]->rand = NodesPool[initStruct[nodeIndex].second];
		}
	}
}

List::List(const std::vector<std::string>& initStringList)
{
	InitStruct initArray(initStringList.size());
	for (size_t strIndex = 0; strIndex < initStringList.size(); strIndex++)
	{
		// 50 / 50 будет ли указатель на случайный нод
		initArray[strIndex] = std::make_pair(initStringList[strIndex], (rand() % 2)?rand() % initStringList.size():-1);
	}

	initList(initArray);
}

List::~List()
{
	clear();
}

void List::clear()
{
	ListNode* curNode = head;
	while (curNode)
	{
		auto nextNode = curNode->next;
		delete curNode;
		curNode = nextNode;
	}

	head = nullptr;
	tail = nullptr;
	count = 0;
}

void List::print()
{
	ListNode* curNode = head;
	while (curNode)
	{
		std::cout << curNode->data << "  " << (curNode->rand ? curNode->rand->data : std::string("null")) << std::endl;
		curNode = curNode->next;
	}
}

void List::Serialize(FILE* file)
{
	using indexType = int;
	std::map<ListNode*, indexType> randMap;
	randMap[nullptr] = -1;
	std::function<void(ListNode*, int)> makeRandMap;
	makeRandMap = [&makeRandMap, &randMap](ListNode* curNode, int curIndex)
	{
		if (!curNode) return;
		randMap[curNode] = curIndex;
		makeRandMap(curNode->next, ++curIndex);
	};

	makeRandMap(head, 0);

	auto curNode = head;
	while (curNode)
	{
		auto strSize = curNode->data.size();
		fwrite(&strSize, sizeof(strSize), 1, file);
		fwrite(curNode->data.data(), sizeof(std::string::value_type), curNode->data.size(), file);
		fwrite(&randMap[curNode->rand], sizeof(indexType), 1, file);
		curNode = curNode->next;
	}
}

void List::Deserialize(FILE* file)
{
	InitStruct initArray;

	while (true)
	{
		std::pair<std::string, int> initArrayElement;

		std::string::size_type curStrSize;
		VALID_READ_CHECK(fread(&curStrSize, sizeof(curStrSize), 1, file));
		initArrayElement.first.resize(curStrSize);
		VALID_READ_CHECK(fread(&initArrayElement.first.front(), sizeof(std::string::value_type), curStrSize, file));
		VALID_READ_CHECK(fread(&initArrayElement.second, sizeof(initArrayElement.second), 1, file));

		initArray.push_back(initArrayElement);
	}
	
	initList(initArray);
}
