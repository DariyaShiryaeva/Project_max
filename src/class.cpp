#include <iostream>
#include <cctype>
#include "../include/class.h"
#include <string>
#include <algorithm>
#include <vector>
#include <stdexcept>

//Проверка корректности ввода
std::string Check::check() {
    setlocale(LC_ALL, "ru");
    bool flag = false;

    // Очистка буфера ввода перед началом
    std::cin.clear();
    std::string str;
    do {
        std::cout << "\n   Ваше выражение: ";
        std::getline(std::cin, str); // Читаем всю строку
        std::cout << std::endl;

        // Проверка на пустое выражение
        bool ifempty = true;
        for (int i = 0; i < str.size(); i++)
            if (str[i] != ' ')
                ifempty = false;
        if (ifempty) {
            std::cout << "  В пустом выражении вычислять нечего. Попробуйте ввести выражение, содержащее операции -\n" <<
                "   поиск минимума(обозначается m(<число1>, <число2>)) и поиск максимума(обозначается М(<число1>, <число2>)).\n" <<
                "   Операции могут быть вложенными\n";
            continue;
        }

        // Проверка на посторонние символы
        const std::string possible = "Mm(), 1234567890";
        bool invalid = false;
        for (char ch : str) {
            if (possible.find(ch) == std::string::npos) {
                invalid = true;
                break;
            }
        }
        if (invalid) {
            std::cout << "  Ошибка! Присутствуют посторонние символы. Пожалуйста, введите выражение заново.\n";
            continue;
        }

        // Проверка сбалансированности скобок
        int balance = 0;
        for (char ch : str) {
            if (ch == '(')
                balance++;
            else
                if (ch == ')')
                    balance--;
            if (balance < 0)
                break;
        }
        if (balance != 0) {
            std::cout << "  Ошибка! Несбалансированы скобки. Пожалуйста, введите выражение заново.\n";
            continue;
        }

        //Проверка соответствия количества скобок количеству операций
        int oper = 0; //количество операций 
        int par = 0; // количество скобок при них
        for (char ch : str) {
            if (ch == '(' || ch == ')')
                par++;
            if (ch == 'm' || ch == 'M')
                oper++;
        }
        if (oper * 2 != par) {
            std::cout << "  Ошибка! Количество скобок не соответствует количеству операций." <<
                " Пожалуйста, введите выражение заново.\n";
            continue;
        }

        // Проверка, что нет операции без аргументов
        if (str.find("()") != std::string::npos) {
            std::cout << "  Ошибка! Найдена операция без аргументов. Пожалуйста, введите выражение заново.\n";
            continue;
        }

        // Проверка количества аргументов
        Stack<int> argStack;
        bool valid = true;

        for (size_t i = 0; i < str.size(); ++i) {
            char c = str[i];

            if ((c == 'm' || c == 'M') && (i + 1 < str.size() && str[i + 1] == '(')) {
                argStack.push(0);
                i++; // Пропускаем '('
            }
            else if (c == ',' && !argStack.empty()) {
                argStack.topRef()++;
            }
            else if (c == ')') {
                if (argStack.empty()) {
                    valid = false;
                    break;
                }
                argStack.topRef()++;
                if (argStack.top() != 2) {
                    valid = false;
                    break;
                }
                argStack.pop();
            }
        }
        if (!valid) {
            std::cout << "  Ошибка! Количество аргументов в операции должно равняться двум. "
                << "    Пожалуйста, введите выражение заново.\n";
            continue;
        }
        flag = true;
    } while (!flag);
    return str;
}

int Calculate::calculate(std::string str) {
    Stack<int> nums;
    Stack<char> ops;
    int i = 0;
    size_t n = str.size();

    while (i < n) {
        if (str[i] == ' ') {
            i++;
            continue;
        }
        if (std::isdigit(str[i])) {
            int j = i;
            while (j < n && std::isdigit(str[j])) {
                j++;
            }
            int num = std::stoi(str.substr(i, j - i));
            nums.push(num);
            i = j;
        }
        else if (str[i] == 'm' || str[i] == 'M') {
            ops.push(str[i]);
            i++;
            if (i < n && str[i] == '(') {
                i++;
            }
        }
        else if (str[i] == ',') {
            i++;
        }
        else if (str[i] == ')') {
            int arg2 = nums.top(); nums.pop();
            int arg1 = nums.top(); nums.pop();
            char op = ops.top(); ops.pop();

            int res;
            if (op == 'm') {
                res = std::min(arg1, arg2);
            }
            else {
                res = std::max(arg1, arg2);
            }
            nums.push(res);
            i++;
        }
        else {
            i++;
        }
    }

    return nums.top();
}