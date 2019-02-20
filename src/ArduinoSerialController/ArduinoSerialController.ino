#include "Arduino.h"
#include <duinocom.h>

bool isDebugMode = false;

#define PIN_MODE_COMMAND_OUTPUT 0
#define PIN_MODE_COMMAND_INPUT 1
#define PIN_MODE_COMMAND_INPUT_PULLUP 2
//#define PIN_MODE_COMMAND_INPUT_PULLDOWN 3


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

    processMsg(msg);
  }

  delay(1);
}

void processMsg(char* msg)
{
  if (isDebugMode)
  {
    Serial.print("Processing message: ");
    Serial.println(msg);
  }

  char letter = msg[0];

  if (letter != '\0')
  {
    if (letter == byte('M'))
    {
      int pinNumber = getPinNumber(msg);

      Serial.println("Pin number:");
      Serial.println(pinNumber);
      
      int value = getValue(msg);

      Serial.println("Value:");
      Serial.println(value);
      
      if (value == PIN_MODE_COMMAND_OUTPUT)
      {
        Serial.print("Setting pin ");
        Serial.print(pinNumber);
        Serial.println(" mode to OUTPUT.");
        pinMode(pinNumber, OUTPUT);
      }
      else if (value == PIN_MODE_COMMAND_INPUT)
      {
        Serial.print("Setting pin ");
        Serial.print(pinNumber);
        Serial.println(" mode to INPUT.");
        pinMode(pinNumber, INPUT);
      }
      else if (value == PIN_MODE_COMMAND_INPUT_PULLUP)
      {
        Serial.print("Setting pin ");
        Serial.print(pinNumber);
        Serial.println(" mode to INPUT_PULLUP.");
        pinMode(pinNumber, INPUT_PULLUP);
      }
      /*else if (value == PIN_MODE_COMMAND_INPUT_PULLDOWN)
      {
        Serial.print("Setting pin ");
        Serial.print(pinNumber);
        Serial.println(" mode to INPUT_PULLDOWN.");
        pinMode(pinNumber, INPUT_PULLDOWN);
      }*/
    }
    else if (letter == byte('D'))
    {
      int pinNumber = getPinNumber(msg);

      if (isReadCmd(msg))
      {
        if (isDebugMode)
          Serial.println("Is read command");
          
        pinMode(pinNumber, INPUT);
        digitalWrite(pinNumber, LOW);

        Serial.println(digitalRead(pinNumber));
      }
      else
      {

        if (isDebugMode)
          Serial.println("Is write command");

        int value = getValue(msg);

        if (isDebugMode)
        {
          Serial.print("Pin number: ");
          Serial.println(pinNumber);
          Serial.print("Value: ");
          Serial.println(value);
        }

        pinMode(pinNumber, OUTPUT);
        digitalWrite(pinNumber, value);
      }
    }
    else if (letter == byte('A'))
    {
      int pinNumber = getPinNumber(msg);

      if (isReadCmd(msg))
      {
        if (isDebugMode)
          Serial.println("Is read command");

        Serial.println(analogRead(pinNumber));
      }
      else
      {
        int value = getValue(msg);

        if (isDebugMode)
        {
          Serial.print("Pin number: ");
          Serial.println(pinNumber);
          Serial.print("Value: ");
          Serial.println(value);
        }

        pinMode(pinNumber, OUTPUT);
        analogWrite(pinNumber, value);
      }
    }
    else
    {
      if (isDebugMode)
      {
        Serial.println("Invalid command");
      }
    }
  }

  if (isDebugMode)
  {
    Serial.println("Finished processing message ");
    Serial.println("");
  }
}

void turn(bool value, char msg[10])
{
  int outputPin = getPinNumber(msg);

  if (isDebugMode)
  {
    Serial.print("Setting pin ");
    Serial.print(outputPin);
    Serial.print(" to ");
    Serial.println(value);
  }

  pinMode(outputPin, OUTPUT);

  digitalWrite(outputPin, value);
}

int getPinNumber(char* msg)
{
  if (isDebugMode)
  {
    Serial.println("Getting pin number");
  }

  int colonPosition = getColonPosition(msg);
  
  int numberLength = 0;
  
  if (colonPosition > 0)
    numberLength = colonPosition -1;
  else
    numberLength = strlen(msg);

  int outputPin = readInt(msg, 1, numberLength);

  if (isDebugMode)
  {
    Serial.print("  Output pin:");
    Serial.println(outputPin);

    Serial.println("Finished Getting pin number");
    Serial.println("");
  }

  return outputPin; 
}

bool isReadCmd(char* msg)
{

  if (isDebugMode)
    Serial.println("Getting value");

  int colonPosition = getColonPosition(msg);

  if (isDebugMode)
  {
    Serial.print("  Colon position: ");
    Serial.println(colonPosition);
  }

  int valueLength = strlen(msg)-colonPosition-1;

  if (isDebugMode)
  {
    Serial.print("  Value length: ");
    Serial.println(valueLength);
  }

  int valueStartPosition = colonPosition+1;

  if (isDebugMode)
  {
    Serial.print("  Value start position: ");
    Serial.println(valueStartPosition);
  }

  char value = msg[valueStartPosition];
  
  if (isDebugMode)
  {
    Serial.print("  Value: ");
    Serial.println(value);

    Serial.println("Finished getting value");
    Serial.println("");
  }

  return value == byte('R');
}

int getValue(char* msg)
{

  if (isDebugMode)
  {
    Serial.println("Getting value");
  }

  int colonPosition = getColonPosition(msg);

  if (isDebugMode)
  {
    Serial.print("  Colon position: ");
    Serial.println(colonPosition);
  }

  int valueLength = strlen(msg)-colonPosition-1;

  if (isDebugMode)
  {
    Serial.print("  Value length: ");
    Serial.println(valueLength);
  }

  int valueStartPosition = colonPosition+1;

  if (isDebugMode)
  {
    Serial.print("  Value start position: ");
    Serial.println(valueStartPosition);
  }

  int value = readInt(msg, valueStartPosition, valueLength);
  
  if (isDebugMode)
  {
    Serial.print("  Value: ");
    Serial.println(value);

    Serial.println("Finished getting value");
    Serial.println("");
  }

  return value;
}

int getColonPosition(char* msg)
{

  if (isDebugMode)
  {
    Serial.print("Getting colon position from: ");
    Serial.println(msg);
  }

  int colonPosition = 0;

  unsigned int numElements = strlen(msg);
  unsigned int i;
  for(i = 0; i < numElements; ++i) {
      if (msg[i] == ':') {
          colonPosition = i;
          break;
      }
  }

  return colonPosition;
}
