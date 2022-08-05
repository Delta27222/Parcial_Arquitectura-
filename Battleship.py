from ast import MatchAs
from asyncio.proactor_events import BaseProactorEventLoop
from msilib.schema import File
from operator import truediv
from pydoc import plain
from re import S
from sqlite3 import Row
import string
from tkinter import LEFT, Place, Tk, Label, Button, messagebox, ttk
import tkinter,time  ,serial
from turtle import delay


from tkinter import *
from tkinter.messagebox import *
import threading
#from PIL import ImageTk, Image

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

score = 0 #puntaje del player de pc

Ganar_o_Perder = False
#si es True el jugador de pc gano
#si el false el jugador de pc perdio

contadorPeleas=0 #cantidad de ataques con misiles realizados

contador=0 #contador de posiciones colocadas y guardadas en las matrices

num_Ataque = 0
#Contador de Barcos posicionados o misiles preparados 
#Maximo 10 


contExtra = 0

arduinoData = serial.Serial('COM3',baudrate='9600', bytesize=8)

comienzoAngel = 0

counter_barco = 1



def popUp():
    if Ganar_o_Perder == True:
        messagebox.showinfo('Game Over, Gano',message='Felicidades, su puntaje es: '+ str(score))
    else:
        messagebox.showinfo('Game Over, Perdio',message='Vuelva a intentarlo, su puntaje es: '+ str(score))



class Ventana:
    def __init__(self, master):
        self.master = master
        root.geometry('700x700')
        root.resizable(width=False, height=False)
        root.configure(background='gray')

        self.bienvenida = tkinter.Label(master,text="Bienvenido a Batalla Naval!!")
        self.bienvenida.pack(anchor=CENTER)
        self.bienvenida.config(font=("Arial",20), background="gray")

        master.title("Arduino Battleship")
        self.banner = tkinter.PhotoImage(file="Banner.gif")
        self.lbl_banner = tkinter.Label(master, image=self.banner)
        self.lbl_banner.pack()
        self.etiqueta = Label(master, text="Cargando Barcos")
        self.etiqueta.config(font=("Arial",15), background="gray",foreground="blue")
        self.etiqueta.pack()
        self.aviso = Label(master)
        self.aviso.configure(font=("Arial",10), background="gray", foreground="red")
        self.aviso.place(x=435,y=327)
        self.puntajeTxt = Label(master,text='Score')
        self.puntajeTxt.place(x=620,y=150)
        self.puntajeTxt.config(font=("Arial",15), background="gray",foreground="blue")
        self.puntaje = Label(master,text=(score))
        self.puntaje.place(x=620,y=175)
        self.puntaje.config(font=("Arial",12), background="gray", foreground="blue")

        self.numAtaqueLabel = Label(master,text='Ataques')
        self.numAtaqueLabel.place(x=620,y=210)
        self.numAtaqueLabel.config(font=("Arial",15), background="gray",foreground="blue")
        self.numAtaque = Label(master,text=(contadorPeleas))
        self.numAtaque.place(x=620,y=235)
        self.numAtaque.config(font=("Arial",12), background="gray", foreground="blue")


        def GuaradrPosicion(Fila, Columna,Letra):
            global contador
            if Barcos_o_Misiles == True:
                if contador < 10:
                    aux=MatrizBarcos[Fila]
                    if aux[Columna] == 0:
                        aux[Columna]=1
                        MatrizBarcos[Fila] = aux
                        contador +=1
                        self.aviso.configure(text="Coordenada agregada!",font=("Arial",10), background="gray", foreground="red")
                        t = threading.Timer(1, update_label)   #Ejecuta la funcion de "update_label" despues de 0.7seg
                        t.start()

                        apagarBoton(Fila,Columna)
                        enviar_posicion_Arduino(Letra, Columna)
                    else:
                        self.aviso.configure(text="Coordenada repetida!")
                        t = threading.Timer(0.7, update_label)   #Ejecuta la funcion de "update_label" despues de 0.7seg
                        t.start()
                else:
                    self.aviso.configure(text="Maximo 10 barcos!")
                    t = threading.Timer(0.7, update_label)   #Ejecuta la funcion de "update_label" despues de 0.7seg
                    t.start()
            else:
                if contador < 10:
                    aux=MatrizMisiles[Fila]
                    if aux[Columna] == 0:
                        aux[Columna]=1
                        MatrizMisiles[Fila] = aux
                        contador +=1
                        self.aviso.configure(text="Coordenada agregada!",font=("Arial",10), background="gray", foreground="red")
                        t = threading.Timer(0.7, update_label)   #Ejecuta la funcion de "update_label" despues de 0.7seg
                        t.start()
                        apagarBoton(Fila,Columna)
                        enviar_posicion_Arduino(Letra, str(Columna))
                    else:
                        self.aviso.configure(text="Coordenada repetida!")
                        t = threading.Timer(0.7, update_label)   #Ejecuta la funcion de "update_label" despues de 0.7seg
                        t.start()
                else:
                    self.aviso.configure(text="Maximo 10 misiles!")
                    t = threading.Timer(0.7, update_label)   #Ejecuta la funcion de "update_label" despues de 0.7seg
                    t.start()

        def actualizarScore():
            dataPacket = arduinoData.readline()
            dataPacket = str(dataPacket, 'utf-8')
            print(dataPacket)
            score = int(dataPacket)
            self.puntaje.config(text=score)

        def update_label():
            self.aviso.configure(text="")

        def actualizarAtaque():
            self.numAtaque.config(text=str(contadorPeleas))


        #FUNCIONA PARA QUE MUESTRE UN MENSAJE DE ERROR SI AUN NO HA SELECCIONADO LAS 10
        #POSICIONES PARA LOS BARCOS O MISILES
        def muestra_ventana_error_faltas_posiciones():
            if(contador != 10):
                if(Barcos_o_Misiles):
                    showwarning("Error","Tiene que seleccionar 10 posiciones para los BARCOS solado!")
                else:
                    showwarning("Error","Tiene que seleccionar 10 posiciones para los MISILES solado!")


        #COLOCAR QUE ESTE MENSAJE SE MUESTRE AL INICIO, CUANDO AGARRE LOS BARCOS OJO
        def muestra_ventana_introducir():
            if contadorPeleas == 3:
                return
            elif contadorPeleas != 0:
                showinfo("MISILES","Es momento de que introduzca la posición de la siguiente tanda de MISILES soldado!!")
            elif(Barcos_o_Misiles):
                showinfo("BARCOS","Es momento de que introduzca la posición de sus BARCOS soldado!!")
            else:
                showinfo("MISILES","Es momento de que introduzca la posición de sus MISILES soldado!!")

#--------------------------------------------------------------------------------------------------------------------------------

        def puedo_enviar():  #RECIBIR DE ARDUINO UNA LETRA PARA FUNCIONAR
            dataPacket = arduinoData.readline()
            dataPacket = str(dataPacket, 'utf-8')
            dataPacket = dataPacket.strip('\r\n')
            print(dataPacket)
            data = dataPacket
            if(data != 'L'):
                while (data == 'B'):
                    print('Es B')
                    return True
                                                #TENGO QUE GUARDAR ESA M, B, N EN UNA VARIABLE QUE SI GLOBAL
                while (data == 'M'):
                    print('Es M')
                    return True
                while (data == 'P'):
                    print('Es P')
            print('es l')
            return False

        # def enviar_posicion_Arduino(fila, columna):
        #     arduinoData.write(b'1')
        #     print('se esta enviando')

        def enviar_posicion_Arduino(fila,columna):  #letra es la fila
            filaS = bytes(str(fila), 'utf-8')      # pero me va a dar error de encode.
            columnaS = bytes(str(columna), 'utf-8')      # Si quiero que sean numeros, le quito str
            arduinoData.write(filaS)
            arduinoData.write(columnaS)
            # data.write(pos_colmuna)
            # data.write(pos_fila)
            print(f'Fila ({filaS})----Columna({columnaS})')

#----------------------------------------------------------------------------------------------------------------------------------

        #Fila A

        self.A0 = ttk.Button(master, text="A0",command=lambda: GuaradrPosicion(0,0,'A'))
        self.A0.place(width=60,height=25,x=30,y=370)
        
        self.A1 = ttk.Button(master, text="A1",command=lambda: GuaradrPosicion(0,1,'A'))
        self.A1.place(width=60,height=25, x=95,y=370)

        self.A2 = ttk.Button(master, text="A2",command=lambda: GuaradrPosicion(0,2,'A'))
        self.A2.place(width=60,height=25, x=160,y=370)
        
        self.A3 = ttk.Button(master, text="A3",command=lambda: GuaradrPosicion(0,3,'A'))
        self.A3.place(width=60,height=25, x=225,y=370)

        self.A4 = ttk.Button(master, text="A4",command=lambda: GuaradrPosicion(0,4,'A'))
        self.A4.place(width=60,height=25, x=290,y=370)

        self.A5 = ttk.Button(master, text="A5",command=lambda: GuaradrPosicion(0,5,'A'))
        self.A5.place(width=60,height=25, x=355,y=370)

        self.A6 = ttk.Button(master, text="A6",command=lambda: GuaradrPosicion(0,6,'A'))
        self.A6.place(width=60,height=25, x=420,y=370)

        self.A7 = ttk.Button(master, text="A7",command=lambda: GuaradrPosicion(0,7,'A'))
        self.A7.place(width=60,height=25, x=485,y=370)

        self.A8 = ttk.Button(master, text="A8",command=lambda: GuaradrPosicion(0,8,'A'))
        self.A8.place(width=60,height=25, x=550,y=370)

        self.A9 = ttk.Button(master, text="A9",command=lambda: GuaradrPosicion(0,9,'A'))
        self.A9.place(width=60,height=25, x=615,y=370)

         #Fila B

        self.B0 =ttk.Button(master, text="B0",command=lambda: GuaradrPosicion(1,0,'B'))
        self.B0.place(width=60,height=25,x=30,y=400)

        self.B1 = ttk.Button(master, text="B1",command=lambda: GuaradrPosicion(1,1,'B'))
        self.B1.place(width=60,height=25, x=95,y=400)

        self.B2 = ttk.Button(master, text="B2",command=lambda: GuaradrPosicion(1,2,'B'))
        self.B2.place(width=60,height=25, x=160,y=400)
        
        self.B3 = ttk.Button(master, text="B3",command=lambda: GuaradrPosicion(1,3,'B'))
        self.B3.place(width=60,height=25, x=225,y=400)

        self.B4 = ttk.Button(master, text="B4",command=lambda: GuaradrPosicion(1,4,'B'))
        self.B4.place(width=60,height=25, x=290,y=400)

        self.B5 = ttk.Button(master, text="B5",command=lambda: GuaradrPosicion(1,5,'B'))
        self.B5.place(width=60,height=25, x=355,y=400)

        self.B6 = ttk.Button(master, text="B6",command=lambda: GuaradrPosicion(1,6,'B'))
        self.B6.place(width=60,height=25, x=420,y=400)

        self.B7 = ttk.Button(master, text="B7",command=lambda: GuaradrPosicion(1,7,'B'))
        self.B7.place(width=60,height=25, x=485,y=400)

        self.B8 = ttk.Button(master, text="B8",command=lambda: GuaradrPosicion(1,8,'B'))
        self.B8.place(width=60,height=25, x=550,y=400)

        self.B9 = ttk.Button(master, text="B9",command=lambda: GuaradrPosicion(1,9,'B'))
        self.B9.place(width=60,height=25, x=615,y=400)

         #Fila C

        self.C0 =ttk.Button(master, text="C0",command=lambda: GuaradrPosicion(2,0,'C'))
        self.C0.place(width=60,height=25,x=30,y=430)

        self.C1 = ttk.Button(master, text="C1",command=lambda: GuaradrPosicion(2,1,'C'))
        self.C1.place(width=60,height=25, x=95,y=430)

        self.C2 = ttk.Button(master, text="C2",command=lambda: GuaradrPosicion(2,2,'C'))
        self.C2.place(width=60,height=25, x=160,y=430)
        
        self.C3 = ttk.Button(master, text="C3",command=lambda: GuaradrPosicion(2,3,'C'))
        self.C3.place(width=60,height=25, x=225,y=430)

        self.C4 = ttk.Button(master, text="C4",command=lambda: GuaradrPosicion(2,4,'C'))
        self.C4.place(width=60,height=25, x=290,y=430)

        self.C5 = ttk.Button(master, text="C5",command=lambda: GuaradrPosicion(2,5,'C'))
        self.C5.place(width=60,height=25, x=355,y=430)

        self.C6 = ttk.Button(master, text="C6",command=lambda: GuaradrPosicion(2,6,'C'))
        self.C6.place(width=60,height=25, x=420,y=430)

        self.C7 = ttk.Button(master, text="C7",command=lambda: GuaradrPosicion(2,7,'C'))
        self.C7.place(width=60,height=25, x=485,y=430)

        self.C8 = ttk.Button(master, text="C8",command=lambda: GuaradrPosicion(2,8,'C'))
        self.C8.place(width=60,height=25, x=550,y=430)

        self.C9 = ttk.Button(master, text="C9",command=lambda: GuaradrPosicion(2,9,'C'))
        self.C9.place(width=60,height=25, x=615,y=430)

        #Fila D

        self.D0 =ttk.Button(master, text="D0",command=lambda: GuaradrPosicion(3,0,'D'))
        self.D0.place(width=60,height=25,x=30,y=460)

        self.D1 = ttk.Button(master, text="D1",command=lambda: GuaradrPosicion(3,1,'D'))
        self.D1.place(width=60,height=25, x=95,y=460)

        self.D2 = ttk.Button(master, text="D2",command=lambda: GuaradrPosicion(3,2,'D'))
        self.D2.place(width=60,height=25, x=160,y=460)
        
        self.D3 = ttk.Button(master, text="D3",command=lambda: GuaradrPosicion(3,3,'D'))
        self.D3.place(width=60,height=25, x=225,y=460)

        self.D4 = ttk.Button(master, text="D4",command=lambda: GuaradrPosicion(3,4,'D'))
        self.D4.place(width=60,height=25, x=290,y=460)

        self.D5 = ttk.Button(master, text="D5",command=lambda: GuaradrPosicion(3,5,'D'))
        self.D5.place(width=60,height=25, x=355,y=460)

        self.D6 = ttk.Button(master, text="D6",command=lambda: GuaradrPosicion(3,6,'D'))
        self.D6.place(width=60,height=25, x=420,y=460)

        self.D7 = ttk.Button(master, text="D7",command=lambda: GuaradrPosicion(3,7,'D'))
        self.D7.place(width=60,height=25, x=485,y=460)

        self.D8 = ttk.Button(master, text="D8",command=lambda: GuaradrPosicion(3,8,'D'))
        self.D8.place(width=60,height=25, x=550,y=460)

        self.D9 = ttk.Button(master, text="D9",command=lambda: GuaradrPosicion(3,9,'D'))
        self.D9.place(width=60,height=25, x=615,y=460)

        self.Listo = ttk.Button(master,text='Listo', command= lambda: listoMio())    #SI NO A TOCADO AUN LAS 10 CASILLAS QUE SE BLOQUEE
        self.Listo.place(width=60,height=25, x=630,y=650)

        self.mostrarPosicionLbl = Label(master, font=("Arial",13), background="gray",foreground='blue')
        self.mostrarPosicionLbl.place(x=160, y=490)

        self.mostrarPosicion1 = Label(master, font=("Arial",13), background="gray",foreground='blue')
        self.mostrarPosicion1.place(x=160,y=520,width=60,height=25)

        self.mostrarPosicion2 = Label(master, font=("Arial",13), background="gray",foreground='blue')
        self.mostrarPosicion2.place(x=160,y=550,width=60,height=25)

        self.mostrarPosicion3 = Label(master, font=("Arial",13), background="gray",foreground='blue')
        self.mostrarPosicion3.place(x=160,y=580,width=60,height=25)

        self.mostrarPosicion4 = Label(master, font=("Arial",13), background="gray",foreground='blue')
        self.mostrarPosicion4.place(x=160,y=610,width=60,height=25)

        self.mostrarPosicion5 = Label(master, font=("Arial",13), background="gray",foreground='blue')
        self.mostrarPosicion5.place(x=160,y=640,width=60,height=25)

        self.mostrarPosicion6 = Label(master, font=("Arial",13), background="gray",foreground='blue')
        self.mostrarPosicion6.place(x=225,y=520,width=60,height=25)

        self.mostrarPosicion7 = Label(master, font=("Arial",13), background="gray",foreground='blue')
        self.mostrarPosicion7.place(x=225,y=550,width=60,height=25)

        self.mostrarPosicion8 = Label(master, font=("Arial",13), background="gray",foreground='blue')
        self.mostrarPosicion8.place(x=225,y=580,width=60,height=25)

        self.mostrarPosicion9 = Label(master, font=("Arial",13), background="gray",foreground='blue')
        self.mostrarPosicion9.place(x=225,y=610,width=60,height=25)

        self.mostrarPosicion10 = Label(master, font=("Arial",13), background="gray",foreground='blue')
        self.mostrarPosicion10.place(x=225,y=640,width=60,height=25)

        self.test = ttk.Button(master, text='comienzo',command= lambda: cambiarComienzo())
        self.test.place(x=550, y=600,width=60,height=25)

        self.test2 = ttk.Button(master, text='algo',command= lambda: cambiarAlgo())
        self.test2.place(x=550, y=640,width=60,height=25)

        def apagarTodosLosBotones():
            self.A0.config(state='disable')
            self.A1.config(state='disable')
            self.A2.config(state='disable')
            self.A3.config(state='disable')
            self.A4.config(state='disable')
            self.A5.config(state='disable')
            self.A6.config(state='disable')
            self.A7.config(state='disable')
            self.A8.config(state='disable')
            self.A9.config(state='disable')
            self.B0.config(state='disable')
            self.B1.config(state='disable')
            self.B2.config(state='disable')
            self.B3.config(state='disable')
            self.B4.config(state='disable')
            self.B5.config(state='disable')
            self.B6.config(state='disable')
            self.B7.config(state='disable')
            self.B8.config(state='disable')
            self.B9.config(state='disable')
            self.C0.config(state='disable')
            self.C1.config(state='disable')
            self.C2.config(state='disable')
            self.C3.config(state='disable')
            self.C4.config(state='disable')
            self.C5.config(state='disable')
            self.C6.config(state='disable')
            self.C7.config(state='disable')
            self.C8.config(state='disable')
            self.C9.config(state='disable')
            self.D0.config(state='disable')
            self.D1.config(state='disable')
            self.D2.config(state='disable')
            self.D3.config(state='disable')
            self.D4.config(state='disable')
            self.D5.config(state='disable')
            self.D6.config(state='disable')
            self.D7.config(state='disable')
            self.D8.config(state='disable')
            self.D9.config(state='disable')

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

        apagarTodosLosBotones()

        def cambiarComienzo():
            global comienzo
            comienzo = True
            # quiero teneer una variable que sea global, que se guarde como B, M, NS
            # si es B puede empezar a enviar barcos
            # si es M puede empezar a enviar misiles
            # si es N NO PUEDE ENVIAR

        def puedo_enviar2():  #RECIBIR DE ARDUINO UNA LETRA PARA FUNCIONAR
            dataPacket = arduinoData.readline()
            dataPacket = str(dataPacket, 'utf-8')
            dataPacket = dataPacket.strip('\r\n')
            print(dataPacket)
            data = dataPacket
            if(data == 'B'):
                global counter_barco
                counter_barco = counter_barco + 1
                print('Es B')
                return 'B'
            if(data == 'M'):
                print('Es M')
                return 'M'
            if(data == 'P'):
                print('Es P')
                return 'P'
            if(data == 'L'):
                print('Es L')
                return 'L'


        def listoMio():
            global Ganar_o_Perder
            global comienzoAngel
            global score
            comienzoAngel = puedo_enviar2()
            global contExtra
            global contador
            global contadorPeleas
            global Barcos_o_Misiles
            comparacion = 0
            if comienzoAngel == 'B' and contExtra==0:
                prenderBotones()
                showinfo('Juego','El juego empezo, preparece soldado. Ingrese sus BARCOS')
                contExtra+=1
                return
            if (comienzoAngel == 'M' and contExtra>=1 and contExtra<=4):
                if contador == 10:
                    prenderBotones()
                    showinfo('Juego','El juego empezo, preparece soldado. Ingrese sus MISILES')
                    self.etiqueta.configure(text="Cargando Misiles")
                    self.aviso.configure(text="")
                    if Barcos_o_Misiles == True:
                        posicionesSeleccionadas()
                        prenderBotones()
                        xd()
                    else:
                        dataPacket = arduinoData.readline()
                        dataPacket = str(dataPacket, 'utf-8')
                        dataPacket = dataPacket.strip('\r\n')
                        print(dataPacket)
                        score = int(dataPacket)
                        t = threading.Timer(2, actualizarScore) 
                        t.start() 
                        contadorPeleas +=1
                        actualizarAtaque()
                        if contadorPeleas==3:
                            dataPacket = arduinoData.readline()
                            dataPacket = str(dataPacket, 'utf-8')
                            dataPacket = dataPacket.strip('\r\n')
                            print(dataPacket)
                            comparacion = int(dataPacket)
                            if comparacion==0:
                                Ganar_o_Perder=False
                            else:
                                Ganar_o_Perder=True
                            apagarTodosLosBotones()
                            u = threading.Timer(2, actualizarScore) 
                            u.start() 
                            v = threading.Timer(2, popUp) 
                            v.start() 
                            w = threading.Timer(20, root.destroy)
                            w.start()
                    Barcos_o_Misiles=False
                    muestra_ventana_introducir() 
                    contador=0
                    if (Barcos_o_Misiles == False):
                        self.Listo.configure(text="Atacar")
                    else:
                        self.Listo.configure(text="Listo")
                    contExtra +=1
                else:
                    muestra_ventana_error_faltas_posiciones()
                return
            if (comienzoAngel == 'N'):
                showerror("Aviso",'EL otro jugado aun no esta listo, espere')
                return

        '''
        def listo():
            global comienzo
            comienzo = puedo_enviar()   ##puede ser esta variable comienzo??  falta guardar los valores 
            global contExtra
            global contador
            global contadorPeleas
            global Barcos_o_Misiles
            if comienzo and contExtra == 0:
                prenderBotones()
                showinfo('Juego','El juego empezo, preparece soldado')
                contExtra=1
                return
            if comienzo== False:
                showerror("Aviso",'EL otro jugado aun no esta listo, espere')
                return

            if contador == 10:
                self.etiqueta.configure(text="Cargando Misiles")
                self.aviso.configure(text="")
                if Barcos_o_Misiles == True:
                    posicionesSeleccionadas()
                    prenderBotones()
                    xd()
                else:
                    t = threading.Timer(1, actualizarScore) 
                    t.start() 
                    contadorPeleas +=1
                    actualizarAtaque()
                    if contadorPeleas==3:
                        apagarTodosLosBotones()
                        u = threading.Timer(1, actualizarScore) 
                        u.start() 
                        v = threading.Timer(1, popUp) 
                        v.start() 
                        w = threading.Timer(20, root.destroy)
                        w.start()
                Barcos_o_Misiles=False
                muestra_ventana_introducir() 
                contador=0
                if (Barcos_o_Misiles == False):
                    self.Listo.configure(text="Atacar")
                else:
                    self.Listo.configure(text="Listo")

            else:
                muestra_ventana_error_faltas_posiciones()
        '''
        #python es bien gei ngl salu2

    

        def posicionesSeleccionadas():
            datos=[]
            if Barcos_o_Misiles == True:
                self.mostrarPosicionLbl.config(text='Posiciones de Barcos seleccionadas')
                for i in range(4):
                    aux=MatrizBarcos[i]
                    for j in range(10):
                        if aux[j]==1:
                            if i ==0:
                                datos.append('A'+str(j))
                            elif i ==1:
                                datos.append('B'+str(j))
                            elif i ==2:
                                datos.append('C'+str(j))
                            elif i ==3:
                                datos.append('D'+str(j))
                self.mostrarPosicion1.config(text=datos[0])
                self.mostrarPosicion2.config(text=datos[1])
                self.mostrarPosicion3.config(text=datos[2])
                self.mostrarPosicion4.config(text=datos[3])
                self.mostrarPosicion5.config(text=datos[4])
                self.mostrarPosicion6.config(text=datos[5])
                self.mostrarPosicion7.config(text=datos[6])
                self.mostrarPosicion8.config(text=datos[7])
                self.mostrarPosicion9.config(text=datos[8])
                self.mostrarPosicion10.config(text=datos[9])



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

        def xd():
            if MatrizBarcos[2] == [1,1,1,1,1,1,1,1,1,1]:
                self.banner = tkinter.PhotoImage(file="xd.gif")
                self.lbl_banner.config(image=self.banner)
                self.etiqueta.configure(text="Congrats, encontraste al chiguire fachero xdd")


root = Tk()
miVentana = Ventana(root)
root.mainloop()