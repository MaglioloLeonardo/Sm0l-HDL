#define BOOL_STR(b) (b?"1":"0")

#include<bits/stdc++.h>

typedef struct Node{
    string label;
    struct Node *left;
    struct Node *right;
}Node_Tree;
string print_tree(Node_Tree* node);

Boolean_Translator::Boolean_Translator(string exp, Components_List* inputs, Components_List* outputs, Components_List* flip_flop_list, bool* clk) {
    this->exp = exp;
    this->inputs = inputs;
    this->outputs = outputs;
    this->flip_flop_list = flip_flop_list;
    this->clk = clk;

    flip_flop = nullptr;
    output = nullptr;
}

bool Boolean_Translator::evaluate(){
    string temp_token, parsed;
    parsed = substitute(substitute(exp, ')' , " ) "), '(' , " ( ");
    set_token(&list_token, parsed, ' ');
    return S().first;
}


//PARSER FUNCTIONS____________________________________
pair<bool, Node_Tree*> Boolean_Translator::S(){
    pair<bool, Node_Tree*> p; p.second = nullptr;
    //cout <<  "S() with token:" << read_syntax() << endl;
    if(read() == "assign"){
        index++;
        O();
        if(read() != "=")error();
        index++;
        p = I();
        output->val = p.first;

    }else if(is_flipflop(read())){
        if(flip_flop_list->is_present(read())){
            flip_flop = flip_flop_list->is_present(read());
        }else{
            flip_flop = new Flip_Flop(read(), false, clk);
            flip_flop_list->add_elem(read(), flip_flop);
        }
        index++;
        if(read() != "=")error();
        index++;
        p = I();
        flip_flop->update_val(p.first);
    }else error();

    insert_min_max(p.second);

    return p;
}

pair<bool, Node_Tree*> Boolean_Translator::I(){
    pair<bool, Node_Tree*> p; p.second = nullptr;
    if(read() == "NOT" || is_id(read()) || read() == "(" ){
        pair<bool, Node_Tree*> H_pair = H();
        p = I1(H_pair.first, H_pair.second);
    }else error();
    return p;
}

pair<bool, Node_Tree*> Boolean_Translator::I1(bool I1_prec, Node_Tree* I1_node){
    pair<bool, Node_Tree*> p; p.second = nullptr;
    Node_Tree *temp = new Node_Tree; temp->left = nullptr; temp->right = nullptr;
    if(read() == "NOR"){
        index++;
        pair<bool, Node_Tree*> H_pair = H();
        temp->label = "NOR"; temp->left = H_pair.second; temp->right = I1_node;
        p = I1(!(I1_prec || H_pair.first), temp);
    }else if(read() == "" || read() == ")"){
        p.first = I1_prec;
        p.second = I1_node;
    }else error();
    return p;
}

pair<bool, Node_Tree*> Boolean_Translator::H(){
    pair<bool, Node_Tree*> p; p.second = nullptr;
    if(read() == "NOT" || is_id(read()) || read() == "(" ){
        pair<bool, Node_Tree*> E_pair = E();
        p = H1(E_pair.first, E_pair.second);
    }else error();
    return p;
}

pair<bool, Node_Tree*> Boolean_Translator::H1(bool H1_prec, Node_Tree* H1_node){
    pair<bool, Node_Tree*> p; p.second = nullptr;
    Node_Tree *temp = new Node_Tree; temp->left = nullptr; temp->right = nullptr;
    if(read() == "XOR"){
        index++;
        pair<bool, Node_Tree*> E_pair = E();
        temp->label = "XOR"; temp->left = E_pair.second; temp->right = H1_node;
        p = H1(H1_prec ^ E_pair.first, temp);
    }else if(read() == "NOR" || read() == "" || read() == ")"){
        p.first = H1_prec;
        p.second = H1_node;
    }else error();
    return p;
}

pair<bool, Node_Tree*> Boolean_Translator::E(){
    pair<bool, Node_Tree*> p; p.second = nullptr;
    if(read() == "NOT" || is_id(read()) || read() == "(" ){
        pair<bool, Node_Tree*> G_pair = G();
        p = E1(G_pair.first, G_pair.second);
    }else error();
    return p;
}

pair<bool, Node_Tree*> Boolean_Translator::E1(bool E1_prec, Node_Tree* E1_node){
    pair<bool, Node_Tree*> p; p.second = nullptr;
    Node_Tree *temp = new Node_Tree; temp->left = nullptr; temp->right = nullptr;
    if(read() == "OR"){
        index++;
        pair<bool, Node_Tree*> G_pair = G();
        temp->label = "OR"; temp->left = G_pair.second; temp->right = E1_node;
        p = E1(E1_prec || G_pair.first, temp);
    }else if(read() == "XOR" || read() == "NOR" || read() == "" || read() == ")"){
        p.first = E1_prec;
        p.second = E1_node;
    }else error();
    return p;
}

pair<bool, Node_Tree*> Boolean_Translator::G(){
    pair<bool, Node_Tree*> p; p.second = nullptr;
    if(read() == "NOT" || is_id(read()) || read() == "(" ){
        pair<bool, Node_Tree*> T_pair = T();
        p = G1(T_pair.first, T_pair.second);
    }else error();
    return p;
}

pair<bool, Node_Tree*> Boolean_Translator::G1(bool G1_prec, Node_Tree* G1_node){
    pair<bool, Node_Tree*> p; p.second = nullptr;
    Node_Tree *temp = new Node_Tree; temp->left = nullptr; temp->right = nullptr;
    if(read() == "NAND"){
        index++;
        pair<bool, Node_Tree*> T_pair = T();
        temp->label = "NAND"; temp->left = T_pair.second; temp->right = G1_node;
        p = G1(!(G1_prec && T_pair.first), temp);
    }else if(read() == "OR" || read() == "XOR" || read() == "NOR" || read() == "" || read() == ")"){
        p.first = G1_prec;
        p.second = G1_node;
    }else error();
    return p;
}

pair<bool, Node_Tree*> Boolean_Translator::T(){
    pair<bool, Node_Tree*> p; p.second = nullptr;
    if(read() == "NOT" || is_id(read()) || read() == "(" ) {
        pair<bool, Node_Tree*> F_pair = F();
        p = T1(F_pair.first, F_pair.second);
    } else error();
    return p;
}

pair<bool, Node_Tree*> Boolean_Translator::T1(bool T1_prec, Node_Tree* T1_node){
    pair<bool, Node_Tree*> p; p.second = nullptr;
    Node_Tree *temp = new Node_Tree; temp->left = nullptr; temp->right = nullptr;
    if(read() == "AND"){
        index++;
        pair<bool, Node_Tree*> F_pair = F();
        temp->label = "AND"; temp->left = F_pair.second; temp->right = T1_node;
        p = T1(T1_prec && F_pair.first, temp);
    }else if(read() == "NAND" || read() == "OR" || read() == "XOR" || read() == "NOR" || read() == "" || read() == ")"){
        p.first = T1_prec;
        p.second = T1_node;
    }else {
        cout <<  "READ:" << read() << endl;
        error();
    }
    return p;
}

pair<bool, Node_Tree*> Boolean_Translator::F(){
    pair<bool, Node_Tree*> p; p.second = nullptr;
    if(read() == "NOT" || is_id(read()) || read() == "(" ) {
        pair<bool, Node_Tree*> N_pair = N();
        if(N_pair.first == 1){
            p = F1();
            if(p.second != nullptr){
                Node_Tree *temp = new Node_Tree, *to_attach = new Node_Tree; to_attach->left = nullptr; to_attach->right = nullptr;
                temp->label = "NOT"; to_attach->label = "-1";  //se il nodo contiene -1 l'algoritmo di ricerca deve ignorarlo
                temp->left = p.second; temp->right = to_attach;
                p.second = temp;
            }
        }else p = F1();

        if(N_pair.first == 1)
            p.first = !p.first;
    }else error();
    return p;
}

pair<bool, Node_Tree*> Boolean_Translator::F1(){
    pair<bool, Node_Tree*> p; p.second = nullptr;
    if(read() == "("){
        index++;
        p = I();
        if(read() != ")")error();
        index++;
    }else p = C();
    return p;
}
pair<bool, Node_Tree*> Boolean_Translator::N(){
    pair<bool, Node_Tree*> p; p.second = nullptr;
    if(read() == "NOT"){
        index++;
        p.first = true;
    }else if(read() == "(" || is_id(read())){
        p.first = false;
    }else {
        error();
    }
    return p;
}

pair<bool, Node_Tree*> Boolean_Translator::C(){
    pair<bool, Node_Tree*> p; p.second = nullptr;
    Node_Tree *node = new Node_Tree; node->left = nullptr; node->right = nullptr;
    Component* input = inputs->is_present(read());
    Component* ff = flip_flop_list->is_present(read());

    if(input != nullptr){
        if(output != nullptr && is_present(output->vec_cones, read()) == nullptr){
            output->vec_cones.push_back(input);
        }
        p.first = input->evaluate();
        node->label = read();
        p.second = node;
        index++;
        return p;
    }else if(ff != nullptr && ff != flip_flop){
        if(output != nullptr && is_present(output->vec_cones, read()) == nullptr){
            output->vec_cones.push_back(ff);
        }
        p.first = ff->evaluate();
        node->label = read();
        p.second = node;
        index++;
        return p;
    }else{
        cout << "ERROR(Sintax on circuit_file): \"" << read() << "\" is not a valid input."  << endl;
        exit(1);
        return p;
    }

}

bool Boolean_Translator::O(){
    output = outputs->is_present(read());
    if(output != nullptr){
        out = read();
        index++;
    }else {
        cout << "ERROR(Sintax on circuit_file): \"" << read() << "\" is not a valid output."  << endl;
        exit(1);
    }
    return true;
}

string Boolean_Translator::read(){
    if(index < list_token.size()){
        return list_token.at(index);
    }else return "";
}

bool Boolean_Translator::is_id(string str){
    if(!is_operator(str) && read() != "="){
        return true;
    }else return false;
}

void Boolean_Translator::error(){
    cout <<  "\n\nERROR with token:" << read() << endl;
    exit(1);
}

Component* Boolean_Translator::is_present(vector <Component*> vec, string name){
    for (Component* cir : vec) {
        if (cir->name == name)
            return cir;
    }
    return nullptr;
}

string print_tree(Node_Tree* node){
    if(node == nullptr)return  "";
    string result1, result2;
    if(node->left != nullptr)result1 = print_tree(node->left);
    if(node->right != nullptr)result1 = print_tree(node->right);
    return  "{" + result1 + "| " + node->label + " |" + result2 + "}";
}

pair<int, string> Boolean_Translator::min_max_branch(Node_Tree* node, int depth, string mode){
    pair<int, string> p; assert(mode == "max" || mode == "min");
    Component *input = inputs->is_present(node->label);
    Component *ff = flip_flop_list->is_present(node->label);
    assert(node != nullptr);
    if(node->right != nullptr && node->left != nullptr){
        int to_add;

        if(node->label == "-1"){
            if(mode == "min"){
                to_add = INT_MAX;
            }else to_add = INT_MIN;
        }else to_add = 1;

        pair<int, string> result1 = min_max_branch(node->left, depth + to_add, mode);
        pair<int, string> result2 = min_max_branch(node->right, depth + to_add, mode);


        if(result2.first > result1.first){
            if(mode == "min")
                p = result1;
            else p = result2;
        }else {
            if(mode == "min")
                p = result2;
            else p = result1;
        }
        return p;
    }else{
        int to_add = 0;
        if(node->label == "-1") {
            if (mode == "min")
                 p.first = INT_MAX;
            else p.first = INT_MIN;
        }else if(input != nullptr){
            if(mode == "min" && input->length_min_path != INT_MAX){
                to_add = input->length_min_path;
            }else if(mode == "max" && input->length_max_path != INT_MIN){
                to_add = input->length_max_path;
            }
            p.first = depth + to_add;
        }else if(ff != nullptr){
            if(mode == "min" && ff->length_min_path != INT_MAX){
                to_add = ff->length_min_path;
            }else if(mode == "max" && ff->length_max_path != INT_MIN){
                to_add = ff->length_max_path;
            }
            p.first = depth + to_add;
        }else p.first = depth;
        p.second = node->label;
        return p;
    }
}

void Boolean_Translator::insert_min_max(Node_Tree *node){
    assert(node != nullptr);
    pair<int, string> min_result = min_max_branch(node, 0, "min");
    pair<int, string> max_result = min_max_branch(node, 0, "max");

    Component *out_min_max, *in_min, *in_max;
    out_min_max= outputs->is_present(out);
    if(out_min_max == nullptr)out_min_max = flip_flop;

    in_min= inputs->is_present(min_result.second);
    if(in_min == nullptr)in_min= flip_flop_list->is_present(min_result.second);

    in_max= inputs->is_present(max_result.second);
    if(in_max == nullptr)in_max= flip_flop_list->is_present(max_result.second);

    if(in_min != nullptr && in_max != nullptr && out_min_max != nullptr);


    out_min_max->length_min_path = min_result.first; out_min_max->min_elem = in_min->min_elem;
    out_min_max->length_max_path = max_result.first; out_min_max->max_elem = in_max->max_elem;

    if(is_flipflop(out_min_max->name)){
        out_min_max->length_min_path += 1;
        out_min_max->length_max_path += 1;
    }

    out_min_max->min_path = "<input: " + in_min->min_elem + ", output: " + out + " , len: " + to_string(out_min_max->length_min_path) + ">";
    out_min_max->max_path = "<input: " + in_max->min_elem + ", output: " + out + " , len: " + to_string(out_min_max->length_max_path) + ">";
}



