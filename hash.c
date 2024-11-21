#include <stdio.h>
#include <stdlib.h>

// Node structure for chaining
struct Node {
    int key;
    struct Node* next;
};

// Hash table structure for chaining
struct HashTableChaining {
    struct Node** table;
    int size;  // Size of the hash table
};

// Hash table structure for probing
struct HashTableProbing {
    int* table;
    int size;  // Size of the hash table
};

// Function to create a new node for chaining
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

// Function to create a hash table for chaining
struct HashTableChaining* createHashTableChaining(int size) {
    struct HashTableChaining* hashTable = (struct HashTableChaining*)malloc(sizeof(struct HashTableChaining));
    hashTable->size = size;
    hashTable->table = (struct Node**)malloc(size * sizeof(struct Node*));

    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;  // Initialize all buckets to NULL
    }

    return hashTable;
}

// Function to create a hash table for probing
struct HashTableProbing* createHashTableProbing(int size) {
    struct HashTableProbing* hashTable = (struct HashTableProbing*)malloc(sizeof(struct HashTableProbing));
    hashTable->size = size;
    hashTable->table = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        hashTable->table[i] = -1;  // Initialize all slots to -1 (indicating empty)
    }

    return hashTable;
}

// Hash function using modulo division
int hashFunction(int key, int size) {
    return key % size;
}

// Insert function for chaining
void insertChaining(struct HashTableChaining* hashTable, int key) {
    int index = hashFunction(key, hashTable->size);
    struct Node* newNode = createNode(key);

    // Insert the new node at the beginning of the chain
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;

    printf("Inserted %d at index %d\n", key, index);
}

// Insert function for linear probing
void insertLinearProbing(struct HashTableProbing* hashTable, int key) {
    int index = hashFunction(key, hashTable->size);
    int originalIndex = index;

    // Find next available slot
    while (hashTable->table[index] != -1) {
        printf("Collision occurred for %d at index %d, trying next index\n", key, index);
        index = (index + 1) % hashTable->size;  // Linear probing
        if (index == originalIndex) {
            printf("Table is full, cannot insert %d\n", key);
            return;  // Table is full
        }
    }

    hashTable->table[index] = key;
    printf("Inserted %d at index %d\n", key, index);
}

// Search function for linear probing
int searchLinearProbing(struct HashTableProbing* hashTable, int key) {
    int index = hashFunction(key, hashTable->size);
    int originalIndex = index;

    while (hashTable->table[index] != -1) {
        if (hashTable->table[index] == key) {
            printf("Found %d at index %d\n", key, index);
            return index;
        }
        index = (index + 1) % hashTable->size;  // Linear probing
        if (index == originalIndex) {
            break;  // We have checked the entire table
        }
    }

    printf("%d not found in the table\n", key);
    return -1;  // Not found
}

// Display function for chaining
void displayChaining(struct HashTableChaining* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        struct Node* current = hashTable->table[i];
        printf("Index %d: ", i);
        while (current != NULL) {
            printf("%d -> ", current->key);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Display function for probing
void displayProbing(struct HashTableProbing* hashTable) {