//Grabando Sensor PIR
/*
int PIRpin = 3;
int RELpin = 2;
 
void setup()
{
  Serial.begin(9600);
  pinMode(PIRpin, INPUT);
  pinMode(RELpin, OUTPUT);
}
 
void loop()
{ 
  int value= digitalRead(PIRpin);
  delay(500);
  Serial.println(value);

  if (value == HIGH)
  {
    digitalWrite(RELpin, HIGH);
    delay(10000);
  }else{
    digitalWrite(RELpin, LOW);
  }
/*  if (digitalRead(pirPin) == LOW)
    digitalWrite(relePin, HIGH);
  else
    digitalWrite(relePin, LOW);
 
  delay(100);*/

const int PIRPin= 3;
const int RELPin= 2;
 
int pirState = LOW;           // de inicio no hay movimiento
int val = 0;                  // estado del pin
  
void setup() 
{
  pinMode(RELPin, OUTPUT); 
  pinMode(PIRPin, INPUT);
  Serial.begin(9600);
}
  
void loop()
{
  val = digitalRead(PIRPin);
  if (val == HIGH)   //si está activado
  { 
    digitalWrite(RELPin, HIGH);  //RELAY ON
    delay(9000);
    if (pirState == LOW)  //si previamente estaba apagado
    {
      Serial.println("Sensor activado");
      //Serial.println("Relay LUZ Encendido");
      pirState = HIGH;
    }
  } 
  else   //si esta desactivado
  {
    digitalWrite(RELPin, LOW);  //RELAY ON
    if (pirState == HIGH)  //si previamente estaba encendido
    {
      Serial.println("Sensor parado");
      //Serial.println("Relay LUZ Apagado");
      pirState = LOW;
    }
  }
}
