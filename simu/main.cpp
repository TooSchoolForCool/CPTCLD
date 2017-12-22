#include <iostream>

#include "eNodeB.h"
#include "normalUser.h"
#include "dumpCheater.h"
#include "smartCheater.h"

using namespace std;

int main()
{
    eNodeB eNB;
    userAgent *user = NULL;

    string user_type;
    int iter = 0;

    cin >> user_type >> iter;

    if(user_type == "normal")
        user = new normalUser();
    else if(user_type == "dump")
        user = new dumpCheater();
    else if(user_type == "smart")
        user = new smartCheater();
    else
    {
        cout << "No such options: " << user_type << endl;
        exit(-1);
    }

    for(int i = 0; i < iter; i++)
    {
        Request request = user->generateRequest();
        double alloc = eNB.dealRequest(request);
        user->addAllocation(alloc);
    }

    cout << "-1 -1 -1" << endl;

    delete user;

    return 0;
}