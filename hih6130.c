/* 
 * File:   hih6130.c
 * Author: Raphael
 *
 * Created on 5 de Dezembro de 2017, 13:54
 */

#include "hih6130.h"
#include "my_i2c.h"
#include "configuration_bits.c"
#include <math.h>


void HIH6130_Init_Norm()
{
    I2C_Start();
    I2C_WriteByte(HIH6130_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(0x80); // Send the ADR to the talk device.
    I2C_WriteByte(0x00); // Send the ADR to the talk device.
    I2C_WriteByte(0x00); // Send the ADR to the talk device.
    I2C_Stop();
}

void HIH6130_ReadRHT()
{
    // reads data from the sensor and stores them in temporary variables that
    // are then accessed via public variables
    I2C_Start();
    I2C_WriteByte(HIH6130_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(0x00);
    I2C_RepeatedStart();
    I2C_WriteByte(HIH6130_ADR + 1); // Send the ADR to the talk device.
    _humidity_hi = I2C_ReadByte(1); // Read the data
    _humidity_lo = I2C_ReadByte(1); // Read the data
    _temp_hi = I2C_ReadByte(1); // Read the data
    _temp_lo = I2C_ReadByte(0); // Read the data
    I2C_Stop();

    // Get the status (first two bits of _humidity_hi_)
    _status = (_humidity_hi >> 6);

    // Calculate Relative Humidity
    humidity = (float) (((unsigned int) (_humidity_hi & 0x3f) << 8) | _humidity_lo) * 100 / (pow(2, 14) - 1);

    // Calculate Temperature
    temperature = (float) (((unsigned int) (_temp_hi << 6) + (_temp_lo >> 2)) / (pow(2, 14) - 1) * 165 - 40);
}

double HIH6130_ReadRH()
{
    // reads data from the sensor and stores them in temporary variables that
    // are then accessed via public variables
    I2C_Start();
    I2C_WriteByte(HIH6130_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(0x00);
    I2C_RepeatedStart();
    I2C_WriteByte(HIH6130_ADR + 1); // Send the ADR to the talk device.
    _humidity_hi = I2C_ReadByte(1); // Read the data
    _humidity_lo = I2C_ReadByte(1); // Read the data
    _temp_hi = I2C_ReadByte(1); // Read the data
    _temp_lo = I2C_ReadByte(0); // Read the data
    I2C_Stop();

    // Calculate Relative Humidity
    humidity = (double) (((unsigned int) (_humidity_hi & 0x3f) << 8) | _humidity_lo) * 100 / (pow(2, 14) - 1);
    
    return humidity;
}

unsigned char HIH6130_Get_Status()
{
    unsigned status;
    // reads data from the sensor and stores them in temporary variables that
    // are then accessed via public variables
    I2C_Start();
    I2C_WriteByte(HIH6130_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(0x00);
    I2C_RepeatedStart();
    I2C_WriteByte(HIH6130_ADR + 1); // Send the ADR to the talk device.
    _humidity_hi = I2C_ReadByte(1); // Read the data
    _humidity_lo = I2C_ReadByte(0); // Read the data
    I2C_Stop();

    // Get the status (first two bits of _humidity_hi_)
    status = (_humidity_hi >> 6);
    
    return status;
}
