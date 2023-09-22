
#define VERDE PB7
#define AMARILLO PB8
#define ROJO PB9
#define BTN PA1
#define BTN_ALARMA PA2

bool isPressed_BTN = false;
bool isPressed_ALARMA = false;
int mode = 0;

#define DEFAULT 0
#define STOP 1
#define ALARM 2

void setup()
{  
  pinMode(ROJO, OUTPUT);
  pinMode(AMARILLO, OUTPUT);
  pinMode(VERDE, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  pinMode(BTN_ALARMA, INPUT_PULLUP);

  Timer1.pause();
  Timer1.setPeriod(200000); 
  Timer1.setMode(TIMER_CH1,TIMER_OUTPUT_COMPARE);
  Timer1.setCompare(TIMER_CH1, 1);
  Timer1.attachInterrupt(TIMER_CH1, interruptTimer);
  Timer1.refresh();
  Timer1.resume();
}

void loop()
{
  
}

void interruptTimer(){

}

void defaultState(){
  digitalWrite(ROJO, LOW);
  digitalWrite(AMARILLO, LOW);
  digitalWrite(VERDE, HIGH);
}