#include "visualisationT.h"

void visualisationT(temp_t myTemp)
{
   char temoin[20];
   FILE *inputFile;
   FILE *verrouConsigne;
   verrouConsigne = fopen(".verrouData","r");
   
   
   if (verrouConsigne != NULL){// Présence du verrou
        fclose( verrouConsigne );
        return;
    }else
    {
        verrouConsigne = fopen(".verrouData","w");//Création de fichier .        
        if (verrouConsigne != NULL)// Présence du verrou
        {
        fclose( verrouConsigne );
        }

        inputFile = fopen("data.txt", "r");
        if(inputFile!=NULL){// Verrification de l'existance du fichier data 
            fscanf(inputFile,"%s",temoin);// Lecture du temoin
            fclose(inputFile);
        }
        

        inputFile = fopen("data.txt", "w");
        if ( inputFile == NULL) { // teste l'ouverture
         // printf( "Cannot open file %s\n", "data.txt" );
            return;
        }
        fprintf(inputFile,"%s\n", temoin);
        fprintf(inputFile,"%.2f\n", myTemp.interieure);// ecriture de la consigne dans le fichier consigne.txt
        fprintf(inputFile,"%.2f", myTemp.exterieure);
        fclose( inputFile ); // ferme le fichier
        remove(".verrouData");
    }
    
}
