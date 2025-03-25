#include "VoltageReference.h"
#include <Adafruit_BMP280.h>

VoltageReference vRef;
Adafruit_BMP280 bmp;

#define buzzer 11   

boolean beep_on = true;     
float pressurecorrecture = 0.0;

float vario = 0;    
byte samples = 40;    
byte maxsamples = 50;
float alt[51];                                                       
float tim[51];  
float tempo = millis();             
float N1 = 0;                                 
float N2 = 0;                                
float N3 = 0;                                 
float D1 = 0;                               
float D2 = 0;      

float beep;                                  
float Beep_period;                

void setup() {                
  Serial.begin(9600);
  vRef.begin();
  bmp.begin(); 
  pinMode(buzzer, OUTPUT);
}

void loop() {
    float Altitude = bmp.readAltitude(1013.25 + pressurecorrecture);     

    VarioMSCalculation();

    if (beep_on){             
      VarioBeep(0.2,-5.0);
    }

    delay(39);  
}

void VarioMSCalculation(){
  tempo = millis();                                                       
  N1 = 0;                                                                 
  N2 = 0;                                                                 
  N3 = 0;                                                                 
  D1 = 0;                                                                 
  D2 = 0;                                                                 
  
  vario = 0;       

  for(int cc=1; cc<=maxsamples; cc++) {                                   
    alt[(cc-1)] = alt[cc];                                                
    tim[(cc-1)] = tim[cc];                                                
  }                                                                        
  alt[maxsamples] = bmp.readAltitude();                                   
  tim[maxsamples] = tempo;                                                
  float stime = tim[maxsamples-samples];                                  
                                                                          
  for(int cc=(maxsamples-samples); cc<maxsamples; cc++) {                 
    N1+=(tim[cc]-stime)*alt[cc];                                          
    N2+=(tim[cc]-stime);                                                  
    N3+=(alt[cc]);                                                        
    D1+=(tim[cc]-stime)*(tim[cc]-stime);                                  
    D2+=(tim[cc]-stime);                                                  
  }                                                                        
  
  vario = 1000*((samples*N1)-N2*N3)/(samples*D1-D2*D2);                     
}

void VarioBeep(float TreshUp, float TreshDown){
    if ((tempo - beep) > Beep_period + 100) {                         
        beep = tempo;                                                    
        if (vario > TreshUp && vario < 15) {                                                              
          Beep_period = 400-(vario*80);       
          tone(buzzer, (500 + (250 * vario)), abs(Beep_period));
        }                                             
        else if (vario < TreshDown) {                      
          Beep_period = 200;                                           
          tone(buzzer, 200, 400);                                    
        }                                                          
    }           
}