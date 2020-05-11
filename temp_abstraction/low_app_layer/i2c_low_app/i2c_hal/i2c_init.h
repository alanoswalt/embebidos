#ifndef I2C_H_
#define I2C_H_
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/gpio.h>
#include <stdint.h>
#include <stdbool.h>
enum I2C_RW {
    Read = 1,
    Write = 0
};
extern void i2c_setup(void);
extern void i2c_start_addr(uint8_t addr, enum I2C_RW rw);
extern uint8_t i2c_read(bool lastf);
extern void i2c_stop(void);
extern void i2c_write(uint8_t byte);
extern void i2c_write_restart(uint8_t byte, uint8_t addr);
#endif