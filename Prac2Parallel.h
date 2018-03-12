//==============================================================================
// Copyright (C) John-Philip Taylor
// tyljoh010@myuct.ac.za
//
// This file is part of the EEE4084F Course
//
// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>
//==============================================================================

#ifndef Prac2Parallel_h
#define Prac2Parallel_h
//------------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//------------------------------------------------------------------------------

#include "JPEG.h"
#include "Timer.h"
//------------------------------------------------------------------------------

#define Thread_Count 16
#define winSizeX     9
#define winSizeY     9
//------------------------------------------------------------------------------

// Input and output buffers
JPEG Input;
JPEG Output;
// Struct with thread parameters
struct params {
	int ID;
	int start_i;
	int end_i;
};
//------------------------------------------------------------------------------

pthread_mutex_t Mutex; // General-purpose MutEx
//------------------------------------------------------------------------------

// The thread "main" function.  Receives a unique thread ID as parameter
void* Thread_Main(void* Parameter);
void  printArray(int arr[], int size);
int   getRGB_Integer(unsigned char pR, unsigned char pG, unsigned char pB);
void  quickSort(int* pArray, int pLower_i, int pHigher_i);
int   partition(int* pArray, int pLower_i, int pHigher_i);
void  swap(int* pX, int* pY);
//------------------------------------------------------------------------------

#endif
//------------------------------------------------------------------------------
