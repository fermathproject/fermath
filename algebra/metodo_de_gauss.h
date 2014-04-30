#include <string>
#include <vector>

class EquationsSystem{
private:
	//Tipo de ecuacion:
		//1-compatible determinado
		//2-compatible indeterminado
		//3-incompatible
	std::string tipo;

	/**
	* Esta matriz es la que modificaremos para obtener las soluciones.
	*/

	double ** solution;

	/**
	* Nos indica el numero de ecuaciones que tenemos.
	*/

	int n_equations;
	/**
	* Transformaciones elementales;
	*/
	void intercambia_filas(int i, int j);//Nada mas que añadir.


	void multiplica_por(double lamda, int fila);//Multiplica a la fila por lamda.


	void fila_mas_fila_por_lamda(int primera, int segunda, double lamda);//A la primera se le suma la segunda multiplicada por lamda.

	int busca_termino_no_nulo1(int columna);//Se usa para cambiar de fila si hay un elemento nulo en la diagonal.


	int busca_termino_no_nulo2(int columna);// Se usa para comprobarque se puede cambiar la fila por otra.


	void convierte_a_triangular_inferior(); //Es el primer paso para la resolucion. Deja a unos la diagonal.

	void convierte_a_triangular_superior(); // Se usa tras convierte a triangular_inferior().


	void resuelve(); // Resuelve el sistema de ecuaciones.

	bool es_incompatible(); // Determina si es incompatible.


	bool es_compatible_determinado(); // Determina si es compatible determinado.

	bool es_compatible_indeterminado(); // Determina si es compatible indeterminado.

	void determina_sistema();

public:
	/**
	* Aquí se realiza la lectura de datos. Podeis cambiar la forma de inicializar el sistema de ecuaciones.
	*/

	EquationsSystem(int n_equations);

	/**
	* Devuelve el tipo de sistema que es.
	*/
	
	std::string devuelve_tipo();

	void print_solution();

	std::vector <double> devuelve_soluciones();

};