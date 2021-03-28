/*
 * @f ccn-iribu-forward.h
 * @b CCN lite (CCNL), core header file (internal data structures)
 *
 * Copyright (C) 2011-17, University of Basel
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
 * 2017-06-16 created
 */

#ifndef CCN_IRIBU_FORWARD_H
#define CCN_IRIBU_FORWARD_H

#include "ccn-iribu-buf.h"
#include "ccn-iribu-face.h"
#include "ccn-iribu-prefix.h"
#include "ccn-iribu-relay.h"

typedef void (*tapCallback)(struct ccn_iribu_relay_s *, struct ccn_iribu_face_s *,
                            struct ccn_iribu_prefix_s *, struct ccn_iribu_buf_s *);

struct ccn_iribu_forward_s {
    struct ccn_iribu_forward_s *next;
    struct ccn_iribu_prefix_s *prefix;
    tapCallback tap;
    struct ccn_iribu_face_s *face;
    char suite;
};

#endif    // CCN_IRIBU_FORWARD_H
