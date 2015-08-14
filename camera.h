/*#ifndef __camera_h_
#define __camera_h_
//typedef struct {
//	int x,y;
//	int x1,y1,x2,y2;
//	int size,conf;
//}cam_type;

//extern cam_type cam;

int start_up_camera(void);
int ping(void);
int get_ack(void);
int camera_stop(void);
void wait_for_data(void);
//void write_int_to_serial(int val );
int find_green (void);
void get_camera_data(void);
void avg_coordinates(int cam_xl, int cam_xr, int cam_yl, int cam_yr, int which_light); 


#endif
