//include radiohead library for amplitude shift keying
#include <RH_ASK.h>

//include the SPI library
#include <SPI.h> 

//create amplitude shift keying object
RH_ASK rf_driver;

const int xPin   = A3;
const int yPin   = A2;
const int zPin   = A1;


int x = 0;
int y = 0;
int z = 0;

void setup() {
  pinMode(0,INPUT);
  pinMode(1,OUTPUT);

  //referencing externa 3.3v for analog pins reference
  analogReference(EXTERNAL);
      
    // Initialize ASK Object
    rf_driver.init();

Serial.begin(256000);
} // end setup

void loop() {
    x = analogRead(xPin);
    y = analogRead(yPin);
    
    str_x = String(constrain(map(x,406,612,0,180),0,180));
    str_y = String(constrain(map(y,399,605,0,180),0,180));

    str_out = str_x + str_y;
    
    static char *msg = str_out.c_str();
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
} 
