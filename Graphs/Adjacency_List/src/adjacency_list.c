#include "adjacency_list.h"

int print_err(const char * err_message, const char * err_location)
{
    (void)fprintf(
        stderr, "\n\nERROR [+]  %s: %s\n\n", err_message, err_location);

    return EXIT_FAILURE;
}

int print_note(const char * note_message,
               const char * note_location,
               int          status)
{
    printf("\n\nNOTE [+]  %s: %s\n\n", note_message, note_location);

    return status;
}

int setup_program(int size)
{
    int err = EXIT_SUCCESS;

    printf("\n\nProgram start\n\n");

    return err;
}

/*** EOF ***/
