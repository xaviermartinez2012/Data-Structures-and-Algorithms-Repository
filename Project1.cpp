//
//  Project1.cpp
//  Data Structures and Algorithms Projects
//
//  Created by Xavier Martinez on 9/21/16.
//  Copyright © 2016 Xavier Martinez. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

/* Equ1: f(1) = 1
         f(2) = 1
         f(n) = f(n-1)+f(n-2)
   Sum:  S(n) = f(1)+f(2)+...+f(n)
 */
unsigned long Equ1(int n){
    if (n == 1) {
        return 1;
    }
    else if (n == 2){
        return 1;
    }
    else return (Equ1(n-1) + Equ1(n-2));
}

unsigned long recursiveSum(int n){
    cout << "n = " << n << endl;
    unsigned long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long fn = Equ1(i);
        cout << "f(" << i << ") = " << fn << endl;
        sum += fn;
    }
    cout << "S(n) = " << sum << endl;
    return sum;
}

unsigned long nonRecursiveSum(int n){
    cout << "n = " << n << endl;
    cout << "f(1) = " << 1 << endl;
    cout << "f(2) = " << 1 << endl;
    unsigned long sum = 2;
    unsigned long table[n];
    table[0] = (unsigned long)1;
    table[1] = (unsigned long)1;
    for (int i = 2; i < n; i++) {
        table[i] = table[i - 1] + table[i - 2];
        cout << "f(" << i+1 << ") = " << table[i] << endl;
        sum += table[i];
    }
    cout << "S(n) = " << sum << endl;
    return sum;
}

unsigned long GrimaldiSum(int n){
    cout << "n = " << n << endl;
    unsigned long sum = 0;
    for (int i = 1; i <= n; i++){
        unsigned long gn = (1.0/sqrt(5.0))*(pow(((1.0+sqrt(5))/2.0), i)-pow(((1.0-sqrt(5))/2.0), i));
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
    cout << "Task 4." << endl;
    GrimaldiSum(n);
    println();
    cout << "Task 5 (using Grimaldi's method)." << endl;
    GrimaldiSum(10);
    println();
    GrimaldiSum(20);
    println();
    GrimaldiSum(30);
    println();
    cout << "f(" << 12 << ") = " << Equ1(12) << endl;
    cout << "f(" << 22 << ") = " << Equ1(22) << endl;
    cout << "f(" << 32 << ") = " << Equ1(32) << endl;
    println();
    cout << "Task 8." << endl;
    for (int i = 3; i <= 70; i++) {
        cout << "Recursive Sum" << endl;
        recursiveSum(i);
        println();
        cout << "Non-Recursive Sum" << endl;
        unsigned long uS = nonRecursiveSum(i);
        println();
        cout << "Grimaldi Sum" << endl;
        unsigned long gS = GrimaldiSum(i);
        println();
        cout << "Difference of " << gS-uS << endl;
        println();
    }
    // Grimaldi Sum computes quickly and Exhibits roundoff errors for n > 70...
    // Non-recursive sum computes quickly and largest n is approx. 93. Does not exhibit roundoff errors...
    // Recursive sum is increadibly slow in comarison to the other two approaces. Largest n is approx. 45 (after this too slow)
//    
    return 0;
}