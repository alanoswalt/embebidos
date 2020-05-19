/**
 * Copyright 2020 Jenifer A. Romero Flores
 * This .c file has all methods needed for
 * i2c protocol
 */


#include "i2c_Virtual.h"
void i2c_set_slave_addr(I2C_config *dev, uint8_t sl) {
    dev->slave_addr = sl;
}
/**
 * This method receive which ports are going to be use for I2C clock and data bus then
 * set clocks for those and gpio mode.
 * @param dev is a pointer to a struct that contains all i2c configuration.
 * @param port is a 32-bit integer that represents the port (A, B, C ...).
 * @param pin_sda is a 32-bit integer that contains the SDA pin chose
 * @param pin_scl is a 32-bit integer that contanins the SCL pin chose 
*/
void i2c_set_outputs(I2C_config *dev, uint32_t port, uint32_t pin_sda,uint32_t pin_scl){
    dev->port = port;
    dev->SDA = pin_sda;
    dev->SCL = pin_scl;
    gpio_set_mode(port,
                  GPIO_MODE_OUTPUT_2_MHZ,
                  GPIO_CNF_OUTPUT_PUSHPULL,
                  pin_sda|pin_scl);           
    SDA_SET(port, pin_sda);
    SCL_SET(port, pin_scl);   
}
/**
 * This method can set/change the SDA bus direction (input or output)
 * @param dev pointer to a struct which contains all i2c configuration.
 * @param dir enum whose values are INPUT and OUTPUT.
*/
void i2c_set_sda_direction(I2C_config *dev, enum direction dir){
    if(dir == OUTPUT){
        gpio_set_mode(dev->port,
                  GPIO_MODE_OUTPUT_2_MHZ,
                  GPIO_CNF_OUTPUT_PUSHPULL,
                  dev->SDA); 
    }else{
        gpio_set_mode(dev->port,
                  GPIO_MODE_INPUT,
                  GPIO_CNF_INPUT_PULL_UPDOWN,
                  dev->SDA); 
    }
}
/**
 * This method save the time rise/fall needed for SCL and SDA bus timing.
 * @param dev pointer to a struct which contains all i2c configuration.
 * @param trise 16-bit integer that carry the number of ticks needed for rising/falling
*/
void i2c_set_trise(I2C_config *dev, uint16_t trise){
    dev->trise = trise;
}
/**
 * This method save the hold time for SCL and SDA signals. 
 * @param dev pointer to a struct which contains all i2c configuration.
 * @param thold 16-bit integer that carry the number of ticks equivalent to the hold time
*/
void i2c_set_thold(I2C_config *dev, uint16_t thold){
    dev->thold = thold;
}
/**
 * This method save the timeout time to wait for an slave ack.  
 * @param dev pointer to a struct which contains all i2c configuration.
 * @param timeout 16-bit integer that carry the number of ticks equivalent to the timeout.
*/
void i2c_set_timeout(I2C_config *dev, uint16_t timeout){
    dev->timeout = timeout;
}
/**
 * This method receive a integer number that represents the number of ticks that 
 * are needed to wait.  
 * @param dev pointer to a struct which contains all i2c configuration.
 * @param tick 16-bit integer with a finite number equivalent to a timing.
*/
void wait(uint16_t tick){ 
    do {
        __asm__("nop"); /**< Each tick is equal to one (1/clock frecuency long) */
    } while (--tick);

}
void start_bit(I2C_config *dev){
    SDA_SET(dev->port, dev->SDA);
    SCL_SET(dev->port, dev->SCL); 
    wait(dev->trise);
    SDA_CLR(dev->port, dev->SDA);
    wait(dev->thold);
    SCL_CLR(dev->port, dev->SCL);
}
void stop_bit(I2C_config *dev){
    SDA_CLR(dev->port, dev->SDA);
    SCL_SET(dev->port, dev->SCL);
    wait(dev->trise);
    SDA_SET(dev->port, dev->SDA);
    wait(dev->thold);
    //SDA_CLR();
    //SCL_CLR();
}
/**
 * This method represents the acknoledge given by the master when a read 
 * command is sent.
 * @param dev pointer to a struct which contains all i2c configuration.
*/
void ack_output(I2C_config *dev){
    SDA_CLR(dev->port, dev->SDA);
    SCL_SET(dev->port, dev->SCL);
    wait(dev->trise);
    SCL_CLR(dev->port, dev->SCL);
    wait(dev->thold);
}
/**
 * This method represents the acknoledge given by the slave when a read/write 
 * command is sent.
 * @param dev pointer to a struct which contains all i2c configuration.
*/
uint8_t ack_input(I2C_config *dev){
    /** This ack is coming from the slave */
    uint8_t ack;
    SCL_SET(dev->port, dev->SCL);
    wait(dev->trise);
    i2c_set_sda_direction(dev, INPUT);
    if ((gpio_port_read(dev->port) & (dev->SDA)) == (dev->SDA)){
        ack = 1;
    } else {
        ack = 0;
    }
    i2c_set_sda_direction(dev, OUTPUT);
    SCL_CLR(dev->port, dev->SCL);
    wait(dev->thold);
    return ack;
}
uint8_t receive_byte(I2C_config *dev){
    uint8_t byte = 8, temp = 0;
    i2c_set_sda_direction(dev, INPUT);
    do {
        SCL_CLR(dev->port, dev->SCL);
        wait(dev->thold);
        temp<<= 1;
        if((gpio_port_read(dev->port) & (dev->SDA)) == (dev->SDA)){
            temp|= 1;
        }
        SCL_SET(dev->port, dev->SCL);
        wait(dev->thold);
    } while (--byte);
    SCL_CLR(dev->port, dev->SCL);
    i2c_set_sda_direction(dev,OUTPUT);
    return temp;
}
void send_byte(I2C_config *dev, uint8_t data){
    uint8_t byte = 8;
    do {
        if (data & 0x80){
            SDA_SET(dev->port, dev->SDA);
        } else {
            SDA_CLR(dev->port, dev->SDA);
        }
        data<<= 1;
        SCL_SET(dev->port, dev->SCL);
        wait(dev->trise);
        SCL_CLR(dev->port, dev->SCL);
        wait(dev->thold);
    } while (--byte);
    //SDA_CLR();
}
/**
 * This method performs  a read command sent to the slave device. This was made
 * for read a 16-bit wide integer.
 * @param dev pointer to a struct which contains all i2c configuration.
 * @param slave_addr 1 byte long to contain the slave address.
 * @param reg_to_read 1 byte long to contain the regiter address to read.
 * @return read_data 2-bytes long returned register lecture.
*/
uint16_t i2c_read(I2C_config *dev, uint8_t slave_addr, uint8_t reg_to_read){
    uint16_t read_data = 0;
    start_bit(dev);
    send_byte(dev, slave_addr<<1);
    if (!ack_input(dev)) {
        send_byte(dev, reg_to_read);
        if (!ack_input(dev)) {
            start_bit(dev);
            send_byte(dev, (slave_addr<<1)+1);
            if (!ack_input(dev)) {
                read_data = receive_byte(dev);
                ack_output(dev);
                read_data = (read_data<<8) | receive_byte(dev);
                ack_output(dev);
                stop_bit(dev);
            } else{
                stop_bit(dev);
            }
        } else{
            stop_bit(dev);
        }
    } else{
        stop_bit(dev);
    }
    return read_data;
}
/**
 * This method performs a write command sent to the slave device. This was made
 * for write in a 16-bit integer register.
 * @param dev pointer to a struct which contains all i2c configuration.
 * @param slave_addr 1 byte long to contain the slave address.
 * @param reg_to_write 1 byte long to contain the regiter address will be written.
*/
void i2c_write(I2C_config *dev, uint8_t slave_addr, uint8_t reg_to_write, uint16_t data){
    start_bit(dev);
	send_byte(dev, slave_addr<<1);
	if (!ack_input(dev)) {
			send_byte(dev, reg_to_write);
			if (!ack_input(dev)) {
				send_byte(dev, data>>8);  //0100 0100 1000 0011
                if (!ack_input(dev)) {
                    send_byte(dev, data);
                    if (!ack_input(dev)) {
					    stop_bit(dev);
                    } else {
                        stop_bit(dev);
                    }
                } else {
                    stop_bit(dev);
                }
				
			} else {
                stop_bit(dev);
            }
	} else {
        stop_bit(dev);
    }
}
void i2c_write_mult(I2C_config *dev, uint8_t slave_addr, uint8_t reg_to_write, uint8_t *buf, uint16_t size){
    start_bit(dev);
	send_byte(dev, slave_addr<<1);
	if (!ack_input(dev)) {
			send_byte(dev, reg_to_write);
			if (!ack_input(dev)) {
                for (uint8_t i = 0; i < size; i++){
                    send_byte(dev, buf[i]);
                    if(ack_input(dev)){
                        stop_bit(dev);
                    }
                }
                stop_bit(dev);
            }else{
                stop_bit(dev);
            }
	} else {
        stop_bit(dev);
    }
}
void i2c_write_8bits(I2C_config *dev, uint8_t slave_addr, uint8_t reg_to_write, uint8_t data){
    start_bit(dev);
	send_byte(dev, slave_addr<<1);
	if (!ack_input(dev)) {
			send_byte(dev, reg_to_write);
			if (!ack_input(dev)) {
				    send_byte(dev, data);  //0100 0100 1000 0011
                if (!ack_input(dev)) {
                    stop_bit(dev);
                        
                } else {
                    stop_bit(dev);
                }
				
			} else {
                stop_bit(dev);
            }
	} else {
        stop_bit(dev);
    }
}