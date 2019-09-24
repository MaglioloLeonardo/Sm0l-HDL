#include "Flip_Flop.h"
#include <vector>

using namespace std;

Flip_Flop::Flip_Flop(string name, bool val, bool *clk){
    this->name = name;
    this->val = val;
    this->clk = clk;
    this->min_elem = name;
    this->max_elem = name;
    prev_clk = false;

}

bool Flip_Flop::evaluate() {return val;}

void Flip_Flop::update_val(bool val){
    if(*clk != prev_clk){
        this->val = val;
        prev_clk = *clk;
    }
}
string Flip_Flop::logic_cones(){
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





