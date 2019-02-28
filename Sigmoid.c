#include <stdio.h>
#include <math.h>

/*declare function*/
double sigmoid(double in);

/*test function*/
int main() {
double ans = sigmoid(10);
printf("Input: 1 \n Output: %f \n", ans);
}

/*write function*/
double sigmoid(double in) {
	return (1.0/(1.0+exp(in)));
}
