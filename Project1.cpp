//
//  Project1.cpp
//  Data Structures and Algorithms Projects
//
//  Created by Xavier Martinez on 9/21/16.
//  Copyright © 2016 Xavier Martinez. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <ctime>
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

unsigned long recursiveSum(int n, bool verbose){
    cout << "n = " << n << endl;
    unsigned long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long fn = Equ1(i);
        if (verbose) {
            cout << "f(" << i << ") = " << fn << endl;
        }
        sum += fn;
    }
    cout << "S(n) = " << sum << endl;
    return sum;
}

unsigned long nonRecursiveSum(int n, bool verbose){
    cout << "n = " << n << endl;
    if (verbose) {
        cout << "f(1) = " << 1 << endl;
        cout << "f(2) = " << 1 << endl;
    }
    unsigned long sum = 2;
    unsigned long table[n];
    table[0] = (unsigned long)1;
    table[1] = (unsigned long)1;
    for (int i = 2; i < n; i++) {
        table[i] = table[i - 1] + table[i - 2];
        if (verbose){
            cout << "f(" << i+1 << ") = " << table[i] << endl;
        }
        sum += table[i];
    }
    cout << "S(n) = " << sum << endl;
    return sum;
}

unsigned long GrimaldiSum(int n, bool verbose){
    cout << "n = " << n << endl;
    unsigned long sum = 0;
    for (int i = 1; i <= n; i++){
        unsigned long gn = (1.0/sqrt(5.0))*(pow(((1.0+sqrt(5))/2.0), i)-pow(((1.0-sqrt(5))/2.0), i));
        if (verbose) {
            cout << "f(" << i << ") = " << gn << endl;
        }
        sum += gn;
    }
    cout << "S(n) = " << sum << endl;
    return sum;
}

unsigned long identitySum(int n){
    cout << "n = " << n << endl;
    unsigned long sum = (Equ1(n + 2) - 1);
    cout << "S(n) = " << sum << endl;
    return sum;
}

void println(){
    cout << endl;
}
int main(int argc, const char * argv[]) {
    int n = 10;
    bool verbose = false;
    cout << "Task 1." << endl;
    recursiveSum(n, verbose);
    println();
    cout << "Task 2." << endl;
    nonRecursiveSum(n, verbose);
    println();
    cout << "Task 4." << endl;
    GrimaldiSum(n, verbose);
    println();
    cout << "Task 5 (using Grimaldi's method)." << endl;
    GrimaldiSum(10, verbose);
    println();
    GrimaldiSum(20, verbose);
    println();
    GrimaldiSum(30, verbose);
    println();
    cout << "f(" << 12 << ") = " << Equ1(12) << endl;
    cout << "f(" << 22 << ") = " << Equ1(22) << endl;
    cout << "f(" << 32 << ") = " << Equ1(32) << endl;
    println();
    cout << "Task 7." << endl;
    identitySum(n);
    println();
    cout << "Task 8." << endl;
    if (verbose) {
        for (int i = 3; i <= 40; i++) {
            cout << "Recursive Sum" << endl;
            recursiveSum(i, verbose);
            println();
            cout << "Non-Recursive Sum" << endl;
            unsigned long uS = nonRecursiveSum(i, verbose);
            println();
            cout << "Grimaldi Sum" << endl;
            unsigned long gS = GrimaldiSum(i, verbose);
            println();
            if (verbose){
                cout << "Difference of " << gS-uS << endl;
            }
        }
        println();
    }
    // Grimaldi Sum computes quickly and Exhibits roundoff errors for n > 70...
    // Non-recursive sum computes quickly and largest n is approx. 93. Does not exhibit roundoff errors...
    // Recursive sum is increadibly slow in comarison to the other two approaches. Largest n is approx. 45 (after this too slow)
    cout << "Task 9." << endl;
    cout << "Recursive Sum" << endl;
    int start_s=clock();
    recursiveSum(40, false);
    int stop_s=clock();
    cout << "Recursive sum execution time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << "ms" << endl;
    println();
    cout << "Non-recursive Sum" << endl;
    start_s=clock();
    nonRecursiveSum(40, false);
    stop_s=clock();
    cout << "Non-recursive sum execution time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << "ms" << endl;
    println();
    cout << "Grimaldi Sum" << endl;
    start_s=clock();
    GrimaldiSum(40, false);
    stop_s=clock();
    cout << "Grimaldi sum execution time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << "ms" << endl;
    println();
    cout << "Identity Sum" << endl;
    start_s=clock();
    identitySum(40);
    stop_s=clock();
    cout << "Identity sum execution time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << "ms" << endl;
    
    return 0;
}