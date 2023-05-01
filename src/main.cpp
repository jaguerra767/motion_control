


#include "ClearCore.h"
#include "serial_viam.hpp"



[[noreturn]] int main() {
    viam::setup();
    while (true) {
        viam::cycle();
        Delay_ms(1000);
    }
}









