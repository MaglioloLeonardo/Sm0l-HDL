#ifndef CIRCUITI_IN_OUT_H
#define CIRCUITI_IN_OUT_H

#include<string>
#include "Component.h"

class In_Out: public Component {
public:
    In_Out(std::string name, bool val);
    bool evaluate();
    std::string logic_cones();
};


#endif //CIRCUITI_IN_OUT_H
