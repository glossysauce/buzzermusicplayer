# Arduino Buzzer Music Player

This project consists of two subprojects that work together to play melodies using a passive buzzer connected to an Arduino.

## Hardware Components
- **Arduino Uno R3 Board**
- **Passive Buzzer** (connected to digital pin 9)
- **Potentiometer**
- **Breadboard**
- **Jumper wires**

## Manual Input Subproject (template.c and notes.h)

### Note Representation
The melody is stored in an array (`mainMelody[]`) containing musical notes (frequencies).  
A second array (`mainNotes[]`) stores the duration of each note using standard musical notation (e.g., whole, half, quarter, eighth notes).

### Timing & Playback
- The tempo (bpm) determines the duration of a whole note (`wholenote`), calculated as:  
  `whole note = (60000 * 4)/tempo`.  
  This tempo can be adjusted by the user.
- Each note's duration is derived from this base value, with support for dotted notes.

### Sound Generation
- The `tone()` function sends a frequency signal to the buzzer for a specific duration. This signal is a square wave.
- A blocking loop ensures that each note plays for its full duration before proceeding to the next one.
- After playing a note, `noTone()` is used to stop the sound before the next note starts.

### References & Design Choices
- The buzzer is connected to a digital pin instead of an analog pin for compatibility with Arduino's built-in `tone()` function and the passive buzzer.
- A header file (`notes.h`) that implements a lookup table allows easy modification of melodies and note durations.

## Fourier Transform Audio Subproject

### FFTNoteExtractor.py
This program implements a **Fast Fourier Transform (FFT)** for frequency analysis and note extraction. It processes an input audio file to detect musical notes and their durations, then exports the results as text files that will be read by the `FFToutput.c` program.

#### Key Features
- **Harmonic-Percussive Separation**: Filters out background noise and isolates harmonic tones for cleaner note detection.
- **Short-Time Fourier Transform (STFT)**: Converts the audio signal into a frequency spectrum for analysis.
- **Peak Detection**: Identifies dominant frequencies in each frame to extract musical notes.
- **Grouping & Filtering**: Merges consecutive similar frequencies into sustained notes and removes short-duration noise.
- **Exports to Text Files**: Saves extracted frequencies (`notes.txt`) and note durations (`durations.txt`) for further use.

#### Program Processing
1. **Load and Preprocess Audio**
   - Reads the WAV file using **Librosa** with the original sampling rate (`sr=None`).
   - Applies harmonic-percussive separation to isolate tones.

2. **Perform Short-Time Fourier Transform (STFT)**
   - Computes frequency vs. time representation using an FFT size of **4096** for high accuracy.
   - Converts magnitudes to dB scale to improve peak detection.

3. **Peak Detection for Note Extraction**
   - Identifies the highest peak in each frame as the dominant note frequency.
   - Groups similar frequencies to determine sustained notes.
   - Filters out short-duration transients to reduce noise.

4. **Exporting Data**
   - Saves the extracted frequencies to `notes.txt`.
   - Saves the corresponding note durations to `durations.txt`.

### FFToutput.c
This program is intended to be used for the Arduino.

#### Memory Optimization with PROGMEM
- The `frequencies[]` and `durations[]` arrays are stored in **flash memory** (`PROGMEM`) to reduce **RAM** usage. This prevents large note sequences from consuming dynamic memory, making the program more efficient.

#### Melody Playback
- A `for` loop iterates through all the notes, retrieving frequencies and durations from `PROGMEM`.
- The `tone()` function plays each note as a square wave on the buzzer.
- A `delay()` ensures the note plays for the correct duration, with a small gap (50ms) for separation.
