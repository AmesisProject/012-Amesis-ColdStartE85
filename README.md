# 012-Amesis-ColdStartE85
 Version 1.00 du document ( Vous pouvez me commander des PCB, faites vos demandes à amesisproject@gmail.com)
 
012-Amesis-ColdStartE85
Module d’aide au démarrage à froid pour les moteurs utilisant le carburant Superéthanol E85 dont la cartographie de démarrage à froid n’a pas été réglé.
Les conventions des moteurs à l’éthanol ont généralement un souci mangeur, c’est le ColdStart.

En effet, l’éthanol à son point éclaire à 7 degrés contre -40 pour le super sans plomb. Ce qui entraine donc un démarrage plus difficile voire impossible. 

Module mise au point pour le moteur de Golf IV 1.6L 16v essence passé à l’E85. Equipé du calculateur Magneti Marelli 4MV, mais peut fonctionner sur d’autre model tel quel. A vous d’analyser vos capteurs et signaux pour modifier le code.   

<img src="https://github.com/AmesisProject/012-Amesis-ColdStartE85/blob/main/Hardware/v0.01_dev/Visu/GSKZ1418.JPG" width="600" />



## I Avertissement
 
Ce module n’est nullement homologué, il sera donc fourni à but de test et non à une utilisation sur voie public.
 
Ce module modifiant le signal d’un capteur d’origine, les possibilités d’endommagement de l’ECU ou du moteur reste donc une éventualité. Vous restez seul responsable de l’utilisation de ce module. 
 
Ce module agissant sur des capteurs d’origine du véhicule pourrait entrainer des codes défaut moteur intermittent ou permanant, dans ce cas il est déconseillé de l’utiliser. 
 
Le module a pour but de décaler la plage de temperature du liquide de refroidissement ce qui correspond à des valeurs d’injection et d’allumage plus importante dans les cartographies moteur. Ces cartographies sont généralement très difficiles à modifier car le mappeur doit attendre une température adéquate pour son réglage car le moindre démarrage moteur réchauffe instantanément et rapidement le moteur du fait de la compression de l’air et de la combustion. Il faut attendre plusieurs heures afin de retenter un nouveau réglage, ce qui est parfois laborieux pour les mappeurs. 

C’est donc pour cela que ce module a été créer. 
 
De plus les cartographies de démarrage à froid « cold star » sur les calculateurs ECU Magneti Marelli 4MV sont encore un mystère dans notre communauté.

Cette documentation consterne le module en version matériel 
HW : v0.01dev et logiciel
SW Firmware : v1.031 Béta

Ce module est en version Beta, il sera donc apprécié tout retour d’information positif ou négatif à son sujet pour des nouvelle amélioration matériel et logiciel. 
Vous pouvez nous faire une proposition de modification de cade pas « Pull Requests » de GitHub ou de nous informer sur n’importe quel sujet, problème, bug et améliorations à venir, dans la partie « Issues ». Du repos GitHub du projet « 012-Amesis-ColdStartE85 »
https://github.com/AmesisProject/012-Amesis-ColdStartE85


## II Schéma de câblage
 
Type de branchement possible
Chercher et trouver la sonde de temperature du liquide de refroidissement.
 
La sonde G2 chez le groupe VAG informe la temperature au compteur.
 
La sonde G62 chez le groupe VAG informe la temperature au calculateur moteur (ECU).
 
Pour ce module c’est la sonde de temperature moteur qui nous intéresse. 
 
Ceci a été tester sur une Golf IV 1.6L 16s équipé d’un ECU Magneti Marelli. Ce qui est impotent c’est que la sonde de température du véhicule soit de type NTC c’est à dire que plus elle se réchauffe plus sa résistance réduit (plus elle se rapproche de 0.00 Ohm).
 
Le module doit être raccordé à un plus après contacte et protégé par un fusible 1A (à vérifier suivant la consommation de courant du module) :
 
1)	Sonde à 2 fils (nommer G62 chez le groupe VAG)
 <img src="https://github.com/AmesisProject/012-Amesis-ColdStartE85/blob/main/Manuel%20d'utilisation/1.png" width="600" />
 
2)	Sonde à 4 fils (nommer G2 et G62 chez lez groupe VAG, les deux sondes sont dans le même boitier)
 <img src="https://github.com/AmesisProject/012-Amesis-ColdStartE85/blob/main/Manuel%20d'utilisation/2.png" width="600" />








## III Options du module
 
  Le module est équipé des trois Pins accessible, se qui permet de sélectionner les options.
1)	 Option 1
Aucun jumpeur d’installer :
  <img src="https://github.com/AmesisProject/012-Amesis-ColdStartE85/blob/main/Manuel%20d'utilisation/3.1.png" width="600" />
Dans ce cas, le module et inactif, une fois le contacte mis, il lesse passe le signal d’origine de la sonde de temperature d’origine.

2)	Option 2
Ponter le jumpeur entre le pin 1 et le pin 2 :
   <img src="https://github.com/AmesisProject/012-Amesis-ColdStartE85/blob/main/Manuel%20d'utilisation/3.2.png" width="600" />
Dans ce cas, le module et activer. Il modifie le signal d’origine pour augmenter légèrement l’enrichissement et/ou l’allumage au démarrage.

3)	Option 3
Ponter le jumpeur entre le pin 2 et le pin 3 :
   <img src="https://github.com/AmesisProject/012-Amesis-ColdStartE85/blob/main/Manuel%20d'utilisation/3.3.png" width="600" />
Dans ce cas, le module et activer. Il modifie le signal d’origine pour augmenter moyennement l’enrichissement et/ou l’allumage au démarrage.

4)	Option 4
Ponter le jumpeur entre le pin 1, le pin 2 et le pin 3 :
   <img src="https://github.com/AmesisProject/012-Amesis-ColdStartE85/blob/main/Manuel%20d'utilisation/3.4.png" width="600" />
Dans ce cas, le module et activer. Il modifie le signal d’origine pour augmenter fortement l’enrichissement et/ou l’allumage au démarrage.
IV Fonctionnement
Une fois le contacte mis, 2 solutions :

1)	Solution 1
Le module n’a pas l’option sonde de temperature additionnelle, dans ce cas, suivant l’option engagée, le module sera actif pendant environ 1 min en modifiant le signe d’origine de manière dégressif jusqu’à atteindre la valeur d’origine après environ 1 min. Passé ce délai, le module passe en mode inactif pour laisser l’ECU d’origine faire son travail normalement.
Sans l’option la sonde de temperature additionnelle le module sera actif à chaque mis sous contacte du véhicule

2)	Solution 2
Le module est équipé de la sonde de temperature additionnelle. Celle-ci devra être placer à proximité d’une source de chaleur venant du moteur, par exemple une durite de liquide de refroidissement du circuit cour. 
La sonde de temperature additionnelle ne doit pas être installer en contacte direct avec des organes du moteur pouvant dépasser une centaine de degré sous peine de risque de détérioration de la sonde voir pire risque d’incendies. 
  <img src="https://github.com/AmesisProject/012-Amesis-ColdStartE85/blob/main/Manuel%20d'utilisation/4.png" width="600" />
  
Suivant l’option engagé, si le module a bien la sonde de temperature additionnelle, il sera en mesure de comprendre s’il est nécessaire d’activer l’enrichissement à froid suivant la temperature à la sonde de temperature additionnelle.

Pour la version du HW Firmware v1.031 béta, le seuil de d’déclanchement est approximativement en dessous des 30° de la sonde de temperature additionnelle. Si cette valeur et dépassé, alors le module passe en mode inactif car au-delà de cette temperature, le mode enrichissement à froid est inutile.
Cette valeur pourra être ajusté à la demande si besoin par une mise à jour FW.

## V Communication

Le module est pourvu d’un port USB. Il permet de communiquer avec un ordinateur pour contrôler la version du SW HW et les valeurs retournées du module car le décompte du « cold start » et option engagé.

Pour afficher ces valeurs, vous devez vous munir d’un ordinateur Windows, Mac ou Linux avec le logiciel gratuit IDE Arduino d’installer.

Dans le logiciel vous devrez choisir l‘adresse du port USB utilisé par ex :

-Sur Windows Onglet « Outils » -> « Port » -> « Port Com 4 » 

-Puis ouvrir la console de debug avec l’icône loupe en haut à droite de la fenetre du logiciel Arduino.

-Régler la vitesse sur 115200 Baud

Et les valeurs commenceront à défiler dans la fenetre.

ATTENTION Ce logiciel peut écraser les données du microcontrôleur si vous téléverser un nouveau code. 

Il faudra obligatoirement téléverser le code d’origine pour que le module refonctionne normalement.

#Don 

J'ai travaillé ennormement sur ce projet entre le code, la fabrication du PCB et les testes sur la Golf IV 1.6L essese de Mich. Me faire un don me motive pour continuer de mettre en ligne des projets gratuitement.

https://www.paypal.com/donate/?cmd=_s-xclick&hosted_button_id=R9SMSS8L6FZB2&source=url&ssrt=1681586896608

