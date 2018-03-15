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
#include <map>

using namespace std;

//Fetch cities from file
vector< vector<double> > GetCities(){
    vector< vector<double> > Cities;
    ifstream inFile;
    inFile.open("cities.txt");
    string temp;
    while(getline(inFile,temp)){
        vector<double> coordinatePair;
        istringstream buffer(temp);
        string s1,s2;
        buffer >> s1;
        buffer >> s2;
        coordinatePair.push_back(stof(s1));
        coordinatePair.push_back(stof(s2));
        Cities.push_back(coordinatePair);
    }
	inFile.close();
	return Cities;
}

//Get distance between two cities
double GetDistance(vector<double> c1,vector<double> c2){
    double x1,x2,y1,y2;
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
			total += Distances[randPerm[i]][randPerm[i+1]];
		}	
	}
	
	return total;
}

//import config
map<string,string> GetConfig(){
	map<string,string> config;
	ifstream inFile;
	inFile.open("config.txt");
	string line;
	while(getline(inFile,line)){
		auto delim = line.find("=");
		auto name = line.substr(0,delim);
		auto value = line.substr(delim+1);
		config[name] = value;
	}
	inFile.close();
	return config;
}

int main(){
	cout << "Thermodynamic approach to the Traveling Salesman Problem" << endl << endl << endl;
	
	
	//Load config
	auto config = GetConfig();
	double temperature = stof(config["T"]);
	int iterations = stoi(config["Iterations"]);
	string AdjustTemp = config["AdjustTemp"];
	string Algorithm = config["Algorithm"];
	
	if (Algorithm!="flip" && Algorithm!="switch"){
		cout << "[ERROR] Invalid algorithm, use either switch or flip";
		return 1;
	}
	
	cout << "Temperature used: T=" << temperature << endl;
	cout << "Iterations used: " << iterations << endl;
	if (AdjustTemp=="0") cout << "Not adjusting temperature" << endl;
	else cout << "Adjusting temperature" << endl;
	cout << "Algorithm used: " << Algorithm << endl;
	
   	//Seed random number generator
	random_device rd;
	mt19937 random_number(rd());
			
	
	//Get cities and build distance table
    vector< vector<double> > Cities = GetCities();
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
	int alg_n = N/10;
	
	//create functions for RNG
	uniform_int_distribution<> GetRandomJ(0,N-1);
	uniform_real_distribution<> GetRandomX(0,1);
	
	//generate random permutation for distances
	shuffle(randPerm.begin(),randPerm.end(),random_number);
	cout << "Random route: ";
	for (auto el : randPerm){
		cout << el << " ";
	}
	cout << endl;
	
	//thermodynamic algorithm
	//STEP 1
	//c_k = s_k, calculate distance
	vector<int> c_k = randPerm;
	double length_before = TotalDistance(Distances,c_k);
	vector< pair<int,double> > *filewrite = new vector< pair<int,double> >(iterations);
	
	cout << "LENGTH BEFORE: " << length_before << endl;
	
	int TempCounter = 1;
	int alg_m = N;
	//STEP 2
	//first time set i=0, after increment by 1
	for (int it = 0;it < iterations;it++){
		//reduce temperature every 1/4 of iterations
		if (AdjustTemp!="0" && TempCounter!=0){
			if (it == (int)(round((float)(iterations)/4*TempCounter))){
				if (TempCounter==3){
					cout << "Now using step 3'" << endl;
					TempCounter=0;
				}
				else {
					temperature/=10;
					cout << "Reducing temperature, new temperature: " << temperature << endl;
					TempCounter++;
				}
			}
		}
		for (int alg_i = 0;alg_i<N;alg_i++){
			auto alg_j = alg_i;
			//STEP 3
			//generate random j
			if (TempCounter==0){
				while(alg_j==alg_i && (alg_m >= alg_n)){
					alg_j = GetRandomJ(random_number);
					alg_m = min({abs(alg_j-alg_i),abs(alg_j-alg_i+N),abs(alg_j-alg_i-N)});
				}
			}
			else {
				while (alg_j==alg_i){
					alg_j = GetRandomJ(random_number);
				}
			}
			auto i_tilde = min(alg_i,alg_j);
			auto j_tilde = max(alg_i,alg_j);
			
			//STEP 4
			//switch path
			vector<int> t_k;
			t_k.resize(N);
		
			if (Algorithm=="flip"){
				
				for (int k=0;k<i_tilde;k++){
					t_k[k] = c_k[k];
				}
			
				for (int k=0;k<j_tilde-i_tilde+1;k++){
					t_k[i_tilde+k] = c_k[j_tilde-k];
				}
				
				for (int k=j_tilde+1;k<N;k++){
					t_k[k] = c_k[k];
				}
			}
			
			else {
				
				t_k[i_tilde] = c_k[j_tilde];
				t_k[j_tilde] = c_k[i_tilde];
				for (int k=0;k<N;k++){
					if (k!=i_tilde && k!=j_tilde){
						t_k[k] = c_k[k];
					}
				}
			}
			
			//STEP 5
			//calculate distance after switching
			double length_after = TotalDistance(Distances,t_k);
			
			//STEP 6
			//check if distance improved, if not random chance to accept anyway
			if (length_after<length_before){
				c_k = t_k;
				length_before = length_after;
			}
			//STEP 7
			//accept new path
			else {
				double alg_x = GetRandomX(random_number);
				if (alg_x<exp((length_before-length_after)/temperature)){
					//STEP 7
					c_k = t_k;
					length_before = length_after;
				}
			}
		}
		if (it % 100 == 0){
			cout << it << " " << length_before << endl;
		}
		(*filewrite)[it] = (make_pair(it,length_before));
		
	}
	cout << "LENGTH AFTER: " << length_before;
	
	//write results to file
	ofstream outfile("log.txt");
	for (unsigned int i = 0;i<filewrite->size();i++){
		outfile << (*filewrite)[i].first << " " << (*filewrite)[i].second << endl;
	}
	outfile.close();
	
	ofstream outpath("path.txt");
	for (unsigned int i = 0;i<c_k.size();i++){
		outpath << c_k[i] << endl;
	}
	outpath.close();
	
    return 0;
}
