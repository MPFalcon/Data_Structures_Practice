#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <bits/getopt_core.h>
#include <errno.h>

#define DEFAULT_BASE 10

int print_err(const char * err_message, const char * err_location);

int print_note(const char * note_message,
               const char * note_location,
               int          status);

int setup_program(int size);

#endif /* ADJACENCY_LIST_H */