/**
 * @f ccn-iribu-producer.h
 * @b CCN lite, core CCNx protocol logic
 *
 * Copyright (C) 2011-18 University of Basel
 * Copyright (C) 2015, 2016 INRIA
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * File history:
 * 2018-01-23 created (based on ccn-iribu-riot.h)
 */
#ifndef CCN_IRIBU_PRODUCER_H
#define CCN_IRIBU_PRODUCER_H

#include "ccn-iribu-core.h"

/**
 * @brief Function pointer type for local producer function
 */
typedef int (*ccn_iribu_producer_func)(struct ccn_iribu_relay_s *relay,
                                       struct ccn_iribu_face_s *from,
                                       struct ccn_iribu_pkt_s *pkt);

/**
 * @brief Set a local producer function
 *
 * Setting a local producer function allows to generate content on the fly or
 * react otherwise on any kind of incoming interest.
 *
 * @param[in] func  The function to be called first for any incoming interest
 */
void ccn_iribu_set_local_producer(ccn_iribu_producer_func func);

/**
 * @brief Allows to generates content on the fly/or react to any kind of interest
 *
 * A developer has to provide its own local_producer function which is set via
 * \ref ccn_iribu_set_local_producer as a function pointer. If the function pointer
 * is not, set the function simply returns '0'.
 *
 * @param[in] relay The active ccn-iribu relay
 * @param[in] from  The face the packet was received over
 * @param[in] pkt   The actual received packet
 *
 * @return 0 if no function has been set
 */
#ifndef CCN_IRIBU_ANDROID
int local_producer(struct ccn_iribu_relay_s *relay, struct ccn_iribu_face_s *from,
                   struct ccn_iribu_pkt_s *pkt);
#else
#    define local_producer(...) 0
#endif

#endif
