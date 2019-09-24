#ifndef PARSER_HELPER
#define PARSER_HELPER

#include <string>
#include <vector>
#include <fstream>



#define NULL_INPUT "-1"
using namespace std;


bool is_operator(string str){
    if(str == "NOT" || str == "OR" || str == "AND")
        return true;
    else return false;
}

bool is_flipflop(string str){
    int i = 0;
    if(str.at(i) == 'F') { //FFX where X is a number > 0
        i++;
        if (str.length() <= i || str.at(i) != 'F')return false;
        i++;
        if (str.length() <= i || i >= str.length())return false;
        bool toggle = false;
        while (i < str.length()) {
            if (toggle == false && !(str.at(i) >= 49 && str.at(i) <= 57)) {
                return false;
            } else if (toggle == true && !(str.at(i) >= 48 && str.at(i) <= 57)) {
                return false;
            }
            i++;
            toggle = true;
        }
        return true;
    }else return false;
}

string file_to_string(string path){
    fstream f(path, fstream::in );
    string s;
    getline( f, s, '\0');
    f.close();
    return s;
}

bool str_to_bool(string str){
    if(str == "1" || str == "true" ){
        return true;
    }else{
        return false;
    }
}

string substitute(string str, char to_change, string to_substitute){
    string  to_return;

    for(int i = 0; i < str.length(); i++){
        if(str.at(i) == to_change){
            to_return += to_substitute;
        }else{
            to_return += str.at(i);
        }
    }
    return  to_return;
}

void set_token(vector<string> *vec, string str, char separator){
    string temp_token;

    istringstream ss(str);

    while(getline(ss, temp_token, separator)) {
        if(temp_token != ""){
            vec->push_back(temp_token);
        }
    }
}

Circuit* is_present(vector <Circuit*> vec, std::string name){
    for (Circuit *cir: vec) {
        if (cir->get_name() == name)return cir;
    }
    return nullptr;
}

bool DoesFileExist (string path) {
    ifstream f(path);
    return f.good();
}

void copy_file(string circuit_folder, string inputs_folder,string path_in, string mode){
    assert(mode != "");
    string name_new_file = "";

    if(!DoesFileExist(path_in)){
        cout<<"\nERROR: File '" + path_in  +  "' doesn't exist";
        exit(1);
    }else {
        int index = path_in.length() - 1;
        while (path_in.at(index) != '/') {
            name_new_file += path_in.at(index);
            index--;
        }
        reverse(name_new_file.begin(), name_new_file.end());
        if (mode == "0") {
            std::ifstream in_file(path_in, std::ios::binary);
            std::ofstream out_file(circuit_folder + "/" + name_new_file, std::ios::binary);
            out_file << in_file.rdbuf();
        } else {
            std::ifstream in_file(path_in, std::ios::binary);
            std::ofstream out_file(inputs_folder + "/" + mode + ".txt", std::ios::binary);
            out_file << in_file.rdbuf();
        }

    }
}

#endif
