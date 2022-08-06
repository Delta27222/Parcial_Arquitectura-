void setup() {
  Serial.begin(9600);
}
//int numero = 10021;
//String hola = String(numero);
void loop() {
//  Serial.println(hola);
//  delay(1000);

enviarPuntaje(2722);


}



void enviarPuntaje(int puntuacionJB){
  String puntajeString = String(puntuacionJB);

  Serial.println(puntajeString);
  delay(1000); 
}
