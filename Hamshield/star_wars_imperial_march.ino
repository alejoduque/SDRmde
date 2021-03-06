/* Hamshield
 *   The Imperial March beacon SDR MDE
 *   http://www.instructables.com/id/How-to-easily-play-music-with-buzzer-on-arduino-Th/?ALLSTEPS
*/

#include <HamShield.h>

#define PWM_PIN 3
#define RESET_PIN A3
#define SWITCH_PIN 2

#define  C0 16.35
#define Db0 17.32
#define D0  18.35
#define Eb0 19.45
#define E0  20.60
#define F0  21.83
#define Gb0 23.12
#define G0  24.50
#define Ab0 25.96
#define LA0 27.50
#define Bb0 29.14
#define B0  30.87
#define C1  32.70
#define Db1 34.65
#define D1  36.71
#define Eb1 38.89
#define E1  41.20
#define F1  43.65
#define Gb1 46.25
#define G1  49.00
#define Ab1 51.91
#define LA1 55.00
#define Bb1 58.27
#define B1  61.74
#define C2  65.41
#define Db2 69.30
#define D2  73.42
#define Eb2 77.78
#define E2  82.41
#define F2  87.31
#define Gb2 92.50
#define G2  98.00
#define Ab2 103.83
#define LA2 110.00
#define Bb2 116.54
#define B2  123.47
#define C3  130.81
#define Db3 138.59
#define D3  146.83
#define Eb3 155.56
#define E3  164.81
#define F3  174.61
#define Gb3 185.00
#define G3  196.00
#define Ab3 207.65
#define LA3 220.00
#define Bb3 233.08
#define B3  246.94
#define C4  261.63
#define Db4 277.18
#define D4  293.66
#define Eb4 311.13
#define E4  329.63
#define F4  349.23
#define Gb4 369.99
#define G4  392.00
#define Ab4 415.30
#define LA4 440.00
#define Bb4 466.16
#define B4  493.88
#define C5  523.25
#define Db5 554.37
#define D5  587.33
#define Eb5 622.25
#define E5  659.26
#define F5  698.46
#define Gb5 739.99
#define G5  783.99
#define Ab5 830.61
#define LA5 880.00
#define Bb5 932.33
#define B5  987.77
#define C6  1046.50
#define Db6 1108.73
#define D6  1174.66
#define Eb6 1244.51
#define E6  1318.51
#define F6  1396.91
#define Gb6 1479.98
#define G6  1567.98
#define Ab6 1661.22
#define LA6 1760.00
#define Bb6 1864.66
#define B6  1975.53
#define C7  2093.00
#define Db7 2217.46
#define D7  2349.32
#define Eb7 2489.02
#define E7  2637.02
#define F7  2793.83
#define Gb7 2959.96
#define G7  3135.96
#define Ab7 3322.44
#define LA7 3520.01
#define Bb7 3729.31
#define B7  3951.07
#define C8  4186.01
#define Db8 4434.92
#define D8  4698.64
#define Eb8 4978.03
// DURATION OF THE NOTES 
#define BPM 180    //  you can change this value changing all the others 120
#define H 2*Q //half 2/4
#define Q 60000/BPM //quarter 1/4 
#define E Q/2   //eighth 1/8
#define S Q/4 // sixteenth 1/16
#define W 4*Q // whole 4/4


HamShield radio;

void setup() {
  // NOTE: if not using PWM out, it should be held low to avoid tx noise
  pinMode(PWM_PIN, OUTPUT);
  digitalWrite(PWM_PIN, LOW);

  // prep the switch
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  // set up the reset control pin
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, HIGH);

  Serial.begin(9600);
  Serial.println("If the sketch freezes at radio status, there is something wrong with power or the shield");
  Serial.print("Radio status: ");
  int result = radio.testConnection();
  Serial.println(result, DEC);
  Serial.println("Setting radio to its defaults..");

  radio.initialize();
  radio.setRfPower(0);
  radio.setDTMFC0(697);
  radio.setDTMFC1(770);
  radio.setDTMFC2(852);
  radio.setDTMFC3(941);
  radio.setDTMFC4(1209);
  radio.setDTMFC5(1336);
  radio.setDTMFC6(1477);
  radio.setDTMFC7(1633);
  radio.setCtcss(131.8);
  radio.setCtcssSel(true);
  radio.setOuterCtcssMode();
}

void loop() {
   // We'll wait up to 10 seconds for a clear channel, requiring that the channel is clear for 2 seconds before we transmit, RSSI value of TX busy
   Serial.print("ocupado ? ");
  if (radio.waitForChannel(1000,2000, -90)) {
    // If we get here, the channel is clear. Let's print the RSSI to the serial port as well.
    Serial.print("Signal is clear, RSSI: ");
    Serial.println(radio.readRSSI());
    
    // Start transmitting by putting the radio into transmit mode.
  Serial.print("Transmitting... ");
  Serial.println("We will now tune to 145.670 and send star wars beacon");
  radio.frequency(145670);
  radio.setModeTransmit();  
  delay(300);
  radio.morseOut("  SDR MDE");
  delay(300);
    delay(2*H);
    tone(PWM_PIN,LA3,Q); 
    delay(1+Q); //delay duration should always be 1 ms more than the note in order to separate them.
    tone(PWM_PIN,LA3,Q);
    delay(1+Q);
    tone(PWM_PIN,LA3,Q);
    delay(1+Q);
    tone(PWM_PIN,F3,E+S);
    delay(1+E+S);
    tone(PWM_PIN,C4,S);
    delay(1+S);
    
    tone(PWM_PIN,LA3,Q);
    delay(1+Q);
    tone(PWM_PIN,F3,E+S);
    delay(1+E+S);
    tone(PWM_PIN,C4,S);
    delay(1+S);
    tone(PWM_PIN,LA3,H);
    delay(1+H);
    
    tone(PWM_PIN,E4,Q); 
    delay(1+Q); 
    tone(PWM_PIN,E4,Q);
    delay(1+Q);
    tone(PWM_PIN,E4,Q);
    delay(1+Q);
    tone(PWM_PIN,F4,E+S);
    delay(1+E+S);
    tone(PWM_PIN,C4,S);
    delay(1+S);
    
    tone(PWM_PIN,Ab3,Q);
    delay(1+Q);
    tone(PWM_PIN,F3,E+S);
    delay(1+E+S);
    tone(PWM_PIN,C4,S);
    delay(1+S);
    tone(PWM_PIN,LA3,H);
    delay(1+H);
    
    tone(PWM_PIN,LA4,Q);
    delay(1+Q);
    tone(PWM_PIN,LA3,E+S);
    delay(1+E+S);
    tone(PWM_PIN,LA3,S);
    delay(1+S);
    tone(PWM_PIN,LA4,Q);
    delay(1+Q);
    tone(PWM_PIN,Ab4,E+S);
    delay(1+E+S);
    tone(PWM_PIN,G4,S);
    delay(1+S);
    
    tone(PWM_PIN,Gb4,S);
    delay(1+S);
    tone(PWM_PIN,E4,S);
    delay(1+S);
    tone(PWM_PIN,F4,E);
    delay(1+E);
    delay(1+E);//PAUSE
    tone(PWM_PIN,Bb3,E);
    delay(1+E);
    tone(PWM_PIN,Eb4,Q);
    delay(1+Q);
    tone(PWM_PIN,D4,E+S);
    delay(1+E+S);
    tone(PWM_PIN,Db4,S);
    delay(1+S);
    
    tone(PWM_PIN,C4,S);
    delay(1+S);
    tone(PWM_PIN,B3,S);
    delay(1+S);
    tone(PWM_PIN,C4,E);
    delay(1+E);
    delay(1+E);//PAUSE QUASI FINE RIGA
    tone(PWM_PIN,F3,E);
    delay(1+E);
    tone(PWM_PIN,Ab3,Q);
    delay(1+Q);
    tone(PWM_PIN,F3,E+S);
    delay(1+E+S);
    tone(PWM_PIN,LA3,S);
    delay(1+S);
    
    tone(PWM_PIN,C4,Q);
    delay(1+Q);
     tone(PWM_PIN,LA3,E+S);
    delay(1+E+S);
    tone(PWM_PIN,C4,S);
    delay(1+S);
    tone(PWM_PIN,E4,H);
    delay(1+H);
    
     tone(PWM_PIN,LA4,Q);
    delay(1+Q);
    tone(PWM_PIN,LA3,E+S);
    delay(1+E+S);
    tone(PWM_PIN,LA3,S);
    delay(1+S);
    tone(PWM_PIN,LA4,Q);
    delay(1+Q);
    tone(PWM_PIN,Ab4,E+S);
    delay(1+E+S);
    tone(PWM_PIN,G4,S);
    delay(1+S);
    
    tone(PWM_PIN,Gb4,S);
    delay(1+S);
    tone(PWM_PIN,E4,S);
    delay(1+S);
    tone(PWM_PIN,F4,E);
    delay(1+E);
    delay(1+E);//PAUSE
    tone(PWM_PIN,Bb3,E);
    delay(1+E);
    tone(PWM_PIN,Eb4,Q);
    delay(1+Q);
    tone(PWM_PIN,D4,E+S);
    delay(1+E+S);
    tone(PWM_PIN,Db4,S);
    delay(1+S);
    
    tone(PWM_PIN,C4,S);
    delay(1+S);
    tone(PWM_PIN,B3,S);
    delay(1+S);
    tone(PWM_PIN,C4,E);
    delay(1+E);
    delay(1+E);//PAUSE QUASI FINE RIGA
    tone(PWM_PIN,F3,E);
    delay(1+E);
    tone(PWM_PIN,Ab3,Q);
    delay(1+Q);
    tone(PWM_PIN,F3,E+S);
    delay(1+E+S);
    tone(PWM_PIN,C4,S);
    delay(1+S);
    
    tone(PWM_PIN,LA3,Q);
    delay(1+Q);
     tone(PWM_PIN,F3,E+S);
    delay(1+E+S);
    tone(PWM_PIN,C4,S);
    delay(1+S);
    tone(PWM_PIN,LA3,H);
    delay(1+H);
    
    delay(2*H);
    radio.setModeOff();
    Serial.print("deja de tx,radio off");
  } else {
    // If we get here, the channel is busy. Let's also print out the RSSI.
    Serial.print("The channel was busy. Waiting 10 seconds. RSSI: ");
    Serial.println(radio.readRSSI());
    
    // Wait 10 seconds and check the channel again.
    delay(10000);
  } 
     delay(300000); //espera 5 min
   
}


