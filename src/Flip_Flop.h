#ifndef FLIP_FLOP_H
#define FLIP_FLOP_H

#include<string>
#include "Component.h"


class Flip_Flop: public Component {
    bool prev_clk;
    bool *clk;
public:
    Flip_Flop(std::string name, bool val, bool *clk);
    bool evaluate();
    void update_val(bool val);
    std::string logic_cones();



};
#endif //CIRCUITI_SIMPLE_CIRCUIT_H
