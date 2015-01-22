#About
ArduinoRest is very simple implementation of REST API for arduino.

#Installation
Just copy ArduinoRest folder to your libraries folder. Restart Arduino IDE if needed.

#How to use
<pre>
#include &lt;Arduino.h&gt;
<b>#include &lt;ArduinoRest.h&gt;</b>
#include &lt;stdio.h&gt;

ArduinoRest rest(Serial);  // define rest object and init it with Serial

void setup(){
  Serial.begin(115200);
  <b>rest.AddHandler("echoping", &EchoFunc);</b>         //registering event handler
}

<b>void EchoFunc(Command& cmd)</b> {                     // our event handler
  const char* str = "";
  char buffer[100];
  
  <b>cmd.GetStringParam("string", &str);</b>             //getting "string" parameter to str
  sprintf(buffer, "{ \"echo\": \"%s\" }\n", str);
  
  Serial.print(buffer);
}


void loop(void) {
  <b>rest.Proceed();</b>                           // need to call every cycle
}
</pre>

#Result
![PuttyScreenshot](/ScreenShots/result.png)
