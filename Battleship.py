from ast import MatchAs
from asyncio.proactor_events import BaseProactorEventLoop
from msilib.schema import File
from operator import truediv
from pydoc import plain
from re import S
from sqlite3 import Row
import string
from tkinter import LEFT, Place, Tk, Label, Button, messagebox, ttk
import tkinter,time  #,serial




Barcos_o_Misiles = True
#Variable que determina si se estan ponniendo los barcos o los misiles
#Si es True se ponen los barcos, si es False entonces se ponen los misiles

MatrizBarcos= [[0,0,0,0,0,0,0,0,0,0],
               [0,0,0,0,0,0,0,0,0,0],
               [0,0,0,0,0,0,0,0,0,0],
               [0,0,0,0,0,0,0,0,0,0]]

MatrizMisiles= [[0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0,0,0,0]]

aux=[]

score = 500

Ganar_o_Perder = False
#si es True el jugador de pc gano
#si el false el jugador de pc perdio

contador=0
#Contador de Barcos posicionados o misiles preparados 
#Maximo 10 

#Funciones


'''
#FUNCIONA EN EL ARDUINO AMICO
def enviar_posicion_Arduino(fila, columna):

    arduinoData = serial.Serial('COM3',baudrate='9600', bytesize=8)
    time.sleep(2)
    i = 1

    if(i == 1):
        sentChar = bytes(fila, 'utf-8')
        arduinoData.write(sentChar)             #La envia por el puerto serial
        i = i + 1


    if (i == 2):
        sentChar = bytes(columna, 'utf-8')
        arduinoData.write(sentChar)             #
'''

def popUp():
    if Ganar_o_Perder == True:
        messagebox.showinfo('Game Over, Gano',message='Felicidades, su puntaje es: '+ str(score))
    else:
        messagebox.showinfo('Game Over, Perdio',message='Vuelav a intentarlo, su puntaje es: '+ str(score))



class Ventana:
    def __init__(self, master):
        self.master = master
        root.geometry('700x700')
        master.title("Arduino Battleship")
        self.banner = tkinter.PhotoImage(file="Banner.gif")
        self.lbl_banner = tkinter.Label(master, image=self.banner)
        self.lbl_banner.pack()
        self.etiqueta = Label(master, text="Escoja la posicion de sus 10 barcos")
        self.etiqueta.pack()
        self.aviso = Label(master)
        self.aviso.place(x=210,y=680)
        self.puntajeTxt = Label(master,text='Score')
        self.puntajeTxt.place(x=620,y=150)
        self.puntaje = Label(master,text=(score))
        self.puntaje.place(x=620,y=165)



        def GuaradrPosicion(Fila, Columna,Letra):
            global contador
            if Barcos_o_Misiles == True:
                if contador < 10:
                    aux=MatrizBarcos[Fila]
                    if aux[Columna] == 0:
                        aux[Columna]=1
                        MatrizBarcos[Fila] = aux
                        contador +=1
                        self.aviso.configure(text="Posicion Guardada") 
                        apagarBoton(Fila,Columna)
                        #enviar_posicion_Arduino(Letra, str(Columna))
                    else:
                        self.aviso.configure(text="No puedes poner 2 Barcos en el mismo punto") 
                else:
                    self.aviso.configure(text="El numero maximo de Barcos es 10, presione listo para seguir") 
            else:
                if contador < 10:
                    aux=MatrizMisiles[Fila]
                    if aux[Columna] == 0:
                        aux[Columna]=1
                        MatrizMisiles[Fila] = aux
                        contador +=1
                        self.aviso.configure(text="Posicion Guardada")
                        apagarBoton(Fila,Columna)
                        #enviar_posicion_Arduino(Letra, str(Columna))
                    else:
                        self.aviso.configure(text="No puedes poner 2 Misiles en el mismo punto") 
                else:
                    self.aviso.configure(text="El numero maximo de Misiles es 10, presione listo para seguir") 

        def actualizarScore():
            self.puntaje.config(text=score)


        #Fila A

        self.A0 = ttk.Button(master, text="A0",command=lambda: GuaradrPosicion(0,0,'A'))
        self.A0.place(width=60,height=25,x=30,y=350)
        
        self.A1 = ttk.Button(master, text="A1",command=lambda: GuaradrPosicion(0,1,'A'))
        self.A1.place(width=60,height=25, x=95,y=350)

        self.A2 = ttk.Button(master, text="A2",command=lambda: GuaradrPosicion(0,2,'A'))
        self.A2.place(width=60,height=25, x=160,y=350)
        
        self.A3 = ttk.Button(master, text="A3",command=lambda: GuaradrPosicion(0,3,'A'))
        self.A3.place(width=60,height=25, x=225,y=350)

        self.A4 = ttk.Button(master, text="A4",command=lambda: GuaradrPosicion(0,4,'A'))
        self.A4.place(width=60,height=25, x=290,y=350)

        self.A5 = ttk.Button(master, text="A5",command=lambda: GuaradrPosicion(0,5,'A'))
        self.A5.place(width=60,height=25, x=355,y=350)

        self.A6 = ttk.Button(master, text="A6",command=lambda: GuaradrPosicion(0,6,'A'))
        self.A6.place(width=60,height=25, x=420,y=350)

        self.A7 = ttk.Button(master, text="A7",command=lambda: GuaradrPosicion(0,7,'A'))
        self.A7.place(width=60,height=25, x=485,y=350)

        self.A8 = ttk.Button(master, text="A8",command=lambda: GuaradrPosicion(0,8,'A'))
        self.A8.place(width=60,height=25, x=550,y=350)

        self.A9 = ttk.Button(master, text="A9",command=lambda: GuaradrPosicion(0,9,'A'))
        self.A9.place(width=60,height=25, x=615,y=350)

         #Fila B

        self.B0 =ttk.Button(master, text="B0",command=lambda: GuaradrPosicion(1,0,'B'))
        self.B0.place(width=60,height=25,x=30,y=380)

        self.B1 = ttk.Button(master, text="B1",command=lambda: GuaradrPosicion(1,1,'B'))
        self.B1.place(width=60,height=25, x=95,y=380)

        self.B2 = ttk.Button(master, text="B2",command=lambda: GuaradrPosicion(1,2,'B'))
        self.B2.place(width=60,height=25, x=160,y=380)
        
        self.B3 = ttk.Button(master, text="B3",command=lambda: GuaradrPosicion(1,3,'B'))
        self.B3.place(width=60,height=25, x=225,y=380)

        self.B4 = ttk.Button(master, text="B4",command=lambda: GuaradrPosicion(1,4,'B'))
        self.B4.place(width=60,height=25, x=290,y=380)

        self.B5 = ttk.Button(master, text="B5",command=lambda: GuaradrPosicion(1,5,'B'))
        self.B5.place(width=60,height=25, x=355,y=380)

        self.B6 = ttk.Button(master, text="B6",command=lambda: GuaradrPosicion(1,6,'B'))
        self.B6.place(width=60,height=25, x=420,y=380)

        self.B7 = ttk.Button(master, text="B7",command=lambda: GuaradrPosicion(1,7,'B'))
        self.B7.place(width=60,height=25, x=485,y=380)

        self.B8 = ttk.Button(master, text="B8",command=lambda: GuaradrPosicion(1,8,'B'))
        self.B8.place(width=60,height=25, x=550,y=380)

        self.B9 = ttk.Button(master, text="B9",command=lambda: GuaradrPosicion(1,9,'B'))
        self.B9.place(width=60,height=25, x=615,y=380)

         #Fila C

        self.C0 =ttk.Button(master, text="C0",command=lambda: GuaradrPosicion(2,0,'C'))
        self.C0.place(width=60,height=25,x=30,y=410)

        self.C1 = ttk.Button(master, text="C1",command=lambda: GuaradrPosicion(2,1,'C'))
        self.C1.place(width=60,height=25, x=95,y=410)

        self.C2 = ttk.Button(master, text="C2",command=lambda: GuaradrPosicion(2,2,'C'))
        self.C2.place(width=60,height=25, x=160,y=410)
        
        self.C3 = ttk.Button(master, text="C3",command=lambda: GuaradrPosicion(2,3,'C'))
        self.C3.place(width=60,height=25, x=225,y=410)

        self.C4 = ttk.Button(master, text="C4",command=lambda: GuaradrPosicion(2,4,'C'))
        self.C4.place(width=60,height=25, x=290,y=410)

        self.C5 = ttk.Button(master, text="C5",command=lambda: GuaradrPosicion(2,5,'C'))
        self.C5.place(width=60,height=25, x=355,y=410)

        self.C6 = ttk.Button(master, text="C6",command=lambda: GuaradrPosicion(2,6,'C'))
        self.C6.place(width=60,height=25, x=420,y=410)

        self.C7 = ttk.Button(master, text="C7",command=lambda: GuaradrPosicion(2,7,'C'))
        self.C7.place(width=60,height=25, x=485,y=410)

        self.C8 = ttk.Button(master, text="C8",command=lambda: GuaradrPosicion(2,8,'C'))
        self.C8.place(width=60,height=25, x=550,y=410)

        self.C9 = ttk.Button(master, text="C9",command=lambda: GuaradrPosicion(2,9,'C'))
        self.C9.place(width=60,height=25, x=615,y=410)

        #Fila D

        self.D0 =ttk.Button(master, text="D0",command=lambda: GuaradrPosicion(3,0,'D'))
        self.D0.place(width=60,height=25,x=30,y=440)

        self.D1 = ttk.Button(master, text="D1",command=lambda: GuaradrPosicion(3,1,'D'))
        self.D1.place(width=60,height=25, x=95,y=440)

        self.D2 = ttk.Button(master, text="D2",command=lambda: GuaradrPosicion(3,2,'D'))
        self.D2.place(width=60,height=25, x=160,y=440)
        
        self.D3 = ttk.Button(master, text="D3",command=lambda: GuaradrPosicion(3,3,'D'))
        self.D3.place(width=60,height=25, x=225,y=440)

        self.D4 = ttk.Button(master, text="D4",command=lambda: GuaradrPosicion(3,4,'D'))
        self.D4.place(width=60,height=25, x=290,y=440)

        self.D5 = ttk.Button(master, text="D5",command=lambda: GuaradrPosicion(3,5,'D'))
        self.D5.place(width=60,height=25, x=355,y=440)

        self.D6 = ttk.Button(master, text="D6",command=lambda: GuaradrPosicion(3,6,'D'))
        self.D6.place(width=60,height=25, x=420,y=440)

        self.D7 = ttk.Button(master, text="D7",command=lambda: GuaradrPosicion(3,7,'D'))
        self.D7.place(width=60,height=25, x=485,y=440)

        self.D8 = ttk.Button(master, text="D8",command=lambda: GuaradrPosicion(3,8,'D'))
        self.D8.place(width=60,height=25, x=550,y=440)

        self.D9 = ttk.Button(master, text="D9",command=lambda: GuaradrPosicion(3,9,'D'))
        self.D9.place(width=60,height=25, x=615,y=440)

        self.Listo = ttk.Button(master,text='Listo', command= lambda: listo())
        self.Listo.place(width=60,height=25, x=630,y=650)

        self.test = ttk.Button(master, text='Score',command= lambda: actualizarScore())
        self.test.place(x=200, y=600,width=60,height=25)

        self.test2 = ttk.Button(master, text='PopUp',command= lambda: popUp())
        self.test2.place(x=200, y=640,width=60,height=25)




        def listo():
            global contador
            global Barcos_o_Misiles
            if contador == 10:
                self.etiqueta.configure(text="Coloque las posiciones de los 10 misiles") 
                self.aviso.configure(text="")
                if Barcos_o_Misiles == True:
                    prenderBotones()
                Barcos_o_Misiles=False 
                contador=0
            else:
                self.aviso.configure(text="Debe llenar las 10 Posicionesn antes de avanzar") 




        def prenderBotones():
            self.A0.config(state='enable')
            self.A1.config(state='enable')             
            self.A2.config(state='enable')
            self.A3.config(state='enable')
            self.A4.config(state='enable')
            self.A5.config(state='enable')
            self.A6.config(state='enable')
            self.A7.config(state='enable')
            self.A8.config(state='enable')
            self.A9.config(state='enable')
            self.B0.config(state='enable')
            self.B1.config(state='enable')
            self.B2.config(state='enable')
            self.B3.config(state='enable')
            self.B4.config(state='enable')
            self.B5.config(state='enable')
            self.B6.config(state='enable')
            self.B7.config(state='enable')
            self.B8.config(state='enable')
            self.B9.config(state='enable')
            self.C0.config(state='enable')
            self.C1.config(state='enable')
            self.C2.config(state='enable')
            self.C3.config(state='enable')
            self.C4.config(state='enable')
            self.C5.config(state='enable')
            self.C6.config(state='enable')
            self.C7.config(state='enable')
            self.C8.config(state='enable')
            self.C9.config(state='enable')
            self.D0.config(state='enable')
            self.D1.config(state='enable')
            self.D2.config(state='enable')
            self.D3.config(state='enable')
            self.D4.config(state='enable')
            self.D5.config(state='enable')
            self.D6.config(state='enable')
            self.D7.config(state='enable')
            self.D8.config(state='enable')
            self.D9.config(state='enable')



        def apagarBoton(fila, columna):
            if fila == 0:
                if columna == 0:
                    self.A0.config(state='disable')
                elif columna == 1:
                    self.A1.config(state='disable')
                elif columna == 2:
                    self.A2.config(state='disable')
                elif columna == 3:
                    self.A3.config(state='disable')
                elif columna == 4:
                    self.A4.config(state='disable')
                elif columna == 5:
                    self.A5.config(state='disable')
                elif columna == 6:
                    self.A6.config(state='disable')
                elif columna == 7:
                    self.A7.config(state='disable')
                elif columna == 8:
                    self.A8.config(state='disable')
                elif columna == 9:
                    self.A9.config(state='disable')
            elif fila == 1:
                if columna == 0:
                    self.B0.config(state='disable')
                elif columna == 1:
                    self.B1.config(state='disable')
                elif columna == 2:
                    self.B2.config(state='disable')
                elif columna == 3:
                    self.B3.config(state='disable')
                elif columna == 4:
                    self.B4.config(state='disable')
                elif columna == 5:
                    self.B5.config(state='disable')
                elif columna == 6:
                    self.B6.config(state='disable')
                elif columna == 7:
                    self.B7.config(state='disable')
                elif columna == 8:
                    self.B8.config(state='disable')
                elif columna == 9:
                    self.B9.config(state='disable')
            elif fila == 2:
                if columna == 0:
                    self.C0.config(state='disable')
                elif columna == 1:
                    self.C1.config(state='disable')
                elif columna == 2:
                    self.C2.config(state='disable')
                elif columna == 3:
                    self.C3.config(state='disable')
                elif columna == 4:
                    self.C4.config(state='disable')
                elif columna == 5:
                    self.C5.config(state='disable')
                elif columna == 6:
                    self.C6.config(state='disable')
                elif columna == 7:
                    self.C7.config(state='disable')
                elif columna == 8:
                    self.C8.config(state='disable')
                elif columna == 9:
                    self.C9.config(state='disable')
            elif fila == 3:
                if columna == 0:
                    self.D0.config(state='disable')
                elif columna == 1:
                    self.D1.config(state='disable')
                elif columna == 2:
                    self.D2.config(state='disable')
                elif columna == 3:
                    self.D3.config(state='disable')
                elif columna == 4:
                    self.D4.config(state='disable')
                elif columna == 5:
                    self.D5.config(state='disable')
                elif columna == 6:
                    self.D6.config(state='disable')
                elif columna == 7:
                    self.D7.config(state='disable')
                elif columna == 8:
                    self.D8.config(state='disable')
                elif columna == 9:
                    self.D9.config(state='disable')

root = Tk()
miVentana = Ventana(root)
root.mainloop()





