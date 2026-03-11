    #include <stdio.h>
	 #include <stdlib.h>
    #include "regulation.h"
    #include "define.h"

    float regulationToutOuRien(float consigne,float* tabT, int nT){
        if(nT < 1){
            return 0;
        }
        if (consigne > tabT[nT-1]){
            return 50;
        }
        else{
            return 0;
        }
    }

    float regulationPID(float consigne,float* tabT, int nT, float kp, float ki, float kd){
        if (nT < 2)
        {
            return 0;
        }
        //calcul de la différence entre la consigne et la dernière valeur mesurée
        float proportional = consigne - tabT[nT-1];

        //calcul de la partie intégrale
        float integral=0;

        for (int i=0; i < nT-1 ; i++){
            integral += ((consigne - tabT[i]+consigne - tabT[i+1])*DELTAT)/2.0;
        }

        //calcul de la partie dérivée
        float derivative = ((consigne - tabT[nT-1])-(consigne - tabT[nT-2]))/DELTAT;

        //calcul du PID
        float pid= kp * proportional + ki * integral + kd * derivative;

        // conversion en pourcentage 0 - 100%
        float cmd= pid;
        if(cmd < 0.0){
            cmd = 0.0;
        }
        if(cmd>100.0){
            cmd = 100.0;
        }
        return cmd;
    }



    float regulationTest(int regul,float consigne,float* tabT, int nT){
		float cmd=100.0;
        if (regul==1){
            cmd=regulationToutOuRien(consigne, tabT, nT);
        }
        if (regul==2){
            cmd=regulationPID(consigne, tabT, nT,KP,KI,KD);
        }
        
		return cmd;
	}


