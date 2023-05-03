


#include "ClearCore.h"
#include "serial_viam.hpp"

Connector* output_LEDs[6] = {
        &ConnectorIO0, &ConnectorIO1, &ConnectorIO2, &ConnectorIO3, &ConnectorIO4, &ConnectorIO5
};

[[noreturn]] int main() {
    viam::setup();
    bool led_state = true;
    for (auto i:output_LEDs){
        i->Mode(Connector::OUTPUT_DIGITAL);
    }
    while (true) {
        //output_LEDs[2]->State(led_state);
        viam::cycle();
        ConnectorLed.State(led_state);
        led_state = !led_state;
        Delay_ms(500);
    }
}









