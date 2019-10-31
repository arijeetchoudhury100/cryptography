#include<stdio.h>
#include<stdlib.h>
#define N 10
void cofactor(float m[N][N],float temp[N][N],int p,int q,int n){
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
float det(float m[N][N],int n){
	int d = 0,t=0;
	if(n == 1)
		return m[0][0];
	float temp[N][N];
	int sign = 1;
	
	for(t=0;t<n;t++){
		cofactor(m,temp,0,t,n);
		d = d + sign*m[0][t]*det(temp,n-1);
		sign = -sign;
	}
	return d;
}
float calculateCofactor(float m[N][N],int p,int q,int n){
	int row,col,res,i=0,j=0,sign=1; 
	float cof[N][N];
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
int main(){
	float m[N][N],c[N][N],adj[N][N],d,inv[N][N];
	int i,j,n,sign=1;
	printf("Enter size of the matrix:\n");
	scanf("%d",&n);
	printf("Enter matrix values:\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%f",&m[i][j]);
	//calculate determinant
	d = det(m,n);
	if(d == 0){
		printf("Matrix not invertible\n");
		return -1;
	}
	printf("Determinant: %f\n",d);
	
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
			printf("%f ",c[i][j]);
		printf("\n");
	}
	//find adjoint
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			adj[i][j] = c[j][i];
	}
	printf("Adjoint matrix: \n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			printf("%f ",adj[i][j]);
		printf("\n");
	}
	//calculate inverse
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			inv[i][j] = (float)(adj[i][j]/d);
	}
	printf("Inverse matrix: \n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			printf("%f ",inv[i][j]);
		printf("\n");
	}
	return 0;
}

