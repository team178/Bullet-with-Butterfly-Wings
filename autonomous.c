#include <stdio.h>
#include "ifi_aliases.h"
#include "ifi_default.h"
#include "ifi_utilities.h"
#include "user_routines.h"
unsigned int phase = 0;
extern int autonomous_on;
int timer = 0;

//Autonomous switch vars
int pos;
int is_sliding_on_edge;
int target_mode;
int auto_disabled;
int dead;



void Process_Autonomous_Code(void)
{

	 if (timer <= 400)
	{
		timer++;
		lower_pneu_fwd = 1;
		lower_pneu_rev = 0;
	}
	else if (timer <= 520)
	{
		timer++;
		lower_pneu_fwd = 0;
		lower_pneu_rev = 0;
		upper_pneu_fwd = 1;
		upper_pneu_rev = 0;
	}
	else if (timer <= 535)
	{
		timer++;
		wrist_motor = 100;
		upper_pneu_fwd = 0;
		upper_pneu_rev = 0;
		//Release Claw
		claw_pneu_fwd = 0;
		claw_pneu_rev = 1;		
	}
	else
	{
		claw_pneu_fwd = 0;
		claw_pneu_rev = 1;
		wrist_motor = 127;
	}
/*

	 if (timer <= 180)
	{
		timer++;
		lower_pneu_fwd = 1;
		lower_pneu_rev = 0;
	}
	else if (timer <= 200)
	{
		timer++;
		lower_pneu_fwd = 0;
		lower_pneu_rev = 0;
		upper_pneu_fwd = 1;
		upper_pneu_rev = 0;
	}
	else if (timer <= 215)
	{
		timer++;
		wrist_motor = 100;
		upper_pneu_fwd = 0;
		upper_pneu_rev = 0;		
	}
	else if (timer <= 395)
	{
		omnidrive(127,178,127);
	}
	else if (timer <= 450)
	{
		omnidrive(127,127,127);
		claw_pneu_fwd = 0;
		claw_pneu_rev = 1;
		wrist_motor = 127;
	}
	else if (timer <= 570)
	{
		omnidrive(127,100,127);
		claw_pneu_fwd = 0;
		claw_pneu_rev = 0;
	}


*/
}


void break_dance(void)
{
	if(timer < 120)
	{
	omnidrive(127,127,200);
	timer ++;
	}
	else if (timer < 240)
	{
	omnidrive(127,127,56);
	timer++;
	}
	
}
