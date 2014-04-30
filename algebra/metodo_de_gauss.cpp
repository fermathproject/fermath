#include <iostream>
#include <vector> 
#include <string>
#include "metodo_de_gauss.h"
/**
* Transformaciones elementales;
*/
void EquationsSystem::intercambia_filas(int i, int j){//Nada mas que añadir.
	double aux;

	for (int x = 0; x <= n_equations; x++){
		aux = *(*(solution + i)+x);
		*(*(solution + i)+x) = *(*(solution + j)+x);
		*(*(solution + j)+x) = aux;
	}
}

void EquationsSystem::multiplica_por(double lamda, int fila){//Multiplica a la fila por lamda.
	for ( int i = 0; i <= n_equations; i++){
		*(*(solution + fila)+i) = (*(*(solution + fila)+i))*lamda;
	}
}

void EquationsSystem::fila_mas_fila_por_lamda(int primera, int segunda, double lamda){//A la primera se le suma la segunda multiplicada por lamda.
	for ( int i = 0; i <= n_equations; i++){
		*(*(solution + primera) + i) = (*(*(solution + primera) + i)) + lamda *(*(*(solution + segunda) + i));
	}
}

int EquationsSystem::busca_termino_no_nulo1(int columna){//Se usa para cambiar de fila si hay un elemento nulo en la diagonal.
	bool encontrado = false;
	int no_nula = -1;

	for ( int i = columna + 1; i < n_equations && !encontrado; i++){
		if ( (*(*(solution + i) + columna)) != 0){
			no_nula = i;
			encontrado = true;
		}
	}
	return no_nula;
}

int EquationsSystem::busca_termino_no_nulo2(int columna){// Se usa para comprobarque se puede cambiar la fila por otra.
	bool encontrado = false;
	int no_nula = -1;
	for ( int i = columna - 1; i >= 0 && !encontrado; i--){
		if ( ( *(*(solution + i) + columna)) != 0 && (*(*(solution + i) + i) == 0)){
			no_nula = i;
			encontrado = true;
		}
	}
	return no_nula;
}

void EquationsSystem::convierte_a_triangular_inferior(){ //Es el primer paso para la resolucion. Deja a unos la diagonal.
	for ( int i = 0; i < n_equations; i++){
		if (*(*(solution + i) + i) == 0 && busca_termino_no_nulo1(i) != -1){
			intercambia_filas(i, busca_termino_no_nulo1(i));
			i--;
		}
		else if ( *(*(solution + i) + i) != 0){
			multiplica_por(1/(*(*(solution + i) + i)), i);
			for ( int j = i + 1; j < n_equations; j++){
				fila_mas_fila_por_lamda(j,i,-(*(*(solution + j) + i)));
			}
		}
	}
}

void EquationsSystem::convierte_a_triangular_superior(){ // Se usa tras convierte a triangular_inferior().
	for ( int i = n_equations - 1; i >= 0; i--){
		if (*(*(solution + i) + i) == 0 && busca_termino_no_nulo2(i) != -1){
			intercambia_filas(i,busca_termino_no_nulo2(i));
			resuelve();
		}
		
		else if ( *(*(solution + i) + i) != 0){
			multiplica_por(1/(*(*(solution + i) + i)), i);
			for ( int j = i - 1; j >= 0; j--){
				fila_mas_fila_por_lamda(j,i,-(*(*(solution + j) + i)));
			}
		}
	}
}

void EquationsSystem::resuelve(){ // Resuelve el sistema de ecuaciones.
	convierte_a_triangular_superior();
	convierte_a_triangular_inferior();
}

bool EquationsSystem::es_incompatible(){ // Determina si es incompatible.
	bool es_incompatible = false;
	
	for ( int i = 0; i < n_equations; i++){
		if ( *(*(solution + i) + n_equations) != 0 && *(*(solution +i) + i) == 0){
			es_incompatible = true;
		}
	}


	return es_incompatible;
}

bool EquationsSystem::es_compatible_determinado(){ // Determina si es compatible determinado.
	bool es_compatible = true;
	for(int i = 0; i < n_equations && es_compatible; i++){

		if ( ( *( *(solution + i) + i) == 0)){
			es_compatible = false;
		}
	}
	return es_compatible;
}

bool EquationsSystem::es_compatible_indeterminado(){ // Determina si es compatible indeterminado.
	bool es_compatible_indeterminado = !es_incompatible() && !es_compatible_determinado();
	return es_compatible_indeterminado;

}

void EquationsSystem::determina_sistema(){ // Determina el tipo.
	if ( es_compatible_determinado()){
		this->tipo = "compatible_determinado";
	}
	else if ( es_incompatible()){
		this->tipo = "incompatible";
	}
	else{
		this->tipo = "compatible_indeterminado";
	}
}

/**
* Aquí se realiza la lectura de datos. Podeis cambiar la forma de inicializar el sistema de ecuaciones.
*/

EquationsSystem::EquationsSystem(int n_equations){
	this->n_equations = n_equations;
	solution = new double * [n_equations];

	double entrada;

	for( double **i = solution; i < solution + n_equations; i++){
		*i = new double [n_equations + 1];
		for (double * j = *i; j <= *i + n_equations; j++){
			std::cin >> entrada;
			*j = entrada;
		}
	}
	resuelve();
	determina_sistema();
}

/**
* Devuelve el tipo de sistema que es.
*/

std::string EquationsSystem::devuelve_tipo(){
	return tipo;
}

void EquationsSystem::print_solution(){ // Imprime el sistema de ecuaciones en cada momento.
	for ( int i = 0; i < n_equations; i++){
		std::cout << "[";
		for ( int j = 0; j <= n_equations; j++){
			std::cout << *(*(solution + i) + j) << " ";
		}
		std::cout << "]" << std::endl;
	}
	std::cout << std::endl;
}

std::vector <double> EquationsSystem::devuelve_soluciones(){
	std::vector <double> solution;
	if ( es_compatible_determinado()){
		
		double entrada;
		for (int i = 0; i < n_equations; i++){
			entrada = (*(*(this->solution + i) + n_equations));
			solution.push_back(entrada);
		}
		
	
	}
	return solution;
}