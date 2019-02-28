#include <stdio.h>
#include <math.h>


/*declaring all functions */
void read_data();
void function(); 
void input_layer();
void error(); 
void learning();
void epoch(); 
void initialize(); 

/* Different functions used by nodes in network */

/*Sigmoid function*/

double Sigmoid(double in) {
	return(1.0/(1.0 + exp(-in)));

}


/*running the program*/
int main() {
printf("I'm fucking retard \n");
printf("%f\n",Sigmoid(0.5));

/*setting the number of nodes*/
int numnodes_in = 2;
int numnodes_out = 1;
int numnodes_hidden = 2;

/*setting parameters*/
double error, eta = 0.1, alpha = 0.9; 

}

/*writing all functions */
