#include "display.h"

LiquidCrystal_I2C lcd(DISPLAY_ADDRESS,2,1,0,4,5,6,7,3, POSITIVE);

unsigned long time_display;
unsigned long atual_display;

static void display_status()
{
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.write("SP:     C   ");
    
    if(out_state)     lcd.write("Heat");
    else              lcd.write("Fan");

    if(set_point/100.0 >= 1.0)
        lcd.setCursor(5,0);
    else
        lcd.setCursor(4,0);
    lcd.print(set_point, 1);
    
    lcd.setCursor(0,1);
    lcd.write("PV:     C   ");
    if(heat_state || fan_state) driver_enable=1;
    else                        driver_enable=0;

    if(driver_enable)     lcd.write("ON");
    else                  lcd.write("OFF");

    if(process_value/100.0 >= 1.0)
        lcd.setCursor(5,1);
    else
        lcd.setCursor(4,1);
    lcd.print(process_value, 1);
}

static void display_sp_adjust()
{
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.write("New Set Point");
    
    lcd.setCursor(0,1);
    lcd.write("SP: ");
    lcd.print(temp_sp,1);
}

static void display_g_adjust()
{
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.write("New Prop. Gain");
    
    lcd.setCursor(0,1);
    lcd.write("Kp: ");
    lcd.print(temp_gain,1);
}

static void display_heat_mode()
{
    lcd.clear();

    lcd.setCursor(2,0);
    lcd.write("Manual Mode");
    
    lcd.setCursor(0,1);
    lcd.write("Heat: ");

    if(heat_state){
         lcd.write("ON");
         lcd.setCursor(11, 1);
         lcd.print(heat_pwm,1);
         lcd.print("%");
    }
    else lcd.write("OFF");

}

static void display_fan_mode()
{
    lcd.clear();

    lcd.setCursor(2,0);
    lcd.write("Manual Mode");
    
    lcd.setCursor(0,1);
    lcd.write("Fan: ");
    
    if(fan_state){
         lcd.write("ON");
         lcd.setCursor(11, 1);
         lcd.print(fan_pwm,1);
         lcd.print("%");
    }
    else lcd.write("OFF");
}

static void display_driver()
{
    lcd.clear();

    lcd.setCursor(2,0);
    lcd.write("Driver Status");
    lcd.setCursor(4,1);

    if(temp_de)       lcd.write("Enable");
    else                    lcd.write("Disable");
}

void display_init()
{
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setBacklight(HIGH);
} 

void display_update_screen()
{
    switch (page)
    {
        case STATUS:
            atual_display = millis();
            if(atual_display - time_display >= 200){
                display_status();
                time_display = millis();
            }

        break;

        case SP_ADJUST:
            atual_display = millis();
            if(atual_display - time_display >= 200){
                display_sp_adjust();
                time_display = millis();
            }

        break;

        case G_ADJUST:
            atual_display = millis();
            if(atual_display - time_display >= 200){
                display_g_adjust();
                time_display = millis();
            }

        break;

        case HEAT_M_MODE:
            atual_display = millis();
            if(atual_display - time_display >= 200){
                display_heat_mode();
                time_display = millis();
            }
           
        break;

        case FAN_M_MODE:
            atual_display = millis();
            if(atual_display - time_display >= 200){
                display_fan_mode();
                time_display = millis();
            }
            
        break;

        case DRIVER_DISABLED:
            atual_display = millis();
            if(atual_display - time_display >= 200){
                display_driver();
                time_display = millis();
            }
    
        break;

        default:
        break;
    }
}