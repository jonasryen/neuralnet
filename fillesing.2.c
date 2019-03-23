#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(void) {


//get_intervals();



//}

//int get_intervals(){

	FILE * fp;
	FILE * tabell;

	char * line = NULL;
	size_t len = 0;
    ssize_t read;
    double first = 0.0;
    double second;
    double ex;
    int counter = 0;
    double toppunkt = 0;
    double bunnpunkt = 0;
    int nullpunkt_counter = 1;
    int place_counter = 0;
    double liste_verdier[3868];

    fp = fopen("data.example.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        sscanf(line, "%lf", &ex); /* Leser verdier som double og lagrer de som ex */
    	printf("%lf\n", second);
        first = second;
        second = ex;
        counter += 1;


        if (first > 0 && second < 0 ){
        	printf("\n--------Nullpunkt %d-------- \n\n", nullpunkt_counter);
        	printf("Periode: %d 	Amplitude: %f \n\n", counter, toppunkt);
        	liste_verdier[place_counter] = counter;
        	place_counter = place_counter + 1;
        	liste_verdier[place_counter] = toppunkt;
        	place_counter = place_counter + 1;
        	counter = 0;
        	bunnpunkt = second;
        	nullpunkt_counter = nullpunkt_counter + 1;

        }

        if (first < 0 && second > 0){
        	printf("\n--------Nullpunkt %d-------- \n\n", nullpunkt_counter);
			printf("Periode: %d 	Amplitude: %f \n\n", counter, bunnpunkt);
			liste_verdier[place_counter] = counter;
        	place_counter = place_counter + 1;
        	liste_verdier[place_counter] = bunnpunkt;
        	place_counter = place_counter + 1;
        	counter = 0;
        	toppunkt = second;
        	nullpunkt_counter = nullpunkt_counter +1;


        }

        if (second > toppunkt) {
        	toppunkt = second;
        }

        if (second < bunnpunkt) {
        	bunnpunkt = second;
        }

        


    }

    printf("\n--------Nullpunkt %d -------- \n\n", nullpunkt_counter + 1);
			printf("Periode: %d 	Amplitude: %f \n\n", counter, toppunkt);
        	counter = 0;
        	toppunkt = second;
    
    tabell = fopen("tabell.txt", "w");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int k = 0;
    for (k = 0; k < place_counter; k = k +1){
    	fprintf(tabell, "%f\n",liste_verdier[k]);
    }


    fclose(fp);
    exit(EXIT_SUCCESS);



    tabell = fopen("tabell.txt", "w");
    if (fp == NULL)
        exit(EXIT_FAILURE);
  	

   
}








