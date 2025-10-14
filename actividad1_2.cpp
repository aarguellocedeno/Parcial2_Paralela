#include <stdint.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

int main(){
    string cadena,direccion;
    cin >> cadena;
    cin.ignore();
    cin >> direccion;

    char tap[4][4];
    int i,j,fi,co;

    int tmp = 0;
    for (i =0; i < 4; i++ ){
        for (j=0; j < 4; j++){
            tap[i][j] = cadena[tmp];
            if (cadena[tmp] == '#'){
                fi = i;
                co = j;
            }
            tmp +=1;
        }
    }
    if (direccion == "UP"){
        if(fi!=0){
            swap(tap[fi][co],tap[fi-1][co]);
        }

    }else if(direccion == "DOWN"){
        if(fi!=3){
            swap(tap[fi][co],tap[fi+1][co]);
        }

    }else if(direccion == "LEFT"){
        if(co!=0){
            swap(tap[fi][co],tap[fi][co-1]);
        }
    }else  if(direccion == "RIGHT"){
        if(co!=3){
            swap(tap[fi][co],tap[fi][co+1]);
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