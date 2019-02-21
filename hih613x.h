/* 
 * File:   hih6130.h
 * Author: Raphael Pereira
 *
 * Created on 5 de Dezembro de 2017, 13:54
 */

#ifndef HIH6130_H
#define	HIH6130_H

#define HIH6130_ADR 0x4E

float humidity = 0;
float temperature = 0;

unsigned char humidity_lo = 0;
unsigned char humidity_hi = 0;
unsigned char temp_lo = 0;
unsigned char temp_hi = 0;
unsigned char status = 0;

unsigned char HIH6130_Get_Status();

void HIH6130_Init_Norm();
void HIH6130_ReadRHT();


#endif	/* HIH6130_H */
