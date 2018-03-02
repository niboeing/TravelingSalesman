#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <functional>

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

//calculate total distance from distance table and chosen path
double TotalDistance(vector< vector<double> > Distances, vector<int> randPerm){
	double total = 0.;
	for (unsigned int i=0; i<Distances.size(); i++){
		if (i==Distances.size()-1){
			total+=Distances[randPerm[i]][randPerm[0]];
		}	
		else {
			total += Distances[randPerm[i]][randPerm[i]+1];
		}	
	}
	
	return total;
}

int main(){
   	//Seed random number generator
	random_device rd;
	mt19937 random_number(rd());
	
	//select temperature
	double temperature = 1.;
		
	
	//Get cities and build distance table
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
	int N = Cities.size();
	
	//generate random permutation for distances
	shuffle(randPerm.begin(),randPerm.end(),random_number);
	cout << "Random route: " << endl;
	for (auto el : randPerm){
		cout << el << endl;
	}
	
	//thermodynamic algorithm
	//STEP 1
	//c_k = s_k, calculate distance
	vector<int> c_k = randPerm;
	double length_before = TotalDistance(Distances,c_k);
	
	cout << "LENGTH BEFORE: " << length_before;
	
	
	//STEP 2
	//first time set i=0, after increment by 1
	
	for (int alg_i = 0;alg_i<N;alg_i++){
	
		//STEP 3
		//generate random j
		while (alg_j==alg_i){
			j = bind(uniform_int_distribution<int>(0,N-1),random_number);
		}
		i_tilde = min(alg_i,alg_j);
		j_tilde = max(alg_i,alg_j);
		
		//STEP 4
		//switch path
		vector<int> t_k;
		t_k.resize(N)
		
		for (int k=0;k<i_tilde;k++){
			t_k[k] = c_k[k];
		}
		for (int k=0;k<j_tilde-i_tilde;k++){
			t_k[i_tilde+k-1] = c[j_tilde-k-1];
		}
		for (int k=j_tilde;k<N;k++){
			t_k[k] = c_k[k];
		}
		
		
		//STEP 5
		//calculate distance after switching
		double length_after = TotalDistance(Distances,t_k);
		
		//STEP 6
		//check if distance improved, if not random chance to accept anyway
		if (length_after>length_before){
			double alg_x = bind(uniform_real_distribution<double>(0,1),random_number);
			if (alg_x<exp((length_before-length_after)/temperature)){
				//STEP 7
				c_k = t_k;
				length_before = length_after;
			}
		}
		//STEP 7
		else {
			c_k = t_k;
			length_before = length_after;
		}
	}
	
	cout << "LENGTH AFTER: " << length_before;
    return 0;
}
