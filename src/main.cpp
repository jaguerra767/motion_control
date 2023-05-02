


#include "ClearCore.h"
#include "serial_viam.hpp"



[[noreturn]] int main() {
    viam::setup();
    bool led_state = true;
    while (true) {
        viam::cycle();
        ConnectorLed.State(led_state);
        led_state = !led_state;
        Delay_ms(100);
    }
}









