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
#define intro    0
#define sound1   1
#define sound2   2
#define sound3   3

#define sound4   4
#define sound5   5
#define sound6   6
#define sound7   7
#define sound8   8
#define sound9   9
#define sound10  10
#define sound11  11
#define sound12  12
#define sound13  13
#define sound14  14
#define sound15  15
#define sound16  16
#define sound18  18
#define sound19  19
#define sound20  20

int sensorValue = digitalRead(18);


int interrupcion = 0;
int boton = 0;
int event = 0;
int c1 = 0;
int c2 = 0;

//Chip select for SD card
const int chipSelect = 9;

char name[] = "File_player1.csv"; //

//interruptPins 
const byte interruptPin = 18;
const byte interruptPin2 = 19;
const byte interruptPin3 = 20;
byte state = LOW;
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
  pinMode(33, OUTPUT); // LED_C

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
     // Serial.println( digitalRead(18));
     //Serial.println( digitalRead(19));
      
      if (digitalRead(18)==1  && c1 == 0) {//sound1
        boton = 1;
        MP3.playTrack(1);
        delay(2500); // modify delays as needed
        MP3.stopTrack();
        delay(100);
        button_pressed = millis();
        elapsed = button_pressed - initial_time;
        c1++; 
        
         Serial.println(F("boton1 sonido 1"));
      }
      else if (digitalRead(18) == 1 && c1 == 1) {
       boton = 1;
       MP3.playTrack(2);
       delay(2500); // modify delays as needed
       MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
       c1++;   
           Serial.println(F("boton1 sonido 2"));
            }
   else if (digitalRead(18) == 1 && c1 == 2) {
       boton = 1;
       MP3.playTrack(3);
       delay(2500); // modify delays as needed
       MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
      c1++;  
           Serial.println(F("boton1 sonido 3"));
            }
 else if (digitalRead(18) && c1 == 3) {
       boton = 1;
       MP3.playTrack(4);
       delay(2500); // modify delays as needed
       MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
       c1++;    
           Serial.println(F("boton1 sonido 4"));
            }
 else if (digitalRead(18)&& c1 == 4) {
       boton = 1;
       MP3.playTrack(5);
       delay(2500); // modify delays as needed
       MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
       c1++;    
           Serial.println(F("boton1 sonido 5"));
            }
            
 else if (digitalRead(18)&& c1 == 5) {
       boton = 1;
       MP3.playTrack(6);
       delay(2500); // modify delays as needed
       MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
       c1++;    
           Serial.println(F("boton1 sonido 6"));
           
            }
  else if (digitalRead(18) && c1 == 6) {
       boton = 1;
       MP3.playTrack(7);
       delay(2500); // modify delays as needed
       MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
       c1++;    
               Serial.println(F("boton1 sonido 7"));
            }
            
 else if (digitalRead(18) && c1 == 7) {
       boton = 1;
       MP3.playTrack(8);
       delay(2500); // modify delays as needed
       MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
       c1++;    
                Serial.println(F("boton1 sonido 8"));
            }
            
 else if (digitalRead(18) && c1 == 😎 {
       boton = 1;
       MP3.playTrack(9);
       delay(2500); // modify delays as needed
       MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
       c1++;    
           Serial.println(F("boton1 sonido 9"));
            }
            
 else if (digitalRead(18) && c1 == 9) {
       boton = 1;
       MP3.playTrack(10);
       delay(2500); // modify delays as needed
       MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
       c1=0;   
           Serial.println(F("boton1 sonido 10"));
            }
            
      ///////////////////////////////////////////////////
    else if (digitalRead(19)==1  && c2 == 0) {
        boton = 2;
                
        MP3.playTrack(11);
        delay(2500);
        MP3.stopTrack();
        delay(100);
        button_pressed = millis();
        elapsed = button_pressed - initial_time;
        c2++; 
            Serial.println(F("boton2 sonido 1"));
      }
  else if (digitalRead(19) ==1 && c2 == 1) {
     boton = 2;
            
       MP3.playTrack(12);
       delay(2500); // modify delays as needed
        MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
       c2++;  
       Serial.println(F("boton2 sonido 2"));
            }
 else if (digitalRead(19) && c2 == 2) {
       boton = 2;
       MP3.playTrack(13);
       delay(2500); // modify delays as needed
       MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
       c2++;    
       Serial.println(F("boton2 sonido 3"));
            }
 else if (digitalRead(19) && c2 == 3) {
       boton = 2;
       MP3.playTrack(14);
       delay(2500); // modify delays as needed
       MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
       c2++;    
       Serial.println(F("boton2 sonido 4"));
            }
 else if (digitalRead(19) && c2 == 4) {
       boton = 2;
       MP3.playTrack(15);
       delay(2500); // modify delays as needed
       MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
       c2++;   
            }
            
 else if (digitalRead(19) && c2 == 5) {
       boton = 2;
       MP3.playTrack(16);
       delay(2500); // modify delays as needed
       MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
       c2++;    
            }
  else if (digitalRead(19) && c2 == 6) {
       boton = 2;
       MP3.playTrack(17);
       delay(2500); // modify delays as needed
       MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
       c2++;    
            }
            
 else if (digitalRead(19) && c2 == 7) {
       boton = 2;
       MP3.playTrack(18);
       delay(2500); // modify delays as needed
       MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
       c2++;    
            }
            
 else if (digitalRead(19) && c2 == 😎 {
       boton = 2;
       MP3.playTrack(19);
       delay(2500); // modify delays as needed
       MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
       c2++;    
            }
            
 else if (digitalRead(19) && c2 == 9) {
       boton = 2;
       MP3.playTrack(20);
       delay(2500); // modify delays as needed
       MP3.stopTrack();
       delay(100);
       button_pressed = millis();
       elapsed = button_pressed - initial_time;
       c2=0;
 }
 
///////////////////////////////////////////////////
     if (buttonC == LOW) {
        boton=3;
        button_pressed = millis();
        elapsed = button_pressed - initial_time;
      
      
//attachInterrupt(digitalPinToInterrupt(interruptPin), stimuli_on, RISING);
//attachInterrupt(digitalPinToInterrupt(interruptPin2), stimuli_on, RISING);
////attachInterrupt(digitalPinToInterrupt(interruptPin3), stimuli_on, RISING);
}
