/**
 * i2c_Virtual.c header and declarations 
*/


#ifndef I2C_VIRTUAL_H
 #define I2C_VIRTUAL_H
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
enum direction {OUTPUT, INPUT};
//#define PORT()     PORT
//#define PIN_SDA  GPIO_SDA
//#define PIN_SCL  GPIO_SCL
#define SDA_SET(port, pin) gpio_set(port,pin)     /**< This macro call the gpio_set function to put high the output*/
#define SDA_CLR(port,pin) gpio_clear(port, pin)
#define SCL_SET(port, pin) gpio_set(port,pin)
#define SCL_CLR(port, pin) gpio_clear(port, pin)

typedef struct {
	uint32_t   port;		/**< I2C device */
    uint32_t   SDA; 
    uint32_t   SCL;
	uint16_t   timeout;	/**< ACK timeout */
    uint16_t   trise; 
    uint16_t   thold;  /**< Data hold ticks*/
    uint8_t slave_addr;
}I2C_config;

void i2c_set_outputs(I2C_config *dev, uint32_t port, uint32_t pin_sda,uint32_t pin_scl);
void i2c_set_sda_direction(I2C_config *dev, enum direction dir);
void i2c_set_trise(I2C_config *dev, uint16_t trise);
void i2c_set_thold(I2C_config *dev, uint16_t thold);
void i2c_set_timeout(I2C_config *dev, uint16_t timeout);
void wait(uint16_t tick);
void i2c_set_slave_addr(I2C_config *dev, uint8_t sl);
void start_bit(I2C_config *dev);
void stop_bit(I2C_config *dev);
void ack_output(I2C_config *dev);
uint8_t ack_input(I2C_config *dev);
uint8_t receive_byte(I2C_config *dev);
void send_byte(I2C_config *dev, uint8_t data);
uint16_t i2c_read(I2C_config *dev, uint8_t slave_addr, uint8_t reg_to_read);
void i2c_write(I2C_config *dev, uint8_t slave_addr, uint8_t reg_to_write, uint16_t data);
void i2c_write_mult(I2C_config *dev, uint8_t slave_addr, uint8_t reg_to_write, uint8_t *buf, uint16_t size);
void i2c_write_8bits(I2C_config *dev, uint8_t slave_addr, uint8_t reg_to_write, uint8_t data);

#endif
