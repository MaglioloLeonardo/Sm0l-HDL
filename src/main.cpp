#include <string.h>
#include <iostream>
#include <fstream>

#include "Circuit.cpp"
#include "Boolean_Translator.cpp"
#include "Parser_Helper.cpp"
#include "Component.h"
#include "Components_List.cpp"
#include "Flip_Flop.cpp"
#include "Flip_Flop.h"

using namespace std;

void interface_printer(string *mode);
void circuit_insertion(string *name);

void simulation(string circuit_name);
void analysis(string circuit_name);
void library();


string circuit_folder = "../Circuiti";
string inputs_folder = "../Inputs";

int main(){
    string circuit_name , mode;
    interface_printer(&mode);
    if(mode == "1"){
        circuit_insertion(&circuit_name);
        simulation(circuit_name);
    }else if(mode == "2"){
        circuit_insertion(&circuit_name);
        analysis(circuit_name);
    }else{
        library();
    }

    return 0;
}


void interface_printer(string *mode){
    cout<<"\nEnter the number associated with the mode you intend to use:"<< endl;
    cout<<"\n1 - Simulation\n2 - Analysis\n3 - Library \n"<< endl;
    cin >> *mode;
    if(*mode != "1" && *mode != "2" && *mode != "3"){
        cout<<"\nERROR: Invalid mode";
        exit(1);
    }
}

void circuit_insertion(string *name){
    cout<<"\nEnter the name of the circuit:\n "<< endl;
    cin >> *name;//senza il .txt
    if(!DoesFileExist(circuit_folder + "/" + *name + ".txt")){
        cout<<"\nERROR: File '" + *name + ".txt' doesn't exist in '" + circuit_folder + "'";
        exit(1);
    }
}

void simulation(string circuit_name){
    Components_List *inputs = new Components_List();
    Components_List *outputs = new Components_List();
    bool clk_data = true;

    string path_circuit = circuit_folder + "/";
    ifstream input(inputs_folder + "/" + circuit_name + ".txt");
    Circuit circuit(path_circuit, circuit_name, inputs, outputs, &clk_data);

    int counter = 1;
    for(string line; getline( input, line ); )
    {
        cout<<"Row n "<< counter <<" _____________________________\n"<<endl;
        clk_data = !clk_data;
        circuit.evaluate(line);
        cout<<"Inputs:--------------"<<endl;
        inputs->print_values();
        cout<<"Outputs:-------------"<<endl;
        outputs->print_values();
        cout<<"___________________________________\n\n"<<endl;
        counter++;
    }
}

void analysis(string circuit_name){
    Components_List *inputs = new Components_List();
    Components_List *outputs = new Components_List();
    bool clk_data = true;

    string path_circuit = circuit_folder + "/";
    ifstream input(inputs_folder + "/" + circuit_name + ".txt");
    Circuit circuit(path_circuit, circuit_name, inputs, outputs, &clk_data);
    circuit.evaluate(NULL_INPUT);
    outputs->print_stats();
}

void library(){
    string path, name_new_file = "", circuit_name, mode;
    while(path != "+"){
        cout<<"\nEnter the path of the circuit (enter '+' for evaluate):\n "<< endl;
        cin >> path;//senza il .txt
        if(path == "+")break;
        copy_file(circuit_folder, inputs_folder, path, "0");
    }

    cout<<"\nEnter the number associated with the mode you intend to use:"<< endl;
    cout<<"\n1 - Simulation\n2 - Analysis\n"<< endl;
    cin >> mode;

    circuit_insertion(&circuit_name);

    if(mode == "1"){
        if(!DoesFileExist(inputs_folder + "/" + circuit_name + ".txt")){
            cout<<"\nEnter the path of the input of '" + circuit_name + "':\n" << endl;
            cin >> path;
            copy_file(circuit_folder, inputs_folder, path, circuit_name);
        }
        simulation(circuit_name);
    }else if(mode == "2"){
        analysis(circuit_name);
    }else{
        cout<<"\nERROR: Invalid mode";
        exit(1);
    }


}




