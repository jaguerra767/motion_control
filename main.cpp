#include "ClearCore.h"

[[noreturn]]
int main() {
    bool led_state = true;
    while(true){
        ConnectorLed.State(led_state);
        led_state = !led_state;
        Delay_ms(1000);
    }
}
