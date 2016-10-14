/* 
Program uses Arduino MP3 shield to play sounds from SD card and write activity (here button presses) to SD card. 
attachinterrupts are implemented to capture rapid button Presses, debouncing included. 
program logs each press and the milliseconds since start time.
Written for Sensory Toy Box Project. Stephanie Valencia. 2016.
Notes:
interrupt pins for Arduino Mega 2, 3, 18, 19, 20, 21
Libraries: SdFat, SFEMP3Shield.
*/

//Libraries
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
SdFat sd;
SdFile myFile;
SFEMP3Shield MP3;


//Pins Definitions
#define RST_PIN         26
#define SS_PIN          53

int buttonA = 0;
int buttonB = 0;
int buttonC = 0;

// time 
unsigned long initial_time, button_pressed, elapsed;
float h, m, s, ms;
unsigned long over;

//selected LEDs
#define LED_A           30
#define LED_B           32
#define LED_C           33

//SD card Audio Files in order
#define sound1   0
#define sound2   1
#define sound3   2

int interrupcion = 0;
int boton = 0;
int event = 0;

//Chip select for SD card
const int chipSelect = 9;

char name[] = "File_player1.csv"; //

//interruptPins 
const byte interruptPin = 18;
const byte interruptPin2 = 19;
const byte interruptPin3 = 20;
volatile byte state = LOW;
unsigned long button_time = 0;  
unsigned long last_button_time = 0; 

void setup() {

  Serial.begin(9600);
  pinMode(22, INPUT); //
  initial_time = millis();

#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  if (!sd.begin(chipSelect, SPI_HALF_SPEED)) sd.initErrorHalt();
  
  //outputs
  pinMode(30, OUTPUT); // LED_A
  pinMode(32, OUTPUT); // LED_B
  pinMode(34, OUTPUT); // LED_C

  Serial.begin(9600); 
  while (!Serial);    
  SPI.begin();        

  randomSeed(analogRead(7)); //HERE ESTO para que es?
  sd.begin(SD_SEL, SPI_HALF_SPEED);
  MP3.begin();
  
  //Volume
  union twobyte mp3_vol; 
  mp3_vol.word = MP3.getVolume(); 
  mp3_vol.byte[1] = 2;
  MP3.setVolume(mp3_vol.byte[1], mp3_vol.byte[1]);

  MP3.playTrack(intro);
  delay(2200);
  MP3.stopTrack();

  //STRINGS event,button number, ms
  String stringTitle = String("num,button,milliseconds");
  if (!myFile.open(name, O_RDWR | O_CREAT | O_AT_END)) {
    sd.errorHalt("opening File_player1.txt for write failed");
  }
  // if the file opened okay, write to it:
  myFile.println();
  myFile.print(stringTitle);
  myFile.println();
  myFile.close();
  pinMode(interruptPin, INPUT_PULLUP);
  Serial.println(F("SetUp Completed."));
}

//ISR
int c=0;

void stimuli_on(){

  button_time = millis();
  //check to see if increment() was called in the last 250 milliseconds
  if (button_time - last_button_time > 250)
  {
    c++;
    Serial.println(c);
    last_button_time = button_time;
    Save_log(elapsed, boton);
    
  }
}

void Save_log(long elapsed, int boton){
     h = int(elapsed / 3600000);
     over = elapsed % 3600000;
     m = int(over / 60000);
     over = over % 60000;
     s = int(over / 1000);
     ms = over % 1000;
     String string_dataline = String("#" + String(event) + "," + String(boton) + "," + String(elapsed));
     if (!myFile.open(name, O_RDWR | O_CREAT | O_AT_END)) {
          sd.errorHalt("opening File_player1.txt for write failed");
        }
        // if the file opened okay, write to it:
     myFile.print(string_dataline);
     myFile.println();
     myFile.close();
     event = event + 1;  
}

void loop() {
buttonA = digitalRead(interruptPin);
buttonB = digitalRead(interruptPin2);
buttonC = digitalRead(interruptPin3);
      if (buttonA == HIGH) {
        boton = 1;
        MP3.playTrack(1);
        delay(2500); // modify delays as needed
        MP3.stopTrack();
        delay(100);
        button_pressed = millis();
        elapsed = button_pressed - initial_time;   
      }
      if (buttonB == HIGH) {
        boton = 2;
        MP3.playTrack(2);
        delay(2500);
        MP3.stopTrack();
        delay(100);
        button_pressed = millis();
        elapsed = button_pressed - initial_time;
      }

      if (buttonC == HIGH) {
        boton=3;
        MP3.playTrack(3);
        delay(2500);
        MP3.stopTrack();
        delay(100);
        button_pressed = millis();
        elapsed = button_pressed - initial_time;
      }
attachInterrupt(digitalPinToInterrupt(interruptPin), stimuli_on, FALLING);
attachInterrupt(digitalPinToInterrupt(interruptPin2), stimuli_on, FALLING);
attachInterrupt(digitalPinToInterrupt(interruptPin3), stimuli_on, FALLING);
}
