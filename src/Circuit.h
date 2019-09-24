#ifndef CIRCUITI_GRAPH_GEN_H
#define CIRCUITI_GRAPH_GEN_H

#include<string.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

#include "Component.h"
#include "Flip_Flop.h"
#include "In_Out.h"
#include "In_Out.cpp"
#include "Components_List.h"

using namespace std;

class Circuit {
private:
    string exp, path_circuit, name, input_string, name_instance_circuit;
    bool is_initialized = false, is_subcircuit = false;
    bool *clk;
    vector<string> input_list_token, instance_token,  file_list_token;
    vector<Circuit*> circuit_list;
    map<string, string> name_associator;
    Components_List *inputs, *outputs, *flip_flop_list, *instance_list, *instance_inputs , *instance_outputs;

    int index_syntax = 0, index_instance = 0, index_inputs = 0;

    void initialize();
    void declaration_check();
    void lex_input();
    void body_evaluator();
    bool instance_evaluator(string str);

    void instance_E();
    void instance_T();
    void instance_T_I();
    void instance_T_O();

    void syntax_E();
    void syntax_E1();
    void syntax_O();
    void syntax_T_I();
    void syntax_T_O();
    void syntax_F();

    string read_syntax();
    string read_next_syntax();
    string read_instance();
    string read_next_instance(int pos);
    pair<string, string> to_associate(Component* temp);
    void add_input();
    void add_output();
    bool is_id(string str);
    void error_syntax();
    void error_instance();



public:
    Circuit(string path_circuit_folder, string name, Components_List *inputs, Components_List *outputs,
            bool* clk);

    void evaluate(string input_string);

    void evaluate(Components_List* input_to_cpy);

    string get_name();

};

#endif //CIRCUITI_GRAPH_GEN_H
