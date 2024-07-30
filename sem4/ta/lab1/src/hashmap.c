#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashmap.h"

size_t get_hash(const char* str, size_t capacity) {
    size_t sum = 0;

    for(int i = 0; i < strlen(str); ++i)
        sum += str[i] * (i + 1);
    return (sum % capacity);
}

void hashmap_init(Hashmap* h, size_t capacity) {
    if (h == NULL && capacity < 1)
        abort();
    h->count = 0;
    h->capacity = capacity;
    h->factor = FACTOR;
    h->items = (Item**) calloc(capacity, sizeof(Item*)); 
}

// Previos version of keylist_push function

#if 0
void keylist_push(ListNode** list_ptr_ptr, char* key_arr[], int key_arr_size) {
    ListNode* list_ptr_tmp = NULL;
    for (int i = 0; i < key_arr_size; ++i) {
        ListNode* new_list_node = (ListNode*) calloc(1, sizeof(ListNode));
        new_list_node->key = key_arr[i];
        *list_ptr_ptr = new_list_node;

        if (i == 0) 
            list_ptr_tmp = *list_ptr_ptr;
        *list_ptr_ptr = (*list_ptr_ptr)->next;
    }
    *list_ptr_ptr = list_ptr_tmp;
}
#endif

void keylist_push(Hashmap* h, ListNode* list_ptr, char* key_arr[], int key_arr_size, int offset) {
    ListNode* list_tmp = NULL;

    for (int i = offset; i < key_arr_size; ++i) {
        list_tmp = list_ptr;
        list_ptr = (ListNode*) calloc(1, sizeof(ListNode));
        list_ptr->key = key_arr[i];
        list_tmp->next = list_ptr;
    } 
    h->count += 1;
}

void gen_item_list(Hashmap* h, size_t hash, char* command, char* key_arr[], Item* item_tmp, ListNode** list_save) {
    Item* new_item = (Item*) calloc(1, sizeof(Item));
    ListNode* list_ptr = NULL;
    new_item->command = command;

    if (item_tmp == NULL)
        h->items[hash] = new_item;
    else 
        item_tmp->next = new_item;
    list_ptr = (ListNode*) calloc(1, sizeof(ListNode));
    list_ptr->key = key_arr[0];
    new_item->keys = list_ptr;
    *list_save = list_ptr;
}

void collect_item_fields(Item* item_ptr, char** command, char*** key_arr, int* key_arr_size) {
    int counter = 0;
    ListNode* list_ptr = item_ptr->keys;
    *command = item_ptr->command;
    
    while (list_ptr != NULL) {
        counter += 1;
        list_ptr = list_ptr->next;
    }
    *key_arr = (char**) calloc(counter, sizeof(char*));
    list_ptr = item_ptr->keys; 
    *key_arr_size = counter;
    counter = 0;

    while (list_ptr != NULL) {
        (*key_arr)[counter] = list_ptr->key;
        counter += 1;
        list_ptr = list_ptr->next;
    }
}

void hashmap_resize(Hashmap* h) {
    Hashmap new_h;
    int old_capacity = h->capacity;
    size_t count = h->count;
    hashmap_init(&new_h, old_capacity * 2);
    Item* item_ptr = NULL;
    char* command = NULL;
    char** key_arr = NULL;
    int key_arr_size = 0;

    for (size_t i = 0; i < old_capacity && count != 0; ++i) {
        item_ptr = h->items[i];

        if (item_ptr != NULL)  
            count -= 1;

        while (item_ptr != NULL) {
            collect_item_fields(item_ptr, &command, &key_arr, &key_arr_size);
            hashmap_add(&new_h, command, key_arr, key_arr_size);
            free(key_arr);
            item_ptr = item_ptr->next; 
        } 
    }
    hashmap_free(h);
    *h = new_h;
}

void hashmap_add(Hashmap* h, char* command, char* key_arr[], int key_arr_size) {
    if ((h->count / h->capacity) > h->factor)
        hashmap_resize(h);
    size_t hash = get_hash(command, h->capacity);
    Item* item_ptr = h->items[hash], *item_tmp = NULL;
    ListNode* list_ptr = NULL;

    while (item_ptr != NULL) {
        if (item_ptr->command == command) {
            list_ptr = item_ptr->keys;

            while (list_ptr->next != NULL) {
                list_ptr = list_ptr->next;
            }
            keylist_push(h, list_ptr, key_arr, key_arr_size, 0);
            return;
        }
        item_tmp = item_ptr;
        item_ptr = item_ptr->next;
    }
    gen_item_list(h, hash, command, key_arr, item_tmp, &list_ptr);
    keylist_push(h, list_ptr, key_arr, key_arr_size, 1);
}

void hashmap_print(Hashmap* h) {
    if (h == NULL)
        abort();
    Item* item_ptr = NULL; 
    ListNode* list_ptr = NULL;
    size_t count = h->count;

    for (size_t i = 0; i < h->capacity && count != 0; ++i) {
        item_ptr = h->items[i];

        if (item_ptr != NULL) 
            count -= 1;

        while (item_ptr != NULL) {
            printf("%s", item_ptr->command);
            list_ptr = item_ptr->keys;

            while (list_ptr != NULL) {
                printf(" %s", list_ptr->key);
                list_ptr = list_ptr->next;
            }
            printf("\n");
            item_ptr = item_ptr->next; 
        } 
    }
}

void hashmap_free(Hashmap* h) {
    if (h == NULL)
        abort();
    Item* item_ptr = NULL, *item_tmp = NULL;
    ListNode* list_ptr = NULL, *list_tmp = NULL;
    size_t count = h->count;

    for (size_t i = 0; i < h->capacity && count != 0; ++i) {
        item_ptr = h->items[i];

        if (item_ptr != NULL)  
            count -= 1;

        while (item_ptr != NULL) {
            list_ptr = item_ptr->keys;

            while (list_ptr != NULL) {
                list_tmp = list_ptr->next;
                free(list_ptr);
                list_ptr = list_tmp;
            }
            item_tmp = item_ptr->next;
            free(item_ptr);
            item_ptr = item_tmp; 
        } 
    }
    free(h->items);
}

// Tests

#if 0
int main() {
    Hashmap h;
    char* command = "gcc";
    char* command2 = "tmux";
    char* key_arr[] = { "-g", "-DNDEBUG", "-o" };
    char* key_arr2[] = { "-s" };
    int key_arr_size = sizeof(key_arr) / sizeof(key_arr[0]);
    int key_arr2_size = sizeof(key_arr2) / sizeof(key_arr2[0]);

    hashmap_init(&h, 1);
    hashmap_add(&h, command, key_arr, key_arr_size);
    hashmap_add(&h, command, key_arr, key_arr_size);
    hashmap_add(&h, command2, key_arr2, key_arr2_size);
    hashmap_print(&h);
    hashmap_free(&h);
}
#endif