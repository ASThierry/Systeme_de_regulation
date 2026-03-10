#include <stdio.h>
#include <stdlib.h>

#include<unistd.h>

#include "simulateur.h"

#include "consigne.h"
#include "regulation.h"
#include "visualisationC.h"
#include "visualisationT.h"


// Voir le fichier trace.txt pour comprendre la baisse de température
/*
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
		if (consi==5){
            cmd =0;
            exit(0);
        }


        visualisationC(cmd);
        visualisationT(temperature);

        regulationTest(1,consi,tabT,nT);

		usleep(40000);

        
	}

	
	simDestruct(monSimulateur); // destruction de simulateur
	return EXIT_SUCCESS;
}*/
int main() {
    temp_t temperature;
    temperature.exterieure = 10.0; // Selon ta photo
    temperature.interieure = 15.0;

    float tab_temp[30]; // Taille 30 sur la photo
    int nT = 0;

    float consigne_actuelle = 15.0;
    float consigne_precedente = 15.0;

    float cmd = 0;
    struct simParam_s* monSimulateur = simConstruct(temperature);

    while(1) {
        // 1. Calcul et Visualisation
        temperature = simCalc(cmd, monSimulateur);
        visualisationC(cmd);
        visualisationT(temperature);

        // 2. Gestion de la consigne
        consigne_actuelle = consigne(consigne_precedente);

        // Détection de changement de consigne (Reset)
        if (consigne_actuelle != consigne_precedente) {
            for (int i = 0; i < 30; i++) {
                tab_temp[i] = 0;
            }
            nT = 0;
            consigne_precedente = consigne_actuelle;
        }

        // 3. Gestion du tableau (Fenêtre glissante)
        if (nT == 30) {
            // "List full" : on décale tout vers la gauche
            // ATTENTION : i < nT - 1 pour éviter de lire hors du tableau
            for (int i = 0; i < nT - 1; i++) {
                tab_temp[i] = tab_temp[i + 1];
            }
            // On place la nouvelle température à la dernière place disponible (29)
            tab_temp[29] = temperature.interieure;
        } else {
            // Le tableau n'est pas encore plein
            tab_temp[nT] = temperature.interieure;
            nT++;
        }

        // 4. Régulation
        // On utilise l'option 2 pour le PID comme sur ta photo
        cmd = regulationTest(2, consigne_actuelle, tab_temp, nT);

        // printf("Consigne: %.2f | Int: %.2f | Index Tab: %d\n", consigne_actuelle, temperature.interieure, nT);

        usleep(400000); // 400ms selon ta photo
    }

    simDestruct(monSimulateur);
    return EXIT_SUCCESS;
}
    