import serial #подключаем библиотеку для последовательной связи
import time #подключаем библиотеку чтобы задействовать функции задержки в программе
 
ArduinoSerial = serial.Serial('com6',9600) #создаем объект для работы с портом последовательной связи
time.sleep(2) #ждем 2 секунды чтобы установилась последовательная связь
#print (ArduinoSerial.readline()) #считываем данные из последовательного порта и печатаем их в виде строки
#print ("Enter 1 to turn ON LED and 0 to turn OFF LED")
with open('time_table.txt','r') as f: 
  line=f.readline()  
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
