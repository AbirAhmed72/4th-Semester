#include<bits/stdc++.h>
#include<unistd.h>

using namespace std;

int main(){

    cout << " this wont be executed" << endl;

    fork();
    for(;;);

    cout << "after infinite loop" << endl;

    return 0;
}