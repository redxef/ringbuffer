/* 
 * file:        ringbuffer.h
 * author:      redxef
 * date:        September 29, 2016, 3:21 PM
 * version:     0.1.2
 * 
 * desc:
 * The ringbuffer is used to buffer the data received over an serial interface.
 */

#include <stdint.h>
#include <stdlib.h>

#ifndef __RINGBUFFER_H_
#define __RINGBUFFER_H_

// #define RB_USE_FIXED_SIZE

#ifdef RB_USE_FIXED_SIZE
#ifndef RB_BUFFER_SIZE
#define RB_BUFFER_SIZE          64
#endif
#endif
/**
 * A struct for storing data in a buffer.
 * The ringbuffer is crudely written with
 * ease of use and simplicity in mind.
 * It can either have a fixed size of data
 * predefined at compile time for every instance,
 * or dynamically when constructing a new one.
 * If the macro RB_USE_FIXED_SIZE is defined, then the size
 * is predefined, otherwise it is set upon initialisation
 * of the ringbuffer struct.
 */
struct ringbuffer {
        uint8_t pp;     //put pos
        uint8_t gp;     //get pos
#ifdef RB_USE_FIXED_SIZE
        uint8_t dat[RB_BUFFER_SIZE];
#else
        uint8_t *dat;
        size_t len;
#endif
};

/**
 * Initialises a given ringbuffer struct.
 * If the macro RB_USE_FIXED_SIZE is specified, then the buffer
 * will be able to hold RB_BUFFER_SIZE - 1 items at most.
 * If the parameter rb is NULL, then a new ringbuffer object will
 * be allocated on the heap.
 *
 * @param rb            The ringbuffer to initialize.
 * @param size          The size of the ringbuffer (can hold size-1
 *                      items).
 * @returns             A pointer to the newly initialized struct.
 */
struct ringbuffer *ringbufferInit(struct ringbuffer *rb, uint32_t size);

/**
 * Deletes the given ringbuffer struct. The pointer to pointer
 * style has been used, to set the struct to NULL after deletion
 * for security reasons. Thus, if the struct is deleted, it also
 * says so by being NULL.
 *
 * @param rb            The ringbuffer to be deleted.
 */
void ringbufferDelete(struct ringbuffer **rb);

/**
 * Returns the size of the ringbuffer (RB_BUFFER_SIZE) or the
 * initialized size.
 *
 * @param rb            The ringbuffer from which to get the
 *                      size.
 * @returns             The length of this ringbuffer, where
 *                      this number represents the number of items
 *                      the buffer can hold - 1.
 */
size_t ringbufferSize(struct ringbuffer *rb);

/**
 * Returns the number of bytes which can be read from the
 * ringbuffer.
 *
 * @param rb            The ringbuffer to inspect.
 * @returns             The number of available bytes.
 */
size_t ringbufferAvailable(struct ringbuffer *rb);

/**
 * Puts a new byte of data into the ringbuffer and returns 0 on
 * success. Otherwise the byte will be dropped and 1 returned.
 *
 * @param rb            The ringbuffer, which should receive the
 *                      byte of data.
 * @param dat           The data to feed the ringbuffer.
 * @returns             0 or 1 on success or failure respectively.
 */
uint8_t ringbufferPut(struct ringbuffer *rb, uint8_t dat);

/**
 * Returns the next byte of data from the ringbuffer or -1 if no
 * data is available.
 *
 * @param rb            The buffer from which to get the next byte
 *                      of data.
 * @returns             The next byte in the lower byte of the returned
 *                      value or -1.
 */
int16_t ringbufferGet(struct ringbuffer *rb);

#endif
