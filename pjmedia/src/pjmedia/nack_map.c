
#include <pjmedia/nack_map.h>
#include <pjmedia/rtcp_fb.h>
#include <pjmedia/types.h>
#include <pj/pool.h>
#include <pj/errno.h>
#include <pj/assert.h>
#include <pj/log.h>

#define THIS_FILE   "nack_map.c"

struct pjmedia_nack_map {
    pj_bool_t *packets;
};

#define MAX_MAP_SIZE 65536

PJ_DEF(pj_status_t)
pjmedia_nack_map_create(pj_pool_t *pool,
                           pjmedia_nack_map **map) {

    pjmedia_nack_map *nack_map = PJ_POOL_ZALLOC_T(pool, pjmedia_nack_map);
    PJ_ASSERT_RETURN(nack_map != NULL, PJ_ENOMEM);

    nack_map->packets = pj_pool_alloc(pool, MAX_MAP_SIZE * sizeof(pj_bool_t));
    PJ_ASSERT_RETURN(nack_map->packets != NULL, PJ_ENOMEM);

    pjmedia_nack_map_reset(nack_map);

    *map = nack_map;
    return PJ_SUCCESS;
}

PJ_DEF(pj_status_t)
pjmedia_nack_map_reset(pjmedia_nack_map *map) {
    PJ_ASSERT_RETURN(map, PJ_EINVAL);

    PJ_LOG(3, (THIS_FILE, "Nack map restarted."));
    for (unsigned i=0; i < MAX_MAP_SIZE; i++) {
        map->packets[i] = PJ_FALSE;
    }

    return PJ_SUCCESS;
}

PJ_DEF(pj_status_t)
pjmedia_nack_map_set(pjmedia_nack_map *map,
                         pj_uint16_t sequence_num) {

    PJ_ASSERT_RETURN(map, PJ_EINVAL);

    map->packets[sequence_num] = PJ_TRUE;

    return PJ_SUCCESS;
}

// Function to check if a packet with the given sequence number was NACKed
PJ_DECL(pj_bool_t)
pjmedia_nack_map_contains(pjmedia_nack_map *map,
                                   pj_uint16_t sequence_num) {

    PJ_ASSERT_RETURN(map, PJ_EINVAL);
    pj_bool_t contains = map->packets[sequence_num];
    return contains;
}
