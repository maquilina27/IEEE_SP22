#include <SoftwareSerial.h> 

#define maxLiters 0.5

SoftwareSerial MyBlue(6, 5); // RX | TX 
char flag = '0'; 

int lightPin = 3;
int sensorPin = 2;
volatile int sensorCount;

unsigned long currentTime;
double totalLiters;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  MyBlue.begin(9600); 
  pinMode(sensorPin, INPUT);
  pinMode(lightPin, OUTPUT);
  digitalWrite(lightPin, LOW);
  attachInterrupt(digitalPinToInterrupt(sensorPin), count, RISING);
  Serial.println("Ready to connect\n"); 
}

void count(){
  sensorCount++;
}

void loop() {
  // put your main code here, to run repeatedly:
  currentTime = millis();
  totalLiters = sensorCount/(double)450;
  MyBlue.println("Total Liters: " + String(totalLiters));
  MyBlue.println("Sensor Count: " + String(sensorCount));
  if (totalLiters > maxLiters) {
      //digitalWrite(lightPin, HIGH);
      MyBlue.println("Threshold reached\n");
  }
  //Bluetooth
  if (MyBlue.available()) 
   flag = MyBlue.read(); 
  if (flag == '1') { 
   MyBlue.println("Reset");
   sensorCount = 0;
   totalLiters = 0;
   flag = '0';
 }  
  
  delay(1000);
}
