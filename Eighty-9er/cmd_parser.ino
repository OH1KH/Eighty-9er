
//-------------------------------------------------------
void trimRX(char totrim) { //trim X characters from start
  byte l=0;
  while ((RXbuf[0] == totrim) && (RXbuf[0] != '\0')) {
    do { 
       RXbuf[l] = RXbuf [l+1];
       l++;
    } while ((RXbuf[l]) && (l<=RXmax));
   }
}
//------------------------------------------------------- 
void shlRX(byte r) { //erase first r char
  byte l=0;
  byte f=0;
 do{ 
  if (RXbuf[l]) { 
    do { 
       RXbuf[l] = RXbuf [l+1];
       l++;
    } while ((RXbuf[l]) && (l<=RXmax));
  }
  l=0;
  f++;
 } while (f<r);       
}
 //-------------------------------------------------------
void ParseCommand(){
char starts;
byte l=0;

 while ((RXbuf[l]) && (l<=RXmax)) {
  starts = RXbuf[l];
  if ( (starts !='+') && (starts !=',') && (starts !='|') && (starts !=';') && (starts != 92) )  {
   //accept only selected short commands queued 
   switch (starts) { 
   case 'l': get_level();  break;    
   case 't': get_ptt();    break;  
   case 'f': get_freq();   break;
   case 'j': get_rit();    break;  
   case 'm': get_modeS();   break;    
   case 'v': get_vfo();    break; 
   case 'q': serverClients[CliNr].stop(); break;  
   case 'Q': serverClients[CliNr].stop();  break;
   //special, not hamlib commands:  
   case 'Z': wifi_off(); break;  // NOTE! Will drop your connect !
   case 'H': wifi_output(20.5);  break;//High
   case 'P': wifi_output(1); break; //qrP
  
   default : {ParsePart(); l= RXmax; } break; 
   }
  } else {
    ParsePart(); // if/not short cmd
    l= RXmax; //next quits loop
    }
  l++;
 } //while loop
RXbuf[0] ='\0';
longch = '\n';
}
 //-------------------------------------------------------    
void ParsePart() { 
  char First = RXbuf[0];

  if ((First =='+') || (First ==',') || (First =='|') || (First ==';')) {
    longch = First;
    shlRX(1);
    First = RXbuf[0]; // new first
  } else longch = '\n';
  
// we know now first, leave only rest of command
    shlRX(1);
    //remove spaces from start
    trimRX(' '); 
   //supported rigctld long/short commands
 switch (First) {
  
   case 'b': send_morse(); break; 
   case 'L': set_level();  break; 
   case 'l': get_level();  break;    
   case 't': get_ptt();    break; 
   case 'T': set_ptt();    break;  
   case 'f': get_freq();   break; 
   case 'F': set_freq();   break; 
   case 'j': get_rit();    break;  
   case 'J': set_rit();    break;  
   case 'm': get_mode();   break;    
   case 'M': set_mode();   break;    
   case 'v': get_vfo();    break; 
   case 'V': set_vfo();    break;
   case 'q': serverClients[CliNr].stop(); break;  
   case 'Q': serverClients[CliNr].stop();  break;  
   
    //backslash = longmode
   case 92 : 
    {
     if (strstr(RXbuf,"dump_caps")) dump_caps();
     if (strstr(RXbuf,"dump_state")) dump_state();
     
     if (strstr(RXbuf,"get_freq")) get_freq();
     if (strstr(RXbuf,"get_mode")) get_mode();
     if (strstr(RXbuf,"get_vfo")) get_vfo();
     if (strstr(RXbuf,"get_ptt")) get_ptt();
     if (strstr(RXbuf,"get_level")) get_level();
     if (strstr(RXbuf,"get_rit")) get_rit();
 
     if (strstr(RXbuf,"set_ptt")){ shlRX(7); trimRX(' '); set_ptt();}
     if (strstr(RXbuf,"set_vfo")){ shlRX(7); trimRX(' '); set_vfo();}
     if (strstr(RXbuf,"set_rit")){ shlRX(7); trimRX(' '); set_rit();}
     if (strstr(RXbuf,"set_freq")){ shlRX(8); trimRX(' '); set_freq();}
     if (strstr(RXbuf,"set_mode")){ shlRX(8); trimRX(' '); set_mode();}
     if (strstr(RXbuf,"set_level")){ shlRX(9); trimRX(' '); set_level();}
     if (strstr(RXbuf,"send_morse")){ shlRX(10); trimRX(' '); send_morse();}
   }  break;  //longmode command
  
   default : {
              strcpy(TXbuf,"RPRT -11\n");
              writeCli();
             } break;
              
  }//switch First
  yield();
  RXbuf[0] = '\0';
  longch = '\n';
 }//parse part
//------------------------------------------------------- 
