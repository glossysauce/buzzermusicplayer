/* SOPHIE YANG
blue by yung kai :D 

REFERENCES
breadboard layout from: https://docs.arduino.cc/tutorials/uno-r4-minima/dac/ (this was purely digital and i plugged into dig pin 9 instead of A0)
music from: https://musescore.com/user/36935768/scores/20261989 (i edited bass clef and chords out then exported as a new wav)
*/

#include <avr/pgmspace.h>  // Include the PROGMEM library

#define BUZZERPIN 9  

// Define frequencies in Hz and durations in milliseconds
const float frequencies[] PROGMEM = {
  333.76, 312.23, 247.63, 333.76, 312.23, 247.63, 333.76, 312.23, 247.63, 333.76, 366.06, 419.90, 495.26, 549.10, 656.76, 882.86, 829.03, 742.90, 742.90, 624.46, 656.76, 742.90, 656.76, 495.26, 419.90, 441.43, 495.26, 624.46, 656.76, 495.26, 549.10, 656.76, 882.86, 829.03, 742.90, 624.46, 624.46, 990.53, 882.86, 829.03, 656.76, 742.90, 829.03, 829.03, 829.03, 624.46, 624.46, 549.10, 559.86
};

// Store durations in flash memory
const float durations[] PROGMEM = {
    278.64, 313.47, 325.08, 267.03, 325.08, 336.69, 255.42, 325.08, 336.69, 267.03, 325.08, 313.47, 325.08, 232.20, 371.52, 267.03, 267.03, 673.38, 116.10, 336.69, 325.08, 325.08, 325.08, 963.63, 325.08, 325.08, 325.08, 963.63, 975.24, 348.30, 220.59, 359.91, 290.25, 267.03, 336.69, 766.26, 116.10, 336.69, 290.25, 278.64, 986.85, 1021.68, 267.03, 255.42, 267.03, 336.69, 650.16, 220.59, 104.49
};
// Calculate number of notes
size_t numNotes = sizeof(frequencies) / sizeof(frequencies[0]);

void setup() {
    pinMode(BUZZERPIN, OUTPUT);  // Set buzzer pin as output
    for (int i = 0; i < numNotes; i++) {
        // Read frequency and duration from PROGMEM
        float frequency = pgm_read_float(&frequencies[i]);
        float duration = pgm_read_float(&durations[i]);

        tone(BUZZERPIN, frequency, duration);  // Play the frequency
        delay(duration);  // Wait for the duration of the note
        noTone(BUZZERPIN);  // Stop the buzzer after each note
        delay(50);  // Slight delay for note separation
    }
    delay(1000);  // Delay before repeating the melody
}

void loop() {
}