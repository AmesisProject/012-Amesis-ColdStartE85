//   ^ ^
// =( °°)=
// (")_(") 
// Amesis Project
// 29/09/2022
// Projet : 
// Version : v0.01

#include <LapX9C10X.h>

/* This example assumes you're using an X9C103 (10k) chip. For other variants,
 * Change the value in the line : LapX9C10X led(INCPIN, UDPIN, CSPIN, LAPX9C10X_X9C103);

 * The chip is connected to the Arduino like this:
 * (! indicates that the thing following has a line over the top, called a bar.)
 *   
 * The other pins on the chip must be wired like this:
 * 8 - VCC - 5/3.3V
 * 3 - VH  - 5/3.3V
 * 4 - VSS - GND
 * 6 - VL  - GND
 * 5 - VW  - Output: 680 Ohm resistor to an LED, the other terminal
 *           of the LED connected to GND This value may seem high,
 *           but the maximum steady state wiper current of the chip
 *           is 4.4mA (8.8mA peak for 10 seconds). 680 Ohms - assuming
 *           a 5V supply, and an LED forward voltage drop of 2V, gives 
 *           us almost dead on 4.4mA worst case current (when the wiper
 *           is at the top).
 *           If you want to get the brightest you can, use this formula
 *           for the resistor value (in kilohms), where VCC is the 
 *           supply voltage, and VLED is the LED forward voltage drop:
 *                R = (VCC - VLED) 
 *                    ------------
 *                        4.4
 * If you use different pins, just change the defines below
 */

#define CSPIN 7   // 1 - !INC - pin 7
#define INCPIN 5  // 2 - U/!D - pin 5
#define UDPIN 6   // 7 - !CS  - pin 6

LapX9C10X led(INCPIN, UDPIN, CSPIN, LAPX9C10X_X9C103); // * LAPX9C10X_X9C102(1k)  * LAPX9C10X_X9C103(10k) * LAPX9C10X_X9C503(50k) * LAPX9C10X_X9C104(100k)

void setup() {
  Serial.begin(115100); 
  Serial.println("Starting, set to minimum resistance");  
  led.begin(-1); // Initialisation à 0 Ohms 
  delay(5000);
}

void loop() {
  int counter;      // Le int sert pour le microcontroleur du modul LAPX9C10X_X9C103
  float resistance; // Le float sert pour le microcontroleur du modul LAPX9C10X_X9C103
  
  Serial.println("Using absolute counter changes");  
  counter = 0;     //On ecrit la valeur du counter de 0 à 99 Mapé 0 Ohms à 10K Ohms(Voire tableau de correspondance en bas de code)
    Serial.print("Increasing, counter = ");
    Serial.print(counter);
    led.set(counter);
    Serial.print(", new resistance = ");
    Serial.print(led.getK());
    Serial.println("KOhms");
    delay(5000);

  Serial.println("Using absolute counter changes");  
  counter = 50;
    Serial.print("Increasing, counter = ");
    Serial.print(counter);
    led.set(counter);
    Serial.print(", new resistance = ");
    Serial.print(led.getK());
    Serial.println("KOhms");
    delay(5000);

  Serial.println("Using absolute counter changes");  
  counter = 99;
    Serial.print("Increasing, counter = ");
    Serial.print(counter);
    led.set(counter);
    Serial.print(", new resistance = ");
    Serial.print(led.getK());
    Serial.println("KOhms");
    delay(5000);
  
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