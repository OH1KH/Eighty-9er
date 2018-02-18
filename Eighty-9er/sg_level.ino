
//-------------------------------------------------------    
void get_level(){
     strcpy(Rcmd,"get_level:");
     strcpy(Ritem,"KEYSPD ");
     itoa(cwSpeed,Rvalue,10);
     response(false,true,longch); 
} //-------------------------------------------------------    
void set_level() {  
    boolean rep =false;
    int Csp;
    if (strstr(RXbuf,"KEYSPD")){
      shlRX(6);
      trimRX(' ');
      Csp = atoi(RXbuf);
      if (Csp != 0) { //conv ok
         if (Csp < CWmin) Csp = 5;
         if (Csp > CWmax) Csp = 50;
         setCWspeed(Csp);
         rep =true;
        } 
      }
     strcpy(Rcmd,"set_level:");
     strcpy(Ritem,"KEYSPD "); 
     if (rep) itoa(Csp,Rvalue,10); else strcpy(Rvalue,RXbuf);
     response(true,rep,longch);
}
   
//-------------------------------------------------------  

