#include<iostream>
#include<fstream>
#include<vector>
#include <algorithm>
using namespace std;
vector<double> read_file(char* path){
    ifstream inFile(path);
    vector<double> file;
    int x;
    while (inFile >> x){
        file.push_back(x);
    }
    inFile.close();
    return file;
}

class QuickSort{
    public:
        vector<double> input;
        int size;
        int num_comp = 0;
        void setValue(vector<double> a, int len);
        void quicksort(vector<double> &a, int leftEnd, int RightEnd);
        double select_pivot(vector<double> &a, int leftEnd, int RightEnd, bool median);
};

void QuickSort::setValue(vector<double> a, int len){
    this-> input = a;
    this-> size = len;
}

void QuickSort::quicksort(vector<double> &a, int leftEnd, int RightEnd){
    if(leftEnd >= RightEnd) return;
    int i = leftEnd+1;
    double pivot = select_pivot(a, leftEnd, RightEnd, true);
    for(int j= leftEnd+1; j<=RightEnd; j++){
        this->num_comp++;
        if(a[j] < pivot){
            swap(a[j], a[i]);
            i++;
        }
    }
    swap(a[leftEnd], a[i-1]);
    this->quicksort(a, leftEnd, i-2);
    this->quicksort(a, i, RightEnd);
}

double QuickSort::select_pivot(vector<double> &a, int leftEnd, int RightEnd, bool median){
    if(median==true){
        int middle = (leftEnd+RightEnd)/2;
        if ((a[middle]<=a[RightEnd]<a[leftEnd])||a[leftEnd]<=a[RightEnd]<a[middle])
            swap(a[RightEnd], a[leftEnd]);
        if ((a[leftEnd]<=a[middle]<a[RightEnd])||a[RightEnd]<=a[middle]<a[leftEnd])
            swap(a[middle], a[leftEnd]);
    }
    return a[leftEnd];
}

int main(int argc, char const *argv[])
{
/*     cout << "Quicksort" << endl; */
    char* path = "QuickSort.txt";
    vector<double> input = read_file(path);
    int len = static_cast<int>(input.size());
    QuickSort qs;
    qs.setValue(input, len);
    qs.quicksort(input, 0, len-1); 
    cout << "result is: " << qs.num_comp << endl;
    return 0;
}
