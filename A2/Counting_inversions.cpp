#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
using namespace std;
vector<double> read_file(char* path){
    ifstream inFile(path);
    vector <double> file;
    double x;
    while (inFile >> x){
        file.push_back(x);
    } 
    inFile.close();
    return file;
};

int merge(vector<double> &A, vector<double> temp, int left, int mid, int right){
    unsigned int inv_count = 0;
    int L = left;
    int R = mid;
    int tmp_index = left;
    while ((L<=mid-1) && (R<=right)){
        if(A[L] < A[R]){
            temp[tmp_index++] = A[L++];
        }
        if(A[R] < A[L]){
            temp[tmp_index++] = A[R++];
            inv_count = inv_count + (mid - L);
        }
    }
    while (L<=mid-1){
        temp[tmp_index++] = A[L++];
    }
    while (R<=right){
        temp[tmp_index++] = A[R++];
    }
    for (int i = left; i <= right; i++) 
        A[i] = temp[i]; 
    return inv_count;
};

int merge_sort(vector<double> &A, vector<double> temp, int left, int right)
{
    unsigned int mid, inv_count = 0;
    if(left<right){
        mid = (left + right)/2;
        inv_count += merge_sort(A, temp, left, mid);
        inv_count += merge_sort(A, temp, mid+1, right);
        inv_count += merge(A, temp, left, mid+1, right);
    }   
    return inv_count;
}
int main()
{
    char* path = "IntegeArray.txt";
    vector <double> file;
    file = read_file(path);
    int len = static_cast<int>(file.size());
    unsigned int inv_count = 0;
    vector<double> temp = file;
    inv_count = merge_sort(file, temp, 0, len-1);
    cout << "answer is " << inv_count << endl;
    return 0;
}