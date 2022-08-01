from msilib.schema import File
from sqlite3 import Row
from tkinter import LEFT, Tk, Label, Button, ttk
import tkinter


    

class Ventana:
    def __init__(self, master):
        self.master = master
        root.geometry('700x700')
        master.title("Arduino Battleship")
        self.banner = tkinter.PhotoImage(file="Banner.gif")
        self.lbl_banner = tkinter.Label(master, image=self.banner)
        self.lbl_banner.pack()
        self.etiqueta = Label(master, text="Tablero de juego")
        self.etiqueta.pack()

        #Fila A

        self.A0 = ttk.Button(master, text="A0")
        self.A0.place(width=60,height=25,x=30,y=350)
        
        self.A1 = ttk.Button(master, text="A1")
        self.A1.place(width=60,height=25, x=95,y=350)

        self.A2 = ttk.Button(master, text="A2")
        self.A2.place(width=60,height=25, x=160,y=350)
        
        self.A3 = ttk.Button(master, text="A3")
        self.A3.place(width=60,height=25, x=225,y=350)

        self.A4 = ttk.Button(master, text="A4")
        self.A4.place(width=60,height=25, x=290,y=350)

        self.A5 = ttk.Button(master, text="A5")
        self.A5.place(width=60,height=25, x=355,y=350)

        self.A6 = ttk.Button(master, text="A6")
        self.A6.place(width=60,height=25, x=420,y=350)

        self.A7 = ttk.Button(master, text="A7")
        self.A7.place(width=60,height=25, x=485,y=350)

        self.A8 = ttk.Button(master, text="A8")
        self.A8.place(width=60,height=25, x=550,y=350)

        self.A9 = ttk.Button(master, text="A9")
        self.A9.place(width=60,height=25, x=615,y=350)

         #Fila B

        self.B0 =ttk.Button(master, text="B0")
        self.B0.place(width=60,height=25,x=30,y=380)

        self.B1 = ttk.Button(master, text="B1")
        self.B1.place(width=60,height=25, x=95,y=380)

        self.B2 = ttk.Button(master, text="B2")
        self.B2.place(width=60,height=25, x=160,y=380)
        
        self.B3 = ttk.Button(master, text="B3")
        self.B3.place(width=60,height=25, x=225,y=380)

        self.B4 = ttk.Button(master, text="B4")
        self.B4.place(width=60,height=25, x=290,y=380)

        self.B5 = ttk.Button(master, text="B5")
        self.B5.place(width=60,height=25, x=355,y=380)

        self.B6 = ttk.Button(master, text="B6")
        self.B6.place(width=60,height=25, x=420,y=380)

        self.B7 = ttk.Button(master, text="B7")
        self.B7.place(width=60,height=25, x=485,y=380)

        self.B8 = ttk.Button(master, text="B8")
        self.B8.place(width=60,height=25, x=550,y=380)

        self.B9 = ttk.Button(master, text="B9")
        self.B9.place(width=60,height=25, x=615,y=380)

         #Fila C

        self.C0 =ttk.Button(master, text="C0")
        self.C0.place(width=60,height=25,x=30,y=410)

        self.C1 = ttk.Button(master, text="C1")
        self.C1.place(width=60,height=25, x=95,y=410)

        self.C2 = ttk.Button(master, text="C2")
        self.C2.place(width=60,height=25, x=160,y=410)
        
        self.C3 = ttk.Button(master, text="C3")
        self.C3.place(width=60,height=25, x=225,y=410)

        self.C4 = ttk.Button(master, text="C4")
        self.C4.place(width=60,height=25, x=290,y=410)

        self.C5 = ttk.Button(master, text="C5")
        self.C5.place(width=60,height=25, x=355,y=410)

        self.C6 = ttk.Button(master, text="C6")
        self.C6.place(width=60,height=25, x=420,y=410)

        self.C7 = ttk.Button(master, text="C7")
        self.C7.place(width=60,height=25, x=485,y=410)

        self.C8 = ttk.Button(master, text="C8")
        self.C8.place(width=60,height=25, x=550,y=410)

        self.C9 = ttk.Button(master, text="C9")
        self.C9.place(width=60,height=25, x=615,y=410)

        #Fila D

        self.D0 =ttk.Button(master, text="D0")
        self.D0.place(width=60,height=25,x=30,y=440)

        self.D1 = ttk.Button(master, text="D1")
        self.D1.place(width=60,height=25, x=95,y=440)

        self.D2 = ttk.Button(master, text="D2")
        self.D2.place(width=60,height=25, x=160,y=440)
        
        self.D3 = ttk.Button(master, text="D3")
        self.D3.place(width=60,height=25, x=225,y=440)

        self.D4 = ttk.Button(master, text="D4")
        self.D4.place(width=60,height=25, x=290,y=440)

        self.D5 = ttk.Button(master, text="D5")
        self.D5.place(width=60,height=25, x=355,y=440)

        self.D6 = ttk.Button(master, text="D6")
        self.D6.place(width=60,height=25, x=420,y=440)

        self.D7 = ttk.Button(master, text="D7")
        self.D7.place(width=60,height=25, x=485,y=440)

        self.D8 = ttk.Button(master, text="D8")
        self.D8.place(width=60,height=25, x=550,y=440)

        self.D9 = ttk.Button(master, text="D9")
        self.D9.place(width=60,height=25, x=615,y=440)

        self.Listo = ttk.Button(master,text='Listo')
        

    def saludar(self):
        print("¡Hey!")
root = Tk()
miVentana = Ventana(root)
root.mainloop()