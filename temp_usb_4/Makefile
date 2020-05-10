# -*- MakeFile -*-
BINARY = main
SRCFILES = main.c usb/usbcdc.c usb/rtos/heap_4.c usb/rtos/list.c usb/rtos/port.c usb/rtos/queue.c usb/rtos/tasks.c usb/rtos/opencm3.c\
	low_app_layer/gpio_low_app/gpio_start.c\
	low_app_layer/gpio_low_app/gpio_hal/gpio_init.c\
	low_app_layer/uart_low_app/uart_start.c\
	low_app_layer/uart_low_app/uart_hal/uart_init.c\
	low_app_layer/tim_low_app/tim_start.c\
	low_app_layer/tim_low_app/tim_hal/tim_init.c\
	low_app_layer/I2C_low_app/i2c_Virtual.c\
	low_app_layer/adc_low_app/adc_start.c\
	low_app_layer/adc_low_app/adc_hal/adc_i2c_init.c\
	low_app_layer/lcd_low_app/lcd_start.c\
	ssd1306_oled/lcd.c
	#low_app_layer/adc_low_app/adc_hal/adc_init.c
LDSCRIPT	= usb/stm32f103c8t6.ld

all: elf bin

include ../Makefile.incl
include ../rtos/Makefile.rtos

 
