/*
    MetaReal Compiler version 1.0.0
*/

#include <lexer/token.h>
#include <alloc.h>
#include <stdio.h>

const char *token_labels[MUL_T + 1] =
{
    "EOF",
    "INT",
    "ADD", "SUB", "MUL"
};

void free_tokens(token_t *tokens)
{
    while (tokens->type != EOF_T)
        mr_free(tokens++->value);
}

void print_tokens(const token_t *tokens)
{
    for (; tokens->type != EOF_T; tokens++)
    {
        fputs(token_labels[tokens->type], stdout);

        if (tokens->value)
            printf(": %s", tokens->value);

        putchar('\n');
    }

    fputs("EOF\n", stdout);
}
