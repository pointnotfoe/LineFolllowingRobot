//motor_control013.c //Fast Speed
//We will need to reduce the delay for almost every function.
//Reduce by the same factor by which speed increased.
//Don't know if threshold is linear to speed.

#include "sumovore.h"		//header which has preset functions for LED and Sumobot in general
#include "motor_control.h"	//header containing motor functions.
#include <delays.h>			//to implement delays in the function.
	
void spin_left(void);		//spins the robot left on center axis.
void turn_left(void);		//turns the robot left.
void straight_fwd(void);	//makes the robot go straight.
void turn_right(void);		//turns the robot right
void spin_right(void);		//spins the robot left on center axis.
void Check_Gaps(void);		//check for gaps in the track.
void right_right_angle_turns(void);		//turns the robot right by 90 degrees.
void left_right_angle_turns(void);		//turns the robot left by 90 degrees.
void sharp_right_turns(void);			//for sharp right turns (the angle is less than 90 degrees.)
void sharp_left_turns(void);			//for sharp left turns (the angle is less than 90 degrees.)
void merge_right(void);		//merges to a track on the robot's right.
void merge_left(void);		//merges to a track on the robot's left.

void final_ends(void);// to stop it

void turn_180 (void);//turn around
void ignore_edges (void);//ignores extreme led's for sometime

void motor_control(void)
{
     // Different scenerios to control the motor
     
     if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) straight_fwd();//00100
     
	 //else if (SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) spin_left();//10000
	 else if (SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) ignore_edges();//10000
   	 
	 else if (SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) spin_left();//11000
     else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) turn_left();//01000
	 else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) turn_left();//01100
     else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right) turn_right();//00010
	 else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right) turn_right();//00110
    
     //else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&SeeLine.b.Right) spin_right();//00001
	 else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&SeeLine.b.Right) ignore_edges();//00001

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
  set_motor_speed(left, medium, 0); 
  set_motor_speed(right, fast, 0);
  

}
void straight_fwd(void)	// Go forward
{
  set_motor_speed(left, fast,  0); 
  set_motor_speed(right, fast, -20); // Was intially 0 not -40
}
void spin_right(void)	// to spin left
{
  set_motor_speed(left, fast, 0); // changed from slow (v 005)
  set_motor_speed(right, rev_fast, 0); 
}
void turn_right(void)	//to turn right
{
  set_motor_speed(left, fast, 0); 
  set_motor_speed(right, medium, 40); 
}

void merge_right(void) // not merging left
{
  set_motor_speed(left, fast, 0); 
  set_motor_speed(right, stop, 0); 	
}

void merge_left(void) // not merging right
{
  set_motor_speed(left, stop, 0); 
  set_motor_speed(right, fast, -40); 	
}

void turn_180 (void) //need to reduce the delay for this
{
	spin_right();
	Delay10KTCYx(200); //0.250s
	Delay10KTCYx(120); //0.250s
	Delay10KTCYx(40); //0.250s
}

void ignore_edges (void)
{
	Delay10KTCYx(60); //was 120 
}

void final_ends(void) // final endings
{
	straight_fwd();	// Go forward
	Delay10KTCYx(35); //0.1875s was 150
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
	Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
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
	Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
			
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
				Delay10KTCYx(65);//0.1625s was 130
			
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
	Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
			
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
				Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
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
	Delay10KTCYx(65);//0.1625s was 130	
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
				Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
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
				Delay10KTCYx(65);//0.1625s was 130
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




			
			
}
	
