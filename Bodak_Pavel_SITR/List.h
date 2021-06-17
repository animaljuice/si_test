#pragma once

#include <vector>
#include <string>
#include <cstdio>

// структуру ListNode модифицировать нельзя
struct ListNode {
    ListNode* prev;
    ListNode* next;
    ListNode* rand; // указатель на произвольный элемент данного списка либо NULL
    std::string     data;
};

class List {

    using InitStruct = std::vector<std::pair<std::string, int>>;
    void initList(const InitStruct &initStruct);

public:
    List() {}
    List(const std::vector<std::string> &initStringList);
    ~List();

    void clear();
    void print();

    void Serialize(FILE* file);  // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
    void Deserialize(FILE* file);  // загрузка из файла (файл открыт с помощью fopen(path, "rb"))

private:
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    int       count = 0;
};


