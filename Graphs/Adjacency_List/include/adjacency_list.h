/** @file     adjacency_list.h
 *
 * @brief     Contains code for adjacency list
 */

#ifndef ADJACENCY_LIST_H
#    define ADJACENCY_LIST_H

#    include "user_base_map.h"

#    define DIRECTED     0x1
#    define NON_DIRECTED 0x0
typedef struct __attribute__((packed)) edge_node
{
    uint64_t weight;
    void *   adjacent_node;
} edge_node_t;
typedef struct __attribute__((packed)) adjacency_list_node
{
    // sizeof(edge_node_t) * friend_count
    uint64_t       node_id;
    uint64_t       friend_count;
    uint8_t        directed;
    p_node_t *     data;
    edge_node_t ** edges;
} al_node_t;

/**
 * @brief           Driver code for adjacency list
 *
 * @param size      Size of the graph
 *
 * @return          SUCCESS: 0
 *                  FAILURE: 1
 */
int setup_program(uint64_t size);

#endif /* ADJACENCY_LIST_H */

/*** EOF ***/
