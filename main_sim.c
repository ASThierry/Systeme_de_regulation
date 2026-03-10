#include <stdio.h>
#include <stdlib.h>

#include<unistd.h>

#include "simulateur.h"

#include "consigne.h"
#include "regulation.h"
#include "visualisationC.h"
#include "visualisationT.h"


// Voir le fichier trace.txt pour comprendre la baisse de température

int main(){

	temp_t temperature; // initialisation de la température
	temperature.exterieure = 14.0; // initialisation de la température extérieure à 14.0°C
	temperature.interieure = 15.0; // initialisation de la température intérieure à 15.0°C

    float cmd = 0; // initialisation de la commande du chauffage à 0%
	struct simParam_s*  monSimulateur = simConstruct(temperature); // creation du simulateur, puissance intialisée
    int nT = 50;
    float tabT[nT];

    float consi= 40;
    float consi_avant= 40;

    int i=0;

	while(1){
        temperature = simCalc(cmd,monSimulateur); // calcul de la température grâce à la commande en % du chauffage via simCalc

        consi_avant= consi;
        consi= consigne(consi_avant);

        if (i<nT){
            tabT[i]= temperature.interieure;
            i++;
        }
        else{
            for (i=0; i<nT-1; i++){
                tabT[i]= tabT[i+1];
            }
            tabT[i]= temperature.interieure;
        }


        visualisationC(cmd);
        visualisationT(temperature);

        regulationTest(1,consi,tabT,nT);

		usleep(40000);

        if (consi==5){
            break;
        }
	}

	cmd=0;
	simDestruct(monSimulateur); // destruction de simulateur
	return EXIT_SUCCESS;
}