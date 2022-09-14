#include<bits/stdc++.h>
using namespace std;

int max_need[5][4] =    {{0, 0, 1, 2},
                        {1, 7, 5, 0},
                        {2, 3, 5, 6},
                        {0, 6, 5, 2},
                        {0, 6, 5, 6}};

int allocation[5][4] =  {{0, 0, 1, 2},
                        {1, 0, 0, 0},
                        {1, 3, 5, 4},
                        {0, 6, 3, 2},
                        {0, 0, 1, 4}};
            
int need[5][4];

int main(){

    for(int i=0; i<5; i++){
        for(int j=0; j<4; j++){
            need[i][j] = max_need[i][j] - allocation[i][j];
        }
    }

    // for(int i=0; i<5; i++){
    //     for(int j=0; j<4; j++){
    //         cout << need[i][j];
    //     }
    // }

}