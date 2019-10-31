#include<stdio.h>
int gcd(int,int);
void solve(int,int);
int res[2]={0};
int main(){
	int a,b,c,d,a1,b1,x0,y0,k=0;
	printf("Enter the coefficients a,b and result c..ax+by=c\n");
	scanf("%d%d%d",&a,&b,&c);
	d = gcd(a,b);
	a1 = a/d;
	b1 = b/d;
	if(c%d!=0)
	{
		printf("No solution\n");
		return -1;
	}
	printf("Solving a's+b't=1\n");
	solve(a1,b1);
	x0 = (c/d)*res[0];
	y0 = (c/d)*res[1];
	printf("General solution is:\nx= %d+k%d\ny=%d-k%d\n",x0,b/d,y0,a/d);
	for(k=0;k<5;k++)
	{
		printf("Solution %d: (%d,%d)\n",(k+1),x0+k*(b/d),y0-k*(a/d));
	}
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
void solve(int a,int b){
	int q,r1,r2,r,s1=1,s2=0,t1=0,t2=1,t,s;
	r1 = a;
	r2 = b;
	while(r2>0){
		q = r1/r2;
		r = r1-q*r2;
		r1 = r2;
		r2 = r;
		
		s = s1-q*s2;
		s1 = s2;
		s2 = s;
	
		t = t1-q*t2;
		t1 = t2;
		t2 = t;	
	}
	res[0] = s1;
	res[1] = t1;
}
