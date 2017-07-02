/* 
 * file:        ringbuffer.c
 * author:      redxef
 * date:        September 13, 2016, 2:38 PM
 * version:     0.1.2
 * 
 * desc:
 * Implementation for the ringbuffer.
 */

#include "ringbuffer.h"

struct ringbuffer *ringbufferInit(struct ringbuffer *rb, uint32_t size) {
        uint32_t i;
        uint8_t flags = 0;

        if (rb == NULL) {
                rb = malloc(sizeof (struct ringbuffer));
                if (rb == NULL)
                        return NULL;
                flags |= 1;
        }

        rb->pp = 0;
        rb->gp = 0;

#ifdef RB_USE_FIXED_SIZE
        i = RB_BUFFER_SIZE;
#else
        rb->len = size;
        rb->dat = malloc(size);
        if (rb->dat == NULL) {
                if ((flags & 1) == 1)
                        free(rb);
                return NULL;
        }
        i = size;
#endif
        while (i--) {
                rb->dat[i] = 0;
        }
        
        return rb;
}

void ringbufferDelete(struct ringbuffer **rb) {
        #ifndef RB_USE_FIXED_SIZE
                free((*rb)->dat);
        #endif
        free(*rb);
        *rb = NULL;
}

size_t ringbufferSize(struct ringbuffer *rb) {
#ifdef RB_USE_FIXED_SIZE
        return RB_BUFFER_SIZE;
#else
        return rb->len;
#endif
}

size_t ringbufferAvailable(struct ringbuffer *rb) {
        if (rb->gp < rb->pp) {
                return rb->pp - rb->gp;
        } else if (rb->gp > rb->pp) {
                return rb->pp + ringbufferSize(rb) - rb->gp;
        }

        return 0;
}

uint8_t ringbufferPut(struct ringbuffer *rb, uint8_t dat) {
        if ((rb->pp != rb->gp - 1) && (rb->pp != ringbufferSize(rb) - 1 || rb->gp != 0)) {
                rb->dat[rb->pp] = dat;
                rb->pp += 1;
                if (rb->pp == ringbufferSize(rb))
                        rb->pp = 0;
                return 0;
        }
        return 1;
}

int16_t ringbufferGet(struct ringbuffer *rb) {
        int16_t ret = -1;

        if (rb->gp != rb->pp) {
                ret = rb->dat[rb->gp];
                rb->gp += 1;
                if (rb->gp == ringbufferSize(rb))
                        rb->gp = 0;
        }

        return ret;
}
