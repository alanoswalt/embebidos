//#ifdef LCD_SETUP_H
#define LCD_SETUP_H


#include "../low_app_layer/I2C_low_app/i2c_Virtual.h"




 #define LCD_WIDTH 0x80  /**< 128 */
 #define LCD_HEIGHT 0x20   /**< 32 */
 #define FONT_HEIGHT 26
 #define FONT_WIDTH 16

/**
 * Control variables
 * */
 #define CONTROL_REG 0x00  /**< Register to write, 6-bits wide all 0's */
 #define CONT_BIT (0<<7) /**< This bit is part of the @see CONTROL_REG trama, but I do not what it means */
 #define CMD_MODE (0<<6) /**< command mode */
 #define DATA_MODE (1<<6) /**< This bit is part of the @see CONTROL_REG and it means that a graphic data will be sent */

/**
 * Default values for commands
 * */
 #define MULTIP_RATIO LCD_HEIGHT-1
 #define DISPLAY_OFFSET_DEFAULT 0x00
 #define DISPLAY_START_LINE_DEFAULT 0x40
 #define SEGM_RE_MAP_DEFAULT 0xA1  /**< A0/A1 */
 #define COM_OUTPUT_DEFAULT 0xC8  /**< 0xC8 remapped mode. Scan from COM[N-1] to COM0 */
                                  /**< 0xC0 normal mode. Scan from COM0 to COM[N-1] */
 #define COM_PINS_CONF_DEFAULT 0x02  /**< Sequential COM, Disable COM Left/Right remap*/
 #define CONTRAST_DEFAULT 0x8F
 #define NORMAL_MODE 0xA6
 #define OSC_FRECUENCY_DEFAULT 0xF0
 #define CHARGE_PUMP_DEFAULT 0x14
 #define MEMORY_MODE 0x00 /**< Horizontal addressing mode */

 /**
  * 
 */
 #define COLUMN_ADDR_START 0x00
 #define COLUMN_ADDR_END LCD_WIDTH-1
   
typedef I2C_config i2c_lcd;

enum mode_on {
    ON_RAM,
    ON_NON_RAM
};

enum background{
    BLACK,
    WHITE,
    LINES 
};
typedef struct {
    uint8_t x;
    uint8_t y;
}cursor;

void display_onresume(i2c_lcd *dev, enum mode_on bit_e);
void display_off(i2c_lcd *dev);
void display_on(i2c_lcd *dev);
void set_mult_ratio(i2c_lcd *dev, uint8_t r_m);
void set_clock_divider(i2c_lcd *dev, uint8_t c_d);
void set_display_offset(i2c_lcd *dev, uint8_t o_s);
void set_start_line(i2c_lcd *dev, uint8_t s_l);
void set_segm_re_map(i2c_lcd *dev, uint8_t s_r);
void set_COM_output_direction(i2c_lcd *dev, uint8_t o_d);
void set_COM_pins_config(i2c_lcd *dev, uint8_t pins);
void set_contrast(i2c_lcd *dev, uint8_t c);
void set_display_mode(i2c_lcd *dev, uint8_t m);
void set_osc_frecuency(i2c_lcd *dev, uint8_t o_f);
void set_charge_pump_regulator(i2c_lcd *dev, uint8_t c_p);
//void lcd_draw_pixel(uint8_t x, uint8_t y, enum background color_e);
void lcd_draw_pixel(i2c_lcd *dev,uint8_t x, uint8_t y, enum background color_e);
void set_memory_mode(i2c_lcd *dev, uint8_t m_m);
void lcd_update_screen(i2c_lcd *dev);
void lcd_fill(enum background bgd);
//void lcd_write_char(char ch, enum background color_e, cursor position);
void lcd_write_char(i2c_lcd *dev,char ch, enum background color_e, cursor position);
void lcd_send_word(i2c_lcd *dev, char *str, uint8_t size);

//#endif