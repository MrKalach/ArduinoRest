#About
ArduinoRest is very simple implementation of REST API for arduino.

#Installation
Just copy ArduinoRest folder to your libraries folder. Restart Arduino IDE if needed.

#How to use
    #include <Arduino.h>
    #include <ArduinoRest.h>
    #include <stdio.h>
    
    ArduinoRest rest(Serial);  // define rest object and init it with Serial
    
    void setup(){
      Serial.begin(115200);
        
      rest.AddHandler("echoping", &EchoFunc);         //registering event handler
    }
    
    void EchoFunc(Command& cmd) {                     // our event handler
      const char* str = "";
      char buffer[100];
      
      cmd.GetStringParam("string", &str);             //getting "string" parameter to str
      sprintf(buffer, "{ \"echo\": \"%s\" }\n", str);
      
      Serial.print(buffer);
    }
    
    
    void loop(void) {
      rest.Proceed();                           // need to call every cycle
    }

