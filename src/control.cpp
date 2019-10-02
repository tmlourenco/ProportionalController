#include "control.h"

float duty_heat;
float duty_fan;

void heat_control(void)
{
    if(manual_heat && !manual_fan){
		digitalWrite(ENABLE_HEAT, HIGH);
		digitalWrite(ENABLE_FAN, LOW);
		analogWrite(HEAT_PIN, map(heat_pwm, 0, 100, 0, 255));
	}	
	else if(!fan_state){
		digitalWrite(ENABLE_HEAT, LOW);
		digitalWrite(ENABLE_FAN, HIGH);
		duty_heat = (set_point - process_value) * gain;
		if(duty_heat > 65)	duty_heat = 65;
		if(duty_heat <= 0)	duty_heat = 0;

		analogWrite(HEAT_PIN, duty_heat);
	}
}

void fan_control(void)
{
    if(manual_fan && !manual_heat){	
		digitalWrite(ENABLE_HEAT, LOW);
		digitalWrite(ENABLE_FAN, HIGH);
		analogWrite(FAN_PIN, map(fan_pwm, 0, 255, 0, 100));
	}
	else if(!heat_state){
		digitalWrite(ENABLE_HEAT, HIGH);
		digitalWrite(ENABLE_FAN, LOW);

		duty_fan = (process_value - set_point) * 15;  // Erro * ganho
		
		if(duty_fan > 255)	duty_fan = 255;
		if(duty_fan <= 70)	duty_fan = 70;

		analogWrite(FAN_PIN, duty_fan);
	}
}