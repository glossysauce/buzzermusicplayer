/*REFERENCES
most of the code comes from https://docs.google.com/document/d/1CTlE3SS_InGebgi8vDGx7RPTlqHVYv20GMxSvVFUmk0/mobilebasic
also referenced: https://projecthub.arduino.cc/Code_and_Make/how-to-make-music-with-an-arduino-491912#section5 
music from: https://musescore.com/user/38235231/scores/2325721 
breaboard layout from: https://docs.arduino.cc/tutorials/uno-r4-minima/dac/ (this was purely digital and i plugged into dig pin 9 instead of A0)
*/

#include "notes.h"

#define BUZZERPIN 9  

int tempo = 120;

// this calculates the duration of a whole note in ms (60s/tempo)*4 beats
int wholenote = (60000 * 4) / tempo;

int mainMelody[] = {

  DS4, F4, FS4, GS4, AS4, DS5, CS5, AS4, DS4, AS4, GS4, FS4, F4, DS4, 
  F4, FS4, GS4, AS4, GS4, FS4, F4, DS4, F4, FS4, F4, DS4, D4, F4, DS4, 
  F4, FS4, GS4, AS4, DS5, CS5, AS4, DS4, AS4, GS4, FS4, F4, DS4, F4, 
  FS4, GS4, AS4, GS4, FS4, F4, FS4, GS4, AS4

};

/* 1 = WHOLE NOTE    
   2 = HALF NOTE
   4 = QUARTER NOTE
   8 = EIGHTH NOTE  
  16 = SIXTEENTH NOTE */

int mainNotes[] = {

  8, 8, 8, 8, 4, 8, 8, 4, 4, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 8, 8, 8, 
  8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 4, 8, 8, 8, 8, 8, 8, 8, 8, 4, 
  8, 8, 4, 4, 4, 4

};


//calculate the total length of the notes
size_t melLength = sizeof(mainMelody) / sizeof(mainMelody[0]);


void setup() {

  //buzzer output pin setup

  pinMode(BUZZERPIN, OUTPUT);


  //variable set up

  unsigned long previousMillis = millis();

  unsigned long currentMillis;

  int noteDuration;


  //main melody playing here

  for (int thisNote = 0; thisNote < melLength; thisNote++) {


    //dotted note logic

    mainNotes[thisNote] > 0 ? noteDuration = wholenote / mainNotes[thisNote] : noteDuration = (wholenote / (abs(mainNotes[thisNote]))) * 1.5;


    //play the sound

    tone(BUZZERPIN, mainMelody[thisNote], noteDuration * 0.9);


    // the note's duration time. This will keep pulling until the duration time is up

    do {

      currentMillis = millis();                                     //grab current time

    } while (!((currentMillis - previousMillis) >= noteDuration));  //check if time is long enough

    previousMillis = currentMillis;                                 //update previousmilli


    // stop the tone playing:

    noTone(BUZZERPIN);

  }

}

void loop() {
}