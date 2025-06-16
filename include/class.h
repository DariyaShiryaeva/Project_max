#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

class Unusual {
private:
    std::string _expression;
public:
    void setExpression(std::string str);
    void check();
    int calculate();
};

// ����
template <typename T>
class Node {
public:
    T Data;
    Node<T>* Next;
    Node(const T& val) : Data(val), Next(nullptr) {}
};

// ��������� ����
template <typename T>
class Stack {
private:
    Node<T>* topNode;
public:
    Stack() : topNode(nullptr) {}

    //������� ���������� � ����
    void push(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->Next = topNode;
        topNode = newNode;
    }

    //������� �������� �� �����
    void pop() {
        Node<T>* temp = topNode;
        topNode = topNode->Next;
        delete temp;
    }

    //������� �������� �������
    T top() const {
        return topNode->Data;
    }

    //������� ������ �� �������
    T& topRef() {
        return topNode->Data;
    }

    //�������� �������
    bool empty() const {
        return topNode == nullptr;
    }

    //������ �����
    int size() const {
        int count = 0;
        Node<T>* current = topNode;
        while (current) {
            count++;
            current = current->Next;
        }
        return count;
    }
};
