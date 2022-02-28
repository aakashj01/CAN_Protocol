import tkinter as tk
import serial #Serial imported for Serial communication
import threading

# Create the master object
root = tk.Tk()

ArduinoSerial = serial.Serial('/dev/cu.usbmodem14201', 9600) #Create Serial port object called arduinoSerialData
root.title('can bus')
root.geometry("200x50")
def arduino_handler():
    while True:
        data = ArduinoSerial.readline().strip()
        if data.startswith(b'PotVal:'):
            potval.set(data.split(b":")[1])
        elif data.startswith(b'SwitchVal:'):
            switchval.set(data.split(b":")[1])

tk.Label(root, text="SwitchVal:").grid(row=0, column=0, sticky='w')
switchval = tk.StringVar()
tk.Label(root, textvariable=switchval).grid(row=0, column=1, sticky='w')

tk.Label(root, text="PotVal:" ).grid(row=1, column=0, sticky='w')
potval = tk.StringVar()
tk.Label(root, textvariable=potval).grid(row=1, column=1, sticky='w')

threading.Thread(target=arduino_handler, daemon=True).start()
root.mainloop()
