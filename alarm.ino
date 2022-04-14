#include <Arduino.h>
#include "Display.h"
#include <TimerMs.h>
#include "MelodyPlayer.h"

#define DISPLAY_CLK_PIN 2
#define DISPLAY_DIO_PIN 3
#define SPEAKER_PIN 5
#define BUTTON_1_PIN 7
#define BUTTON_2_PIN 6

int hours = 8;
int minutes = 0;
int seconds = 0;
TimerMs tmr(1000, 1, 1);
Display display(DISPLAY_CLK_PIN, DISPLAY_DIO_PIN);
MelodyPlayer melodyPlayer(SPEAKER_PIN);
bool flag1 = false;
bool flag2 = false;
bool flag3 = false;

void setup() {
pinMode(BUTTON_1_PIN, INPUT);
pinMode(BUTTON_2_PIN, INPUT);
melodyPlayer.init();
  // put your setup code here, to run once:
  Serial.begin(9600);
  //tmr.setTimerMode();
  tmr.setPeriodMode();
  display.init();
}


void loop() {


bool btnState1 = !digitalRead(BUTTON_1_PIN);
  if (!btnState1 && flag1) {  // обработчик нажатия
    flag1 = false;
    hours = hours + 1;
    if (hours > 23){
      hours = 0;
    }
  }
  if (btnState1 && !flag1) {  // обработчик отпускания
    flag1 = true;  
  }
  

 bool btnState2 = !digitalRead(BUTTON_2_PIN);
  if (!btnState2 && flag2) {  // обработчик нажатия
    flag2 = false;
    minutes = minutes + 1;
    if (minutes > 59){
      minutes = 0;
      seconds=0;
    }
  }
    if (btnState2 && !flag2) {  // обработчик отпускания
    flag2 = true;  
  }

  // put your main code here, to run repeatedly:
  //Serial.println(hours);
  //Serial.println(minutes);
  //Serial.println (seconds);
if (tmr.tick()){
  seconds = seconds + 1;
  if (seconds > 59) {
    minutes = minutes + 1;
    seconds = 0;
  }
  if (minutes > 59) {
    hours = hours + 1;
    minutes = 0;
  }
  if (hours > 23) {
    hours = 0; 
  }
display.showTime(hours, minutes);
}
if (hours == 8 && minutes == 45 && !flag3){
  melodyPlayer.playStarwars(); 
  flag3 = true;
}
if (hours == 9 && minutes == 30 && !flag3){
  melodyPlayer.playStarwars(); 
  flag3 = true;
}
if (hours == 9 && minutes == 45 && !flag3){
  melodyPlayer.playStarwars(); 
  flag3 = true;
}
if (hours == 10 && minutes == 30 && !flag3){
  melodyPlayer.playStarwars(); 
  flag3 = true;
}
if (hours == 10 && minutes == 45 && !flag3){
  melodyPlayer.playStarwars(); 
  flag3 = true;
}
if (hours == 11 && minutes == 30 && !flag3){
  melodyPlayer.playStarwars(); 
  flag3 = true;
}
if (hours == 11 && minutes == 45 && !flag3){
  melodyPlayer.playStarwars(); 
  flag3 = true;
}
if (hours == 12 && minutes == 30 && !flag3){
  melodyPlayer.playStarwars(); 
  flag3 = true;
}
if (hours == 12 && minutes == 45 && !flag3){
  melodyPlayer.playStarwars(); 
  flag3 = true;
}
if (hours == 13 && minutes == 30 && !flag3){
  melodyPlayer.playStarwars(); 
  flag3 = true;
}
if (hours == 13 && minutes == 45 && !flag3){
  melodyPlayer.playStarwars(); 
  flag3 = true;
}
if (hours == 14 && minutes == 30 && !flag3){
  melodyPlayer.playStarwars(); 
  flag3 = true;
}
}
