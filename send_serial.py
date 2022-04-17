import serial #подключаем библиотеку для последовательной связи
import time #подключаем библиотеку чтобы задействовать функции задержки в программе
import datetime #подключаем библиотеку для работы со временем

 
ArduinoSerial = serial.Serial('com6',9600) #создаем объект для работы с портом последовательной связи
time.sleep(2) #ждем 2 секунды чтобы установилась последовательная связь
now = datetime.datetime.now()
h=str(now.hour)
if len(h)==1:
   h="0"+str(now.hour)
m=str(now.minute)
if len(m)==1:
   m="0"+str(now.minute)
s=str(now.second)           
if len(s)==1:
   s="0"+str(now.second)
                
clock=h+m+s
#print (time)

with open('time_table.txt','r') as f: 
  line=f.readline()+clock  
  ArduinoSerial.write(line.encode())
  print(line)
  print("ok!")
  ArduinoSerial.close()

 
"""
while 1: #бесконечный цикл
    var = input() #считываем данные от пользователя
    print ("you entered", var) #печатаем подтверждение ввода    
    if (var == "1140"): #если значение равно 1
        ArduinoSerial.write("1140".encode()) #передаем 1
        print ("LED turned ON")
        time.sleep(1)
    
    if (var != ""): # если значение равно 0
        ArduinoSerial.write(var.encode()) #передаем 0
        print ("LED turned OFF")
        time.sleep(1)
"""
