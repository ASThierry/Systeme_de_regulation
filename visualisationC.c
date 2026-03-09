#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "visualisationC.h"

void visualisationC(float puissance_f){
    FILE * lockFile;
    FILE * data;
    lockFile = fopen(".verrouData","r");
    if (lockFile == NULL){
        lockFile = fopen(".verrouData","w");
        data = fopen("data.txt","w");
        if (data){
            if (puissance_f==0){
                fprintf(data,"false");
            }
            else {
                if (puissance_f>0) {
                    fprintf(data,"true");
                }
            }
            fclose(data);
        }
        fclose(lockFile);
        remove(".verrouData");
    }
    else {
        fclose(lockFile);
    }
}