#include<iostream>
#include<fstream>
#include<vector>
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
        int num_comp = 1;
        void setValue(vector<double> a, int len);
        void quicksort(vector<double> &a, int leftEnd, int RightEnd);
        double select_pivot(vector<double> a, int leftEnd, int RightEnd);
};

void QuickSort::setValue(vector<double> a, int len){
    this-> input = a;
    this-> size = len;
}

void QuickSort::quicksort(vector<double> &a, int leftEnd, int RightEnd){
    if(leftEnd >= RightEnd) return;

    int leftCursor = leftEnd, rightCursor = RightEnd;
    double pivot = select_pivot(a, leftEnd, RightEnd);

    while(true){
        while(a[leftCursor]<pivot && this->num_comp++){
            leftCursor++;
        }
         while(a[rightCursor]>pivot && this->num_comp++){
            rightCursor--;
        }
        if(leftCursor>=rightCursor) break;
        swap(a[leftCursor], a[rightCursor]);
    }
    a[rightCursor] = pivot;
    this->quicksort(a, leftEnd, rightCursor-1);
    this->quicksort(a, rightCursor+1, RightEnd);
}

double QuickSort::select_pivot(vector<double> a, int leftEnd, int RightEnd){
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
