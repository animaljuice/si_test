#pragma once

#include <vector>
#include <string>
#include <cstdio>

// ��������� ListNode �������������� ������
struct ListNode {
    ListNode* prev;
    ListNode* next;
    ListNode* rand; // ��������� �� ������������ ������� ������� ������ ���� NULL
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

    void Serialize(FILE* file);  // ���������� � ���� (���� ������ � ������� fopen(path, "wb"))
    void Deserialize(FILE* file);  // �������� �� ����� (���� ������ � ������� fopen(path, "rb"))

private:
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    int       count = 0;
};


