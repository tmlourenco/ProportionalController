#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

#define DISPLAY_ADDRESS 0x27

enum {
    STATUS=0, 
    SP_ADJUST, 
    G_ADJUST, 
    HEAT_M_MODE, 
    FAN_M_MODE, 
    DRIVER_DISABLED,

    NUMBER_OF_SCREENS
};

void display_init();
void display_update_screen();

extern LiquidCrystal_I2C lcd;
extern uint8_t page;

extern uint8_t out_state;
extern uint8_t heat_state;
extern uint8_t fan_state;
extern uint8_t heat_pwm;
extern uint8_t fan_pwm;

extern float temp_sp;
extern float temp_gain;
extern uint8_t temp_de;

extern float set_point;
extern float process_value;
extern uint8_t driver_enable;