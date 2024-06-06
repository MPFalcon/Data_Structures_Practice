/** @file     cli_handling.h
 *
 * @brief     Contains code for adjacency list
 */

#ifndef CLI_HANDLING_H
#    define CLI_HANDLING_H

#    include <getopt.h>
#    include <bits/getopt_core.h>

#    include "adjacency_list.h"

/**
 * @brief                   Handles command line arguments
 *
 * @param argc              Number of arguments to process
 * @param argv              Command line arguments
 * @param requested_size    Requested size of the adjacency list
 *
 * @return                  SUCCESS: 0
 *                          FAILURE: 1
 */
int handle_cli(int argc, char ** argv, uint64_t * requested_size);

#endif /* CLI_HANDLING_H */

/*** EOF ***/
