#include "ArduinoRest.h"
#include <Arduino.h>
#include <HardwareSerial.h>

ArduinoRest::ArduinoRest(HardwareSerial& serial) : _serial(serial)
{
    _requestLen = 0;
    handlersCount = 0;
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW); 
}

void ArduinoRest::AddHandler(const char* command, TFuncHandlerP funcPointer)
{
    handlers[handlersCount] = funcPointer;
    commands[handlersCount] = command;
    handlersCount++;
}
 
void ArduinoRest::Proceed(char* request)
{
    Command cmd(request);

    for (size_t n = 0; n < handlersCount; n++)
    {
        if (strcmp(commands[n], cmd.Name()) == 0)
        {
            handlers[n](cmd);
            return;
        }
    }
    
    _serial.print("{ \"status\": \"ERROR\", \"error\": \"Invalid command: '");
    _serial.print(cmd.Name());
    _serial.println("'\" }");
}

void ArduinoRest::Proceed()
{
    while (_serial.available() > 0)
    {
        digitalWrite(LED_BUILTIN, HIGH);

        int c = _serial.read();
        
        if (_requestLen >= BufferSize)
        {
            if (c == '\n' || c == '\r')
            {
                _serial.println("{ \"status\": \"ERROR\", \"error\": \"Request too long\" }");
                _requestLen = 0;
            }
            else
                _requestBuf[0] = c;
            
            continue;
        } 
        else if (_requestLen > 0 && (c == '\n' || c == '\r'))
        {
            if(_serial.available() == 1)
                _serial.read();
            
            _requestBuf[_requestLen] = 0;

            Proceed(_requestBuf);
            _requestLen = 0;

            continue;
        }
        
        _requestBuf[_requestLen++] = c;
    }
    digitalWrite(LED_BUILTIN, LOW);
}
