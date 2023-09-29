//Pines
#define VERDE PB7
#define AMARILLO PB8
#define ROJO PB9
#define BTN PA1
#define BTN_ALARMA PA2
#define BUZZER PA0

//Estados
#define DEFAULT_GREEN 0
#define YELLOW 1
#define YELLOW_RED 2
#define RED 3
#define EMERGENCY 4

//Tiempos
#define WAIT_SEQUENCE 2 * 1000000
#define WAIT_CROSSING 5 * 1000000 

#define MODE RISING

//Variables globales
int state = DEFAULT_GREEN;
bool alarm = false;

void setup()
{ 
  Serial.begin(115200);
  pinMode(ROJO, OUTPUT);
  pinMode(AMARILLO, OUTPUT);
  pinMode(VERDE, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  pinMode(BTN_ALARMA, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  attachInterrupt(BTN, buttonInterrupt, MODE);
  attachInterrupt(BTN_ALARMA, alarmInterrupt, MODE);


  Timer1.pause();
  Timer1.setPeriod(WAIT_SEQUENCE); 
  Timer1.setMode(TIMER_CH1,TIMER_OUTPUT_COMPARE);
  Timer1.setCompare(TIMER_CH1, -1);
  Timer1.attachInterrupt(TIMER_CH1, interruptTimer);
  Timer1.refresh();
  Timer1.resume();
}

void loop()
{

  switch (state){
    case DEFAULT_GREEN:
      digitalWrite(ROJO, LOW);
      digitalWrite(AMARILLO, LOW);
      digitalWrite(VERDE, HIGH);
      break;
    
    case YELLOW:
      digitalWrite(ROJO, LOW);
      digitalWrite(AMARILLO, HIGH);
      digitalWrite(VERDE, LOW);
      Timer1.pause();
      Timer1.refresh();
      Timer1.resume();
      break;
      
    case YELLOW_RED:
      digitalWrite(ROJO, HIGH);
      digitalWrite(AMARILLO, HIGH);
      digitalWrite(VERDE, LOW);
      Timer1.pause();
      Timer1.refresh();
      Timer1.resume();
      break;

    case RED:
      digitalWrite(ROJO, HIGH);
      digitalWrite(AMARILLO, LOW);
      digitalWrite(VERDE, LOW);
      Timer1.pause();
      Timer1.setPeriod(WAIT_CROSSING);
      Timer1.refresh();
      Timer1.resume();
      break;
    
    case EMERGENCY:
      digitalWrite(ROJO, HIGH);
      digitalWrite(AMARILLO, LOW);
      digitalWrite(VERDE, LOW);
      break;
  }

  switch (alarm) {
    case true:
      Serial.print("There's an emergency, alarm ON");
      digitalWrite(BUZZER, HIGH);
      estado = EMERGENCY;
      break;
    
    case false:
      estado = VERDE;
  }
}

void interruptTimer(){
  switch (state) {
    case DEFAULT_GREEN:
      state = YELLOW;
      Timer1.pause();
      Timer1.refresh();
      Timer1.resume();
      break;
    case YELLOW:
      
  }
}

void defaultState(){
  digitalWrite(ROJO, LOW);
  digitalWrite(AMARILLO, LOW);
  digitalWrite(VERDE, HIGH);
}

void buttonInterrupt(){

}

void alarmInterrupt(){

}