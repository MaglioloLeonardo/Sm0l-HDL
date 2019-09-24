#include "In_Out.h"
#include "assert.h"
#include <vector>
using namespace std;

In_Out::In_Out(std::string name, bool val){
    this->name = name;
    this->val = val;
    this->min_elem = name;
    this->max_elem = name;
}

bool In_Out::evaluate() { return val;}

string In_Out::logic_cones(){
    string to_return = "{";
    bool toggle = false;
    for(Component* circuit : vec_cones){
        if(toggle == true)to_return += ", ";
        to_return += circuit->name;
        toggle = true;
    }
    to_return += "}";
    return to_return;
}