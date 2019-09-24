#include<bits/stdc++.h>
#include "Components_List.h"
#define BOOL_STR(b) (b?"1":"0")
    void Components_List::add_elem(std::string name, Component* component) {
        Node node; node.name = name; node.component = component;
        list.push_back(node);
    }

    Component* Components_List::is_present(std::string name){
        for (Node node : list) {
            if (node.name == name)return node.component;
        }
        return nullptr;
    }

    int Components_List::get_size(){ return list.size();}

    Component* Components_List::get_last(){ return list.back().component;}

    Component* Components_List::get_in_pos(int pos){
        int temp = 0;
        if(pos < 0 || pos >= list.size()){
            std::cout<<"Invalid pos in get_in_pos()"<<std::endl;
            exit(1);
        }
        for(std::list<Node>::iterator iter = list.begin(); iter != list.end(); iter++) {
            if(temp == pos)return iter->component;
            temp++;
        }
        return nullptr;
    }

    void Components_List::print_values() {
        std::string to_print;
        for(std::list<Node>::iterator iter = list.begin(); iter != list.end(); iter++){
            to_print += "Name: " + iter->name +" Value:" + BOOL_STR(iter->component->val) +  "\n";
        }
        std::cout << to_print << std::endl;
    }

    void Components_List::print_stats(){
        std::string to_print;
        int min = INT_MAX, max = INT_MIN;
        std::string path_min, path_max;
        for(std::list<Node>::iterator iter = list.begin(); iter != list.end(); iter++){
            to_print += "Name:" + iter->name + " Logic cone: " + iter->component->logic_cones() + "\n";

            if(iter->component->length_min_path < min){
                min = iter->component->length_min_path;
                path_min = iter->component->min_path;
            }else if(iter->component->length_min_path == min){
                path_min += "\n    " + iter->component->min_path;
            }

            if(iter->component->length_max_path > max){
                max = iter->component->length_max_path;
                path_max = iter->component->max_path;
            }else if(iter->component->length_max_path == max){
                path_max += "\n    " + iter->component->max_path;
            }

        }
        to_print += "\nMinimum circuit paths:\n    " + path_min + "\nMaximum circuit paths:\n    " + path_max + "\n";
        std::cout << to_print << std::endl;
    }

    void Components_List::test_print_list() {
        int counter = 0; std::string to_print, temp;
        for(std::list<Node>::iterator iter = list.begin(); iter != list.end(); iter++){
            to_print += "\n____________\nNode n:" + std::to_string(counter) + "\n";
            to_print += "Name:" + iter->name +"\nValue:" + BOOL_STR(iter->component->val) +  "\n";
            to_print += "Logic cones:" + iter->component->logic_cones() + "\n";
            to_print += "Min path:" + iter->component->min_path + " len:" + std::to_string(iter->component->length_min_path) +"\n";
            to_print += "Max path:" + iter->component->max_path + " len:" + std::to_string(iter->component->length_max_path) + "\n____________";
            counter++;
        }
        std::cout << "\n" + to_print << std::endl;
    }


