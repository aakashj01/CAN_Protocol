from tkinter import *
import serial
import threading
import time

master = Tk()

ArduinoSerial = serial.Serial('/dev/cu.usbmodem14201', 9600)

def swi():
    global prev_potstate


    ArduinoSerial.write(prev_potstate.encode())
    print(prev_potstate)
    time.sleep(1.5)

    global prev_state

    if prev_state==0:
        print('1')
        ArduinoSerial.write(b'1')
        prev_state=1
    else:
        print('0')
        ArduinoSerial.write(b'0')
        prev_state=0
    time.sleep(1)

def sendPotVal(i):
    global prev_potstate
    prev_potstate=i
    ArduinoSerial.write(bytes(i,'utf-8'))
    print(i)
    time.sleep(1.5)

    global prev_state


    if prev_state==0:
        print('0')
        ArduinoSerial.write(b'0')
        
    else:
        print('1')
        ArduinoSerial.write(b'1')

    time.sleep(1)



if __name__ == "__main__":

    prev_state=0
    master.geometry("200x100")
    master.title('can bus')


    w = Scale(master, from_=1, to=256,label='pot:', orient=HORIZONTAL,command=sendPotVal)
    i=w.get()
    w.pack()

    chk=Button(master, text='switch',command=swi)

    chk.pack()

    mainloop()
