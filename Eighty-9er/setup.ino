
//------------------------------------------------------- 
boolean both_pads(String action) {

boolean result = false;
boolean b = true;
#ifdef DEBUG
 Serial.print(F("Enter "));
 Serial.print(action);
 Serial.println(F(" setup pressing both pads"));
#endif
  for (int i=0; i<100; i++) { 
     if (i%10 == 0) {
      if (b) Serial.println(action); else Serial.println() ; 
      b = !b; 
     }
     delay(50);
     //trigger pin or both paddles down to enter wifi setup.
     if ( (digitalRead(CWdit)==LOW) && (digitalRead(CWdah)==LOW) )  {
     result = true;
     i = 150;
     }
   }
 while  ( (digitalRead(CWdit)==LOW) && (digitalRead(CWdah)==LOW) ) delay(5); 
 #ifdef DEBUG
  Serial.println();
 #endif  
 return result;  
}
//------------------------------------------------------- 
//------------------------------------------------------- 
void append(char* s, char c) {
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}
//------------------------------------------------------- 

void response(boolean is_set, boolean okay, char lch) {
                       
if (okay) {
  if (lch == '\n') {
   strcpy(TXbuf,Rvalue);
   strcat(TXbuf,"\n");
   writeCli();
    if (is_set) {
      strcpy(TXbuf,"RPRT 0\n");
      writeCli();
      }
    } else {
       if (lch == '+') lch = '\n';
       if (is_set) {
          strcpy(TXbuf,Rcmd);
          writeCli();
          } 
         else { 
         strcpy(TXbuf,Rcmd);
         append(TXbuf,lch);
         strcat(TXbuf,Ritem );
         writeCli();
         }
       strcpy(TXbuf,Rvalue);
       append(TXbuf,lch);
       strcat(TXbuf,"RPRT 0\n");
       writeCli();
      }

      
 } else { //not okay
   if (lch == '\n') { 
      strcpy(TXbuf,"RPRT -1\n");
      writeCli();
      }
     else {  
      if (lch == '+') lch = '\n';
      if (is_set) {
        strcpy(TXbuf,Rcmd);
        writeCli();
        } 
       else { 
        strcpy(TXbuf,Rcmd);
        append(TXbuf,lch);
        strcat(TXbuf,Ritem );
        writeCli();
       }
      strcpy(TXbuf,Rvalue);
      append(TXbuf,lch);
      strcat(TXbuf,"RPRT -1\n");
      writeCli();
     };
   };
}      


//------------------------------------------------------- 
void setup(void) {
  boolean b=true;
  delay(100);
  Serial.setTimeout(2000);
  Serial.begin(115200); 
  while(!Serial) { } // Wait for serial to initialize.
//------------------------------------------------------- 
#ifdef DEBUG  
  Serial.print(F("\n\r \n\rStarting setup with "));
#endif
//------------------------------------------------------- 
if (!both_pads(F("F on")))  wifi_off(); else WiFi.mode(WIFI_AP_STA); 
//------------------------------------------------------- 
  //wifi setup
  if (both_pads(F("WiFi"))) {
    wifiSetup();
    #ifdef DEBUG
    Serial.println(F("WiFi setup,done"));
    #endif
   } else {
    serialHamlib = both_pads(F("s hl")); //serial hamlib
    #ifdef DEBUG
    Serial.println(F("serialHamlib setup,done"));
    #endif
  }
  delay(100);
  
//------------------------------------------------------- 
 // needs frequency save
/*  eeprom
    *  0 checsum
    *  1 cwdit paddle
    *  2 cwdah paddle
    *  3 cwspeed
    *  4 CWrit Hi
    *  5 CWrit Lo
    */
   if (eestart()) {
     byte a = eerbyte(1);  // zero eeprom has checksum ok !!
     byte b = eerbyte(2);
     if ((((a == ditpad) || (a == dahpad)) && (a != b)) && (((b == ditpad) || (b == dahpad)) && (a != b))) { //must be in limits and not equal
        CWdit = a;
        CWdah = b; 
      } else {            //iambic keyer pad pins default
        CWdit = ditpad;
        CWdah = dahpad;       
      }
      a = eerbyte(3);  
     if ((a >= CWmin) && (a <= CWmax)) cwSpeed = a; // must be in limits
     
     int r = eerint(4); // rit
     if ((r >= CWritMin) && (r <= CWritMax)) CWrit = r; // must be in limits
     
   }
   #ifdef DEBUG
   Serial.println(F("Read eeprom, done"));
   #endif

   
  //MorseTxEsp_setup
  pinMode(CWOUT,OUTPUT);
  pinMode(CWdit,INPUT);
  pinMode(CWdah,INPUT);
  #ifdef DEBUG
  Serial.println(F("Paddle swap, press dit pad"));
  #endif
  for (int i=0; i<100; i++) { 
     if (i%10 == 0) {
      if (b) Serial.println(F("-dit")); else Serial.println(F("dit-")); ; 
      b = !b; 
     }
     delay(50);
    if (digitalRead(CWdah) == LOW ) { //want reverse pads = keep wanted dit down during restart
       byte a = CWdit;
       CWdit = CWdah; //iambic keyer pad pins swithed
       CWdah = a; 
       Serial.println(F("swap"));
       delay(200);
       i=100; //exit loop
      }
    if (digitalRead(CWdit) == LOW ) { //no need to reverse, exit 
        i=100; //exit loop
       }
  }
  #ifdef DEBUG
  Serial.println();
  #endif
  if((eerbyte(1) != CWdit ) || (eerbyte(2) != CWdah )){ //write pads if changed
     eewbyte(1,CWdit);
     eewbyte(2,CWdah);
     eesum();
   }
  #ifdef DEBUG
  Serial.println(F("Paddle swap,done"));
  #endif
  attachInterrupt(CWdit,dit_int,FALLING);
  attachInterrupt(CWdah,dah_int,FALLING);
  


//-------------------------------------------------------
   // configure data pins for DDS 
  pinMode(FQ_UD, OUTPUT);
  pinMode(W_CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(RESET, OUTPUT);
  
  pinMode(RESET, OUTPUT);
  
  pulseHigh(RESET);
  pulseHigh(W_CLK);
  pulseHigh(FQ_UD);  // this pulse enables serial mode - Datasheet page 12 figure 10

  //rotary encoder
  pinMode(Rot1,INPUT);
  pinMode(Rot2,INPUT);
  attachInterrupt(Rot1,RotIsr,FALLING);
 #ifdef DEBUG
 Serial.println(F("DDS vfo setup, done. Init DDS"));
 #endif

 sendFrequency(MyQrg); 
 #ifdef DEBUG 
 Serial.print(F("Serial hamlib "));
 Serial.println(serialHamlib);
 Serial.print(F("WiFi hamlib "));
 Serial.println(wifiHamlib);
 #endif
 
 ShowBase = millis();

 
//-------------------------------------------------------
 


}

