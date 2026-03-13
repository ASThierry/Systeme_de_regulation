    #include <stdio.h>
	#include <stdlib.h>
	#include "define.h"

    //les macros ont été calculées par la méthode de Zieglers-Nichols
    #define KP 600 //0.6*Ku, Ku étant la valeur de Kp pour laquelle la courbe commence à osciller
    #define KI 0.67 //2/f0 f0 = 3*DELTAT, la fréquence de l'oscillation obtenue
    #define KD 3.75 //0.125*f0
    #define DELTAT 10
    
    float regulationTest(int regul,float consigne,float* tabT, int nT);

    float regulationPID(float consigne,float* tabT, int nT, float kp, float ki, float kd);

    float regulationToutOuRien(float consigne,float* tabT, int nT);
