#include "MAX30102_MODULE.h"


int main() {
    MAX30102_Module sensor;
    
    sensor.initialize_module();
    
    while(1){
        sensor.readData();
    }
    return 0;
}