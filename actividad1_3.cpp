#include <stdint.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

int main(){
    string cadena,direccion;
    cin >> cadena;
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

    if ((fi<3 && fi>0) && (co<3 && co>0 )){
        cout << "\nUP" << "\nDOWN"<< "\nLEFT" << "\nRIGHT"<<endl;
    }else if((fi==3) && (co<3 && co>0 )){
        cout << "\nUP"<< "\nLEFT" << "\nRIGHT"<<endl;
    }else if((fi==0) && (co<3 && co>0 )){
        cout << "\nDOWN"<< "\nLEFT" << "\nRIGHT"<<endl;
    }else if (co==3){
        cout << "\nUP" << "\nDOWN"<< "\nLEFT" <<endl;
    }else if(co==0){
        cout << "\nUP" << "\nDOWN"<< "\nRIGHT"<<endl;
    }
    return 0;
    
}