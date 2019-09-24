#ifndef CIRCUIT_CIRCUIT_H
#define CIRCUIT_CIRCUIT_H

#include<bits/stdc++.h>
#include <vector>

class Component {
public:
    std::string name = "";
    bool val = false;
    std::vector<Component*> vec_cones;
    int length_min_path = INT_MAX, length_max_path = INT_MIN;
    std::string min_path, max_path, min_elem, max_elem;
    virtual bool evaluate() = 0;
    virtual void update_val(bool value){value = val;}
    virtual std::string logic_cones(){ return "";}
};


#endif //CIRCUIT_CIRCUIT_H
