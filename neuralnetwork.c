#include <stdio.h>
#include <math.h>


/*declaring all functions */
void read_data();
double function(); 
void input_layer();
double sum_squared_error(); 
void learning();
void epoch(); 
void initialize();
double function(double in);

/*running the program*/
int main() {
printf("I'm a neural network \n");

/*setting the number of nodes*/
int numnodes_in = 2;
int numnodes_out = 1;
int numnodes_hidden = 2;
int num_pattern = 1;

/*setting parameters*/
double error, eta = 0.1, alpha = 0.9;
int i,j,k; 

/*setting datastructures*/
double weight_input_hidden[numnodes_in+1][numnodes_hidden+1];
double weight_hidden_output[numnodes_hidden+1][numnodes_out+1];
double input_nodes[numnodes_in+1];
double input_hidden[numnodes_hidden+1];
double hidden_nodes[numnodes_hidden+1];
double output_nodes[numnodes_out];
double target_values[num_pattern+1][numnodes_out+1];

/*testing functions*/
/*testing sum_squared_error*/
double t[3] = {1.0,1.0,2.0};
double a[3] = {1.0,2.0,2.0};
/*printf("%f\n",t[2]);*/
printf("The error is %f",sum_squared_error(t,a));

}

/*Defining all functions */

/* Function used by nodes in network */
double function(double in) {
	/*Sigmoid function*/
	return(1.0/(1.0 + exp(-in)));

}

/*Calculating the error of desired output vs actual output*/
double sum_squared_error(double target, double actual) {
		double error = 0.0;
		int p;
		for(p=0; p <= sizeof(target); p++) {
			error += (target[p] - actual[p])*(target[p] - actual[p]);
		}
	return error;
} 













