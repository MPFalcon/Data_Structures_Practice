#include "adjacency_list.h"

int main(int argc, char ** argv)
{
    int    exit_code       = EXIT_SUCCESS;
    int    requested_size  = 0;
    char * restricted_char = NULL;
    int    opt             = 0;

    errno = 0;

    if (1 == argc)
    {
        exit_code = print_err(
            "Command should be ran like this: 'adjacency_list -s 10'", "");

        goto EXIT;
    }

    opt = getopt(argc, argv, "s:");

    if ((-1 == opt) || ('?' == opt))
    {
        exit_code = print_err(
            "Command should be ran like this: 'adjacency_list -s 10'", "");

        goto EXIT;
    }

    switch (opt)
    {
        case 's':
            if (NULL == optarg)
            {
                exit_code = print_err(
                    "Command should be ran like this: 'adjacency_list -s 10'",
                    "");

                break;
            }

            requested_size = strtol(optarg, &restricted_char, DEFAULT_BASE);

            if (('\0' != *restricted_char) || (errno != 0))
            {
                printf("\n\n%c\n\n", *(char *)restricted_char);
                exit_code =
                    print_err("Size must be an integral value", "main()");

                break;
            }

            exit_code = print_note("Adjacency list will have requested size of",
                                   optarg,
                                   EXIT_SUCCESS);

            exit_code = setup_program(requested_size);

            break;
        default:
            exit_code = EXIT_FAILURE;

            break;
    }

EXIT:

    return exit_code;
}

/*** EOF ***/
