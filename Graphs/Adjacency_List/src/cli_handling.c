#include "cli_handling.h"

int handle_cli(int argc, char ** argv, uint64_t * requested_size)
{
    int err_code = EXIT_FAILURE;

    char * restricted_char = NULL;
    int    opt             = 0;

    errno = 0;

    if (1 == argc)
    {
        print_error(
            "Command should be ran like this: 'adjacency_list -s 10'", __func__);

        goto EXIT;
    }

    opt = getopt(argc, argv, "s:");

    if ((-1 == opt) || ('?' == opt))
    {
        print_error(
            "Command should be ran like this: 'adjacency_list -s 10'", __func__);

        goto EXIT;
    }

    switch (opt)
    {
        case 's':
            if (NULL == optarg)
            {
                print_error(
                    "Command should be ran like this: 'adjacency_list -s 10'",
                    __func__);

                break;
            }

            *requested_size = strtol(optarg, &restricted_char, DEFAULT_BASE);

            if (('\0' != *restricted_char) || (errno != 0))
            {
                printf("\n\n%c\n\n", *(char *)restricted_char);

                print_error("Size must be an integral value", __func__);

                break;
            }

            printf("Adjacency list will have requested size of %s",
                                   optarg);

            if (SUCCESS == setup_program(*requested_size))
            {
                err_code = EXIT_SUCCESS;
            }

            break;
        default:
            err_code = EXIT_FAILURE;

            break;
    }

EXIT:

    return err_code;
}