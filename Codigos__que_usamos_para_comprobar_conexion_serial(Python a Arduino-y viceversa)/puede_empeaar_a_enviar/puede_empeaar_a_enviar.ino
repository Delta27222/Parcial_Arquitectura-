#include <Keypad.h>
//---------------------------------------

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);


//---------------------------------------

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'}, 
  {'7', '8', '9', 'C'}, 
  {'D', '0', 'D', 'D'} 
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char key = keypad.getKey();


//-----------------------------------------------------

const byte FILA_MATRIZ = 4;
const byte COLUMNA_MATRIZ = 10;

//Matrices para los BARCOS de ambos jugadores
char JA_Barcos[FILA_MATRIZ][COLUMNA_MATRIZ]={ 
  {'X', 'O', 'O', 'O','O', 'O', 'O', 'O','O','X'},
  {'X', 'O', 'O', 'O','O', 'O', 'O', 'O','O','X'},
  {'X', 'O', 'O', 'O','O', 'O', 'O', 'O','O','X'},
  {'X', 'X', 'O', 'O','O', 'O', 'O', 'O','X','X'}
};
char JB_Barcos[FILA_MATRIZ][COLUMNA_MATRIZ]={ 
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'}
};

//Matrices para los MISILES de ambos jugadores
char JA_Misiles[FILA_MATRIZ][COLUMNA_MATRIZ]={ 
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'}
};
char JB_Misiles[FILA_MATRIZ][COLUMNA_MATRIZ]={ 
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'}
};



//--------------------------------------------------

int dato, datoWhile;

char pulsacion1 = ' ';
char pulsacion2 = ' ';
int counterInit = 0;
int counter = 0;
int contadorInicio = 0;

int puntuacionJA = 0; 
int puntuacionJB = 0;

int cantAciertosJA = 0;
int cantAciertosJB = 0;

bool ene = true;


void setup() {
   Serial.begin(9600);
    pinMode(9,OUTPUT);
    pinMode(8,OUTPUT);
   empezandoEnvio('B');
   
   llenandoBarcosJB();

   empezandoEnvio('M');
   
  llenandoMisilesJB();

  comprobarPosicionAtaque(1);

  comprobarPosicionAtaque(2);

  enviarPuntaje(puntuacionJB);

  empezandoEnvio('M');
   
  llenandoMisilesJB();

  comprobarPosicionAtaque(1);

  comprobarPosicionAtaque(2);

  enviarPuntaje(puntuacionJB);

  empezandoEnvio('M');
   
  llenandoMisilesJB();

  comprobarPosicionAtaque(1);

  comprobarPosicionAtaque(2);

  enviarPuntaje(puntuacionJB);

  
}
void loop() {
}


void enviarPuntaje(int puntuacionJB){
  Serial.println(puntuacionJB);
}


int recibiendoPosiciones(int user){
  while(!Serial.available()){
  }
  char valuePosition = Serial.read();
  if(pulsacion1 == ' '){
      pulsacion1 = valuePosition;
      counterInit = counterInit + 1;
      digitalWrite(8, HIGH);
      delay(1000);
  }else{
    if (pulsacion2 == ' '){
      pulsacion2 = valuePosition;
      counterInit = counterInit + 1;
      digitalWrite(9, HIGH);
      delay(1000);
    }
  }
  if (counterInit == 2){    //Se supone que en este punto, ya las pulsaciones esta guardadas PULSACION1 para las letras y PULSACION2 para los numeros
    digitalWrite(8, LOW);
    delay(1000);
    digitalWrite(9, LOW);
    delay(1000);
    //SE SUPONE QUE LO QUE NOS ESTA ENVIANDO EL .PY YA ESTA COMPROBADO QUE NO ESTA TOMADO----------------------------------------------------------------------------------------------------
    //De todas formas voy a utilizar la funcion de "isTaken()"
//    istaken(user, pulsacion1, pulsacion2);   //De esta forma se verifica que no estan repetidas y por ende actualice la matriz
    limpiarRegistroPulsaciones(); 
    }
}




//FUNCIONAL - Funciona para recibir los BARCOS del JB del .py
void llenandoBarcosJB(){
  int i = 0;
  while (i < 20){
    recibiendoPosiciones(2);
    i++;
  }
}

//FUNCIONAL - Funciona para recibir los MISILES del JB del .py
void llenandoMisilesJB(){
  int i = 0;
  while (i < 20){
    recibiendoPosiciones(3);
    i++;
  }
}

//FUNCIONAL - ATAQUE JA MISILES - JB BARCOS   &&&&&    ATAQUE JB MISILES - JA BARCOS
void comprobarPosicionAtaque(int jugador) {
  for(int i=0; i < FILA_MATRIZ; i++){
    for(int j = 0; j < COLUMNA_MATRIZ; j++){
      if(jugador == 1){
        if(JA_Misiles[i][j] == 'X' and JB_Barcos[i][j] == 'X'){ //JA le dio a un barco del JUGADOR B
          comprobarAtaque(1,i,j);
        } 
      }else{
        if(jugador == 2){
          if(JB_Misiles[i][j] == 'X' and JA_Barcos[i][j] == 'X'){ //JB le dio a un barco del JUGADOR A
            comprobarAtaque(2,i,j);
          } 
        }
      }
    }
  }
}

//FUNCIONAL - Funcion para actualizar las matrices de barcos cuando le den a un barco con un misil
void comprobarAtaque(int jugador, int fila, int columna){
  if(jugador == 1){
    JB_Barcos[fila][columna] = '#';
    puntuacionJA = puntuacionJA + 10;
    cantAciertosJA = cantAciertosJA + 1;
  }else{
    if(jugador == 2){
      JA_Barcos[fila][columna] = '#';
      puntuacionJB = puntuacionJB + 10;
      cantAciertosJB = cantAciertosJB + 1;
    }
  }
}

void empezandoEnvio(char letra){
  Serial.println(letra);
}

//FUNCIONAL - Funcion para limpiar las variables encargadas de captar las pulsaciones del keypad, cuando ya se tengan las dos coordenadas
void limpiarRegistroPulsaciones(){
  pulsacion1 = ' ';
  pulsacion2 = ' ';
  counterInit = 0;
}
