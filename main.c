/*
 *  CSC-615 FA19 Unix Programming - Assignment #4
 * 
 * Application: IR Sensor - Clean Exit
 * 
 * Author: Stephen Sams
 * Student ID: 918135613
 * Due Date: 11/21/2019
 * Source File: ir_reader.c
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wiringPi.h>
#include <softPwm.h>


#define LINE_L  24  
#define LINE_R  27 
#define LINE_C	25 

#define WHEEL_L_R  2
#define WHEEL_L_F  3
#define WHEEL_L_PWM  0

#define WHEEL_R_F  5
#define WHEEL_R_R  4
#define WHEEL_R_PWM  6
  
#define WHEEL_R  20  

#define FORWARD_PIN 15
#define REVERSE_PIN 13

#define FORWARD 100
#define STOP  0
#define BACKWARD -100

typedef void (*sighandler_t)(int);

void halt();
void shutdown();


void sig_handler(int sig_num)
{
	if(sig_num == SIGINT)
	{
		printf("\n Shutting Down %d\n", sig_num);
	}
	shutdown();
	exit(sig_num);
}

void startup()
{

	wiringPiSetup();
	
	pinMode(LINE_L, INPUT);
	pinMode(LINE_R, INPUT);
	pinMode(LINE_C, INPUT);
	
	pinMode(WHEEL_L_F, OUTPUT);
	pinMode(WHEEL_L_R, OUTPUT);
	int x = softPwmCreate(WHEEL_L_PWM, 0, 100);
	
	pinMode(WHEEL_R_F, OUTPUT);
	pinMode(WHEEL_R_R, OUTPUT);
	int y = softPwmCreate(WHEEL_R_PWM, 0, 100);
     printf("PWM Create: Left Result %d; Right Result %d\n",x,y);
	
}

void shutdown()
{
	digitalWrite(WHEEL_L_F, 0);
	digitalWrite(WHEEL_L_R, 0);
	digitalWrite(WHEEL_L_PWM, 0);
	
	digitalWrite(WHEEL_R_F, 0);
	digitalWrite(WHEEL_R_R, 0);
	digitalWrite(WHEEL_R_PWM, 0);

}



void move(int speed)
{

}

void forward()
{

}

void halt()
{
	move(STOP);
}

void backward()
{
	move(BACKWARD);
}



int main(int argc, char *argv[])
{
	signal(SIGINT, sig_handler);
	//Enable GPIO pins	
	startup();
	digitalWrite(WHEEL_L_F, HIGH);
	digitalWrite(WHEEL_L_R, LOW);
	softPwmWrite(WHEEL_L_PWM, 35);
	
	digitalWrite(WHEEL_R_F, HIGH);
	digitalWrite(WHEEL_R_R, LOW);
	softPwmWrite(WHEEL_R_PWM, 38);
	
	//Loop
	for(;;)
	{
		printf("LINE_L: %d\t", digitalRead(LINE_L));
		printf("LINE_R: %d\n", digitalRead(LINE_R));
		
		forward();
		usleep(1000*1000);
	}
		
	return(0);
}
