# SOPHIE YANG - FFT NOTE EXTRACTER
import numpy as np
import librosa
import scipy.signal

def extract_notes(wav_file):
    # loading the wav file
    y, sr = librosa.load(wav_file, sr=None)
    
    # isolate clean tones with harmonic-percussive separation
    y_harmonic, _ = librosa.effects.hpss(y)

    # perform short term fourier transform
    n_fft = 4096  # increased for better frequency accuracy, this is # of points for FFT
    hop_length = 512 #step size between FFT
    stft = librosa.stft(y_harmonic, n_fft=n_fft, hop_length=hop_length) #computes the short term fourier transform

    # get the magnitude spectrogram
    # since stft contains real and imag parts, we need to extract the magnitude + ignore phase
    magnitude = np.abs(stft) 

    # convert magnitude to dB scale, this is how humans perceive loudness
    # this will prevent small peaks from being overshadowed by loud freqs!
    log_magnitude = librosa.amplitude_to_db(magnitude)

    # find peaks in the spectrogram to detect notes
    frequencies = librosa.fft_frequencies(sr=sr, n_fft=n_fft)
    times = librosa.frames_to_time(np.arange(log_magnitude.shape[1]), sr=sr, hop_length=hop_length)

    # detect notes by finding peaks in the frequency domain
    # note = highest peak in each frame
    notes = []
    for i in range(log_magnitude.shape[1]):
        frame = log_magnitude[:, i]
        peaks, _ = scipy.signal.find_peaks(frame, height=np.mean(frame) - 10)
        if len(peaks) > 0:
            dominant_freq = frequencies[peaks[np.argmax(frame[peaks])]]
            notes.append((dominant_freq, times[i]))

    #grouping similar freqs into notes
    note_durations = []
    if not notes:
        return note_durations  # empty if no notes were detected

    prev_freq = notes[0][0]  # first detected frequency
    start_time = notes[0][1]  # first note start time
    freq_tolerance = 2  # 2hz tolerance
    dur_tolerance = 30 #reject any note duration shorter than dur_tolerance ms, can be changed based on bpm

# group consecutive and similar frequencies into a single note
    for i in range(1, len(notes)):
        freq, timestamp = notes[i]
        
        if abs(freq - prev_freq) > freq_tolerance:  # detect significant changes
            duration = (timestamp - start_time) * 1000  # convert to ms
            
            if duration > dur_tolerance:  # apply duration filter
                note_durations.append((prev_freq, duration))
            
            start_time = timestamp  # reset start time
            prev_freq = freq  # update frequency

    # handle the last note
    duration = (times[-1] - start_time) * 1000
    if duration > dur_tolerance:
        note_durations.append((prev_freq, duration))

    return note_durations

#export notes and durations in a txt file
def export_notes(note_durations, output_file):
    with open(output_file, 'w') as f:
        frequencies = [f"{freq:.2f}" for freq, _ in note_durations]
        f.write(", ".join(frequencies))

def export_durations(note_durations, output_file):
    with open(output_file, 'w') as f:
        durations = [f"{duration:.2f}" for _, duration in note_durations]
        f.write(", ".join(durations))

# import audio as wav
wav_file = "your_audio.wav"
note_durations = extract_notes(wav_file)

export_notes(note_durations, "notes.txt")
export_durations(note_durations, "durations.txt")

print("notes + durations extracted and saved")
