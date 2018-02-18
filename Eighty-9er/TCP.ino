

//-------------------------------------------------------
void serveTCP() {
   
  //check if there are any new clients connecting
  if (server.hasClient()){
    for(CliNr = 0; CliNr < MAX_SRV_CLIENTS; CliNr++){
      //find free/disconnected spot
      if (!serverClients[CliNr] || !serverClients[CliNr].connected()){
        if(serverClients[CliNr]) serverClients[CliNr].stop();
        serverClients[CliNr] = server.available();
        // Serial.print("New client: #"); Serial.println(CliNr);
        continue;
      }
    }
    //no free/disconnected spot so reject
    WiFiClient serverClient = server.available();
    serverClient.stop();
  }
 }  
//-------------------------------------------------------
void readCli() {
  //boolean rdy = false; 
  //check TCP clients for commands
  for(CliNr = 0; CliNr < MAX_SRV_CLIENTS; CliNr++){
    if (serverClients[CliNr] && serverClients[CliNr].connected()){
      if(serverClients[CliNr].available()){
        
        //get data from the telnet client and push it to the UART
        while(serverClients[CliNr].available()) { // serve clients in order
          unsigned long LastCh = millis();
          
          while( (serverClients[CliNr].available() > 0)  && ((millis()-LastCh) < IFtimeout)) { //wait for end of string or timeout
             char OneRead=serverClients[CliNr].read();
             if ((OneRead == '\n')) {               //end of string
                  RXpos = 0;
                  ParseCommand();
              } 
            if ((OneRead > 31) && (OneRead < 127))  {
              RXbuf[RXpos++] = OneRead;
              RXbuf[RXpos] = '\0';   
            }
            yield();
          } // while char
          
          //flush if not complete otherwise already flushed at parser 
           RXbuf[0] = '\0';        
        } // while curr client
        
      } // if client nr has data
      
    } // if client nr is connected
    
  } // for all clients
}


//------------------------------------------------------
//-------------------------------------------------------
void readSer() {
if (serialHamlib) {
  byte l = 0;
  
if (Serial.available() > 0) {
 char OneRead=Serial.read();
             if ((OneRead == '\n')) {               //end of string
               RXpos = 0;
               ParseCommand();
              } 
             if ((OneRead > 31) && (OneRead < 127)) {
              RXbuf[RXpos++] = OneRead;
              RXbuf[RXpos] = '\0';  
            }
            yield();
  }
 }
}
//-------------------------------------------------------
void writeCli() {
  if (!serialHamlib) {
  if (serverClients[CliNr] && serverClients[CliNr].connected()){
     serverClients[CliNr].write((const uint8_t*)TXbuf, sizeof(TXbuf));
     yield();
     }
   } else {
   Serial.print((char*)TXbuf);  
  } 
  TXbuf[0] = '\0'; 
}

//-------------------------------------------------------
void showNumberDec(int a) {
Serial.println(a);
}

