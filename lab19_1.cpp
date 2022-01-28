#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include <cstring>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string file, vector<string> &names, vector<int> &points, vector<char> &grades){
    ifstream source(file);
    string line;
    do {

        getline(source, line);

        if (!line.size()) break;

        char name[30] = {};
        int scores[3] = {}, sum = 0;
        sscanf(line.c_str(), "%[^:]", name);
        sscanf(line.c_str()+strlen(name)+2, "%d %d %d", scores, scores+1, scores+2);
        for (int i = 0;i < 3; ++i){ 
            sum += scores[i];
        }

        names.push_back(string(name));
        points.push_back(sum);
        grades.push_back(score2grade(sum));
    } while(line.size());

    source.close();
}

void getCommand(string &s1, string &s2){
    string command;

    cout << "Please input your command: ";
    getline(cin, command);

    unsigned int i, j = 0;
    for (i = 0; i < command.size(); ++i){
        if (command[i] == ' ') {
            command[i] = '\0';
            j = i + 1;
            break;
        }
    }
    s1 = string(&command[0]);
    if (j) s2 = string(&command[j]);
}

void searchName(const vector<string> &names, const vector<int> &points, const vector<char> &grades, const string x){
    cout << "---------------------------------\n";

    bool f = false;
    for (unsigned int i = 0; i < names.size(); ++i){
        if (toUpperStr(names[i]) == x) {
            cout << names[i] << "'s score = " << points[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            f = true;
        }
    }
    if (!f) cout << "Cannot found." << "\n";
    cout << "---------------------------------\n";
}

void searchGrade(const vector<string> &names, const vector<int> &points, const vector<char> &grades, const string x){
    cout << "---------------------------------\n";

    for (unsigned int i = 0; i < grades.size(); ++i){
        if (grades[i] == x[0]) {
            cout << names[i] << " (" << points[i] << ")\n";
        }
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}