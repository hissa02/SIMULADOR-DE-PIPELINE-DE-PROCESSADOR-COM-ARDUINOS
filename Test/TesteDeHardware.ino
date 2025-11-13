// C++ code
//
int ledf11 = 0;
int ledf12 = 1;
int ledf13 = 2;
int ledf14 = 3;

int ledf21 = 4;
int ledf22 = 5;
int ledf23 = 6;
int ledf24 = 7;

int ledf31 = 8;
int ledf32 = 9;
int ledf33 = 10;
int ledf34 = 11;

int ledf41 = 12;
int ledf42 = 13;
int ledf43 = 19; //A5
int ledf44 = 18; //A4

int ledR = 17; //A3
int ledB = 16; //A2
int ledG = 15; //A1

void setup()
{
  pinMode(ledf11, OUTPUT);
  pinMode(ledf12, OUTPUT);
  pinMode(ledf13, OUTPUT);
  pinMode(ledf14, OUTPUT);
  
  pinMode(ledf21, OUTPUT);
  pinMode(ledf22, OUTPUT);
  pinMode(ledf23, OUTPUT);
  pinMode(ledf24, OUTPUT);
  
  pinMode(ledf31, OUTPUT);
  pinMode(ledf32, OUTPUT);
  pinMode(ledf33, OUTPUT);
  pinMode(ledf34, OUTPUT);
  
  pinMode(ledf41, OUTPUT);
  pinMode(ledf42, OUTPUT);
  pinMode(ledf43, OUTPUT);
  pinMode(ledf44, OUTPUT);
  
  pinMode(ledR, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledB, OUTPUT); 
}

void loop()
{
  //teste de funcionamento de hardware	
  //fileiras de leds
  digitalWrite(ledf11, HIGH);
  digitalWrite(ledf21, HIGH);
  digitalWrite(ledf31, HIGH);
  digitalWrite(ledf41, HIGH);
  delay(500);
  digitalWrite(ledf11, LOW);
  digitalWrite(ledf21, LOW);
  digitalWrite(ledf31, LOW);
  digitalWrite(ledf41, LOW);
  delay(500);
  
  digitalWrite(ledf12, HIGH);
  digitalWrite(ledf22, HIGH);
  digitalWrite(ledf32, HIGH);
  digitalWrite(ledf42, HIGH);
  delay(500);
  digitalWrite(ledf12, LOW);
  digitalWrite(ledf22, LOW);
  digitalWrite(ledf32, LOW);
  digitalWrite(ledf42, LOW);
  delay(500);
  
  digitalWrite(ledf13, HIGH);
  digitalWrite(ledf23, HIGH);
  digitalWrite(ledf33, HIGH);
  digitalWrite(ledf43, HIGH);
  delay(500);
  digitalWrite(ledf13, LOW);
  digitalWrite(ledf23, LOW);
  digitalWrite(ledf33, LOW);
  digitalWrite(ledf43, LOW);
  delay(500);
  
  digitalWrite(ledf14, HIGH);
  digitalWrite(ledf24, HIGH);
  digitalWrite(ledf34, HIGH);
  digitalWrite(ledf44, HIGH);
  delay(500);
  digitalWrite(ledf14, LOW);
  digitalWrite(ledf24, LOW);
  digitalWrite(ledf34, LOW);
  digitalWrite(ledf44, LOW);
  delay(500);
  
  //leds rgb de estado
  digitalWrite(ledR, HIGH);
  delay(500);
  digitalWrite(ledR, LOW);
  delay(500);
  
  digitalWrite(ledB, HIGH);
  delay(500);
  digitalWrite(ledB, LOW);
  delay(500);  
}