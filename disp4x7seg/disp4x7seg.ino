
  /* 4x7segment driver common anode OH1KH -2018
   *  
   *  Uses Arduino Nano as driver
   *  async 115200baud serial input (only 1 pin needed!)
   */
  // segments  vs digital pins
  //cathodes
#define OUTa 8
#define OUTb 2
#define OUTc 4 
#define OUTd 5
#define OUTe 6
#define OUTf 7
#define OUTg 3

 
 // positions  vs digital pins  (0123, 0 is leftmost)
 //common anode
byte CommonAnode[4] = { 13,12,11,10 };

byte posit;
byte disp[4] = {B1111111,B1111111,B1111111,B1111111};
byte buff[4] = {B1111111,B1111111,B1111111,B1111111};



byte charLib[66] =   {             //      segments by bits
                        B00000000, // <space>    000
                        B00110000, // !         5   1
                        B00100000, // "         5   1
                        B00000000, // #         5   1
                        B00000000, // $          666   
                        B00000000, // %         4   2
                        B00000000, // &         4   2
                        B00100000, // '         4   2
                        B00111001, // (          333
                        B00001111, // )
                        B00000000, // *
                        B00000000, // +
                        B00000000, // 
                        B01000000, // -
                        B00000000, // .
                        B01010010, // /
                        B00111111, //0
                        B00000110, //1
                        B01011011, //2
                        B01001111, //3
                        B01100110, //4
                        B01101101, //5
                        B01111101, //6
                        B00000111, //7
                        B01111111, //8
                        B01100111, //9
                        B00000000, // :
                        B00000000, // ;
                        B00000000, // <
                        B00000000, // =
                        B00000000, // >
                        B01010011, // ?
                        B00000000, // @
                        B01110111, //a
                        B01111100, //b
                        B01011000, //c
                        B01011110, //d
                        B01111001, //e
                        B01110001, //f
                        B01101111, //g
                        B01110110, //h
                        B00000110, //i
                        B00011110, //j
                        B00000000, //k
                        B00111000, //l
                        B00000000, //m
                        B01010100, //n
                        B00111111, //o
                        B01110011, //p
                        B01100111, //q
                        B01010000, //r
                        B01101101, //s
                        B01111000, //t
                        B00111110, //u
                        B00011100, //v
                        B01100010, //w
                        B00000000, //x
                        B01100110, //y
                        B00000000, //z
                        B00000000, //[ 
                        B00000000, //\
                        B00000000, //]
                        B00000000, //^
                        B00000000, //_
                        B00000000, //'                       
                    };

//-------------------------------------------------------
boolean readSer() { 

 byte j = 0;
 int  i = 0;
  
 while (Serial.available() > 0) {
  
 char OneRead=Serial.read();
             if ((OneRead == '\n')) {                        //end of input string copy buffer to display
               Serial.println(" buff");
               for (i=0;i<4;i++) {
                disp[i] = buff[i];
                buff[i] = B1111111; //blank 
                Serial.print("   ");
                Serial.print(disp[i],BIN); 
                Serial.print("  ");
               }
               
               Serial.println(" disp");
               return true;
             }
             
             if (OneRead > 31) {        //accepted ascii chars or direct segment bytes
               if (( OneRead > 96) && (OneRead < 128)) {  j = charLib[(OneRead-64)]; }      //turn to upcase first -32
                 else { j =  charLib[(OneRead-32)]; }
               Serial.print(OneRead); 
               if (OneRead > 127) { j = OneRead & B01111111; } // if high bit set direct segment byte input
             
             for (i=0;i<3;i++)  buff[i] = buff[i+1];    // rotate left
             buff[3] = ~j;                                  //bitwise not if common anode     
             Serial.print("  ");
             Serial.print(buff[3],BIN); 
             Serial.print("  ");
            }
 }
}
//-------------------------------------------------------
void allOff() { 
 for (byte i=0;i<4;i++){
 digitalWrite(CommonAnode[i],LOW); // common is anode, turn digit on 
 }
}
//-------------------------------------------------------
 void segments(byte pos) {
//set segments

 digitalWrite(OUTa,(disp[pos] & B00000001) );
 digitalWrite(OUTb,((disp[pos] & B00000010) >> 1));
 digitalWrite(OUTc,((disp[pos] & B00000100) >> 2));
 digitalWrite(OUTd,((disp[pos] & B00001000) >> 3));
 digitalWrite(OUTe,((disp[pos] & B00010000) >> 4));
 digitalWrite(OUTf,((disp[pos] & B00100000) >> 5));
 digitalWrite(OUTg,((disp[pos] & B01000000) >> 6));
}
//-------------------------------------------------------

//-------------------------------------------------------

//-------------------------------------------------------
void setup() {
Serial.begin(115200);
while(!Serial) { } // Wait for serial to initialize.
//cathodes
pinMode(2,OUTPUT);
pinMode(3,OUTPUT); 
pinMode(4,OUTPUT); 
pinMode(5,OUTPUT); 
pinMode(6,OUTPUT); 
pinMode(7,OUTPUT); 
pinMode(8,OUTPUT);
//Common anodes 
pinMode(9,OUTPUT); 
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(12,OUTPUT);

allOff;
digitalWrite(2,HIGH);
digitalWrite(3,HIGH);
digitalWrite(4,HIGH);
digitalWrite(5,HIGH);
digitalWrite(6,HIGH);
digitalWrite(7,HIGH);
digitalWrite(8,HIGH);

posit = 0;

}
//-------------------------------------------------------
void loop() {
  readSer();
  allOff();
  segments(posit);
  digitalWrite(CommonAnode[posit],HIGH); // common is anode, turn digit on
  posit++;
  if (posit>3) posit = 0;
  delay(4);
  
}
