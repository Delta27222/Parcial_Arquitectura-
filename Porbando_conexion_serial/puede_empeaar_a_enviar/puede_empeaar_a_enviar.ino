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
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'}
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
  int i = 0;
  while (i < 20){
    prende();
    i++;
  }

  empezandoEnvio('L');
  delay(1000);

  empezandoEnvio('M');

  int j = 0;
  while (j < 20){
    prende();
    j++;
  }
}


void prende(){
  
  while(!Serial.available()){
    
  }
  char valuePosition = Serial.read();
  if(pulsacion1 == ' '){
      pulsacion1 = valuePosition;
      counterInit = counterInit + 1;
  }else{
    if (pulsacion2 == ' '){
      pulsacion2 = valuePosition;
      counterInit = counterInit + 1;
    }
  }
  if (counterInit == 2){    //Se supone que en este punto, ya las pulsaciones esta guardadas PULSACION1 para las letras y PULSACION2 para los numeros
    limpiarRegistroPulsaciones();  
    //SE SUPONE QUE LO QUE NOS ESTA ENVIANDO EL .PY YA ESTA COMPROBADO QUE NO ESTA TOMADO----------------------------------------------------------------------------------------------------
    //De todas formas voy a utilizar la funcion de "isTaken()"
    //istaken(user, pulsacion1, pulsacion2);   //De esta forma se verifica que no estan repetidas y por ende actualice la matriz
    
    }




  
}




int i = 0;

void loop() {
}


//   mensajeEsperaJB(2);
     //empezandoEnvio('B');  //LE ENVIO A PYTHON QUE PUEDE EMPEZAR A ENVIAR
  //llenandoBarcosJB();//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//    empezandoEnvio('M');
  //El usuario JB posicionando MISILES
//  mensajeEsperaJB(3);
//llenandoMisilesJB()//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  empezandoEnvio('N');

void empezandoEnvio(char letra){
  Serial.println(letra);
}

void llenandoBarcosJB(){
  int listo = 1;
    while (listo != 20){
      recibiendoPosiciones(2);//--------------------------------------------------------------
      listo = listo + 1; 
      digitalWrite(13 , HIGH);   // poner el Pin en HIGH
      delay(1000);                   // esperar un segundo
      digitalWrite(13 , LOW);    // poner el Pin en LOW
      delay(1000);  
    }
}

//FUNCIONAL - Funciona para recibir los MISILES del JB del .py
void llenandoMisilesJB(){
  int listo = 1;
    while (listo != 20){
      recibiendoPosiciones(3);//--------------------------------------------------------------
      listo = listo + 1; 
    }
}


//FUNCIONAL - Funcion para captar los datos de misiles y barcos que vienen de PYTHON  (esto se debe ejecutar cada vez por coordenada A1)
int recibiendoPosiciones(int user){
    digitalWrite(9, HIGH);
    delay(5000);
    digitalWrite(9, LOW);
  if (Serial.available() > 0){
    char valuePosition = Serial.read();
    if(counterInit == 0){
        pulsacion1 = valuePosition;
        counterInit = counterInit + 1;
        digitalWrite(8, HIGH);
    }else{
      if (counterInit == 1){
        pulsacion2 = valuePosition;
        counterInit = counterInit + 1;
        digitalWrite(9, HIGH);
      }
    }
    if (counterInit == 2){    //Se supone que en este punto, ya las pulsaciones esta guardadas PULSACION1 para las letras y PULSACION2 para los numeros
      limpiarRegistroPulsaciones();  
      
      //SE SUPONE QUE LO QUE NOS ESTA ENVIANDO EL .PY YA ESTA COMPROBADO QUE NO ESTA TOMADO----------------------------------------------------------------------------------------------------
      //De todas formas voy a utilizar la funcion de "isTaken()"
      //istaken(user, pulsacion1, pulsacion2);   //De esta forma se verifica que no estan repetidas y por ende actualice la matriz
      
    }
  }
}


//FUNCIONAL - Esta funcion comprueba que la coordenada recien introducida por el usuario NO ESTE USADA POR OTRO (BARCO, MISIL)
bool istaken(int user, char fila, char columna){
  
  int filaS; 
  if (fila == 'A'){filaS = 0;}
  if (fila == 'B'){filaS = 1;}
  if (fila == 'C'){filaS = 2;}
  if (fila == 'D'){filaS = 3;}
  
  int columnaS; 
  if (columna == '0'){columnaS = 0;}
  if (columna == '1'){columnaS = 1;}
  if (columna == '2'){columnaS = 2;}
  if (columna == '3'){columnaS = 3;}
  if (columna == '4'){columnaS = 4;}
  if (columna == '5'){columnaS = 5;}
  if (columna == '6'){columnaS = 6;}
  if (columna == '7'){columnaS = 7;}  
  if (columna == '8'){columnaS = 8;}
  if (columna == '9'){columnaS = 9;} 

  if (user == 0){
  char x = JA_Barcos[filaS][columnaS];   
    if (x == 'X'){return true;}
  }
  if (user == 1){
  char x = JA_Misiles[filaS][columnaS];
    if (x == 'X'){return true;}
  }
  if (user == 2){
  char x = JB_Barcos[filaS][columnaS];
    if (x == 'X'){return true;}
  }
  if (user == 3){
  char x = JB_Misiles[filaS][columnaS];
    if (x == 'X'){return true;}
  }
  actualizarMatriz(user,filaS,columnaS);  
  Serial.print("se actualizo la matriz  ---- valor en matriz actualizado  ---->   ");
  Serial.println(JA_Barcos[filaS][columnaS]);
  return false;
}

//FUNCIONAL - Funcion para posicionar a los barcos y misiles de cada jugador
void actualizarMatriz(int user,int filaS,int columnaS){
    if (user == 0){
      JA_Barcos[filaS][columnaS] = 'X';   
    }
    if (user == 1){
      JA_Misiles[filaS][columnaS] = 'X';
    }
    if (user == 2){
      JB_Barcos[filaS][columnaS] = 'X';
    }
    if (user == 3){
      JB_Misiles[filaS][columnaS] = 'X';
    }   
  
}

//FUNCIONAL - Funcion para limpiar las variables encargadas de captar las pulsaciones del keypad, cuando ya se tengan las dos coordenadas
void limpiarRegistroPulsaciones(){
  pulsacion1 = ' ';
  pulsacion2 = ' ';
  counterInit = 0;
}
