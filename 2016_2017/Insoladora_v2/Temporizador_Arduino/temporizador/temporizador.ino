#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);

//--------------------------------------
//Variables
volatile unsigned long contador_minutos = 0;
volatile int escribir_minutos = 0;
long T0_minutos = 0;

volatile unsigned long contador_segundos = 0;
volatile int escribir_segundos = 0;
long T0_segundos = 0;

unsigned long auxiliar = 0;

unsigned long tiempo = 0;

//--------------------------------------
// CONSTANTES 
const int LED = A0;
const int LED_ON = 6;
const int START = 4;

//--------------------------------------
//Funciones
void inicializacion (void){
  
  contador_minutos = 0;
  escribir_minutos = 0;
  T0_minutos = 0;
  
  contador_segundos = 0;
  escribir_segundos = 0;
  T0_segundos = 0;
  
  auxiliar = 0;
  tiempo = 0;

lcd.clear();
  
lcd.setCursor(0,0);
 lcd.write("Min");
 
 //MINUTOS
 lcd.setCursor(0,0);
 lcd.write("Min");
 //Decenas
 escribirMinutosDecenas(0);
 //Unidades
 escribirMinutosUnidades(1);
 
 //SEGUNDOS
 lcd.setCursor(5,0);
 lcd.write("Seg");
  //Decenas
 escribirSegundosDecenas(2);
 //Unidades
 escribirSegundosUnidades(3);
 
 //START
 lcd.setCursor(11,1);
 lcd.write("Start");
}


void escribirMinutosDecenas (int valor){
 lcd.setCursor(0,1);
 lcd.write(((char)valor+48));
}
void escribirMinutosUnidades (int valor){
 lcd.setCursor(1,1);
 lcd.write(((char)valor+48));
}
void escribirSegundosDecenas (int valor){
 lcd.setCursor(5,1);
 lcd.write(((char)valor+48));
}
void escribirSegundosUnidades (int valor){
 lcd.setCursor(6,1);
 lcd.write(((char)valor+48));
}

//RAIs

void actualizarminuotsLCD (void) {

 if ( millis() > T0_minutos  + 250) // Forma de evitar rebotes en interrupciones. millis se congela dentro de una
                            //  interr porque depende de timers e interr, pero el valor que tenia puede ser leido
                            // Rebote => entra de nuevo en la interrupcion antes de los 250 ms de margen dado => no hace nada
   {   if (contador_minutos < 99){
          contador_minutos ++;}
      else{contador_minutos = 0;}
          escribir_minutos = 1;
          
       T0_minutos = millis();
   } 

}

void actualizarsegundosLCD (void) {

 if ( millis() > T0_segundos  + 250) // Forma de evitar rebotes en interrupciones. millis se congela dentro de una
                            //  interr porque depende de timers e interr, pero el valor que tenia puede ser leido
                            // Rebote => entra de nuevo en la interrupcion antes de los 250 ms de margen dado => no hace nada
   {   if (contador_segundos < 59){
          contador_segundos ++;}
      else{contador_segundos = 0;}
          escribir_segundos = 1;
          
       T0_segundos = millis();
   } 

}
//--------------------------------------

void setup() {
  
  //PINES
 //*************************************

  pinMode (LED, OUTPUT);
  pinMode (LED_ON, OUTPUT);
  pinMode (START, INPUT);
  digitalWrite(LED,LOW);

 //PANTALLA LED 
 //*************************************
  
 lcd.begin(16, 2);
 
 
 //INTERRUPCIONES
 //*************************************
 attachInterrupt( 0, actualizarminuotsLCD, RISING); //  Tmabien configura el pin D2
 attachInterrupt( 1, actualizarsegundosLCD, RISING); //  Tmabien configura el pin D3
 
  //PUERTO SERIE
 //*************************************
 Serial.begin(9600);
}

//--------------------------------------
//Programa Principal
//--------------------------------------

void loop() {
 
 inicializacion(); 
  
 while (digitalRead(START)==LOW){
   
         if (escribir_minutos = 1){
         
           auxiliar = contador_minutos / 10;
           escribirMinutosDecenas(auxiliar);
           
           auxiliar = contador_minutos % 10;
           escribirMinutosUnidades(auxiliar);
           
           escribir_minutos = 0;
         
         }
         
          if (escribir_segundos = 1){
         
           auxiliar = contador_segundos / 10;
           escribirSegundosDecenas(auxiliar);
           
           auxiliar = contador_segundos % 10;
           escribirSegundosUnidades(auxiliar);
           
           escribir_segundos = 0;}
 }
 
 Serial.println(contador_minutos);
 Serial.println(contador_segundos);
 
 lcd.clear();
 lcd.write("Insolando...");
 
 digitalWrite(LED,HIGH);
 digitalWrite(LED_ON,HIGH);
 
 tiempo = (contador_minutos * 60 + contador_segundos) * 1000;
 
 Serial.println(tiempo);
   
 delay(tiempo);
 
 digitalWrite(LED,LOW);
 digitalWrite(LED_ON,LOW);
 
} 
