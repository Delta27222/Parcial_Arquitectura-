//Este codigo funciona para recibir de python y hacer algo

const int pinLed = 13;
const byte FILA_MATRIZ = 4;
const byte COLUMNA_MATRIZ = 10;
//Matrices para los BARCOS de ambos jugadores
char JA_BarcosS[FILA_MATRIZ][COLUMNA_MATRIZ]={ 
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O'}
};

char pulsacion1 = ' ';
char pulsacion2 = ' ';
int counterInit = 0;
int contador = 0;

void setup() {
  Serial.begin(9600);
  digitalWrite(13 , LOW);
  pinMode(pinLed, OUTPUT);
}

void loop() {
//  while(Serial.available() > 0){
//    recibiendoPosiciones();
//  }

llenandoBarcosJB();

}


//FUNCIONAL - Funcion para limpiar las variables encargadas de captar las pulsaciones del keypad, cuando ya se tengan las dos coordenadas
void limpiarRegistroPulsaciones(){
  pulsacion1 = ' ';
  pulsacion2 = ' ';
  counterInit = 0;
}


//en el caso de que envie una por una las posiciones   CREO QUE SOLO PUEDO ENVIAR CARACTERES WE
void recibiendoPosiciones(){
  if (Serial.available() > 0){
    char valuePosition = Serial.read();
    if(pulsacion1 == ' ' and pulsacion2 == ' '){
        pulsacion1 = valuePosition;
        counterInit = counterInit + 1;
//        if(pulsacion1 == 'A'  or pulsacion1 == 'B'  or pulsacion1 == 'C'  or pulsacion1 == 'D'){
//          digitalWrite(13 , HIGH);   // poner el Pin en HIGH
//          delay(1000);                   // esperar un segundo
//          digitalWrite(13 , LOW);    // poner el Pin en LOW
//          delay(1000);
//        }
    }else{
      if (pulsacion1 != ' ' and pulsacion2 == ' '){
        pulsacion2 = valuePosition;
        counterInit = counterInit + 1;
//         if(pulsacion2 == '0' or pulsacion2 == '1' or pulsacion2 == '2' or pulsacion2 == '3' or pulsacion2 == '4' or pulsacion2 == '5' or pulsacion2 == '6' or pulsacion2 == '7' or pulsacion2 == '8' or pulsacion2 == '9'){
//          digitalWrite(13 , HIGH);   // poner el Pin en HIGH
//          delay(5000);                   // esperar un segundo
//          digitalWrite(13 , LOW);    // poner el Pin en LOW
//          delay(1000);
//        }
      }
    }
    if (counterInit == 2){    //Se supone que en este punto, ya las pulsaciones esta guardadas PULSACION1 para las letras y PULSACION2 para los numeros
      limpiarRegistroPulsaciones();
      //positioning(user, pulsacion1, pulsacion2); //User = 2 para los barcos User = 3 para los misiles
          digitalWrite(13 , LOW);    // poner el Pin en LOW
          delay(1000);
          digitalWrite(13 , HIGH);   // poner el Pin en HIGH
          delay(1000);                   // esperar un segundo
          digitalWrite(13 , LOW);    // poner el Pin en LOW
        
    }
  }else{

    contador = contador +1;
  }
}

//FUNCIONAL - Funciona para recibir los BARCOS del JB del .py
void llenandoBarcosJB(){
  int listo = 1;
    while (listo != 10){
      recibiendoPosiciones();//--------------------------------------------------------------
      listo = listo + 1; 
    }
}
