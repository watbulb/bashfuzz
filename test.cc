#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include <iostream>

#pragma clang diagnostic ignored "-Wwritable-strings"

extern "C" int AFLTestOneInput(uint8_t *data, size_t size)
{
    char *bash_var = new char[size];
    char *casted_data = reinterpret_cast<char*>(data);

    char *_env[3];
    char *_argv[4];

    strcat(bash_var, "HTTP_COOKIE");

    strncat(
        bash_var,
        casted_data,
        (strlen(casted_data) - 1)
    );

    _env[0] = bash_var;
    _env[1] = "PATH=/bin:/usr/bin";
    _env[2] = NULL;

    _argv[0] = "/bin/bash";
    _argv[1] = "-c";
    _argv[2] = ":";
    _argv[3] = NULL;

    try{execve(_argv[0], &(_argv[0]), _env);}
    catch (const std::exception &exc)
    {
        std::cerr << exc.what() << std::endl;

        delete[] bash_var;
        free(casted_data);

        return -1;
    }
    delete[] bash_var;
    free(casted_data);

    return 0;
}