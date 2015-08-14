/*******************************************************************************
* FILE NAME: user_routines.h
*
* DESCRIPTION: 
*  This is the include file which corresponds to user_routines.c and
*  user_routines_fast.c
*  It contains some aliases and function prototypes used in those files.
*
* USAGE:
*  If you add your own routines to those files, this is a good place to add
*  your custom macros (aliases), type definitions, and function prototypes.
*******************************************************************************/

#ifndef __user_program_h_
#define __user_program_h_
//player controls
//#define levelone  p3_sw_top
//#define leveltwo  p3_sw_aux1
//#define levelthree  p3_sw_aux2
#define shoulder  p2_x
#define elbow p2_y
#define wrist p2_wheel
//#define slider_control_on p2_sw_trig
//CLAW
#define claw_grab p2_sw_aux1
#define claw_release p2_sw_aux2
#define claw_pneu_fwd relay5_fwd
#define claw_pneu_rev relay5_rev  
//POTS
#define shoulder_pot	Get_Analog_Value(rc_ana_in04)
#define elbow_pot 		Get_Analog_Value(rc_ana_in05)
#define pot_wrist 		Get_Analog_Value(rc_ana_in06)
//pnuematics
#define upper_pneu_fwd relay3_fwd
#define upper_pneu_rev relay3_rev 
#define lower_pneu_fwd relay2_fwd
#define lower_pneu_rev relay2_rev
//wrist
#define wrist_motor pwm05
//compressor
#define digital_compressor rc_dig_in01
#define relay_compressor relay1_fwd
//drive
#define mot_lf pwm01	//left front
#define mot_rf pwm02	//right front
#define mot_lr pwm03	//left rear
#define mot_rr pwm04	//right rear
//wings
#define wings p2_sw_top
#define wing_servo_one pwm06
#define wing_servo_two pwm07
//autoleveling
#define slider_control_on p2_sw_trig
#define levelone  p3_sw_top
#define leveltwo  p3_sw_aux1
#define levelthree  p3_sw_aux2
#define pick_up_button p3_sw_trig
//Autonomous Buttons
#define auto_left p4_sw_top
#define auto_right p4_sw_trig
#define auto_light p4_sw_aux1
#define	auto_gap p4_sw_aux2
#define auto_spin_strafe p1_sw_trig
//limits
#define OPEN        1     /* Limit switch is open (input is floating high). */
#define CLOSED      0     /* Limit switch is closed (input connected to ground). */

/*******************************************************************************
                           FUNCTION PROTOTYPES
*******************************************************************************/

/* These routines reside in user_routines.c */
void User_Initialization(void);
void Process_Data_From_Master_uP(void);
void Default_Routine(void);
void Process_Disabled_Code(void);
void compressor(void);
void init_wings(void);
void control_wings(void);
/* These routines reside in user_routines_fast.c */
void InterruptHandlerLow (void);  /* DO NOT CHANGE! */
void User_Autonomous_Code(void);  /* Only in full-size FRC system. */
void Process_Data_From_Local_IO(void);
//omnidrive
void omnidrive(signed int xinpt, signed int yinpt, signed int zinpt);
void kiddydrive(signed int xinput, signed int yinput, signed int zinput);
//void go_straight(unsigned int input_speed);
void reverse_motor(int motornum);
unsigned int limit (int input_value, int low_value, int high_value);
//autoplacing
void first_level(void);
void second_level(void);
void third_level(void);
void pick_up(void);
//arm
void shoulder_control(void);
void elbow_control(void);
void wrist_control(void);
//autonomous
void Process_Autonomous_Code(void);
void custom_autonomous(void);
void defense_autonomous(void);
void dead_reckoning_autonomous(void);
//break dancing
void break_dance(void);
#endif
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
