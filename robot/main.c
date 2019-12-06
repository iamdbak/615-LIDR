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
#include "gpio.h"

#define LINE_L   24  
#define LINE_R   27  

#define WHEEL_L  17  
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
	/*GPIOExport(LINE_L);
	GPIOExport(LINE_R);
	GPIOExport(WHEEL_L);
	GPIOExport(WHEEL_R);
	GPIOExport(FORWARD_PIN);
	GPIOExport(REVERSE_PIN);
	usleep(1000*1000);
	GPIODirection(LINE_L, IN);
	GPIODirection(LINE_R, IN);
	GPIODirection(WHEEL_L, OUT);
	GPIODirection(WHEEL_R, OUT);
	GPIODirection(FORWARD_PIN, OUT);
	GPIODirection(REVERSE_PIN, OUT);*/
	wiringPiSetup();
	
	pinMode(LINE_L, INPUT);
	pinMode(LINE_R, INPUT);
	
}

void shutdown()
{
	GPIOUnexport(LINE_L);
	GPIOUnexport(LINE_R);
	halt();
	GPIOUnexport(WHEEL_L);
	GPIOUnexport(WHEEL_R);
}



void move(int speed)
{
	GPIOWrite(WHEEL_L, speed);
	GPIOWrite(WHEEL_R, speed);
}

void forward()
{
	GPIOWrite(FORWARD_PIN, FORWARD);
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
