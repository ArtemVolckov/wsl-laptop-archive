#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/hashmap.h"

#define BUF_SIZE 256
#define DELIM " \t"

void collect_print_statistics() {
    Hashmap h;
    hashmap_init(&h, 10);
    char buf[BUF_SIZE] = {0}, additional_buf[BUF_SIZE] = {0};
    const char* match_str = "Match", *nomatch_str = "Nomatch";
    int match_str_len = strlen(match_str), nomatch_str_len = strlen(nomatch_str);
    char command[BUF_SIZE] = {0}, *token = NULL;
    char** key_arr = NULL;
    int counter = 0, offset = 0, additional_offset = 0, buf_len = 0;

    while (fgets(buf, BUF_SIZE, stdin)) {
        buf_len = strlen(buf);
        memcpy(additional_buf, buf, buf_len);

        if (buf[0] == ' ' || buf[0] == '\t' || buf[buf_len - 2] == ' ' || buf[buf_len - 2] == '\t' || buf_len < nomatch_str_len + 5)
            abort();
        token = strtok(buf, DELIM);

        if (strncmp(token, match_str, match_str_len)) {
            token = strtok(NULL, DELIM);
            //command = token;
            offset = token - buf;
            token = strtok(NULL, DELIM);
            additional_offset = token - buf;
            //memcpy(command, token + )
            offset = token - buf;
            memcpy(additional_buf, buf + offset, buf_len - offset);

            while (token != NULL) {
                counter += 1;
                token = strtok(NULL, DELIM);
            }
            key_arr = (char**) calloc(counter, sizeof(char*));
            counter = 0;
            token = strtok(buf, DELIM);

            while (token != NULL) {
                token = strtok(NULL, DELIM);
                key_arr[counter] = token;
                counter += 1;
            }
            hashmap_add(&h, command, key_arr, counter);
            counter = 0;
            free(key_arr);
        }
        else if (strncmp(token, nomatch_str, nomatch_str_len)) {
            continue;
        }
        else {
            abort();
        }
    }
    hashmap_free(&h);
}

int main() {
    collect_print_statistics();
    return 0;
}