int sensorPin = 2;
volatile int sensorCount;

unsigned long currentTime;
double totalLiters;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(sensorPin), count, RISING);

}

void count(){
  sensorCount++;
}

void loop() {
  // put your main code here, to run repeatedly:
  currentTime = millis();
  totalLiters = sensorCount/(double)450;
  Serial.println("Total Liters: " + String(totalLiters));
  Serial.println("Sensor Count: " + String(sensorCount));
  delay(1000);
}
