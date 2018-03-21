int led = 13;
int reedwitch = 5;
int buzzer = 8;
int val = 0;
int pote = 0;
int boton = 2;
int boton_estado;
boolean alerta = true;

void setup(){
  pinMode(led, OUTPUT);
  pinMode(reedwitch, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(boton,INPUT);
}

void loop(){
  boton_estado = digitalRead(boton);
  if(boton_estado == 0){
    alerta = false;
  }
  pote = analogRead(A0);
    val = digitalRead(reedwitch);
    
  if(alerta){
    if(val == LOW){
      digitalWrite(led, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(pote);
      digitalWrite(led, LOW);
      digitalWrite(buzzer, LOW);
      delay(pote);
        
  }else{
      digitalWrite(led, LOW);
      digitalWrite(buzzer, LOW);
      
    }
  }else{
    if(val == HIGH){
      alerta = true;
    }
  }
  

  
}
