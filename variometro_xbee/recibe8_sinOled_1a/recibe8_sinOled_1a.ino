#include <SoftwareSerial.h>
#define buzzer 11 

SoftwareSerial miSerial(2, 3); // RX, TX
boolean beep_on = true; 

float pressurecorrecture = 0.0;
float vario = 0;    
byte samples = 10;       //40
byte maxsamples = 20;     // 50
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
float numero;


void setup() {
  //Serial.begin(9600);     // Inicia el puerto serie principal
  miSerial.begin(9600);    // Inicia el SoftwareSerial en los pines 2 (RX) y 3 (TX)
}

void loop() {
  if (miSerial.available()) {  // Verifica si hay datos disponibles en SoftwareSerial
    
  numero = miSerial.parseFloat(); // Lee el número decimal
    //Serial.print("Numero recibido: ");  // Usa Serial.print() para que no agregue un salto de línea
    //Serial.println(numero);    // Imprime el número recibido
    variometro();
}
}


void variometro(){
float Altitude = numero;
   VarioMSCalculation();

    if (beep_on){             
      VarioBeep(0.2,-5.0);
    }
    //delay(10);  
}

void VarioMSCalculation() {
    tempo = millis();                                                       
    N1 = N2 = N3 = D1 = D2 = 0; // Reiniciar valores    
    vario = 0;       
    // Desplazar valores en los arrays dentro del rango correcto
    for (int cc = 0; cc < maxsamples - 1; cc++) {                                   
        alt[cc] = alt[cc + 1];                                                  
        tim[cc] = tim[cc + 1];                                                  
    }  

    // Agregar la nueva lectura
    alt[maxsamples - 1] = numero;                                   
    tim[maxsamples - 1] = tempo;                                                

    float stime = tim[maxsamples - samples];                                  

    for (int cc = maxsamples - samples; cc < maxsamples; cc++) {                 
        N1 += (tim[cc] - stime) * alt[cc];                                          
        N2 += (tim[cc] - stime);                                                  
        N3 += alt[cc];                                                         
        D1 += (tim[cc] - stime) * (tim[cc] - stime);                                  
        D2 += (tim[cc] - stime);                                                  
    }                                                                        
    
    float denominator = (samples * D1 - D2 * D2);
    if (denominator != 0) {
        vario = 1000 * ((samples * N1) - N2 * N3) / denominator;                     
    } else {
        vario = 0; // Evitar división por cero
    }
}

void VarioBeep(float TreshUp, float TreshDown) {
    if ((tempo - beep) > Beep_period + 100) { // Control del tiempo entre beeps                         
        beep = tempo;                                                    

        noTone(buzzer); // Apagar beep previo

        if (vario > TreshUp && vario < 15) {                                                              
            Beep_period = 400 - (vario * 80);       
            tone(buzzer, (500 + (250 * vario)), abs(Beep_period));
        }                                             
        else if (vario < -0.15) {                      
            Beep_period = 200;                                           
            tone(buzzer, 200, 400);                                    
        }                                                          
    } 

    //Serial.print("Variometro: ");
    //Serial.println(vario);       
}