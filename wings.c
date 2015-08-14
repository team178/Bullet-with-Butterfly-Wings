#include "user_routines.h"
#include "ifi_aliases.h"
#include "ifi_utilities.h"
#include "ifi_default.h"

void control_wings(void)
{
	if (wings) 
	{
		wing_servo_one = 127;
		wing_servo_two = 127;
	}
	else
	{
		wing_servo_one = 10;
		wing_servo_two = 244;
	}
} 

void init_wings(void)
{
	wing_servo_one = 10;
	wing_servo_two = 244;
}
