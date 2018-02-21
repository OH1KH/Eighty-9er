// DDS transfers a byte, a bit at a time, LSB first to the 9850 via serial DATA line
void tfr_byte(byte data)
{
  for (int i=0; i<8; i++, data>>=1) {
    digitalWrite(DATA, data & 0x01);
    pulseHigh(W_CLK);   //after each bit sent, CLK is pulsed high
  }
}
//-------------------------------------------------------
 // DDS frequency calc from datasheet page 8 = <sys clock> * <frequency tuning word>/2^32
void sendFrequency(unsigned long frequency) {
unsigned long k=0;

if ( frequency > QRGmax ) { frequency = QRGmax; MyQrg = QRGmax;};
if ( frequency < QRGmin ) { frequency = QRGmin; MyQrg = QRGmin;};
  
  if ( CWkey == 0) { //rx
     frequency = frequency+CWrit;
     if (!serialHamlib) {
      #ifdef DEBUG
       Serial.println("R"+String(frequency-CWrit));
      #endif 
       k = frequency-CWrit;
      } 
   } else { //tx
     if  (!serialHamlib) {
      #ifdef DEBUG
        Serial.println("T"+String(frequency));
      #endif 
       k = frequency;
      }  
   }
  
 
  int32_t freq = frequency * 4294967295/125000000;  // note 125 MHz clock on 9850
  for (int b=0; b<4; b++, freq>>=8) {
    tfr_byte(freq & 0xFF);
  }
  tfr_byte(0x000);   // Final control byte, all 0 for 9850 chip
  pulseHigh(FQ_UD);  // Done!  Should see output

#if !defined DEBUG
 if (k!=0) {
   switch (RotStep) {  
          case   10: k = (k - QRG010)/10; break;
          case  100: k = (k - QRG100)/100;  break;
          case 1000: k =  k/1000;  break;
   } 
     if (!CWkey) showNumberDec(k); else showNumberDec(cwSpeed);
     ShowBase = millis()+upd7seg;
 }
#endif 
}
//------------------------------------------------------
void RotIsr() { //rotary encoder ISR: falling edge Rot1
  if (digitalRead(Rot2) == HIGH ) {  
    Step++;
  } else {
    Step--;
  }
}
//------------------------------------------------------
void RotKnob() {   
  if ((Step != 0) && (CWkey == 0 )) {
      MyQrg = MyQrg + Step*RotStep;
      sendFrequency(MyQrg);
      ShowBase = millis()+upd7seg;
      Step = 0;
      }  
      yield();       
}
//------------------------------------------------------
void RotSteps(){

  boolean ritChange = false;

  if (analogRead(A0) > 500) {
  switch (RotStep) {  //change rotseteps
   case   10: RotStep = 100; break;
   case  100: RotStep = 1000;  break;
   case 1000: {
                showNumberDec(CWrit);
                int lo=0;
                while ( lo<200 ) {
                  if (Step != 0) {
                    CWrit = CWrit + Step*10;
                    if (CWrit < -9000) CWrit =-9000;   //max & min values for rit
                    if (CWrit >  9000) CWrit = 9000;
                    sendFrequency(MyQrg);             //set new rit in effect
                    if (CWrit>-999 ) showNumberDec(CWrit); else showNumberDec(CWrit/10); //4digits cant show negative under -999  
                    Step = 0;
                    lo = 0;
                    ritChange = true;
                    ShowBase = millis()+upd7seg;
                    }
                  lo++;
                  delay(10);
                  }
                 if (ritChange) { //value has changed
                  eewint(4,CWrit);
                  eesum();
                 }
                RotStep = 10;
                }; break;
   
   default: RotStep = 100;  break;
   } 
   if ((!serialHamlib) && (!wifiHamlib)) { 
   #ifdef DEBUG
    Serial.println(RotStep);
   #endif 
  
   showNumberDec(RotStep);
   ShowBase = millis()+upd7seg;
 
    } 
   while (analogRead(A0) > 500) delay(50);
  }
 
 
}

