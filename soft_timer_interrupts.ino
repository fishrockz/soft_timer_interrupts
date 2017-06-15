#include <PulseEvent.h>

PulseEventOutput myOut;
PulseEventInput myIn;
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


int count=0;
void EventFunction(){

  int i, num;

  // Every time new data arrives, simply print it
  // to the Arduino Serial Monitor.
  num = myIn.available();
  if (num > 0) {
    count = count + 1;
    Serial.print("EventFunction: ");
    Serial.print(count);
    Serial.print(" :  ");
    for (i=1; i <= num; i++) {
      float val = myIn.read(i);
      Serial.print(val);
      Serial.print("  ");
    }
    Serial.println();
  }else{
  Serial.println("num==0");
  }


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
   
   
     myOut.begin(9);  // connect pins 9 and 10 together...
  myIn.begin(10,EventFunction);
  myOut.write(1, 600.03);
  myOut.write(2, 1500);
  myOut.write(3, 759.24);
  // slots 4 and 5 will default to 1500 us
  myOut.write(6, 1234.56);
   
}


// The main program will print the blink count
// to the Arduino Serial Monitor
void loop(void)
{
  
  
  
  delay(3000);
  NVIC_TRIGGER_INTERRUPT(interruptID);
  
  while(1){;}
  
  
  
  
}






