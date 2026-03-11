#include "consigne.h"


float consigne(float thermostatPrec_f)
{
float thermostat_f=0;
   FILE *inputFile;
   FILE *verrouConsigne;
 
   verrouConsigne = fopen(".verrouConsigne","r");
   // Verification si le verrou existe
   if (verrouConsigne != NULL){
         thermostat_f = thermostatPrec_f;
   }else{
            
            verrouConsigne = fopen(".verrouConsigne","w");//Création de fichier .verrouconsigne
            inputFile = fopen("consigne.txt", "r");
            if ( inputFile == NULL) { // teste l'ouverture
           // printf( "Cannot open file %s\n", "consigne.txt" );
            exit( 0 );
            }
            fscanf(inputFile,"%f", &thermostat_f);// Lecture de la consigne dans le fichier consigne.txt
            fclose( inputFile ); // ferme le fichier
            if(verrouConsigne!=NULL){
              fclose( verrouConsigne );
            }
            
      }
   

   
      remove(".verrouConsigne");
     
      return thermostat_f;

}

