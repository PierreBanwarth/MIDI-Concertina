# MIDI-concertina


This is The Github project wich his a personnal work about Making an electronic version of my concertina,

Goal is to play by night with my headphones for my neighboors and maybe with my band BernyTradSchool

Arduino =>( midi library )  Serial port ( hairless midi serial ) => midi port ( loopMidi ) => Fruity Loops / Ableton / ...

We chose this solution because it's the most generic you can interface with

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


=== I'm actually trying to make a custom PCB for both hands, and maybe adding a pressure sensor to put in a real instrument ===

Some personnal note in french about the new version 

=?= capteur de pression  =?=
    
- comment partager l'info du bmp 280 ?
- combien d'entrée ça prend un bmp 280 ? Réponse : 4
- pour avoir une valeur normative on pourrait faire un differenciel avec un autre bmp 280 placé dans le clavier
- dans les deux cas comment on fait passer la même info des deux côtés de l'instrument ?
    
=?= question physiques  =?=

- cableries avec étanchéité ?
- Un trou de taille variable pourrait permettre de tester les influences différentes d'un trou qui simule un bouton ouvert.
- Gestion de l'air on passe de pousser/tirer a pousser/rien/tirer

=?= clavier  =?=

- Boutons custom ?
https://www.massdrop.com/buy/gateron-switches
- Cercle silicon ? 
- lubrification des boutons ?
- achat de clip qui se posent sur le switch avec 30% de réduction du bruit ?
    
=?= Couleurs  =?=
- LED ? on pourrait ajouter un arduino pour gerer les leds eventuels ?

RASPBERRY integration
- Deux boards FTDI 
    - par défaut branché au raspberry
    - si branché a un pc raspberry annulé
    
- Une batterie
    - branché au raspberry
    - bouton on/off pour l'alimentation 
    - sortie de recharge en exterieur
- Sortie casque

sorties prévues en facade : 
    - sortie casque (output son raspberry)
    - prise usb 1 (pour arduino 1)
    - prise usb 2 (pour arduino 2)
    - prise usb 3 pour recharge batterie du raspberry
    - switch on/off pour alimentation raspberry

intérèt d'imprimer une version test sans soupape du boitier imprimé en 3D
- tester et valider la forme des boites
- tester et valider les entrées et les boutons
- valider installation capteur de préssion
- tester pour savoir ce qu'on peux ajouter et comment
