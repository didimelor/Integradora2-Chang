#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;


int obtenerNumeroDeStr(string line, int & pos){ 
	int initPos = pos;
	while(int(line[pos]) > 47 && int(line[pos]) < 58 && pos < line.length() - 1){
		pos++;
	}
	return stoi(line.substr(initPos , pos));
	//return -1;
}

void leerMat(vector< vector<int> > & mat, ifstream & MyReadFile, int numColonias){
	string inputRow; //Guarda la linea del input de archivo de texto
	int i = 0;
	for(int row = 0; row < numColonias; row++){
		getline (MyReadFile, inputRow);
		for(int col = 0; col < numColonias; col++){
			while(inputRow[i] == ' '){
				i++;
			}
			mat[row][col] = obtenerNumeroDeStr(inputRow, i);
		}
		i = 0;
	}

}

void leerListaPares(vector< pair<int, int> > & vec, ifstream & MyReadFile, int numColonias){
	string inputRow; //Guarda la linea del input de archivo de texto
	int i = 1;
	int currNum;
	int secondNum;
	while (getline (MyReadFile, inputRow)){
		currNum = obtenerNumeroDeStr(inputRow, i);
		i += 1;
		secondNum = obtenerNumeroDeStr(inputRow, i);
		vec.push_back(make_pair(currNum, i));
		i = 1;
	}
}

int main(){
	string c;
	ifstream MyReadFile("inpIntegradora2.txt");
	//Numero de Colonias a int
	getline (MyReadFile, c);
	int numColonias = stoi(c);
	//Inicializar matrices/vectores
	vector< vector<int> > distanciaEntreColonias (numColonias, vector<int> (numColonias, -1));
	vector< vector<int> > flujoEntreColonias (numColonias, vector<int> (numColonias, -1));
	vector< pair<int, int> > distanciaCentrales;


	leerMat(distanciaEntreColonias, MyReadFile, numColonias);
	leerMat(flujoEntreColonias, MyReadFile, numColonias);
	leerListaPares(distanciaCentrales, MyReadFile, numColonias);

	MyReadFile.close();
	
	return 0;
}