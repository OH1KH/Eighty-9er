//-------------------------------------------------------
boolean eecheck() {
  byte check = 0;
// byte 0 xored checksum of whole area
 for (int address = 1;address <= EETOP; ++address){ check = EEPROM.read(address) ^ check;};
  if (EEPROM.read(0) != check) { return false; } else { return true; };
}
//-------------------------------------------------------
void eesum() {
 //write checksum to 0
  byte check = 0;
  for (int address = 1;address <= EETOP; ++address){ check = EEPROM.read(address) ^ check;};
  EEPROM.write(0,check); 
  #ifdef DEBUG
  if (!serialHamlib) {Serial.print(F("writing eeprom check byte "));Serial.print(check);Serial.println(F(" position 0"));}
  #endif 
  EEPROM.commit(); //note here the commit!
}
//-------------------------------------------------------lowByte(dat)
boolean eestart() {
  boolean ret = true;
  #ifdef DEBUG
  if (!serialHamlib) {Serial.println(F("Reserve EEPROM"));}
  #endif 
  EEPROM.begin(EETOP); 
  #ifdef DEBUG
  if (!serialHamlib) {Serial.println(F("check EEPROM "));}
  #endif 
  if (!eecheck()) {
      #ifdef DEBUG
      if (!serialHamlib) {Serial.println(F("Is NOT ok. Writing 0 to EEPROM"));}
      #endif 
      for (int address = 0;address <= EETOP; ++address){ EEPROM.write(address,0); };
      EEPROM.commit(); //note here the commit!
      ret = false;
     } else {
     #ifdef DEBUG
     if (!serialHamlib) {Serial.println(F(" Reading EEPROM is ok."));}
     #endif 
   } 
}

//-------------------------------------------------------
//-----------------WRITES--------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
// write byte to pos NOTE must checksummed separeately
void eewbyte(int pos, byte dat) {
 #ifdef DEBUG
 if (!serialHamlib) {Serial.print(F("writing eeprom byte "));Serial.print(dat);Serial.print(F(" position "));Serial.println(pos);}
 #endif 
 EEPROM.write(pos, dat);  
 EEPROM.commit();
}
//-------------------------------------------------------
// write int (2xbyte) to pos NOTE must checksummed separeately
void eewint(int pos, int dat) {
 #ifdef DEBUG 
 if (!serialHamlib) {Serial.print(F("writing eeprom int "));Serial.print(dat);Serial.print(F(" position "));Serial.println(pos); }
 #endif 
 EEPROM.write(pos, highByte(dat)); 
 #ifdef DEBUG
 if (!serialHamlib) {Serial.print(F("writing eeprom int HI "));Serial.print(highByte(dat));Serial.print(F(" position "));Serial.println(pos);}
 #endif 
 EEPROM.write(pos +1, lowByte(dat)); 
 #ifdef DEBUG
 if (!serialHamlib) {Serial.print(F("writing eeprom int LO "));Serial.print(lowByte(dat));Serial.print(F(" position "));Serial.println(pos+1);}
 #endif 
 EEPROM.commit();
}

//-------------------------------------------------------
//-----------------READS---------------------------------
//-------------------------------------------------------
// read int (2xbyte) from pos
int eerint(int pos) {
 byte eerh = EEPROM.read(pos); // HI byte
 #ifdef DEBUG
 if (!serialHamlib) {Serial.print(F("reading eeprom int HI "));Serial.print(eerh);Serial.print(F(" from position "));Serial.println(pos);} 
 #endif 
 byte eerl = EEPROM.read(pos+1);
 #ifdef DEBUG
 if (!serialHamlib) {Serial.print(F("reading eeprom int LO "));Serial.print(eerl);Serial.print(F(" from position "));Serial.println(pos+1);}
 #endif 
 int eer = word(eerh,eerl);
 if((eer>>15) == 1) eer = eer - 65536;
 #ifdef DEBUG
 if (!serialHamlib) {Serial.print(F("reading eeprom int RESULT "));Serial.print(eer);Serial.print(F(" from position "));Serial.println(pos); }
 #endif 
return eer;
}
//-------------------------------------------------------
// read byte from pos 
byte eerbyte(int pos) {
 byte eer = EEPROM.read(pos);
 #ifdef DEBUG
 if (!serialHamlib) {Serial.print(F("reading eeprom byte "));Serial.print(eer);Serial.print(F(" from position "));Serial.println(pos);}
 #endif 
 return eer;
}
//-------------------------------------------------------

