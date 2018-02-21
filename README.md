# Eighty-9er
80m CW QRP tranceiver with ESP12e and AD9850 DDS


###### Forty-9er  -->  Eighty-9er : Modification to 80m with DDS vfo

English text follows at the end of this file.

-----------------------------------------------------------------------

Forty-9er on suhteelisen helppo modifioida 40m versiosta 80m versioon. Jos sattuu löytämään kaksi kidettä, vaikkapa 3.560MHz niin vaihtamalla ne, ja sen lisäksi kelojen L3 ja L4 kerrosmäärät sekä kelan L4 molemmilla puolilla olevat kondensaattorit homma on valmis.

Jos sen sijaan havittelee hieman laajempaa taajuusaluetta pitää kiteiden tilalle saada vfo ja vastaanottosuotimeksi LC-piiri.

Fortyn modifiointi 40m DDS versioksi löytyy QST 3/16 artikkeli W8TEE, K2ZIA ja W6DQ laatimana. Tätä soveltaen, ja miljoonalaatikon antia käyttäen, suunnittelin 80m modifikaationi.

#### Aloitetaan antennipiiristä.
Vastaanotossa alkuperäinen versio käyttää kidettä vastaanottosuotimena. Jos halutaan laajempi taajuusalue on kide korvattava jollain. Yksi tapa voisi olla kiteen vaihto keraamiseen resonaattoriin, mutta helpommin miljoonalaatikosta löytyy kondensaattoreita ja keloja.

Piirilevylle, kiteen paikalle, kannattaa juottaa kanta johon uuden bandisuotimen voi asettaa erillisellä pienellä printillä.
Lisäksi se mahdollistaa erillaisten variaatioiden kokeilun, jos intoa riittää. Minulla se loppui heti kun sain ensimmäisen toimivan version tehtyä. Kytkentäkaavasta selviää rakenne, joka on siis kaksi 150pF kondensaattoria (DC erotus) joiden välissä on rinnakkaisresonassipiiri.

Piirin kela on kierretty samalaiselle ferrriittirungolle kuin Fortyn L3. Ulkoiset mitat ovat samat ja väri on sama joten luulen sen olevan FT37-43. MUtta miljoonalaatikon osista ei voi olla ihan varma.
Kierroksia on 16. Kondesnsaattorilla (useammalla jotka on rinnankytennässä) 125pF sain resonanssin kutakuinkin 3.560MHz.
Suosittelen kuitenkin noin 80pF kiinteää kondensaattoria jonka rinnalla on 10-60pF tirmmeri. Siten viritys tulee huomattavasti nopeammaksi ja helpommaksi. Jos mittalaitteita ei ole säädetää trimeriä vain niin että vastaanotin on herkimmillään noin 3.560MHz kohdalla.

Lähetinpuolella ferrittirungot käämitään eri kierroksilla. Päätetransitorin kollektorilla oleva L3 saa 17 kierrosta ja antennipiirin sarjakela L4 24kkierrosta. Kondensaattorit L4 molemmin puolin (470pF) muutetaan molemmat 1nF suuruisiksi.

Nyt on helmpommat hommat tehty.

DDS-moduli on AD9850. Sitä ohjaamaan laitoin ESP24e WiFi mikrokontrollerin. Sillä saadaan monenlaisia toimintoja mutta siinä on hieman liian vähän i/o-linjoja kaikkien herkkujen toteuttamiseen.
Alkuperäisenä ajatuksena oli että rigiä ohjattaisiin tabletilla, läppärillä tai kännykällä. Kuitenkin projektin edetessä tuli selväksi että VFO-nuppi pitää olla. Samoin paikallinen näyttö jotta käyttö ilman tietureitakin onnistuisi.
 
#### DDS-modulin liittäminen.
Kun datalinjat on kytketty alkaa analgipuolen kytkentä (lue: vaikemapi kytkentä). Modulin ulostulojännite on Fortyä varten liian alhainen joten tarvitaan vahvistinaste.
QST:n artikkelin mukainen 2 transistorinen kytkentä voidaan kopioida suoraan. Jos alkuperäinen kideoskillaattori jätetään kalustamatta voi kyseisiä piirilevyn johteita ja luovaa mielikuvitusta käyttäen rakentaa tuon vahvistimen samaan tilaan kuin oskillaattori oli rakennettu.
Rakentamisessa ei ole mitään sen kummempaa, mutta trimmeripotikka on todella tarpeellinen. 

#### Varoituksen sanat
Fortyn lähetin on suunniteltu, netistä löytämääni (alkuperäistä??) kytkentää muuttaen niin että ohjainasteen Q6 emitteriltä on jätetty vastus ja sen RF-ohituskondensaattori pois.
Se johtaa siihen että jos transistori ei saa yhtään ohjausta transistori paistaa itsensä.
Tästä varoitetaan, jokseenkin epäselvästi joka selkisi myöhemmin, alkuperäisessä ohjeessa jossa sanotaa että kidettä ei saa koskea kun lähetys on päällä (johtaa oskillaattorin pysähtymiseen).

Omaan versiooni laitoin 100ohm emitterivastuksen ja sen rinnalle 0.1 mikron kondensaattorin. Näin transistori kestää jonkin aikaa ilman ohjaustakin. Ja kun tulevalle sigaalille on etuvahvistin saadaan kuitenkin riittävä teho päätetransistorille.

Toinen varoitus liittyykin tähän vahvistuksen säätöön trimmerillä. Vahvistimesta saa nimittäin niin ison signaaline että se ohjainasteen jälkeen pystyy polttamaan päätetransistorin. Itselleni sääsin ulostulotehoksi 2W joka riittää kyllä kotimaan qsoihin.

Kolmas ongelma voi olla sarjassa oleva L1 100mH kela audiopuolella. Ensimmäisessä Fortyssäni tämä kela oli jo valmiiksi poikki. Sen sai kyllä korjattua mikroskoopilla ja kolvilla.
Tässä toisessa, modatussa versiossa, siinä tuntuu olevan lämpövika. Eli jos kotelo suljetaan niin jonkin ajan kuluttua ääni loppuu. Se palautuu kun kelaan ruiskuttaa kylmäspraytä, joten se menee vaihtoon.

#### Paikallinen näyttö
Koska ESP:issä on niin vähän i/o-linjoja, ja koska miljoonalaatikosta kaivetussa kotelossa oli valmiiksi 25-napaisen canon-liittimen reikä, piti näytön suhteen keksiä jotain.
Reikään sopi 0.28" neljän numeron 7segmenttinen ledinäyttö. Niitä on irrallisena, sekä myös ohjainpiirillä TM1637 varustettuna. Ohjainpiirissä on vainse vika että se tarvitsee sekä kellon, että datan. Kaksi nastaa ESP:istä on aivan liikaa.
Siksi tein ohjaimen juottamalla näytön taakse 90asteen kulmaan Arduino Nanon. Näiden lisäksi tarvittiin vain 7 vastusta ja 4 npn transistoria. Ja tietty ohjelma, joka oli se helpoin työvaihe.
Tämä naytto toimii Nanon RX-datan kautta . Vain yksi pinni. 115200baudin vauhdilla. RX-data voidaan kytkeä suoraan ESP:in TXdataan ja pitää se kiinni myös ESP:in ohjelmointien aikana. Siis paras ratkaisu.
 
#### Audio
Fortyn audioulostulo on tehty kuulokkeita varten, ja niilläkin signaali on melko vaimea. Siksi lisävahvistin on tarpeen kaiutinvoimakkuuden saavuttamiseksi. Vahvistin on TDA7052 peruskytkentä ja sillä saadaan tarvittava audiovoimakkuus.


#### Osat
Kaikki tarvittavat komponentit Forty, DDS, ESP,Arduino Nano, 7seg-näyttö, TDA7052, rotary encoder(vfo) ja lisäksi 100kpl ohjaintarnsistoreja SS8050 sekä 10kpl päätetransistoreja 2SD882 (edellä varoitetuista syistä) on tilattu ebay.com:sta. Ne ovat hyvin edullisia ja kannattaa tilata muutamia kerrallaan kun postituskin sisältyy hintaan. Haittapuoli on 3-4 viikon toimitusaika jonka johdosta useampi kappale auttaa asiaa jos savu sattuu nousemaan. 


#### Ohjelman ominaisuudet pääpiirteissään

	- Taajuusalue 3.5 - 3.7Mhz (helposti muutettavissa)
	- VFOa painamalla askellus muuttuu 10->100->1000->(rx rit asetus)10Hz->jne...
	- RX 700Hz lähetystä ylempänä (rx rit, oletus helposti muutettavissa)
	  Näyttö näyttää aina lähetystaajuutta.
	- 7seg näyttö näyttää alkuvalinnat, taajuuden, vfo:n askelluksen, CW nopeuden
	- Hamlib rigctld emulointi. Liittyvän ohjelman asetuksissä käytä rigiä -m 2
	  Liityntä joko sarjaportin kautta (vaatii erillisen USB/ttl muuntimen) tai WiFin kautta.
	- WiFi tulee liittymistä olemassa olevaan langattomaan verkkoon tai oma riippumattoman
	  verkon luontia (oma dhcp).
	- iambic keyer (5 - 50wpm)

#### Käynnistys

Näytöllä vilkkuu erillaisia tekstejä. Valinnat tehdään liitetyllä avainnusoasalla (2-vartinen). Myöntävä vastaus on kun molemmat padit painetaan pohjaan. Kieltävässä ei tehdä mitään, vain odotetaan seuraavaa kysymystä.
Poikkeuksena on avainnuksen pisteen ja viivan paikan vaihto. Siihen vastataan painamalla se padi pohjaan josta halutaan pisteet. Tämä tallettuu eepromille yhdessä viimeksi käyteyn CW-nopeuden kanssa joten niitä ei tarvitse jokaisessa käynnistyksessä määrittää.
```
    "F On" (käynnistetäänko WiFi?)
     |n  |y
     |   ------" net" (liitytäänkö olemassa oleaan verkkoon?)		
     |		|n  |y
     |		|   --------------------Käynnistää avoimen WiFi verkon "Eighty-9er"
     |		|                       jossa Wifi manager osoittessa 192.168.4.1 (selaimella auki)
     |		|                       Aplikaation kautta yhdistetään olemass olevaan verkkoon.
     |		| 
     |	    Käynnistää oman WiFi verkon "Local80"
     |	    johon voidaan liittyä ja käyttää
     |      rigctld:tä (tcp) osoitteessa
     |      192.168.4.1:4532
     |		|  
     |		|  
  "s hl"        | (käytetäänkö rigctld:tä sarjaliitynnän kautta?)
     |		|   
     |----------- 
  "dit-"  (paina sitä padia josta haluat pisteet. Tallettuu eepromille ei joka kerta tarvitse painaa)
     |
     |
  "3560"  (käyttö alkaa. Oletustaajuus 3.560Mhz)
```
#### Käyttö

Kun VFO nuppia kierretään näytössä näkyy "3560"-> "3561" tai "3559" jne... Jos askellus on 1000Hz.

Oletusaskellus on 100Hz, jolloin näyttöön vaihtuu "5600" -> "5601" tai "5599" jne... riippuen miten paljon
nuppia kierretään. Näytöstä poistuu siis ylin "3" eli MHz säädön ajaksi. Kun säätö lopetetaan palautuu taas neljä eniten merkitsevää numeroa.

Jos askellus on 10Hz putoaa 2 ylintä numero pois säädön ajaksi. Siis "6000" -> "6001 tai "5999" jne...

Askellusta muutetaan VFO nuppia painamalla. Rotary encoderissa toimii sulkukosketin painettaessa sisään.
Askellus muuttuu oletuksesta 100Hz, näytössä: -> 1000 -> rit säätö jolloin näkyy oletusarvo 700 (jota käytetään vain jos eeprmin arvo on rajojen ulkopuolella) joka on muutettavissa nuppia kiertämällä 10 portain alueella -9000 .. +9000Hz. Kun säätöä ei tehdä 2 sekuntiin tulee näytölle 10, joka tarkoittaa että VFO askellus asettui samalla kertaa 10Hz. Jos rit arvo muuttui se tallennetaan eepromille ja luetaan sieltä käynnistyksessä.

Jälleen seuraava painallus tuo näyttöön/askeleeksi 100. Tästä eteenpäin kierretään samaa 1000->rit/10->100 jne...

Lähetyksen aikana näyttöön tulee käytetty automaattiavaimen nopeus wpm:nä. Oletus on 18 (helposti muutettavissa). Kun palataan lähetyksetä kuunteluun näkyy ensin taajuuden vähiten merkitsevät numerot (jos askellus alle 1000) ja hetken kuluttua ne vaihtuvat eniten merkitseviin.

Käytettäessä pumppuavainta näyttö pysyy taajuuden perusnäytöllä koko ajan.

Rigctld komennoista toimivat:
	b text		lähetä sähkötyksellä "text"
        l		näytä CW nopeus
	L KEYSPD xx	aseta CW nopeus xx WPM (5 - 50 wpm)
	t		näytä lähettimen tila (1 / 0)
	T		aseta lähetin päälle pois (1/0)
	f		näytä taajuus (Hz)
	F xxxxxxx	aseta taajuus (Hz 3500000 - 3700000)
	j		näytä RX rit (Hz)
	J xxxxx		aseta RX rit (-9000 - 9000. Arvoa 0 ei voi käyttää. Käytä 1 sen sijaan)
	m		näytä mode (aina CW )
	M yy		aseta mode (vain CW kelpaa)
	v		naytä VFO (aina VFOA)
	V		asta VFO ( vain currVFO, VFO ja VFOA kelpaavat)
	q		katkaise yhteys (TCP)
	Q		katkaise yhteys (TCP)

Vastaavat komennot toimivat myös rigcltd pitkällä muodolla lukuunottamatta komentoja b,q ja Q
Siis f = "get_freq", F = "set_freq" jne... Katso rigctld man-sivut.

Vain pitkissä komennoissa toimivat "dump_caps" ja "dump_state", mutta ne ovat enemmän tai vähemmän "sinne päin". Niitä tarvitaan kun ohjelmat tai toinen rigcld liittyy tähän rigcltd:hen.

Rigctld kuulumattomia komentoja ovat:

	Z		katkaise WiFi (HUOM! yhteys menetetään !)
	H		aseta WiFin maksimiteho (saattaa kuulua "tikkana" bandilla)
	P		aseta WiFin minimiteho. Oletus on maksimi, jos "tikka" haittaa voi tällä pudottaa tehoa.





-----------------------------------------------------------------------------------------------------------

## Same in English 
###### (nearly.. . hope so...)





Translation based on translate.google.com  (fixed manually. You have been warned...).


Forty-9er is relatively easy to modify from 40m to 80m version. If you find two crystals, say 3.560MHz, by changing them, and in addition, the coefficients of coils L3 and L4 and the capacitors on both sides of coil L4 you are ready.

If, instead, you require a slightly larger frequency range you need crystals replaced by a vfo and a receive filter LC circuit.

Forty's modification to 40m DDS can be found in QST 3/16 article by W8TEE, K2ZIA and W6DQ. Using this and  my junkbox I designed this 80m modification.

#### Let's start with the antenna circuits.
At reception side, the original version uses the crystal as a reception filter. If you want broader frequency range the crystal must be replaced by something. One way could be to replace the crystal with a ceramic resonator, but more easily with capacitors and coil from the junkbox.


At the circuit board, where the RX filter crystal is placed, it is best to solder a socket on which the new band filter can be set with a separate small print.
It allows experiments of different variations if there is enough enthusiasm. I ended testing as soon as I got my first running version done. The circuit diagram illustrates the structure, which has two 150pF capacitors (DC separation) with a parallel resonance circuit.

The circuit coil is twisted to the same kind of ferrite body as the Forty's L3. The outer dimensions are the same and the color is the same so I think it is FT37-43. You can not be sure of that because it was found from my junkbox, sorry.
There are 16 rounds. With a condensator (more than one in parallel) of 125pF I got a resonance about 3.560MHz.
However, I recommend about 80pF solid capacitor along with 10-60pF trimmer one. Thus tuning becomes much faster and easier. If there are no measuring devices adjust the trimmer just so that the receiver is most sensitive around 3.560MHz.

On the transmitter side, the ferrite rings are wound with different rounds. The L3 at the final transistor collector has 17 turns and the antenna circuit L4 has 24 rounds. The capacitors at L4 both sides (470pF) are both changed to 1nF.

Now the easiest modifications are done.

The DDS module is AD9850.It is driven by ESP24e WiFi microcontroller. It provides a wide range of functions but has a bit too little amount of i/o lines to make all bells and whistles.
The original idea was to control the rig with a tablet, laptop or cell phone. However, as the project progressed, it became clear that the VFO knob must exist. Likewise, a local display to be used when in standalone installation would be nice.
 
#### Connecting a DDS Module.

When the data lines are connected to ESP starts the harder part of connection (the analog work). The DDS module's output voltage is too low for Forty, so an amplifier is required.
Two transistor coupling according to the QST article can be used here directly. If the original crystal oscillator components are not installed, the circuit board holes and stripes can be used with creative imagination to build that amplifier in the same place as the oscillator was originally placed.
There is nothing special with construction, but a trimmer poti is really necessary.

#### Words of warning
The Forty's Transmitter is designed a bit differently as the (original) circuit that I found from web.The resistance of the Q6 emitter at the driver stage and it's RF bypass capacitor is excluded.
It will result situation where the transistor burns itself with DC current if there exist no RF feed.
This is warned, somewhat unclearly, in the original instructions that says the crystal should not be touched when the transmission is on (may lead to an oscillator stop and RF disppear).

In my version I used 100ohm emitter resistor with a 0.1 microfarad capacitor in parallel. Thus, the transistor will survive now some time even without RF feed. And now when there is a pre-amplifier for the sigal, enough power for the driver transistor is achieved even when the 100 ohms emitter resistance with capacitor will drop gain a bit.

Another warning relates to this gain adjustment with a trimmer. The amplifier can make signal so large that it can burn the final transistor. For myself output is adjusted to 2W, which is enough for qsos.

The third problem may be  L1 100mH coil on the audio side. In my First Forty the coil was already broken when received. I repaired it with a microscope and soldering iron.
In this second, modified version, it seems to have a thermal fault. That is, if the enclosure is closed for a while, the sound will end. It comes back when the coil is sprayed with cold spray, so it have to be changed.

#### Local display

Because there are so few I/O lines in the ESP, and since my case for this project, found from junkbox, had a ready hole for a 25-pole canon connector, I had to find suitable display using these properties.
The size of 0.28" 4-digit 7-segment LED display was suitable.It can be controlled with TM1637. Problem is that circuit needs both clock and data (2 pins).It is too much thinking about ESP pins.
That's why I made the controller by installing Arduino Nano to 90 degree angle to back side of the display. In addition  only 7 resistors and 4 npn transistors were needed. And of course the program, which was the easiest work to do :).
This module works now using only Nano's RX data. Only one pin. At 115200baud's speed. The RX data line can be directly connected to the TX data of the ESP and can be connected also while ESP programming. So the best solution.
 
#### Audio

Forty's audio output is made for headphones, and even then signal is pretty small. Therefore, an additional amplifier is needed to achieve loudspeaker volume. The amplifier is a TDA7052 in basic connection and provides the required audio volume.


#### Assemblies
All the necessary components for Forty, DDS, ESP, Arduino Nano, 7seg display, TDA7052, rotary encoder (vfo) and additionally 100pcs of driver SS8050 and 10pcs of final transistors 2SD882 (for the reasons cleared in warnings section) have been ordered from ebay.com. They are very inexpensive and it is worth to order a few at a time when mailing is included in the price. The disadvantage is the delivery time of 3-4 weeks, which means that more than one piece will help if the smoke appears when testing.


#### Main features of the program

	- Frequency range 3.5 - 3.7Mhz (easy to change)	
	- Press VFO knob to change vfo step 10Hz -> 100Hz -> 1000Hz -> (rx rit setting) 10Hz-> etc ...
	- rx rit 700Hz  (rx rit, default can be easily changed)
	  The display always shows the transmission frequency.
	- 7seg display shows start options, frequency, vfo step, CW speed
	- Hamlib rigctld emulation. In the related program settings, use rig model -m 2
	  Connects either via a serial port (requires a separate USB / ttl converter) or via WiFi.
	- WiFi can be connected to an existing wireless network or creates own independent network (my dhcp).
	- iambic keyer (5 - 50wpm)

#### Starting rig

Different texts will flash on the screen. Options are selected with the attached keyer (2-pole). The  answer is "yes" when both pads are pressed down. "No" is just  doing nothing untill the next question.
An exception is the swapping of paddles dit and dah. It is answer is done by pressing the pad that you want to use for dits. This is stored in eeprom together with the latest CW speed so they do not need to be set at each startup.
```
    "F On" (is WiFi being started)
     | n | y
     |   ------ "net" (does it link to exist on the network?)
     |   | n | y
     |   |   -------------------- Launches Open WiFi Network "Eighty-9er"
     |   |                        where the Wifi manager at 192.168.4.1 (with the browser open)
     |   |                        Through application, you connect to a network that exists.
     |   |
     |   Launch your own WiFi network "Local80"
     |   which can be associated and used
     |   rigctld (tcp) at
     |   192.168.4.1:4532
     |   |
     |   |
  "s hl" | (do I use rigctld via serial interface?)
     |   |
     |----
  "-dit"(press the one you want to score from. The deposit to eeprom does not have to be pressed every time)
     |
     |
  "3560" (usage starts, Default frequency 3.560Mhz)
```

#### Usage

When the VFO knob is rotated, the display shows "3560" -> "3561" or "3559" etc ... If the step is 1000Hz.
The default step is 100Hz, which changes display to "5600" -> "5601" or "5599" etc ... depending on how much
the knob is rotated. The screen will hide the highest "3" of MHz.
When the adjustment is stopped, the four most significant digits are returned.

If the step is 10Hz, two higes numbers are dropped out during adjustment. So display shows, "6000" -> "6001 or" 5999 "etc ...

Press the VFO knob to change the step. The rotary encoder has closing contact when pressed.
The step changes from the default to 100Hz, in the display: -> 1000 -> rit value to display. The default value is 700 (that occurs only if eeprom read fails) which can be changed by rotating knob. The range is -9000 .. + 9000Hz with steps of 10. When no adjustment is made for 2 seconds, the display will show 10, which means that the VFO's step was set at 10Hz at the same go. If rit changed new value is written to eeprom and read from there at next startup.

The next press will give the step and display of 100. From here on, the same 1000-> rit / 10-> 100 etc will be rotated ...

During transmission, the iambic key speed will be displayed as wpm. The default is 18 (easily changeable). When returning to RX, the least significant numbers of the frequency (if a step is below 1000) are displayed first, and in a few moments they will change the most significant.

When using the stright key, the display stays on the basic frequency display all the time.

Rigctld commands that works are:
	b text 		send CW "text"
        l 		show the CW speed
	L KEYSPD xx 	set CW speed xx WPM (5 to 50 wpm)
	t 		show transmitter status (1/0)
	T 		turn the transmitter on and off (1/0)
	f 		display frequency (Hz)
	F xxxxxxx 	set the frequency (Hz 3500000 to 3700000)
	j 		show RX rit (Hz)
	J xxxxx 	set RX rit (-9000 to 9000. Value 0 is invalid. Use 1 instead)
	m 		show mode (always CW)
	M yy 		set mode (only CW valid)
	v 		show VFO (always VFOA)
	V yyyy		set VFO (only currVFO, VFO and VFOA accepted)
	q 		disconnect (TCP)
	Q 		disconnect (TCP)

The corresponding commands also work in rigcltd's long form except the commands b, q, and q
So f = "get_freq", F = "set_freq" etc ... See rigctld man pages.

Only long commands are "dump_caps" and "dump_state", but they are more or less "from there". They are only needed when programs or another rigcld are associated with this rigcltd.


Not rigctld commands are:

	Z 		cut off WiFi (note!! the connection is lost!)
	H 		set WiFi maximum power (may be cause a "woodpecker" to band)
	P 		set WiF minimum power. The default is the maximum pwr. if a "woodpecker" exist dropping power may help.





