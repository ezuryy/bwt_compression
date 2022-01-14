#ifndef MY_PROJECT_SUFFIXTREE_H
#define MY_PROJECT_SUFFIXTREE_H

#include "variables.h"

using std::vector;
using std::string;
using std::map;
using std::pair;
using std::queue;
using std::stack;
using std::cout;

typedef unsigned char uchar;

class AdoptedSuffixTree {

    struct Node {
        struct Edge {
            Node* node;
            int bwt_index = -1;
            vector<int> from_to;
        };
        // красно-чёрное дерево, ребра сортируются по первому значению uchar
        map<uchar, Edge> edges;
    };
    Node* root_;
    vector<uchar> str_;
    void addSuffix(const int& suffix_begin_index);
public:
    AdoptedSuffixTree() = default;
    ~AdoptedSuffixTree();
    void createTree(const string& input);
    pair<vector<uchar>, int> BWT_encode_optimized();
};



#endif //MY_PROJECT_SUFFIXTREE_H
