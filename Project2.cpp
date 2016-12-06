//
//  Project2.cpp
//  Data Structures and Algorithms Projects
//
//  Created by Xavier Martinez on 12/5/16.
//  Copyright © 2016 Xavier Martinez. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <math.h>
#include <ctime>
#include <fstream>
#include <string>
#include <set>
using namespace std;

// Ensure minimum size of key is 25 by padding
void smallKey(string key, char *newKey)
{
    for (int i = 0; i < key.size(); i++)
    {
        newKey[i] = key[i];
    }
    for (int i = key.size(); i < 25; i++)
    {
        newKey[i] = (char)32;
    }
}

// Copy key into char array
void largeKey(string key, char *newKey)
{
    for (int i = 0; i < key.size(); i++)
    {
        newKey[i] = key[i];
    }
}

// Division Method
unsigned long long int hx(char *key, int size, int tableSize)
{
    unsigned long long int hash = 0;
    cout << "\"";
    for (int i = 0; i < size; i++)
    {
        cout << key[i];
        hash += (unsigned long long int)key[i] * (unsigned long long int)powl((long double)37, (long double)i);
    }
    cout << "\" hashes to: ";
    hash = hash % (unsigned long long int)tableSize;
    cout << hash << endl;
    return hash;
}

// Multiplication Method
unsigned long long hy(char *key, int size, int tableSize)
{
    unsigned long long hash = 0;
    cout << "\"";
    for (int i = 0; i < size; i++)
    {
        cout << key[i];
        hash += (unsigned long long)key[i] * (unsigned long long)powl((long double)37, (long double)i);
    }
    long double k = hash * ((long double)0.618033989);
    long double ro = floorl(k);
    long double sub = (long double)k - (long double)ro;
    long double mul = ((long double)tableSize) * sub;
    cout << "\" hashes to: ";
    hash = floorl(mul);
    cout << hash << endl;
    return hash;
}

// Measure the number of collisions
int collisions(unsigned long long *keyues, int size)
{
    set<unsigned long long> collisions;
    set<unsigned long long> collisionkeyues;
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            if (i == j)
            {
                continue;
            }
            else
            {
                if (keyues[i] == keyues[j])
                {
                    collisions.insert(i);
                    collisionkeyues.insert(keyues[i]);
                    break;
                }
            }
        }
    }

    // Debug Code
    //    for (set<unsigned long long>::iterator it=collisionkeyues.begin(); it!=collisionkeyues.end(); ++it)
    //        cout << ' ' << *it;
    //    std::cout<<"\n";

    return collisions.size();
}

// Node structure
struct node
{
    string key;
    string value;
    int next;
    int prev;
};

void linearProbing(node *table, int hash, int prev, string key, string value)
{
    bool placed = false;
    int probe = (hash + 1) % 51;
    while (!placed)
    {
        if (table[probe].key == "/")
        {
            table[probe].key = key;
            table[probe].value = value;
            table[prev].next = probe;
            table[probe].prev = prev;
            placed = true;
        }
        else
        {
            probe = (probe + 1) % 51;
        }
    }
}

void insert(node *table, int hash, string key, string value)
{
    if (table[hash].key == "/")
    {
        table[hash].key = key;
        table[hash].value = value;
    }
    else
    {
        if (table[hash].next == -1)
        {
            linearProbing(table, hash, hash, key, value);
        }
        else
        {
            int current = table[hash].next;
            bool found = false;
            while (!found)
            {
                if (table[current].next == -1)
                {
                    found = true;
                    linearProbing(table, hash, current, key, value);
                }
                else
                {
                    current = table[current].next;
                }
            }
        }
    }
}

void search(node * table, string key){
    if (key.size() > 25)
            {
                char keyArr[key.size()];
                largeKey(key, keyArr);
                unsigned long long hashx = hx(keyArr, key.size(), 301);
                if (table[hashx] == key)
                {
                    cout << table[hashx].value << endl;
                }
            }
            else
            {
                char keyArr[25];
                smallKey(key, keyArr);
                unsigned long long hashx = hx(keyArr, 25, 301);
                unsigned long long hashy = hy(keyArr, 25, 301);
                divisionMethodkeyues[pos] = hashx;
                multiplicationMethodkeyues[pos] = hashy;
            }
}

void displayTable(node *table, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << i << "\t|" << setw(32) << table[i].key << "|" << setw(60) << table[i].value.substr(0, 55) << "\t|" << table[i].next << "\t|" << table[i].prev << endl;
    }
}

int main()
{
    cout.precision(100);
    string titles = "/home/xavier/git-repositories/Data-Structures-and-Algorithms-Repository/WikiTitles.txt";
    string leaks = "/home/xavier/git-repositories/Data-Structures-and-Algorithms-Repository/wikileaks.txt";
    string wd = "/home/xavier/git-repositories/Data-Structures-and-Algorithms-Repository/";
    // Implementing the hash data structure
    node table[51];
    for (int i = 0; i < 51; i++)
    {
        table[i].key = "/";
        table[i].value = "/";
        table[i].next = -1;
        table[i].prev = -1;
    }

    // Declare Variables to be used in performance test
    string key;
    unsigned long long divisionMethodkeyues[100];
    unsigned long long multiplicationMethodkeyues[100];

    // Open the 100 Wiki Titles for reading.
    ifstream wikiTitles;
    wikiTitles.open(titles);
    if (!wikiTitles)
    {
        cout << "ERROR: UNABLE TO OPEN INPUT DATA!" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        int pos = 0;
        while (getline(wikiTitles, key))
        {
            // Determine whther or not to add padding
            if (key.size() > 25)
            {
                char keyArr[key.size()];
                largeKey(key, keyArr);
                unsigned long long hashx = hx(keyArr, key.size(), 301);
                unsigned long long hashy = hy(keyArr, key.size(), 301);
                divisionMethodkeyues[pos] = hashx;
                multiplicationMethodkeyues[pos] = hashy;
            }
            else
            {
                char keyArr[25];
                smallKey(key, keyArr);
                unsigned long long hashx = hx(keyArr, 25, 301);
                unsigned long long hashy = hy(keyArr, 25, 301);
                divisionMethodkeyues[pos] = hashx;
                multiplicationMethodkeyues[pos] = hashy;
            }
            pos++;
        }
        cout << "The division method exhibited " << collisions(divisionMethodkeyues, 100) << " collisions!" << endl;
        cout << "The multiplication method exhibited " << collisions(multiplicationMethodkeyues, 100) << " collisions!" << endl;
        cout << endl;
    }
    wikiTitles.close();

    // Implementation of the hash data structure
    cout << "## Implementation of hash data structure ##" << endl;
    string leak;
    ifstream wikileaks;
    wikileaks.open(leaks);
    if (!wikileaks)
    {
        cout << "ERROR: UNABLE TO OPEN INPUT DATA!" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        while (getline(wikileaks, leak))
        {
            string tmp = leak;
            leak.append(".txt");
            leak = wd + leak;
            string value;
            ifstream summary;
            summary.open(leak);
            if (!summary)
            {
                cout << "ERROR: UNABLE TO OPEN SUMMARY DATA!" << endl;
                exit(EXIT_FAILURE);
            }
            else
            {
                getline(summary, value);
            }
            // Determine whether or not to add padding
            if (tmp.size() > 25)
            {
                char keyArr[tmp.size()];
                largeKey(tmp, keyArr);
                unsigned long long hashx = hx(keyArr, tmp.size(), 51);
                insert(table, hashx, tmp, value);
            }
            else
            {
                char keyArr[25];
                smallKey(tmp, keyArr);
                unsigned long long hashx = hx(keyArr, 25, 51);
                insert(table, hashx, tmp, value);
            }
            summary.close();
        }
    }
    displayTable(table, 51);
    wikileaks.close();
    return 0;
}