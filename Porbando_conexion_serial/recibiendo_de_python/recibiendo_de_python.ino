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
int counter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);
}

void loop() {
  while(Serial.available() > 0){
    recibiendoPosiciones();
  }
}
//en el caso de que envie una por una las posiciones   CREO QUE SOLO PUEDO ENVIAR CARACTERES WE
void recibiendoPosiciones(){
  if (Serial.available() > 0){
    char valuePosition = Serial.read();
    if(pulsacion1 == ' ' and pulsacion2 == ' '){
        pulsacion1 = valuePosition;
        counterInit = counterInit + 1;
    }else{
      if (pulsacion1 != ' ' and pulsacion2 == ' '){
        pulsacion2 = valuePosition;
        counterInit = counterInit + 1;
      }
    }
    if (counterInit == 2){    //Se supone que en este punto, ya las pulsaciones esta guardadas PULSACION1 para las letras y PULSACION2 para los numeros
      limpiarRegistroPulsaciones();
      positioning(user, pulsacion1, pulsacion2); //User = 2 para los barcos User = 3 para los misiles
    }
  }else{

    contador = contador +1
  }
}



//FUNCIONAL - Funcion para limpiar las variables encargadas de captar las pulsaciones del keypad, cuando ya se tengan las dos coordenadas
void limpiarRegistroPulsaciones(){
  pulsacion1 = ' ';
  pulsacion2 = ' ';
  counterInit = 0;
}
