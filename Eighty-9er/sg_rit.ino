
//-------------------------------------------------------
void get_rit() {
   // get rit
    strcpy(Rcmd,"get_rit:");
    strcpy(Ritem,"Rit: ");
    itoa(CWrit,Rvalue,10);
    response(false,true,longch);
}
//-------------------------------------------------------
void set_rit() {
 boolean rep =false;
        int Csp = atoi(RXbuf);
        if (Csp != 0) { //conv ok NOTE rit 0 is not valid then!!
         if (Csp < -9000) Csp =-9000;
         if (Csp > 9000) Csp = 9000;
         CWrit = Csp;
         rep = true;
         sendFrequency(MyQrg);
         eewint(4,CWrit);
         eesum(); 
        } 
    strcpy(Rcmd,"set_rit:");
    strcpy(Ritem,"Rit: ");
    itoa(CWrit,Rvalue,10);
    response(true,rep,longch);
}
//-------------------------------------------------------

