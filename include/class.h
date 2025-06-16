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

// Узлы
template <typename T>
class Node {
public:
    T Data;
    Node<T>* Next;
    Node(const T& val) : Data(val), Next(nullptr) {}
};

// Шаблонный стек
template <typename T>
class Stack {
private:
    Node<T>* topNode;
public:
    Stack() : topNode(nullptr) {}

    //функция добавления в стек
    void push(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->Next = topNode;
        topNode = newNode;
    }

    //функция удаления из стека
    void pop() {
        Node<T>* temp = topNode;
        topNode = topNode->Next;
        delete temp;
    }

    //возврат значения вершины
    T top() const {
        return topNode->Data;
    }

    //возврат ссылки на вершину
    T& topRef() {
        return topNode->Data;
    }

    //проверка пустоты
    bool empty() const {
        return topNode == nullptr;
    }

    //размер стека
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
