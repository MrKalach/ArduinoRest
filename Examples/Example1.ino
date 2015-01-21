#include <Arduino.h>
#include <ArduinoRest.h>

ArduinoRest rest(Serial);

void setup(){
  Serial.begin(115200);
    
  rest.AddHandler("ping", &PingFunc);
}

void PingFunc(Command& cmd) {
  Serial.println("{ \"status\": \"OK\" }");
}


void loop(void) {
  rest.Proceed();
}

