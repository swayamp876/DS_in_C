#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;


typedef struct {
    int size;
    Node** buckets;
} HashMap;

HashMap* createMap(int size) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->size = size;
    map->buckets = (Node**)calloc(size, sizeof(Node*));
    return map;
}

unsigned int hash(int key, int size) {
    return (unsigned int)(key < 0 ? -key : key) % size;
}

void insert(HashMap* map, int key, int value) {
    unsigned int h = hash(key, map->size);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = map->buckets[h];
    map->buckets[h] = newNode;
}

int find(HashMap* map, int key) {
    unsigned int h = hash(key, map->size);
    Node* curr = map->buckets[h];
    while (curr != NULL) {
        if (curr->key == key) {
            return curr->value;
        }
        curr = curr->next;
    }
    return -1;
}

void freeMap(HashMap* map) {
    for (int i = 0; i < map->size; i++) {
        Node* curr = map->buckets[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(map->buckets);
    free(map); 
}


int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashMap* map = createMap(numsSize * 2);
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int foundIndex = find(map, complement);
        
        if (foundIndex != -1) {
            result[0] = foundIndex;
            result[1] = i;
            freeMap(map);
            return result;
        }
        
        insert(map, nums[i], i);
    }

    freeMap(map);
    *returnSize = 0;
    return NULL;
}