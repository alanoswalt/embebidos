

import serial
import tkinter as t
from tkinter import ttk
import threading
import time


class House(t.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.pack()
        
        self.updateInfo =t.StringVar()
        self.updateTemp = "Temp: 0C"
        self.updateMaxTempTh = "MaxTempTh: 200C"
        self.updateMinTempTh = "MinTempTh: 100C"
        self.updateMaxTempRec = "MaxTemp: off"
        self.updateMinTempRec = "MinTemp: off"
        
        self.receiving = True
        
        self.max_temp= 200
        self.min_temp= 100
        self.max_temp_str = t.StringVar()
        self.min_temp_str = t.StringVar()
        
        self.intensityBar = ttk.Progressbar(self,length=200)
        self.barValue = 0
        self.barPercentage = t.StringVar()
        self.updateLedIntensityIncr = False
        self.updateLedIntensityDecr = False
        
        self.buildWin()
        
        self.t1 = ""
    
    
        #despues de crear la GUI estar a la espera de llegada de actualizacion de informacion
        #self.update()
    
    def disconnect(self):
        self.receiving = False
        self.ser.close()
        self.t1.join()
    
    def update(self):
        while(self.receiving):
    
                receive_word = str(self.ser.readline())[2:-5]
                #print(receive_word)
                if receive_word[:4] == "Temp":
                    if receive_word[6]=="0":
                        self.updateTemp = receive_word[:6]+receive_word[7:]
                    else:
                        self.updateTemp =receive_word
                elif receive_word[:9] == "MinTempTh":
                    if receive_word[11] == "0":
                        self.updateMinTempTh =  receive_word[:11]+receive_word[12:]
                        self.min_temp_str.set(self.updateMinTempTh[-3:-1])
                    else:
                        self.updateMinTempTh = receive_word
                        self.min_temp_str.set(self.updateMinTempTh[-4:-1])
                elif receive_word[:9] == "MaxTempTh":
                    self.updateMaxTempTh = receive_word
                    self.max_temp_str.set(self.updateMaxTempTh[-4:-1])
                elif receive_word[:7] == "MinTemp":
                    self.updateMinTempRec = receive_word
                
                elif receive_word[:7] == "MaxTemp":
                    self.updateMaxTempRec = receive_word
                
                elif receive_word[:3] == "okq":
                    self.intensityBar["value"]= self.barValue
                    if self.barValue == 99:
                        self.barValue = 100;
                    self.barPercentage.set(str(self.barValue)+"%")
                
                elif receive_word[:3] == "okw":
                    self.intensityBar["value"] = self.barValue
                    self.barPercentage.set(str(self.barValue)+"%")
                else:
                    continue
                

                self.updateInfo.set(self.updateTemp+"\n"+self.updateMaxTempTh+", "+self.updateMinTempTh+"\n"+self.updateMaxTempRec+", "+self.updateMinTempRec)
    
    def buildWin(self):
        self.master.title("House")
        self.master.geometry('370x300')
        
        for c in range(6):
            self.columnconfigure(c)
        for r in range(6):
            self.rowconfigure(r, weight=1)
        
        #Pantalla para mostrar la temperatura
       
        self.updateInfo.set(self.updateTemp+"\n"+self.updateMaxTempTh+", "+self.updateMinTempTh+"\n"+self.updateMaxTempRec+", "+self.updateMinTempRec)
        t.Label(self, textvariable=self.updateInfo, font="Calibri 16 bold", justify=t.LEFT).grid(row=1,column=0, columnspan=6,sticky=t.W)
        
        #Interfaz para Max Temp Threshold
        t.Button(self, text="+", command=lambda:self.stepperMaxTemp(1)).grid(row=3, column=0,ipadx=15,ipady=10)
        t.Button(self, text="-", command=lambda:self.stepperMaxTemp(-1)).grid(row=3,column=1,ipadx=15,ipady=10)
        t.Label(self, text="Max Temp Threshold: ").grid(row=3, column=3)
        self.max_temp_str.set("200")
        t.Entry(self,textvariable= self.max_temp_str, width=6).grid(row=3, column=4)
        t.Button(self, text="Set", command= lambda:self.changeMaxTemp(self.max_temp_str.get())).grid(row=3, column=5,ipadx=15,ipady=10)
        
        #Interfaz para Min Temp Threshold
        t.Button(self, text="+", command=lambda:self.stepperMinTemp(1)).grid(row=4, column=0,ipadx=15,ipady=10)
        t.Button(self, text="-", command=lambda:self.stepperMinTemp(-1)).grid(row=4,column=1,ipadx=15,ipady=10)
        t.Label(self, text="Min Temp Threshold: ").grid(row=4, column=3)
        self.min_temp_str.set("100")
        t.Entry(self,textvariable= self.min_temp_str, width=6).grid(row=4, column=4)
        
        t.Button(self, text="Set", command= lambda:self.changeMinTemp(self.min_temp_str.get())).grid(row=4, column=5,ipadx=15,ipady=10)
    
        #interfaz para el dimmer
        t.Button(self, text="+", command=self.incrIntensity).grid(row=5, column=0,ipadx=15,ipady=10)
        t.Button(self, text="-", command=self.decrIntensity).grid(row=5,column=1,ipadx=15,ipady=10)
        self.intensityBar.grid(row=5, column=2, columnspan=3,sticky=t.W, padx=10)
        self.barPercentage.set("0%")
        t.Label(self, textvariable=self.barPercentage).grid(row=5, column=5)
        
        def startReceiving():
                self.ser = serial.Serial('/dev/tty.usbserial-1A1220', timeout=10)  # open serial port
                print(self.ser.name)
                self.receiving = True
                self.t1 = threading.Thread(target = self.update)
                self.t1.daemon = True
                self.t1.start()
        
                                                            
        #boton de encendido
        t.Button(self, text="On", command=startReceiving).grid(row=6, column=0, ipadx=15, ipady=10, columnspan=2)
        #boton de apagado
        t.Button(self, text="Off", command=self.disconnect).grid(row=6, column=2, ipadx=15, ipady=10, columnspan=2)
                                                            
            
    def sendCommand(self, command, value):
        self.ser.write(value)
        self.ser.write(command)

    def stepperMaxTemp(self, step):
        self.max_temp+=step
        
        #enviar al micro la actualizacion
        self.sendCommand(b'x',bytes(str(self.max_temp),'utf-8'))
        #y esperar una respuesta para poder refrescar la GUI
        
    
    def changeMaxTemp(self, value):
        try:
            max = int(value)
        except ValueError:
            self.max_temp_str.set(self.updateMaxTempTh[-4:-1])
            return
        
        self.max_temp = max
        #enviar al micro la actualizacion
        self.sendCommand(b'x',bytes(str(self.max_temp),'utf-8'))
        #y esperar una respuesta para poder refrescar la GUI
        
    
    def stepperMinTemp(self, step):
        self.min_temp+=step
        
        #enviar al micro la actualizacion
        self.sendCommand(b'n',bytes(str(self.min_temp),'utf-8'))
        #y esperar una respuesta para poder refrescar la GUI
        
    
    def changeMinTemp(self, value):
        try:
            min = int(value)
        except ValueError:
            self.min_temp_str.set(self.updateMinTempTh[-4:-1])
            return
        
        self.min_temp= min
        #enviar al micro la actualizacion
        self.sendCommand(b'n',bytes(str(self.min_temp),'utf-8'))
        #y esperar una respuesta para poder refrescar la GUI
        

    def incrIntensity(self):
        self.barValue+=10
    
        if self.barValue == 100:
            self.barValue = 99
        elif self.barValue > 100:
            self.barValue = 0
                
        #enviar al micro la actualizacion
        self.sendCommand(b'q',bytes(str(self.barValue),'utf-8'))
        #y esperar una respuesta para poder refrescar la GUI


    def decrIntensity(self):
        self.barValue-=10
        
        if self.barValue < 0:
            self.barValue = 0
    
        #enviar al micro la actualizacion
        self.sendCommand(b'w',bytes(str(self.barValue),'utf-8'))
        #y esperar una respuesta para poder refrescar la GUI


def main():
    root = t.Tk()
    smart_house = House(root)
    smart_house.mainloop()
if __name__ =="__main__":
    main()


'''
    
    ser = serial.Serial('COM3', timeout=2)  # open serial port
    print(ser.name)         # check which port was really used
    ser.write(b'x')
    print(ser.readline())
    print(ser.readline())
    ser.write(b'123\r\n')     # write a string
    #name = ser.readline()
    #print(name)
    ser.close()
    '''

