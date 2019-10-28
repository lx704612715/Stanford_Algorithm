#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<sstream>
#include <typeinfo>
#include<ctime>
#include<cstdlib>
using namespace std;

vector<vector<int> > create_graph(char* path){
    ifstream inFile(path);
    string line;
    vector<vector<int> > file(201);
    while (getline(inFile, line)){
        int value;
        std::stringstream ss(line);   
        bool first_element = true;
        int v = 0;
        while (ss >> value){
            if(first_element){
                v = value;
                first_element = false;
            }
            else {
                file[v].push_back(value); 
            }
        };  
    };
    inFile.close();
    return file;
}

int MinCut(vector<vector<int> > adjlist, int &V){
    while(V>2){
        int ran_u = 0;
        int ran_v = 0;
        do{
            srand(int(time(0)));
            ran_u = rand()%199+1;
            int size = adjlist[ran_u].size();
            int temp = rand()%size;
            ran_v = adjlist[ran_u][temp];
        }while(adjlist[ran_u][0]==0);
        for (int i=0; i<adjlist[ran_u].size(); i++){
            if(adjlist[ran_u][i] != ran_v){
                adjlist[ran_v].push_back(adjlist[ran_u][i]);
                adjlist[adjlist[ran_u][i]].push_back(ran_v);
            }
        }
        for (int j=1; j<adjlist.size(); j++){
            if(j != ran_u){
                for (int k=0; k<adjlist[j].size(); k++){
                    if(adjlist[j][k] == ran_u){
                        adjlist[j].erase(adjlist[j].begin()+k);
                    }
                }
            }
        }
        adjlist[ran_u][0]=0;
        V--;
    }
    int min_cut = 100;
    for(int n=1; n<=200; n++){
        if(adjlist[n][0] > 0){
            int temp = adjlist[n].size();
            if(temp < min_cut){
                min_cut = temp;
            }
        }
    }
    return min_cut;
};
int main(int argc, char const *argv[]){
    char* path = "kargerMinCut.txt";
    int V = 200;
    vector <vector<int> > adjlist(201);
    adjlist = create_graph(path);
    int min_cut = 100;
    for(int i=0; i<200; i++){
        int temp = MinCut(adjlist, V);
        if (temp < min_cut){
            min_cut = temp;
        }
    }
    cout << "min_cut is" << min_cut << endl;
    return 0;
}