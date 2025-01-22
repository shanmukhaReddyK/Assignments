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


void arithmeticRightShift(vector<bool>& A, vector<bool>& Q, bool& q0) {
    bool msb = A[0];
    q0 = Q.back();
    Q.pop_back();
    Q.insert(Q.begin(), A.back());
    A.pop_back();
    A.insert(A.begin(), msb);
}

int main() {
    int n;
    cout << "Enter the size of bitsets (n): ";
    cin >> n;

    string b1, b2; //b1 is binary string of M and b2 is binary string of Q
    cout << "1st binary number (multiplicand): ";
    cin >> b1;
    cout << "2nd binary number (multiplier): ";
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

    bool q0 = 0; 

    cout << "\nPerforming Booth's Algorithm...\n";
    for (int i = 0; i < n; ++i) {
        if (Q.back() == 1 && q0 == 0) {
            A = addSUM(A,M,'-');

        } else if (Q.back() == 0 && q0 == 1) {
            A = addSUM(A, M,'+');
        }

        
        arithmeticRightShift(A, Q, q0);
    }

   
    vector<bool> result(2 * n, 0);// result is final answer
    for (int i = 0; i < n; ++i) {
        result[i] = A[i];
        result[n + i] = Q[i];
    }

    
    cout << "\nResult (in binary): ";
    for (bool bit : result) {
        cout << bit;
    }
    cout << endl;

    return 0;
}
