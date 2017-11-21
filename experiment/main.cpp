#include <iostream>
#include <string>
#include "tester.h"

using namespace std;

int main(int argc, char* argv[]) {
    vector<string> arg_name({"Scheduling Algorithm", "Testcase", "Testresult"});
    vector<string> arg(3);

    if (argc > 4) {
        cout << "Argument error." << endl;
        return -1;
    }

    Tester tester;
    cout << "CPTCLD test initiated." << endl;

    string testcase_path = "./testcase/";
    string testresult_path = "./testresult/";
    cout << "Default testcase path: " << testcase_path << endl;
    cout << "Default testresult path: " << testresult_path << endl;

    int i = 0;
    for (;i < argc - 1; i++) arg[i] = argv[i + 1];
    int arg_start = i;

    if (arg_start == 3) tester.RunTest(arg[0], testcase_path + arg[1], testresult_path + arg[2]);
    else if (arg_start == 2) {
        cout << "Testresult: ";
        cin >> arg[2];
        tester.RunTest(arg[0], testcase_path + arg[1], testresult_path + arg[2]);
    }
    else {
        while (true) {
            cout << "--------------------" << endl;
            for (i = arg_start; i < arg.size(); i++) {
                cout << arg_name[i] << ": ";
                cin >> arg[i];
                if (arg[i] == "exit") {
                    cout << "CPTCLD test terminated." << endl;
                    return 0;
                }
            }
            tester.RunTest(arg[0], testcase_path + arg[1], testresult_path + arg[2]);
        }
    }

    cout << "CPTCLD test terminated." << endl;
    return 0;  
}