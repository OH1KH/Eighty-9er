
//-------------------------------------------------------
void get_freq() {
   // get operating frequency
    strcpy(Rcmd,"get_freq:");
    strcpy(Ritem,"Frequency: ");
    itoa(MyQrg,Rvalue,10);
    response(false,(MyQrg != 0),longch);
}
//------------------------------------------------------- 
void set_freq() {
   // set operating frequency
   boolean ok = false;
   trimRX('0');
   int i = atoi(RXbuf);
     if (( i <= QRGmax ) && ( i >= QRGmin )) {
         MyQrg = i;  
         sendFrequency(MyQrg);
         ok = true;
         }       
    strcpy(Rcmd,"set_freq:");
    strcpy(Ritem,"Frequency: ");
    itoa(MyQrg,Rvalue,10);
    response(true,ok,longch);
  }
//-------------------------------------------------------

