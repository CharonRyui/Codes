#include <iostream>
#include <vector>
#include <utility>
#include <cstring>
#include <algorithm>
using namespace std;
vector<pair<string,int>> store;
string command;
int main() {
    while (true) {
        cout << "input your command here, input '-h' for help" << endl;
        cin >> command;
        if (command == "-h") {
            cout << "-a: add a new item" << endl;
            cout << "-f name: find a student's grade with name" << endl;
            cout << "-v: calculate the average grade of all students" << endl;
            cout << "-s: display all students'grades by order" << endl;
            cout << "-e: exit the programe" << endl;
        } else if (command == "-a") {
            string new_name;
            int new_grade;
            cout << "please input the name and grade of the student" << endl;
            cin >> new_name >> new_grade;
            store.push_back(pair<string,int>(new_name, new_grade));
            cout << "successfully added" << endl;
        } else if (command == "-f") {
            cout << "input the student you want to search" << endl;
            string name;
            cin >> name;
            vector<pair<string, int>>::iterator it = find_if(store.begin(), store.end(), [&name](pair<string, int> p){return p.first == name;});
            cout << "the student's grade is " << (*it).second << endl;
        } else if (command == "-v") {
            vector<pair<string, int>>::iterator it = store.begin();
            double sum = 0;
            int count = 0;
            for (it; it != store.end(); it++) {
                sum += (*it).second;
                count++;
            }
            cout << "the average grades of your students is " << sum / count << endl;
        } else if (command == "-s") {
            sort(store.begin(), store.end());
            vector<pair<string, int>>::iterator it = store.begin();
            for (it; it != store.end(); it++) {
                cout << (*it).first << " " << (*it).second << endl;
            }
            cout << "your students' grades are above" << endl;
        }else if (command == "-e") break;
        else cout << "i do not understand your meaning, if you need any help, please input '-h'" << endl;
        cout << "------------------------------------------------------------------------------------" << endl; 
    }
    return 0;
}