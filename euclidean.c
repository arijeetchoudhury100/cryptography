#include<stdio.h>
int gcd(int,int);

int main(){
	int a,b,res;
	printf("Enter the numbers\n");
	scanf("%d%d",&a,&b);
	res = gcd(a,b);
	printf("GCD of %d and %d is: %d\n",a,b,res);
	return 0;
}

int gcd(int a,int b){
	int r1 = a,r2 = b,r,q;
	while(r2>0){
		q = r1/r2;
		r = r1-q*r2;
		r1 = r2;
		r2 = r;
	}
	return r1;
}
