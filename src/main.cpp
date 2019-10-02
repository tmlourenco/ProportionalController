#include "main.h"

float set_point = INITIAL_SP;
float gain = INITIAL_GAIN;
float process_value;

uint8_t out_state = 0;
uint8_t heat_state = 0;
uint8_t fan_state = 0;

uint8_t heat_pwm = 20;
uint8_t fan_pwm  = 35;

uint8_t driver_enable = 0;

uint8_t page = STATUS;

unsigned long time_hb;
unsigned long atual_hb;
uint8_t liga=0;

unsigned long time_bt;
unsigned long atual_bt;

uint8_t temp_de = driver_enable;
float temp_sp = set_point;
float temp_gain = gain;

uint8_t manual_heat = 0;
uint8_t manual_fan = 0;

void setup() 
{
  display_init();
  button_init();
  control_init();

  pinMode(LED_HB, OUTPUT);

  /* Interrupcao externa adicionada a borda de subida no pino do botão P */
  attachInterrupt(digitalPinToInterrupt(BUTTON_P_PIN), select_screen, RISING);
}

void loop() 
{
  display_update_screen();
  update_values();
  heart_beating(driver_enable);  
}

void control_init(void)
{
  pinMode(HEAT_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(ENABLE_HEAT, OUTPUT);
  pinMode(ENABLE_FAN, OUTPUT);
}

void button_init(void)
{
  pinMode(BUTTON_P_PIN,   INPUT);
  pinMode(BUTTON_S_PIN,   INPUT);
  pinMode(BUTTON_ADD_PIN, INPUT);
  pinMode(BUTTON_SUB_PIN, INPUT);
}

void heart_beating(uint8_t driver_state)
{
  if(!driver_state)   digitalWrite(LED_HB, 1);
  else
  {
    atual_hb = millis();
    if(atual_hb - time_hb > 2000){
      digitalWrite(LED_HB, liga);
      liga = !liga;
      time_hb = atual_hb;
    }
  }
}

void select_screen(void)
{
  if(page <= NUMBER_OF_SCREENS)   page++;
  else                            page=0;
}

void update_values(void)
{
  

	for (int i = 0; i < 50; i++) {
    process_value += (analogRead(SENSOR_PIN) * 5.0/1023)/0.01;
  }
	
  process_value = process_value / 52;

  if(!manual_heat && !manual_fan){
    if(process_value < set_point){
      heat_state = 1;
      fan_state  = 0;
      heat_control();
    }
    else{
      heat_state = 0;
      fan_state  = 1;
      fan_control();
    }             
  }

  switch (page)
  {
    case SP_ADJUST:
      if(digitalRead(BUTTON_ADD_PIN)){
        
        atual_bt = millis();
        while(digitalRead(BUTTON_ADD_PIN) == HIGH);
        time_bt = millis();

        if(time_bt - atual_bt >= 100)   temp_sp += VALUE_INCR;
      }

      if(digitalRead(BUTTON_SUB_PIN)){
        atual_bt = millis();
        while(digitalRead(BUTTON_SUB_PIN) == HIGH);
        time_bt = millis();

        if(time_bt - atual_bt >= 100)   temp_sp -= VALUE_INCR;
      }

      if(digitalRead(BUTTON_S_PIN)){
        page = STATUS;
        set_point = temp_sp;
      }     

    break;

    case G_ADJUST:
      if(digitalRead(BUTTON_ADD_PIN)){
        
        atual_bt = millis();
        while(digitalRead(BUTTON_ADD_PIN) == HIGH);
        time_bt = millis();

        if(time_bt - atual_bt >= 100)   temp_gain += VALUE_INCR;
      }

      if(digitalRead(BUTTON_SUB_PIN)){
        atual_bt = millis();
        while(digitalRead(BUTTON_SUB_PIN) == HIGH);
        time_bt = millis();

        if(time_bt - atual_bt >= 100)   temp_gain -= VALUE_INCR;
      }

      if(digitalRead(BUTTON_S_PIN)){
        page = STATUS;
        gain = temp_gain;
      }

    break;

    case HEAT_M_MODE:
        manual_heat = 0;
        manual_fan  = 1;
        if(!heat_state){
          if(digitalRead(BUTTON_ADD_PIN)){
            atual_bt = millis();
            while(digitalRead(BUTTON_ADD_PIN) == HIGH);
            time_bt = millis();

            if(time_bt - atual_bt >= 100)   heat_state = 1;
          }
        }
        else{
          if(digitalRead(BUTTON_ADD_PIN)){
            atual_bt = millis();
            while(digitalRead(BUTTON_ADD_PIN) == HIGH);
            time_bt = millis();

            if(time_bt - atual_bt >= 100)   heat_pwm += 10;
          }

          if(digitalRead(BUTTON_SUB_PIN)){
            atual_bt = millis();
            while(digitalRead(BUTTON_SUB_PIN) == HIGH);
            time_bt = millis();

            if(time_bt - atual_bt >= 100)    heat_pwm -= 10;
            if(time_bt - atual_bt >= 1000)   heat_state = 0;
          }
        }
        
    break;

    case FAN_M_MODE:
        manual_heat = 1;
        manual_fan  = 0;
        if(!fan_state){
          if(digitalRead(BUTTON_ADD_PIN)){
            atual_bt = millis();
            while(digitalRead(BUTTON_ADD_PIN) == HIGH);
            time_bt = millis();

            if(time_bt - atual_bt >= 100)   fan_state = 1;
          }
        }
        else{
          if(digitalRead(BUTTON_ADD_PIN)){
            atual_bt = millis();
            while(digitalRead(BUTTON_ADD_PIN) == HIGH);
            time_bt = millis();

            if(time_bt - atual_bt >= 100)   fan_pwm += 10;
          }

          if(digitalRead(BUTTON_SUB_PIN)){
            atual_bt = millis();
            while(digitalRead(BUTTON_SUB_PIN) == HIGH);
            time_bt = millis();

            if(time_bt - atual_bt >= 100)    fan_pwm -= 10;
            if(time_bt - atual_bt >= 1000)   fan_state = 0;
          }
        }
        
    break;

    case DRIVER_DISABLED:
      if(digitalRead(BUTTON_ADD_PIN)){
        
        atual_bt = millis();
        while(digitalRead(BUTTON_ADD_PIN) == HIGH);
        time_bt = millis();

        if(time_bt - atual_bt >= 100)   temp_de = 1;
      }

      if(digitalRead(BUTTON_SUB_PIN)){
        atual_bt = millis();
        while(digitalRead(BUTTON_SUB_PIN) == HIGH);
        time_bt = millis();

        if(time_bt - atual_bt >= 100)   temp_de = 0;
      }

      if(digitalRead(BUTTON_S_PIN)){
        page = STATUS;
        driver_enable = temp_de;
      }

    break;

  default:
    break;
  }
}