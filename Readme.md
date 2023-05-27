# Tale's JSFX Pack

This is my homebrew collection of free, hackable
[JSFX](https://www.reaper.fm/sdk/js/js.php) audio/MIDI plug-ins and
libraries for [REAPER](https://www.reaper.fm/) v4.60+.

## Documentation

Tale's JSFX Pack includes these JSFX plug-ins:

* [**ab_mono**](Effects/Tale/ab_mono): A/B two mono channels.
* [**colored_noise**](Effects/Tale/colored_noise): Colored noise generator.
* [**drum_synth**](Effects/Tale/drum_synth): Simple drum synth (GM compatible, although incomplete).
* [**insert_to_bus**](Effects/Tale/insert_to_bus): Insert to bus convertor.
* [**midi_sustain**](Effects/Tale/midi_sustain): MIDI sustain emulator.
* [**midi_vibrato**](Effects/Tale/midi_vibrato): MIDI vibrato via Pitch Bend.
* [**mono_synth**](Effects/Tale/mono_synth): Simple mono/poly synth.
* [**music_box**](Effects/Tale/music_box): Toy music box synth.
* [**pc_speaker**](Effects/Tale/pc_speaker): PC speaker square wave synth.
* [**poly_mono_midi_router**](Effects/Tale/poly_mono_midi_router): Dynamic poly/mono MIDI router.
* [**random_midi_notes**](Effects/Tale/random_midi_notes): Random MIDI note generator.
* [**rc_filter**](Effects/Tale/rc_filter): Multimode RC filter.
* [**tube_amp**](Effects/Tale/tube_amp): Preamp simulation.
* [**zdf_filter**](Effects/Tale/zdf_filter): Multimode ZDF filter.

The following JSFX libraries are included:

* [**adsr.jsfx-inc**](Effects/Tale/adsr.jsfx-inc): ADSR envelope. [#](https://www.taletn.com/reaper/mono_synth/#adsr)
* [**array.jsfx-inc**](Effects/Tale/array.jsfx-inc): Simple two-dimensional array interface. [#](https://www.taletn.com/reaper/mono_synth/#array)
* [**complex.jsfx-inc**](Effects/Tale/complex.jsfx-inc): Complex math operations. [#](https://www.taletn.com/reaper/mono_synth/#complex)
* [**fft_real_synth.jsfx-inc**](Effects/Tale/fft_real_synth.jsfx-inc): Real FFT bandlimited synthesis. [#](https://www.taletn.com/reaper/mono_synth/#fft_real_synth)
* [**fft_synth.jsfx-inc**](Effects/Tale/fft_synth.jsfx-inc): FFT bandlimited synthesis. [#](https://www.taletn.com/reaper/mono_synth/#four)
* [**fourier_series.jsfx-inc**](Effects/Tale/fourier_series.jsfx-inc): Fourier series waveforms. [#](https://www.taletn.com/reaper/mono_synth/#fourier_series)
* [**lfo.jsfx-inc**](Effects/Tale/lfo.jsfx-inc): Naive (non-bandlimited) low-frequency oscillator. [#](https://www.taletn.com/reaper/mono_synth/#lfo)
* [**malloc.jsfx-inc**](Effects/Tale/malloc.jsfx-inc): Dynamic memory management. [#](https://www.taletn.com/reaper/mono_synth/#malloc)
* [**midi_queue.jsfx-inc**](Effects/Tale/midi_queue.jsfx-inc): Sample accurate MIDI queue. [#](https://www.taletn.com/reaper/mono_synth/#midiq)
* [**noise.jsfx-inc**](Effects/Tale/noise.jsfx-inc): Noise generator. [#](https://www.taletn.com/reaper/mono_synth/#lcg)
* [**oversample.jsfx-inc**](Effects/Tale/oversample.jsfx-inc): 2x oversampler. [#](https://www.taletn.com/reaper/mono_synth/#os)
* [**poly_blep.jsfx-inc**](Effects/Tale/poly_blep.jsfx-inc): PolyBLEP quasi-bandlimited tone generator. [#](https://www.taletn.com/reaper/mono_synth/#poly)
* [**rbj_filter.jsfx-inc**](Effects/Tale/rbj_filter.jsfx-inc): 2nd-order RBJ filter. [#](https://www.taletn.com/reaper/mono_synth/#rbj)
* [**rc_filter.jsfx-inc**](Effects/Tale/rc_filter.jsfx-inc): 1st-order RC filter. [#](https://www.taletn.com/reaper/mono_synth/#rc)
* [**sine.jsfx-inc**](Effects/Tale/sine.jsfx-inc): Efficient sine/cosine wave oscillator. [#](https://www.taletn.com/reaper/mono_synth/#sin)
* [**uint.jsfx-inc**](Effects/Tale/uint.jsfx-inc): Low-level 32/64-bit unsigned integer operations. [#](https://www.taletn.com/reaper/mono_synth/#uint)
* [**wavetable.jsfx-inc**](Effects/Tale/wavetable.jsfx-inc): Wavetable oscillator. [#](https://www.taletn.com/reaper/mono_synth/#wave)
* [**window.jsfx-inc**](Effects/Tale/window.jsfx-inc): Window functions. [#](https://www.taletn.com/reaper/mono_synth/#wnd)
* [**zdf_filter.jsfx-inc**](Effects/Tale/zdf_filter.jsfx-inc): Zero-delay feedback state variable filter. [#](https://www.taletn.com/reaper/mono_synth/#zdf)

## Installation

To install Tale's JSFX Pack copy the `Effects/Tale` folder to your REAPER JS
`Effects` folder. The exact location of this folder depends on your REAPER
installation. To navigate to the right location launch REAPER, and choose
*Show REAPER resource path in explorer/finder...* from the *Options* menu.

## System Requirements

Tale's JSFX Pack should run on REAPER v4.60 or newer.

## License

Plug-ins: [LGPL](https://www.gnu.org/licenses/lgpl.html)  
Libraries: [WTFPL](http://www.wtfpl.net/)
