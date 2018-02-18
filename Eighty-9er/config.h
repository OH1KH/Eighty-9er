/* Eighty-9er DDS copyright (C) OH1KH 2017  (See GPL statement at end of config.h)
 *
 * This program drives Eighty-9er DDS
 */

//#define DEBUG     //comment out-in by needs 

#define MAX_SRV_CLIENTS 3
//how many clients should be able to telnet to this rig
//recommend: USE 1. If you need more connects stack rigctlds. Put one running @ localhost and tell that
//it's "rig" is "-m2" (rigctld) and  point it to rig-WiFi with proper IP address:
//  rigctld -m2 --set-conf=rig_pathname=192.168.60.220:4532,timeout=3000 -vvvv


#define CWFREQ 800       //tone of morse code (not used now) 
#define CWmax 50	       //CW speed max and minimum wpm
#define CWmin 5
#define CWdef 18        //defaut speed of morse code in WPM (words per minute) 
#define CWtail 500      // tail ms to keep xit in after last element sent
#define CWritBase  700      //rit in Hz during rx (plain always added. Actually rx is rit up, displays TX freq)
#define MAXtxTime 120000 // max tx time via rigctld t1 (ms)

#define QRGdef 3560000  //DDS default frequency
#define QRGmax 3800000  // DDS upper and lower limits
#define QRGmin 3500000
#define QRG010 3500000  //led display shifts when step is 10
#define QRG100 3000000  // step 100

#define RXmax 199          //max characters+1 (0 base) in buffer

#define IFtimeout 900  //timeout for response ms
#define RepDelay 10  //wait ms between repeats.

#define upd7seg 2000   // update interval for 7 segment display 

#define W_CLK 13       // Pin 13 - connect to AD9850 module word load clock pin (CLK)
#define FQ_UD 12       // Pin 12 - connect to freq update pin (FQ)
#define DATA 14        // Pin 14 - connect to serial data load pin (DATA)
#define RESET 16       // Pin 16 - connect to reset pin (RST).
#define Rot1 4         //rotary encoder A
#define Rot2 5         //rotary encoder B
#define EETOP 20       //max reserved eeprom bytes
                       //byte 0 xored checksum of whole cwmem area, 
                  
#define pulseHigh(pin) {digitalWrite(pin, HIGH); delayMicroseconds(5); digitalWrite(pin, LOW); }

#define ditpad 0                //iambic keyer pad pins
#define dahpad 2
#define CWOUT 15         


IPAddress ipAP(192, 168, 4, 1);
IPAddress ipAPgw(192, 168, 4, 1); 
IPAddress ipAPmask(255, 255, 255, 0); 
//------------------------------------------------------------------



/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
