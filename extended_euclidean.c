#include<stdio.h>
void gcd(int,int,int[]);

int main(){
	int a,b,res[3]={0};
	printf("Enter the numbers\n");
	scanf("%d%d",&a,&b);
	gcd(a,b,res);
	printf("GCD of %d and %d is: %d\n",a,b,res[0]);
	printf("Value of s: %d\n",res[1]);
	printf("Value of t: %d\n",res[2]);
	return 0;
}

void gcd(int a,int b,int res[]){
	int r1 = a,r2 = b,s1 = 1,s2 = 0,t1 = 0,t2 = 1,r,q,s,t;
	while(r2>0){
		q = r1/r2;
		r = r1-q*r2;
		r1 = r2;
		r2 = r;

		t = t1-q*t2;
		t1 = t2;
		t2 = t;

		s = s1-q*s2;
		s1 = s2;
		s2 = s;	
	}
	res[0] = r1;
	res[1] = s1;
	res[2] = t1;
}
