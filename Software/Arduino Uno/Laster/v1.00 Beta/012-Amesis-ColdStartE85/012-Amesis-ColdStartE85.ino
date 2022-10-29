//    ^ ^
//  =( '')=
//  ( ")_( ") 
// Amesis Project
// 09/10/2022
// Projet : Amesis-ColdStartE85
// Version : v1.00 Beta
// Description : Ce programme a pour but de hacker une sonde de temperature de liquide de refroidissement pour que les véhicule passer a l'e85 demmarre correctement
//               Nos 1er tests seront réaliser sur une VW Golf IV 1.6L 16v.
//               Le but est de leurer le calculateur en lui faisant croie que la temperature de liquide de refroidissement est extremement froide ce qui change les valeurs
//               choisis dans les cartographie d'injection et d'allumage. 
//               Le code utilise une sonde de temperature pour adapter les valeurs en fonction de la temperature de LR et lisse progressivement le leure.
//  Option 1 : Pas de Jumpers d'installés : Le systeme fait comme si tout été d'orige, aucune resistance de ragoutée
//  Option 2 : Un Jumpeur entre 1 & 2 : ajout d'une resistance faible en plus de la sonde de LR d'origne               
//  Option 3 : Un Jumpeur entre 2 & 3 : ajout d'une resistance mayenne en plus de la sonde de LR d'origine
//  Option 4 : Les deux jumpeurs 1 & 2 & 3 : les valeur maximum sont ajouté en + de la sonde de temparature d'orige.
// Avertissement : Ce système et aucunnement omologué pour une utilisation sur voix public. Il modiffie les données constructeur et 
//                 ceci peut créer un deffaut moteur de temperature valeur de sonde dépassé et autre DTC. Voir la destruction du moteur. Comme ça vous êtes prevenue.
//                 Les valeurs de resistance peuvent être ajuster dans la fonction "void outPutResistanceLap()" dnas le Mapage. Le tebleau de correspondance est affiché en fin de code.  

#include "LapX9C10X.h" //Librairie 

int airTempPin = A7 ;            // A7 Pin de la sonde de temperature d'air 
int airTempValue ;               // Variable pour la valeur de la temperature 
int ATMin = -48 ;                // Calibration de la sonde de temperature valeur mini
int ATMax = 125 ;                // Calibration de la sonde de temperature valeur Maxi
int DTC_AT ;                     // Deffaut de la sonde de temperature
int jpOption1Pin = 10 ;          // 10 Pin pour le jumpeur 1
int jpOption1Value ;             // Variable boleene pour le Jumpeur 1
int jpOption2Pin = 12 ;          // 12 Pin pour le jumper 2
int jpOption2Value ;             // Variable boleen pour le Jumpeur 2 
int optionValue ;                // Option engagée pour l'execution du programme 1 2 3 4 
int tempo = 1000 ;               // delais d'une boucle système
int AT_Seuil = 30 ;              // Cette variable est le seuil au dessus dequel le LAP passe a 0 ohms
unsigned long coldStart = 60000 ;// Temps du ColdStart avant de basculer un valeur d'origine en ms

//Pour ce programme le module potentiometre numerique LAPX9C103 10Kohms à été choisis (Pour les autres variantes,Changez la valeur dans la ligne : LapX9C10X led(INCPIN, UDPIN, CSPIN, LAPX9C10X_X9C103);) 
//Pins de comunication entre l'arduino et le module LAPX9C103
#define CSPIN 7   // 1 - !INC - pin 7
#define INCPIN 5  // 2 - U/!D - pin 5
#define UDPIN 6   // 7 - !CS  - pin 6
LapX9C10X led(INCPIN, UDPIN, CSPIN, LAPX9C10X_X9C103); // * LAPX9C10X_X9C102(1k)  * LAPX9C10X_X9C103(10k) * LAPX9C10X_X9C503(50k) * LAPX9C10X_X9C104(100k)
int counter; //variable pour envoyer la commande au modul LAP
float resistance; //variable qui retourne l'info de la resistance choisis venant du LAP

//TO DO 
//Ces variable sont lier a le fonction void degre() qui semble très interresente pour le calibrage des sonde AirTemperature Mais pas utilisé dans cette V1.00 Beta
//Fonction pour les valeur en degré C° pour la fonction "void degre()"
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

//Initialisation du programme
void setup(){
  airTempValue = 0 ;// Initialisation
  optionValue = 0 ; // Initialisation

  pinMode (jpOption1Pin, INPUT_PULLUP) ; //Declaration de entré Jumpeur un PullUp
  pinMode (jpOption2Pin, INPUT_PULLUP) ; //Declaration de entré Jumpeur un PullUp
  
  Serial.begin(115100);  // Initialisation de la liaison serie 
  Serial.println("Demarrage du système "); 
  Serial.println("09/10/2022 Projet : Amesis-ColdStartE85  Firmware Version : v1.00 Beta ");
  delay(50); 
  led.begin(-1); // Initialisation à 0 Ohms du modul LAPX9C103
  delay(50);
}

//Demmarage du programme
void loop(){

 unsigned long currentMillis = millis(); // Enregistrement de la date pour le temps du coldStart non bloquante

 option(); // Appel a la fonction option -- Il y a 4 options dans ce programme suivant le positionnement des jumpers sur le HW / L'option 1 ne fais rien elle lesse la continuité du fils pour avoir 0 ohms
  Serial.println ("");
  Serial.print ("Option ");
  Serial.print (optionValue);
  Serial.println (" activée ");

 DTC(); //Appel a la fonction DTC
   if (DTC_AT == 1) { //Si il y a un deffaut
        Serial.println ("ColdStart DTC MODE = ON"); 
        counter = 99 ; 
        for (int i=0; i<99; i++) { // Incrementation de 99 car le LAP a une plage de 0 à 99
              counter = counter - 1 ; // on enlève 1 a counter pour rappel counter 99 = 100K ohms 0 = 0 ohm (voire tableau en fin de code)
              Serial.print ("Le counter = ") ;
              Serial.println (counter) ;
              led.set(counter);
              delay (coldStart/60) ; // delay pour la boucle for en fonction du delay du coldStart choisi dans la declaration des variables
             }
        for (int j=0; j<1;){ // boucle for pour verouiller la boucle et ne plus en sortir.
              Serial.println ("ColdStart DTC MODE = OVER");
              counter = 0 ;  
              led.set(counter);
              delay (1000);
        }
        
 }
 else if (currentMillis < coldStart){
  Serial.println ("ColdStart = ON");

 outPutResistanceLap(); // Appel de la fonction 
  Serial.print ("une résistance de sortie de Lap est de ");
  Serial.print (led.getK());
  Serial.println (" Khoms");
 }
  else {
    Serial.println ("ColdStart = OFF");
  int counter;      // Le int sert pour le microcontroleur du modul LAPX9C10X_X9C103
  float resistance; // Le float sert pour le microcontroleur du modul LAPX9C10X_X9C103
  counter = 0 ;     //On ecrit la valeur du counter de 0 à 99 Mapé 0 Ohms à 10K Ohms(Voire tableau de correspondance en bas de code)
    led.set(counter);
    Serial.print ("Le programme ce deroule sans ajout, la resistance du Lap de ");
    Serial.print (led.getK());
    Serial.println ("Khoms");
  }
  Serial.print ("Il s'est écoulé ");
  Serial.print (currentMillis / 1000); 
  Serial.println ("s depuis le contacte mis");
  Serial.println ("_____________________________________________________");
  delay(tempo);
}

void option(){

  // Pin entré pour jumper
  jpOption1Value = digitalRead(jpOption1Pin) ;
  jpOption2Value = digitalRead(jpOption2Pin) ;

  if (jpOption1Value == LOW & jpOption2Value == LOW) {// Option 4 Avec les 2 jumpeurs d'installé entre 1 & 2 et 2 & 3
     //Serial.println ("Option 4 +++ ");
     optionValue = 4 ;
       } 

 else if (jpOption2Value == LOW ) {// Option 3 Avec le jumpeur entre 2 & 3
       // Serial.println ("Option 3 ++ ");
        optionValue = 3 ;
       }        
                          
 else if (jpOption1Value == LOW ) {
        //Serial.println ("Option 2 + ");// Option 1 Avec le jumper entre 1 & 2
        optionValue = 2 ;
       }

 else if (jpOption1Value == HIGH & jpOption2Value == HIGH) {
        //Serial.println ("Option 1 ");
        optionValue = 1 ; // Option 0 Sans jumper

       }  
       return (optionValue);
}

void outPutResistanceLap(){
 //Sonde airTemp ext 
 //degre();
 airTempValue = analogRead(airTempPin); //airTempValue enregistre la valeur du Pin
 airTempValue = map(airTempValue, 0, 1023, ATMin, ATMax); // Regler les deux dernier chiffre avec la valeur constructeur de la sonde airTemp min max pour ATMin ATMax dans la declaration des variable

  Serial.print ("La temperature exterieur est de ");
  Serial.print (airTempValue); //Affiche sur le port serie la valeur de la variable
  Serial.println ("C° ");
  
  //int counter;      // Le int sert pour le microcontroleur du modul LAPX9C10X_X9C103
  //float resistance; // Le float sert pour le microcontroleur du modul LAPX9C10X_X9C103
         if (optionValue  == 4){ //Si Option 4 est enclanchée 
               if (airTempValue <= 0) { counter = 99 ; }   //sinon on met au max de l'option 4    
          else if (airTempValue > 0 && airTempValue < AT_Seuil) {counter = map(airTempValue, ATMin, ATMax, 99, 69);} //on mets le counter mapé avec les valeurs entre ()
          else if (airTempValue >= AT_Seuil) { counter = 0  ; }   //Sinon on met le LAP à 0 ohms   Cette ligne peut être commenté pour ne pas limité 
           }

    else if (optionValue  == 3){ //Si Option 3 est enclanchée 
               if (airTempValue <= 0) { counter = 69 ; }          //sinon on met au mac de l'option 3 
          else if (airTempValue > 0 && airTempValue < AT_Seuil) {counter = map(airTempValue, ATMin, ATMax, 69, 39);} //on mets le counter mapé avec les valeurs entre ()
          else if (airTempValue >= AT_Seuil) { counter = 0  ; }   //Sinon on met le LAP à 0 ohms   Cette ligne peut être commenté pour ne pas limité   
          } 

    else if (optionValue  == 2){ //Si Option 2 est enclanchée
               if (airTempValue <= 0) { counter = 39 ; }         //sinon on met au mac de l'option 2 
          else if (airTempValue > 0 && airTempValue < AT_Seuil) {counter = map(airTempValue, ATMin, ATMax, 39, 9);} //on mets le counter mapé avec les valeurs entre ()
          else if (airTempValue >= AT_Seuil) { counter = 0  ; }   //Sinon on met le LAP à 0 ohms   Cette ligne peut être commenté pour ne pas limité   
          }

    else if (optionValue  == 1) {counter = 0 ;} //Si Option 1 est enclanchée on mets le counter a 0 ce qui équivau a une resistance du Lap de 0 ohms

  Serial.print("Le counter = ");
  Serial.print(counter);
  led.set(counter); //On envoie la variable au module LAP
  Serial.println(" ce qui équiveau à ");
  return (led.getK());
}

void degre (){// Cette fonction n'est pas exploitée pour le moment 

  Vo = analogRead(airTempPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  airTempValue = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  airTempValue = airTempValue - 273.15;
 // airTempValue = (airTempValue * 9.0)/ 5.0 + 32.0; 
  //delay(10);

  return(airTempValue);

}

void DTC(){
       if (airTempValue == ATMin) {DTC_AT = 1 ;} //Si la valeur min à été ateinte alor deffaut 
  else if (airTempValue == ATMax) {DTC_AT = 1 ;} //Si la valeur max à été ateinte alor deffaut 
  else {DTC_AT = 0 ;}                            //Sinon pas de deffaut

  Serial.print ("DTC = ");
  Serial.println (DTC_AT);

 return (DTC_AT);
}

/** Tableau de correspondance :
01:14:21.757 -> Starting, set to minimum resistance
01:14:26.820 -> Using absolute counter changes
01:14:26.820 -> Increasing, counter = 0, new resistance = 0.00KOhms
01:14:26.914 -> Increasing, counter = 1, new resistance = 0.10KOhms
01:14:27.007 -> Increasing, counter = 2, new resistance = 0.20KOhms
01:14:27.100 -> Increasing, counter = 3, new resistance = 0.30KOhms
01:14:27.240 -> Increasing, counter = 4, new resistance = 0.40KOhms
01:14:27.333 -> Increasing, counter = 5, new resistance = 0.51KOhms
01:14:27.425 -> Increasing, counter = 6, new resistance = 0.61KOhms
01:14:27.518 -> Increasing, counter = 7, new resistance = 0.71KOhms
01:14:27.612 -> Increasing, counter = 8, new resistance = 0.81KOhms
01:14:27.749 -> Increasing, counter = 9, new resistance = 0.91KOhms
01:14:27.841 -> Increasing, counter = 10, new resistance = 1.01KOhms
01:14:27.935 -> Increasing, counter = 11, new resistance = 1.11KOhms
01:14:28.030 -> Increasing, counter = 12, new resistance = 1.21KOhms
01:14:28.123 -> Increasing, counter = 13, new resistance = 1.31KOhms
01:14:28.216 -> Increasing, counter = 14, new resistance = 1.41KOhms
01:14:28.356 -> Increasing, counter = 15, new resistance = 1.52KOhms
01:14:28.449 -> Increasing, counter = 16, new resistance = 1.62KOhms
01:14:28.540 -> Increasing, counter = 17, new resistance = 1.72KOhms
01:14:28.634 -> Increasing, counter = 18, new resistance = 1.82KOhms
01:14:28.727 -> Increasing, counter = 19, new resistance = 1.92KOhms
01:14:28.864 -> Increasing, counter = 20, new resistance = 2.02KOhms
01:14:28.957 -> Increasing, counter = 21, new resistance = 2.12KOhms
01:14:29.050 -> Increasing, counter = 22, new resistance = 2.22KOhms
01:14:29.144 -> Increasing, counter = 23, new resistance = 2.32KOhms
01:14:29.238 -> Increasing, counter = 24, new resistance = 2.42KOhms
01:14:29.331 -> Increasing, counter = 25, new resistance = 2.53KOhms
01:14:29.471 -> Increasing, counter = 26, new resistance = 2.63KOhms
01:14:29.564 -> Increasing, counter = 27, new resistance = 2.73KOhms
01:14:29.658 -> Increasing, counter = 28, new resistance = 2.83KOhms
01:14:29.753 -> Increasing, counter = 29, new resistance = 2.93KOhms
01:14:29.845 -> Increasing, counter = 30, new resistance = 3.03KOhms
01:14:29.984 -> Increasing, counter = 31, new resistance = 3.13KOhms
01:14:30.078 -> Increasing, counter = 32, new resistance = 3.23KOhms
01:14:30.172 -> Increasing, counter = 33, new resistance = 3.33KOhms
01:14:30.263 -> Increasing, counter = 34, new resistance = 3.43KOhms
01:14:30.357 -> Increasing, counter = 35, new resistance = 3.54KOhms
01:14:30.452 -> Increasing, counter = 36, new resistance = 3.64KOhms
01:14:30.591 -> Increasing, counter = 37, new resistance = 3.74KOhms
01:14:30.684 -> Increasing, counter = 38, new resistance = 3.84KOhms
01:14:30.775 -> Increasing, counter = 39, new resistance = 3.94KOhms
01:14:30.867 -> Increasing, counter = 40, new resistance = 4.04KOhms
01:14:30.960 -> Increasing, counter = 41, new resistance = 4.14KOhms
01:14:31.098 -> Increasing, counter = 42, new resistance = 4.24KOhms
01:14:31.191 -> Increasing, counter = 43, new resistance = 4.34KOhms
01:14:31.285 -> Increasing, counter = 44, new resistance = 4.44KOhms
01:14:31.378 -> Increasing, counter = 45, new resistance = 4.55KOhms
01:14:31.472 -> Increasing, counter = 46, new resistance = 4.65KOhms
01:14:31.610 -> Increasing, counter = 47, new resistance = 4.75KOhms
01:14:31.703 -> Increasing, counter = 48, new resistance = 4.85KOhms
01:14:31.797 -> Increasing, counter = 49, new resistance = 4.95KOhms
01:14:31.889 -> Increasing, counter = 50, new resistance = 5.05KOhms
01:14:31.982 -> Increasing, counter = 51, new resistance = 5.15KOhms
01:14:32.119 -> Increasing, counter = 52, new resistance = 5.25KOhms
01:14:32.210 -> Increasing, counter = 53, new resistance = 5.35KOhms
01:14:32.304 -> Increasing, counter = 54, new resistance = 5.45KOhms
01:14:32.400 -> Increasing, counter = 55, new resistance = 5.56KOhms
01:14:32.494 -> Increasing, counter = 56, new resistance = 5.66KOhms
01:14:32.588 -> Increasing, counter = 57, new resistance = 5.76KOhms
01:14:32.727 -> Increasing, counter = 58, new resistance = 5.86KOhms
01:14:32.818 -> Increasing, counter = 59, new resistance = 5.96KOhms
01:14:32.912 -> Increasing, counter = 60, new resistance = 6.06KOhms
01:14:33.007 -> Increasing, counter = 61, new resistance = 6.16KOhms
01:14:33.100 -> Increasing, counter = 62, new resistance = 6.26KOhms
01:14:33.194 -> Increasing, counter = 63, new resistance = 6.36KOhms
01:14:33.333 -> Increasing, counter = 64, new resistance = 6.46KOhms
01:14:33.428 -> Increasing, counter = 65, new resistance = 6.57KOhms
01:14:33.519 -> Increasing, counter = 66, new resistance = 6.67KOhms
01:14:33.612 -> Increasing, counter = 67, new resistance = 6.77KOhms
01:14:33.704 -> Increasing, counter = 68, new resistance = 6.87KOhms
01:14:33.842 -> Increasing, counter = 69, new resistance = 6.97KOhms
01:14:33.935 -> Increasing, counter = 70, new resistance = 7.07KOhms
01:14:34.027 -> Increasing, counter = 71, new resistance = 7.17KOhms
01:14:34.120 -> Increasing, counter = 72, new resistance = 7.27KOhms
01:14:34.212 -> Increasing, counter = 73, new resistance = 7.37KOhms
01:14:34.351 -> Increasing, counter = 74, new resistance = 7.47KOhms
01:14:34.444 -> Increasing, counter = 75, new resistance = 7.58KOhms
01:14:34.538 -> Increasing, counter = 76, new resistance = 7.68KOhms
01:14:34.630 -> Increasing, counter = 77, new resistance = 7.78KOhms
01:14:34.724 -> Increasing, counter = 78, new resistance = 7.88KOhms
01:14:34.863 -> Increasing, counter = 79, new resistance = 7.98KOhms
01:14:34.954 -> Increasing, counter = 80, new resistance = 8.08KOhms
01:14:35.046 -> Increasing, counter = 81, new resistance = 8.18KOhms
01:14:35.139 -> Increasing, counter = 82, new resistance = 8.28KOhms
01:14:35.233 -> Increasing, counter = 83, new resistance = 8.38KOhms
01:14:35.326 -> Increasing, counter = 84, new resistance = 8.48KOhms
01:14:35.464 -> Increasing, counter = 85, new resistance = 8.59KOhms
01:14:35.557 -> Increasing, counter = 86, new resistance = 8.69KOhms
01:14:35.649 -> Increasing, counter = 87, new resistance = 8.79KOhms
01:14:35.742 -> Increasing, counter = 88, new resistance = 8.89KOhms
01:14:35.835 -> Increasing, counter = 89, new resistance = 8.99KOhms
01:14:35.975 -> Increasing, counter = 90, new resistance = 9.09KOhms
01:14:36.069 -> Increasing, counter = 91, new resistance = 9.19KOhms
01:14:36.163 -> Increasing, counter = 92, new resistance = 9.29KOhms
01:14:36.257 -> Increasing, counter = 93, new resistance = 9.39KOhms
01:14:36.350 -> Increasing, counter = 94, new resistance = 9.49KOhms
01:14:36.444 -> Increasing, counter = 95, new resistance = 9.60KOhms
01:14:36.584 -> Increasing, counter = 96, new resistance = 9.70KOhms
01:14:36.675 -> Increasing, counter = 97, new resistance = 9.80KOhms
01:14:36.767 -> Increasing, counter = 98, new resistance = 9.90KOhms
01:14:36.860 -> Increasing, counter = 99, new resistance = 10.00KOhms
*/
