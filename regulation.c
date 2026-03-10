    #include <stdio.h>
	 #include <stdlib.h>
    #include "regulation.h"

    float regulationToutOuRien(float consigne,float* tabT, int nT){
        if (consigne > tabT[nT-1]){
            return 50;
        }
        else{
            return 0;
        }
    }

    float regulationPID(float consigne,float* tabT, int nT, float kp, float ki, float kd){

        //calcul de la différence entre la consigne et la dernière valeur mesurée
        float proportional = tabT[nT-1]-consigne;

        //calcul de la partie intégrale

        float integral=0;

        for (int i=0; i < nT-2 ; i++){
            integral += (((tabT[i]-consigne)+(tabT[i+1]-consigne))*100)/2;
        }

        //calcul de la partie dérivée
        float derivative = integral/((nT-1)*100);

        //calcul du PID
        float pid= kp * proportional + ki * integral + kd * derivative;

        // conversion en pourcentage

        float cmd= pid*100/(40);
        return cmd;
    }



    float regulationTest(int regul,float consigne,float* tabT, int nT){
		float cmd=100.0;
        if (regul==1){
            cmd=regulationToutOuRien(consigne, tabT, nT);
        }
        else {
            if (regul==2){
                cmd=regulationPID(consigne, tabT, nT,1.1,0.2,0.15);
            }
        }
		return cmd;
	}


