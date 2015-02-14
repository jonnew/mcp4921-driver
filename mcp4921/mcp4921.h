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

#ifndef MCP4921_h
#define MCP4921_h

#if ARDUINO >= 100
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif
#include <SPI.h>

//MCP4921 commands
#define DAC_CONF_ACTIVE 	(0x7000)
#define DAC_CONF_SHDN 		(0x6000)

//Function macros for setting bits in registers
#define cbi(sfr,bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr,bit) (_SFR_BYTE(sfr) |= _BV(bit))

class MCP4921 {

  public:

    MCP4921( uint16_t CS, uint16_t LDAC);

    // Onboard signal generation
	void send_test_waveform( void );
    void load_voltage( uint16_t voltage );
    void load_dac(void );
    void generate_waveform( int voltage[], uint16_t length, uint16_t sample_period_us );
	void shutdown_dac( void );
   
  private:
   
    // Private properties
	boolean _initialized;
    uint16_t _CS, _LDAC;
};

#endif



