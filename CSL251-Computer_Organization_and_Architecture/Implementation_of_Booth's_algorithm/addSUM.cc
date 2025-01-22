#include<bits/stdc++.h>
using namespace std;

vector<bool> addSUM(vector<bool> &A,vector<bool> &B,char op){
   int n = A.size();
   vector <bool> result(n+1,0);
   bool carryB=0;
   
   if(op=='+'){
             bool carry = 0;
            for (int i = n-1; i >= 0; --i) {
               bool sum = A[i] ^ B[i] ^ carry;
               carry = (A[i] & B[i]) | (A[i] & carry) | (B[i] & carry);
               result[i+1] = sum;
               if(i==1)carryB=carry;
            }
            result[0]=!(carry^carryB);
            return result;
   }
   else {
            bool carry = 1;
             for (int i = n-1; i >= 0; --i) {
               bool sum = A[i] ^ !B[i] ^ carry;
               carry = (A[i] & !B[i]) | (A[i] & carry) | (!B[i] & carry);
               result[i+1] = sum;
               if(i==1)carryB=carry;
            } 
            result[0]=!(carry^carryB);  
            return result;

   }
}

int main(){
     int n;
    cout << "Enter the size of bitsets (n): ";
    cin >> n;

    string b1, b2;
    cout << "1st binary number : ";
    cin >> b1;
    cout << "2nd binary number: ";
    cin >> b2;

    char op;
    cout<<"enter the operation"<<endl;
    cin>>op;

 
    if (b1.length() != n || b2.length() != n) {
        cout << "Error: Binary numbers must be of size " << n << endl;
        return 1;
    }

    
    vector<bool> A(n), B(n), result(n+1, 0); 
    for (int i = 0; i < n; ++i) {
        A[i] = b1[i] - '0';
        B[i] = b2[i] - '0';
    }

   result= addSUM(A,B,op);

    for (bool bit : result) {
        cout << bit;
    }
    cout << endl;
   return 0;
}