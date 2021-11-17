#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cstdlib> 			// for abs function.
#include <math.h>				// for sqrt

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

// no se utiliza numColonias aqui
void leerListaPares(vector< pair<int, int> > & vec, ifstream & MyReadFile, int numColonias){
	string inputRow; //Guarda la linea del input de archivo de texto
	int i = 1;
	int currNum;
	int secondNum;
	while (getline (MyReadFile, inputRow)){
		currNum = obtenerNumeroDeStr(inputRow, i);
		i++;
		secondNum = obtenerNumeroDeStr(inputRow, i);
		vec.push_back(make_pair(currNum, secondNum));
		//cout << currNum << ", " << secondNum << endl;
 		i = 1;
	}
}

int getDistance(pair<int, int> a, pair<int, int> b){

	int distance;
	distance = sqrt(pow((b.first - a.first), 2) + pow((b.second - a.second), 2));
	return distance;
}

// Function to get closest pair of coordenates - Section 4
pair<int, int> closestCentral(vector<pair<int, int>> vec){

	pair<int, int> closest; // pair to hold the indexes of the closest coordenates.
	int distance = INT_MAX; // lowest possible distance.
	int currDistance = 1; // current distance.

	//cout << vec[0].first << ", " << vec[0].second << endl;
	//cout << vec[1].first << ", " << vec[1].second << endl;

	// O(n^2)
	for (int i = 0; i < vec.size() - 1; ++i){

		for (int j = i + 1; j < vec.size(); ++j){

			currDistance = getDistance(vec[i], vec[j]);

			// For the very first iteration this is always true.
			if (currDistance < distance){
				closest.first = i;
				closest.second = j;
				distance = currDistance;
			}
		}
	}

	//cout << closest.first << ", " << closest.second << endl;
	//cout << distance << " vs " << currDistance << endl;
	//cout << closest[0].first << ", " << closest[0].second << endl;
	//cout << closest[1].first << ", " << closest[1].second << endl;
	return closest;
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

	closestCentral(distanciaCentrales);

	/*
		TODO:
		0. Read data ✅
		1. Floyd Warshall 📌
		2. Max Flow 📌
		3. Function to get closest pair of coordenates 📌
	*/

	return 0;
}
