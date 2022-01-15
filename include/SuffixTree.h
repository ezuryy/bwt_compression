#ifndef MY_PROJECT_SUFFIXTREE_H
#define MY_PROJECT_SUFFIXTREE_H

#include "variables.h"

class AdoptedSuffixTree {

    struct Node {
        struct Edge {
            Node* node{};
            int bwt_index = -1;
            int from = 0;
            int to = 0;
        };
        // красно-чёрное дерево, ребра сортируются по первому значению uchar
        map<uchar, Edge> edges;
    };
    Node* root_;
    ustring str_;
    void addSuffix(const int& suffix_begin_index);
public:
    AdoptedSuffixTree() : root_(nullptr) {}
    explicit AdoptedSuffixTree(ustring& input);
    ~AdoptedSuffixTree();
    void createTree(ustring& input);
    pair<ustring, int> BWT_encode_optimized();
};

#endif //MY_PROJECT_SUFFIXTREE_H
