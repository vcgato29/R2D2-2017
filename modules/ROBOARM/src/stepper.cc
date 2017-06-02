#include "stepper.hh"

Stepper::Stepper(hwlib::target::pin_out &dir_pin, hwlib::target::pin_out &stp_pin) : dir_pin(dir_pin),
                                                                                     stp_pin(stp_pin) {
    stp_pin.set(0);
    dir_pin.set(1);
}

void Stepper::step(bool clockwise) {
    dir_pin.set(clockwise);
    hwlib::wait_ms(1);
    stp_pin.set(1);
    hwlib::wait_ms(1);
    stp_pin.set(0);
}
