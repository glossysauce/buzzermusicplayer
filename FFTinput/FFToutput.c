/* SOPHIE YANG
REFERENCES
breadboard layout from: https://docs.arduino.cc/tutorials/uno-r4-minima/dac/ (this was purely digital and i plugged into dig pin 9 instead of A0)
music from: https://musescore.com/user/36935768/scores/20261989 (i edited bass clef and chords out then exported as a new wav)
*/

#include <avr/pgmspace.h>  // Include the PROGMEM library

#define BUZZERPIN 9  

// Define frequencies in Hz and durations in milliseconds
const float frequencies[] PROGMEM = {
    // paste notes.txt output
};

// Store durations in flash memory
const float durations[] PROGMEM = {
    // paste notes.txt output
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
}

void loop() {
}