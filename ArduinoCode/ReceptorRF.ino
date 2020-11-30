#include <VirtualWire.h>
 
const int dataPin = 2;
const int ledPin = 13;
int cont = 0;
int ent = 0;
int sal = 0;
 
void setup()
{
    Serial.begin(9600);
    vw_setup(2000);
    vw_set_rx_pin(dataPin);
    vw_rx_start();
    
    
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, false);
}
 
void loop()
{
    uint8_t data;
    uint8_t dataLength=1;
 
    if (vw_get_message(&data,&dataLength))
    {
        if((char)data=='a'){
          if (ent==0){
            digitalWrite(ledPin, true);
            Serial.print("Entrada");
            delay(1000);
            cont++;
            ent=1;
            sal=0;
          }
      
            
        }
        else if((char)data=='b')
        { 
          if (sal==0){
            digitalWrite(ledPin, false);
            //Serial.print("Salida");
            delay(1000);
            sal=1;
            ent=0;
          }
            
          }else{
            if((char)data=='c'){
              Serial.print("Salida");
              delay(1500);
              
              
              
            }
            

            
          }
            
     }            
 }
