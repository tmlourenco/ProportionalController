#include <Arduino.h>
#include <string.h>

#include "display.h"
#include "control.h"

#define LED_HB                 7
#define BUTTON_P_PIN           2
#define BUTTON_S_PIN           3
#define BUTTON_ADD_PIN         9
#define BUTTON_SUB_PIN         8

#define INITIAL_SP          20.0
#define INITIAL_GAIN        10.0
#define VALUE_INCR           0.5

void button_init(void);
void control_init(void);
void heart_beating(uint8_t driver_state);
void select_screen(void);
void update_values(void);

extern uint8_t driver_enable;