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

// Program to calculate S (n) by calculating the values of the Fibonacci sequence recursively.
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
/*
 Non-recursive program to calculate S (n). This program uses the recurrence definition to calculate and tabulate the values of the
 Fibonacci sequence.
 */
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

// Program that calculates S(n) using Grimaldi's definition.
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
    int n = 15;
    bool verbose = true;
    
//  Test the recursive sum program
    cout << "Task 1." << endl;
    recursiveSum(n, verbose);
    println();
    
//  Test the non-recursive sum program
    cout << "Task 2." << endl;
    nonRecursiveSum(n, verbose);
    println();
    
//  Test the Grimaldi sum program
    cout << "Task 4." << endl;
    GrimaldiSum(n, verbose);
    println();
    
/*  
    Use Grimaldi sum calculate values of S for n = 10, 20, 30. 
    Compute values of f for n = 12, 22, 32
 */
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
    
//  Test the identity sum program
    cout << "Task 7." << endl;
    identitySum(n);
    println();
    
//  Experimentation with programs...
    cout << "Task 8." << endl;
    for (int i = 3; i <= 40; i++) {
        cout << "Recursive Sum" << endl;
        recursiveSum(i, verbose);
        println();
        cout << "Non-Recursive Sum" << endl;
        nonRecursiveSum(i, verbose);
        println();
        cout << "Grimaldi Sum" << endl;
        GrimaldiSum(i, verbose);
        println();
        cout << "Identity Sum" << endl;
        identitySum(i);
        println();
    }
    // Grimaldi Sum computes quickly and Exhibits roundoff errors for n > 70...
    // Non-recursive sum computes quickly and largest n is approx. 93. Does not exhibit roundoff errors...
    // Recursive sum is increadibly slow in comarison to the other non-recursive approaches. Largest n is approx. 45 (after this too slow)
    // Identity sum exhibits characteristics found in recursive sum. It is increadibly slow in comarison to the other non-recursive approaches.
    // Largest n is approx. 45 (after this too slow)
    
//  Comparing the execution times of the 4 programs.
    cout << "Task 9." << endl;
    bool exit = false;
    while (!exit){
        cout << "Choose a value for n: ";
        int nValue;
        cin >> nValue;
        println();
        cout << "1. Recursive Sum" << endl;
        cout << "2. Non-Recursive Sum" << endl;
        cout << "3. Grimaldi Sum" << endl;
        cout << "4. Identity Sum" << endl;
        cout << "0. Exit" << endl;
        println();
        cout << "Choose a method to compute S(n): ";
        int choice;
        cin >> choice;
        println();
        switch (choice) {
            case 1:
            {
                cout << "Recursive Sum" << endl;
                int start_s=clock();
                recursiveSum(nValue, false);
                int stop_s=clock();
                cout << "Recursive sum execution time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << "ms" << endl;
                println();
                break;
            }
            case 2:
            {
                cout << "Non-recursive Sum" << endl;
                int start_s=clock();
                nonRecursiveSum(nValue, false);
                int stop_s=clock();
                cout << "Non-recursive sum execution time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << "ms" << endl;
                println();
                break;
            }
            case 3:
            {
                cout << "Grimaldi Sum" << endl;
                int start_s=clock();
                GrimaldiSum(nValue, false);
                int stop_s=clock();
                cout << "Grimaldi sum execution time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << "ms" << endl;
                println();
                break;
            }
            case 4:
            {
                cout << "Identity Sum" << endl;
                int start_s=clock();
                identitySum(nValue);
                int stop_s=clock();
                cout << "Identity sum execution time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << "ms" << endl;
                println();
                break;
            }
            case 0:
            {
                cout << "Exiting..." << endl;
                exit = true;
                break;
            }
            default: cout << "Invalid choice. Exiting..." << endl;
                break;
        }
        cout << "...continue (y/n)? ";
        char response;
        cin >> response;
        if (response == 'n') exit = true;
        cout << "Exiting..." << endl;
    }
    return 0;
}