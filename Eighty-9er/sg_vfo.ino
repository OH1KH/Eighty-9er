
//------------------------------------------------------- 
void get_vfo() { //get vfo is fake just vfoA
     // get vfo
    strcpy(Rcmd,"get_vfo:");
    strcpy(Ritem,"VFO: ");
    strcpy(Rvalue,"VFOA");
    response(false,true,longch);
}
    
//-------------------------------------------------------    
void set_vfo() {  //set is fake, just one vfoA
    // set  vfo
    boolean ok = false;
    char rep[8];
    if (strstr(RXbuf,"currVFO")){
      ok = true;
      strcpy(Rvalue,"currVFO");
     }
     if (strstr(RXbuf,"VFO")){
      size_t len = sizeof(RXbuf);
      if (len == 3 ) ok = true;
      strcpy(Rvalue,"VFO");
     }
    if (strstr(RXbuf,"VFOA")){
      ok = true;
      strcpy(Rvalue,"VFOA");
     }
    strcpy(Rcmd,"get_vfo:");
    strcpy(Ritem,"VFO: ");
    response(true,ok,longch);
   }
//-------------------------------------------------------

