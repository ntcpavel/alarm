// (с) Школа 1103 Звонок для учителя по расписанию
#include <Arduino.h>
#include "GyverTM1637.h"
#include <FlexiTimer2.h>
#include "MelodyPlayer.h"
#define DEBUG 0 // для отладки
#define CLK 2
#define DIO 3
#define SPEAKER_PIN 5
#define BUTTON_1_PIN 7
#define BUTTON_2_PIN 6
#define BOUNCE_DELAY 100 // время на дребезг кнопки в мс
#define MAX_LESSONS 12 // количество уроков в расписании
#define LONG_PRESS 3000 // длинное нажатие в мс
#define TIMER_PERIOD 1000 // период аппаратного таймера



byte hours = 8;
byte minutes = 0;
byte seconds = 0;
GyverTM1637 disp(CLK, DIO);
MelodyPlayer melodyPlayer(SPEAKER_PIN);
bool btnState1 = false;
bool flagBtn1Pressed = false;
bool btnState2 = false;
bool flagBtn2Pressed = false;
bool pointFlag = false;
unsigned long btn1Timer = 0; // таймер для устранения дребезга кнопки
unsigned long btn2Timer = 0; // таймер для устранения дребезга кнопки
unsigned long btn1LongTimer = 0; // таймер для длинного нажатия
String strData = ""; //полученная строка по com порту
String strData1 = ""; 
String strData2 = "";
boolean recievedFlag; // флаг получения

#if (DEBUG==1)
int cnt=0;
#endif
byte i=0; // счетчик
byte j=0; // счетчик
struct time_table {
  byte hours;
  byte minutes;
};

time_table my_time_table[MAX_LESSONS];

void setup() {
pinMode(BUTTON_1_PIN, INPUT);
pinMode(BUTTON_2_PIN, INPUT);
melodyPlayer.init();
 
  Serial.begin(9600);
  disp.clear();
  disp.brightness(7);  // яркость, 0 - 7 (минимум - максимум)
  FlexiTimer2::set(TIMER_PERIOD, timerInterupt); // установка аппаратного таймера
  FlexiTimer2::start(); // пуск аппаратного таймера

//****расписание********  
my_time_table[0].hours = 9;
my_time_table[0].minutes = 2;
my_time_table[1].hours = 9;
my_time_table[1].minutes = 30;
my_time_table[2].hours = 9;
my_time_table[2].minutes = 45;
my_time_table[3].hours = 10;
my_time_table[3].minutes = 30;
my_time_table[4].hours = 10;
my_time_table[4].minutes = 45;
my_time_table[5].hours = 11;
my_time_table[5].minutes = 30;
my_time_table[6].hours = 11;
my_time_table[6].minutes = 45;
my_time_table[7].hours = 12;
my_time_table[7].minutes = 30;
my_time_table[8].hours = 12;
my_time_table[8].minutes = 45;
my_time_table[9].hours = 13;
my_time_table[9].minutes = 30;
my_time_table[10].hours = 13;
my_time_table[10].minutes = 45;
my_time_table[11].hours = 14;
my_time_table[11].minutes = 30;
}


void loop() {

// кнопка часов синяя
 btnState1 = digitalRead(BUTTON_1_PIN);
      
  if (btnState1 && !flagBtn1Pressed && millis() - btn1Timer > BOUNCE_DELAY) {  // обработчик нажатия
    flagBtn1Pressed = true;
    hours = hours + 1;
      #if (DEBUG==1)
      cnt++;
      Serial.print("cnt=");
      Serial.println(cnt);
      #endif
    if (hours > 23){
      hours = 0;
    }
    btn1LongTimer=millis();
  }
  if (!btnState1 && flagBtn1Pressed && millis() - btn1Timer > BOUNCE_DELAY) {  // обработчик отпускания
    flagBtn1Pressed = false;
    btn1Timer = millis();
    if (millis()-btn1LongTimer>LONG_PRESS){
      show_time_table();  
    }
  }
  
// кнопка минут зеленая
  btnState2 = digitalRead(BUTTON_2_PIN);
 // Serial.print("btnState2=");
//  Serial.println(btnState2);
  if (btnState2 && !flagBtn2Pressed && millis() - btn2Timer > BOUNCE_DELAY) {  // обработчик нажатия
    flagBtn2Pressed = true;
    minutes = minutes + 1;
    if (minutes > 59){
      minutes = 0;
      seconds=0;
     }
  }
    if (!btnState2 && flagBtn2Pressed && millis() - btn2Timer > BOUNCE_DELAY) {  // обработчик отпускания
    flagBtn2Pressed = false;
    btn2Timer = millis();  
  }

  
 // Serial.println(hours);
 // Serial.println(minutes);
 // Serial.println (seconds);
 
//**** Вывод времени
 
  disp.point(pointFlag);   // выкл/выкл точки
  disp.displayClock(hours, minutes); // выводим время функцией часов


for (i=0; i<MAX_LESSONS;i++) { // проверка звонка
 if (my_time_table[i].hours ==hours &&  my_time_table[i].minutes== minutes && seconds==0){
  melodyPlayer.playStarwars(); 
  }
  }

// ****получение нового расписания по com порту

  while (Serial.available()>0){
    strData += (char)Serial.read();        // заполняем строку принятыми данными
    recievedFlag = true;                   // поднять флаг что получили данные
    delay(2);              
}

if (recievedFlag== true) {
  disp.displayInt(strData.length());
  delay(2000);  
 
for (i=0, j=0; i<MAX_LESSONS*4; i+=4,j++) {
 strData1=strData.substring(i,i+2);
 strData2=strData.substring(i+2,i+4); 
 my_time_table[j].hours=strData1.toInt();
 my_time_table[j].minutes=strData2.toInt();
}
//время
strData1=strData.substring(MAX_LESSONS*4,MAX_LESSONS*4+2);
hours=strData1.toInt();
strData1=strData.substring(MAX_LESSONS*4+2,MAX_LESSONS*4+4);
minutes=strData1.toInt();
strData1=strData.substring(MAX_LESSONS*4+4,MAX_LESSONS*4+6);
seconds=strData1.toInt();
strData = "";                          // очистить
recievedFlag = false;                  // опустить флаг
  }

}

  

  void show_time_table(){
  // показать расписание
  #if (DEBUG==1)
      Serial.println("Start");
      Serial.print("h=");Serial.print(hours);Serial.print(" m=");Serial.print(minutes); Serial.print(" s=");Serial.println(seconds);
      #endif
      byte welcome_banner[] = {_c, _l, _o, _c, _empty, _empty,
                           _t, _a, _b, _l, _e, _empty, _empty
                                                     };
  disp.runningString(welcome_banner, sizeof(welcome_banner), 200);  // 200 время в миллисекундах
  for (i=0; i<MAX_LESSONS;i++) {
  disp.displayInt(i+1);
  delay(700);
  disp.displayClock(my_time_table[i].hours, my_time_table[i].minutes);
  delay(700);
   }
  #if (DEBUG==1)
      Serial.println("End");
      Serial.print("h=");Serial.print(hours);Serial.print(" m=");Serial.print(minutes); Serial.print(" s=");Serial.println(seconds);
   #endif   
}
void  timerInterupt(){
  //прерывание аппаратного таймера
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
  pointFlag = !pointFlag;
  
  
}
