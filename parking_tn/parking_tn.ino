#include <Servo.h> 
Servo myservo_e;
Servo myservo_s;

//les variables d'entrées pour ultrason et servo
const int trig_e=43;
const int echo_e=41;
const int LR_e=48;
const int LV_e=46;

//les variables de sorties pour ultrason et servo
const int trig_s=47;
const int echo_s=49;
const int LR_s=44;
const int LV_s=42;

float d1,d2;

void setup()
{
    Serial.begin(9600);
  //déclaration des servos: servo1 dans la pin 9 de l'arduino et servo2 dans la pin 8
  myservo_e.attach(24);
  myservo_s.attach(25);
  
//déclaration des capteurs ultrason: trig comme output et echo comme INPUT
pinMode(trig_e, OUTPUT);
pinMode(echo_e, INPUT);
pinMode(trig_s, OUTPUT);
pinMode(echo_s, INPUT);

//déclaration des leds comme OUTPUT
pinMode(LR_e, OUTPUT);
pinMode(LV_e, OUTPUT);
pinMode(LR_s, OUTPUT);
pinMode(LV_s, OUTPUT);
}

// fonction qui retourne la distance mesuré par le capteur UltraSon  
long Dist_e(void){
  unsigned long t ;
  digitalWrite(trig_e,LOW);
  delayMicroseconds(20);
  digitalWrite(trig_e,HIGH);
  delayMicroseconds(50);
  digitalWrite(trig_e,LOW);
  t=pulseIn(echo_e,HIGH); // t en microseconds
  return t / 2.0 / 29.0 ;  // vitesse_du_son = 0.034 cm/microsecond = 1 / 29
}
long Dist_s(void){
  unsigned long t ;
  digitalWrite(trig_s,LOW);
  delayMicroseconds(20);
  digitalWrite(trig_s,HIGH);
  delayMicroseconds(50);
  digitalWrite(trig_s,LOW);
  t=pulseIn(echo_s,HIGH); // t en microseconds
  return t / 2.0 / 29.0 ;  // vitesse_du_son = 0.034 cm/microsecond = 1 / 29
}

void loop() {

// Gestion d'entrée
//Présence de voiture à l'entrée

d1=Dist_e();
Serial.println(d1);

if(d1>5)
{
  //etat initial -Barriere basse, Feu Rouge-
 myservo_e.write(180);
 digitalWrite(LR_e,HIGH);
 digitalWrite(LV_e,LOW);
 
}
else 
{ 
  myservo_e.write(90);
  digitalWrite(LR_e,LOW);
  digitalWrite(LV_e,HIGH);
  delay(4000);
  digitalWrite(LR_e,HIGH);
  digitalWrite(LV_e,LOW);
  delay(500);
  myservo_e.write(180);
}

// Gestion de sortie
//Présence de voiture à la sortie

d2=Dist_s();
Serial.println(d2);

if(d2>5)
{
  //etat initial -Barriere basse, Feu Rouge-

  myservo_s.write(180);
  digitalWrite(LR_s,HIGH);
  digitalWrite(LV_s,LOW);
}  
else 
{
   myservo_s.write(90);
  digitalWrite(LR_s,LOW);
  digitalWrite(LV_s,HIGH);
  delay(4000);
  digitalWrite(LR_s,HIGH);
  digitalWrite(LV_s,LOW);
  delay(500);
  myservo_s.write(180);
}
}

