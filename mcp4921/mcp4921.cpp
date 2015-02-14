/*
Copyright (c) Jon Newman (jpnewman ~at~ mit <dot> edu) 
All right reserved.

CL is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

CL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with CL.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mcp4921.h"

MCP4921::MCP4921(uint16_t CS, uint16_t LDAC) {
    
    // Set the chip select and load dac pins
    _CS = CS;
    _LDAC = LDAC;

    // Set pin modes
    pinMode(_CS, OUTPUT);
    pinMode(_LDAC, OUTPUT);

	// Get the CS and load-dac lines ready
    digitalWrite(_CS, HIGH);
    digitalWrite(_LDAC, HIGH);

    // Initialize SPI bus
    SPI.setDataMode(SPI_MODE0);
    SPI.setBitOrder(MSBFIRST);
    SPI.begin();

    // Initialize private variables
	_initialized = true;
}


void MCP4921::send_test_waveform(void) {

    uint16_t v_out = 0;

    while (v_out < 4085) {
        v_out += 10;
        load_voltage(v_out);
        load_dac();
    }
    while (v_out > 10) {
        v_out -= 10;
        load_voltage(v_out);
        load_dac();
    }
}


void MCP4921::generate_waveform( int voltage[], uint16_t length, uint16_t sample_period_us) {

    for (int i = 0; i < length; i++) {
        load_voltage(voltage[i]);
        load_dac();
        delayMicroseconds(sample_period_us);  
    }
}

void MCP4921::load_voltage( uint16_t voltage) {

    // Create data packet
    unsigned int spi_out = DAC_CONF_ACTIVE | (voltage & 0x0fff);

    // take the SS pin low to select the chip
    digitalWrite(_CS, LOW);

    //  send in the address and value via SPI:
    SPI.transfer(spi_out >> 8 & 0xff);
    SPI.transfer(spi_out >> 0 & 0xff);

    // take the SS pin high to de-select the chip:
    digitalWrite(_CS, HIGH);

}

void MCP4921::load_dac(void) {

    digitalWrite(_LDAC, LOW);
    __asm__("nop\n\t");
    __asm__("nop\n\t");
    digitalWrite(_LDAC, HIGH);
}

void MCP4921::shutdown_dac (void) {

	// Create data packet
    unsigned int spi_out = DAC_CONF_SHDN;

    // Take the CS pin low to select the chip
    digitalWrite(_CS, LOW);

    // Send in the config and data via SPI:
    SPI.transfer(spi_out >> 8 & 0xff);
    SPI.transfer(spi_out >> 0 & 0xff);

    // Take the CS pin high to de-select the chip:
    digitalWrite(_CS, HIGH);

}
