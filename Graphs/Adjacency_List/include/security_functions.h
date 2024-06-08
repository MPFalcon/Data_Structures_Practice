
/** @file     security_functions.h
 *
 * @brief     Holds encryption and hashing algorithms for ease
 *            of processes and security
 */

#ifndef SECURITY_FUNCTIONS_H
#    define SECURITY_FUNCTIONS_H

#    include "print_utilities.h"

/**
 * @brief               Contains hashing logic
 *
 * @param p_str         Provided string
 *
 * @return              Resulting hash value of the givin input
 */
uint32_t hash_value(const char * p_str);

#endif /* SECURITY_FUNCTIONS_H */

/*** EOF ***/
