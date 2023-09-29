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

#define ON HIGH
#define OFF OFF
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


  //configuro el Timer1
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
    case DEFAULT_GREEN: //enciende luz verde
      digitalWrite(ROJO, OFF);
      digitalWrite(AMARILLO, OFF);
      digitalWrite(VERDE, ON);
      digitalWrite(BUZZER, OFF);
      break;
    
    case YELLOW: //enciende luz amarilla
      digitalWrite(ROJO, OFF);
      digitalWrite(AMARILLO, ON);
      digitalWrite(VERDE, OFF);
      digitalWrite(BUZZER, OFF);
      break;
      
    case YELLOW_RED: //enciende luz amarilla y luz roja
      digitalWrite(ROJO, ON);
      digitalWrite(AMARILLO, ON);
      digitalWrite(VERDE, OFF);
      digitalWrite(BUZZER, OFF);
      break;

    case RED: //enciende luz roja
      digitalWrite(ROJO, ON);
      digitalWrite(AMARILLO, OFF);
      digitalWrite(VERDE, OFF);
      digitalWrite(BUZZER, OFF);
      break;
    
    case EMERGENCY: //estado de emergencia
      digitalWrite(ROJO, ON);
      digitalWrite(AMARILLO, OFF);
      digitalWrite(VERDE, OFF);
      digitalWrite(BUZZER, ON);
      break;
  }

  if (alarm){
    Serial.print("There's an emergency, alarm ON");
    digitalWrite(BUZZER, ON);
    state = EMERGENCY;
    Timer1.Pause();
  }
  else {
    state = VERDE;
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
      state = RED;
      Timer1.pause();
      Timer1.setPeriod(WAIT_CROSSING);
      Timer1.refresh();
      Timer1.resume();
      break;
    
    case RED:
      state = YELLOW_RED;
      Timer1.pause();
      Timer1.setPeriod(WAIT_SEQUENCE);
      Timer1.refresh();
      Timer1.resume();
      break;

    case YELLOW_RED:
      state = DEFAULT_GREEN;
      
  }
}

void defaultState(){
  digitalWrite(ROJO, OFF);
  digitalWrite(AMARILLO, OFF);
  digitalWrite(VERDE, ON);
}

void buttonInterrupt(){

}

void alarmInterrupt(){

}