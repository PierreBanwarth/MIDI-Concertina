# MIDI-concertina


This is The Github project wich his a personnal work about Making an electronic version of my concertina,

Goal is to play by night with my headphones for my neighboors and maybe with my band BernyTradSchool

Arduino =>( midi library )  Serial port ( hairless midi serial ) => midi port ( loopMidi ) => Fruity Loops / Ableton / ...

We chose this solution because it's the most generic you can interface with

===============================NEW================================================
I'm actually trying to make a custom PCB for both hands, and maybe adding a pressure sensor to put in a real instrument
==================================================================================

I use two arduinos (nano)

With MIDILibrary (very easy to use for outputs)
http://playground.arduino.cc/Main/MIDILibrary

Good for interface with a virtual midi port and to test while developing
http://projectgus.github.io/hairless-midiserial/

to test and interface with Hairless Midi <-> Serial
http://www.tobias-erichsen.de/software/loopmidi.html

this project is developed with platformIO file structure.
http://platformio.org/

After the V1 done (whithout air sensor) it's look my buttons was very bad and not speed enough to play music so i have ordered some Cherry mx black keys 

I have done my custom keyboard here 
http://www.keyboard-layout-editor.com/#/

and use it to create the grid to plate mounted switches
http://builder.swillkb.com/

I've write tutorials here :
In english
https://www.instructables.com/id/Make-Your-MIDI-Accordion/
In french
https://ouiaremakers.com/posts/tutoriel-diy-creation-d-un-accordeon-midi
