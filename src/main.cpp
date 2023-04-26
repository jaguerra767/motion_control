


#include "ClearCore.h"
#include "serial_viam.hpp"



[[noreturn]] int main() {
    while (true) {
        viam::setup();
        viam::cycle();
        Delay_ms(1000);
    }
}

