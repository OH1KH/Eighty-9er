
//-------------------------------------------------------
void get_mode() { //this is fake, just CW 2,2kHz
    // get mode 
    strcpy(Rcmd,"get_mode:");
    strcpy(Ritem,"Mode: CW ");
    strcpy(Rvalue,"Passband: 2200"); 
    response(false,true,longch); 
}   
//-------------------------------------------------------
void get_modeS() { //this is fake, just CW 2,2kHz
    // get mode 
    strcpy(Rcmd,"get_mode:");
    strcpy(Ritem,"CW "); //this does not print
    strcpy(Rvalue,"CW\n2200"); 
    response(false,true,longch); 
}     
//-------------------------------------------------------     
void set_mode() { //we do not use passband as no filters in rig (CWn)+M
   // set mode
   if (longch == '\n') {
    Rcmd[0]='\0';
    Ritem[0]='\0';
    Rvalue[0]='\0'; 
    response(true,(ModeSet()),longch);
   } else {
    strcpy(Rcmd,"set_mode: ");
    Ritem[0]='\0';
    strcpy(Rvalue,RXbuf); 
    response(true,(ModeSet()),longch);  
   }
} 
//-------------------------------------------------------
boolean ModeSet() { //fake, just error if not CW
    boolean ok = false;
    if (strstr(RXbuf,"CW")){
      ok = true;
     }
  return ok; 
}
