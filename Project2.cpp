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

// Linear probing code (used with coalesced chaining
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

// Insert a key and value into table
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

// Search for a key in a hash table
int search(node * table, string key){
    if (key.size() > 25)
    {
        char keyArr[key.size()];
        largeKey(key, keyArr);
        unsigned long long hashx = hx(keyArr, key.size(), 51);
        if (table[hashx].key == key)
        {
            cout << table[hashx].value << endl;
            return hashx;
        }
        else if (table[hashx].key == "/")
        {
            cout << key << " is not in the table." << endl;
            return -1;
        }
        else
        {
            int current = table[hashx].next;
            bool found = false;
            while (current != -1 and !found) {
                if (table[current].key == key) {
                    cout << table[current].value << endl;
                    found = true;
                }
                else
                {
                    current = table[current].next;
                }
            }
            if (!found)
            {
                cout << key << " is not in the table." << endl;
                return -1;
            }
            else
            {
                return current;
            }
        }
    }
    else
    {
        char keyArr[25];
        smallKey(key, keyArr);
        unsigned long long hashx = hx(keyArr, 25, 51);
        if (table[hashx].key == key)
        {
            cout << table[hashx].value << endl;
            return hashx;
        }
        else if (table[hashx].key == "/")
        {
            cout << key << " is not in the table." << endl;
            return -1;
        }
        else
        {
            int current = table[hashx].next;
            bool found = false;
            while (current != -1 and !found) {
                if (table[current].key == key) {
                    cout << table[current].value << endl;
                    found = true;
                }
                else
                {
                    current = table[current].next;
                }
            }
            if (!found) {
                cout << key << " is not in the table." << endl;
                return -1;
            }
            else
            {
                return current;
            }
        }
    }
}

// Delete a key from the table
void del(node *table, string key){
    int finder = search(table, key);
    if (finder == -1){
        cout << key << " not int the table." << endl;
    }
    else
    {
        if (table[finder].next == -1 and table[finder].prev == -1) {
            table[finder].key = "/";
            table[finder].value = "/";
        }
        else if (table[finder].next == -1 and table[finder].prev != -1){
            table[table[finder].prev].next = -1;
            table[finder].prev = -1;
            table[finder].key = "/";
            table[finder].value= "/";
        }
        else if (table[finder].next != -1 and table[finder].prev == -1){
            table[table[finder].next].prev = -1;
            table[finder].next = -1;
            table[finder].key = "/";
            table[finder].value= "/";
        }
        else{
            table[table[finder].next].prev = table[finder].prev;
            table[table[finder].prev].next = table[finder].next;
            table[finder].next = -1;
            table[finder].prev = -1;
            table[finder].key = "/";
            table[finder].value= "/";
        }
    }
}

// Display the Hash Table
void displayTable(node *table, int size)
{
    cout << endl << "Index" << "\t|" << setw(32) << "Key" << "|" << setw(20) << "Value" << "\t|" << "Next" << "\t|" << "Prev" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << i << "\t|" << setw(32) << table[i].key << "|" << setw(20) << table[i].value.substr(0, 10) << "\t|" << table[i].next << "\t|" << table[i].prev << endl;
    }
}

int main()
{
    //    cout.precision(100);
    
    // Set the file paths
    string titles = "/Users/xaviermartinez/Documents/CECS 328 Projects/Data Structures and Algorithms Projects/Data Structures and Algorithms Projects/Data-Structures-and-Algorithms-Repository/WikiTitles.txt";
    string leaks = "/Users/xaviermartinez/Documents/CECS 328 Projects/Data Structures and Algorithms Projects/Data Structures and Algorithms Projects/Data-Structures-and-Algorithms-Repository/wikileaks.txt";
    string wd = "/Users/xaviermartinez/Documents/CECS 328 Projects/Data Structures and Algorithms Projects/Data Structures and Algorithms Projects/Data-Structures-and-Algorithms-Repository/";
    
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
    // Exit program if file cannot be read - continue otherwise
    if (!wikiTitles)
    {
        cout << "ERROR: UNABLE TO OPEN INPUT DATA!" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        // Hash the wiki page title
        int pos = 0;
        while (getline(wikiTitles, key))
        {
            // Determine whether or not to add padding
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
        // Display perforance results
        cout << "The division method exhibited " << collisions(divisionMethodkeyues, 100) << " collisions!" << endl;
        cout << "The multiplication method exhibited " << collisions(multiplicationMethodkeyues, 100) << " collisions!" << endl;
        cout << endl;
    }
    // Close the IO reader
    wikiTitles.close();
    
    // Implementation of the hash data structure
    cout << "## Implementation of hash data structure ##" << endl;
    // Open the wiki titles to insert into the table
    string leak;
    ifstream wikileaks;
    wikileaks.open(leaks);
    // Exit program if file cannot be read - continue otherwise
    if (!wikileaks)
    {
        cout << "ERROR: UNABLE TO OPEN INPUT DATA!" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        // Hash and insert the key value pair
        // Every key in the "wikileaks.txt" file has a corresponding text file with the wiki page's summary
        while (getline(wikileaks, leak))
        {
            // File housekeeping
            string tmp = leak;
            leak.append(".txt");
            leak = wd + leak;
            string value;
            ifstream summary;
            // Open the wiki page summary for reading
            summary.open(leak);
            // Exit program if file cannot be read - continue otherwise
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
            // Insert key value pair into table
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
            // Close the summary reader
            summary.close();
        }
    }
    // Display the final table
    displayTable(table, 51);
    // Close the wiki titles reader
    wikileaks.close();
    
    // User-interface
    bool exit = false;
    while (!exit) {
        int choice = 0;
        cout << "(1) Search" << endl;
        cout << "(2) Insert New Title" << endl;
        cout << "(3) Delete a Title" << endl;
        cout << "(4) Exit" << endl;
        cout << "Enter a selection: ";
        cin >> choice;
        cin.clear();
        cin.ignore(1000, '\n');
        if (choice == 4) {
            exit = true;
        }
        else if (choice == 1){
            // Obtain a title to search
            string response = "";
            cout << "Enter a title: ";
            getline(cin, response);
            search(table, response);
        }
        else if (choice == 2){
            string title = "";
            string summary = "";
            cout << "Enter the name of the title: ";
            getline(cin, title);
            cout << "Enter the 1st paragraph summary: ";
            getline(cin, summary);
            if (title.size() > 25)
            {
                char keyArr[title.size()];
                largeKey(title, keyArr);
                unsigned long long hashx = hx(keyArr, title.size(), 51);
                insert(table, hashx, title, summary);
            }
            else
            {
                char keyArr[25];
                smallKey(title, keyArr);
                unsigned long long hashx = hx(keyArr, 25, 51);
                insert(table, hashx, title, summary);
            }
            displayTable(table, 51);
        }
        else if(choice == 3){
            string title = "";
            cout << "Enter the name of the title: ";
            getline(cin, title);
            del(table, title);
            displayTable(table, 51);
        }
    }
    return 0;
}