/**
 * @author      
 * @file        test.c
 * @version     0.0.0-r0
 * @since       
 * 
 * @brief       A brief documentation about the file.
 *
 * A detailed documentation.
 */

#include "ringbuffer.h"
#include <stdio.h>

/* V A R I A B L E S                                                          */


/* C O D E                                                                    */
// int main(int argc, char **argv) {
//         struct ringbuffer rb;
//         int i, j;
//         if (ringbufferInit(&rb, 10) == NULL) {
//                 fprintf(stderr, "failed to init rb!\n");
//                 return 1;
//         }

//         printf("created rb with size: %zu\n", ringbufferSize(&rb));
//         printf("availabel: %zu\n", ringbufferAvailable(&rb));
//         for (j = 0; j < 10; j++) {
//                 /* put as much information as possible into the buffer
//                    this is size - 1 items  */
//                 i = 'A';
//                 while (!ringbufferPut(&rb, i++));
//                 printf("inserted: %d\n", --i-'A');
//                 while ((i = ringbufferGet(&rb)) != -1) {
//                         printf("%c\n", i);
//                 }
//                 /* break alignment */
//                 ringbufferPut(&rb, 'C');
//                 ringbufferGet(&rb);
//         }

//         return 0;
// }

int main(int argc, char **argv) {
        struct ringbuffer rb;
        int i, j;
        if (ringbufferInit(&rb, 10) == NULL) {
                fprintf(stderr, "failed to init rb!\n");
                return 1;
        }

        printf("created rb with size: %zu\n", ringbufferSize(&rb));
        printf("availabel: %zu\n", ringbufferAvailable(&rb));
        for (j = 0; j < 6; j++) {
                ringbufferPut(&rb, 'C');
                ringbufferGet(&rb);
        }
        ringbufferPut(&rb, 'A');
        ringbufferPut(&rb, 'A');
        ringbufferPut(&rb, 'A');
        ringbufferPut(&rb, 'A');
        ringbufferPut(&rb, 'A');
        ringbufferPut(&rb, 'A');
        ringbufferPut(&rb, 'A');
        ringbufferPut(&rb, 'A');
        ringbufferPut(&rb, 'A');
        ringbufferGet(&rb);
        ringbufferGet(&rb);
        ringbufferGet(&rb);
        ringbufferGet(&rb);
        ringbufferPut(&rb, 'A');
        ringbufferPut(&rb, 'A');
        ringbufferGet(&rb);
        ringbufferGet(&rb);
        ringbufferGet(&rb);
        ringbufferGet(&rb);
        ringbufferGet(&rb);
        ringbufferGet(&rb);
        ringbufferGet(&rb);

        printf("pp = %d; gp = %d\n", rb.pp, rb.gp);

        printf("availabel: %zu\n", ringbufferAvailable(&rb));
        return 0;
}