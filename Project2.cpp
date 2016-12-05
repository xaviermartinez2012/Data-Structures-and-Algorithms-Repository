//
//  Project2.cpp
//  Data Structures and Algorithms Projects
//
//  Created by Xavier Martinez on 12/5/16.
//  Copyright © 2016 Xavier Martinez. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <ctime>
#include <fstream>
#include <string>
#include <set>
using namespace std;

// Ensure minimum size of key is 25 by padding
void smallKey(string key, char * newKey){
    for (int i = 0; i < key.size(); i ++) {
        newKey[i] = key[i];
    }
    for (int i = key.size(); i < 25; i ++) {
        newKey [i] = (char) 32;
    }
}

// Copy key into char array
void largeKey(string key, char * newKey){
    for (int i = 0; i < key.size(); i ++) {
        newKey[i] = key[i];
    }
}

// Division Method
unsigned long long hx(char * key, int size){
    unsigned long long hash;
    cout << "\"";
    for (int i = 0; i < size; i++) {
        cout << key[i];
        hash += (unsigned long long) key[i] * (unsigned long long) pow((double) 37, (double) i);
    }
    cout << "\" hashes to: ";
    hash = hash % 301;
    cout << hash << endl;
    return hash;
}

// Multipliation Method
unsigned long long hy(char * key, int size){
    unsigned long long hash;
    cout << "\"";
    for (int i = 0; i < size; i++) {
        cout << key[i];
        hash += (unsigned long long) key[i] * (unsigned long long) pow((double) 37, (double) i);
    }
    long double k = (long double)hash * (long double)0.618033989;
    long double ro = floorl(k);
    long double sub = k - ro;
    cout << "\" hashes to: ";
    hash = floorl(((long double)301.0) * sub);
    cout << hash << endl;
    return hash;
}

// Measure the number of collisions
int collisions(unsigned long long * values, int size){
    set<unsigned long long> collisions;
    set<unsigned long long> collisionValues;
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (i == j) {
                continue;
            }
            else{
                if (values[i] == values[j]) {
                    collisions.insert(i);
                    collisionValues.insert(values[i]);
                    break;
                }
            }
        }
    }
    
// Debug Code
//    for (set<unsigned long long>::iterator it=collisionValues.begin(); it!=collisionValues.end(); ++it)
//        cout << ' ' << *it;
//    std::cout<<"\n";
    
    return collisions.size();
}

struct node{
    string val;
    int next;
    int prev;
};

void linearProbing(node * table, int hash, int prev, string key){
    bool placed = false;
    int probe = (hash + 1) % 301;
    while(!placed){
        if (table[probe].val == "/") {
            table[probe].val = key;
            table[hash].next = probe;
            table[probe].prev = prev;
            placed = true;
        }
        else{
            probe = (probe + 1) % 301;
        }
    }
}

void insert(node * table, unsigned long long hash, string key){
    if (table[hash].val == "/") {
        table[hash].val = key;
    }
    else{
        if (table[hash].next == -1) {
            linearProbing(table, hash, hash, key);
        }
        else {
            int current = table[hash].next;
            bool found = false;
            while (!found) {
                if (table[current].next == -1) {
                    found = true;
                    linearProbing(table, hash, current, key);
                }
                else{
                    current = table[current].next;
                }
            }
        }
        
    }
}

void displayTable(node * table, int size){
    for (int i = 0; i < size; i++){
        cout << i << "\t|" << table[i].val << "\t|" << table[i].next << "\t|" << table[i].prev << endl;
    }
}


int main(){
    cout.precision(40);
    
    // Declare Variables to be used in performance test
    string key;
    unsigned long long divisionMethodValues[100];
    unsigned long long multiplicationMethodValues[100];
    
    // Open the 100 Wiki Titles for reading.
    ifstream wikiTitles;
    wikiTitles.open("/Users/xaviermartinez/Documents/CECS 328 Projects/Data Structures and Algorithms Projects/Data Structures and Algorithms Projects/Data-Structures-and-Algorithms-Repository/WikiTitles.txt");
    if(!wikiTitles)
    {
        cout << "ERROR: UNABLE TO OPEN INPUT DATA!" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        // Test the Division Method
        cout << "## DIVISION METHOD ##" << endl;
        int pos = 0;
        while(getline(wikiTitles, key)){
            // Determine whther or not to add padding
            if (key.size() > 25) {
                char keyArr [key.size()];
                largeKey(key, keyArr);
                divisionMethodValues[pos] = hx(keyArr, key.size());
            }
            else {
                char keyArr [25];
                smallKey(key, keyArr);
                divisionMethodValues[pos] = hx(keyArr, 25);
            }
            pos++;
        }
        cout << "The division method exhibited " << collisions(divisionMethodValues, 100) << " collisions!" << endl;
        
        // Clear reader to start over from the beginning of the file
        wikiTitles.clear();
        wikiTitles.seekg(0, ios::beg);
        
        // Test the multiplication method
        cout << "## MULTIPLICATION METHOD ##" << endl;
        pos = 0;
        while(getline(wikiTitles, key)){
            // Determine whther or not to add padding
            if (key.size() > 25) {
                char keyArr [key.size()];
                largeKey(key, keyArr);
                multiplicationMethodValues[pos] = hy(keyArr, key.size());
            }
            else {
                char keyArr [25];
                smallKey(key, keyArr);
                multiplicationMethodValues[pos] = hy(keyArr, 25);
            }
            pos++;
        }
        cout << "The multiplication method exhibited " << collisions(multiplicationMethodValues, 100) << " collisions!" << endl;
    }
    
    // Begin implementing the hash data structure
    node table [100];
    for (int i = 0; i < 100; i ++){
        table[i].val = "/";
        table[i].next = -1;
        table[i].prev = -1;
    }
    
    // Clear reader to start over from the beginning of the file
    wikiTitles.clear();
    wikiTitles.seekg(0, ios::beg);
    
    while(getline(wikiTitles, key)){
        // Determine whther or not to add padding
        if (key.size() > 25) {
            char keyArr [key.size()];
            largeKey(key, keyArr);
            unsigned long long hash = hx(keyArr, key.size());
            insert(table, hash, key);
        }
        else {
            char keyArr [25];
            smallKey(key, keyArr);
            unsigned long long hash = hx(keyArr, 25);
            insert(table, hash, key);
        }
    }
    displayTable(table, 100);
    return 0;
}