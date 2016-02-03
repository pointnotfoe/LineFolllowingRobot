//motor_control005.c
#include "sumovore.h"
#include "motor_control.h"
#include <delays.h>
	
void spin_left(void);
void turn_left(void);
void straight_fwd(void);
void turn_right(void);
void spin_right(void);
//added this
void Check_Gaps(void);


void motor_control(void)
{
     // Different scenerios to control the motor
     
     if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) straight_fwd();//00100
     else if (SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) spin_left();//10000
   	 else if (SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) spin_left();//11000
     else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) turn_left();//01000
	 else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) turn_left();//01100
     else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right) turn_right();//00010
	 else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right) turn_right();//00110
     else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&SeeLine.b.Right) spin_right();//00001
	 else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&SeeLine.b.CntRight&&SeeLine.b.Right) spin_right();//00011
	 else if ( (SeeLine.B ) == 0b00000u) Check_Gaps();//00000
	 else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&SeeLine.b.Right) right_right_angle_turns();//00111
	 else if (SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) left_right_angle_turns();//11100
	 else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&SeeLine.b.Right) sharp_right_turns();//00101
	 else if (SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) sharp_left_turns();//10100
	 else if (SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right) merge_right();//10010
     else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&SeeLine.b.Right) merge_left();//01001
	 else if (SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right) merge_right();//11010
     else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&SeeLine.b.CntRight&&SeeLine.b.Right) merge_left();//01011
	 else if (SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&SeeLine.b.Right) final_ends();//11111
}

void spin_left(void)	// to spin left
{
  set_motor_speed(left, rev_fast, 0); 
  set_motor_speed(right, fast, 0); // changed from -40 (v 005)
}

void turn_left(void)	// to turn left
{
  set_motor_speed(left, stop, 0); 
  set_motor_speed(right, fast, 0); 
}
void straight_fwd(void)	// to move forward
{
  set_motor_speed(left, fast, 0); 
  set_motor_speed(right, fast, -40); // Was intially 0 not -40
}
void spin_right(void)	// to spin left
{
  set_motor_speed(left, fast, 0); // changed from slow (v 005)
  set_motor_speed(right, rev_fast, 0); 
}
void turn_right(void)	//to turn right
{
  set_motor_speed(left, fast, 0); 
  set_motor_speed(right, stop, 0); 
}


void Check_Gaps(void)	//checks gaps and makes a 180 degree turn if necessary
{

	int sensor_check = 0;
	for(sensor_check; sensor_check < 20; sensor_check++)
		{
			check_sensors();
	
			if ( (SeeLine.B ) == 0b00000u)
				{
					set_motor_speed(left, fast, 0); 
		  			set_motor_speed(right, fast, -40); //Wheels Adjustment
					Delay10KTCYx(20);
					if( sensor_check == 19)
					{
						
						turn_180 ();
						set_motor_speed(left, medium, 0); 
		  				set_motor_speed(right, medium, -40);//Wheels Adjustment
					
					}	
				}
			else 
			{
				sensor_check = 19;
			}
		}
}
