# CTAG Drum-Sampler

This project implements an Audio-Drum-Sampler-VST-Plug-in for Windows built within the [JUCE Framework] (https://juce.com/)

### Goal of the Project
The goal of this project was to design a sampler where you can choose between 5 different modes (Chromatic, Minor, Major, Harmonic Minor and Melodic Minor).
When one mode is chosen, you can only pitch the sample within your given key.

### Features
* Total of 9 Voices
* Each Voice has: ADSR-Volume-Envelope, Gain-Control, Pan-Control, Pitching, One-Pole-Filter, WaveShaper, Velocity Modulation for amplitude and filter cutoff
* Choose between 5 different Drum-Kits with (Kick, Snare, Clap, ClHat, OpHat, Tom, Perc, Ride, Crash)
* Drum Instruments arranged after General-Midi-Standard 
* Choose between 5 different Modes and all Root Notes to choose your Scale
* Hi-Hat Choke Group to emulate real world drum behavior


### How to use
For using the plug-in you can choose between a standalone and a VST2 version of the Sampler (Both for Windows).
For both you have to place the given Samples folder into the users desktop directory, so that all samples can get loaded properly.
