#include <Arduino.h>
#include <ArduinoRest.h>
#include <stdio.h>

ArduinoRest rest(Serial);

void setup(){
  Serial.begin(115200);
    
  rest.AddHandler("echoping", &EchoFunc);
}

void EchoFunc(Command& cmd) {
  Serial.print("EchoFunc");
  const char* str = "";
  char buffer[100];
  cmd.GetStringParam("string", &str);
  sprintf(buffer, "{ \"echo\": \"%s\" }\n", str);
  
  Serial.print(buffer);
}


void loop(void) {
  rest.Proceed();
}

