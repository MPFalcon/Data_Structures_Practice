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
static uint64_t compare_attributes(const char * occupation_01,
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
 * @brief               Create profile for user
 *
 * @param user          Valid user profile instance passed by reference
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
static int create_user_profile(al_node_t ** user,
                               uint64_t     size,
                               char *       username,
                               char *       password,
                               char *       name,
                               char *       occupation,
                               char *       city,
                               char *       state,
                               uint64_t     age);

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

/**
 * @brief                   Probe every user in a given city
 *
 * @param city_map          Valid city map instance
 * @param recommendation    Valid recommendation list
 * @param user              Valid instance of current user
 * @param curr_quota        Current amount of people in the
 *                          recommendation list
 *
 * @return                  SUCCESS: 0
 *                          FAILURE: 1
 */
static int check_city(ub_list_t *  city_map,
                      al_node_t ** recommendation,
                      al_node_t *  user,
                      uint32_t *   curr_quota);

/**
 * @brief                   Probe every state in user base map
 *
 * @param recommendation    Valid recommendation list
 * @param user              Valid instance of current user
 * @param curr_quota        Current amount of people in the
 *                          recommendation list
 *
 * @return                  SUCCESS: 0
 *                          FAILURE: 1
 */
static int check_states(al_node_t ** recommendation,
                        al_node_t *  user,
                        uint32_t *   curr_quota);

/**
 * @brief                   Probe every city in a given state
 *
 * @param city_map          Valid state map instance
 * @param recommendation    Valid recommendation list
 * @param user              Valid instance of current user
 * @param curr_quota        Current amount of people in the
 *                          recommendation list
 *
 * @return                  SUCCESS: 0
 *                          FAILURE: 1
 */
static int traverse_state(ub_list_t *  state_map,
                          al_node_t ** recommendation,
                          al_node_t *  user,
                          uint32_t *   curr_quota);

static int recommend_friends(al_node_t * user);

/**
 * @brief                           Print what is recommended to the screen
 *
 * @param potential_friends_list    Valid recommended list instance
 *
 * @return                          SUCCESS: 0
 *                                  FAILURE: 1
 */
static int print_recommended(al_node_t ** potential_friends_list);

int setup_program(uint64_t size)
{
    int         err          = FAILURE;
    al_node_t * user_profile = NULL;

    // Use SQLDB++ to retrieve user information, otherwise
    // invoke function below

    create_user_profile(&user_profile,
                        size,
                        "cybergod1",
                        "discipline8",
                        "PFC Purifoy",
                        "Soldier",
                        "Augusta",
                        "GA",
                        21);

    // ----------------------------------------------

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
                   "rachet",
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
                   "sgtimhoff82",
                   "firstline",
                   "Imhoff",
                   "Soldier",
                   "Augusta",
                   "GA",
                   21);

    recommend_friends(user_profile);

    err = SUCCESS;

    return err;
}

static int create_user_profile(al_node_t ** user,
                               uint64_t     size,
                               char *       username,
                               char *       password,
                               char *       name,
                               char *       occupation,
                               char *       city,
                               char *       state,
                               uint64_t     age)
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
    *user             = new_graph_node;

    err_code = SUCCESS;

EXIT:

    return err_code;
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

static uint64_t compare_attributes(const char * occupation_01,
                                   const char * occupation_02)
{
    // TODO: Use XOR algorithm to find check if hashed values
    // are the same in an array produced by strtok

    uint64_t weighted_points = 0;

EXIT:

    return weighted_points;
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

    free(buffer);
    buffer = NULL;

    err_code = SUCCESS;

EXIT:

    return err_code;
}

static int check_city(ub_list_t *  city_map,
                      al_node_t ** recommendation,
                      al_node_t *  user,
                      uint32_t *   curr_quota)
{
    int           err_code     = FAILURE;
    ub_bucket_t * curr_node    = city_map->head;
    uint64_t      total_weight = 0;

    while (NULL != curr_node)
    {
        if (user->node_id == ((al_node_t *)curr_node->data)->node_id)
        {
            curr_node = curr_node->next;

            continue;
        }

        total_weight +=
            (compare_attributes(
                 user->data->occupation,
                 ((al_node_t *)curr_node->data)->data->occupation) +
             compare_attributes(user->data->name,
                                ((al_node_t *)curr_node->data)->data->name));

        if (total_weight <= 100)
        {
            recommendation[*curr_quota] = ((al_node_t *)curr_node->data);
            (*curr_quota)++;
        }

        if (RECOMMENDATION_QUOTA > *curr_quota)
        {
            curr_node = curr_node->next;
        }
        else
        {
            err_code = SUCCESS;

            break;
        }
    }

    err_code = SUCCESS;

EXIT:

    return err_code;
}

static int recommend_friends(al_node_t * user)
{
    int      err_code             = FAILURE;
    uint32_t recommendation_quota = 0;
    uint64_t idx                  = 0;

    al_node_t * recommendation[RECOMMENDATION_QUOTA] = { 0 };

    uint32_t hashed_city =
        (hash_value(user->data->city) % AVG_CITIES_PER_STATE);
    uint32_t hashed_state = (hash_value(user->data->state) % MAX_STATES);

    while (NULL != user->edges[idx])
    {
        // TODO: implement dykstra's algorithm, or 4-star, to find friends of
        // friends;
    }

    if (RECOMMENDATION_QUOTA != recommendation_quota)
    {
        err_code =
            check_city(user_base_map_g[hashed_state]->city_map[hashed_city],
                       recommendation,
                       user,
                       &recommendation_quota);
    }

    if (RECOMMENDATION_QUOTA != recommendation_quota)
    {
        err_code = traverse_state(user_base_map_g[hashed_state],
                                  recommendation,
                                  user,
                                  &recommendation_quota);
    }

    if (RECOMMENDATION_QUOTA != recommendation_quota)
    {
        err_code = check_states(recommendation, user, &recommendation_quota);
    }

    (void)print_recommended(recommendation);

    err_code = SUCCESS;

EXIT:

    return err_code;
}

static int print_recommended(al_node_t ** potential_friends_list)
{
    int      err_code = FAILURE;
    uint64_t idx      = 0;

    while (NULL != potential_friends_list[idx])
    {
        printf("\n\n");
        printf("ID: %lu\n", potential_friends_list[idx]->node_id);
        printf("Name: %s\n", potential_friends_list[idx]->data->name);
        printf("Username: %s\n", potential_friends_list[idx]->data->username);
        printf("Location: %s, %s\n",
               potential_friends_list[idx]->data->city,
               potential_friends_list[idx]->data->state);
        printf("Occupation: %s", potential_friends_list[idx]->data->occupation);
        printf("\n\n");

        idx++;
    }

    err_code = SUCCESS;

EXIT:

    return err_code;
}

static int traverse_state(ub_list_t *  state_map,
                          al_node_t ** recommendation,
                          al_node_t *  user,
                          uint32_t *   curr_quota)
{
    int      err_code = FAILURE;
    uint32_t users_hashed_city =
        (hash_value(user->data->city) % AVG_CITIES_PER_STATE);

    for (uint64_t idx = 0; AVG_CITIES_PER_STATE > idx; idx++)
    {
        if ((NULL != state_map->city_map[idx]) && (users_hashed_city != idx))
        {
            if (FAILURE ==
                check_city(
                    state_map->city_map[idx], recommendation, user, curr_quota))
            {
                print_error("Something went wrong", __func__);

                goto EXIT;
            }
        }
    }

    err_code = SUCCESS;

EXIT:

    return SUCCESS;
}

static int check_states(al_node_t ** recommendation,
                        al_node_t *  user,
                        uint32_t *   curr_quota)
{
    int      err_code           = FAILURE;
    uint32_t users_hashed_state = (hash_value(user->data->state) % MAX_STATES);

    for (uint64_t idx = 0; MAX_STATES > idx; idx++)
    {
        if ((NULL != user_base_map_g[idx]) && (users_hashed_state != idx))
        {
            if (FAILURE ==
                traverse_state(
                    user_base_map_g[idx], recommendation, user, curr_quota))
            {
                print_error("Something went wrong", __func__);

                goto EXIT;
            }
        }
    }

    err_code = SUCCESS;

EXIT:

    return err_code;
}

/*** EOF ***/
