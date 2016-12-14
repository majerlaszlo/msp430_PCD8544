/*
 * uscia0_spi.h
 *
 *  Created on: 2016. dec. 14.
 *      Author: lmajer
 *
 *      USCIA0 in 3 wire SPI mode
 */

//  Pin description:
//  P1.1 - MISO
//  P1.2 - MOSI
//  P1.4 - CLK

#ifndef USCIA0_SPI_H_
#define USCIA0_SPI_H_

void init_spi(void);
unsigned char transferSpi(unsigned char data);  // Send data and retun with received data

#endif /* USCIA0_SPI_H_ */
