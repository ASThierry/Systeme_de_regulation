    #include <stdio.h>
	#include <stdlib.h>
	#include "define.h" 
    #define KP 0.1
    #define KI 1.1
    #define KD 0.15
    #define DELTAT 10
    
   float regulationTest(int regul,float consigne,float* tabT, int nT);
