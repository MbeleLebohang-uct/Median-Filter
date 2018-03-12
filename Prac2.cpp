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

#include "Prac2.h"
#include <iostream>
//------------------------------------------------------------------------------

// This is each thread's "main" function.  It receives a unique ID
void* Thread_Main(void* Parameter){
 int ID = *((int*)Parameter);

 pthread_mutex_lock(&Mutex);
  printf("Hello from thread %d\n", ID);
 pthread_mutex_unlock(&Mutex);

 for(int j = 0; j < 1e6; j++); // Do some heavy calculation

 pthread_mutex_lock(&Mutex);
  printf("Thread %d: I QUIT!\n", ID);
 pthread_mutex_unlock(&Mutex);

 return 0;
}
//------------------------------------------------------------------------------
/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n----------------------------------------------------------------------------\n");
}

//------------------------------------------------------------------------------
/**
 * @brief: Convert the given RGB to Hex equivalent.
 * @return  Int equivalent of the converted Hex number
 */
int getRGB_Integer(unsigned char pR, unsigned char pG, unsigned char pB){
 return (((int)pR & 0xff) << 16) + (((int)pG & 0xff) << 8) + ((int)pB & 0xff);
}
//-----------------------------------------------------------------------------
void swap(int* pX, int* pY){
 int temp = *pX;
 *pX = *pY;
 *pY = temp;
}
//-----------------------------------------------------------------------------
int partition(int* pArray, int pLower_i, int pHigher_i){
 int pivot = pArray[pHigher_i];
 int i = pLower_i - 1;

 for(int j = pLower_i; j < pHigher_i; j++){
   if(pArray[j] < pivot){
     i++;
     swap(&pArray[i], &pArray[j]);
   }
 }
 
 swap(&pArray[i + 1],&pArray[pHigher_i]);
 return (i + 1);
}
//-----------------------------------------------------------------------------
void quickSort(int* pArray, int pLower_i, int pHigher_i){
 if(pLower_i < pHigher_i){
   int partition_index = partition(pArray, pLower_i, pHigher_i);
   
   // Recursively sort items before and after partition index
   quickSort(pArray, pLower_i, partition_index - 1);
   quickSort(pArray, partition_index + 1, pHigher_i);
 }
}
//-----------------------------------------------------------------------------
int main(int argc, char** argv){
  printf("Code is running...");
  tic();
  Input.Read("Data/small.jpg");
  int winSizeX = 9;
  int winSizeY = 9;
  //quickSort(arr, 0, n-1);
  //quickSort(arr, 0, n-1);
  
  if(!Output.Allocate(Input.Width, Input.Height, Input.Components)){ 
    return -2;
  }   
  int* neighborPixels;  

  int x, y, fx, fy, winEdgeX, winEdgeY;
  for(y = 0; y < Input.Height; y++){
    winEdgeY = y - (winSizeY/2);
    if(winEdgeY < 0){
      winEdgeY = 0;
    }

    for(x = 0; x < Input.Width*Input.Components; x+= Input.Components){
      // get all the neighboring pixels and put them in and array of 81 items
      // Window will be shrinked near the boundries
      winEdgeX = x - (((int)(winSizeX/2))*Input.Components);
      if(winEdgeX < 0){
        winEdgeX = 0;
      }

      int diffX = 0;
      int diffY = 0;
      if((winEdgeX + (winSizeX*Input.Components)) > (Input.Width*Input.Components)){
        diffX = (winEdgeX + (winSizeX*Input.Components)) - (Input.Width*Input.Components);
      } 
      if((winEdgeY + winSizeY) > Input.Height){
        diffY = (winEdgeY + winSizeY) - Input.Height;
      }
      int n = (winSizeX - (diffX/Input.Components))*(winSizeY - diffY);
      neighborPixels = new int[n];
      int i = 0;
      for(fy = 0; fy < (winSizeY - diffY); fy++){
	for(fx = 0;fx < ((winSizeX*Input.Components) - diffX); fx+=Input.Components){
	  neighborPixels[i++] = getRGB_Integer(Input.Rows[winEdgeY+fy][winEdgeX+fx+0],Input.Rows[winEdgeY+fy][winEdgeX+fx+1],Input.Rows[winEdgeY+fy][winEdgeX+fx+2]);
        }
      }
      // Sort this list
      std::cout << "Before sorting ---------------" << std::endl;
      printArray(neighborPixels, n);
      quickSort(neighborPixels, 0, n - 1);
      std::cout << "After sorting ---------------" << std::endl;
      printArray(neighborPixels, n); 
      // Save the median of the sorted list to the current pixel
      int median = neighborPixels[(n - 1)/2];
      delete[] neighborPixels;

      // Convert the median back to RGB (3 components
      std::cout << "Size of window ---------------: " << n << std::endl;
      std::cout << "Median ---------------: " << median << std::endl;

      Output.Rows[y][x + 0] = ((median >> 16) & 0xff)/255.0;
      Output.Rows[y][x + 1] = ((median >> 8) & 0xff)/255.0;
      Output.Rows[y][x + 2] = (median & 0xff)/255.0;
      
      std::cout << "-------R--------" << (int)Output.Rows[y][x + 0] <<std::endl;
      std::cout << "-------G--------" << (int)Output.Rows[y][x + 1] <<std::endl;
      std::cout << "-------B--------" << (int)Output.Rows[y][x + 2] <<std::endl;      
      break;
    }
    break;
  }

  printf("Run time is: %lg ms \n", toc()/(1e-3));
  printf("Finish...");

  return 0;
}
//------------------------------------------------------------------------------
