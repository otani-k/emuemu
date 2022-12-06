#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(){
    ifstream ifs1, ifs2;
    string str1, str2;

    ifs1.open("../sample/nestest.txt");
    ifs2.open("../result.txt"); 
    while (getline(ifs1, str1)) {
        getline(ifs2, str2);
        if(str1 != str2){
            cout << "nestest result : " << str1 << endl;
            cout << "emulator result: " << str2 << endl;
            return 0;
        }
    }
    return 0;
}