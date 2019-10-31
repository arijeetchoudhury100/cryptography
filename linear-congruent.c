#include<stdio.h>
int gcd(int,int);
int findInverse(int,int);
int main(){
	int a,b,n,d,a1,b1,n1,a_inv,k,x0;
	printf("Enter a,b and n:\n");
	scanf("%d%d%d",&a,&b,&n);
	d = gcd(a,n);
	if(b%d == 0){
		//d solutions exist
		a1 = a/d;
		b1 = b/d;
		n1 = n/d;
		a_inv = findInverse(n1,a1);
		x0 = (b1*a_inv)%n1;
		for(k=0;k<d;k++){
			printf("Solution %d: %d\n",k+1,x0+k*(n/d));
		}
	}
	else
		printf("No Solutions..\n");
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
}
