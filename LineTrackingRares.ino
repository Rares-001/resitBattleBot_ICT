

int mhSensorRight = 39; 
int mhSensorLeft = 34; 

const byte led_gpio = 17;
const byte led_gpio1 = 5;
 
const byte back1 = 16; 
const byte back2 = 18; 


void setup() {
  ledcAttachPin(led_gpio, 0); // assign a led pins to a channel
  ledcAttachPin(led_gpio1, 1); // assign a led pins to a channel
  ledcAttachPin(back1, 2); // assign a led pins to a channel
  ledcAttachPin(back2, 3); // assign a led pins to a channel

  // Initialize channels
  // channels 0-15, resolution 1-16 bits, freq limits depend on resolution
  // ledcSetup(uint8_t channel, uint32_t freq, uint8_t resolution_bits);
  ledcSetup(0, 4000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(1, 4000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(2, 4000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(3, 4000, 8); // 12 kHz PWM, 8-bit resolution


  pinMode (mhSensorLeft, INPUT); // sensor pin INPUT
  pinMode (mhSensorRight, INPUT); // sensor pin INPUT
Serial.begin(9600);
}

  void loop() {
    LineTracking();
  Serial.println(digitalRead(mhSensorRight));
  Serial.println(digitalRead(mhSensorLeft));
  }

 int turnLeft(int speed){
    ledcWrite(0, speed); 
    ledcWrite(1, speed); 
    ledcWrite(2, 0); 
    ledcWrite(3, 0); 
}

int turnRight(int speed){
    ledcWrite(0, 0); 
    ledcWrite(1, 0); 
    ledcWrite(2, speed); 
    ledcWrite(3, speed); 
}

int goBackward(int speed){
    ledcWrite(0, speed); 
    ledcWrite(1, 0); 
    ledcWrite(2, 0); 
    ledcWrite(3, speed); 
}

int goForward(int speed){
    ledcWrite(0, 0); 
    ledcWrite(1, speed); 
    ledcWrite(2, speed); 
    ledcWrite(3, 0); 
}

int stop(){
    ledcWrite(0, 0); 
    ledcWrite(1, 0); 
    ledcWrite(2, 0); 
    ledcWrite(3, 0); 
}

int LineTracking()
{
if (digitalRead(mhSensorLeft) == 0 && digitalRead(mhSensorRight) == 0 ) 
{
    goForward(110);
  }
  else if (digitalRead(mhSensorLeft) == 0 && digitalRead(mhSensorRight) == 1 ) {
    turnLeft(160);
  }
  else if (digitalRead(mhSensorLeft) == 1 && digitalRead(mhSensorRight) == 0 ) {
    turnRight(160);
  }
  else if (digitalRead(mhSensorLeft) == 1 && digitalRead(mhSensorRight) == 1 ) {
    stop();
  }
}


  
