default: HashTable.out

HashTable.out: HashTable.cpp
    g++ -o HashTable.out HashTable.cpp

clean:
    rm -f HashTable.out
