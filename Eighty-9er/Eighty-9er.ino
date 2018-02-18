


/*  Eighty-9er QRP CW tranceiver  OH1KH 2017-2018
 *   
 *   DDS driven 3,5 -3,7MHz
 *   Digital vfo knob. Pushing knob changes tuning steps 10->100->1000->(set rx rit)10Hz
 *   RX rit defaults +700 over transmitting(displayed) frequency. Adjustable -9000 to +9000
 *   4digit / 7seg display for showing: Starting selections, frequency, vfo step, CW Wpm
 *   Emulates hamlib rigctld (use rig model 2 for connecting from software)
 *   rigctld either from serial port 115200baud (requires external TTL to USB converter) or via WiFi network
 *   Wifi supports connecting to existing accespoint as station, or creating a standalone accespoint with dhcp.
 *   iambic keyer built in, but also has socket for direct keying (RX auto-rit does not wirk with stright key)
 *   Speaker and headpone soket for audio
 *   
 *   
 *   To DO:
 *   better interrupt keying
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManage



#include "config.h"

char vers[]     = "V3.3";         //Version  
char localAP[]  = "Local80";      //name for local accesspoint (if MGr not used)
byte mac[6];                      //mac display for AP 
char RXbuf[RXmax] = {0};           //buffer for receiving commands (length limits morse out text max)
char TXbuf[RXmax] = {0};           //buffer for sending responses to client
byte RXpos = 0;
byte TXpos = 0;
char Rcmd[15] = {0};              // for response
char Ritem[15] = {0}; 
char Rvalue[15] = {0}; 

WiFiServer server(4532);          // this is standard rigctld's port
WiFiClient serverClients[MAX_SRV_CLIENTS];

uint8_t CliNr; //client #nr
//set wifi hostname  !!
char HOST[11] = "Eighty-9er";

char longch = '\n';
boolean serialHamlib = false;        //rigctld uses tcp or serial
boolean wifiHamlib = false;

unsigned long MyQrg = QRGdef;     // will store qrg in Hz
int CWrit = CWritBase;
const String mode_is = "CW";
const String passband = "2200";

unsigned int RotStep = 100;             //rotary encoder step in Hz
int Step = 0;                           //steps by ISR
unsigned long ShowBase = 0;            //delay timer to show freq msb

unsigned int CWkey = 0;               //rig keyed mem
unsigned long CWkeyed = 0;            //delay timer
byte CWdit = ditpad;                 //iambic keyer pad pins default
byte CWdah = dahpad;
byte Idit = 1;                  // keyer state pressed set by interrupts
byte Idah = 1;
unsigned int cwSpeed = CWdef;
byte CWstate = 0;		//keyer state

unsigned int duration;
char morseLib[63] [6]= {
                        { 0,0,0,0,0,0 }, // <space>
                        { 1,1,3,3,1,0 }, // !
                        { 0,0,0,0,0,0 }, // "
                        { 0,0,0,0,0,0 }, // #
                        { 0,0,0,0,0,0 }, // $
                        { 0,0,0,0,0,0 }, // %
                        { 0,0,0,0,0,0 }, // &
                        { 0,0,0,0,0,0 }, // '
                        { 0,0,0,0,0,0 }, // (
                        { 0,0,0,0,0,0 }, // )
                        { 0,0,0,0,0,0 }, // *
                        { 0,0,0,0,0,0 }, // +
                        { 3,3,1,1,3,3 }, // ,
                        { 3,1,1,1,1,3 }, // -
                        { 1,3,1,3,1,3 }, // .
                        { 3,1,1,3,1,0 }, // /
                        { 3,3,3,3,3,0 }, //0
                        { 1,3,3,3,3,0 }, //1
                        { 1,1,3,3,3,0 }, //3
                        { 1,1,1,3,3,0 }, //3
                        { 1,1,1,1,3,0 }, //4
                        { 1,1,1,1,1,0 }, //5
                        { 3,1,1,1,1,0 }, //6
                        { 3,3,1,1,1,0 }, //7
                        { 3,3,3,1,1,0 }, //8
                        { 3,3,3,3,1,0 }, //9
                        { 0,0,0,0,0,0 }, // :
                        { 0,0,0,0,0,0 }, // ;
                        { 0,0,0,0,0,0 }, // <
                        { 3,1,1,1,3,0 }, // =
                        { 0,0,0,0,0,0 }, // >
                        { 1,1,3,3,1,1 }, // ?
                        { 0,0,0,0,0,0 }, // @
                        { 1,3,0,0,0,0 }, //a
                        { 3,1,1,1,0,0 }, //b
                        { 3,1,3,1,0,0 }, //c
                        { 3,1,1,0,0,0 }, //d
                        { 1,0,0,0,0,0 }, //e
                        { 1,1,3,1,0,0 }, //f
                        { 3,3,1,0,0,0 }, //g
                        { 1,1,1,1,0,0 }, //h
                        { 1,1,0,0,0,0 }, //i
                        { 1,3,3,3,0,0 }, //j
                        { 3,1,3,0,0,0 }, //k
                        { 1,3,1,1,0,0 }, //l
                        { 3,3,0,0,0,0 }, //m
                        { 3,1,0,0,0,0 }, //n
                        { 3,3,3,0,0,0 }, //o
                        { 1,3,3,1,0,0 }, //p
                        { 3,3,1,3,0,0 }, //q
                        { 1,3,1,0,0,0 }, //r
                        { 1,1,1,0,0,0 }, //s
                        { 3,0,0,0,0,0 }, //t
                        { 1,1,3,0,0,0 }, //u
                        { 1,1,1,3,0,0 }, //v
                        { 1,3,3,0,0,0 }, //w
                        { 3,1,1,3,0,0 }, //x
                        { 3,1,3,3,0,0 }, //y
                        { 3,3,1,1,0,0 }, //z
                        { 1,3,3,1,3,0 }, // [ Å (a with round)
                        { 3,3,3,1,0,0 }, // \ Ö (o with dots)
                        { 1,3,1,3,0,0 }, // ] Ä (a with dots)
                   };
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//------------------------------------------------------- 
//-------------------------------------------------------
//-------------------------------------------------------

