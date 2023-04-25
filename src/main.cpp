

#include <cstdint>
#include "ClearCore.h"

//Viam defines
constexpr int V_OK = 0;
constexpr int V_ERR = 1;
constexpr int V_SENT = 2;
constexpr int V_RCV = 3;



int main() {
    bool led_state = true;
    while(true){
        ConnectorLed.State(led_state);
        led_state = !led_state;
        Delay_ms(1000);
    }
}

