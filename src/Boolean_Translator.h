#ifndef CIRCUITI_BOOLEAN_TRANSLATOR_H
#define CIRCUITI_BOOLEAN_TRANSLATOR_H

#include<string.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>


#include "Parser_Helper.cpp"
#include "Boolean_Translator.h"
#include "Flip_Flop.h"

using namespace std;

class Boolean_Translator {
private:
    typedef struct Node Node_Tree;

    string exp, out = "";
    bool* clk;
    int index = 0;
    vector<string> list_token;

    Components_List* inputs;
    Components_List* outputs;
    Components_List* flip_flop_list;
    Component* output;
    Component* flip_flop;


    pair<bool, Node_Tree*> S();
    pair<bool, Node_Tree*> I();
    pair<bool, Node_Tree*> I1(bool I1_prec, Node_Tree* I1_node);
    pair<bool, Node_Tree*> H();
    pair<bool, Node_Tree*> H1(bool H1_prec, Node_Tree* H1_node);
    pair<bool, Node_Tree*> E();
    pair<bool, Node_Tree*> E1(bool E1_prec, Node_Tree* E1_node);
    pair<bool, Node_Tree*> G();
    pair<bool, Node_Tree*> G1(bool G1_prec, Node_Tree* G1_node);
    pair<bool, Node_Tree*> T();
    pair<bool, Node_Tree*> T1(bool T1_prec, Node_Tree* T1_node);
    pair<bool, Node_Tree*> F();
    pair<bool, Node_Tree*> F1();
    pair<bool, Node_Tree*> N();
    pair<bool, Node_Tree*> C();

    bool O();
    string read();
    bool is_id(string str);
    void error();
    Component* is_present(vector <Component*> vec, std::string name);
    void insert_min_max(Node_Tree *node);
    pair<int, string> min_max_branch(Node_Tree *node, int depth, string mode);

public:
    Boolean_Translator(string exp, Components_List* inputs, Components_List* outputs, Components_List* flip_flop_list, bool* clk);
    bool evaluate();

};


#endif //CIRCUITI_BOOLEAN_TRANSLATOR_H
