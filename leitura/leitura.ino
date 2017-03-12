#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f,16,2);

byte delta[8] =
{
  B00000,
  B00000,
  B00100,
  B01010,
  B10001,
  B11111,
  B00000,
  B00000
};

byte micro[8] =
{
  B00000,
  B10001,
  B10001,
  B10011,
  B11101,
  B10000,
  B10000,
  B00000
//B00000, B00000, B10001, B10001, B10001, B10011, B01101, B00000 u
};

const int trigPin = 12;
const int echoPin = 13;
unsigned long intervalo_tempo;
const int tempPin = 0;
float temp;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, delta);
  lcd.createChar(1, micro);

  Serial.begin(9600);
}

void loop() {
  delay(1000);
  // leitura do sensor HC-SR04 (intervalo tempo)
  // mandar sinal
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // ler intervalo de tempo
  intervalo_tempo = pulseIn(echoPin, HIGH); //microsegundos

  // sensor LM35 (temperatura)
  temp = analogRead(tempPin) * (5.0/1024) * 100;

  // escrever no lcd
  lcd.clear();

  // intervalo de tempo (som)
  lcd.setCursor(0,0);
  lcd.write(0); //delta <-- simbolo
  lcd.print("t: ");
  lcd.print(intervalo_tempo);
  lcd.setCursor(10, 0);
  lcd.write(1); //micro <-- simbolo
  lcd.print("s");

  // temperatura
  lcd.setCursor(1, 1);
  lcd.print("T: ");
  lcd.print(temp);
  lcd.setCursor(10, 1);
  lcd.write(223); //º <-- simbolo
  lcd.print("C");

  //escrever no serial
  Serial.print("\n\nDelta t:\tTemp:\n");
  Serial.print(intervalo_tempo);
  Serial.print("\t");
  Serial.print(temp);
}
