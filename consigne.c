#include "consigne.h"

   float consigne(float thermostatPrec_f)
   {
   
      float thermostat_f=0;
      FILE *inputFile;
      inputFile = fopen("consigne.txt", "r");
      if ( inputFile == NULL) { // teste l'ouverture
            printf( "Cannot open file %s\n", "consigne.txt" );
            exit( 0 );
      }
      fscanf(inputFile,"%f", &thermostat_f);
      

      fclose( inputFile ); // ferme le fichier
   
     
      return thermostat_f;
   
   }
