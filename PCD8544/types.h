/*
 * types.h
 *
 *  Created on: 2016. dec. 14.
 *      Author: lmajer
 */

#ifndef TYPES_H_
#define TYPES_H_

#define HIGH    1
#define LOW     0

typedef struct
{
    volatile unsigned char b0:  1;
    volatile unsigned char b1:  1;
    volatile unsigned char b2:  1;
    volatile unsigned char b3:  1;
    volatile unsigned char b4:  1;
    volatile unsigned char b5:  1;
    volatile unsigned char b6:  1;
    volatile unsigned char b7:  1;

}bitfield;

typedef union
{
    bitfield *bit;
    volatile unsigned char *bits;
}port;


#endif /* TYPES_H_ */
