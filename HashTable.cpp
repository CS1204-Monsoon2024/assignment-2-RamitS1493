#include <iostream>
#include <list>
#include <vector>
#include <cmath>

using namespace std;

class HashTable {
private:
    int capacity;                          
    std::vector<int> table;               
    int size;                              
    double load_factor_threshold = 0.8;    

    
    int hashFunction(int key) {
        return key % capacity;
    }

public:
    
    HashTable(int initialSize) : capacity(initialSize), table(initialSize, -1), size(0) {
    }

    
    double loadFactor() {
        return static_cast<double>(size) / capacity;
    }

    
    void insert(int value) {
        
        if (loadFactor() > load_factor_threshold) {
            resize();
        }

        int i = 0;
        int keyIndex;

        
        while (i < capacity) {
            keyIndex = (hashFunction(value) + i * i) % capacity;
            
            
            if (table[keyIndex] == -1) {
                table[keyIndex] = value;
                size++;
                return;
            }
            
            else if (table[keyIndex] == value) {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }
            i++;
        }

        
        cout << "Max probing limit reached!" << endl;
    }

    
    void remove(int value) {
        int i = 0;
        int keyIndex;

        while (i < capacity) {
            keyIndex = (hashFunction(value) + i * i) % capacity;
            
            
            if (table[keyIndex] == -1) {
                cout << "Element not found" << endl;
                return;
            }
            
            if (table[keyIndex] == value) {
                table[keyIndex] = -1;
                size--;
                return;
            }
            i++;
        }
        
        cout << "Element not found" << endl;
    }

    
    int search(int value) {
        int i = 0;
        int keyIndex;

        while (i < capacity) {
            keyIndex = (hashFunction(value) + i * i) % capacity;
            
            
            if (table[keyIndex] == -1) {
                return -1;
            }
            
            if (table[keyIndex] == value) {
                return keyIndex;
            }
            i++;
        }
        return -1; 
    }

    
    void resize() {
        
        std::vector<int> oldTable = table;

        
        int newCapacity = next_prime(capacity * 2);

        
        std::vector<int> newTable(newCapacity, -1);
        table = newTable;
        capacity = newCapacity;
        size = 0;

        
        for (int val : oldTable) {
            if (val != -1) {
                insert(val);
            }
        }
    }

    
    bool is_prime(int num) {
        if (num <= 1) {
            return false;
        }
        for (int i = 2; i <= sqrt(num); i++) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }

    
    int next_prime(int n) {
        while (!is_prime(n)) {
            n++;
        }
        return n;
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
