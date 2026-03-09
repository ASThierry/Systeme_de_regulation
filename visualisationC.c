#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "visualisationC.h"

void visualisationC(float puissance_f){
    FILE * verrouData;
    FILE * data;
    char ligne[25];
    float text=0.0;
    float tint=0.0;
    verrouData = fopen(".verrouData","r");
    
    if (verrouData != NULL){// Présence du verrou
        fclose(verrouData);
        return;
    }
    // Création d'un vérrou
    verrouData = fopen(".verrouData","w");
    fclose( verrouData );
    data = fopen("data.txt","r");
      if (data !=NULL)
      {
        // On récupéré les donnée dans le fichier data.
        fgets(ligne,sizeof(ligne),data);// Sauter la permier ligne.
        
        fgets(ligne,sizeof(ligne),data);
        text=atof(ligne);

        fgets(ligne,sizeof(ligne),data);
        tint=atof(ligne);
        fclose(data);
      }
      
        
        // on doit récupéré la valeur de la  consigne et celle de la température intérieur
        
        
        data = fopen("data.txt","w");
        if (data!=NULL){

            if (puissance_f > 0){
                fprintf(data,"true\n");
            }else{
                fprintf(data,"false\n");
                
            }
            fprintf(data,"%.2f\n",text);
            fprintf(data,"%.2f",tint);
            fclose(data);
        }
        
        remove(".verrouData");
    
    }
