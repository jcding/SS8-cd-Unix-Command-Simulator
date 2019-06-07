#include <iostream>
#include <string>
#include <vector>

using namespace std;


string execute_instruct(string &start_dir, string& og_end_dir, vector<string> instructions){
    if(start_dir[start_dir.size()-1] == '/'){
        start_dir.erase( start_dir.end()-1 );
    }

    for(int i = 0 ; i < int(instructions.size()); i++){
        if(instructions[i].find("..") != string::npos && instructions[i].size() != 2){
           return og_end_dir + ": No such file or directory";
        }
        else if(instructions[i] == ".."){
            if(start_dir.size() > 0){
                while(start_dir[start_dir.size()-1] != '/'){
                    //remove the last char
                    start_dir.erase( start_dir.end()-1 );
                }
                // remove the last char
                start_dir.erase( start_dir.end()-1 );
            }
        }
        else if(instructions[i] == "."){
            continue;
        }
        else{
            if(start_dir[start_dir.size()-1] == '/'){
                start_dir = start_dir + instructions[i];
            }
            else{
                start_dir = start_dir + '/' + instructions[i];
            }
        }
    }

    if(!start_dir.size()){
        return "/";
    }
    else{
        return start_dir;
    }
    
}


string mycd(string start_dir, string &end_dir){
    vector<string> instructions;
    string og_end_dir = end_dir;
    string placeholder = start_dir;

    // remove all consecutive duplicate "/" in end_dir
    // parse the instructions
    for (unsigned int i = 0; i < end_dir.length(); i++){
        if(end_dir[i] == '/' && i != end_dir.length()-1){
            for(unsigned int inner = i+1; inner < end_dir.length();){
                if(end_dir[inner] == '/'){
                    end_dir.erase(inner, 1);
                }
                else{
                    break;
                }
            }
        }
    }

    cout << "after parsing for duplicated '/': " << end_dir << endl;

    // if the end_dir starts with '/' just return the end_dir
    if(end_dir[0] == '/'){
        return end_dir;
    }
    else{
        // applying instruction as we go
        string instruction = "";
        for(unsigned int i = 0; i < end_dir.length(); i++){
            if(end_dir[i] != '/'){
                instruction += end_dir[i];
            }
            else{
                instructions.push_back(instruction);
                instruction = "";
            }
        }
        if(instruction != ""){
            instructions.push_back(instruction);
        }

        cout << "instructions:" << endl;
        for(unsigned int i = 0; i < instructions.size(); i++){
            cout << instructions[i] << endl;
        }
        cout << "*****************************" << endl;
    }

    return execute_instruct(start_dir, og_end_dir, instructions);
}

int main(int argc, char** argv){

    if(argc != 3){
        cout << "USAGE: ./mycd (starting directory) (end directory)" << endl;
        return 0;
    }

    

    string start_dir = argv[1];
    string end_dir = argv[2];
    // end_dir 

    // cout << start_dir << endl;
    // cout << end_dir << endl;

    cout << "result: "+ mycd(start_dir, end_dir) << endl;


    return 0;
}