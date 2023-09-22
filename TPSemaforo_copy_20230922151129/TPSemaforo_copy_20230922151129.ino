//Declaro los Estados y defines útiles 
#define RED PB?
#define YELLOW PB?
#define GREEN PB?
#define PULS PB?


//Declaro las variables globales que voy a usar

void setup()
{  
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(PULS, INPUT);
  
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