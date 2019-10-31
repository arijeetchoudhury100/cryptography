// C++ program to find adjoint and inverse of a matrix 
#include<bits/stdc++.h> 
using namespace std; 
#define N 100


int detInverse(int d)
{
    int q,r1=26,r2=d,r,t1=0,t2=1,t;
    while(r2>0)
    {
        q = r1/r2;
        
        r = r1-q*r2;
        r1 = r2;
        r2 = r;

        t = t1-q*t2;
        t1 = t2;
        t2 = t;
    }
    if(r1 == 1)
    {
        while(t1<0)
            t1 += 26;
        return t1;
    }
    return -1;
}
// Function to get cofactor of A[p][q] in temp[][]. n is current 
// dimension of A[][] 
void getCofactor(int A[N][N], int temp[N][N], int p, int q, int n) 
{ 
	int i = 0, j = 0; 

	// Looping for each element of the matrix 
	for (int row = 0; row < n; row++) 
	{ 
		for (int col = 0; col < n; col++) 
		{ 
			// Copying into temporary matrix only those element 
			// which are not in given row and column 
			if (row != p && col != q) 
			{ 
				temp[i][j++] = A[row][col]; 

				// Row is filled, so increase row index and 
				// reset col index 
				if (j == n - 1) 
				{ 
					j = 0; 
					i++; 
				} 
			} 
		} 
	} 
} 

/* Recursive function for finding determinant of matrix. 
n is current dimension of A[][]. */
int determinant(int A[N][N], int n) 
{ 
	int D = 0; // Initialize result 

	// Base case : if matrix contains single element 
	if (n == 1) 
		return A[0][0]; 

	int temp[N][N]; // To store cofactors 

	int sign = 1; // To store sign multiplier 

	// Iterate for each element of first row 
	for (int f = 0; f < n; f++) 
	{ 
		// Getting Cofactor of A[0][f] 
		getCofactor(A, temp, 0, f, n); 
		D += sign * A[0][f] * determinant(temp, n - 1); 

		// terms are to be added with alternate sign 
		sign = -sign; 
	} 

	return D; 
} 

// Function to get adjoint of A[N][N] in adj[N][N]. 
void adjoint(int A[N][N],int adj[N][N],int size) 
{ 
	if (size == 1) 
	{ 
		adj[0][0] = 1; 
		return; 
	} 

	// temp is used to store cofactors of A[][] 
	int sign = 1, temp[N][N]; 

	for (int i=0; i<size; i++) 
	{ 
		for (int j=0; j<size; j++) 
		{ 
			// Get cofactor of A[i][j] 
			getCofactor(A, temp, i, j, size); 

			// sign of adj[j][i] positive if sum of row 
			// and column indexes is even. 
			sign = ((i+j)%2==0)? 1: -1; 

			// Interchanging rows and columns to get the 
			// transpose of the cofactor matrix 
			adj[j][i] = (sign)*(determinant(temp, size-1)); 
		} 
	} 
} 

// Function to calculate and store inverse, returns false if 
// matrix is singular 
bool inverse(int A[N][N], float inverse[N][N],int size) 
{ 
	// Find determinant of A[][] 
	int det = determinant(A,size);
    while(det<0)
        det += 26;
    int d_inv = detInverse(det); 
	if (d_inv == -1) 
	{ 
		cout << "Inverse of the matrix doesn't exist"; 
		return false; 
	} 

	// Find adjoint 
	int adj[N][N]; 
	adjoint(A,adj,size); 

    for (int i=0; i<size; i++) 
		for (int j=0; j<size; j++) 
		{
            while(adj[i][j] < 0)   
                adj[i][j] += 26;
            adj[i][j] = adj[i][j] % 26;
        }	 
 
	for (int i=0; i<size; i++) 
		for (int j=0; j<size; j++) 
			inverse[i][j] = (adj[i][j] * d_inv) % 26; 

	return true; 
} 

template<class T> 
void display(T A[N][N],int size) 
{ 
	for (int i=0; i<size; i++) 
	{ 
		for (int j=0; j<size; j++) 
			cout << A[i][j] << " "; 
		cout << endl; 
	} 
} 

// Driver program 
int main() 
{ 
	int A[N][N],size;
	int adj[N][N]; // To store adjoint of A[][] 
	float inv[N][N]; // To store inverse of A[][] 
    cout<<"Enter size of the matrix"<<endl;
    cin>>size;
    cout<<"Enter the matrix"<<endl;
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            cin>>A[i][j];
	cout << "Input matrix is :\n"; 
	display(A,size);

	cout << "\nThe Inverse is :\n"; 
	if (inverse(A,inv,size)) 
		display(inv,size); 
	return 0; 
} 
