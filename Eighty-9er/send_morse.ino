

//-------------------------------------------------------
void send_morse() {// send string as CW 
    strcpy(Rcmd,"send_morse:");
    Ritem[0] = '\0';
    Rvalue[0] = '\0';
    response(true,true,longch);
    MorseTxEsp_CSend(cwSpeed,RXbuf);
    }
//-------------------------------------------------------

