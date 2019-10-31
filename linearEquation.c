#include<stdio.h>
#define N 10
void cofactor(int m[N][N],int temp[N][N],int p,int q,int n){
	int row,col,i=0,j=0;
	for(row=0;row<n;row++){
		for(col=0;col<n;col++){
			if(row!=p && col!=q){
				temp[i][j++] = m[row][col];
				if(j == (n-1)){
					j = 0;
					i++;
				}
			}
		}
	}
}
int det(int m[N][N],int n){
	int d = 0,t=0;
	if(n == 1)
		return m[0][0];
	int temp[N][N];
	int sign = 1;
	
	for(t=0;t<n;t++){
		cofactor(m,temp,0,t,n);
		d = d + sign*m[0][t]*det(temp,n-1);
		sign = -sign;
	}
	return d;
}
int calculateCofactor(int m[N][N],int p,int q,int n){
	int row,col,res,i=0,j=0,sign=1; 
	int cof[N][N];
	for(row=0;row<n;row++){
		for(col=0;col<n;col++){
			if(row!=p && col!=q){
				cof[i][j++] = m[row][col];
				if(j == (n-1)){
					j = 0;
					i++;
				}
			}
		}
	}
	return det(cof,n-1);
}
int findInverse(int n,int a){
	int q,r1,r2,r,t1=0,t2=1,t;
	r1 = n;
	r2 = a;
	while(r2>0){
		q = r1/r2;
		r = r1-q*r2;
		r1 = r2;
		r2 = r;
	
		t = t1-q*t2;
		t1 = t2;
		t2 = t;	
	}
	if(r1 == 1){
		while(t1<0){
			t1 = t1 + n;
		}
		return t1;
	}
	return -1;
}
int main(){
	int m[N][N],c[N][N],adj[N][N],b[N],d,inv[N][N],res[N]={0};
	int i,j,n,sign=1,mod,d_inv;
	printf("Enter no. of variables:\n");
	scanf("%d",&n);
	printf("Enter coefficient values:\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&m[i][j]);
	printf("Enter b-matrix:\n");
	for(i=0;i<n;i++)
		scanf("%d",&b[i]);
	printf("Enter modulo value:\n");
	scanf("%d",&mod);
	//calculate determinant
	d = det(m,n);
	while(d<0)
		d = d+mod;
	//check if inverse of determinant exists
	d_inv = findInverse(mod,d);
	
	if(d_inv == -1){
		printf("Matrix not invertible\n");
		return -1;
	}
	printf("Determinant: %d\n",d);
	
	//calculate cofactor
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			c[i][j] = sign*calculateCofactor(m,i,j,n);
			sign = -sign;
		}
	}
	printf("Cofactor matrix: \n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			printf("%d ",c[i][j]);
		printf("\n");
	}
	//find adjoint
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			adj[i][j] = c[j][i];
			while(adj[i][j]<0)
				adj[i][j] += mod;
			adj[i][j] = adj[i][j]%mod;
		}
	}
	printf("Adjoint matrix: \n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			printf("%d ",adj[i][j]);
		printf("\n");
	}
	//calculate inverse
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			inv[i][j] = (adj[i][j]*d_inv)%mod;
	}
	printf("Inverse matrix: \n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			printf("%d ",inv[i][j]);
		printf("\n");
	}
	//calculate final result
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			res[i] = res[i]+inv[i][j]*b[j];
		}			
		res[i] = res[i]%mod;
	}
	printf("Result: \n");
	for(i=0;i<n;i++){
		printf("%d\n",res[i]);
	}
	return 0;
}

