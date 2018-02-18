
//-------------------------------------------------------
void dump_caps() {
  //this is a fake for clients like wsjt-x and fldigi who wants to see what the rig is capable of

strcpy(TXbuf,"\
Caps dump for model: 201\n\
Model name:	TS-50S\n\
Mfg name:	Kenwood\n\
Backend version:	0.9\n\
Backend copyright:	LGPL\n\
Backend status:	Untested\n\
Rig type:	Mobile\n\
PTT type:	Rig capable\n");

writeCli();

strcpy(TXbuf,"\
DCD type:	Rig capable\n\
Port type:	RS-232\n\
Serial speed: 4800..4800 bauds, 8N2 \n\
Write delay: 20ms, timeout 2500ms, 10 retry\n\
Post Write delay: 30ms\n\
Has targetable VFO: Y\n\
Has transceive: Y\n");

writeCli();

strcpy(TXbuf,"\
Announce: 0x0\n\
Max RIT: -0.0kHz/+0.0kHz\n\
Max XIT: -0.0kHz/+0.0kHz\n\
Max IF-SHIFT: -0.0kHz/+0.0kHz\n\
Preamp: None\n\
Attenuator: None\n\
CTCSS: None\n\
DCS: None\n\
Get functions: \n\
Set functions: \n");

writeCli();

strcpy(TXbuf,"\
Get level: ATT(0..0/0) AF(0..0/0) RF(0..0/0) SQL(0..0/0) RFPOWER(0..0/0) MICGAIN(0..0/0) AGC(0..0/0) STRENGTH(0..0/0) \n\
Set level: ATT(0..0/0) AF(0..0/0) RF(0..0/0) SQL(0..0/0) RFPOWER(0..0/0) MICGAIN(0..0/0) AGC(0..0/0) \n");

writeCli();

strcpy(TXbuf,"\
Extra levels:\n\
Get parameters: \n\
Set parameters: \n\
Extra parameters:\n\
Mode list: CW \n\
VFO list: VFOA \n\
VFO Ops: UP DOWN \n\
Scan Ops: \n\
Number of banks:	0\n");

writeCli();

strcpy(TXbuf,"\
Memory name desc size:	0\n\
Memories:\n\
	0..0:   	MEM\n\
	  Mem caps: \n\
	0..0:   	EDGE\n\
	  Mem caps: \n\
TX ranges status, region 1:	OK (0)\n\
RX ranges status, region 1:	OK (0)\n");

writeCli();

strcpy(TXbuf,"\
TX ranges status, region 2:	OK (0)\n\
RX ranges status, region 2:	OK (0)\n\
Tuning steps:\n\
	10 Hz:   	CW \n\
	100 Hz:   	CW \n\
	1 kHz:   CW \n\
	ANY:   	CW \n\
Tuning steps status:	OK (0)\n");

writeCli();

strcpy(TXbuf,"\
Filters:\n\
	2.2 kHz:   	CW \n\
Bandwidths:\n\
	CW	Normal: 2.2 kHz,	Narrow: 0 Hz,	Wide: 0 Hz\n\
Has priv data:	Y\n\
Has Init:	N\n\
Has Cleanup:	N\n\
Has Open:	N\n\
Has Close:	N\n");

writeCli();

strcpy(TXbuf,"\
Can set Conf:	N\n\
Can get Conf:	N\n\
Can set Frequency:	Y\n\
Can get Frequency:	Y\n\
Can set Mode:	Y\n\
Can get Mode:	Y\n\
Can set VFO:	Y\n\
Can get VFO:	Y\n\
Can set PTT:	Y\n\
Can get PTT:	Y\n");

writeCli();

strcpy(TXbuf,"\
Can get DCD:	N\n\
Can set Repeater Duplex:	N\n\
Can get Repeater Duplex:	N\n\
Can set Repeater Offset:	N\n\
Can get Repeater Offset:	N\n\
Can set Split Freq:	N\n\
Can get Split Freq:	N\n\
Can set Split Mode:	N\n\
Can get Split Mode:	N\n\
Can set Split VFO:	N\n");

writeCli();

strcpy(TXbuf,"\
Can get Split VFO:	N\n\
Can set Tuning Step:	N\n\
Can get Tuning Step:	N\n\
Can set RIT:	N\n\
Can get RIT:	N\n\
Can set XIT:	N\n\
Can get XIT:	N\n");

writeCli();

strcpy(TXbuf,"\
Can set CTCSS:	N\n\
Can get CTCSS:	N\n\
Can set DCS:	N\n\
Can get DCS:	N\n\
Can set CTCSS Squelch:	N\n\
Can get CTCSS Squelch:	N\n\
Can set DCS Squelch:	N\n");

writeCli();

strcpy(TXbuf,"\
Can get DCS Squelch:	N\n\
Can set Power Stat:	N\n\
Can get Power Stat:	N\n\
Can Reset:	N\n\
Can get Ant:	N\n\
Can set Ant:	N\n\
Can set Transceive:	Y\n\
Can get Transceive:	Y\n\
Can set Func:	Y\n\
Can get Func:	Y\n\
Can set Level:	Y\n");

writeCli();

strcpy(TXbuf,"\
Can get Level:	Y\n\
Can set Param:	N\n\
Can get Param:	N\n\
Can send DTMF:	N\n\
Can recv DTMF:	N\n\
Can send Morse:	N\n\
Can decode Events:	N\n\
Can set Bank:	N\n\
Can set Mem:	N\n\
Can get Mem:	N\n");

writeCli();

strcpy(TXbuf,"\
Can set Channel:	N\n\
Can get Channel:	N\n\
Can ctl Mem/VFO:	N\n\
Can Scan:	N\n\
Can get Info:	N\n\
Can get power2mW:	N\n\
Can get mW2power:	N\n\
\n\
Overall backend warnings: 0\n\
RPRT 0\n");

writeCli();

}

//-------------------------------------------------------



