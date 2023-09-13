#ifndef __PJMEDIA_NACK_MAP_H__
#define __PJMEDIA_NACK_MAP_H__

/**
 * @file nack_map.h
 * @brief Map for packet ids sent in NACK message.
 */

#include <pjmedia/rtcp_fb.h>
#include <pjmedia/types.h>

PJ_BEGIN_DECL

/**
 * Opaque declaration for nack buffer.
 */
typedef struct pjmedia_nack_map pjmedia_nack_map;

PJ_DEF(pj_status_t) pjmedia_nack_map_create(pj_pool_t *pool, pjmedia_nack_map **map);
PJ_DEF(pj_status_t) pjmedia_nack_map_check_cycle(pjmedia_nack_map *map, pjmedia_rtp_session *rtp);
PJ_DEF(pj_status_t) pjmedia_nack_map_reset(pjmedia_nack_map *map);
PJ_DEF(pj_status_t) pjmedia_nack_map_set(pjmedia_nack_map *map, pj_uint16_t sequence_num);
PJ_DECL(pj_bool_t) pjmedia_nack_map_contains(pjmedia_nack_map *map, pj_uint16_t sequence_num);

PJ_END_DECL

#endif /* __PJMEDIA_NACK_MAP_H__ */
