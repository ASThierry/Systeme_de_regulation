#include <stdio.h>
#include <stdlib.h>

#include<unistd.h>

#include "simulateur.h"

#include "consigne.h"
#include "regulation.h"
#include "visualisationC.h"
#include "visualisationT.h"


int main() {
    temp_t temperature; // initialisation de la température
    temperature.exterieure = 14.0; // initialisation de la température extérieure à 14.0°C
    temperature.interieure = 15.0; // initialisation de la température intérieure à 15.0°C

    float cmd = 0; // initialisation de la commande du chauffage à 0%
    struct simParam_s *monSimulateur = simConstruct(temperature); // creation du simulateur, puissance intialisée
    int nT = 50;
    float tabT[50];

    float consi = 10;
    float consi_avant = 10;

    int i = 0;
    int k=0;

    while (1) {
        temperature = simCalc(cmd,monSimulateur); // calcul de la température grâce à la commande en % du chauffage via simCalc

        consi_avant = consi;
        consi = consigne(consi_avant);

        if (consi == 5) {
            cmd=0;
            break;
        }

        if (i < nT - 1) {
            tabT[i] = temperature.interieure;
            i++;
        } else {
        for (int j = 0; j < nT - 1; j++) {
                tabT[j] = tabT[j + 1];
        }
        tabT[nT - 1] = temperature.interieure;
    }

        cmd = regulationTest(2, consi, tabT, nT);

        visualisationC(cmd);
        visualisationT(temperature);

        usleep(40000);
        k++;
        printf("étape: %d; puissance: %f; consigne: %f\n",k,cmd, consi);

    }


    simDestruct(monSimulateur); // destruction de simulateur
    return EXIT_SUCCESS;
}
    