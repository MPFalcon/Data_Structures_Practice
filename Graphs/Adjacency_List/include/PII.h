/** @file     PII.h
 *
 * @brief     Holds data for a persons profile
 */

#ifndef PII_H
#    define PII_H

#    include "security_functions.h"

#    define MAX_CHAR_LEN 1096

typedef struct profile_node
{
    char     username[MAX_CHAR_LEN];
    char     password[MAX_CHAR_LEN];
    char     name[MAX_CHAR_LEN];
    char     occupation[MAX_CHAR_LEN];
    char     city[MAX_CHAR_LEN];
    char     state[MAX_CHAR_LEN];
    uint32_t age;
} p_node_t;

#endif /* PII_H */

/*** EOF ***/
