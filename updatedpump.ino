//new copy of pump code
int bPin1 = 4;
int bPin2 = 5;  //second bPin for amount of times to water in the day
int lPin1 = 9;
int lPin2 = 8;
int lPin3 = 7;
int relayPin = 6;

int timerModes = 3; //different timers: 1min, 2min, 5min

void setup() {
  // put your setup code here, to run once:
  // put your main code here, to run repeatedly:
  initializationSwitch(bPin1); //initializing button
  initializationSwitch(bPin2); 
  initializationLed(lPin1);
  initializationLed(lPin2);
  initializationLed(lPin3);
  initializationLed(relayPin);
  Serial.begin(2400);
}

void initializationSwitch(int pin) {
  pinMode(pin, INPUT_PULLUP);
}

void initializationLed(int pin) {
  pinMode(pin, OUTPUT);
}


//reads a button and returns its state 

unsigned long currentMillis = 0;
unsigned long lastDebounceTime1 = 0;
int buttonState1 = 1;
int intervalSwitch=0;

int buttonRead(int pin) {
  unsigned long debounceDelay1 = 500;
  //loop
  if (digitalRead(pin) == LOW) {
    if (currentMillis - lastDebounceTime1 > debounceDelay1) {
      lastDebounceTime1 = currentMillis;
      buttonState1++;
      intervalSwitch=1;
    }
  }
  else{
    intervalSwitch=0;
  }

  if (buttonState1 > 3) {
    buttonState1 = 1;
  }
  return buttonState1;
}

double currentInterval = 1;
unsigned long timerSwitch(int buttonState1) {

  
  switch (buttonState1)
  {
    case 1:
      currentInterval = 5;
      digitalWrite(lPin1, HIGH);
      digitalWrite(lPin2, LOW);
      digitalWrite(lPin3, LOW);
      break;
    case 2:
      currentInterval = 2;
      digitalWrite(lPin1, LOW);
      digitalWrite(lPin2, HIGH);
      digitalWrite(lPin3, LOW);
      break;
    case 3:
      currentInterval = 1;
      digitalWrite(lPin1, LOW);
      digitalWrite(lPin2, LOW);
      digitalWrite(lPin3, HIGH);
      break;
  }
  return currentInterval;
}



unsigned long cm =0;
unsigned long pm =0;
unsigned long count=0;

void timer(int currentInterval) {
  double interval = currentInterval * 60000;  //converting interval to ms
  double maxCount = 24*60/currentInterval;
  if (cm - pm >= interval)
  {
    pm = cm;
    count++;
  }
  if(count==maxCount){
    count=0;
  }
  Serial.println(maxCount);
  Serial.println(interval);
}



 int pumpState=0;
 
 void pumpStateChange(){
  if(count == 1){
  pumpState=1;
    
  }
  else{
    pumpState=0;
  }
  
 }


 void relay(){
  if(pumpState==1){
    digitalWrite(relayPin, HIGH);
  }
  else{
    digitalWrite(relayPin, LOW);
  }
  
 }


void resetTimer() {
 if(intervalSwitch==1){
  count=0;
  pumpState=0;  
 }
 }

void loop() {

  //starting counters
  currentMillis = millis();
  cm = millis();

  int bState1 = buttonRead(bPin1);
   Serial.println(bState1);
   
  int currentInterval = timerSwitch(bState1);
  Serial.println(currentInterval);
  Serial.println(count);
  timer(currentInterval);
  //resetTimer();
  //pumpStateChange();
  //relay();
//Serial.println(count);


}
