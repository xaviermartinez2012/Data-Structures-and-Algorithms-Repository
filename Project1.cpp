//
//  Project1.cpp
//  Data Structures and Algorithms Projects
//
//  Created by Xavier Martinez on 9/21/16.
//  Copyright © 2016 Xavier Martinez. All rights reserved.
//

#include <iostream>
using namespace std;

int Equ1(int n){
    if (n == 1) {
        return 1;
    }
    else if (n == 2){
        return 1;
    }
    else return (Equ1(n-1) + Equ1(n-2));
}

int Equ1_withoutRecusrion(int n){
    cout << "n = " << n << endl;
    cout << "f(1) = " << 1 << endl;
    cout << "f(2) = " << 1 << endl;
    int sum = 2;
    int table[n];
    table[0] = 1;
    table[1] = 1;
    for (int i = 2; i < n; i++) {
        table[i] = table[i - 1] + table[i - 2];
        cout << "f(" << i+1 << ") = " << table[i] << endl;
        sum += table[i];
    }
    cout << "S(n) = " << sum << endl;
    return sum;
}


int recursiveSum(int n){
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += Equ1(i);
    }
    return sum;
}

int main(int argc, const char * argv[]) {
    /* Equ1: f(1) = 1
             f(2) = 1
             f(n) = f(n-1)+f(n-2)
       Sum:  S(n) = f(0)+f(1)+...+f(n)
     */
    Equ1_withoutRecusrion(4);
    return 0;
}
