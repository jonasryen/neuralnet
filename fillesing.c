#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("data.example.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    int shifter = 0;
    int axis = 0;
    double ex;
    double first = 0.0;
    double second;
    double topp1 = 0;
    double topp2;
    double bunn1 = 0;
    double bunn2;
    double topp_punkter[3000];
    double bunn_punkter[3000];
    double periode_topper[3000];
    double periode_bunner[3000];
    int tid_første_topp = 0;
    int tid_andre_topp;
    int tid_første_bunn = 0;
    int tid_andre_bunn;
    int antall_topper = 0;
    int antall_bunner = 0;


    int counter = 0;



    while ((read = getline(&line, &len, fp)) != -1) {

  	
        sscanf(line, "%lf", &ex); /* Gjør om fra char til int */
        second = ex;

        if (shifter == 0){
	        if(second < first) {
	        	
	        	
	        	tid_andre_topp = counter;
	        	int intervall = tid_andre_topp - tid_første_topp;
	        	periode_topper[antall_topper] = intervall;
                antall_topper += 1;
                tid_første_topp = counter;
                topp_punkter[antall_topper] = first;
                shifter = 1;
                

                printf("%f\n",periode_topper[antall_topper] );
	        	
	        	
	        	printf("\nToppunkt?\n\n");
	     		
	     		

	     		
	        }
	     }
	     else {
	     	if (second > first) {
	     		antall_bunner += 1;


				tid_andre_bunn = counter;
	        	int intervall = tid_andre_bunn - tid_første_bunn;
	        	periode_bunner[antall_bunner] = intervall;
                if (intervall > 90) {

                }
	        	tid_første_bunn = counter;

	        	printf("\nBunnpunkt?\n\n");
	     		shifter = 0;
	     		bunn_punkter[antall_bunner] = first;
	     		
	     	}

	     }
	    printf("%d         %lf\n", counter, ex);
        first = second;
        counter += 1;

    }


    int i;
    printf("\nTopperioder:\n");
    int sum_topp_perioder = 0;
    for (i = 0; i < antall_topper; i = i+1){
        sum_topp_perioder = sum_topp_perioder + periode_topper[i];
    	printf("%lf\n", periode_topper[i]);
    	i = i + 1;
    }

    printf("\nBunnperioder:\n\n");
    int j;
    int sum_bunn_perioder = 0;
    for (j = 0; j < antall_bunner; j = j + 1) {
        sum_bunn_perioder = sum_bunn_perioder + periode_bunner[j];
        printf("%lf\n", periode_bunner[j]);
    }


    double avg_topp_perioder = sum_topp_perioder/antall_topper;
    printf("Snitt periodetid mellom topper: %f\n", avg_topp_perioder );
    double avg_bunn_perioder = sum_bunn_perioder/antall_bunner;
    printf("Snitt periodetid mellom bunner: %f\n", avg_bunn_perioder);



	
	//printf("\nAmplitude 1: %lf\nAmplitude 2: %lf\nAmplitude 3: %lf\nAmplitude 4: %lf\n\n", topp1, topp2, -1*bunn1, -1*bunn2);	

		axis += 1;

/*
	    if (counter == 0){

	        if (atof(first) > atof(second)){
	        	printf("Ekstremalpunkt?");
	        	counter = 1;
	        }
	    }

	    else {
	    	if (atof(first) < atof(second)){
	    		printf("Bunnpunkt?");
	    		counter = 0;
	    	}
	    }

	    */
    

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}