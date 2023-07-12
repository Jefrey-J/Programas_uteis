#include <iostream> 

using std::cout; 

float pot(float, int);
float montante(float, float, int); 
int main(int argc, char** argv) {

	float C = 3600; // Capital
	int t = 25*12;   // Tempo de investimento 
	float j = (9/100.0)/12.0; // Taxa de juros
	
	cout << "Montante: " << montante(C, j, t) << "\n"; 
	cout << "Montante formula: " << C*pot(1 + j, t)  << "\n"; 
	return 0;
}

float montante(float C, float j, int t) {
	float M = 0; 
	for(int it = 0; it < t; it++) {
		M = C * (1 + j);  
		C = M + 500.0;
	}
	return M; 
}

float pot(float x, int n) {
	float p = 1; 
	for(int it = 0; it < n; it++) {
		p *= x;  
	}
	if(n == 0)
	{
		p = 1; 
	}
	return p;
}
