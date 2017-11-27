#include "Arduino.h"
#include <duinocom.h>

 
void setup() {
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void loop() {
  if (checkMsgReady())
  {
    char* msg = getMsg();

    
    for (int i = 0; i < 3; i++)
    {
        Serial.print(msg[i]);
    }
    Serial.println();

    processMsg(msg);
  }

  delay(1);
}

void processMsg(char* msg)
{
  Serial.print("Processing message: ");
  Serial.println(msg);

  char letter = msg[0];

  if (letter != '\0')
  {
    if (letter == byte('D'))
    {
      int pinNumber = getPinNumber(msg);
      int value = getValue(msg);
      Serial.print("Pin number: ");
      Serial.println(pinNumber);
      Serial.print("Value: ");
      Serial.println(value);

      pinMode(pinNumber, OUTPUT);
      digitalWrite(pinNumber, value);
    }
    else if (letter == byte('A'))
    {
      int pinNumber = getPinNumber(msg);
      int value = getValue(msg);
      Serial.print("Pin number: ");
      Serial.println(pinNumber);
      Serial.print("Value: ");
      Serial.println(value);

      pinMode(pinNumber, OUTPUT);
      analogWrite(pinNumber, value);
    }
/*    else if (letter == 'L')
    {
      Serial.println("LOW");
      turn(LOW, msg);
    }*/ 
    else
    {
      Serial.println("Invalid command");
    }
  }

  Serial.println("Finished processing message ");
  Serial.println("");
}

void turn(bool value, char msg[10])
{
  //int outputPin = readInt(msg, 1, 2);
  int outputPin = getPinNumber(msg);

  Serial.print("Setting pin ");
  Serial.print(outputPin);
  Serial.print(" to ");
  Serial.println(value);

  pinMode(outputPin, OUTPUT);

  //Serial.println(outputPin);
  digitalWrite(outputPin, value);
  /*if (value == 0 || value == 1)
    digitalWrite(outputPin, value);
  else if (value >= 1 || value <= 255)
    digitalWrite(outputPin, value);*/
}

int getPinNumber(char* msg)
{
  Serial.println("Getting pin number");

  int colonPosition = getColonPosition(msg);

  int numberLength = colonPosition -1;

  int outputPin = readInt(msg, 1, numberLength);

  Serial.print("  Output pin:");
  Serial.println(outputPin);

  Serial.println("Finished Getting pin number");
  Serial.println("");

  return outputPin; 
}

int getValue(char* msg)
{

  Serial.println("Getting value");

  int colonPosition = getColonPosition(msg);

  Serial.print("  Colon position: ");
  Serial.println(colonPosition);

  int valueLength = strlen(msg)-colonPosition-1;

  Serial.print("  Value length: ");
  Serial.println(valueLength);

  int valueStartPosition = colonPosition+1;

  Serial.print("  Value start position: ");
  Serial.println(valueStartPosition);

  int value = readInt(msg, valueStartPosition, valueLength);
  
  Serial.print("  Value: ");
  Serial.println(value);

  Serial.println("Finished getting value");
  Serial.println("");
/*
  for (int i = 0; i < 

  int outputPin = readInt(msg, 1, 2);

  Serial.print("Output pin:");
  Serial.println(outputPin);

  return outputPin; */
return value;
}

int getColonPosition(char* msg)
{

  Serial.print("Getting colon position from: ");
  Serial.println(msg);

  int colonPosition = 0;

  unsigned int numElements = strlen(msg);//sizeof(msg)/sizeof(char0]);
  unsigned int i;
  for(i = 0; i < numElements; ++i) {
  //    Serial.print("Checking character ");
  //    Serial.println(msg[i]);
      if (msg[i] == ':') {
          colonPosition = i;
//          Serial.println("Found at %u\n", i);
          break;
      }
  }

  return colonPosition;
}

/*int readSerialNumber()
{ 
  if (Serial.available() > 0) {   // something came across serial
    integerValue = 0;         // throw away previous integerValue
    while(1) {            // force into a loop until 'n' is received
      incomingByte = Serial.read();
      if (incomingByte == '\n') break;   // exit the while(1), we're done receiving
      if (incomingByte == -1) continue;  // if no characters are in the buffer read() returns -1
      integerValue *= 10;  // shift left 1 decimal place
      // convert ASCII to integer, add, and shift left 1 decimal place
      integerValue = ((incomingByte - 48) + integerValue);
    }
    Serial.println(integerValue);   // Do something with the value
    setPwmValue(integerValue);
  }
}

void setPwmValue(int value)
{
  if (value < 0)
    Serial.println("Value too low");
  else if (value > 255)
    Serial.println("Value too high");
  else
  {
    Serial.print("Setting to: ");
    Serial.println(value);
    analogWrite(outputPin, value);
  }
}*/
