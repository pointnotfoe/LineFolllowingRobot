//motor_control011.c 
//Medium Speed, also took out the interruption function and added turn 180
#include "sumovore.h"
#include "motor_control.h"
#include <delays.h>
	
void spin_left(void);
void turn_left(void);
void straight_fwd(void);
void turn_right(void);
void spin_right(void);
void Check_Gaps(void);
void right_right_angle_turns(void);
void left_right_angle_turns(void);
void sharp_right_turns(void);
void sharp_left_turns(void);
void merge_right(void);
void merge_left(void);
void final_ends(void);
//added this
void turn_180 (void);


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
  set_motor_speed(left, rev_medium, 0); 
  set_motor_speed(right, medium, 0); // changed from -40 (v 005)
}

void turn_left(void)	// to turn left
{
  set_motor_speed(left, stop, 40); 
  set_motor_speed(right, medium, 0);
  

}
void straight_fwd(void)	// Go forward
{
  set_motor_speed(left, medium, -40); 
  set_motor_speed(right, medium, 20); // Was intially 0 not -40
}
void spin_right(void)	// to spin left
{
  set_motor_speed(left, medium, 0); // changed from slow (v 005)
  set_motor_speed(right, rev_medium, 0); 
}
void turn_right(void)	//to turn right
{
  set_motor_speed(left, medium, 0); 
  set_motor_speed(right, stop, 40); 
}

void merge_right(void) // not merging left
{
  set_motor_speed(left, medium, 0); 
  set_motor_speed(right, stop, 0); 	
}

void merge_left(void) // not merging right
{
  set_motor_speed(left, stop, 0); 
  set_motor_speed(right, medium, -40); 	
}



void final_ends(void) // final endings
{
	straight_fwd();	// Go forward
	Delay10KTCYx(150); //0.1875s
	check_sensors();
	while(SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&SeeLine.b.Right)
	{
	motors_brake_all();	
	check_sensors();
	}
}




void Check_Gaps(void)	//checks gaps and makes a 180 degree turn if necessary
{

	int sensor_check = 0;
	for(sensor_check; sensor_check < 20; sensor_check++)
		{
			check_sensors();
	
			if ( (SeeLine.B ) == 0b00000u)
				{
					straight_fwd();
					Delay10KTCYx(20);
					if( sensor_check == 19)
					{
						
						turn_180 ();
						straight_fwd();
					
					}	
				}
			else 
			{
				sensor_check = 19;
			}
		}
}

void right_right_angle_turns(void)	// right right angle turns, if else cases cover sharp turns as well
{   // Go straight
    straight_fwd();	// Go forward
	Delay10KTCYx(130);//0.1625s
	check_sensors();
	if ( (SeeLine.B ) == 0b00000u)
	{
	while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
					{   //Rotates Right
						
						spin_right();
						check_sensors();							
					}
	}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right) //00010
		{       
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
					{
					
					   while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
							{		//Rotates Right
									
									spin_right();
									check_sensors();							
							}
					}
		}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right) //01110
		{		//Go Straight
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
					{
					
						while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
							{       // Rotates Right
									
                                    spin_right();
									check_sensors();							
							}
					}
		}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00100
		{		//Go Straight
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
					{
					
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
								{   //Rotates Right
									
									spin_right();
									check_sensors();							
								}
					}
		}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right) //00110
		{		//Go Striaght
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
					{
					
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
								{   //Rotates Right
									
									spin_right();
									check_sensors();							
								}
					}
		}
	else;
		
}

void left_right_angle_turns(void) //left right angle turns, if else cases cover sharp turns aswell
{   
	straight_fwd();	// Go forward
	Delay10KTCYx(130);
	check_sensors();
	if ( (SeeLine.B ) == 0b00000u)
	{
	while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
					{
						
						spin_left(); //Changed from spin_right (v 005)
						check_sensors();							
					}
	}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//01000
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
					{
			
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
								{
									spin_left(); //Changed from spin_right (v 005)
									check_sensors();							
								}
					}
		}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right)//01110
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
					{
			
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
								{
									spin_left(); //Changed from spin_right (v 005)
									check_sensors();							
								}
					}
		}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00100
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
			
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
					{
			
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
								{
									spin_left(); //Changed from spin_right (v 005)
									check_sensors();							
								}
					}
		}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//01100
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
			
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
					{
			
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
								{
									spin_left(); //Changed from spin_right (v 005)
									check_sensors();							
								}
					}
		}
	else;
}

void sharp_right_turns(void) //sharp right turns
{
	
	straight_fwd();	// Go forward
	Delay10KTCYx(130);	
	check_sensors();
	if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
		{
			
					while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000 sees nothing
					{//spin right
						spin_right();
						check_sensors();							
					}
		}

	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&SeeLine.b.Right) //00101
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
					{
			
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
								{
									spin_right();
									check_sensors();							
								}
					}
		}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&SeeLine.b.CntRight&&SeeLine.b.Right) //00011
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
					{
			
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
								{
									spin_right();
									check_sensors();							
								}
					}
		}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right)//00010
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
					{
			
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
								{
									spin_right();
									check_sensors();							
								}
					}
		}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right)//01110
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
					{
			
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
								{
									spin_right();
									check_sensors();							
								}
					}
		}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00100
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
			
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
					{
			
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
								{
									spin_right();
									check_sensors();							
								}
					}
		}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//01100
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
					{
			
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
								{
									spin_right();
									check_sensors();							
								}
					}
		}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right)//00110
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
					{
			
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
								{
									spin_right();
									check_sensors();							
								}
					}
		}
	else;
}

void sharp_left_turns(void)	//sharp left turns
{
	straight_fwd();	// Go forward
	Delay10KTCYx(130);	
	check_sensors();
	if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
				{
					spin_left(); //changed from spin_right (v 005)
					check_sensors();
				}
		}

	else if (SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//10100
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
					{
					
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
								{
									spin_left(); //Changed from spin_right (v 005)
									check_sensors();							
								}
					}
		}
	else if (SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//11000
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
					{
					
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
								{
									spin_left(); //Changed from spin_right (v 005)
									check_sensors();							
								}
					}
		}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//01000
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
					{
					
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
								{
									spin_left(); //Changed from spin_right (v 005)
									check_sensors();							
								}
					}
		}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right)//01110
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
					{
					
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
								{
									spin_left(); //Changed from spin_right (v 005)
									check_sensors();							
								}
					}
		}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00100
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
					{
					
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
								{
									spin_left(); //Changed from spin_right (v 005)
									check_sensors();							
								}
					}
		}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right)//00110
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
					{
					
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
								{
									spin_left(); //Changed from spin_right (v 005)	
									check_sensors();							
								}
					}
		}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//01100
		{
				straight_fwd();	// Go forward
				Delay10KTCYx(130);
				check_sensors();
				if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
					{
					
							while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//0000
								{
									spin_left(); //Changed from spin_right (v 005)
									check_sensors();							
								}
					}
		}
	else;



void turn_180 (void)
{
	spin_right();
	Delay10KTCYx(200); //0.250s
	Delay10KTCYx(120); //0.250s
}