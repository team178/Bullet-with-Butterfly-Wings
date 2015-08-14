//motors
#include "ifi_aliases.h"
#include "ifi_default.h"
#include "user_routines.h"
#include "camera.h"
#include "gyro.h"
#include <stdio.h>



/*
void set_motors(signed int lmot, signed int rmot) 
{
	motor_l = lmot;
	motor_l2 = lmot;
	motor_r = rmot;
	motor_r2 = rmot;
}
*/

void omnidrive(signed int xinpt, signed int yinpt, signed int zinpt)
{
	
	signed int p1_z = ((signed) zinpt-127);	//for rotation
	signed int asdf = limit((signed)yinpt - (254 - (signed)xinpt) + 127,0,254);
	signed int fdsa = limit((signed)yinpt - (signed)xinpt + 127,0,254);
	mot_lf = limit((signed)asdf+(signed)p1_z,0,254);	//Front Left
	mot_rr = limit((signed)asdf-(signed)p1_z,0,254);	//Rear Right
	mot_rf = limit((signed)fdsa-(signed)p1_z,0,254);	//Front Right
	mot_lr = limit((signed)fdsa+(signed)p1_z,0,254);	//Rear Left
//1:leftfront 2:rightfront 3:leftback 4:rightback
reverse_motor(2);
reverse_motor(4);
//fill_gyro_vars();
}

/*void go_straight(unsigned int input_speed)
{
	//
}
*/ 
void reverse_motor(int motornum)
{
	if(motornum == 1)
	{
		pwm01 = 254 - pwm01;
	}
	else if(motornum == 2)
	{
		pwm02 = 254 - pwm02;
	}
	else if(motornum == 3)
	{
		pwm03 = 254 - pwm03;
	}
	else
	{
		pwm04 = 254 - pwm04;
	}
}

void kiddydrive(signed int xinput, signed int yinput, signed int zinput)
{
		xinput -= 127;
		xinput = xinput / 4;
		xinput += 127;

		yinput -= 127;
		yinput = yinput / 4;
		yinput += 127;

		zinput -= 127;
		zinput = zinput / 2;
		zinput += 127;
		omnidrive(xinput,yinput,zinput);
}
