/*******************************************************************************
* FILE NAME: user_routines.c <FRC VERSION>
*
* DESCRIPTION:
*  This file contains the default mappings of inputs  
*  (like switches, joysticks, and buttons) to outputs on the RC.  
*
* USAGE:
*  You can either modify this file to fit your needs, or remove it from your 
*  project and replace it with a modified copy. 
*
*******************************************************************************/

#include <stdio.h>

#include "ifi_aliases.h"
#include "ifi_default.h"
#include "ifi_utilities.h"
#include "user_routines.h"
#include "user_Serialdrv.h"

//From autonomous
extern int pos;
extern int is_sliding_on_edge;
extern int target_mode;
extern int auto_disabled;
extern int dead;
int test = 0;
int shmove = 0;
int current_sh = 128;
int prev_sh = 128;
int target_sh = 128;
int direction_sh =0;
int direction_el = 0;

int elmove = 0;
int current_el = 128;
int prev_el = 128;
int target_el = 128;
int eldirection=0;

int wrist_tar = 0;
int wrist_state=0;

unsigned int limit (int input_value, int low_value, int high_value)
{
    if(input_value < low_value) 
	{
	      input_value = low_value; //limiting the low value of the input
	}
    else if(input_value > high_value)
	{
	      input_value = high_value; // limiting the high value.
	}
    return (unsigned)input_value;
}


void compressor(void) 
{
	if(!digital_compressor)
	{
		relay_compressor = 1;	
	}
	else
	{
		relay_compressor = 0;
	}
}



/*******************************************************************************
* FUNCTION NAME: User_Initialization
* PURPOSE:       This routine is called first (and only once) in the Main function.  
*                You may modify and add to this function.
* CALLED FROM:   main.c
* ARGUMENTS:     none
* RETURNS:       void
*******************************************************************************/
void User_Initialization (void)
{
	init_wings();
  User_Proc_Is_Ready();         /* DO NOT CHANGE! - last line of User_Initialization */
}

/*******************************************************************************
* FUNCTION NAME: Process_Data_From_Master_uP
* PURPOSE:       Executes every 26.2ms when it gets new data from the master 
*                microprocessor.
* CALLED FROM:   main.c
* ARGUMENTS:     none
* RETURNS:       void
*******************************************************************************/
void Process_Data_From_Master_uP(void)
{
  static unsigned char i;

  Getdata(&rxdata);   /* Get fresh data from the master microprocessor. */

  if(disabled_mode)
  {
	Process_Disabled_Code();
  }
  else
  {
  	Default_Routine();  /* Optional.  See below. */
  }
  /* Add your own code here. (a printf will not be displayed when connected to the breaker panel unless a Y cable is used) */

  //printf("shoulder_tar %3d, shoulder_pot %3d, shoulder_state %d\r",shoulder_tar,shoulder_pot,shoulder_state);  /* printf EXAMPLE */

  Generate_Pwms(pwm13,pwm14,pwm15,pwm16);

  /* Example code to check if a breaker was ever tripped. */



  Putdata(&txdata);             /* DO NOT CHANGE! */
}

void Process_Disabled_Code(void)
{
	auto_left = 1 - auto_left;
	auto_right = 1 - auto_right;
	auto_gap = 1 - auto_gap;
	auto_spin_strafe = 1 - auto_spin_strafe;


    if(auto_spin_strafe)
	{
		auto_disabled = 1;
	}
	else
	{
		auto_disabled = 0;
	}
 
	if(auto_left == 1 && auto_right == 0)
	{
		pos = 0;
	}	
	else if(auto_left == 0 && auto_right == 1)
	{
		pos = 2;
	}
	else
	{
		pos = 0;
		//CURRENTLY DEFAULTING TO LEFT SIDE, NO MIDDLE
	}
	if(auto_light == 1 && auto_gap == 0) 
	{
		target_mode = 0;
	}
	else if(auto_light == 0 && auto_gap == 1)
	{
		target_mode = 2;
	}
	else
	{
		target_mode = 1;
	}
	
	if(auto_light && auto_gap && auto_left && auto_right)
	{
		dead = 1;
	}


/*	if(found_camera == 0)
	{
		if(ping())
		{
			found_camera++;
		}
	}
	else if(found_camera == 1)
	{
		if(find_green())
		{
			found_camera ++;
		}
	}
	else
	{
		get_camera_data();
	}
*/
}




/*******************************************************************************
* FUNCTION NAME: Default_Routine
* PURPOSE:       Performs the default mappings of inputs to outputs for the
*                Robot Controller.
* CALLED FROM:   this file, Process_Data_From_Master_uP routine
* ARGUMENTS:     none
* RETURNS:       void
*******************************************************************************/
void Default_Routine(void)
{
	control_wings();
	//DRIVING!!!
	omnidrive(p1_x,p1_y,((((signed)p1_wheel-127)/3)+127));
	compressor();
	shoulder = 254 - shoulder;
	elbow= 254- elbow;
	wrist = 254 - wrist;
	//ARM STUFF!!!!

current_sh = shoulder;
target_sh = (837 - (current_sh*3/2));

printf("shmove %4d, direction %3d, current_sh %2d, target_sh %d, lower_pot %d\r",shmove,direction_sh,current_sh,target_sh, shoulder_pot);  /* printf EXAMPLE */

	if (direction_sh > 0 && shoulder_pot < target_sh)
	{
			lower_pneu_fwd = 0;
			lower_pneu_rev = 0;
			shmove = 0;
	}
	else if (direction_sh < 0 && shoulder_pot > target_sh)
	{	
			lower_pneu_fwd = 0;
			lower_pneu_rev = 0;
			shmove = 0;
	}


if (prev_sh > (current_sh + 3) || prev_sh < (current_sh - 3))
{
	shmove = 1;
	prev_sh = current_sh;
}

if (shmove == 1)
{
	if (shoulder_pot > target_sh)
	{
//		pnuematics go up;
		lower_pneu_fwd = 1;
		lower_pneu_rev = 0;
		direction_sh = 1;
	}
	else if (shoulder_pot < target_sh)
	{
//		pnuematics go down;
		lower_pneu_fwd = 0;
		lower_pneu_rev = 1;
		direction_sh = -1;
	}
	else
	{
		lower_pneu_fwd = 0;
		lower_pneu_rev = 0;
		direction_sh = 0;
		shmove=0;
	}
}

/*
current_el = elbow;
target_el = (837 - current_el*3/2);

/////////////////////////////


	if (direction_el > 0 && elbow_pot < target_el)
	{
			upper_pneu_fwd = 0;
			upper_pneu_rev = 0;
			elmove = 0;
	}
	else if (direction_el < 0 && elbow_pot > target_el)
	{	
			upper_pneu_fwd = 0;
			upper_pneu_rev = 0;
			elmove = 0;
	}


if (prev_el > (current_el + 3) || prev_el < (current_el - 3))
{
	elmove = 1;
	prev_el = current_el;
}

if (elmove == 1)
{
	if (elbow_pot > target_el)
	{
//		pnuematics go up;
		upper_pneu_fwd = 1;
		upper_pneu_rev = 0;
		direction_el = 1;
	}
	else if (elbow_pot < target_el)
	{
//		pnuematics go down;
		upper_pneu_fwd = 0;
		upper_pneu_rev = 1;
		direction_el = -1;
	}
	else
	{
		upper_pneu_fwd = 0;
		upper_pneu_rev = 0;
		direction_el = 0;
		elmove=0;
	}
}
*/

if ( wrist < 54)
{
	wrist_motor = 154;
}
else if (wrist >200)
{
	wrist_motor = 100;
}
else
{
	wrist_motor = 127;
}
if ( elbow < 54)
{
	upper_pneu_fwd = 0;
	upper_pneu_rev = 1;
	
}
else if (elbow > 200)
{
	upper_pneu_fwd = 1;
	upper_pneu_rev = 0;
}
else
{
	upper_pneu_fwd = 0;
	upper_pneu_rev = 0;
}
//////////////////////////


	if (claw_grab && claw_release)
	{
		claw_pneu_fwd = 1;
		claw_pneu_rev = 0;
	}
	else if (!claw_release && !claw_grab)
	{
		claw_pneu_fwd = 0;
		claw_pneu_rev = 1;
	}
	else 
	{
		claw_pneu_fwd = 0;
		claw_pneu_rev = 0;
	}



}
 /* END Default_Routine(); */




/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
