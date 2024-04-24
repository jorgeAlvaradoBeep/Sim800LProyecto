#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 9);
int ledPin = 13;
volatile bool flag = false;  // Variable utilizada para comunicar entre ISR y el loop principal
int sensorPin=2;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin,LOW);
  pinMode(sensorPin, INPUT);  // Configura el pin 2 como entrada con resistencia de pull-up
  attachInterrupt(0, myISR, FALLING); // Configura la interrupción
  interrupts(); 
  

  Serial.println("Iniciando..."); 
  delay(1000);

  mySerial.println("AT");
  updateSerial();
  digitalWrite(ledPin,HIGH);

}

void loop() {
  if (flag) {
    // Haz algo cuando la interrupción ha ocurrido
    Serial.println("Interrupción detectada!");
    //Mandamos Mensaje
    pulseReceive();
    flag = false;  // Restablece la bandera
  }
}
void pulseReceive()
{
  mySerial.println("AT+CMGF=1"); 
  updateSerial();
  mySerial.println("AT+CMGS=\"+523322893377\""); // enter your phone number here (prefix country code)
  updateSerial();
  mySerial.print("Nivel De tinaco bajo"); // enter your message here
  updateSerial();
  mySerial.write(26);
  updateSerial();
}
void myISR() {
  flag = true;  // Establece la bandera cuando la interrupción es activada
}
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
