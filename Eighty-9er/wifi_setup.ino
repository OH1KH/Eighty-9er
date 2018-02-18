
//-------------------------------------------------------
void wifiSetup() {
  wifiHamlib = true;
  boolean MgrPassed = false;
  if (both_pads(F("net"))) {
      wifiMgr();
      MgrPassed = true; 
     }
  
 if (! MgrPassed) { 
 Serial.println(F("loca")); //shows loc at 7seg display
 wifi_off();
// wifi_set_phy_mode(PHY_MODE_11B);
 WiFi.mode(WIFI_AP);
 delay(1000);  
 WiFi.softAPConfig(ipAP,ipAPgw,ipAPmask);
 WiFi.softAP(localAP,"",11);
 delay(500); 
 #ifdef DEBUG
 Serial.println();
 Serial.println(F("Local AP UP"));
 Serial.println(WiFi.softAPIP());
 WiFi.softAPmacAddress(mac);
 printMac();
 #endif
 } else {
   #ifdef DEBUG
   Serial.println(F("WiFi Mgr passed"));
   #endif
 }
 #ifdef DEBUG
 WiFi.printDiag(Serial); 
 #endif
 //rigctld emualtion tcp start  
  server.begin();
  server.setNoDelay(true);
  delay(5);
  #ifdef DEBUG
  Serial.println(F("Telnet server started"));
  #endif
}
//-------------------------------------------------------
void wifiMgr() {
   //Local intialization. Once its business is done, there is no need to keep it around
      wifi_station_set_hostname(HOST);
     WiFiManager wifiManager;

    //sets timeout until configuration portal gets turned off
    //useful to make it all retry or go to sleep
    //in seconds
    wifiManager.setConfigPortalTimeout(180);
    //it starts an access point with the specified name
    //here  "AutoConnectAP"
    //and goes into a blocking loop awaiting configuration

    //WITHOUT THIS THE AP DOES NOT SEEM TO WORK PROPERLY WITH SDK 1.5 , update to at least 1.5.1
    //WiFi.mode(WIFI_STA);
    
     if (!wifiManager.startConfigPortal(HOST)) {
       delay(2000);
      //reset and try again, or maybe put it to deep sleep
      //reset settings - for testing
      wifiManager.resetSettings(); 
      ESP.eraseConfig();
      delay(1000);
      ESP.reset();
      delay(1000);
      }
    //if you get here you have connected to the WiFi 
         
  } //Configuration portal end

//-----------------------------------------------------------
void wifi_off() {   //kills hamlib emulation and cuts down woodpecker
  
   //WiFi.persistent(false);
   WiFi.disconnect();
   delay(1000); 
   //WiFi.persistent(true);
   WiFi.mode(WIFI_OFF);
   #ifdef DEBUG
   Serial.println(F("WIFI_OFF"));
   #endif
   delay(1000);
}
//-----------------------------------------------------------
void wifi_output(float a) {  //range 20.5 -- 0 dBm
   WiFi.setOutputPower(a);
   #ifdef DEBUG
   Serial.print(F("WIFI_output "));Serial.print(a);Serial.println(F(" dBm"));
   #endif
}
//-------------------------------------------------------
void showWiFi(int stat) {
  #ifdef DEBUG
  switch (stat) {
    case   0: Serial.println (F("WL_IDLE_STATUS")); break;
    case   1: Serial.println (F("WL_NO_SSID_AVAIL")); break;
    case   2: Serial.println (F("WL_SCAN_COMPLETED")); break;
    case   3: Serial.println (F("WL_CONNECTED")); break;
    case   4: Serial.println (F("WL_CONNECT_FAILED")); break;
    case   5: Serial.println (F("WL_CONNECTION_LOST")); break;
    case   6: Serial.println (F("WL_DISCONNECTED")); break;
    case 255: Serial.println (F("WL_NO_SHIELD")); break;
  }
  #endif
}
//-----------------------------------------------------------
void printMac() {
  #ifdef DEBUG
  Serial.print(mac[0],HEX);
  Serial.print(F(":"));
  Serial.print(mac[1],HEX);
  Serial.print(F(":"));
  Serial.print(mac[2],HEX);
  Serial.print(F(":"));
  Serial.print(mac[3],HEX);
  Serial.print(F(":"));
  Serial.print(mac[4],HEX);
  Serial.print(F(":"));
  Serial.println(mac[5],HEX);
  #endif
} 
//-------------------------------------------------------
