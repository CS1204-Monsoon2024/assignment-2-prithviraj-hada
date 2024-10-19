#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class HashTable {
private:
    vector<int> hashTable;
    int cap;
    int size;
    double loadFactor;

    int computeHash(int value) {
        return value % cap;
    }

    int getNextPrime(int number) {
        while (true) {
            bool prime = true;
            for (int i = 2; i * i <= number; i++) {
                if (number % i == 0) {
                    prime = false;
                    break;
                }
            }
            if (prime) return number;
            number++;
        }
    }

    void rehash() {
        int newcap = getNextPrime(cap * 2);
        vector<int> tempTable(newcap, -1);

        for (int i = 0; i < cap; i++) {
            if (hashTable[i] != -1 && hashTable[i] != -2) {
                int value = hashTable[i];
                int idx = value % newcap;
                int probe = 0;
                while (tempTable[(idx + probe * probe) % newcap] != -1) {
                    probe++;
                }
                tempTable[(idx + probe * probe) % newcap] = value;
            }
        }
        hashTable = tempTable;
        cap = newcap;
    }

public:
    HashTable(int initialcap = 5) {
        cap = getNextPrime(initialcap);
        hashTable = vector<int>(cap, -1);
        size = 0;
        loadFactor = 0.8;
    }

    void insert(int value) {
        if (size >= loadFactor * cap) {
            rehash();
        }
        int idx = computeHash(value);
        int probe = 0;

        while (probe <= cap / 2 + 1) {
            int idx2 = (idx + (probe * probe)) % cap;
            if (hashTable[idx2] == value) {
                cout << "Duplicate value insertion is not allowed" << endl;
                return;
            }
            if (hashTable[idx2] == -1 || hashTable[idx2] == -2) {
                hashTable[idx2] = value;
                size++;
                return;
            }
            probe++;
        }
        cout << "Max probing limit reached!" << endl;
    }

    void remove(int value) {
        int idx = computeHash(value);
        int probe = 0;

        while (probe <= cap / 2 + 1) {
            int idx2 = (idx + (probe * probe)) % cap;
            if (hashTable[idx2] == value) {
                hashTable[idx2] = -2; // Mark as deleted
                size--;
                return;
            }
            probe++;
        }
        cout << "Element not found" << endl;
    }

    int search(int value) {
        int idx = computeHash(value);
        int probe = 0;

        while (probe <= cap / 2 + 1) {
            int idx2 = (idx + (probe * probe)) % cap;
            if (hashTable[idx2] == value) {
                return idx2;
            }
            probe++;
        }
        return -1;
    }

    void printTable() {
        for (int i = 0; i < cap; i++) {
            if (hashTable[i] == -1 || hashTable[i] == -2) {
                cout << "- ";
            } else {
                cout << hashTable[i] << " ";
            }
        }
        cout << endl;
    }
};
