/*
 * @f ccn-iribu-pkt-switch.c
 * @b CCN lite - encoding for switching packet formats
 *
 * Copyright (C) 2014, Christian Tschudin, University of Basel
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
 * 2014-12-21 created
 */

// see ccn-iribu-defs.h for the ENC constants

#ifndef CCN_IRIBU_LINUXKERNEL
#    include "ccn-iribu-core.h"
#    include "ccn-iribu-pkt-ccnb.h"
#    include "ccn-iribu-pkt-ccntlv.h"
#    include "ccn-iribu-pkt-ndntlv.h"
#else
#    include "../../ccn-iribu-core/include/ccn-iribu-core.h"
#    include "../include/ccn-iribu-pkt-ccnb.h"
#    include "../include/ccn-iribu-pkt-ccntlv.h"
#    include "../include/ccn-iribu-pkt-ndntlv.h"
#endif

int8_t ccn_iribu_switch_dehead(uint8_t **buf, size_t *len, int32_t *code)
{
    if (*len < 2 || **buf != 0x80) {
        return -1;
    }
    if ((*buf)[1] < 253) {
        *code = (*buf)[1];
        *buf += 2;
        *len -= 2;
        return 0;
    }
    // higher code values not implemented yet
    return -1;
}

int ccn_iribu_enc2suite(int enc)
{
    switch (enc) {
#ifdef USE_SUITE_CCNB
    case CCN_IRIBU_ENC_CCNB:
        return CCN_IRIBU_SUITE_CCNB;
#endif
#ifdef USE_SUITE_NDNTLV
    case CCN_IRIBU_ENC_NDN2013:
        return CCN_IRIBU_SUITE_NDNTLV;
#endif
#ifdef USE_SUITE_CCNTLV
    case CCN_IRIBU_ENC_CCNX2014:
        return CCN_IRIBU_SUITE_CCNTLV;
#endif
#ifdef USE_SUITE_LOCALRPC
    case CCN_IRIBU_ENC_LOCALRPC:
        return CCN_IRIBU_SUITE_LOCALRPC;
#endif
    default:
        break;
    }

    return -1;
}

// ----------------------------------------------------------------------

#ifdef NEEDS_PACKET_CRAFTING

int8_t ccn_iribu_switch_prependCodeVal(uint64_t val, size_t *offset, uint8_t *buf,
                                       size_t *res)
{
    size_t len, i;
    uint8_t t;

    if (val < 253) {
        len = 0, t = (uint8_t) val;
    } else if (val <= 0xffff) {
        len = 2, t = 253;
    } else if (val <= 0xffffffffL) {
        len = 4, t = 254;
    } else {
        len = 8, t = 255;
    }

    if (*offset < (len + 1)) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        buf[--(*offset)] = (uint8_t)(val & 0xff);
        val              = val >> 8;
    }
    buf[--(*offset)] = t;
    *res             = len + 1;
    return 0;
}

int8_t ccn_iribu_switch_prependCoding(uint64_t code, size_t *offset, uint8_t *buf,
                                      size_t *res)
{
    size_t len;

    if (*offset < 2) {
        return -1;
    }
    if (ccn_iribu_switch_prependCodeVal(code, offset, buf, &len) || *offset < 1) {
        return -1;
    }
    *offset -= 1;
    buf[*offset] = 0x80;

    *res = len + 1;
    return 0;
}

#endif    // NEEDS_PACKET_CRAFTING

// eof
