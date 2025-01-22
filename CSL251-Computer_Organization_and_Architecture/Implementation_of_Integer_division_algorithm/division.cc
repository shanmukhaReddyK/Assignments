#include <iostream>
#include <vector>
using namespace std;


vector<bool> addSUM(vector<bool> &A,vector<bool> &B,char op){
   int n = A.size();
   vector <bool> result(n+1,0);
   bool carryB=0;// last before carry
   
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


void arithmeticleftShift(vector<bool>& A, vector<bool>& Q) {
    bool msb = Q[0];
    Q.erase(Q.begin());
    Q.insert(Q.end(), A[0]);
    A.erase(A.begin());
    A.insert(A.end(), msb);
}

int main() {
    int n;
    cout << "Enter the size of bitsets (n): ";
    cin >> n;

    string b1, b2; //b1 is binary string of M and b2 is binary string of Q
    cout << "1st binary number (Divisor): ";
    cin >> b1;
    cout << "2nd binary number (Dividend): ";
    cin >> b2;

 
    if (b1.length() != n || b2.length() != n) {
        cout << "Error: Binary numbers must be of size " << n << endl;
        return 1;
    }

    
    vector<bool> M(n), Q(n), A(n, 0); 
    for (int i = 0; i < n; ++i) {
        M[i] = b1[i] - '0';
        Q[i] = b2[i] - '0';
    }

    cout << "\nPerforming Division...\n";

    for (int count = 0; count < n; ++count) {  

        arithmeticleftShift(A, Q);

        A=addSUM(A,M,'-');
        A.erase(A.begin());  //removing the extra bit

        if(A[0]==1){

            Q[Q.size()-1]=0;
            A = addSUM(A, M,'+');
            A.erase(A.begin());  //removing the extra bit   

        }

        else{

            Q[Q.size()-1]=1;

        }    
    }
    
    cout << "\nRemainder (in binary): ";
    for (bool bit : A) {
        cout << bit;
    }

    cout << "\nQuotient (in binary): ";
    for (bool bit : Q) {
        cout << bit;
    }
    cout << endl;

    return 0;
}
