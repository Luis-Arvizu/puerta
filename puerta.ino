//Librerias para suspender arduino.
#include <avr/sleep.h>
#include <avr/power.h>

//Define los pines por cada elemento

//Boton que cancela la alarma
const int interruptor = 4;
//Lector de reed switch
const int buttonpin = 2;
//Pin que controla el buzzer
const int buzzerPin = 9;
//Tiempo intermedio entre frecuencias de sonido
const int tempo = 113;
//Pin habilitado para despertar el arduino
const int pin2 = 2;

//Constantes que definen sonidos y frecuencias

//Cada elemento de beats define las veces que se ejecuta una nota
const int beats[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};
//Define la secuencia de notas
String notes = "cdfda ag cdfdg gf ";

//Funcion que se ejecuta al activarse el pin2
void pin2Interrupt(void){
  detachInterrupt(0);
}


//Inicia la suspencion de arduino
void enterSleep(void){
  
  attachInterrupt(0, pin2Interrupt, LOW);
  delay(100);

  //Establece el tipo de suspencion
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  //Habilita los metodos de suspencion
  sleep_enable();
  sleep_mode();
  sleep_disable(); 
}


void setup() {
  Serial.begin(9600);
  //Inicializa los pines
  pinMode(buttonpin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(interruptor, INPUT);
  pinMode(pin2, INPUT);

  //Suspende el arduino
  enterSleep();
}

//Variable de prueba
int i=0;

void loop() {

  //Imprime variable de prueba
  Serial.println(i++);

  //Evalua la activacion de reed switch
  if (digitalRead(buttonpin) == LOW){
    //Si el iman esta cerca ejecuta el tono 
    tono();
    //Habilita el modo suspencion
    enterSleep();
  }
}


//Retorna la frecuancia numerica a partir de un char
int frequency(char note) {
  int i;
  const int numNotes = 8; 

  //Definicion de notas
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  //Definicion de frecuencias por notas
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};

  //Busqueda de notas y cuando lo encuentra retorna la frecuencia equivalente
  for (i = 0; i < numNotes; i++){
    if (names[i] == note){
      return(frequencies[i]);     
    }
  }

  //Si no se encontro una nota, retorna 0 (Silencio)
  return(0);  
              
}

void tono(){
  int i, duration;

  //Recorre el string que contenga las notas, siempre y cuando el boton de interrupcion no sea presionado
  for (i = 0; i < notes.length() && digitalRead(interruptor) == HIGH; i++){
    //Define la duracion del tono apartir del tiempo promedio establecido y 
    //las veces que la nota sea repetida, la cual esta definida en el arreglo beats
    duration = beats[i] * tempo;  

    //Si el char es vacio, hay una pausa con tiempo promedio
    if (notes[i] == ' '){
      delay(duration);            
    }
    else{
      tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration);            
    }
    delay(tempo/10);              
  }
}
