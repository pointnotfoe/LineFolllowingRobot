//motor_control008.c		//name and version of the code

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


//added these
void merge_right(void);		//merges to a track on the robot's right.
void merge_left(void);		//merges to a track on the robot's left.


void motor_control(void)	//Different scenerios that will light up the LEDs in a certain way,
							//and the motor reactions to the scenarios.
{     
	if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) straight_fwd();	//00100
	else if (SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) spin_left();	//10000
	else if (SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) spin_left();	//11000
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) turn_left();	//01000
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) turn_left();	//01100
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right) turn_right();//00010
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right) turn_right();	//00110
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&SeeLine.b.Right) spin_right();//00001
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&SeeLine.b.CntRight&&SeeLine.b.Right) spin_right();	//00011
	else if ( (SeeLine.B ) == 0b00000u) Check_Gaps();	//00000	//all LEDs OFF
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&SeeLine.b.Right) right_right_angle_turns();	//00111
	else if (SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) left_right_angle_turns();	//11100
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&SeeLine.b.Right) sharp_right_turns();		//00101
	else if (SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) sharp_left_turns();		//10100
	else if (SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right) merge_right();			//10010
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&SeeLine.b.Right) merge_left();				//01001
	else if (SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right) merge_right();				//11010
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&SeeLine.b.CntRight&&SeeLine.b.Right) merge_left();				//01011
	else if (SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&SeeLine.b.Right) final_ends();				//11111	//all LEDs ON
}

void spin_left(void)	// to spin left
{
  set_motor_speed(left, rev_fast, 0);	//left wheel goes reverse		//wheels move in opposite direction	
  set_motor_speed(right, fast, 0);		//right wheel goes straight		//to spin the robot right on center axis.
}

void turn_left(void)	// to turn left
{
  set_motor_speed(left, medium, 0);		//left wheel medium down (for prev. versions, left wheel stops.)
  set_motor_speed(right, fast, 0);		//right wheel maintains fast speed
}
void straight_fwd(void)	// to move forward
{
  set_motor_speed(left, fast, 0);		// both left wheel and		//-40 for motor adjustment to match
  set_motor_speed(right, fast, -40);	// right wheel moves fast	//speed of both wheels 
}
void spin_right(void)	// to spin left
{
  set_motor_speed(left, fast, 0);		//left wheel goes straight		//wheels move in opposite direction	
  set_motor_speed(right, rev_fast, 0);	//right wheels goes reverse		//to spin the robot left on center axis	
}
void turn_right(void)	//to turn right
{
  set_motor_speed(left, fast, 0);		//left wheel maintains fast speed
  set_motor_speed(right, medium, 0);		//right wheels medium down (for prev. versions, right wheel stops.)
}



//************* CHECK GAPS *************//

void Check_Gaps(void)	//checks gaps and makes a 180 degree turn after going about 8cm (needs to be exact.)
{
	int sensor_check = 0;									//variable sensor check
	for(sensor_check; sensor_check < 10; sensor_check++)	//executes 20 times, looking for gaps in each count.
		{
			check_sensors();				//constantly keeps checking for LED combinations
			if ( (SeeLine.B ) == 0b00000u)	//all LEDs OFF
			{
				straight_fwd();			//go straight
				Delay10KTCYx(20);		//0.025s OR 25ms.
				if( sensor_check == 9)	//last condition 
				{
					turn_180 ();
					straight_fwd();
				}	
			}
			else 
			{
				sensor_check = 9;
			}
		}
}

//*****************RIGHT RIGHT ANGLE TURN********************//

void right_right_angle_turns(void)			//right right angle turns, if-else cases cover sharp turns as well
{	
    straight_fwd();
	Delay10KTCYx(25);						//0.03125s
	check_sensors();						//constantly keeps checking to see LED combinations.		
	if ( (SeeLine.B ) == 0b00000u) 			//all LEDs OFF.
	{
		while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //while all off; 00000
		{   
			spin_right();		//spins the robot right.
			check_sensors();	//constantly keeps checking to see LED combinations.						
		}
	}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right) //00010
	{       
		straight_fwd();					//go straight
		Delay10KTCYx(25);				//0.03125s
		check_sensors();
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
				{		
					spin_right(); 		//spins the robot right.
					check_sensors();	//constantly keeps checking to see LED combinations.							
				}
		}
	}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right) //01110
	{		
		straight_fwd(); 	//Go straight.
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations.
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
			{       
            	spin_right(); 		//Rotates Right
				check_sensors();	//constantly keeps checking to see LED combinations.						
			}
		}
	}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00100
	{		
		straight_fwd();		//Go straight.
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//contantly keeps checking to see LED combinations.
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
			{  				
				spin_right();		//spins right
				check_sensors();	//constantly keeps checking to see LED combinations.				
			}
		}
	}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right) //00110
	{		
		straight_fwd();		//Go straight.
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations.
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
			{   		
				spin_right();		//Rotates right.
				check_sensors();	//constantly keeps checking to see LED combinations.			
			}
		}
	}
	else;
}



//*************************LEFT RIGHT ANGLE TURN*****************************//



void left_right_angle_turns(void) //left right angle turns, if else cases cover sharp turns aswell
{   
	straight_fwd();					//go straight
	Delay10KTCYx(25);				//0.03125s
	check_sensors();				//constantly keeps checking to see LED combinations.
	if ( (SeeLine.B ) == 0b00000u)	//all LEDS OFF
	{
		while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
			{
				spin_left(); 		//spins left (was spin right in v004)
				check_sensors();	//constantly keeps checking to see LED combinations.						
			}
	}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//01000
	{
		straight_fwd();
		Delay10KTCYx(25);			//0.03125s
		check_sensors();
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
				{
					spin_left();		//spins left (was spin right in v004).
					check_sensors();	//constantly keeps checking to see LED combinations.						
				}
		}
	}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right)//01110
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations.
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
			{
				while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
				{
					spin_left(); 		//spins left (was spin right in v004).
					check_sensors();	//constantly keeps checking to see LED combinations.						
				}
			}
	}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00100
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s			
		check_sensors();	//constantly keeps checking to see LED combinations.
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
			{			
				while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
				{
					spin_left(); 		//spins left (was spin right in v004).
					check_sensors();	//constantly keeps checking to see LED combinations.													}
				}
	}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//01100
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);						//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations.
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
			{
				while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
				{
					spin_left();		//spins left (was spins right in v004);
					check_sensors();	//constantly keeps checking to see LED combinations.							
				}
			}
	}
	else;
	}
}


//***************************SHARP RIGHT TURN******************//



void sharp_right_turns(void) //sharp right turns
{
	straight_fwd();		//go straight
	Delay10KTCYx(25);	//0.03125s
	check_sensors();	//constantly keeps checking to see LED combinations
	if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
	{
		while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000 sees nothing
			{
				spin_right();		//spins right
				check_sensors();	//constantly keeps checking to see LED combinations			
			}
	}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&SeeLine.b.Right) //00101
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations.
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
			{
				spin_right();		//spins right
				check_sensors();	//constantly keeps checking to see LED combinations.			
			}
		}
	}
//THIS WAS ADDED IN v008
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&SeeLine.b.Right)//00111
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
				{
					spin_right();		//spins right
					check_sensors();	//constantly keeps checking to see LED combinations
				}
		}
	}
//FUNCTION STOPS HERE
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&SeeLine.b.CntRight&&SeeLine.b.Right) //00011
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right) //00000
			{
				spin_right();		//spins right
				check_sensors();	//constantly keeps checking to see LED combinations			
			}
		}
	}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right)//00010
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
			{
				spin_right();		//spins right
				check_sensors();	//constantly keeps checking to see LED combinations.			
			}
		}
	}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right)//01110
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations.
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
			{
				spin_right();		//spins right
				check_sensors();	//constantly keeps checking to see LED combinations			
			}
		}
	}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00100
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
				{
					spin_right();		//spins right
					check_sensors();	//constantly keeps checking to see LED combinations			
				}
		}
	}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//01100
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
			{
				spin_right();		//spins right
				check_sensors();	//constanlty keeps checking to see LED combinations			
			}
		}
	}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right)//00110
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations.
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
			{
				spin_right();		//spins right
				check_sensors();	//constantly keeps checking to see LED combinations.			
			}
		}
	}
	else;
}

//**********************SHARP LEFT TURNS*********************//

void sharp_left_turns(void)	//sharp left turns
{
	straight_fwd();		//go straight
	Delay10KTCYx(25);	//0.03125s
	check_sensors();	//constantly keeps checking to see LED combinations
	if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
	{
		while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
		{
			spin_left();		//spins left (was spin right in v004)
			check_sensors();	//constantly keeps checking to see LED combinations
		}
	}
	else if (SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//10100
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
			{
				spin_left();		//spins left (was spin right in v004);
				check_sensors();	//constantly keeps checking to see LED combinations						
			}
		}
	}
//WE ADDED THIS LINE TO SEE IF IT MAKES A DIFFERENCE (ADDED IN v008)
		else if (SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//11100
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
				{
					spin_left();		//spins left (was spin right in v004)
					check_sensors();	//constantly keeps checking to see LED combinations
				}
		}
	}
//THIS LINE FUNCTION ENDS HERE
	else if (SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//11000
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
			{
				spin_left();		//spins left (was spin right in v004);
				check_sensors();	//constantly keeps checking to see LED combinations
			}
		}
	}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//01000
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
				{
					spin_left();		//spins left (was spin right in v004)
					check_sensors();	//constantly keeps checking to see LED combinations
				}
		}
	}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right)//01110
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
			{
				while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
				{
					spin_left();		//spins left (was spin right in v004)
					check_sensors();	//constantly keeps checking to see LED combinations
				}
			}
	}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00100
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
				{
					spin_left();		//spins left (was spin right in v004)
					check_sensors();	//constantly keeps checking to see LED combinations
				}
		}
	}
	else if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&SeeLine.b.Center&&SeeLine.b.CntRight&&!SeeLine.b.Right)//00110
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
		{
			while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
				{
					spin_left();		//spins left (was spin right in v004)	
					check_sensors();	//constantly keeps checking to see LED combinations
				}
		}
	}
	else if (!SeeLine.b.Left&&SeeLine.b.CntLeft&&SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//01100
	{
		straight_fwd();		//go straight
		Delay10KTCYx(25);	//0.03125s
		check_sensors();	//constantly keeps checking to see LED combinations
		if (!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//00000
			{
				while(!SeeLine.b.Left&&!SeeLine.b.CntLeft&&!SeeLine.b.Center&&!SeeLine.b.CntRight&&!SeeLine.b.Right)//0000
				{
					spin_left();		//spins left (was spin right in v004)
					check_sensors();	//constantly keeps checking to see LED combinations.
				}
			}
	}
	else;
}


void merge_right(void)	//not merging left <--------- don't know what this is supposed to be
{
  set_motor_speed(left, fast, 0);	//NOTE:: this is the same as turn right in v004
  set_motor_speed(right, stop, 0); 	//NOTE:: this is the same as turn right in v004
}

void merge_left(void)	//not merging right <-------- don't know what this is supposed to be
{
  set_motor_speed(left, stop, 0);	//NOTE:: this is the same as turn left
  set_motor_speed(right, fast, -40);//NOTE:: this is the same as turn left (also, -40 for motor adjustment)
}
