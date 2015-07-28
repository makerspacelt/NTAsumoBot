int ir_sensor = 3;
int led = 13;

void setup() {
  pinMode(ir_sensor, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(ir_sensor);
  digitalWrite(led, buttonState);
}
