/* libusbcdc header
 * Warren W. Gay VE3WWG
 */
#ifndef LIBUSBCDC_H
#define LIBUSBCDC_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <libopencm3/cm3/scb.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>
#include <libopencm3/cm3/scb.h>

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include <libwwg/src/miniprintf.h>
#include <libwwg/src/getline.h>

void usb_start(void);
bool usb_ready(void);

void usb_putc(char ch);
void usb_puts(const char *buf);
void usb_write(const char *buf,unsigned bytes);
int usb_vprintf(const char *format,va_list ap);

int usb_printf(const char *format,...);

int usb_getc(void);
int usb_getline(char *buf,unsigned maxbuf);

#endif /* LIBUSBCDC_H */

/* End libusbcdc.h */
