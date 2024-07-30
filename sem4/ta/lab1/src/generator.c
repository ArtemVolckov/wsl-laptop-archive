#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MIN_STR_SIZE 4

void gen_str(char* str, size_t max_add_size, int* position, const char* char_set, size_t char_set_len) { 
    if (max_add_size == 0) 
        return;
    size_t size = (rand() % max_add_size);
    
    for (int i = 0; i < size; ++i) {
        str[*position] = char_set[rand() % char_set_len];
        *position += 1;
    }
}

void gen_char(char* str, int* position, const char* char_set, size_t char_set_len) {
    str[*position] = char_set[rand() % char_set_len];
    *position += 1;
}

void gen_strings(int strings, size_t max_add_command_size, size_t max_add_keylist_size) {
    if (strings < 1 && max_add_command_size < 0 && max_add_keylist_size < 0)
        abort();
    int str_size = MIN_STR_SIZE + max_add_command_size + max_add_keylist_size;
    char* str = (char*) calloc(str_size, sizeof(char));
    int position = 0;

    const char* command_char_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
    const char* blank_char_set = "\t ";
    const char* keylist_char_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\t ";
    const char* allnum_char_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    size_t command_char_set_len = strlen(command_char_set); 
    size_t blank_char_set_len = strlen(blank_char_set); 
    size_t keylist_char_set_len = strlen(keylist_char_set); 
    size_t allnum_char_set_len = strlen(allnum_char_set);

    srand(time(0));

    for (int i = 0; i < strings; ++i) {
        gen_char(str, &position, command_char_set, command_char_set_len);                       // Always
        gen_str(str, max_add_command_size, &position, command_char_set, command_char_set_len);  // Optional
        gen_char(str, &position, blank_char_set, blank_char_set_len);                           // Always
        gen_str(str, max_add_keylist_size, &position, keylist_char_set, keylist_char_set_len);  // Optional
        gen_char(str, &position, allnum_char_set, allnum_char_set_len);                         // Always
        
        fputs(str, stdout);
        printf("\n");
        memset(str, 0, str_size);
        position = 0;
    }
    free(str);
}

int main(int argc, char* argv[]) {
    int strings = 100;
    size_t max_add_command_size = 20, max_add_keylist_size = 20;
    char* end = NULL;
    long val = 0;

    for (int i = 1; i < argc, ++i) {
        val = strtol(argv[i], &end, 10);

        if (end == argv[i] || *end != '\0') {

        }
    }
    gen_strings(strings, max_add_command_size, max_add_keylist_size);
    return 0;
}
