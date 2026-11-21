#include <stdio.h>
#define STB_C_LEXER_IMPLEMENTATION
#include "stb_c_lexer.h"

int main(void) {
    stb_lexer lex;
    const char *text = "int x = 1;";
    char storage[1024];
    stb_c_lexer_init(&lex, text, text + 10, storage, (int)sizeof(storage));
    if (stb_c_lexer_get_token(&lex)) {
        printf("ok %ld\n", lex.token);
        return 0;
    }
    return 1;
}
