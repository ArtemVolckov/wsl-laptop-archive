#pragma once

#define FACTOR 0.75

typedef struct ListNode {
    char* key;
    struct ListNode* next;
} ListNode;

typedef struct Item {
    char* command;
    ListNode* keys;
    struct Item* next; 
} Item;

typedef struct Hashmap {
    Item** items;
    double factor;
    size_t capacity;
    size_t count;
} Hashmap;

size_t get_hash(const char* str, size_t capacity);

// Non-dynamic memory allocation is required for h

void hashmap_init(Hashmap* h, size_t capacity);
void hashmap_add(Hashmap* h, char* command, char* key_arr[], int key_arr_size);
void hashmap_print(Hashmap* h);
void hashmap_free(Hashmap* h);
