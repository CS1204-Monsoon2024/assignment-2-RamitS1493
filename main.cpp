#include "HashTable.cpp"

int main() {
    int initialSize = 7; 
    HashTable ht(initialSize);

    // Example test case
    ht.insert(1);
    ht.printTable();
    ht.insert(6);
    ht.printTable();
    ht.insert(15);
    ht.printTable(); 
    ht.insert(25);
    ht.printTable();
    ht.remove(15);
    ht.printTable();
    ht.insert(29);  
    ht.printTable(); 

    int find = ht.search(22);
    std::cout << "Found at:" << find << std::endl;

    return 0;
}

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
    
    HashTable(int size) : capacity(size), table(size, -1), size(0) {}


    double loadFactor() {
        return static_cast<double>(size) / capacity;
    }

  
    void insert(int value) {
        if (loadFactor() > load_factor_threshold) {
            resize();
        }

        int i = 0;
        int key;

        while (i < capacity) { 
            key = (hashFunction(value) + i * i) % capacity;
            if (table[key] == -1) {
                table[key] = value; 
                size++;
                return;
            } else if (table[key] == value) {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }
            i++;
        }
        cout << "Max probing limit reached!" << endl;
    }

   
    void remove(int value) {
        int i = 0;
        int key;
        while (i < capacity) { // Use capacity instead of max
            key = (hashFunction(value) + i * i) % capacity;
            if (table[key] == -1) {
                cout << "Element not found" << endl;
                return;
            }
            if (table[key] == value) {
                table[key] = -1;
                size--;
                return;
            }
            i++;
        }
        cout << "Element not found" << endl;
    }

    
    int search(int value) {
        int i = 0;
        int key;
        while (i < capacity) { 
            key = (hashFunction(value) + i * i) % capacity;
            if (table[key] == -1) {
                return -1; 
            }
            if (table[key] == value) {
                return key; 
            }
            i++;
        }
        return -1;
    }

    void resize() {
        std::vector<int> old_table = table;
        int new_capacity = next_prime(capacity * 2);
        std::vector<int> new_table(new_capacity, -1);
        table = new_table; 
        capacity = new_capacity;
        size = 0;  

        for (int value : old_table) {
            if (value != -1) {
                insert(value);
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
            n += 1;
        }
        return n;
    }

    // Print the hash table
    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] == -1) {
                cout << "-" << " ";
            } else {
                cout << table[i] << " "; 
            }
        }
        cout << endl; 
    }
};\
