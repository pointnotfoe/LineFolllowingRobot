//motor_control001.c
#include "sumovore.h"
#include "motor_control.h"
#include <delays.h>

void spin_left(void);
void turn_left(void);
void straight_fwd_fast(void);
void straight_fwd_medium(void);
void straight_bk_fast(void);
void straight_bk_medium(void);
void turn_right(void);
void spin_right(void);
void spin_around(void);
void spin_one_place(void);
void spin_large_circle(void);

void motor_control(void)
{
	 spin_around();
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds

	 spin_one_place();
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds

	 spin_large_circle();	 
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 Delay10KTCYx(200); // Wait 0.250 seconds
	 

	 
    /*// very simple motor control
    if ( SeeLine.b.Center ) straight_fwd_fast();
     else if (SeeLine.b.Left) spin_left();
     else if (SeeLine.b.CntLeft) turn_left();
     else if (SeeLine.b.CntRight) turn_right();
     else if (SeeLine.b.Right) spin_right();

     if ( (SeeLine.B ) == 0b00000u) motors_brake_all();*/
}


void spin_left(void)
{
  set_motor_speed(left, rev_fast, 0); 
  set_motor_speed(right, fast, 0); 
}

void turn_left(void)
{
  set_motor_speed(left, stop, 0); 
  set_motor_speed(right, fast, 0); 
}
void straight_fwd_fast(void)
{
  set_motor_speed(left, fast, 0); 
  set_motor_speed(right, fast, -40); 
}
void spin_right(void)
{
  set_motor_speed(left, fast, 0); 
  set_motor_speed(right, rev_fast, 0); 
}
void turn_right(void)
{
  set_motor_speed(left, fast, 0); 
  set_motor_speed(right, stop, 0); 
}
void straight_fwd_medium(void)
{
  set_motor_speed(left, medium, 0); 
  set_motor_speed(right, medium, 0); 
}
void straight_bk_fast(void)
{
  set_motor_speed(left, rev_fast, 0); 
  set_motor_speed(right, rev_fast, 0); 
}
void straight_bk_medium(void)
{
  set_motor_speed(left, rev_medium, 0); 
  set_motor_speed(right, rev_medium, 0); 
}
void spin_around(void)
{
  set_motor_speed(left, stop, 0); 
  set_motor_speed(right, fast, 0); 
}
void spin_one_place(void)
{
  set_motor_speed(left, rev_fast, 0); 
  set_motor_speed(right, fast, 0); 
}
void spin_large_circle(void)
{
  set_motor_speed(left, slow, 0); 
  set_motor_speed(right, fast, 0); 
}

