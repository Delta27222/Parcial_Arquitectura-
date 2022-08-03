from dataclasses import dataclass
import time
import serial

arduinoData = serial.Serial('COM3',baudrate='9600', bytesize=8)
time.sleep(1) #LE ESTAMOS DANDO UN DELAY DE 1 SEGUNDO


def run():

    dataPacket = arduinoData.readline()
    dataPacket = str(dataPacket, 'utf-8')
    print(dataPacket)
    arduinoData.close()

if __name__ == '__main__':
    run()