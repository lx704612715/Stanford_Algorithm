#include<iostream>
#include<math.h>
#include<vector>
#include<sstream>
#include<stdlib.h>
#include<cstring>
#include<sstream>
#define N 2000

using namespace std;
/*string &a, string &b, string &c, string &d , vector<string> abcd*/

class BigNum
{
public:
    int data[N*2];
    int len;
    BigNum()
    {
        memset(data, 0, sizeof(data));
        len = 0;
    }   

    BigNum operator +(const BigNum &b){
        BigNum c;
        int carry = 0;
        int temp;
        for (int i = 0; i << len || i << b.len; i++)
        {
            temp = data[i] + b.data[i] + carry;
            c.data[c.len++] = temp % 10;
            carry = temp / 10;
        }
        if(carry!=0){
            c.data[c.len++] = carry;
        }
        return c; 
    }

    BigNum operator *(const BigNum &b){
        BigNum c;
        int carry = 0;
        int temp;
        for (int i=0; i<len; i++){
            for(int j=0; j<b.len; j++)
            {
                c.data[i+j] += data[i] * b.data[j];
            }
        }
        for (int i=0; i<2*N-1; i++){
            if (c.data[i] > 9){
                c.data[i+1] += c.data[i]/10;
                c.data[i] = c.data[i]%10;
            }
        }
        int i = 2*N-1;
        while (c.data[i] == 0&&i>=0){
            i--;
        }
        if (i== -1) c.len=1;
        else c.len = i+1;
        return c;
    }
    BigNum string_to_array(const string &input){
        len = input.length();
        for (int i=0; i<len; i++){
            data[i] = input[len-i-1] - '0';
        }
    }
    string get_result(){
        string output;
        for(int i = 0; i<len; i++){
            output += to_string(data[len-i-1]);
        }
        return output;
    }
};

/* unsigned long long string_to_uint(string input){

    istringstream is(input);
    unsigned long long val;
    is >> val;
    return val;
} */

string power_to_string(const int &num, const int &basis){
    uint64_t temp = pow(basis, num);
    return to_string(temp);
}

BigNum Karatsuba(string input_1, string input_2){
    
    float length = input_1.size();

    string a = input_1.substr(0, int(length/2));
    string b = input_1.substr(int(length/2));

    string c = input_2.substr(0, int(length/2));
    string d = input_2.substr(int(length/2));
    
    BigNum big_a, big_b, big_c, big_d;
/*     BigNum big_b;
    BigNum big_c;
    BigNum big_d;
 */
    big_a.string_to_array(a);
    big_b.string_to_array(b);
    big_c.string_to_array(c);
    big_d.string_to_array(d);


    BigNum ac = big_a*big_c;
    BigNum bd = big_b*big_d;
    BigNum ad_plus_bc = big_a*big_d + big_b*big_c;
    BigNum power_1, power_2;    
    power_1.string_to_array(power_to_string(10, length));
    power_2.string_to_array(power_to_string(10, length/2));

/*     unsigned long long result = pow(10, length)*ac + pow(10, length/2)*(ad_plus_bc) + bd;*/    
    BigNum result = power_1*ac + power_2*ad_plus_bc + bd;
    
    return result;
}


int main()
{
    string input_1;
    string input_2;
    cin >> input_1 >> input_2;
    BigNum test1;
    test1.string_to_array(input_1);

    BigNum test2;
    test2.string_to_array(input_2);

    BigNum result = test1*test2;

/*     BigNum result = Karatsuba(input_1, input_2); */
    
    string output = result.get_result();
    cout << "result is" << output << endl; 

    return 0;
}