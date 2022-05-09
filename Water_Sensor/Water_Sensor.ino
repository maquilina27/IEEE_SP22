//can be changed to match user specification
#define maxLiters 0.5


int lightPin = 3;
int sensorPin = 2;
volatile int sensorCount;

unsigned long currentTime;
double totalLiters;

void setup() {
  // put your setup code here, to run once:
  //initialize baud
  Serial.begin(9600);
  //initialize pins
  //sensor pin should be an input
  pinMode(sensorPin, INPUT);
  //notifier pin should be an output
  pinMode(lightPin, OUTPUT);
  //notifier pin should start low
  digitalWrite(lightPin, LOW);
  //attach interrupt to sensor so we can constantly read its output
  attachInterrupt(digitalPinToInterrupt(sensorPin), count, RISING);

}

void count(){
  sensorCount++;
}

void loop() {
  // put your main code here, to run repeatedly:
  //currentTime = millis();
  //the sensor outputs 450 ticks (full wheel rotations)
  //for every liter, which means that the number of liters
  //that pass through the sensor is #ticks/450
  totalLiters = sensorCount/(double)450;
  //debug serial outputs
  Serial.println("Total Liters: " + String(totalLiters));
  Serial.println("Sensor Count: " + String(sensorCount));
  //notify user if limit is exceeded
  if (totalLiters > maxLiters) {
      digitalWrite(lightPin, HIGH);  
  }
  delay(1000);
}
