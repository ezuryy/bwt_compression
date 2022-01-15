#include "SuffixTree.h"

AdoptedSuffixTree::AdoptedSuffixTree(ustring& input) : str_(input){
    root_ = new Node;
    str_.push_back(END_SYMBOL);
    root_->edges.insert({str_[0], {nullptr, 0, 0, static_cast<int>(str_.size())}});
    for (size_t i = 1; i < str_.size(); i++) {
        addSuffix(static_cast<int>(i));
    }
}

void AdoptedSuffixTree::addSuffix(const int& suffix_begin_index) {
    int suffix_compare_index = suffix_begin_index;
    Node *curr_node = root_;
    bool isFinished = false;
    // сверяем символы суффикса пока он не закончится или же пока не найдется несовпадения
    while (suffix_compare_index < static_cast<int>(str_.size()) && !isFinished) {
        // получаем индекс ребра, по которому нужно идти, сравнивая символы
        auto iterator_to_edge = curr_node->edges.find(str_[suffix_compare_index]);
        // если такого ребра нет, добавляем оставшуюся часть суффикса в виде нового ребра. Так появляется лист
        if (iterator_to_edge == curr_node->edges.end()) {
            curr_node->edges.insert({str_[suffix_compare_index], {nullptr, suffix_begin_index, suffix_compare_index, static_cast<int>(str_.size())}});
            break;
        }
        auto &edge_from = iterator_to_edge->second.from;
        auto &edge_to = iterator_to_edge->second.to;
        int edge_compare_index = edge_from;
        /* ребро для сравнения есть, значит пора пройтись по нему и сравнить с суффиксом. Прерываемся, если ребро/суффикс
         * закончились, или же было найдено несовпадение */
        for (; edge_compare_index < edge_to && suffix_compare_index < (int)str_.size() && edge_compare_index < (int)str_.size(); edge_compare_index++, suffix_compare_index++) {
            // найдено несовпадение - нужно поделить ребро
            if (str_[suffix_compare_index] != str_[edge_compare_index]) {
                // создаем новый узел
                Node *new_node = new Node();
                // старый узел мог ссылаться на какой-то другой, значит новый тоже должен, чтобы сохранить структуру
                Node* temp_node = iterator_to_edge->second.node;
                int prev_bwt_index = iterator_to_edge->second.bwt_index;
                new_node->edges.insert({str_[edge_compare_index], {temp_node, prev_bwt_index, edge_compare_index, edge_to}});
                // старый теперь ссылается на наш новый
                iterator_to_edge->second.node = new_node;
                iterator_to_edge->second.bwt_index = -1;
                // теперь метка старого узла изменилась - ребро идет до несовпадающего символа
                edge_to = edge_compare_index;
                // добавляем оставшуюся часть суффикса в новый узел
                new_node->edges.insert({str_[suffix_compare_index], {nullptr, suffix_begin_index, suffix_compare_index, static_cast<int>(str_.size())}});
                // говорим программе, что работа по добавлению суффикса завершена
                isFinished = true;
            }
        }
        // если ребро закончилось, нужно перейти к узлу, к которому ведёт данное ребро и повторить алгоритм
        curr_node = iterator_to_edge->second.node;
    }
}

void AdoptedSuffixTree::createTree(ustring& input) {
    root_ = new Node;
    str_ = input;
    str_ += END_SYMBOL;
    root_->edges.insert({str_[0], {nullptr, 0, 0, static_cast<int>(str_.size())}});
    for (size_t i = 1; i < str_.size(); i++) {
        addSuffix(static_cast<int>(i));
    }
}

AdoptedSuffixTree::~AdoptedSuffixTree() {
    queue<Node *> queue;
    // добавляем корень
    queue.push(root_);
    // пока очередь не пустая - есть узлы, которые нужно удалить
    while (!queue.empty()) {
        Node *curr_node = queue.front();
        // добавляем очередь всех детей
        for (auto& map_element : curr_node->edges) {
            if (map_element.second.node != nullptr) {
                queue.push(map_element.second.node);
            }
        }
        // очищаем массивы с ребрами, символами и следующими узлами
        curr_node->edges.clear();
        delete curr_node;
        // узел удален, убираем его из очереди
        queue.pop();
    }
}

pair<ustring, int> AdoptedSuffixTree::BWT_encode_optimized() {
    int coefficient = 0;
    ustring bwt_result;
    vector<int> answer;
    stack<pair<Node*, int>> s;
    s.push({root_, -1});
    while (!s.empty()) {
        Node* cur = s.top().first;
        int cur_index = s.top().second;
        s.pop();
        if (cur != nullptr) {
            for (auto rit = cur->edges.rbegin(); rit != cur->edges.rend(); rit++) {
                s.push({rit->second.node, rit->second.bwt_index});
            }
        }
        if (cur_index != -1) { // нашли лист
            int true_index = ((cur_index == 0) ? int(str_.size() - 1) : int(cur_index - 1));
            bwt_result += str_[true_index];
            answer.push_back(true_index);
            if (str_[true_index] == END_SYMBOL) {
                coefficient = true_index;
            }
        }
    }
    return {bwt_result, coefficient};
}
