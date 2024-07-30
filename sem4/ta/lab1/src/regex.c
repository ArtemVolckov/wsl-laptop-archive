#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <assert.h>

// Previous variant of regex: "^[[:alnum:]./]+[[:blank:]][[:alnum:][:blank:]]*[[:alnum:]]$"
// regcomp with REG_EXTENDED flag is required

#define BUF_SIZE 256 

// String recognition and printing with verification information (Format: "[Match|Nomatch] some string") 
void print_status_and_str(regex_t* regex, const char* cline) {
    if (regexec(regex, cline, 0, NULL, 0))  
        printf("Nomatch %s\n", cline);
    else 
        printf("Match %s\n", cline);
}

// String recognition and printing of matching (For output_parser)
void print_matching_str(regex_t* regex, const char* cline) {
    if (!regexec(regex, cline, 0, NULL, 0))  
        printf("%s\n", cline);
}

void recognize(const char* cregex, int is_regexextended_required, int argc, char* argv[]) {
    void (*function_pointer)(regex_t*, const char*) = &print_status_and_str;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--collect") == 0) {
            function_pointer = &print_matching_str;
            break;
        } 
    } 
    regex_t regex;
    int reg_check = 0;

    if (is_regexextended_required) 
        reg_check = regcomp(&regex, cregex, REG_EXTENDED);
    else 
        reg_check = regcomp(&regex, cregex, 0);
    assert(reg_check == 0); 
    char buf[BUF_SIZE] = {0};

    while (fgets(buf, BUF_SIZE, stdin)) {
        int str_len = strlen(buf) - 1;

        if (buf[str_len] == '\n')
            buf[str_len] = '\0';
        function_pointer(&regex, buf);
    }
    regfree(&regex);
}

int main(int argc, char* argv[]) {
    const char* cregex = "^[[:alnum:]./][[:alnum:]./]*[[:blank:]][[:alnum:][:blank:]]*[[:alnum:]]$";
    recognize(cregex, 0, argc, argv);
    return 0;
}