
#ifndef CIRCUITI_COMPONENTS_LIST_H
#define CIRCUITI_COMPONENTS_LIST_H

#include <list>
#include<string>
#include <iostream>

#include "Component.h"

class Components_List {
private:
    struct Node {
        std::string name;
        Component *component
        ;
    };
    std::list<Node> list;
public:
    //No constructor, let default constructor called

    void add_elem(std::string name, Component* component);
    Component* is_present(std::string name);
    int get_size();
    Component* get_last();
    Component* get_in_pos(int pos);
    void print_values();
    void print_stats();
    void test_print_list();
};




#endif //CIRCUITI_COMPONENTS_LIST_H
