#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

class Check {
public:
    static std::string check();
};

class Calculate {
public:
    static int calculate(std::string str);
};

// ����
template <typename T>
class Node {
private:
    T _Data;
    Node<T>* _Next;

public:
    Node(const T& val) : _Data(val), _Next(nullptr) {}
    void setData(const T& val) {
        _Data = val;
    }

    T getData() const {
        return _Data;
    }

    T& getDataRef() {
        return _Data;
    }

    void setNext(Node<T>* next) {
        _Next = next;
    }

    Node<T>* getNext() const {
        return _Next;
    }
};


// ��������� ����
template <typename T>
class Stack {
private:
    Node<T>* _topNode;
public:
    Stack() : _topNode(nullptr) {}

    //������� ���������� � ����
    void push(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->setNext(_topNode);
        _topNode = newNode;
    }

    //������� �������� �� �����
    void pop() {
        if (_topNode) {
            Node<T>* temp = _topNode;
            _topNode = _topNode->getNext();
            delete temp;
        }
    }

    //������� �������� �������
    T top() const {
        return _topNode->getData();
    }

    //������� ������ �� �������
    T& topRef() {
        return _topNode->getDataRef();
    }

    //�������� �������
    bool empty() const {
        return _topNode == nullptr;
    }

    //������ �����
    int size() const {
        int count = 0;
        Node<T>* current = _topNode;
        while (current) {
            count++;
            current = current->getNext();
        }
        return count;
    }
};
