#include <iostream>
#include "metodo_de_gauss.h"

int main(int argc, char const *argv[]){

	int n_equations;
	std::cin >> n_equations;

	EquationsSystem ecuaciones(n_equations);

	ecuaciones.print_solution();

	std::cout << ecuaciones.devuelve_tipo() << std::endl;

	std::vector <double> soluciones = ecuaciones.devuelve_soluciones();

	for ( int i = 0; i < soluciones.size(); i++){
		std::cout << "Incognita " << i + 1 << ": " <<soluciones[i] << std::endl;
	}

	return 0;
}