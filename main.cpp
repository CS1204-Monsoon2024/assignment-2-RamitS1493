#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class HashTable {
private:
    int capacity;                
    vector<int> table;           
    int size;                    
    double load_factor_threshold = 0.8; 

    // the hashfunction
    int hashFunction(int key) {
        return key % capacity;
    }

    // For checking the prime number
    bool is_prime(int num) {
        if (num <= 1) return false;
        for (int i = 2; i <= sqrt(num); i++) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }

    // Finding next prime using while loop
    int next_prime(int n) {
        while (!is_prime(n)) {
            n++;
        }
        return n;
    }
    double loadFactor() {
        return static_cast<double>(size) / capacity;
    }

    // Resizing and rehashing to fix
    void resize() {
        vector<int> old_table = table;
        int new_capacity = next_prime(capacity * 2);
        vector<int> new_table(new_capacity, -1);
        table = new_table; 
        capacity = new_capacity;
        size = 0; 

        for (int value : old_table) {
            if (value != -1) {
                insert(value);  
            }
        }
    }

public:
    HashTable(int initialSize) : capacity(initialSize), table(initialSize, -1), size(0) {
    }

    void insert(int value) {
        if (loadFactor() > load_factor_threshold) {
            resize();
        }
        
        int i = 0;
        int probeIndex;

        while (i < capacity) {
            probeIndex = (hashFunction(value) + i*i) % capacity;
            
            if (table[probeIndex] == -1) {
                table[probeIndex] = value;
                size++;
                return;
            }
            else if (table[probeIndex] == value) {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }
            i++;
        }
        
        cout << "Max probing limit reached!" << endl;
    }

    void remove(int value) {
        int i = 0;
        int probeIndex;

        while (i < capacity) {
            probeIndex = (hashFunction(value) + i*i) % capacity;
            
            if (table[probeIndex] == -1) {
                cout << "Element not found" << endl;
                return;
            }
            
            if (table[probeIndex] == value) {
                table[probeIndex] = -1;
                size--;
                return;
            }
            i++;
        }
        cout << "Element not found" << endl;
    }

    int search(int value) {
        int i = 0;
        int probeIndex;
        
        while (i < capacity) {
            probeIndex = (hashFunction(value) + i*i) % capacity;
            
            
            if (table[probeIndex] == -1) {
                return -1;
            }
            
            if (table[probeIndex] == value) {
                return probeIndex;
            }
            i++;
        }
        return -1;
    }

    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] == -1) {
                cout << "- ";
            } else {
                cout << table[i] << " ";
            }
        }
        cout << endl;
    }
};
