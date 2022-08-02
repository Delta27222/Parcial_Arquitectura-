#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

#include <Adafruit_LiquidCrystal.h>

//LiquidCrystal_I2C lcd(0x27,16,2);
Adafruit_LiquidCrystal lcd(0);

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
  {'X', 'X', 'O', 'O','O', 'O', 'O', 'O','X','X'},
  {'X', 'O', 'O', 'O','O', 'O', 'O', 'O','O','X'},
  {'X', 'O', 'O', 'O','O', 'O', 'O', 'O','O','X'},
  {'X', 'O', 'O', 'O','O', 'O', 'O', 'O','O','X'}
};

//Matrices para los MISILES de ambos jugadores
char JA_Misiles[FILA_MATRIZ][COLUMNA_MATRIZ]={ 
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'}
};
char JB_Misiles[FILA_MATRIZ][COLUMNA_MATRIZ]={ 
  {'X', 'O', 'X', 'O','X', 'O', 'X', 'O','O','X'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'},
  {'O', 'O', 'O', 'O','O', 'O', 'O', 'O','O','O'},
  {'X', 'O', 'X', 'O','X', 'O', 'O', 'O','O','X'}
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

void setup(){
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  lcd.setBacklight(1); 
  //lcd.setCursor(0,0);
  //lcd.print("Bienvenido a la ");
  //lcd.setCursor(2,1);
  //lcd.print("Batalla Naval");
  //delay(1000); 
  //lcd.clear();
  //lcd.setCursor(0,0);
  //lcd.print("A continuacion  ");
  //lcd.setCursor(0,1);
  //lcd.print("se mostrara el ");
  //delay(500); 
  //lcd.clear();
  //lcd.setCursor(0,0);
  //lcd.print("menu del juego,");
  //lcd.setCursor(0,1);
  //lcd.print("seleccione con");
  //delay(500); 
  //lcd.clear();
  //lcd.setCursor(0,0);
  //lcd.print("el keypad la");
  //lcd.setCursor(0,1);
  //lcd.print("opcion correcta!");
  //delay(500); 
  //lcd.clear();
  
  
  
}
  
void loop(){
  lcd.setCursor(0,0);
  lcd.print("1.JUGADOR A");  
  lcd.setCursor(0,1);					//Aca estamos mostrando el menu principal del juego 
  lcd.print("2.INICIAR GUERRA");
  
  key = keypad.getKey(); 
  String valor = String(key);

  if (key){
    if (key == '1'){
      menu2a();
    }
    if (key == '2'){
      if(contadorInicio == 0){
        lcd.clear();
        lcd.setCursor(0,0);
  		lcd.print("ERROR:Introduzca");
        lcd.setCursor(0,1);					
        lcd.print("los Barcos de JA");
        delay(2000); 
        lcd.clear();
      }else{
        menu2b();
      }
    }
  }
}

//FUNCIONAL - Funcion para mostrar el menu del JUGADOR A
void menu2a(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("1.Pos.Barcos JA");  
  lcd.setCursor(0,1);
  lcd.print("2.Ver Barcos");
  lcd.setCursor(13,1);
  lcd.print("3=+");
  dato = 1; 
  while(dato){
    key = keypad.getKey();
    if (key == '1'){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Seleccione con"); 
      lcd.setCursor(0,1);
      lcd.print("el keypad las");
      delay(100); 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("posiciones de"); 
      lcd.setCursor(0,1);
      lcd.print("los barcos");
      delay(100); 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Posicion...");
      datoWhile = 1;
      lcd.setCursor(9,1);
      lcd.print("Cant:");
      lcd.print(counter);
      while (datoWhile){
        key = keypad.getKey();
        if(key){
          lcd.setCursor(3,1);
          lcd.print(key);
          captarPosicion(key, 0);
          //Serial.print("-------------------------------------------->   ");
          //Serial.println(counter);
          lcd.setCursor(9,1);
          lcd.print("Cant:");
          lcd.print(counter);
          if(counter == 10){//---------------------------------------------------------------------CAMBIO CANTIDAD BARCOS
            counter = 0; 
            datoWhile = 0;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Posiciones de ");
            lcd.setCursor(0,1);
            lcd.print("barcos agregadas!");
            delay(2);
            contadorInicio = 1;        
            menu2a();
          }
        }
      }
      lcd.clear();
      dato = 0; 
    }
    if (key == '2'){
      lcd.clear(); 
   	  verMatrizBarcosJA();
      lcd.clear(); 
      menu2a();      
    }
   	if(key == '3'){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("3.Ptos Victo");  
      lcd.setCursor(0,1);
      lcd.print("4.Volver");
      datoWhile = 1;
      while (datoWhile){
        key = keypad.getKey();
        if(key == '3'){
          lcd.clear(); 
          lcd.setCursor(0,0);
          lcd.print("Punjate:"); 
          lcd.setCursor(7,1);
          lcd.print(puntuacionJA);
          delay(3000);
          menu2a();
        }
        if(key == '4'){
          datoWhile = 0;
          menu2a();
        }
      }
    }
    if(key == '0'){
      lcd.clear();
      dato = 0;
    }
  }
}

//FUNCIONAL - Funcion para mostrar el menu del JUGADOR B
void menu2b(){
  bool finBatalla = false;
  puntuacionJA = 0;
  lcd.clear();
  
  //Pide en el LCD los misiles al JA
  misilesJA();
  
  //El usuario JB posicionando BARCOS
  mensajeEsperaJB(2);
//llenandoBarcosJB();//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
  //El usuario JB posicionando MISILES
  mensajeEsperaJB(3);
//llenandoMisilesJB()//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
  //Mostramos que EMPEZO LA RONDA 1
  mensajeEmpezoLaGuerra(1);
  
  //FUNCION QUE HACE LAS COMPROBACIONES DEL PRIMER ATAQUE
  
  comprobarPosicionAtaque(1);//Comprueba que el jugador A le dio a un BARCO DEL JB
	
  comprobarPosicionAtaque(2);//Comprueba que el jugador B le dio a un BARCO DEL JA
  
  if(cantAciertosJA != 10 or cantAciertosJB !=10){

    //Mostramos los resultados del ataque
    mostrarPuntaje();

    //Enviamos el puntaje y acertados a python 
    //enviarPuntaje();ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd

    //Mostramos la matriz de los barcos del JA
    verMatrizBarcosJA2();
    lcd.clear();
       
    //Pide en el LCD los misiles al JA
    //misilesJA();//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    //El usuario JB posicionando MISILES
    mensajeEsperaJB(3);
    //llenandoMisilesJB//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    //Mostramos que EMPEZO LA RONDA 2
    mensajeEmpezoLaGuerra(2);
	lcd.clear();

    //FUNCION QUE HACE LAS COMPROBACIONES DEL PRIMER ATAQUE

    comprobarPosicionAtaque(1);//Comprueba que el jugador A le dio a un BARCO DEL JB

    comprobarPosicionAtaque(2);//Comprueba que el jugador B le dio a un BARCO DEL JA

    if(cantAciertosJA != 10 or cantAciertosJB !=10){
      //Mostramos los resultados del ataque
      mostrarPuntaje();

      //Enviamos el puntaje y acertados a python 
      //enviarPuntaje();ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd

      //Mostramos la matriz de los barcos del JA
      verMatrizBarcosJA2();
      lcd.clear();

      lcd.clear();
      //Pide en el LCD los misiles al JA
      //misilesJA();//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

      //El usuario JB posicionando MISILES
      mensajeEsperaJB(3);
      //llenandoMisilesJB//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

      //Mostramos que EMPEZO LA RONDA 3
      mensajeEmpezoLaGuerra(3);
      lcd.clear();

      //FUNCION QUE HACE LAS COMPROBACIONES DEL PRIMER ATAQUE

      comprobarPosicionAtaque(1);//Comprueba que el jugador A le dio a un BARCO DEL JB

      comprobarPosicionAtaque(2);//Comprueba que el jugador B le dio a un BARCO DEL JA
      
       //Mostramos los resultados del ataque
      mostrarPuntaje();

      //Mostramos la matriz de los barcos del JA
      verMatrizBarcosJA2();
      lcd.clear();

	  finBatalla = true;
    }else{
      finBatalla = true;
    }
  }else{
    finBatalla = true;
  }
  
  
  if (finBatalla == true){
    lcd.clear();
    lcd.setCursor(1,1);
    lcd.print("FIN BATALLA!!");
    delay(3000);
    lcd.clear();
  }

  //Funcion que muestra quien es el ganador
  ganador(puntuacionJA, puntuacionJB);   //ACA DENTRO PUEDO ENVIAR LA PUNTUACIONA PYTHON puede ser que lo haga aca

  contadorInicio = 0;
  puntuacionJB = 0;
}



//FUNCIONAL - Funcion que muestra mensaje de ataque
void mensajeEmpezoLaGuerra(int numero){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Empezo la ronda");
  lcd.setCursor(4,1);
  lcd.print("numero ");
  lcd.setCursor(12,1);
  lcd.print(numero);
  delay(500);
  lcd.clear();
}


//FUNCIONAL - Funcion para mostrar en pantalla quien GANO,PERDIO, O QUEDO EMPATADO (TAMBIEN PUEDE ENVIAR A PYTHON)
void ganador(int puntuacionJA, int puntuacionJB){
  if (puntuacionJA == puntuacionJB){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Empatados, sera ");
    lcd.setCursor(0,1);
    lcd.print("para la proxima!!");
    
    //FUNCION PARA ENVIAR A JUGADOR B QUE ES EMPATE
    
    delay(3000);
    lcd.clear();
  }else{
    if(puntuacionJA > puntuacionJB){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Has GANADO la ");
        lcd.setCursor(0,1);
        lcd.print("batalla !!");

        //FUNCION PARA ENVIAR A JUGADOR B QUE PERDIO

        delay(3000);
      	lcd.clear();
    }else {
      if (puntuacionJA < puntuacionJB){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Has PERDIDO la");
        lcd.setCursor(0,1);
        lcd.print("batalla :c");
        
        //FUNCION PARA ENVIAR A JUGADOR B QUE GANO

        delay(3000);
        lcd.clear();
      }
    }
    
  }
  
  
}







//Funcionalidades--------------------------------------------------------------------------------------------------------------------------

//FUNCIONAL - Funciona para recibir los BARCOS del JB del .py
void llenandoBarcosJB(){
  int listo = 1;
    while (listo != 10){
      recibiendoPosiciones(2);//--------------------------------------------------------------
      listo = listo + 1; 
    }
}

//FUNCIONAL - Funciona para recibir los MISILES del JB del .py
void llenandoMisilesJB(){
  int listo = 1;
    while (listo != 10){
      recibiendoPosiciones(3);//--------------------------------------------------------------
      listo = listo + 1; 
    }
}


//FUNCIONAL - Funcion para captar los datos de misiles y barcos que vienen de PYTHON  (esto se debe ejecutar cada vez por coordenada A1)
int recibiendoPosiciones(int user){
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
      
      //SE SUPONE QUE LO QUE NOS ESTA ENVIANDO EL .PY YA ESTA COMPROBADO QUE NO ESTA TOMADO----------------------------------------------------------------------------------------------------
      //De todas formas voy a utilizar la funcion de "isTaken()"
      istaken(user, pulsacion1, pulsacion2);   //De esta forma se verifica que no estan repetidas y por ende actualice la matriz
      
    }
  }
}

//FUNCIONAL - ATAQUE JA MISILES - JB BARCOS   &&&&&    ATAQUE JB MISILES - JA BARCOS
void comprobarPosicionAtaque(int jugador){ 
  for(int i=0; i < FILA_MATRIZ; i++){
    for(int j = 0; j < COLUMNA_MATRIZ; j++){
      if(jugador == 1){
        if(JA_Misiles[i][j] == 'X' and JB_Barcos[i][j] == 'X'){	//JA le dio a un barco del JUGADOR B
          comprobarAtaque(1,i,j);
        } 
      }else{
        if(jugador == 2){
          if(JB_Misiles[i][j] == 'X' and JA_Barcos[i][j] == 'X'){	//JB le dio a un barco del JUGADOR A
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

//FUNCIONAL - Funcion para Mostrar el puntaje de ambos jugadores luego ataque
void mostrarPuntaje(){
  //JUGADOR A
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Jugador A:");
  lcd.setCursor(1,1);
  lcd.print("Aciertos->");
  lcd.setCursor(12,1);
  lcd.print(cantAciertosJA);
  delay(1000);

  lcd.setCursor(0,1);
  lcd.print("                ");

  lcd.setCursor(1,1);
  lcd.print("Puntaje->");
  lcd.setCursor(12,1);
  lcd.print(puntuacionJA);
  delay(1000);

  //JUGADOR B
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Jugador B:");
  lcd.setCursor(1,1);
  lcd.print("Aciertos->");
  lcd.setCursor(12,1);
  lcd.print(cantAciertosJB);
  delay(1000);

  lcd.setCursor(0,1);
  lcd.print("                ");

  lcd.setCursor(1,1);
  lcd.print("Puntaje->");
  lcd.setCursor(12,1);
  lcd.print(puntuacionJB);
  delay(1000);
  lcd.clear();
}


//FUNCIONAL - Funcion para captar las coordenadas uintroducidas por el usuario mediant el keypad
void captarPosicion(char pulsacion, int user){
  
  if (pulsacion1 == ' ' and pulsacion2 == ' '){
    pulsacion1 = pulsacion;
    //Serial.print("pulsacion1 ---> ");					GUARDAMOS EL PRIMER VALOR TECLEADO EN ESTA VARIABLE -> "pulsacion1"
    //Serial.println(pulsacion1);
    counterInit = counterInit + 1;
  }else{
    if (pulsacion1 != ' ' and pulsacion2 == ' '){
      pulsacion2 = pulsacion;
      //Serial.print("pulsacion2 ---> ");				GUARDAMOS EL SEGUNDO VALOR TECLEADO EN ESTA VARIABLE -> "pulsacion2"
      //Serial.println(pulsacion2);
      counterInit = counterInit + 1;
    }
  }
  
  //En este punto, ya tenemos las coordenadas de en donde colocaresmos nuestros barcos o misiles....AHORA LLENAMOS LA MATRIZ QUE QUERRAMOS

  if(counterInit == 2){  
    if ((pulsacion1 == 'A' or pulsacion1 ==  'B' or pulsacion1 ==  'C' or pulsacion1 ==  'D') and (pulsacion2 == 'A' or pulsacion2 ==  'B' or pulsacion2 ==  'C' or pulsacion2 ==  'D')){   //Para este caso, comprobamos que PULSACION1 y PULSACION2 son letras (CASO QUE NO PUEDE PASAR) 
       limpiarRegistroPulsaciones(); 
	   error();
       Serial.println("Las coordenadas NO pueden ser de DOBLE letra");
    }else {
      if ((pulsacion1 == '0' or pulsacion1 == '1' or pulsacion1 == '2' or pulsacion1 == '3' or pulsacion1 == '4' or pulsacion1 == '5' or pulsacion1 == '6' or pulsacion1 == '7' or pulsacion1 == '8' or pulsacion1 == '9') and (pulsacion2 == '0' or pulsacion2 == '1' or pulsacion2 == '2' or pulsacion2 == '3' or pulsacion2 == '4' or pulsacion2 == '5' or pulsacion2 == '6' or pulsacion2 == '7' or pulsacion2 == '8' or pulsacion2 == '9')){
        limpiarRegistroPulsaciones();
		error();
        Serial.println("Las coordenadas NO pueden ser de DOBLE numero");
      }else{
        if(pulsacion1 == 'A' or pulsacion1 ==  'B' or pulsacion1 ==  'C' or pulsacion1 ==  'D'){
          boolean y = istaken(user, pulsacion1,pulsacion2);
          if (y == false){
            counter = counter + 1; 
            exito();
            Serial.println("Posicion agregada con exito");
          }else{
            error();
            Serial.println("Ya esta posicion esta tomada");
          }
		  limpiarRegistroPulsaciones(); 
        }else{
          if(pulsacion2 == 'A' or pulsacion2 ==  'B' or pulsacion2 ==  'C' or pulsacion2 ==  'D'){
            boolean y = istaken(user, pulsacion2,pulsacion1);
            if (y == false){
              counter = counter + 1; 
              exito();
              Serial.println("Posicion agregada con exito");
            }else{
              error();
              Serial.println("Ya esta posicion esta tomada");
            }
            limpiarRegistroPulsaciones();
          }
        } 
      }           
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



//FUNCIONAL - Funcion para captar en guerra los misiles del JA
void misilesJA(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Seleccione con"); 
  lcd.setCursor(0,1);
  lcd.print("el keypad las");
  delay(100); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("posiciones de"); 
  lcd.setCursor(0,1);
  lcd.print("los misiles");
  delay(100); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Posicion...");
  datoWhile = 1;
  lcd.setCursor(9,1);
  lcd.print("Cant:");
  lcd.print(counter);
  while (datoWhile){
    key = keypad.getKey();
    if(key){
      lcd.setCursor(3,1);
      lcd.print(key);
      captarPosicion(key, 1);
      //Serial.print("-------------------------------------------->   ");
      //Serial.println(counter);
      lcd.setCursor(9,1);
      lcd.print("Cant:");
      lcd.print(counter); 
      if(counter == 10){ //---------------------------------------------------------------------CAMBIO CANTIDAD MISILES
        counter = 0; 
        datoWhile = 0;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Posiciones de ");
        lcd.setCursor(0,1);
        lcd.print("misiles agregadas!");
        delay(2);
        contadorInicio = 1;        //AGREGAR AL FINAL DE LA GUERRA QUE SE PONGA EN 0
      }
    }
  }
  lcd.clear();
}

//FUNCIONAL - Funcion para limpiar las variables encargadas de captar las pulsaciones del keypad, cuando ya se tengan las dos coordenadas
void limpiarRegistroPulsaciones(){
  pulsacion1 = ' ';
  pulsacion2 = ' ';
  counterInit = 0;
}

//MOSTRANDOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO-------------------------------------------------------------

//FUNCIONAL - Funcion para mostrar el ESPERANDO en el LCD
void esperando(){
    lcd.setCursor(0,0);
    lcd.print("Esperando a JB...");
    delay(500);
  	lcd.clear();
}

//FUNCIONAL - Funcion para mostrar el ERROR en el LCD
void error(){
  lcd.setCursor(11,0);
  lcd.print("Error");
  delay(500);
  lcd.setCursor(11,0);
  lcd.print("     ");
}

//FUNCIONAL - Funcion para mostrar el EXITO en el LCD
void exito(){
  lcd.setCursor(11,0);
  lcd.print("Exito!");
  delay(500);
  lcd.setCursor(11,0);
  lcd.print("     ");
}


//FUNCIONAL - Funcion para mostrar mensaje de que ESPERAMOS al JB
void mensajeEsperaJB(int user){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Esperamos a que"); 
  lcd.setCursor(0,1);
  lcd.print("el jugador B");
  delay(100); 
  lcd.clear();					
  lcd.setCursor(0,0);
  lcd.print("coloque las"); 
  lcd.setCursor(0,1);
  lcd.print("posiciones de sus");
  delay(100); 
  lcd.clear();
  if(user == 2){
    lcd.setCursor(0,0);
    lcd.print("Barcos ..."); 
    delay(100);
    
  }else{
    lcd.setCursor(0,0);
    lcd.print("Misiles ..."); 
    delay(100);
  }
  lcd.clear(); 
}

//FUNCIONAL - Funcioes para MOSTRAR LAS MATRICES
void verMatrizBarcosJA(){
  lcd.clear();
  //Primera FILA del LCD
  lcd.setCursor(0,0);
  lcd.print('|'); 
  lcd.setCursor(1,0);
  lcd.print(JA_Barcos[0][0]); 
  lcd.setCursor(2,0);
  lcd.print(JA_Barcos[0][1]);
  lcd.setCursor(3,0);
  lcd.print(JA_Barcos[0][2]);
  lcd.setCursor(4,0);
  lcd.print(JA_Barcos[0][3]);
  lcd.setCursor(5,0);
  lcd.print(JA_Barcos[0][4]); 
  lcd.setCursor(6,0);
  lcd.print(JA_Barcos[0][5]);
  lcd.setCursor(7,0);
  lcd.print(JA_Barcos[0][6]);
  lcd.setCursor(8,0);
  lcd.print(JA_Barcos[0][7]);
  lcd.setCursor(9,0);
  lcd.print(JA_Barcos[0][8]); 
  lcd.setCursor(10,0);
  lcd.print(JA_Barcos[0][9]); 
  lcd.setCursor(11,0);
  lcd.print('|');
  
  lcd.setCursor(14,0);
  lcd.print("P1");
  
  lcd.setCursor(13,1);
  lcd.print("3=+");
  
  //Segunda FILA del LCD
  lcd.setCursor(0,1);
  lcd.print('|'); 
  lcd.setCursor(1,1);
  lcd.print(JA_Barcos[1][0]); 
  lcd.setCursor(2,1);
  lcd.print(JA_Barcos[1][1]);
  lcd.setCursor(3,1);
  lcd.print(JA_Barcos[1][2]);
  lcd.setCursor(4,1);
  lcd.print(JA_Barcos[1][3]);
  lcd.setCursor(5,1);
  lcd.print(JA_Barcos[1][4]); 
  lcd.setCursor(6,1);
  lcd.print(JA_Barcos[1][5]);
  lcd.setCursor(7,1);
  lcd.print(JA_Barcos[1][6]);
  lcd.setCursor(8,1);
  lcd.print(JA_Barcos[1][7]);
  lcd.setCursor(9,1);
  lcd.print(JA_Barcos[1][8]); 
  lcd.setCursor(10,1);
  lcd.print(JA_Barcos[1][9]); 
  lcd.setCursor(11,1);
  lcd.print('|');
  dato = 1; 
  while(dato){
    key = keypad.getKey();
    if (key == '3'){
      lcd.clear();
      //Primera FILA del LCD
      lcd.setCursor(0,0);
      lcd.print('|'); 
      lcd.setCursor(1,0);
      lcd.print(JA_Barcos[2][0]); 
      lcd.setCursor(2,0);
      lcd.print(JA_Barcos[2][1]);
      lcd.setCursor(3,0);
      lcd.print(JA_Barcos[2][2]);
      lcd.setCursor(4,0);
      lcd.print(JA_Barcos[2][3]);
      lcd.setCursor(5,0);
      lcd.print(JA_Barcos[2][4]); 
      lcd.setCursor(6,0);
      lcd.print(JA_Barcos[2][5]);
      lcd.setCursor(7,0);
      lcd.print(JA_Barcos[2][6]);
      lcd.setCursor(8,0);
      lcd.print(JA_Barcos[2][7]);
      lcd.setCursor(9,0);
      lcd.print(JA_Barcos[2][8]); 
      lcd.setCursor(10,0);
      lcd.print(JA_Barcos[2][9]); 
      lcd.setCursor(11,0);
      lcd.print('|'); 
      
      lcd.setCursor(14,0);
      lcd.print("P2");
      
      lcd.setCursor(13,1);
      lcd.print("0=-");
      
      //Segunda FILA del LCD
      lcd.setCursor(0,1);
      lcd.print('|'); 
      lcd.setCursor(1,1);
      lcd.print(JA_Barcos[3][0]); 
      lcd.setCursor(2,1);
      lcd.print(JA_Barcos[3][1]);
      lcd.setCursor(3,1);
      lcd.print(JA_Barcos[3][2]);
      lcd.setCursor(4,1);
      lcd.print(JA_Barcos[3][3]);
      lcd.setCursor(5,1);
      lcd.print(JA_Barcos[3][4]); 
      lcd.setCursor(6,1);
      lcd.print(JA_Barcos[3][5]);
      lcd.setCursor(7,1);
      lcd.print(JA_Barcos[3][6]);
      lcd.setCursor(8,1);
      lcd.print(JA_Barcos[3][7]);
      lcd.setCursor(9,1);
      lcd.print(JA_Barcos[3][8]); 
      lcd.setCursor(10,1);
      lcd.print(JA_Barcos[3][9]); 
      lcd.setCursor(11,1);
      lcd.print('|'); 
    }
    if (key == '0'){
		dato = 0;
    }
  }
}

void verMatrizMisilesJA(){
  lcd.clear();
  //Primera FILA del LCD
  lcd.setCursor(0,0);
  lcd.print('|'); 
  lcd.setCursor(1,0);
  lcd.print(JA_Misiles[0][0]); 
  lcd.setCursor(2,0);
  lcd.print(JA_Misiles[0][1]);
  lcd.setCursor(3,0);
  lcd.print(JA_Misiles[0][2]);
  lcd.setCursor(4,0);
  lcd.print(JA_Misiles[0][3]);
  lcd.setCursor(5,0);
  lcd.print(JA_Misiles[0][4]); 
  lcd.setCursor(6,0);
  lcd.print(JA_Misiles[0][5]);
  lcd.setCursor(7,0);
  lcd.print(JA_Misiles[0][6]);
  lcd.setCursor(8,0);
  lcd.print(JA_Misiles[0][7]);
  lcd.setCursor(9,0);
  lcd.print(JA_Misiles[0][8]); 
  lcd.setCursor(10,0);
  lcd.print(JA_Misiles[0][9]); 
  lcd.setCursor(11,0);
  lcd.print('|');
  
  lcd.setCursor(14,0);
  lcd.print("P1");
  
  lcd.setCursor(13,1);
  lcd.print("3=+");
  
  //Segunda FILA del LCD
  lcd.setCursor(0,1);
  lcd.print('|'); 
  lcd.setCursor(1,1);
  lcd.print(JA_Misiles[1][0]); 
  lcd.setCursor(2,1);
  lcd.print(JA_Misiles[1][1]);
  lcd.setCursor(3,1);
  lcd.print(JA_Misiles[1][2]);
  lcd.setCursor(4,1);
  lcd.print(JA_Misiles[1][3]);
  lcd.setCursor(5,1);
  lcd.print(JA_Misiles[1][4]); 
  lcd.setCursor(6,1);
  lcd.print(JA_Misiles[1][5]);
  lcd.setCursor(7,1);
  lcd.print(JA_Misiles[1][6]);
  lcd.setCursor(8,1);
  lcd.print(JA_Misiles[1][7]);
  lcd.setCursor(9,1);
  lcd.print(JA_Misiles[1][8]); 
  lcd.setCursor(10,1);
  lcd.print(JA_Misiles[1][9]); 
  lcd.setCursor(11,1);
  lcd.print('|');
  dato = 1; 
  while(dato){
    key = keypad.getKey();
    if (key == '3'){
      lcd.clear();
      //Primera FILA del LCD
      lcd.setCursor(0,0);
      lcd.print('|'); 
      lcd.setCursor(1,0);
      lcd.print(JA_Misiles[2][0]); 
      lcd.setCursor(2,0);
      lcd.print(JA_Misiles[2][1]);
      lcd.setCursor(3,0);
      lcd.print(JA_Misiles[2][2]);
      lcd.setCursor(4,0);
      lcd.print(JA_Misiles[2][3]);
      lcd.setCursor(5,0);
      lcd.print(JA_Misiles[2][4]); 
      lcd.setCursor(6,0);
      lcd.print(JA_Misiles[2][5]);
      lcd.setCursor(7,0);
      lcd.print(JA_Misiles[2][6]);
      lcd.setCursor(8,0);
      lcd.print(JA_Misiles[2][7]);
      lcd.setCursor(9,0);
      lcd.print(JA_Misiles[2][8]); 
      lcd.setCursor(10,0);
      lcd.print(JA_Misiles[2][9]);
      lcd.setCursor(11,0);
      lcd.print('|'); 
      
      lcd.setCursor(14,0);
      lcd.print("P2");
      
      lcd.setCursor(13,1);
      lcd.print("0=-");
      
      //Segunda FILA del LCD
      lcd.setCursor(0,1);
      lcd.print('|'); 
      lcd.setCursor(1,1);
      lcd.print(JA_Misiles[3][0]); 
      lcd.setCursor(2,1);
      lcd.print(JA_Misiles[3][1]);
      lcd.setCursor(3,1);
      lcd.print(JA_Misiles[3][2]);
      lcd.setCursor(4,1);
      lcd.print(JA_Misiles[3][3]);
      lcd.setCursor(5,1);
      lcd.print(JA_Misiles[3][4]); 
      lcd.setCursor(6,1);
      lcd.print(JA_Misiles[3][5]);
      lcd.setCursor(7,1);
      lcd.print(JA_Misiles[3][6]);
      lcd.setCursor(8,1);
      lcd.print(JA_Misiles[3][7]);
      lcd.setCursor(9,1);
      lcd.print(JA_Misiles[3][8]);
      lcd.setCursor(10,1);
      lcd.print(JA_Misiles[3][9]);
      lcd.setCursor(11,1);
      lcd.print('|'); 
    }
    if (key == '0'){
		dato = 0;
    }
  }
}

void verMatrizBarcosJB(){
  lcd.clear();
  //Primera FILA del LCD
  lcd.setCursor(0,0);
  lcd.print('|'); 
  lcd.setCursor(1,0);
  lcd.print(JB_Barcos[0][0]); 
  lcd.setCursor(2,0);
  lcd.print(JB_Barcos[0][1]);
  lcd.setCursor(3,0);
  lcd.print(JB_Barcos[0][2]);
  lcd.setCursor(4,0);
  lcd.print(JB_Barcos[0][3]);
  lcd.setCursor(5,0);
  lcd.print(JB_Barcos[0][4]); 
  lcd.setCursor(6,0);
  lcd.print(JB_Barcos[0][5]);
  lcd.setCursor(7,0);
  lcd.print(JB_Barcos[0][6]);
  lcd.setCursor(8,0);
  lcd.print(JB_Barcos[0][7]);
  lcd.setCursor(9,0);
  lcd.print(JB_Barcos[0][8]); 
  lcd.setCursor(10,0);
  lcd.print(JB_Barcos[0][9]); 
  lcd.setCursor(11,0);
  lcd.print('|');
  
  lcd.setCursor(14,0);
  lcd.print("P1");
  
  lcd.setCursor(13,1);
  lcd.print("3=+");
  
  //Segunda FILA del LCD
  lcd.setCursor(0,1);
  lcd.print('|'); 
  lcd.setCursor(1,1);
  lcd.print(JB_Barcos[1][0]); 
  lcd.setCursor(2,1);
  lcd.print(JB_Barcos[1][1]);
  lcd.setCursor(3,1);
  lcd.print(JB_Barcos[1][2]);
  lcd.setCursor(4,1);
  lcd.print(JB_Barcos[1][3]);
  lcd.setCursor(5,1);
  lcd.print(JB_Barcos[1][4]); 
  lcd.setCursor(6,1);
  lcd.print(JB_Barcos[1][5]);
  lcd.setCursor(7,1);
  lcd.print(JB_Barcos[1][6]);
  lcd.setCursor(8,1);
  lcd.print(JB_Barcos[1][7]);
  lcd.setCursor(9,1);
  lcd.print(JB_Barcos[1][8]); 
  lcd.setCursor(10,1);
  lcd.print(JB_Barcos[1][9]); 
  lcd.setCursor(11,1);
  lcd.print('|');
  dato = 1; 
  while(dato){
    key = keypad.getKey();
    if (key == '3'){
      lcd.clear();
      //Primera FILA del LCD
      lcd.setCursor(0,0);
      lcd.print('|'); 
      lcd.setCursor(1,0);
      lcd.print(JB_Barcos[2][0]); 
      lcd.setCursor(2,0);
      lcd.print(JB_Barcos[2][1]);
      lcd.setCursor(3,0);
      lcd.print(JB_Barcos[2][2]);
      lcd.setCursor(4,0);
      lcd.print(JB_Barcos[2][3]);
      lcd.setCursor(5,0);
      lcd.print(JB_Barcos[2][4]); 
      lcd.setCursor(6,0);
      lcd.print(JB_Barcos[2][5]);
      lcd.setCursor(7,0);
      lcd.print(JB_Barcos[2][6]);
      lcd.setCursor(8,0);
      lcd.print(JB_Barcos[2][7]);
      lcd.setCursor(9,0);
      lcd.print(JB_Barcos[2][8]);
      lcd.setCursor(10,0);
      lcd.print(JB_Barcos[2][8]);
      lcd.setCursor(11,0);
      lcd.print('|'); 
      
      lcd.setCursor(14,0);
      lcd.print("P2");
      
      lcd.setCursor(13,1);
      lcd.print("0=-");
      
      //Segunda FILA del LCD
      lcd.setCursor(0,1);
      lcd.print('|'); 
      lcd.setCursor(1,1);
      lcd.print(JB_Barcos[3][0]); 
      lcd.setCursor(2,1);
      lcd.print(JB_Barcos[3][1]);
      lcd.setCursor(3,1);
      lcd.print(JB_Barcos[3][2]);
      lcd.setCursor(4,1);
      lcd.print(JB_Barcos[3][3]);
      lcd.setCursor(5,1);
      lcd.print(JB_Barcos[3][4]); 
      lcd.setCursor(6,1);
      lcd.print(JB_Barcos[3][5]);
      lcd.setCursor(7,1);
      lcd.print(JB_Barcos[3][6]);
      lcd.setCursor(8,1);
      lcd.print(JB_Barcos[3][7]);
      lcd.setCursor(9,1);
      lcd.print(JB_Barcos[3][8]);
      lcd.setCursor(10,1);
      lcd.print(JB_Barcos[3][9]);
      lcd.setCursor(11,1);
      lcd.print('|'); 
    }
    if (key == '0'){
		dato = 0;
    }
  }

}

void verMatrizMisilesJB(){
  lcd.clear();
  //Primera FILA del LCD
  lcd.setCursor(0,0);
  lcd.print('|'); 
  lcd.setCursor(1,0);
  lcd.print(JB_Misiles[0][0]); 
  lcd.setCursor(2,0);
  lcd.print(JB_Misiles[0][1]);
  lcd.setCursor(3,0);
  lcd.print(JB_Misiles[0][2]);
  lcd.setCursor(4,0);
  lcd.print(JB_Misiles[0][3]);
  lcd.setCursor(5,0);
  lcd.print(JB_Misiles[0][4]); 
  lcd.setCursor(6,0);
  lcd.print(JB_Misiles[0][5]);
  lcd.setCursor(7,0);
  lcd.print(JB_Misiles[0][6]);
  lcd.setCursor(8,0);
  lcd.print(JB_Misiles[0][7]);
  lcd.setCursor(9,0);
  lcd.print(JB_Misiles[0][8]); 
  lcd.setCursor(10,0);
  lcd.print(JB_Misiles[0][9]); 
  lcd.setCursor(11,0);
  lcd.print('|');
  
  lcd.setCursor(14,0);
  lcd.print("P1");
  
  lcd.setCursor(13,1);
  lcd.print("3=+");
  
  //Segunda FILA del LCD
  lcd.setCursor(0,1);
  lcd.print('|'); 
  lcd.setCursor(1,1);
  lcd.print(JB_Misiles[1][0]); 
  lcd.setCursor(2,1);
  lcd.print(JB_Misiles[1][1]);
  lcd.setCursor(3,1);
  lcd.print(JB_Misiles[1][2]);
  lcd.setCursor(4,1);
  lcd.print(JB_Misiles[1][3]);
  lcd.setCursor(5,1);
  lcd.print(JB_Misiles[1][4]); 
  lcd.setCursor(6,1);
  lcd.print(JB_Misiles[1][5]);
  lcd.setCursor(7,1);
  lcd.print(JB_Misiles[1][6]);
  lcd.setCursor(8,1);
  lcd.print(JB_Misiles[1][7]);
  lcd.setCursor(9,1);
  lcd.print(JB_Misiles[1][8]); 
  lcd.setCursor(10,1);
  lcd.print(JB_Misiles[1][9]); 
  lcd.setCursor(11,1);
  lcd.print('|');
  dato = 1; 
  while(dato){
    key = keypad.getKey();
    if (key == '3'){
      lcd.clear();
      //Primera FILA del LCD
      lcd.setCursor(0,0);
      lcd.print('|'); 
      lcd.setCursor(1,0);
      lcd.print(JB_Misiles[2][0]); 
      lcd.setCursor(2,0);
      lcd.print(JB_Misiles[2][1]);
      lcd.setCursor(3,0);
      lcd.print(JB_Misiles[2][2]);
      lcd.setCursor(4,0);
      lcd.print(JB_Misiles[2][3]);
      lcd.setCursor(5,0);
      lcd.print(JB_Misiles[2][4]); 
      lcd.setCursor(6,0);
      lcd.print(JB_Misiles[2][5]);
      lcd.setCursor(7,0);
      lcd.print(JB_Misiles[2][6]);
      lcd.setCursor(8,0);
      lcd.print(JB_Misiles[2][7]);
      lcd.setCursor(9,0);
      lcd.print(JB_Misiles[2][8]); 
      lcd.setCursor(10,0);
      lcd.print(JB_Misiles[2][9]);
      lcd.setCursor(11,0);
      lcd.print('|'); 
      
      lcd.setCursor(14,0);
      lcd.print("P2");
      
      lcd.setCursor(13,1);
      lcd.print("0=-");
      
      //Segunda FILA del LCD
      lcd.setCursor(0,1);
      lcd.print('|'); 
      lcd.setCursor(1,1);
      lcd.print(JB_Misiles[3][0]); 
      lcd.setCursor(2,1);
      lcd.print(JB_Misiles[3][1]);
      lcd.setCursor(3,1);
      lcd.print(JB_Misiles[3][2]);
      lcd.setCursor(4,1);
      lcd.print(JB_Misiles[3][3]);
      lcd.setCursor(5,1);
      lcd.print(JB_Misiles[3][4]); 
      lcd.setCursor(6,1);
      lcd.print(JB_Misiles[3][5]);
      lcd.setCursor(7,1);
      lcd.print(JB_Misiles[3][6]);
      lcd.setCursor(8,1);
      lcd.print(JB_Misiles[3][7]);
      lcd.setCursor(9,1);
      lcd.print(JB_Misiles[3][8]); 
      lcd.setCursor(10,1);
      lcd.print(JB_Misiles[3][9]);
      lcd.setCursor(11,1);
      lcd.print('|'); 
    }
    if (key == '0'){
		dato = 0;
    }
  }


}

void limpiarMatrizBarcosJA() {
  JA_Barcos[0][0] = 'O';
  JA_Barcos[0][1] = 'O';
  JA_Barcos[0][2] = 'O';
  JA_Barcos[0][3] = 'O';
  JA_Barcos[0][4] = 'O';
  JA_Barcos[0][5] = 'O';
  JA_Barcos[0][6] = 'O';
  JA_Barcos[0][7] = 'O';
  JA_Barcos[0][8] = 'O';
  JA_Barcos[0][9] = 'O';

  JA_Barcos[1][0] = 'O';
  JA_Barcos[1][1] = 'O';
  JA_Barcos[1][2] = 'O';
  JA_Barcos[1][3] = 'O';
  JA_Barcos[1][4] = 'O';
  JA_Barcos[1][5] = 'O';
  JA_Barcos[1][6] = 'O';
  JA_Barcos[1][7] = 'O';
  JA_Barcos[1][8] = 'O';
  JA_Barcos[1][9] = 'O';

  JA_Barcos[2][0] = 'O';
  JA_Barcos[2][1] = 'O';
  JA_Barcos[2][2] = 'O';
  JA_Barcos[2][3] = 'O';
  JA_Barcos[2][4] = 'O';
  JA_Barcos[2][5] = 'O';
  JA_Barcos[2][6] = 'O';
  JA_Barcos[2][7] = 'O';
  JA_Barcos[2][8] = 'O';
  JA_Barcos[2][9] = 'O';

  JA_Barcos[3][0] = 'O';
  JA_Barcos[3][1] = 'O';
  JA_Barcos[3][2] = 'O';
  JA_Barcos[3][3] = 'O';
  JA_Barcos[3][4] = 'O';
  JA_Barcos[3][5] = 'O';
  JA_Barcos[3][6] = 'O';
  JA_Barcos[3][7] = 'O';
  JA_Barcos[3][8] = 'O';
  JA_Barcos[3][9] = 'O';
}

void limpiarMatrizBarcosJB() {
  JB_Barcos[0][0] = 'O';
  JB_Barcos[0][1] = 'O';
  JB_Barcos[0][2] = 'O';
  JB_Barcos[0][3] = 'O';
  JB_Barcos[0][4] = 'O';
  JB_Barcos[0][5] = 'O';
  JB_Barcos[0][6] = 'O';
  JB_Barcos[0][7] = 'O';
  JB_Barcos[0][8] = 'O';
  JB_Barcos[0][9] = 'O';

  JB_Barcos[1][0] = 'O';
  JB_Barcos[1][1] = 'O';
  JB_Barcos[1][2] = 'O';
  JB_Barcos[1][3] = 'O';
  JB_Barcos[1][4] = 'O';
  JB_Barcos[1][5] = 'O';
  JB_Barcos[1][6] = 'O';
  JB_Barcos[1][7] = 'O';
  JB_Barcos[1][8] = 'O';
  JB_Barcos[1][9] = 'O';

  JB_Barcos[2][0] = 'O';
  JB_Barcos[2][1] = 'O';
  JB_Barcos[2][2] = 'O';
  JB_Barcos[2][3] = 'O';
  JB_Barcos[2][4] = 'O';
  JB_Barcos[2][5] = 'O';
  JB_Barcos[2][6] = 'O';
  JB_Barcos[2][7] = 'O';
  JB_Barcos[2][8] = 'O';
  JB_Barcos[2][9] = 'O';

  JB_Barcos[3][0] = 'O';
  JB_Barcos[3][1] = 'O';
  JB_Barcos[3][2] = 'O';
  JB_Barcos[3][3] = 'O';
  JB_Barcos[3][4] = 'O';
  JB_Barcos[3][5] = 'O';
  JB_Barcos[3][6] = 'O';
  JB_Barcos[3][7] = 'O';
  JB_Barcos[3][8] = 'O';
  JB_Barcos[3][9] = 'O';
}



void limpiarMatrizMisilesJA() {
  JA_Misiles[0][0] = 'O';
  JA_Misiles[0][1] = 'O';
  JA_Misiles[0][2] = 'O';
  JA_Misiles[0][3] = 'O';
  JA_Misiles[0][4] = 'O';
  JA_Misiles[0][5] = 'O';
  JA_Misiles[0][6] = 'O';
  JA_Misiles[0][7] = 'O';
  JA_Misiles[0][8] = 'O';
  JA_Misiles[0][9] = 'O';

  JA_Misiles[1][0] = 'O';
  JA_Misiles[1][1] = 'O';
  JA_Misiles[1][2] = 'O';
  JA_Misiles[1][3] = 'O';
  JA_Misiles[1][4] = 'O';
  JA_Misiles[1][5] = 'O';
  JA_Misiles[1][6] = 'O';
  JA_Misiles[1][7] = 'O';
  JA_Misiles[1][8] = 'O';
  JA_Misiles[1][9] = 'O';

  JA_Misiles[2][0] = 'O';
  JA_Misiles[2][1] = 'O';
  JA_Misiles[2][2] = 'O';
  JA_Misiles[2][3] = 'O';
  JA_Misiles[2][4] = 'O';
  JA_Misiles[2][5] = 'O';
  JA_Misiles[2][6] = 'O';
  JA_Misiles[2][7] = 'O';
  JA_Misiles[2][8] = 'O';
  JA_Misiles[2][9] = 'O';

  JA_Misiles[3][0] = 'O';
  JA_Misiles[3][1] = 'O';
  JA_Misiles[3][2] = 'O';
  JA_Misiles[3][3] = 'O';
  JA_Misiles[3][4] = 'O';
  JA_Misiles[3][5] = 'O';
  JA_Misiles[3][6] = 'O';
  JA_Misiles[3][7] = 'O';
  JA_Misiles[3][8] = 'O';  
  JA_Misiles[3][9] = 'O';
}


void limpiarMatrizMisilesJB() {
  JB_Misiles[0][0] = 'O';
  JB_Misiles[0][1] = 'O';
  JB_Misiles[0][2] = 'O';
  JB_Misiles[0][3] = 'O';
  JB_Misiles[0][4] = 'O';
  JB_Misiles[0][5] = 'O';
  JB_Misiles[0][6] = 'O';
  JB_Misiles[0][7] = 'O';
  JB_Misiles[0][8] = 'O';
  JB_Misiles[0][9] = 'O';

  JB_Misiles[1][0] = 'O';
  JB_Misiles[1][1] = 'O';
  JB_Misiles[1][2] = 'O';
  JB_Misiles[1][3] = 'O';
  JB_Misiles[1][4] = 'O';
  JB_Misiles[1][5] = 'O';
  JB_Misiles[1][6] = 'O';
  JB_Misiles[1][7] = 'O';
  JB_Misiles[1][8] = 'O';
  JB_Misiles[1][9] = 'O';

  JB_Misiles[2][0] = 'O';
  JB_Misiles[2][1] = 'O';
  JB_Misiles[2][2] = 'O';
  JB_Misiles[2][3] = 'O';
  JB_Misiles[2][4] = 'O';
  JB_Misiles[2][5] = 'O';
  JB_Misiles[2][6] = 'O';
  JB_Misiles[2][7] = 'O';
  JB_Misiles[2][8] = 'O';
  JB_Misiles[2][9] = 'O';

  JB_Misiles[3][0] = 'O';
  JB_Misiles[3][1] = 'O';
  JB_Misiles[3][2] = 'O';
  JB_Misiles[3][3] = 'O';
  JB_Misiles[3][4] = 'O';
  JB_Misiles[3][5] = 'O';
  JB_Misiles[3][6] = 'O';
  JB_Misiles[3][7] = 'O';
  JB_Misiles[3][8] = 'O';
  JB_Misiles[3][9] = 'O';
}

//FUNCIONAL - Funcion para mostrar matriz de barcos luego de ataque
void verMatrizBarcosJA2(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Matriz barcos JA"); 
  lcd.setCursor(0,1);
  lcd.print("luego de ataque "); 
  delay(500);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print('|'); 
  lcd.setCursor(1,0);
  lcd.print(JA_Barcos[0][0]); 
  lcd.setCursor(2,0);
  lcd.print(JA_Barcos[0][1]);
  lcd.setCursor(3,0);
  lcd.print(JA_Barcos[0][2]);
  lcd.setCursor(4,0);
  lcd.print(JA_Barcos[0][3]);
  lcd.setCursor(5,0);
  lcd.print(JA_Barcos[0][4]); 
  lcd.setCursor(6,0);
  lcd.print(JA_Barcos[0][5]);
  lcd.setCursor(7,0);
  lcd.print(JA_Barcos[0][6]);
  lcd.setCursor(8,0);
  lcd.print(JA_Barcos[0][7]);
  lcd.setCursor(9,0);
  lcd.print(JA_Barcos[0][8]); 
  lcd.setCursor(10,0);
  lcd.print(JA_Barcos[0][9]); 
  lcd.setCursor(11,0);
  lcd.print('|');
  
  lcd.setCursor(0,1);
  lcd.print('|'); 
  lcd.setCursor(1,1);
  lcd.print(JA_Barcos[1][0]); 
  lcd.setCursor(2,1);
  lcd.print(JA_Barcos[1][1]);
  lcd.setCursor(3,1);
  lcd.print(JA_Barcos[1][2]);
  lcd.setCursor(4,1);
  lcd.print(JA_Barcos[1][3]);
  lcd.setCursor(5,1);
  lcd.print(JA_Barcos[1][4]); 
  lcd.setCursor(6,1);
  lcd.print(JA_Barcos[1][5]);
  lcd.setCursor(7,1);
  lcd.print(JA_Barcos[1][6]);
  lcd.setCursor(8,1);
  lcd.print(JA_Barcos[1][7]);
  lcd.setCursor(9,1);
  lcd.print(JA_Barcos[1][8]); 
  lcd.setCursor(10,1);
  lcd.print(JA_Barcos[1][9]); 
  lcd.setCursor(11,1);
  lcd.print('|');
  delay(1000);
  
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print('|'); 
  lcd.setCursor(1,0);
  lcd.print(JA_Barcos[2][0]); 
  lcd.setCursor(2,0);
  lcd.print(JA_Barcos[2][1]);
  lcd.setCursor(3,0);
  lcd.print(JA_Barcos[2][2]);
  lcd.setCursor(4,0);
  lcd.print(JA_Barcos[2][3]);
  lcd.setCursor(5,0);
  lcd.print(JA_Barcos[2][4]); 
  lcd.setCursor(6,0);
  lcd.print(JA_Barcos[2][5]);
  lcd.setCursor(7,0);
  lcd.print(JA_Barcos[2][6]);
  lcd.setCursor(8,0);
  lcd.print(JA_Barcos[2][7]);
  lcd.setCursor(9,0);
  lcd.print(JA_Barcos[2][8]); 
  lcd.setCursor(10,0);
  lcd.print(JA_Barcos[2][9]); 
  lcd.setCursor(11,0);
  lcd.print('|'); 

  lcd.setCursor(0,1);
  lcd.print('|'); 
  lcd.setCursor(1,1);
  lcd.print(JA_Barcos[3][0]); 
  lcd.setCursor(2,1);
  lcd.print(JA_Barcos[3][1]);
  lcd.setCursor(3,1);
  lcd.print(JA_Barcos[3][2]);
  lcd.setCursor(4,1);
  lcd.print(JA_Barcos[3][3]);
  lcd.setCursor(5,1);
  lcd.print(JA_Barcos[3][4]); 
  lcd.setCursor(6,1);
  lcd.print(JA_Barcos[3][5]);
  lcd.setCursor(7,1);
  lcd.print(JA_Barcos[3][6]);
  lcd.setCursor(8,1);
  lcd.print(JA_Barcos[3][7]);
  lcd.setCursor(9,1);
  lcd.print(JA_Barcos[3][8]); 
  lcd.setCursor(10,1);
  lcd.print(JA_Barcos[3][9]); 
  lcd.setCursor(11,1);
  lcd.print('|'); 
  delay(1000);
}






//FUNCIONAL ----------------------------------------------------------------















  
  

































































































