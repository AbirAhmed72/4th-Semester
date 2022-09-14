#include <bits/stdc++.h>
using namespace std;

#define n 5
#define m 4

void computeNeed(int currentNeed[n][m], int maxNeed[n][m], int allocated[n][m]){

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            currentNeed[i][j] = maxNeed[i][j] - allocated[i][j];
        }    
    }
}

void systemSafe(int processes[n], int available[m], int maximum[n][m], int allocated[n][m]){

    int i, j, k;
    bool flag;
    int need[n][m];
    int count = 0;

    computeNeed(need, maximum, allocated);

    bool finished[n] = {false};

    int safeSequence[n];
    int available2[m];

    for (i = 0; i < m; i++){
        available2[i] = available[i];
    }

    while (count < n){
        
        flag = false;

        for(i = 0; i < n; i++){
            
            if(!finished[i]){
                
                for(j = 0; j < m; j++){
                    if(need[i][j] > available2[j])
                    break;
                }
                    
                if(j == m){

                    for(k = 0; k < m; k++){
                        available2[k] += allocated[i][k];
                    }
                    
                    safeSequence[count++] = i;

                    finished[i] = true;

                    flag = true;
                }
            }
        }

        if(flag == false){
            cout << "System is not in a safe state" << endl;
            return;
        }
    }

    cout << "System is in a safe state.\nSafe sequence is:\n";

    for (int i = 0; i < n; i++){
        cout << safeSequence[i] << "\n";
    }
    
    return;
}

int main(){
  
    int processes[n] = {0, 1, 2, 3, 4};
    int available[m] = {1, 5, 2, 0};

    int maximum[n][m] = {{0, 0, 1, 2},
                        {1, 7, 5, 0},
                        {2, 3, 5, 6},
                        {0, 6, 5, 2},
                        {0, 6, 5, 6}};

    int allocated[n][m] = {{0, 0, 1, 2},
                        {1, 0, 0, 0},
                        {1, 3, 5, 4},
                        {0, 6, 3, 2},
                        {0, 0, 1, 4}};

    systemSafe(processes, available, maximum, allocated);

    return 0;
}