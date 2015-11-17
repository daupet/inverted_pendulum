const int LED_pin = 13;
const int motin1 = 8;
const int motin2 = 9;

int i = 0;

void setup() {
  pinMode(motin1, OUTPUT);
  pinMode(motin2, OUTPUT);
  pinMode(LED_pin, OUTPUT);
}

void loop() {
  analogWrite(10, 1000);
  digitalWrite(motin1, HIGH);
  digitalWrite(motin2, LOW);
  digitalWrite(LED_pin, HIGH);
  delay(2000);

  analogWrite(10, 20);
  digitalWrite(motin1, HIGH);
  digitalWrite(motin2, LOW);
  digitalWrite(LED_pin, HIGH);
  delay(2000);

/**
  analogWrite(1, 300);
  digitalWrite(motin1, LOW);
  digitalWrite(motin2, HIGH);
  digitalWrite(LED_pin, LOW);
  delay(2000);

  analogWrite(1, 400);
  digitalWrite(motin1, LOW);
  digitalWrite(motin2, HIGH);
  digitalWrite(LED_pin, LOW);
  delay(2000);
  */
}

