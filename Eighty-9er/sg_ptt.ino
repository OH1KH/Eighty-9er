
//-------------------------------------------------------
   
void get_ptt() {
    // get TX state
    strcpy(Rcmd,"get_ptt:");
    strcpy(Ritem,"PTT: ");
    itoa(CWkey,Rvalue,10);
    response(false,true,longch);
} 
//-------------------------------------------------------
void set_ptt() {
    // start/stop TX
    char pt = RXbuf[0];
    switch (pt) {
      case '0': {
            keying_set(0);
            strcpy(Rcmd,"set_ptt:");
            strcpy(Ritem,"PTT: ");
            strcpy(Rvalue,"0");
            response(true,true,longch);
            };
       break;
      case '1': {
           digitalWrite(CWOUT, 1);
           keying_set(-1);
           strcpy(Rcmd,"set_ptt:");
           strcpy(Ritem,"PTT: ");
           strcpy(Rvalue,"1");
           response(true,true,longch);
            }     
       break;
      default :{
         strcpy(Rcmd,"set_ptt:");
         strcpy(Ritem,"PTT: ");
         strcpy(Rvalue,RXbuf);
         response(true,false,longch);
      }     
     break;  
     } // switch pt
}
//-------------------------------------------------------
