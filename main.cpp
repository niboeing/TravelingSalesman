#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>

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
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

int main(){
    //Read city positions from file and generate distance table
    vector< vector<int> > Cities = GetCities();
    vector< vector<double> > Distances;
	vector<int> randPerm;
    for (int i=0; i<Cities.size(); i++){
		randPerm.push_back(i);
        for (int j=0; j<Cities.size(); j++){
            Distances[i][j] = GetDistance(Cities[i],Cities[j]);
        }
    }
	//generate random permutation for distances
	random_shuffle(randPerm.begin(),randPerm.end());
		
	double total = 0.;
	for (int i=0; i<Cities.size()-1; i++){
		total += Distances[randPerm[i]][randPerm[i]+1];
	}
	
	cout << "Total distance: " << total << endl;
    return 0;
}
