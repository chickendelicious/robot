/*
  I2C Pinouts
  SDA -> A4
  SCL -> A5
*/

//Import the library required
#include <Wire.h>
#include <Servo.h>

//Slave Address for the Communication
#define SLAVE_ADDRESS 0x04

Servo servo1;  // create servo object to control a servo
Servo servo2;
const int SERVO_COUNT = 2;
Servo servos[SERVO_COUNT] = {
  servo1,
  servo2
};

char number[50];
int state = 0;
int lag = 250;
int maxx = 127;

//Code Initialization
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  servo1.attach(9);  // attaches the servo on pin 9 to the servo object
  servo2.attach(10);
  // initialize i2c as slave
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  //  Wire.onRequest(sendData);
  for(int i = 0; i < SERVO_COUNT; i++){
    servos[i].write(0);
  }
}

void loop() {
  delay(100);
} // end loop

//blinks the on board LED
void blink(int times){
  Serial.print("Blinking x" + String(times) + "\n");
  while(times > 0){
    Serial.print(String(times)+"\n");
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    times --;
    if(times > 0){
      delay(500);
    }   
  }

}

//move a servo motor
void move(Servo servo, int dest){  
  int pos = servo.read();
  Serial.print("Moving: " + String(pos) + "->" + String(dest) + "\n");
  if(dest > pos){
    for(int i = pos; i < dest; i++){
      servo.write(i);
      delay(lag);
    }
  }
  else if(pos > dest){
    for(int i = pos; i > dest; i--){
      servo.write(i);
      delay(lag);
    }
  }
}

// callback for received data
void receiveData(int byteCount) {
  int i = 0;
  while (Wire.available()) {
    number[i] = Wire.read();
    //Serial.print(number[i] + "\n");
    i++;
  }
  number[i] = '\0';
  parse_msg(number);
}  // end while

// callback for sending data
void sendData() {
  Wire.write(number);
}


void parse_msg(char msg[]){
  switch (msg[1]) {
    case 0: // blink command
      blink(msg[2]);
      break;
    case 1: // move command
      for(int i = 0; i < SERVO_COUNT; i++){
        move(servos[i], msg[i+2]);
      }
      break;
    default:
      break;
  }
}



//End of the program
