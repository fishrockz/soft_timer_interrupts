IntervalTimer myTimer;

#define NVIC_STIR (*(volatile uint32_t *)0xE000EF00)
#define NVIC_TRIGGER_INTERRUPT(x) NVIC_STIR=(x);

const int led = LED_BUILTIN;  // the pin with a LED
int ledState = LOW;
void blinkLED(void)
{
  if (ledState == LOW) {
    ledState = HIGH;
    //blinkCount = blinkCount + 1;  // increase when LED turns on
  } else {
    ledState = LOW;
  }
  digitalWrite(led, ledState);
}


void softISR() {
        delay(1000); // if we are at a high priorty then we block the blinking for this time, if it is lower then nothing seems to happen, as the blinks intureut this function
}

int interruptID=IRQ_SOFTWARE;
void setup(void)
{
  pinMode(led, OUTPUT);
  myTimer.begin(blinkLED,150000);
 
  myTimer.priority(128);
  
  
   _VectorsRam[interruptID+16] = softISR;    
   NVIC_ENABLE_IRQ(interruptID); 
   //NVIC_SET_PRIORITY(interrupt, 150); //nothing seems to happen  
   NVIC_SET_PRIORITY(interruptID, 100); //there will be a pause in the flashing.
}


// The main program will print the blink count
// to the Arduino Serial Monitor
void loop(void)
{
  
  
  
  delay(3000);
  NVIC_TRIGGER_INTERRUPT(interruptID);
  
  while(1){;}
  
  
  
  
}






