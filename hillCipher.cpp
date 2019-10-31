#include<iostream>
#include<cstdlib>
#include<cmath>
#include<cstring>
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
bool inverse(int A[N][N], int inverse[N][N],int size) 
{ 
	// Find determinant of A[][] 
	int det = determinant(A,size);
    while(det<0)
        det += 26;
    int d_inv = detInverse(det); 
	if (d_inv == -1) 
		return false;

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

char* encrypt(char *msg,int key[N][N],int size)
{
    int num_rows = ceil(strlen(msg)/float(size));
    int msgmatrix[num_rows][size],i=0,j=0;
    int ciphermatrix[num_rows][size];

    for(int k=0;k<strlen(msg);k++)
    {   
        msgmatrix[i][j] = msg[k]-'A';
        j = j+1;
        if(j == size)
        {
            i = i+1;
            j = 0;
        }
    }
    if(j != 0)
    {
        while(j != size)
            msgmatrix[i][j++] = 25;
    }
    cout<<"The message matrix is:"<<endl;
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<size;j++){
            cout<<msgmatrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"The key matrix is:"<<endl;
    display(key,size);

    for(int i=0;i<num_rows;i++){
        for(int j=0;j<size;j++){
            ciphermatrix[i][j]=0;
            for(int k=0;k<size;k++){
                ciphermatrix[i][j] += msgmatrix[i][k] * key[k][j];
            }
            ciphermatrix[i][j] %= 26;
        }
    }

    cout<<"The cipher matrix is:"<<endl;
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<size;j++){
            cout<<ciphermatrix[i][j]<<" ";
        }
        cout<<endl;
    }
    int in = 0;
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<size;j++){
            msg[in++] = ciphermatrix[i][j] + 'A';
        }
    }
    msg[in] = '\0';
    return msg;
}
char* decrypt(char *msg,int key_inv[N][N],int size)
{
    int num_rows = ceil(strlen(msg)/float(size));
    int ciphermatrix[num_rows][size],i=0,j=0;
    int msgmatrix[num_rows][size];

    for(int k=0;k<strlen(msg);k++)
    {   
        ciphermatrix[i][j] = msg[k]-'A';
        j = j+1;
        if(j == size)
        {
            i = i+1;
            j = 0;
        }
    }
    
    cout<<"The cipher matrix is:"<<endl;
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<size;j++){
            cout<<ciphermatrix[i][j]<<" ";
        }
        cout<<endl;
    }

    for(int i=0;i<num_rows;i++){
        for(int j=0;j<size;j++){
            msgmatrix[i][j]=0;
            for(int k=0;k<size;k++){
                msgmatrix[i][j] += ciphermatrix[i][k] * key_inv[k][j];
            }
            msgmatrix[i][j] %= 26;
        }
    }

    cout<<"The message matrix is:"<<endl;
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<size;j++){
            cout<<msgmatrix[i][j]<<" ";
        }
        cout<<endl;
    }
    int in = 0;
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<size;j++){
            msg[in++] = msgmatrix[i][j] + 'A';
        }
    }
    msg[in] = '\0';
    return msg;
}
// Driver program 
int main() 
{ 
    char msg[N],*cipher,*plain;
	int key[N][N],size;
	int adj[N][N]; // To store adjoint of A[][] 
	int inv[N][N]; // To store inverse of A[][] 
    
    cout<<"Enter size of the key"<<endl;
    cin>>size;
    cout<<"Enter the key matrix"<<endl;
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            cin>>key[i][j];
 
	if (!inverse(key,inv,size)) 
	{
        cout<<"Inverse of the key doesn't exist";
        exit(0);
    }
    cout<<"Inverse of the key is:"<<endl;	
    display(inv,size);

    cout<<"Enter the message to be sent"<<endl;
    cin>>msg; 

    cipher = encrypt(msg,key,size);
    cout<<"Encrypted message is: "<<cipher<<endl;

    plain = decrypt(cipher,inv,size);
    cout<<"Decrypted message is: "<<plain<<endl;
	return 0; 
} 
