# MIDI-concertina

This is The Github project wich his a personnal work about Making an electronic version of my concertina,

Goal is to play by night with my headphones for my neighboors and maybe with my band BernyTradSchool

Arduino =>( midi library ) Serial port ( hairless midi serial ) => midi port ( loopMidi ) => Fruity Loops / Ableton / ...

We chose this solution because it's the most generic you can interface with

I use two arduinos (nano)

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

Some personnal note in french about the new version

# Le projet : petit historique
Je suis developpeur et je joue du concertina et j'aime cet instrument inventé par un physicien (https://fr.wikipedia.org/wiki/Charles_Wheatstone)

Le problème initial était de pouvoir jouer au casque la nuit et ainsi laisser ma copine dormir.

## Electronique :
Dans cet objectif la j'ai acheté mon premier Arduino à noel 2016.

Avec cet objectif en tête je me suis dabord entrainé sur un controlleur de vole spatiaux pour le jeu Kerbal Space Program.


[PHOTO DE LA BOITE EN CARTON]

ça m'a permis de comprendre le branchement des boutons et la récupération des entrée/sortie dans le code.

J'ai ensuite réalisé un premier prototype de concertina MIDI


[PHOTO DU premier PROTOTYPE]

à l'époque je n'avais pas en tête l'utilisation du protocole MIDI je sortais donc le son en 8bit sur une sortie casque.

## Le clavier et les Boutons :

Depuis le début du projet le choix a été fait de ne pas faire de matrice de boutons.

Le but est de reproduire le plus fidèlement possible le jeux sur l'instrument (dans un premier temps son clavier au moins)

Hors le multipléxage ne permet pas de jouer plusieurs notes en même temps de façon continue.

Si je tape sur 6 touches je veux obtenir six sons différents.

Hors quand on tape sur six touches de son clavier d'ordinateur simultanément : on obtiens une seul frappe.

(peut etre a mieux expliquer)

Donc chaque sortie de l'arduino sera dédié a une touche.

### Premiers boutons :

[PHOTO Des premiers boutons]

Cependant les boutons etait bas de gamme et ne reagissais parfois pas du tout a l'appuie.

Hors ce projet necessite des boutons réactifs et précs.

### CHERRY MX
Je ne me souviens pas si c'est moi ou si on m'a soufflé l'idée mais c'est vrai que les boutons de claviers mécaniques ont plusieurs avantages :

Une communauté active qui a crée :
- Des PCB personnalisés.
- Les "Footprint" des divers boutons.
- beaucoup de comparatifs des différents boutons.
- Des utilitaires en lignes comme :
http://www.keyboard-layout-editor.com/#/
http://builder.swillkb.com/
- Des lubrifiants, ressorts alternatifs et autres silencieux (en cours d'études)

L'avantage de ces switchs c'est qu'ils sont fait pour durer dans le temps, sont fiable et précis.

De plus ils ont un "top" qui permet d'adapter tout et n'importe quoi sur le dessus :

étude en cours :
- boutons de clavier :
- boutons style accordéon :
- bontons style concertina :

Merci beaucoup à toutes la communauté de Geekhack et de Reddit/CustomKeyboard pour toutes les heures de lectures.

J'ai donc fait un premier clavier (sans soufflet) qui ressemble aux claviers coupés en deux

[PHOTO DE LA VERSION 2]

Soucis rencontrés avec ce modèle : le clavier etait souder sans PCB donc par des cables.

Au niveau du temps et des manipulations ça s'est averé plutot fragile (malgré l'intervention d'un ami electronicien)

L'avantage du clavier de CONCERTINA-MIDI-V3 c'est que le PCB va finir de stabiliser les boutons

## Note sur le soufflet :
N'ayant qu'un seul concertina à cet époque la j'ai eu plusieurs idée de réalisation de soufflet custom.

Cependant devant la complexité de la chose j'ai décidé de ne pas gérer le soufflet dans un premier temps et d'utiliser un bouton à la place pour simuler le pousser/tirer.

* footswitch (pédale de guitare) : trop dur pour la main
* Bouton d'arcade : pas mal mais placé au mauvais endroit (sous la paume)
* Joystick : contre intuitif mais interessant de par les deux axes (mais on sort de l'idée de reproduction d'accordéon.)
* Cherry MX : parce que finalement c'est les meilleurs boutons qu'on puisse trouver j'ai réussi a en placer un sous mon pouce et c'etait plutôt efficace.

Cependant en 2017 j'ai acheté un nouveau concertina. Me laissant du coup l'ancien modèle libre. On en reparlera quand on evoquera l'impression 3D

## OPEN SOURCE MIDI :

Attiré depuis le début par la réalisation d'un projet a 100% Open Source et Open Hardware

Concernant le protocole MIDI j'ai entendu des choses sur des protocoles plus récent et peut être plus adapté a mon besoin.

Cependant je n'ai pas eu l'occasion ni le temps de me pencher sur ces solutions

With MIDILibrary (very easy to use for outputs)
http://playground.arduino.cc/Main/MIDILibrary

Good for interface with a virtual midi port and to test while developing
http://projectgus.github.io/hairless-midiserial/

to test and interface with Hairless Midi <-> Serial
http://www.tobias-erichsen.de/software/loopmidi.html

## RASPBERRY AS MIDI SYNTH.

Après la version 2.0 j'ai appris quelques morceaux les nuits d'insomnie, je me suis bien amusé a jouer de la guitare electrique et des sons MIDI vraiments moches

Cependant un nouveau besoin est arrivé, j'avais 2x45 minutes de trajets en bus par jour donc pourquoi pas profiter de ce temps "mort" pour jouer du concertina MIDI

J'ai donc cherché une solution et découvert que le Raspberry pouvait remplir la fonction de synthé MIDI.

Alors on ajoute une batterie pour alimenter le raspberry, On lance le démarrage du synthé MIDI, et on connect ça aux arduinos.

[Peut être mettre ici un tuto sur l'installation du synthé et son démarrage automatique]

plus qu'a choisir le son et on peux jouer en branchant un prise jack a la solution existante.


Cette version répond au besoin mais pause de nouvelles intérogations et ouvre un nouveau chant des possible

Nouveaux défi :
- laisser un raspberry dans la solution et permettre de brancher quand meme les deux mains de l'accordéon a un ordinateur
- intégrer la batterie a la solution => recharchement / boutons on/off

## NUMEROTATION DES VERSIONS ET MODELE ECONOMIQUE

Au fil de l'eau j'ai décidé d'un systême de notation des versions

les versions supérieurs verront un nouveau systême soit sur le clavier soit le soufflet voir les deux

et on passera a 3.5 sur une version portable (avec raspberry intégré)

J'ai réalisé qu'une seul main sans gestion du soufflet correspondais un petit clavier MIDI sans Matrice qui peux servir pour la musique electronique

Vu que le projet est Open Source vous n'aurez pas besoin de moi pour refaire tout de A à Z mais vous risquez d'y passer du temps.

J'ai donc opté pour une solution de vente du style Tyndie ou je vendrais
- le circuit imprimé
- le circuit imprimé + Arduino + Cherry MX + Boitier + vis etc..

https://www.tindie.com/

peut etre aussi une solution du style Pay me a coffee.

## GESTION DU SOUFFLE
  On a vu à travers l'impression 3D qu'on pouvais enfin sans abimer l'ancien concertina recreer des boitiers

  On peux donc placer un capteur de préssion.

  Mais on doit faire attention a la circulation de l'air :

    - attention a laisser passer de l'air (comme si on appuyais en permanence sur un bouton)

    - laisser passer de l'air implique une soupape (Gros trou ouvrable a l'aide d'un bouton pour reprendre ou relacher beaucoup d'air d'un coup)


# CONCERTINA MIDI V3.1
Le nouvelle version comporte deux avancés majeurs :
* gestion de l'air réaliste
* circuit imprimé pour les boutons et le BME280

## Impression 3D :
C'est en arrivant vivre à Rennes que j'ai découvert l'imprimante 3D d'un ami.
[PHOTO DU TRUMP 3D]

J'en ai acheté une peux de temps après, j'ai cependant fait l'erreure d'acheter une Geeetech I3 PRO B que je n'ai jamais vraiment réussi a maitriser.
[PHOTO DE MON IMPRIMANTE]

J'ai donc fini par prendre contact avec un imprimeur sur Rennes (https://www.hephaprint.fr/)

Au début l'idée c'était de faire une grille spécial pour mon nouveau concertina et c'etait l'occasion de faire connaissance :
[PHOTO DU CONCERTINA BLEU]

C'est un peu plus tard que je me suis rendu compte que si on pouvais imprimer le haut du boitier on pouvais du coup faire le bas

Et ainsi mettre le clavier déja réalisé dans une boite étanche et a la taille exact du soufflet.

Ce qui finalement nous permettrait de mettre un capteur de préssion pour gagner en réalisme.

Nous avons donc pris les côtes de mon premier concertina et réalisé un boitié en PET.
[PHOTO DE LA BOITE NOIRE]

## MY OWN PCB
Petit feedback sur la réalisation d'un circuit imprimé pour les boutonsn, le capteur de préssion et l'arduino

Tester c'est douter ?

J'ai réalisé deux plaques a l'heure ou j'ecrit ça et j'espere que la troisieme version sera la derniere.

Soucis de la première : Les boutons sont trop écartés et la plaque est trop grande

Soucis de la deuxième et de la premiere aussi du coup : Problème de branchement sur le capteur de préssion BME 280

Avant de réaliser un circuit bien penser a tester, je me suis fait un petit excès de confiance et ça m'a couté 40 balles

Pour réaliser le circuit je me suis inspiré de ça :
https://github.com/ruiqimao/keyboard-pcb-guide

Après sur l'utilisation de KiCad et LibreCad c'est long, dur, ingras.

Un peu compliqué de créer un circuit quand tu as rapidement bidouillé des Arduinos et que tu passes en mode ingenierie serieuse et définitive (20$ par essai).

la grande difficulté de ce projet c'est la maitrise des outils logiciels.

## Placer le circuit sur la grille du concertina.

Une fois le PCB crée il faut réaliser la grille en métal dans laquelle iront se loger les boutons
pour ça j'ai extrait dans un dxf le haut du boitié réalisé avec l'imprimeur 3D
une fois supprimé les détails inutils pour la grille j'ai intégré une extraction de la couche F.Skills de mon projet KiCad

## Raspberry PI
J'ai récemment réfléchie a une nouvelle solution ou le raspberry Pi centraliserais les entrées des différents arduino
via un programme python je récupere les entrées MIDI des deux Arduino
Un switch ON/Off
- ON : on envoie du son via la prise jack raspberry
- OFF : on envoie du MIDI via une prise USB

## Test
Pour tester le capteur de préssion on va essayer de voir les différentes variations de préssions a l'interieur de l'instrument
Pour cette experience j'ai mis une des anciennes mains présentes sur mon instrument d'origine et j'ai mis un boitié imprimé en 3D.
J'ai tenté de boucher les entrées / sorties d'air de la version imprimé en 3D et j'ai placé le capteur de préssion

TODO poster ici les courbes de pression


## Prix de la V3
Parlons du prix de tout ça maintenant:
### Frais déja engagés

* 3 Arduino PRO (un est deja décédé (inversion gnd et 5v sur le BME280) : EUR 15,99
* 2 capteurs de Pression BME280EUR 6,76
* 40 switchs cherry Mx : 40$
* 2 Boitiers (design + impression) : 70$
* 2 repose poignet (design + impression) : 10$
* 2 Grilles test pour validation dxf grille : 25$
* 10 PCB Grille v2.9 : 25$
* 10 PCB Grille v3.0 : 25$

### frais à Engager :
* 10 PCB Grille V3.1 : 25$
* 2 Grilles découpe laser : 50$
* 2 sangles en cuir : 30$

Soit pour l'instant 306 euros on peux distinguer le cout R&D et le cout réel de l'objet
Le prix d'un soufflet et de la mécanique soupape est exclu :

### Cout d'un concertina MIDI
* Composant electroniques
     * 2 Arduino Pro : 10$
     * 2 capteurs de Pression BME280 : 10$
     * 10 PCB Grille V3.1 : 25$
     * 30 switchs cherry Mx : 30$
     * 2 Grilles découpe laser : 50$
* Cordonnerie :
     * 2 sangles en cuir : 30$
* Impression 3D :
     * 2 Boitiers (design + impression) : 70$
     * 2 repose poignet (design + impression) : 10$
* Total : 235$

## Reflexion sur la V3.5
Le but serait ici de rajouter un raspberry, une batterie et son systeme de rechargement + gestion ON/OFF
On pourrait ainsi jouer au casque directement sur l'instrument. De plus brancher deux cables en facades en direction d'un ordinateur nous permettra d'utiliser l'instrument avec Ableton etc..

- [ ] Rechargement de la batterie
- [ ] Capacité de la batterie minimal de 5h
- [ ] Possibilité de faire On/Off sur l'alimentation
- [ ] Couper la liaison Arduino -> Raspberry quand on plug un Arduino -> PC
- [ ] que toute les prises soit sur la même face de l'hexagone.

sorties prévues en facade :
- sortie casque (output son raspberry)
- prise usb 1 (pour arduino 1)
- prise usb 2 (pour arduino 2)
- prise usb 3 pour recharge batterie du raspberry
- switch on/off pour alimentation raspberry


=?= capteur de pression=?=

- comment partager l'info du bmp 280 ?
- combien d'entrée ça prend un bmp 280 ? Réponse : 4
-> Update i2C => deux entrées
- pour avoir une valeur normative on pourrait faire un differenciel avec un autre bmp 280 placé dans le clavier
- dans les deux cas comment on fait passer la même info des deux côtés de l'instrument ?

=?= question physiques=?=

- cableries avec étanchéité ?
- Un trou de taille variable pourrait permettre de tester les influences différentes d'un trou qui simule un bouton ouvert.
- Gestion de l'air on passe de pousser/tirer a pousser/rien/tirer

=?= clavier=?=

- Boutons custom ?
https://www.massdrop.com/buy/gateron-switches
- Cercle silicon ?
- lubrification des boutons ?
- achat de clip qui se posent sur le switch avec 30% de réduction du bruit ?

=?= Couleurs=?=
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


intérèt d'imprimer une version test sans soupape du boitier imprimé en 3D
- tester et valider la forme des boites
- tester et valider les entrées et les boutons
- valider installation capteur de préssion
- tester pour savoir ce qu'on peux ajouter et comment

Dans un premier temps on fera pas de FTDI on en a besoin pour la version 3.5 qui sera elle tout embarqué


la différence avec mon projet :

- pas dematrice
- plus simple d'utiliser la footprint de l'arduin plutot que de mettre un Atmega sur la board (surtout niveau soudure)

Point d'avancement 01/02/2019 :

Le prototype de boite 3D semble parfait pour l'usage qu'on en fait j'irais chercher la deuxieme boite bientôt.
Le PCB changeant régulierement le travail sur le dessin de la grille se retrouve toujours décallé a plus tard.

<<<<<<< HEAD

BUILD LOG

Faire un journal de bord c'est se rendre compte qu'on aurais du écouter les gens qui nous ont conseillés
cependant il semble que la pin13 de l'arduino soit reconnu a l'etat LOW a cause d'une resistance et d'une LED qui y sont branchés
https://forum.arduino.cc/index.php?topic=328387.0
Visiblement il se peux que rajouter une resistance dans le circuit puisse changer la donne.
=======
Alors 13, 16 et 17 c'est des entrées de merdes qui marchent pas comme des grosses connasses
>>>>>>> a101e9a32d0ce61c1e40775b79481c0ef097a120
