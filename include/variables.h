#ifndef MY_PROJECT_VARIABLES_H
#define MY_PROJECT_VARIABLES_H

#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <stack>

using std::pair;
using std::string;
using std::unordered_map;
using std::vector;
using std::ifstream;
using std::ofstream;

typedef unsigned char uchar;

// Количество битов в коде
#define BITS 12
// Максимальное значение кода (2 ^ 12 - 1)
#define MAX_CODE ((1 << BITS) - 1)
// Размер алфавита, является также кодом конца потока
#define ALPHABET_SIZE 256
// Код первой добавляемой в словарь фразы после записи символов алфавита
#define FIRST_CODE 257
// Символ, который мы считаем не появляющимся. Служит символом окончания строки в суффиксном дереве
#define END_SYMBOL static_cast<uchar>(255)

#endif //MY_PROJECT_VARIABLES_H
