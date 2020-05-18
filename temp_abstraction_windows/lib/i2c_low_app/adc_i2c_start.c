#include "adc_i2c_start.h"
void ADC_setup(void) {
    i2c_setup();
    i2c_start_addr(0x48, Write);
    i2c_write(0x0);
    i2c_stop();
}

uint16_t read_adc(void) {
    uint16_t read_data = 0;
    uint16_t lsb = 0;
    i2c_start_addr(0x48, Write);
    i2c_write_restart(0x0,0x48);
    read_data = i2c_read(false);
    lsb = i2c_read(true);
    i2c_stop();
    read_data = (read_data << 8) | lsb;
    return read_data * 205 /32768;
}

void adc_status(short st) {
    // Nothing to do
}