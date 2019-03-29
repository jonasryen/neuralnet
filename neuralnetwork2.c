

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <math.h>
#include <fcntl.h>

#define NUMIN  2
#define NUMHID 4
#define NUMOUT 2
#define INPUTFILE "testdata_input.txt"
#define TARGETFILE "testdata_target.txt"
#define OUTPUTFILE "testdata:output.txt"
#define MAXITERATIONS 1000
#define ACCEPTABLEERROR 0.0004
#define LEARNINGRATE 0.1
#define MOMENTUM 0.9
#define INITIALWEIGHT 0.2
#define FILESIZE 10000

#define rando() ((double)rand()/((double)RAND_MAX+1))

int main() {
    int    i, j, k, p, np, op, iteration;
    int max_iterations = MAXITERATIONS;
    double acceptable_error = ACCEPTABLEERROR;
    
    //Henter inputdata fra fil. 
    char * line = NULL;
    char file_name[FILESIZE] = INPUTFILE;
    ssize_t read;
    size_t len = 0;
    int numberofelements = 0; 
    double ex;
    int number;
    int patterns; 

    FILE *fp;
    fp = fopen(file_name, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    //Sjekker hvor mange linjer med data det er i inputfilen

    while((read = getline(&line, &len, fp)) != -1) {
        numberofelements += 1;
    }

    fclose(fp);
    line = NULL;
    len = 0; 

    fp = fopen(file_name, "r");

    //Legger til data i inputtabellen
    patterns = numberofelements/NUMIN;
    int NUMPAT = patterns;
    int ranpat[patterns+1];
    double input_nodes[patterns+1][NUMIN+1];
    printf("Number of datasets: %i\n",patterns);
    int n = 1; 
    int m = 1;
    int counter = 0; 

       while((read = getline(&line, &len, fp)) != -1) {
        sscanf(line, "%lf", &ex); /* Gjør om fra char til double */
        input_nodes[n][m] = ex;
        counter += 1; 
        if(counter % NUMIN == 0) {
            n += 1;
            m = 1; 
        } else {
            m += 1;
        }; 

        }
       fclose(fp);


    //Henter target data fra fil.
    line = NULL;
    char tfile_name[FILESIZE] = TARGETFILE;
    len = 0;
    int target_patterns = NUMOUT*patterns;
    double target_values[target_patterns+1][NUMOUT+1];

    FILE *tfp;
    tfp = fopen(tfile_name, "r");
    if (tfp == NULL)
        exit(EXIT_FAILURE);

    n = 0;
    m = 1;
    counter = 0;


    while((read = getline(&line, &len, tfp)) != -1) {
        sscanf(line, "%lf", &ex); /* Gjør om fra char til double */
        target_values[n][m] = ex;
        counter += 1; 
        if(counter % NUMOUT == 0) {
            n += 1;
            m = 1; 
        } else {
            m += 1;
        }; 

        }
       fclose(tfp);


    //Gjør klar hidden layer
    int    NumPattern = patterns, numnodes_in = NUMIN, numnodes_hidden = NUMHID, numnodes_out = NUMOUT;
    double input_hidden[NUMPAT+1][NUMHID+1], weight_input_hidden[NUMIN+1][NUMHID+1], hidden_nodes[NUMPAT+1][NUMHID+1];
    double SumO[NUMPAT+1][NUMOUT+1], weight_hidden_output[NUMHID+1][NUMOUT+1], output_nodes[NUMPAT+1][NUMOUT+1];
    double DeltaO[NUMOUT+1], SumDOW[NUMHID+1], DeltaH[NUMHID+1];
    double Deltaweight_input_hidden[NUMIN+1][NUMHID+1], Deltaweight_hidden_output[NUMHID+1][NUMOUT+1];
    double Error, eta = LEARNINGRATE, alpha = MOMENTUM, smallwt = INITIALWEIGHT;

  
    for( j = 1 ; j <= numnodes_hidden ; j++ ) {    /* initialize weight_input_hidden and Deltaweight_input_hidden */
        for( i = 0 ; i <= numnodes_in ; i++ ) { 
            Deltaweight_input_hidden[i][j] = 0.0 ;
            weight_input_hidden[i][j] = 2.0 * ( rando() - 0.5 ) * smallwt ;
        }
    }
    for( k = 1 ; k <= numnodes_out ; k ++ ) {    /* initialize weight_hidden_output and Deltaweight_hidden_output */
        for( j = 0 ; j <= numnodes_hidden ; j++ ) {
            Deltaweight_hidden_output[j][k] = 0.0 ;              
            weight_hidden_output[j][k] = 2.0 * ( rando() - 0.5 ) * smallwt ;
        }
    }
     
    for( iteration = 0 ; iteration < max_iterations; iteration++) {    /* iterate weight updates */
        for( p = 1 ; p <= NumPattern ; p++ ) {    /* randomize order of training patterns */
            ranpat[p] = p ;
        }
        for( p = 1 ; p <= NumPattern ; p++) {
            np = p + rando() * ( NumPattern + 1 - p ) ;
            op = ranpat[p] ; ranpat[p] = ranpat[np] ; ranpat[np] = op ;
        }
        Error = 0.0 ;
        for( np = 1 ; np <= NumPattern ; np++ ) {    /* repeat for all the training patterns */
            p = ranpat[np];
            for( j = 1 ; j <= numnodes_hidden ; j++ ) {    /* compute hidden unit activations */
                input_hidden[p][j] = weight_input_hidden[0][j] ;
                for( i = 1 ; i <= numnodes_in ; i++ ) {
                    input_hidden[p][j] += input_nodes[p][i] * weight_input_hidden[i][j] ;
                }
                hidden_nodes[p][j] = 1.0/(1.0 + exp(-input_hidden[p][j])) ;
            }
            for( k = 1 ; k <= numnodes_out ; k++ ) {    /* compute output unit activations and errors */
                SumO[p][k] = weight_hidden_output[0][k] ;
                for( j = 1 ; j <= numnodes_hidden ; j++ ) {
                    SumO[p][k] += hidden_nodes[p][j] * weight_hidden_output[j][k] ;
                }
                output_nodes[p][k] = 1.0/(1.0 + exp(-SumO[p][k])) ;   /* Sigmoidal Outputs */
/*              output_nodes[p][k] = SumO[p][k];      Linear Outputs */
                Error += 0.5 * (target_values[p][k] - output_nodes[p][k]) * (target_values[p][k] - output_nodes[p][k]) ;   /* SSE */
/*              Error -= ( target_values[p][k] * log( Output[p][k] ) + ( 1.0 - target_values[p][k] ) * log( 1.0 - Output[p][k] ) ) ;    Cross-Entropy Error */
                DeltaO[k] = (target_values[p][k] - output_nodes[p][k]) * output_nodes[p][k] * (1.0 - output_nodes[p][k]) ;   /* Sigmoidal Outputs, SSE */
/*              DeltaO[k] = target_values[p][k] - output_nodes[p][k];     Sigmoidal Outputs, Cross-Entropy Error */
/*              DeltaO[k] = target_values[p][k] - output_nodes[p][k];     Linear Outputs, SSE */
            }
            for( j = 1 ; j <= numnodes_hidden ; j++ ) {    /* 'back-propagate' errors to hidden layer */
                SumDOW[j] = 0.0 ;
                for( k = 1 ; k <= numnodes_out ; k++ ) {
                    SumDOW[j] += weight_hidden_output[j][k] * DeltaO[k] ;
                }
                DeltaH[j] = SumDOW[j] * hidden_nodes[p][j] * (1.0 - hidden_nodes[p][j]) ;
            }
            for( j = 1 ; j <= numnodes_hidden ; j++ ) {     /* update weights weight_input_hidden */
                Deltaweight_input_hidden[0][j] = eta * DeltaH[j] + alpha * Deltaweight_input_hidden[0][j] ;
                weight_input_hidden[0][j] += Deltaweight_input_hidden[0][j] ;
                for( i = 1 ; i <= numnodes_in ; i++ ) { 
                    Deltaweight_input_hidden[i][j] = eta * input_nodes[p][i] * DeltaH[j] + alpha * Deltaweight_input_hidden[i][j];
                    weight_input_hidden[i][j] += Deltaweight_input_hidden[i][j] ;
                }
            }
            for( k = 1 ; k <= numnodes_out ; k ++ ) {    /* update weights weight_hidden_output */
                Deltaweight_hidden_output[0][k] = eta * DeltaO[k] + alpha * Deltaweight_hidden_output[0][k] ;
                weight_hidden_output[0][k] += Deltaweight_hidden_output[0][k] ;
                for( j = 1 ; j <= numnodes_hidden ; j++ ) {
                    Deltaweight_hidden_output[j][k] = eta * hidden_nodes[p][j] * DeltaO[k] + alpha * Deltaweight_hidden_output[j][k] ;
                    weight_hidden_output[j][k] += Deltaweight_hidden_output[j][k] ;
                }
            }
        }
        
        //Skriver ut error for hver runde (iteration)
        if( iteration%100 == 0 ) fprintf(stdout, "\niteration %-5d :   Error = %f", iteration, Error) ;
        if( Error < acceptable_error ) break ;  
    }

    //Skriver ut tabellene med verdier for inputnodene, outputnodene osv. 
    
    fprintf(stdout, "\n\nNETWORK DATA - iteration %d\n\nPat\t", iteration) ;   
    for( i = 1 ; i <= numnodes_in ; i++ ) {
        fprintf(stdout, "input_nodes%-4d\t", i) ;
    }

    //TODO endre denne til å skrive amplitude, periode osv. i stedet. 
    for( k = 1 ; k <= numnodes_out ; k++ ) {
        fprintf(stdout, "target_values%-4doutput_nodes%-4d", k, k) ;
    }


    for( p = 1 ; p <= NumPattern ; p++ ) {        
    fprintf(stdout, "\n%d\t", p) ;
        for( i = 1 ; i <= numnodes_in ; i++ ) {
            fprintf(stdout, "%f\t", input_nodes[p][i]) ;
        }
        for( k = 1 ; k <= numnodes_out ; k++ ) {
            fprintf(stdout, "%f\t%f\t", target_values[p][k], output_nodes[p][k]) ;
        } 
    
    }
    //Skriver output til fil
    FILE *ofp;
    char ofile_name[1000] = OUTPUTFILE;
    ofp = fopen(ofile_name, "w");

    for (p = 1; p <= NumPattern ; p++) {
        for (k = 1 ; k <= numnodes_out ; k++) {
            fprintf(ofp, "%f\n\n", output_nodes[p][k]);
        }
    }
    fclose(ofp);


    fprintf(stdout, "\n\nFullført!\n\n") ;
    return 1 ; 

}

/*******************************************************************************/