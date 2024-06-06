#include "cli_handling.h"

int main(int argc, char ** argv)
{
    int exit_code = EXIT_FAILURE;

    uint64_t requested_size = 0;

    exit_code = handle_cli(argc, argv, &requested_size);

EXIT:

    return exit_code;
}

/*** EOF ***/
