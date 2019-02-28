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
printf("I'm a neural network \n");
printf("%f\n",Sigmoid(0.5));
}

/*writing all functions */
