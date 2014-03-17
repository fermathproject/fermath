//compile with g++ -I eigen systems.cpp -o systems

#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <string>

using namespace std;
using namespace Eigen;

// Funcion que devuelve la solucion de sistemas lineales hasta 5 incognitas.
// El numero de ecuaciones debe de ser igual al numero de incognitas.
// 
// Tipo de dato devuelto: vector con las soluciones del sistema
// eqs-> ecuaciones del sistema
// tipo-> tipo de sistema: compatible determinado, compatible indeterminado, incompatible
vector<double> Solve_eq_System (vector<vector<double> > &eqs, string &tipo)
{
	int nincog=eqs.size();
	if(nincog==1)
	{
		Matrix<double,1,1> A; // Matriz de los coeficientes
		Matrix<double,1,1> B; // Vector de los terminos independientes
		Matrix<double,1,2> C; // Matriz ampliada
		Matrix<double,1,1> result; // Soluciones del sistema

		for(int i=0; i<nincog; i++)
		{
			for(int j=0; j<eqs[i].size(); j++)
			{
				if(j!=(eqs[i].size())-1)
				{
					A(i,j)=eqs[i][j];
				}
				else
				{
					B(i)=eqs[i][j];
				}
				C(i,j)=eqs[i][j];
			}
		}

		// Tipo de sistema
		bool com_det=false, incompatible=false, com_indet=false;
		vector<double> finalresult;
	
		if(A.fullPivLu().rank()==C.fullPivLu().rank() && A.fullPivLu().rank()==nincog)
		{
			com_det=true;
			tipo="compatible determinado";

			result = A.colPivHouseholderQr().solve(B);

			for(int i=0; i<nincog;i++)
				finalresult.push_back(result[i]);
		}
		else if(A.fullPivLu().rank()==C.fullPivLu().rank() && A.fullPivLu().rank()<nincog)
		{
			com_indet=true;
			tipo="compatible indeterminado";
		}
		else if (A.fullPivLu().rank()!=C.fullPivLu().rank())
		{
			incompatible=true;
			tipo="incompatible";
		}
	
		return finalresult;	
	}
	if(nincog==2)
	{
		Matrix<double,2,2> A; // Matriz de los coeficientes
		Matrix<double,2,1> B; // Vector de los terminos independientes
		Matrix<double,2,3> C; // Matriz ampliada
		Matrix<double,2,1> result; // Soluciones del sistema

		for(int i=0; i<nincog; i++)
		{
			for(int j=0; j<eqs[i].size(); j++)
			{
				if(j!=(eqs[i].size())-1)
				{
					A(i,j)=eqs[i][j];
				}
				else
				{
					B(i)=eqs[i][j];
				}
				C(i,j)=eqs[i][j];
			}
		}

		// Tipo de sistema
		bool com_det=false, incompatible=false, com_indet=false;
		vector<double> finalresult;
	
		if(A.fullPivLu().rank()==C.fullPivLu().rank() && A.fullPivLu().rank()==nincog)
		{
			com_det=true;
			tipo="compatible determinado";

			result = A.colPivHouseholderQr().solve(B);

			for(int i=0; i<nincog;i++)
				finalresult.push_back(result[i]);
		}
		else if(A.fullPivLu().rank()==C.fullPivLu().rank() && A.fullPivLu().rank()<nincog)
		{
			com_indet=true;
			tipo="compatible indeterminado";

			finalresult.push_back(eqs[0][2]);
			finalresult.push_back(eqs[0][1]); // esto debe llevar un menos delante
			finalresult.push_back(eqs[0][0]); // esto divide a la suma de lo anterior
		}
		else if (A.fullPivLu().rank()!=C.fullPivLu().rank())
		{
			incompatible=true;
			tipo="incompatible";
		}
	
		return finalresult;		
	}
	if(nincog==3)
	{
		Matrix<double,3,3> A; // Matriz de los coeficientes
		Matrix<double,3,1> B; // Vector de los terminos independientes
		Matrix<double,3,4> C; // Matriz ampliada
		Matrix<double,3,1> result; // Soluciones del sistema

		for(int i=0; i<nincog; i++)
		{
			for(int j=0; j<eqs[i].size(); j++)
			{
				if(j!=(eqs[i].size())-1)
				{
					A(i,j)=eqs[i][j];
				}
				else
				{
					B(i)=eqs[i][j];
				}
				C(i,j)=eqs[i][j];
			}
		}

		// Tipo de sistema
		bool com_det=false, incompatible=false, com_indet=false;
		vector<double> finalresult;
	
		if(A.fullPivLu().rank()==C.fullPivLu().rank() && A.fullPivLu().rank()==nincog)
		{
			com_det=true;
			tipo="compatible determinado";

			result = A.colPivHouseholderQr().solve(B);

			for(int i=0; i<nincog;i++)
				finalresult.push_back(result[i]);
		}
		else if(A.fullPivLu().rank()==C.fullPivLu().rank() && A.fullPivLu().rank()<nincog)
		{
			com_indet=true;
			tipo="compatible indeterminado";
		}
		else if (A.fullPivLu().rank()!=C.fullPivLu().rank())
		{
			incompatible=true;
			tipo="incompatible";
		}
	
		return finalresult;
	}
	if(nincog==4)
	{
		Matrix<double,4,4> A; // Matriz de los coeficientes
		Matrix<double,4,1> B; // Vector de los terminos independientes
		Matrix<double,4,5> C; // Matriz ampliada
		Matrix<double,4,1> result; // Soluciones del sistema

		for(int i=0; i<nincog; i++)
		{
			for(int j=0; j<eqs[i].size(); j++)
			{
				if(j!=(eqs[i].size())-1)
				{
					A(i,j)=eqs[i][j];
				}
				else
				{
					B(i)=eqs[i][j];
				}
				C(i,j)=eqs[i][j];
			}
		}

		// Tipo de sistema
		bool com_det=false, incompatible=false, com_indet=false;
		vector<double> finalresult;
	
		if(A.fullPivLu().rank()==C.fullPivLu().rank() && A.fullPivLu().rank()==nincog)
		{
			com_det=true;
			tipo="compatible determinado";

			result = A.colPivHouseholderQr().solve(B);

			for(int i=0; i<nincog;i++)
				finalresult.push_back(result[i]);
		}
		else if(A.fullPivLu().rank()==C.fullPivLu().rank() && A.fullPivLu().rank()<nincog)
		{
			com_indet=true;
			tipo="compatible indeterminado";
		}
		else if (A.fullPivLu().rank()!=C.fullPivLu().rank())
		{
			incompatible=true;
			tipo="incompatible";
		}
	
		return finalresult;
	}
	if(nincog==5)
	{
		Matrix<double,5,5> A; // Matriz de los coeficientes
		Matrix<double,5,1> B; // Vector de los terminos independientes
		Matrix<double,5,6> C; // Matriz ampliada
		Matrix<double,5,1> result; // Soluciones del sistema

		for(int i=0; i<nincog; i++)
		{
			for(int j=0; j<eqs[i].size(); j++)
			{
				if(j!=(eqs[i].size())-1)
				{
					A(i,j)=eqs[i][j];
				}
				else
				{
					B(i)=eqs[i][j];
				}
				C(i,j)=eqs[i][j];
			}
		}

		// Tipo de sistema
		bool com_det=false, incompatible=false, com_indet=false;
		vector<double> finalresult;
	
		if(A.fullPivLu().rank()==C.fullPivLu().rank() && A.fullPivLu().rank()==nincog)
		{
			com_det=true;
			tipo="compatible determinado";

			result = A.colPivHouseholderQr().solve(B);

			for(int i=0; i<nincog;i++)
				finalresult.push_back(result[i]);
		}
		else if(A.fullPivLu().rank()==C.fullPivLu().rank() && A.fullPivLu().rank()<nincog)
		{
			com_indet=true;
			tipo="compatible indeterminado";
		}
		else if (A.fullPivLu().rank()!=C.fullPivLu().rank())
		{
			incompatible=true;
			tipo="incompatible";
		}
	
		return finalresult;
	}	
}

// Funcion que imprime por pantalla las soluciones de un sistema de 2
// ecuaciones y 2 incognitas
void Imprime_System_Result_2eq (const vector<double> &result, const string &tipo)
{
	cout << "Tipo de sistema: " << tipo << endl;
	if(tipo=="compatible determinado")
		cout << "x=" << result[0] << "; y=" << result[1] << endl << endl;
	if(tipo=="compatible indeterminado")
	{
		cout << "Tiene infinitas soluciones" << endl;		
		cout << "x=(" << result[0] << "-(" << result[1] << ")*A)/" << result[2] << ";" << endl << "y=A;" << endl << endl;
	}
	if(tipo=="incompatible")
		cout << "No tiene solucion" << endl;
}

// Funcion que imprime por pantalla las soluciones de un sistema de 3
// ecuaciones y 3 incognitas
void Imprime_System_Result_3eq (const vector<double> &result, const string &tipo)
{
	cout << "Tipo de sistema: " << tipo << endl;
	if(tipo=="compatible determinado")
		cout << "x=" << result[0] << "; y=" << result[1] << "; z=" << result[2] << endl << endl;
	if(tipo=="compatible indeterminado")
		cout << "Tiene infinitas soluciones" << endl;
	if(tipo=="incompatible")
		cout << "No tiene solucion" << endl;
}

int main()
{
 	// Pruebas

	// Sistema compatible determinado
	//  1x+2y-2z=10
	//  4x- y+ z= 4
	// -2x+ y+ z=-2 ==> x=2;y=3;z=-1

	vector<vector<double> > eqs;
	vector<double> eq, result;
	string tipo;
	
	eq.push_back(1);
	eq.push_back(2);
	eq.push_back(-2);
	eq.push_back(10);
	eqs.push_back(eq);
	eq.clear();
	
	eq.push_back(4);
	eq.push_back(-1);
	eq.push_back(1);
	eq.push_back(4);
	eqs.push_back(eq);
	eq.clear();	

	eq.push_back(-2);
	eq.push_back(1);
	eq.push_back(1);
	eq.push_back(-2);
	eqs.push_back(eq);
	eq.clear();

	cout << "Sistema:" << endl;
	cout << "    1x+2y-2z=10" << endl << "    4x- y+ z= 4" << endl << "   -2x+ y+ z=-2" << endl;

	result=Solve_eq_System(eqs,tipo);
	Imprime_System_Result_3eq(result,tipo);

	eqs.clear();
		

	// *************************************************************************** //
	// Sistema compatible indeterminado
	// 2x-3y=1
	// 4x-6y=2 ==> infinitas soluciones

	eq.push_back(2);
	eq.push_back(-3);
	eq.push_back(1);
	eqs.push_back(eq);
	eq.clear();

	eq.push_back(4);
	eq.push_back(-6);
	eq.push_back(2);
	eqs.push_back(eq);
	eq.clear();

	cout << "Sistema:" << endl;
	cout << "    2x-3y=1" << endl << "    4x-6y=2" << endl;

	result=Solve_eq_System(eqs,tipo);
	Imprime_System_Result_2eq(result,tipo);

	eqs.clear();

	// *************************************************************************** //
	// Sistema incompatible
	//  x-2y-3z=1
	// 3x+ y-7z=0 
	//  x+5y- z=2 ==> no tiene solucion

	eq.push_back(1);
	eq.push_back(-2);
	eq.push_back(-3);
	eq.push_back(1);
	eqs.push_back(eq);
	eq.clear();
	
	eq.push_back(3);
	eq.push_back(1);
	eq.push_back(-7);
	eq.push_back(0);
	eqs.push_back(eq);
	eq.clear();	

	eq.push_back(1);
	eq.push_back(5);
	eq.push_back(-1);
	eq.push_back(2);
	eqs.push_back(eq);
	eq.clear();

	cout << "Sistema:" << endl;
	cout << "     x-2y-3z=1" << endl << "    3x+ y-7z=0" << endl << "     x+5y- z=2" << endl;

	result=Solve_eq_System(eqs,tipo);
	Imprime_System_Result_3eq(result,tipo);

	eqs.clear();
}
