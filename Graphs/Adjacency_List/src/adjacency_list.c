#include "adjacency_list.h"

/**
 * @brief                   Calculate weight by comparing hashes of occupation
 *                          strings
 *
 * @param occupation_01     First occupation
 * @param occupation_02     Second occupation
 *
 * @return                  Weight
 */
static int compare_occupations(const char * occupation_01,
                               const char * occupation_02);

/**
 * @brief               Create a profile
 *
 * @param size          Amount of friends that can be had
 * @param username      Username
 * @param password      Password
 * @param name          Name
 * @param occupation    Occupation
 * @param city          City
 * @param state         State
 * @param age           Age
 *
 * @return              SUCCESS: 0
 *                      FAILURE: 1
 */
static int create_profile(uint64_t size,
                          char *   username,
                          char *   password,
                          char *   name,
                          char *   occupation,
                          char *   city,
                          char *   state,
                          uint64_t age);

/**
 * @brief       Process id of a new profile
 *
 * @param id    Id passed by reference so it can
 *              be assigned after processing
 *
 * @return      SUCCESS: 0
 *              FAILURE: 1
 */
static int dequeue_id(uint64_t * id);

int setup_program(uint64_t size)
{
    int err = FAILURE;

    create_profile(size,
                   "beautifulones2",
                   "goddess444",
                   "Leeahni Rodriguez",
                   "Aesthetistision",
                   "Houston",
                   "TX",
                   21);

    create_profile(size,
                   "bigsexxxy123",
                   "rachetb*tch",
                   "Bailey",
                   "Night Club Host",
                   "Miami",
                   "FL",
                   23);

    create_profile(size,
                   "ofgoddess",
                   "aquarius34",
                   "Evelyn",
                   "Night Club Dancer",
                   "Fort Lauderdale",
                   "FL",
                   22);

    create_profile(size,
                   "cybergod1",
                   "discipline8",
                   "PFC Purifoy",
                   "Soldier",
                   "Augusta",
                   "GA",
                   21);

    err = SUCCESS;

    return err;
}

static int create_profile(uint64_t size,
                          char *   username,
                          char *   password,
                          char *   name,
                          char *   occupation,
                          char *   city,
                          char *   state,
                          uint64_t age)
{
    int err_code = FAILURE;

    al_node_t * new_graph_node = (al_node_t *)calloc(1, sizeof(al_node_t));

    new_graph_node->directed = DIRECTED;
    new_graph_node->edges    = (edge_node_t **)calloc((size - 1), 8);

    new_graph_node->data = (p_node_t *)calloc(1, sizeof(p_node_t));

    strncpy(new_graph_node->data->username, username, MAX_CHAR_LEN);
    strncpy(new_graph_node->data->password, password, MAX_CHAR_LEN);
    strncpy(new_graph_node->data->name, name, MAX_CHAR_LEN);
    strncpy(new_graph_node->data->occupation, occupation, MAX_CHAR_LEN);
    strncpy(new_graph_node->data->city, city, MAX_CHAR_LEN);
    strncpy(new_graph_node->data->state, state, MAX_CHAR_LEN);
    new_graph_node->data->age = age;
    dequeue_id(&new_graph_node->node_id);

    uint32_t hashed_state = (hash_value(state) % MAX_STATES);
    uint32_t hashed_city  = (hash_value(city) % AVG_CITIES_PER_STATE);

    ub_bucket_t * curr_bucket = (ub_bucket_t *)calloc(1, sizeof(ub_bucket_t));

    if (NULL == user_base_map_g[hashed_state])
    {
        user_base_map_g[hashed_state] =
            (ub_list_t *)calloc(1, sizeof(ub_list_t));

        if (NULL == user_base_map_g[hashed_state]->city_map[hashed_city])
        {
            user_base_map_g[hashed_state]->city_map[hashed_city] =
                (ub_list_t *)calloc(1, sizeof(ub_list_t));
        }

        user_base_map_g[hashed_state]->city_map[hashed_city]->head =
            curr_bucket;
        user_base_map_g[hashed_state]->city_map[hashed_city]->tail =
            curr_bucket;
    }
    else if (NULL == user_base_map_g[hashed_state]->city_map[hashed_city])
    {
        user_base_map_g[hashed_state]->city_map[hashed_city] =
            (ub_list_t *)calloc(1, sizeof(ub_list_t));
        user_base_map_g[hashed_state]->city_map[hashed_city]->head =
            curr_bucket;
        user_base_map_g[hashed_state]->city_map[hashed_city]->tail =
            curr_bucket;
    }
    else
    {
        user_base_map_g[hashed_state]->city_map[hashed_city]->tail->next =
            curr_bucket;
        curr_bucket->prev =
            user_base_map_g[hashed_state]->city_map[hashed_city]->tail;
        user_base_map_g[hashed_state]->city_map[hashed_city]->tail =
            curr_bucket;
    }

    curr_bucket->data = new_graph_node;

    err_code = SUCCESS;

EXIT:

    return err_code;
}

static int compare_occupations(const char * occupation_01,
                               const char * occupation_02)
{
    // TODO: Use XOR algorithm to find check if hashed values
    // are the same in an array produced by strtok

    uint64_t weighted_points = 0;
}

static int dequeue_id(uint64_t * id)
{
    int err_code = FAILURE;
    int rw_fd = open("./Graphs/Adjacency_List/db/id_queue.dat", O_RDWR, "rb+");
    uint64_t next_avail_id = 0;

    if (0 > rw_fd)
    {
        print_error("File Does not exist", __func__);

        goto EXIT;
    }

    if (0 == lseek(rw_fd, 0L, SEEK_END))
    {
        *id           = BASE_ID;
        next_avail_id = ((*id) + 1);
        write(rw_fd, &next_avail_id, sizeof(uint64_t));
        close(rw_fd);

        goto EXIT;
    }

    off_t  final_len = (lseek(rw_fd, 0L, SEEK_END) - sizeof(uint64_t));
    void * buffer    = calloc(1, final_len);

    lseek(rw_fd, 0L, SEEK_SET);
    read(rw_fd, id, sizeof(uint64_t));
    lseek(rw_fd, sizeof(uint64_t), SEEK_SET);
    read(rw_fd, buffer, final_len);
    close(rw_fd);

    rw_fd = open(
        "./Graphs/Adjacency_List/db/id_queue.dat", (O_WRONLY | O_TRUNC), "wb+");
    next_avail_id = ((*id) + 1);
    lseek(rw_fd, 0L, SEEK_SET);
    write(rw_fd, buffer, final_len);
    lseek(rw_fd, final_len, SEEK_SET);
    write(rw_fd, &next_avail_id, sizeof(uint64_t));
    close(rw_fd);

    err_code = SUCCESS;

EXIT:

    return err_code;
}

/*** EOF ***/
