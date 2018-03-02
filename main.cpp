#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <chrono>

using namespace std;

//Fetch cities from file
vector< vector<int> > GetCities(){
    vector< vector<int> > Cities;
    ifstream inFile;
    inFile.open("cities.txt");
    string temp;
    while(getline(inFile,temp)){
        vector<int> coordinatePair;
        istringstream buffer(temp);
        string s1,s2;
        buffer >> s1;
        buffer >> s2;
        coordinatePair.push_back(stoi(s1));
        coordinatePair.push_back(stoi(s2));
        Cities.push_back(coordinatePair);
    }
	return Cities;
}

//Get distance between two cities
double GetDistance(vector<int> c1,vector<int> c2){
    int x1,x2,y1,y2;
    x1 = c1[0];
    y1 = c1[1];
    x2 = c2[0];
    y2 = c2[1];
	cout << "Distance is " << 
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

double TotalDistance(vector< vector<double> > Distances, vector<int> randPerm){
	double TotalDist = 0.;
	
	return TotalDist;
}

int main(){
   	//Seed random number generator
	random_device rd;
	mt19937 random_number(rd());
		

    vector< vector<int> > Cities = GetCities();
    vector< vector<double> > Distances;
	vector<int> randPerm;
	Distances.resize(Cities.size());
    for (unsigned int i=0; i<Cities.size(); i++){
		Distances[i].resize(Cities.size());
		randPerm.push_back(i);
        for (unsigned int j=0; j<Cities.size(); j++){
            Distances[i][j] = GetDistance(Cities[i],Cities[j]);
        }
    }
	//generate random permutation for distancesi
	shuffle(randPerm.begin(),randPerm.end(),random_number);
	cout << "Random route: " << endl;
	for (auto el : randPerm){
		cout << el << endl;
	}
		
	double total = 0.;
	for (unsigned int i=0; i<Cities.size()-1; i++){
		total += Distances[randPerm[i]][randPerm[i]+1];
		cout << "Distance between" << randPerm[i] << " and " << randPerm[i+1] << " is " << Distances[randPerm[i]][randPerm[i+1]];
	}
	
	cout << "Total distance: " << total << endl;
    return 0;
}
