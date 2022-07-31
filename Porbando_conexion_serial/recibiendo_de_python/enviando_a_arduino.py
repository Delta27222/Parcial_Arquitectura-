# Este codigo funciona para enviar de python a arduino
import serial, time

# arduinoData = serial.Serial('COM3',baudrate='9600', bytesize=8)
# time.sleep(2)

def sentCoordinatesToArduino(pulsacion1, pulsacion2):
    arduinoData = serial.Serial('COM3',baudrate='9600', bytesize=8)
    time.sleep(2)

    # pulsacion1 = input("Indique la pulsacion 1(primera coordenada QUE SEA LA LETRA):")      #QUE EN VARIABLES SE META EL VALOR DE LA COORDENADA
    if (pulsacion1 == 'A'):
        arduinoData.write(b'A')
    elif(pulsacion1 == 'B'):
        arduinoData.write(b'B')
    elif(pulsacion1 == 'C'):
        arduinoData.write(b'C')
    elif(pulsacion1 == 'D'):
        arduinoData.write(b'D')

    # pulsacion2 = input("Indique la pulsacion 1(primera coordenada QUE SEA LA LETRA):")      #QUE EN VARIABLES SE META EL VALOR DE LA COORDENADA
    if (pulsacion2 == '0'):
        arduinoData.write(b'0')
    elif (pulsacion2 == '1'):
        arduinoData.write(b'1')
    elif(pulsacion2 == '2'):
        arduinoData.write(b'2')
    elif(pulsacion2 == '3'):
        arduinoData.write(b'3')
    elif(pulsacion2 == '4'):
        arduinoData.write(b'4')
    elif(pulsacion2 == '5'):
        arduinoData.write(b'5')
    elif(pulsacion2 == '6'):
        arduinoData.write(b'6')
    elif(pulsacion2 == '7'):
        arduinoData.write(b'7')
    elif(pulsacion2 == '8'):
        arduinoData.write(b'8')
    elif(pulsacion2 == '9'):
        arduinoData.write(b'9')

    arduinoData.close()

def run():

    #Esta es una solucion a la manera de enviar las coordenadas por python, me parece que es la mass facil

    #Enviar siempre en orden las coordenadas.......LAS LETRAS POR PULSACION1 Y LOS NUMEROS POR PULSACION2 OJO
    sentCoordinatesToArduino('A', '0')

if __name__ == '__main__':
    run()

