/** @file     user_base_map.h
 *
 * @brief     Contains map of user data in the confines
 *            of the United States
 */

#ifndef USER_BASE_MAP
#    define USER_BASE_MAP

#    include "PII.h"

#    define MAX_STATES           52
#    define AVG_CITIES_PER_STATE 300

typedef struct user_base_bucket
{
    void *                    data;
    struct user_base_bucket * prev;
    struct user_base_bucket * next;
} ub_bucket_t;

typedef struct user_bucket_list
{
    struct user_bucket_list * city_map[AVG_CITIES_PER_STATE];
    ub_bucket_t *             head;
    ub_bucket_t *             tail;
} ub_list_t;

extern ub_list_t * user_base_map_g[MAX_STATES];

#endif /* USER_BASE_MAP */

/*** EOF ***/
