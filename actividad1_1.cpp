#include <stdint.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

int main(){
    string cadena;
    cin >> cadena;

    char tap[4][4];
    int i,j;
    int tmp = 0;
    for (i =0; i < 4; i++ ){
        for (j=0; j < 4; j++){
            tap[i][j] = cadena[tmp];
            tmp +=1;
        }
    }
    for (i =0; i < 4; i++ ){
        for (j=0; j < 4; j++){
            cout<<tap[i][j];
        }
        cout << endl;
    }

    return 0;
    
}