#include <assert.h>
#include "Circuit.h"
#include "Parser_Helper.cpp"
#include "Boolean_Translator.h"

Circuit::Circuit(string path_circuit, string name, Components_List *inputs, Components_List *outputs, bool *clk){
    assert(inputs != nullptr);
    this->path_circuit = path_circuit;
    this->name = name;
    this->input_string = input_string;
    this->inputs = inputs;
    this->outputs = outputs;
    this->clk = clk;
    flip_flop_list = new Components_List();
    exp = substitute(file_to_string(path_circuit + name + ".txt"), '\r', "");
}

string Circuit::get_name(){ return name;}

void Circuit::evaluate(string input_string){
    input_string = substitute(substitute(input_string, '\n', " "), '\r', " ");
    if(input_string == NULL_INPUT){is_subcircuit = true; initialize(); goto end;}

    this->input_string = input_string;
    lex_input();

    if(!is_initialized)initialize();
    //_____________________________________________________

    if(input_list_token.size() < inputs->get_size()){
        cout<< "INTERNAL ERROR: Invalid input file on component: " << path_circuit + name << endl;
        exit(1);
    }

    for(int i = 0; i < inputs->get_size(); i++){
        inputs->get_in_pos(i)->val = str_to_bool(input_list_token[i]);
    }

    end:
    body_evaluator();
}


void Circuit::evaluate(Components_List* input_to_cpy){
    is_subcircuit = true;
    if(is_initialized == false)initialize();

    for(int i = 0; i < input_to_cpy->get_size(); i++){
        Component *component = input_to_cpy->get_in_pos(i);
        Component *temp = inputs->is_present(component->name);
        if(temp == nullptr){
            cout<<"(subcircuit:" << name << ")ERROR: has been called by 'instance' with some invalid input names"<<endl;
            cout<<"Lable: " << component->name << endl;
            exit(1);
        }else{
            temp->val = component->val;
        }
    }

    body_evaluator();
}

void Circuit::initialize(){
        //Lexing declaration string
        string temp_token, parsed, after_declaration = "";

        for(int i = 0; i < exp.length(); i++){
            if(exp.at(i) == ','){
                parsed += " , ";
            }else if(exp.at(i) == '\n'){
                parsed += " \n ";
            }else{
                parsed += exp.at(i);
                if(exp.at(i) == ';'){
                    if(i+2 < exp.length())exp = exp.substr(i+2, exp.length()); //Body string
                    break;
                }
            }
        }

        set_token(&file_list_token, parsed, ' ');
        declaration_check();
        is_initialized = true;
    }


void Circuit::declaration_check(){
    if(read_syntax() == "module"){
        index_syntax++;
        if(read_syntax() == "(" || read_syntax() == ")" || read_syntax() == ";" or read_syntax() == "," ||
                read_syntax() == "module")
            error_syntax();
        index_syntax++;
        if(read_syntax() != "(")error_syntax();
        index_syntax++;
        if(read_syntax() != "\n")error_syntax();
        index_syntax++;
        syntax_E();
    }else error_syntax();
}

void Circuit::lex_input(){
    input_list_token.clear();
    string parsed, temp_token;

    parsed = substitute(substitute(input_string, '0' , " 0 "), '1' , " 1 ");

    for(int i = 0; i < parsed.length(); i++){
        if(!(parsed.at(i) == '0' || parsed.at(i) == '1' || parsed.at(i) == '\n' || parsed.at(i) == ' ' )){
            cout<< "Invalid input file on component: " << path_circuit + name<< endl;
            cout<< "CODE: " << (int) '\r'<< endl;
            exit(1);
        }
    }

    set_token(&input_list_token, parsed, ' ');
}

void Circuit::body_evaluator(){
    string temp_token;
    istringstream ff(exp);
    bool  end_check = false;

    while(getline(ff, temp_token, '\n')) {
        if(temp_token == "endmodule"){
            end_check = true;
        }else if(temp_token.find("instance") < temp_token.length() && temp_token.find("instance") >= 0) {
                instance_evaluator(temp_token);
        }else if(temp_token != ""){
                Boolean_Translator bool_exp(temp_token, inputs, outputs, flip_flop_list, clk);
                bool_exp.evaluate();

        }
    }

    if(end_check == false){
        cout << "missing 'endmodule'" << endl;
        exit(1);
    }

    //flip_flop_list->print_list(); //da togliere
}

bool Circuit::instance_evaluator(string str){
    index_instance = 0; instance_token.clear();
    instance_list = new Components_List();
    str = substitute(substitute(substitute(substitute(substitute(str, '=', " = "), '(', " ( "), ')', " ) "), ',', " , "), '.', " . ");
    set_token(&instance_token, str, ' ');

    if(!is_flipflop(read_instance()) && is_id(read_instance())){
        if(!DoesFileExist(path_circuit + "/" + read_instance() + ".txt")){
            cout << "\n\n" << "(invalid 'instance' on component:" << name << ")ERROR: FILE '"<< read_instance() <<".txt' DOES NOT EXIST" << endl;
            exit(1);
        }
        name_instance_circuit = read_instance();
        index_instance++;
        if(read_instance() != "instance")error_instance();
        index_instance++;
        Circuit* instance_circuit = is_present(circuit_list, name_instance_circuit);
        if(instance_circuit == nullptr){
            instance_inputs = new Components_List();
            instance_outputs = new Components_List();
            instance_circuit = new Circuit(path_circuit, name_instance_circuit, instance_inputs, instance_outputs, clk);
            circuit_list.push_back(instance_circuit);
            instance_circuit->is_subcircuit = true;
            instance_circuit->initialize();
        }
        instance_E();
        if(index_instance < instance_token.size())error_instance();
    }else error_instance();

    return false;
}

//--------------Circuit Sintax Parser--------------------------------------------
void Circuit::syntax_E(){
    if(read_syntax() == "clk"){
        index_syntax++;
        if(read_syntax() != "\n")error_syntax();
        index_syntax++;
        syntax_E1();
    }else if(read_syntax() == "input" || read_syntax() == "\n"){
        syntax_E1();
    }else{
        error_syntax();
    }

}

void Circuit::syntax_E1(){
    if(read_syntax() == "input"){
        index_syntax++;
        if(read_next_syntax() == "\n"){
            if(!is_id(read_syntax()))error_syntax();
            add_input();
            index_syntax++;
            index_syntax++; // "\n" lo aveva già trovato
            if(read_syntax() == "input"){ //Cambiato con read_next_syntax()
                syntax_E1();
            }else syntax_O();
        }else{
            syntax_T_I();
        }
    }else if(read_syntax() == "\n"){
        index_syntax++;
        syntax_E1();
    }else error_syntax();

}


void Circuit::syntax_T_I(){
    if(read_next_syntax() == ","){
        if(!is_id(read_syntax()))error_syntax();
        add_input();
        index_syntax++;
        index_syntax++;//"," lo aveva già trovato
        syntax_T_I();
    }else if(is_id(read_syntax())){
        add_input();
        index_syntax++;
        if(read_syntax() != "\n")error_syntax();
        index_syntax++;
        if(read_syntax() == "output"){
            syntax_O();
        }else syntax_E1();
    }else error_syntax();
}

void Circuit::syntax_T_O(){
    if(read_next_syntax() == ","){
        if(!is_id(read_syntax()))error_syntax();
        add_output();
        index_syntax++;
        index_syntax++;//"," lo aveva già trovato
        syntax_T_O();
    }else if(is_id(read_syntax())){
        add_output();
        index_syntax++;
        if(read_syntax() != "\n")error_syntax();
        index_syntax++;
        if(read_syntax() == "output"){
            syntax_O();
        }else syntax_F();
    }else error_syntax();
}

void Circuit::syntax_O(){
    if(read_syntax() == "output"){
        index_syntax++;
        if(read_next_syntax() == "\n"){
            if(!is_id(read_syntax()))error_syntax();
            add_output();
            index_syntax++;
            index_syntax++;//"\n" lo aveva già trovato
            if(read_syntax() == ");"){
                syntax_F();
            }else{
                syntax_O();
            }
        }else syntax_T_O();
    }else if(read_syntax() == "\n"){
        index_syntax++;
        syntax_O();
    }else error_syntax();
}

void Circuit::syntax_F(){
    if(read_syntax() == ");"){
        index_syntax++;
    }else error_syntax();
}
//--------------Circuit Sintax Parser--------------------------------------------

//--------------Instance Parser--------------------------------------------
void Circuit::instance_E(){
    if(read_instance() == "("){
        index_instance++;
        instance_T();
        if(read_instance() != ")")error_instance();
        index_instance++;
    }else error_instance();
}

void Circuit::instance_T(){
    if(read_instance() == ".") {
        index_instance++;
        if(!(is_flipflop(read_instance()) == false && is_id(read_instance()) == true))error_instance();
        string temp_name = read_instance();
        index_instance++;
        if(read_instance() != "=")error_instance();
        index_instance++;
        Component* temp = inputs->is_present(read_instance());
        if(temp == nullptr)error_instance();
        instance_list->add_elem(temp_name, new In_Out(temp_name, temp->val));
        name_associator.insert(pair<string, string>(temp_name, read_instance()));
        index_instance++;
        instance_T_I();
        instance_T_O();
    }else error_instance();
}

void Circuit::instance_T_I(){
    Component* temp_input = nullptr;
    temp_input =  instance_inputs->is_present(read_next_instance(2));

    if(temp_input == nullptr){ //epsilon
        Circuit* instance_circuit = is_present(circuit_list, name_instance_circuit);
        if(instance_circuit == nullptr){
            cout << "Internal error in instance_parser circuit.cpp, missing circuit instance" << endl;
            exit(1);
        }
        instance_circuit->evaluate(instance_list);
    }else if(read_instance() == ","){
        index_instance++;
        if(read_instance() != ".")error_instance();
        index_instance++;
        if(!(is_flipflop(read_instance()) == false && is_id(read_instance()) == true))error_instance();
        string temp_name = read_instance();
        index_instance++;
        if(read_instance() != "=")error_instance();
        index_instance++;
        Component* temp_input = inputs->is_present(read_instance());
        if(temp_input == nullptr)error_instance();
        instance_list->add_elem(temp_name, new In_Out(temp_name, temp_input->val));
        name_associator.insert(pair<string, string>(temp_name, read_instance()));
        index_instance++;
        instance_T_I();
    } else error_instance();
}

void Circuit::instance_T_O(){
    if(read_instance() == ")"){

    }else if(read_instance() == ","){
        index_instance++;
        if(read_instance() != ".")error_instance();
        index_instance++;
        Component* temp = instance_outputs->is_present(read_instance());
        if(temp == nullptr){
            cout << "\n\n" << "(invalid 'instance' on component:" << name << ")ERROR: '"<< read_instance() << "' is not a valid "<< name_instance_circuit <<" output" << endl;
            exit(1);
        }
        pair<string, string> p = to_associate(temp);
        string min_to_associate = p.first, max_to_associate = p.second;
        index_instance++;
        if(read_instance() != "=")error_instance();
        index_instance++;
        if(is_flipflop(read_instance())){
            Component* temp_ff = flip_flop_list->is_present(read_instance());
            if(temp_ff == nullptr){
                Flip_Flop *ff = new Flip_Flop(read_instance(), false, clk);
                flip_flop_list->add_elem(read_instance(), ff);
                ff->update_val(temp->val);
                ff->length_min_path = temp->length_min_path+1; ff->length_max_path = temp->length_max_path+1;
                ff->min_elem = min_to_associate; ff->max_elem = max_to_associate;
            }else{
                temp_ff->update_val(temp->val);
                temp_ff->length_min_path = temp->length_min_path+1; temp_ff->length_max_path = temp->length_max_path+1;
                temp_ff->min_elem = min_to_associate; temp_ff->max_elem = max_to_associate;
            }
        }else if(is_id(read_instance())){
            Component* temp_in = inputs->is_present(read_instance());
            if(temp_in == nullptr){
                cout << "\n\n" << "(invalid 'instance' on component:" << name << ")ERROR: '"<< read_instance() << "' is not a valid "<< name <<" input" << endl;
                exit(1);
            }else{
                temp_in->val = temp->val;
                temp_in->length_min_path = temp->length_min_path; temp_in->length_max_path = temp->length_max_path;
                temp_in->min_elem = min_to_associate; temp_in->max_elem = max_to_associate;
            }
        }else error_instance();
        index_instance++;
        instance_T_O();
    } else error_instance();
}


//--------------Instance Parser--------------------------------------------

string Circuit::read_syntax(){
    if(index_syntax < file_list_token.size()){
        return file_list_token.at(index_syntax);
    }else return "";
}

string Circuit::read_next_syntax(){
    if(index_syntax+1< file_list_token.size()){
        return file_list_token.at(index_syntax+1);
    }else return "";
}

string Circuit::read_instance(){
    if(index_instance< instance_token.size()){
        return instance_token.at(index_instance);
    }else return "";
}

string Circuit::read_next_instance(int pos){
    if(index_instance+pos< instance_token.size()){
        return instance_token.at(index_instance+pos);
    }else return "";
}

void Circuit::add_input(){
        if (inputs->is_present(read_syntax()) != nullptr || outputs->is_present(read_syntax()) != nullptr) {
            cout << "\nCant define two inputs/outputs with the same label";
            error_syntax();
        }

        if (index_inputs < input_list_token.size()) {
            inputs->add_elem(read_syntax(), new In_Out(read_syntax(), str_to_bool(input_list_token.at(index_inputs))));
            index_inputs++;
        }else if(is_subcircuit){
            inputs->add_elem(read_syntax(), new In_Out(read_syntax(), false));
            index_inputs++;
        }else{
            cout << "Invalid input file on component: " << path_circuit + name << endl;
            exit(1);
        }
}

void Circuit::add_output(){
    if(inputs->is_present(read_syntax()) != nullptr || outputs->is_present(read_syntax()) != nullptr){
        cout << "\nCant define two inputs/outputs with the same label";
        error_syntax();
    }

    outputs->add_elem(read_syntax(), new In_Out(read_syntax(), false));
}

bool Circuit::is_id(string str){
    if(!is_operator(str) && read_syntax() != "="){
        return true;
    }else return false;
}

void Circuit::error_syntax(){
    cout << "\n\n" << "(declaration of component:" << name << ")ERROR with token:"<< read_syntax() << endl;
    exit(1);
}

void Circuit::error_instance(){
    cout << "\n\n" << "(invalid 'instance' on component:" << name << ")ERROR with token:"<< read_instance() << endl;
    exit(1);
}

pair<string, string> Circuit::to_associate(Component* temp){
    string ind = read_instance();
    pair<string, string> p;
    map<string,string>::iterator it = name_associator.find(temp->min_elem);
    if(name_associator.count(temp->min_elem) > 0){
        p.first = it->second;
    }else p.first = "." + temp->min_elem;
    it = name_associator.find(temp->max_elem);
    if(name_associator.count(temp->max_elem) > 0){
        p.second = it->second;
    }else p.second = "." + temp->max_elem;
    return p;
}