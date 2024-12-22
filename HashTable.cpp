#include <iostream>
#include <list>
#include <vector>
#include <cmath>

using namespace std;

class HashTable {
private:
    static const int EMPTY   = -1;  
    static const int DELETED = -2;  
    int capacity;                 
    std::vector<int> table;       
    int size;                     
    double load_factor_threshold = 0.8;

    
    int hashFunction(int key) {
        return key % capacity;
    }

public:
    HashTable(int initialSize) 
        : capacity(initialSize), table(initialSize, EMPTY), size(0) {
    }

    double loadFactor() {
        return static_cast<double>(size) / capacity;
    }

    void insert(int value) {
        
        if (loadFactor() > load_factor_threshold) {
            resize();
        }

        int hashIndex = hashFunction(value);
        int firstDeletedIndex = -1;  
        int i = 0;

        while (i < capacity) {
            int probeIndex = (hashIndex + i * i) % capacity;

            
            if (table[probeIndex] == EMPTY) {
                if (firstDeletedIndex != -1) {
                    
                    table[firstDeletedIndex] = value;
                } else {
                    table[probeIndex] = value;
                }
                size++;
                return;
            }
            
            else if (table[probeIndex] == DELETED) {
                if (firstDeletedIndex == -1) {
                    firstDeletedIndex = probeIndex;
                }
            }
            
            else if (table[probeIndex] == value) {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }
            i++;
        }

        if (firstDeletedIndex != -1) {
            
            table[firstDeletedIndex] = value;
            size++;
        } else {
            
            cout << "Max probing limit reached!" << endl;
        }
    }

    void remove(int value) {
        int hashIndex = hashFunction(value);
        int i = 0;

        while (i < capacity) {
            int probeIndex = (hashIndex + i * i) % capacity;

            if (table[probeIndex] == EMPTY) {
                cout << "Element not found" << endl;
                return;
            }
            
            if (table[probeIndex] == value) {
                table[probeIndex] = DELETED;
                size--;
                return;
            }
            i++;
        }
        
        cout << "Element not found" << endl;
    }
    
    int search(int value) {
        int hashIndex = hashFunction(value);
        int i = 0;

        while (i < capacity) {
            int probeIndex = (hashIndex + i * i) % capacity;

            if (table[probeIndex] == EMPTY) {
                return -1;
            }
            
            if (table[probeIndex] == value) {
                return probeIndex;
            }
            
            i++;
        }
        return -1; 
    }

    void resize() {
        
        std::vector<int> oldTable = table;
        
        int newCapacity = next_prime(capacity * 2);

        std::vector<int> newTable(newCapacity, EMPTY);
        table = newTable;
        capacity = newCapacity;
        size = 0;

        for (int val : oldTable) {
            if (val != EMPTY && val != DELETED) {
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
            if (table[i] == EMPTY || table[i] == DELETED) {
                cout << "- ";
            } else {
                cout << table[i] << " ";
            }
        }
        cout << endl;
    }
};
