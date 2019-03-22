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
int numnodes_in = 3;
int numnodes_out = 1;
int numnodes_hidden = 3;

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

double example_input[3] = {1,2,3};
double example_weight[3][4] = {(1,1,1),(2,2,2),(3,3,3),(4,4,4)};


double result[4] = calc_hidden_values(example_input,example_weight);


}

/*writing all functions */

/* Defining function to calculate all inputs to nodes in hidden layer*/

double calc_hidden_values(double input_nodes, double weight_input_hidden) {
	int j;
	int i;
	int numnodes_in = 3;
	int numnodes_out = 1;
	int numnodes_hidden = 3;
	double input_hidden[numnodes_hidden+1];
	double hidden_nodes[numnodes_hidden+1];

	for (j = 1; j<= numnodes_hidden; j++) {
		input_hidden[j] = weight_input_hidden[0][j];
		for (i = 1; i<= numnodes_in; i++) {
			input_hidden[j] += input_nodes[i]*weight_input_hidden[i][j];
		}
		/*hidden_nodes[j] = function(input_hidden[j])*/
	}
	return(input_hidden)
}