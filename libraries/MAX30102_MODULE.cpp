
#include <time.h>
#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include "MAX30102_MODULE.h"

#define F_CPU 16000000UL			
#include "lcd.h"

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to


MAX30105 particleSensor;

MAX30102_Module::MAX30102_Module()
{
}

uint16_t irBuffer[100]; //Dados sobre o IR lidos do armazenamento do sensor
uint16_t redBuffer[100];  //Dados sobre o LED lidos do armazenamento do sensor
LCD lcd;


void MAX30102_Module::setClock(unsigned long clock){
    #define F_CPU clock;
}

// Initialize sensor
bool MAX30102_Module::initialize_module(){    
    
    lcd.LCD_Initializer(); //Inicializa o lcd
    lcd.LCD_String("Inicializando...");
    _delay_ms(1000);

    byte ledBrightness = 60; //Options: 0=Off to 255=50mA
    byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
    byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
    byte sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
    int pulseWidth = 411; //Options: 69, 118, 215, 411
    int adcRange = 4096; //Options: 2048, 4096, 8192, 16384

    //A linha a seguir, aplica as configurações
    particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);
    
    lcd.LCD_Clear();
    lcd.LCD_String("Inicializado!");
    _delay_ms(400);
    return true;
}

bool MAX30102_Module::hasNewData(){
    if (particleSensor.available() == true){
        particleSensor.check();
        return true;
    }
    return false;
}

void MAX30102_Module::readData(){
    lcd.LCD_Clear();
    while (hasNewData() == false){ //Aguardando por novos dados
        //particleSensor.check(); //Checa os dados no armazenamento do sensor;
        lcd.LCD_String(("Encoste o dedo..."));
        delay(100);
    } 

    if (particleSensor.available() == true) {
        for (byte i = 0 ; i < 100 ; i++){

            redBuffer[i] = particleSensor.getRed();
            irBuffer[i] = particleSensor.getIR();
            particleSensor.nextSample(); //We're finished with this sample so move to next sample
            lcd.LCD_Clear();
            lcd.LCD_String(("red="));
            lcd.LCD_String((char *)redBuffer[i]);
            lcd.LCD_String((", ir="));
            lcd.LCD_String((char *)irBuffer[i]);
            _delay_ms(50);
        }
    }
}

