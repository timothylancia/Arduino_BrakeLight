int pinPower = 9; //button to turn on the system
int pinNight = 2; //button to toggle night mode
int pinBrake = 3; //the pin where we connect the button
int LED = 5; //the pin we connect the LED

int brakeBtn = 0;
int powerBtn = 0;
int nightBtn = 0;

int currentPower = 0;      // the current state of the output pin
int currentMode = 0;      // the current state of the output pin

int light = 0;

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 100;   // the debounce time, increase if the output flickers

void setup() {
  pinMode(pinBrake, INPUT); //set the brake button pin as INPUT
  pinMode(pinNight, INPUT); //set the night mode button pin as INPUT
  pinMode(pinPower, INPUT); //set the power button pin as INPUT
  pinMode(LED, OUTPUT); //set the LED pin as OUTPUT

  // Makes the brake button an interupt
  // Meaning that no matter what other thing is going on,
  // The brake will activate when the button is pressed
  attachInterrupt(digitalPinToInterrupt(pinBrake), brakeLight, CHANGE);

  attachInterrupt(digitalPinToInterrupt(pinNight), nightMode, CHANGE);

  Serial.begin(9600);

  Serial.print("Test");
}

void loop() {
  powerBtn = digitalRead(pinPower); //read the state of the button
  nightBtn = digitalRead(pinNight); //read the state of the button

  if (powerBtn == 1){
    if (currentPower == 0){
      currentPower = 1;
      Serial.println("On");
    } 
    else {
      if (currentPower == 1){
      currentPower = 0;
      Serial.println("Off");
      }
    }
    // Allows only one instance of the button being pressed to switch
    // Without it, the button bounces between ON/OFF
    // for as long as you hold the button
    delay(500);
  }

  if (currentPower == 1){
    if (currentMode == 1) {
      if (brakeBtn == 0) {
        nightModeLight();
      }
    }
  }
}

void brakeLight() {
  brakeBtn = digitalRead(pinBrake); //read the state of the button
  
  if (currentPower == 1) {
    if(brakeBtn == 1) { //if is pressed
      light = 1;
      digitalWrite(LED, light); //write 1 or HIGH to led pin
    } else { //if not pressed
      light = 0;
      digitalWrite(LED, light);  //write 0 or LOW to led pin
    }
  }
}

void nightMode() {
  nightBtn = digitalRead(pinNight); //read the state of the button
  
  if (currentPower == 1){
    if (nightBtn == 1){
      if (currentMode == 0){
        currentMode = 1;
        Serial.println("Night Mode On");
      } 
      else {
        if (currentMode == 1){
        currentMode = 0;
        light = 0;
        digitalWrite(LED, light);
        Serial.println("Night Mode Off");
        }
      }
    }
  }
  delayMicroseconds(100);
}

// Alternate between ON/OFF with 800 delay
void nightModeLight() {
  if (light == 1) {
    light = 0;
    digitalWrite(LED, light);  //write 0 or LOW to led pin
  } else {
    light = 1;
    digitalWrite(LED, light); //write 1 or HIGH to led pin
  }
  delay(800);
}
