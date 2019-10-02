#include <Arduino.h>

#define HEAT_PIN        6
#define FAN_PIN         5
#define ENABLE_HEAT     4
#define ENABLE_FAN      1
#define SENSOR_PIN     A0

void heat_control(void);
void fan_control(void);

extern uint8_t manual_heat;
extern uint8_t manual_fan;
extern uint8_t heat_pwm;
extern uint8_t fan_pwm;

extern uint8_t heat_state;
extern uint8_t fan_state;

extern float set_point;
extern float gain;
extern float process_value;