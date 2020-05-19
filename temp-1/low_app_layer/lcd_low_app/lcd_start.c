#include "lcd_start.h"

static i2c_lcd i2c_t;

void lcd_setup(){
    rcc_periph_clock_enable(RCC_GPIOB);    // I2C
    /**
     * Set I2C configuration
    */
    i2c_set_outputs(&i2c_t, GPIOB, GPIO10, GPIO11);
    i2c_set_thold(&i2c_t, 3);  /**< Hoja de datos dice que 0 ns y setup time min 100 ns */
    i2c_set_trise(&i2c_t,  2);  /**< En fast-mode son 300 ns */
    i2c_set_timeout(&i2c_t, 8);
    i2c_set_slave_addr(&i2c_t, 0x3C);
    /**
     * Set LCD configuration
    */
    display_off(&i2c_t);
    set_osc_frecuency(&i2c_t, OSC_FRECUENCY_DEFAULT);
    set_mult_ratio(&i2c_t, MULTIP_RATIO);
    set_display_offset(&i2c_t, DISPLAY_OFFSET_DEFAULT);
    set_start_line(&i2c_t, DISPLAY_START_LINE_DEFAULT);
    set_charge_pump_regulator(&i2c_t, CHARGE_PUMP_DEFAULT);
    set_memory_mode(&i2c_t, MEMORY_MODE);
    set_segm_re_map(&i2c_t, SEGM_RE_MAP_DEFAULT);
    set_COM_output_direction(&i2c_t, COM_OUTPUT_DEFAULT);
    set_COM_pins_config(&i2c_t, COM_PINS_CONF_DEFAULT);
    set_contrast(&i2c_t, CONTRAST_DEFAULT);
    i2c_write_8bits(&i2c_t,i2c_t.slave_addr, CONT_BIT | CMD_MODE | CONTROL_REG, 0xd9);
    i2c_write_8bits(&i2c_t,i2c_t.slave_addr, CONT_BIT | CMD_MODE | CONTROL_REG, 0xF1);
    i2c_write_8bits(&i2c_t,i2c_t.slave_addr, CONT_BIT | CMD_MODE | CONTROL_REG,0xDB );
    i2c_write_8bits(&i2c_t,i2c_t.slave_addr, CONT_BIT | CMD_MODE | CONTROL_REG, 0x40);
    display_onresume(&i2c_t, ON_RAM);
    set_display_mode(&i2c_t, NORMAL_MODE);
    i2c_write_8bits(&i2c_t,i2c_t.slave_addr, CONT_BIT | CMD_MODE | CONTROL_REG, 0x2E);
    //set memory addressing mode
    //i2c_write(&i2c_t,i2c_t.slave_addr, CONT_BIT | CMD_MODE | CONTROL_REG, 0x20);
    i2c_write_8bits(&i2c_t,i2c_t.slave_addr, CONT_BIT | CMD_MODE | CONTROL_REG, 0xB0); 
    i2c_write_8bits(&i2c_t,i2c_t.slave_addr, CONT_BIT | CMD_MODE | CONTROL_REG, 0x00);
    i2c_write_8bits(&i2c_t,i2c_t.slave_addr, CONT_BIT | CMD_MODE | CONTROL_REG, 0x10);  
    display_on(&i2c_t);
}
void show_temp_lcd(char *str_temp){
    //lcd_fill(BLACK);
    uint8_t size = 4;
    char temp[size+1];
    temp[0] = str_temp[6];
    temp[1] = str_temp[7];
    temp[2] = str_temp[8];
    temp[3] = str_temp[9];
    lcd_send_word(&i2c_t, temp, size);
    lcd_update_screen(&i2c_t);

}
