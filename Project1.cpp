//
//  Project1.cpp
//  Data Structures and Algorithms Projects
//
//  Created by Xavier Martinez on 9/21/16.
//  Copyright © 2016 Xavier Martinez. All rights reserved.
//

#include <iostream>
#include <math.h>
using namespace std;

/* Equ1: f(1) = 1
         f(2) = 1
         f(n) = f(n-1)+f(n-2)
   Sum:  S(n) = f(1)+f(2)+...+f(n)
 */
int Equ1(int n){
    if (n == 1) {
        return 1;
    }
    else if (n == 2){
        return 1;
    }
    else return (Equ1(n-1) + Equ1(n-2));
}

int recursiveSum(int n){
    cout << "n = " << n << endl;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        int fn = Equ1(i);
        cout << "f(" << i << ") = " << fn << endl;
        sum += fn;
    }
    cout << "S(n) = " << sum << endl;
    return sum;
}

int nonRecursiveSum(int n){
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

int GrimaldiSum(int n){
    cout << "n = " << n << endl;
    double sum = 0;
    for (int i = 1; i <= n; i++){
        double gn = (1.0/sqrt(5.0))*(pow(((1.0+sqrt(5))/2.0), i)-pow(((1.0-sqrt(5))/2.0), i));
        cout << "f(" << i << ") = " << gn << endl;
        sum += gn;
    }
    cout << "S(n) = " << sum << endl;
    return sum;
}

void println(){
    cout << endl;
}
int main(int argc, const char * argv[]) {
    int n = 10;
    cout << "Task 1." << endl;
    recursiveSum(n);
    println();
    cout << "Task 2." << endl;
    nonRecursiveSum(n);
    println();
    cout << "Task 3." << endl;
    GrimaldiSum(n);
    return 0;
}