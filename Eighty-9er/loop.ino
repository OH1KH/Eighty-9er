
//------------------------------------------------------- 
void loop() {
  
#if !defined DEBUG  
 if ((ShowBase < millis()) && (CWkey == 0)){
  ShowBase = millis()+upd7seg;
  showNumberDec(MyQrg/1000);
 }
#endif

iambic();
if ( (CWkey == 1) && (millis()>CWkeyed) ) { keying_set(0);} // remove rit 
RotSteps();
RotKnob();
if ( wifiHamlib) {
    serveTCP();//check connects and disconnects
    readCli();
    } 
if ( serialHamlib) {    
    readSer();   
    }
delay(10);
}
//-------------------------------------------------------
