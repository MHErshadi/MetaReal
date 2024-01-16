/*
MIT License

Copyright (c) 2023 MetaReal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
*/

/**
 * @file main.c
 * Main file of the compiler that aggregates all compiler parts together. \n
 * Command line prompts are also defined here.
*/

#include <lexer/lexer.h>
#include <parser/parser.h>
#include <optimizer/optimizer.h>
#include <generator/generator.h>
#include <optimizer/value.h>
#include <stack.h>
#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <consts.h>

/**
 * It compiles the \a code according to MetaReal compile rules. \n
 * Order of compilation:
 * <pre>
 *     [code] -> lexer -> parser -> optimizer -> generator -> assembler -> linker -> [executable]
 * </pre>
 * Also, debugger will debug the \a code during compilation process (if enabled). \n
 * Dollar methods are handled with a different mechanism in the optimization step.
 * @return It returns a code which indicates if process was successful or not. \n
 * If process was successful, it returns 0. Otherwise, it returns the error code.
*/
mr_byte_t mr_compile(void);

void mr_handle_args(mr_str_ct argv[], mr_byte_t size);

/**
 * It prints out the help information (called with a \--help flag).
*/
void mr_print_help(void);

int main(
    int argc, mr_str_ct argv[])
{
    if (argc == 1)
    {
        fputs(
            "Internal Error: Invalid command, nothing to process.\n"
            "Write \"MetaReal --help\" for more information.\n",
            stderr);
        return MR_ERROR_BAD_COMMAND;
    }

    if (argc >= 2)
    {
        if (!strcmp(argv[1], "--help"))
        {
            mr_print_help();
            return MR_NOERROR;
        }
        if (!strcmp(argv[1], "--version"))
        {
            fputs(
                "MetaReal compiler version " MR_VERSION "\n"
                "MetaReal core verified as " MR_CORE ", version " MR_CORE_VERSION "\n"
                "MetaReal port verified as " MR_PORT ", version " MR_PORT_VERSION "\n",
                stdout);
            return MR_NOERROR;
        }
        if (!strcmp(argv[1], "--dumpver"))
        {
            fputs(
                MR_VERSION " "
                MR_CORE " " MR_CORE_VERSION " "
                MR_PORT " " MR_PORT_VERSION "\n",
                stdout);
            return MR_NOERROR;
        }

        if (argc > 2)
            mr_handle_args(argv + 2, (mr_byte_t)argc - 2);

#if defined(__GNUC__) || defined(__clang__)
        FILE *file = fopen(argv[1], "rb");
        if (!file)
#elif defined(_MSC_VER)
        FILE *file;
        if (fopen_s(&file, argv[1], "rb"))
#endif
        {
            fprintf(stderr,
                "Internal Error: Can not find the file \"%s\"\n",
                argv[1]);
            return MR_ERROR_FILE_NOT_FOUND;
        }

        fseek(file, 0, SEEK_END);
        mr_long_t size = ftell(file);
        rewind(file);

        if (size >= MR_FILE_MAXSIZE)
        {
            fprintf(stderr,
                "Internal error: File size exceeds the limit (%" PRIu64 ")",
                MR_FILE_MAXSIZE);

            fclose(file);
            return MR_ERROR_FILE_TOO_LARGE;
        }

        if (!size)
        {
            fclose(file);
            return MR_NOERROR;
        }

        mr_str_t code = malloc((size + 1) * sizeof(mr_chr_t));
        if (!code)
        {
            fclose(file);
            fputs("Internal error: not enough memory.\n", stderr);
            return MR_ERROR_NOT_ENOUGH_MEMORY;
        }

        fread(code, sizeof(mr_chr_t), size, file);
        fclose(file);
        code[size] = '\0';

        _mr_config.code = code;
        _mr_config.size = size;
        _mr_config.fname = argv[1];

        mr_byte_t retcode = mr_compile();
        free(code);

        if (retcode == MR_ERROR_NOT_ENOUGH_MEMORY)
            fputs("Internal Error: Not enough memory.\n", stderr);
        printf("END\n"); // dummy
        return retcode;
    }

    fputs(
        "Internal Error: Invalid command.\n"
        "Write \"MetaReal --help\" for more information.\n",
        stderr);
    return MR_ERROR_BAD_COMMAND;
}

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
mr_byte_t mr_compile(void)
{
    LARGE_INTEGER s, e;

    mr_lexer_t lexer;
    QueryPerformanceCounter(&s);
    mr_byte_t retcode = mr_lexer(&lexer);
    if (retcode != MR_NOERROR)
    {
        if (retcode == MR_ERROR_BAD_FORMAT)
            mr_illegal_chr_print(&lexer.error);
        return retcode;
    }

    if (lexer.tokens->type == MR_TOKEN_EOF)
    {
        free(lexer.tokens);
        return MR_NOERROR;
    }

    retcode = mr_stack_init(
        _mr_config.size * MR_STACK_SIZE_FACTOR,
        _mr_config.size / MR_STACK_PSIZE_CHUNK + 1);
    if (retcode != MR_NOERROR)
        return retcode;

    mr_parser_t parser;
    retcode = mr_parser(&parser, lexer.tokens);
    if (retcode != MR_NOERROR)
    {
        if (retcode == MR_ERROR_BAD_FORMAT)
            mr_invalid_syntax_print(&parser.error);

        mr_stack_free();
        return retcode;
    }

    mr_optimizer_t optimizer;
    retcode = mr_optimizer(&optimizer, parser.nodes, parser.size);
    if (retcode != MR_NOERROR)
    {
        if (retcode == MR_ERROR_BAD_FORMAT)
            mr_invalid_semantic_print(&optimizer.error);

        mr_stack_free();
        return retcode;
    }
    QueryPerformanceCounter(&e);
    printf("%lf msc\n", (e.QuadPart - s.QuadPart) / 10000.0);

    mr_generator_t generator;
    retcode = mr_generator(&generator, optimizer.values,
        optimizer.size, optimizer.size * MR_GENERATOR_STRING_FACTOR);

    if (retcode != MR_NOERROR)
    {
        mr_stack_free();
        return retcode;
    }

    mr_byte_t asize = 5 + (mr_byte_t)strlen(_mr_config.fname);
    mr_str_t afile = malloc(asize);
    sprintf(afile, "%s.asm", _mr_config.fname);

#if defined(__GNUC__) || defined(__clang__)
    FILE *file = fopen(afile, "w");
#elif defined(_MSC_VER)
    FILE *file;
    fopen_s(&file, afile, "w");
#endif
    fwrite(generator.data, sizeof(mr_chr_t), generator.size, file);
    fclose(file);

    asize += 58 + sizeof(__MR_ASSEMBLER__) + generator.ssize;
    mr_str_t command = malloc(asize);
    sprintf(command, "\"%s\" %s "
        "/link /entry:main /subsystem:console /stack:%" PRIu32
        ">nul 2>nul", __MR_ASSEMBLER__, afile, generator.stacksize);
    system(command);

    free(generator.data);
    free(afile);
    free(command);

    mr_stack_free();
    return MR_NOERROR;
}

void mr_handle_args(mr_str_ct argv[], mr_byte_t size)
{
    mr_str_ct str;
    for (; size; size--)
    {
        str = *argv++;

        if (!strcmp(str, "-Od"))
            mr_config_opt(OPT_LEVELD);
        else if (!strcmp(str, "-O0"))
            mr_config_opt(OPT_LEVEL0);
        else if (!strcmp(str, "-O1"))
            mr_config_opt(OPT_LEVEL1);
        else if (!strcmp(str, "-O2"))
            mr_config_opt(OPT_LEVEL2);
        else if (!strcmp(str, "-O3"))
            mr_config_opt(OPT_LEVEL3);
        else if (!strcmp(str, "-Ou"))
            mr_config_opt(OPT_LEVELU);
        else if (!strcmp(str, "-Od-const-fold"))
            _mr_config.opt_const_fold = MR_FALSE;
        else if (!strcmp(str, "-Oe-const-fold"))
            _mr_config.opt_const_fold = MR_TRUE;
        else if (!strcmp(str, "-Od-rem-useless"))
            _mr_config.opt_rem_useless = MR_FALSE;
        else if (!strcmp(str, "-Oe-rem-useless"))
            _mr_config.opt_rem_useless = MR_TRUE;
    }
}

void mr_print_help(void)
{
    fputs(
        "MetaReal [output] [files] [options]\nOptions:\n"
        "  --help\t\tDisplays the help information.\n"
        "  --version\t\tDisplays the version information.\n"
        "  --dumpver\t\tDisplays the version data.\n",
        stdout);
}
