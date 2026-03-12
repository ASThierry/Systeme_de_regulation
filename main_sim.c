#include <stdio.h>
#include <stdlib.h>

#include<unistd.h>

#include "simulateur.h"
#include "regulation.h"
#include "consigne.h"
#include "visualisationC.h"
#include "visualisationT.h"


int main() {
    temp_t temperature; // initialisation de la température
    temperature.exterieure = 14.0; // initialisation de la température extérieure à 14.0°C
    temperature.interieure = 15.0; // initialisation de la température intérieure à 15.0°C

    float cmd = 0; // initialisation de la commande du chauffage à 0%
    struct simParam_s *monSimulateur = simConstruct(temperature); // creation du simulateur, puissance intialisée

    //initialise le tableau qui stocke les températures et une variable qui représente sa longueur
    int nT = 50;
    float tabT[50];

    //initialise la consigne et sa valeur précédente
    float consi = 10;
    float consi_avant = 10;

    //cet index permet de déterminer le taux de remplissage du tableau afin de déterminer quand le décalage doit commencer
    int i = 0;
    int k=0;

    while (1) {
        temperature = simCalc(cmd,monSimulateur); // calcul de la température grâce à la commande en % du chauffage via simCalc


        //mets à jour la consigne dans consigne.txt en gardant trace de la consigne précédente
        consi_avant = consi;
        consi = consigne(consi_avant);


        //arrête le programme quand la consigne est 5
        if (consi == 5) {
            cmd=0;
            break;
        }

        //remplis le tableau de températures
        if (i < nT - 1) {
            tabT[i] = temperature.interieure;
            i++;
        }
        //le tableau est plein, les valeurs sont donc décalées vers la gauche
        else {
        for (int j = 0; j < nT - 1; j++) {
                tabT[j] = tabT[j + 1];
        }
        tabT[nT - 1] = temperature.interieure;
    }
        //effectue la régulation de la puissance avec la méthode de Ziegler-Nichols
        cmd = regulationPID(consi,tabT,nT,0.6*1000,2/3*DELTAT,0.125*(3*DELTAT));

        //écrit les températures et le témions dans data.txt
        visualisationC(cmd);
        visualisationT(temperature);

        usleep(40000);
        k++;
        printf("étape: %d; puissance: %f; consigne: %f\n",k,cmd, consi);

    }


    simDestruct(monSimulateur); // destruction de simulateur
    return EXIT_SUCCESS;
}
    