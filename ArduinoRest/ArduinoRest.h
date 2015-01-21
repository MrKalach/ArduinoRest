#ifndef __MyREST_H__
#define __MyREST_H__

#include <Arduino.h>
#include <HardwareSerial.h>
#include "Command.h"

typedef void (*TFuncHandlerP)(Command& cmd);

class ArduinoRest
{
public:
	static const size_t BufferSize = 128;
	static const size_t MAX_COUNT = 10;

    ArduinoRest(HardwareSerial& serial);
    void AddHandler(const char* command, TFuncHandlerP funcPointer);
    void Proceed(char* request);
    void Proceed();
private:    
	HardwareSerial&	_serial;
	char        	_requestBuf[BufferSize];
    size_t      	_requestLen;
	
	TFuncHandlerP 	handlers[MAX_COUNT];
	const char*		commands[MAX_COUNT];	
	size_t			handlersCount;
};



#endif