#include <stdio.h>
#include "ifi_aliases.h"
#include "ifi_default.h"
#include "ifi_utilities.h"
#include "user_routines.h"
int is_tracking = 0;
int packet_count = 0;
/*
int num_of_lights;
int color_ref;
int xl;
int yl;
int xr;
int yr;
int color_ref_2;
int xl_2;
int yl_2;
int xr_2;
int yr_2;
int camx;
int camy;
int camx_2;
int camy_2;
int light_size_x;
int light_size_y;
int light_size_x_2;
int light_size_y_2;
int cam_state=0;


int start_up_camera(void)
{
	if (ping())
	{
		
		return find_green();
	}
	else
	{
		return 0;
	}
}

int camera_stop(void)
{
	is_tracking = 0;
	Write_Serial_Port_Two('D');
	Write_Serial_Port_Two('T');
	Write_Serial_Port_Two('\r');
	return get_ack();
}

int ping(void)
{
	if (cam_state == 0)
	{
		is_tracking = 0;
		Write_Serial_Port_Two('P');
	  	Write_Serial_Port_Two('G');
	  	Write_Serial_Port_Two('\r');
	}
	else if (cam_state >= 4)
	{
//		printf("%d\r",get_ack());
		cam_state = -1;
	}
	cam_state ++;
	return get_ack();
}




int get_ack(void)
{
  int byte_count;
  int j;
  int k = 0;
//  wait_for_data();
  byte_count = Serial_Port_Two_Byte_Count();
  for(j = 0; j < byte_count; j++)
  {
//	printf("%c",Read_Serial_Port_Two());
    if (Read_Serial_Port_Two() == 'A')
    {
	  k = 1;

    }
  }
  return k;
}

void wait_for_data(void)
{
  int i;

  i = 0;
  while (i<10000)
  {
/*(
	if (Serial_Port_Two_Byte_Count() > 0)
	{
		break;
	}
	else
	{
		i++;
	}
  }
}

int find_green (void)
{
	if (cam_state == 0)
	{
		is_tracking = 0;
		Write_Serial_Port_Two('E');
	  	Write_Serial_Port_Two('T');
	  	Write_Serial_Port_Two('\r');
	}
	else if (cam_state >= 4)
	{
//		printf("%d\r",get_ack());
		is_tracking = get_ack();
		cam_state = -1;
	}
	cam_state ++;
	return is_tracking;
}

void get_camera_data(void)
{
	if(is_tracking)
	{
		while (Serial_Port_Two_Byte_Count()) //will read serial data until eol
		{
			unsigned char current_data = Read_Serial_Port_Two();


			if (current_data == 0x0A)
			{
				packet_count = 0;
			}
			// adding this in for eol
			else if (current_data == 0xFF)
			{
				avg_coordinates(xl,xr,yl,yr,1);
				avg_coordinates(xl_2,xr_2,yl_2,yr_2,2);
				printf("Num of lights = %d  ",num_of_lights);
				printf("X-pos = %d  ",camx);
				printf("Y-pos = %d\r",camy);
				return;
			}
			else
			{
				switch(packet_count)
				{
				case 0:
					num_of_lights = current_data;
				break;
				case 1:
					color_ref = current_data;
				break;
				case 2:
					xl = current_data;
				break;
				case 3:
					yl = current_data;
				break;
				case 4:
					xr = current_data;
					break;
				case 5:
					yr = current_data;
				break;
				case 6:
					color_ref_2 = current_data;
				break;
				case 7:
					xl_2 = current_data;
				break;
				case 8:
					yl_2 = current_data;
				break;
				case 9:
					xr_2 = current_data;
				break;
				case 10:
					yr_2 = current_data;
				break;
				}
			packet_count ++;
			}
		}
	}	
}
		
void avg_coordinates(int cam_xl, int cam_xr, int cam_yl, int cam_yr, int which_light)
{
	if(which_light == 1)
	{
		camx = (cam_xl + cam_xr)/2;
		camy = (cam_yl + cam_yr)/2;
		light_size_x = cam_xr - cam_xl;
		light_size_y = cam_yr - cam_yl;
	}
	else if(which_light == 2)
	{
		camx_2 = (cam_xl + cam_xr)/2;
		camy_2 = (cam_yl + cam_yr)/2;
		light_size_x_2 = cam_xr - cam_xl;
		light_size_y_2 = cam_yr - cam_yl;
	}
}


/*
void write_int_to_serial( int val )
{
  int digit;
  int index;
  index=0;
  digit=val/100;
  digit=digit%10; // This grabs the hundreds place digit
  if(digit>0)    // If it is a zero, we don't need to print it
  {
    Write_Serial_Port_Two(digit+48);
    index++;
  }
  digit=val/10;
  digit=digit%10;    // This grabs the tens place digit
  if(index>0 || digit>0 )  // If the hundreds place was a 0 and this is also
  {					// a 0, skip it, else print the number
    Write_Serial_Port_Two(digit+48);
  }
  digit=val%10;  // Print out the ones place digit no matter what
  Write_Serial_Port_Two(digit+48);
}
*/
