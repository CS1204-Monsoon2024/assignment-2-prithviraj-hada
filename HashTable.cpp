#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;
    std::vector<bool> occupied;
    int size;
    int count;
    const double loadFactorThreshold = 0.8;

    int hash(int key) {
        return key % size;
    }

    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    void resize() {
        int newSize = nextPrime(size * 2);
        std::vector<int> newTable(newSize, -1);
        std::vector<bool> newOccupied(newSize, false);

        std::cout << "Resizing table to new size: " << newSize << std::endl;

        for (int i = 0; i < size; i++) {
            if (occupied[i]) {
                int key = table[i];
                int hashValue = key % newSize;
                int j = 0;
                while (newOccupied[(hashValue + j * j) % newSize]) {
                    j++;
                }
                newTable[(hashValue + j * j) % newSize] = key;
                newOccupied[(hashValue + j * j) % newSize] = true;
            }
        }

        table = newTable;
        occupied = newOccupied;
        size = newSize;
    }

public:
    HashTable(int initialSize) {
        size = nextPrime(initialSize);
        table.resize(size, -1);
        occupied.resize(size, false);
        count = 0;
        std::cout << "Initialized hash table with size: " << size << std::endl;
    }

    void insert(int key) {
        if ((double)count / size >= loadFactorThreshold) {
            resize();
        }

        int hashValue = hash(key);
        int i = 0;
        while (occupied[(hashValue + i * i) % size]) {
            i++;
        }
        table[(hashValue + i * i) % size] = key;
        occupied[(hashValue + i * i) % size] = true;
        count++;
        std::cout << "Inserted key " << key << " at index " << (hashValue + i * i) % size << std::endl;
    }

    bool search(int key) {
        int hashValue = hash(key);
        int i = 0;
        while (occupied[(hashValue + i * i) % size]) {
            if (table[(hashValue + i * i) % size] == key) {
                std::cout << "Found key " << key << " at index " << (hashValue + i * i) % size << std::endl;
                return true;
            }
            i++;
        }
        std::cout << "Key " << key << " not found" << std::endl;
        return false;
    }

    void remove(int key) {
        int hashValue = hash(key);
        int i = 0;
        while (occupied[(hashValue + i * i) % size]) {
            if (table[(hashValue + i * i) % size] == key) {
                table[(hashValue + i * i) % size] = -1;
                occupied[(hashValue + i * i) % size] = false;
                count--;
                std::cout << "Removed key " << key << " from index " << (hashValue + i * i) % size << std::endl;
                return;
            }
            i++;
        }
        std::cout << "Key " << key << " not found for removal" << std::endl;
    }

    void printTable() {
        std::cout << "Hash Table: ";
        for (int i = 0; i < size; i++) {
            if (occupied[i]) {
                std::cout << table[i] << " ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
    }
};
