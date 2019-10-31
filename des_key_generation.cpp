//key generation for des algorithm
#include<bits/stdc++.h>
using namespace std;

void genkey(bool*,bool[][48]);
void shiftleft(bool*,int);
void combine(bool*,bool*,bool*);
void convertbinary(char*,bool*);
void converthex(bool[][48],char[][16]);
bool pkey[56] = {0};
int pdrop[56] = {57,49,41,33,25,17,9,1,
		58,50,42,34,26,18,10,2,
		59,51,43,35,27,19,11,3,
		60,52,44,36,63,55,47,39,
		31,23,15,7,62,54,46,38,
		30,22,14,6,61,53,45,37,
		29,21,13,5,28,20,12,4};

int cdbox[48] = {14,17,11,24,1,5,3,28,
		15,6,21,10,23,19,12,4,
		26,8,16,7,27,20,13,2,
		41,52,31,37,47,55,30,40,
		51,45,33,48,44,49,39,56,
		34,53,46,42,50,36,29,32};

int main(){
	bool key[64]={0},msg[64],roundkey[16][48]={0};
	char m[16],hexkeys[16][16]={0};
	int k=0;
	cout<<"enter the key(in hexadecimal):"<<endl;
	cin>>m;
	convertbinary(m,key);
	cout<<endl;
	//get key for 16 rounds in roundkey
	genkey(key,roundkey);
	converthex(roundkey,hexkeys);
	cout<<"the round keys are: "<<endl;
	for(int i=0;i<16;i++){
		for(int j=0;j<16;j++)
			cout<<hexkeys[i][j];
		cout<<endl;	
	}
	return 0;
}
void genkey(bool *key,bool roundkey[16][48]){
	int num_shift[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
	bool left[28],right[28];

	//perform parity drop and permute, pkey holds the 56-bit key
	bool comb[56] = {0};
	for(int i=0;i<56;i++)
		pkey[i] = key[pdrop[i]-1];
	for(int i=0;i<28;i++)
		left[i] = pkey[i];
	for(int i=28;i<56;i++)
		right[i-28] = pkey[i];

	//perform shifting, rounds 1,2,9,16->1-bit shift, rest->2-bit shift followed by key compression
	for(int i=0;i<16;i++){
		shiftleft(left,num_shift[i]);
		shiftleft(right,num_shift[i]);
		combine(left,right,comb);
		//compression d-box
		for(int j=0;j<48;j++){
			roundkey[i][j] = comb[cdbox[j]-1];
		}
	}
}
void shiftleft(bool* arr,int d){
	for(int i=1;i<=d;i++){
		int t = arr[0];
		for(int j=1;j<28;j++)
			arr[j-1] = arr[j];
		arr[27] = t;
	}
}
void combine(bool* left,bool* right,bool* comb){
	for(int i=0;i<28;i++)
		comb[i] = left[i];
	for(int i=28;i<56;i++)
		comb[i] = right[i-28];
}
void convertbinary(char *m,bool* key){
	int k=0;
	for(int i=0;i<strlen(m);i++){
		if(m[i]=='A'){
			key[k]=1;key[k+1]=0;key[k+2]=1;key[k+3]=0;}
		else if(m[i]=='B'){
			key[k]=1;key[k+1]=0;key[k+2]=1;key[k+3]=1;}
		else if(m[i]=='C'){
			key[k]=1;key[k+1]=1;key[k+2]=0;key[k+3]=0;}
		else if(m[i]=='D'){
			key[k]=1;key[k+1]=1;key[k+2]=0;key[k+3]=1;}
		else if(m[i]=='E'){
			key[k]=1;key[k+1]=1;key[k+2]=1;key[k+3]=0;}
		else if(m[i]=='F'){
			key[k]=1;key[k+1]=1;key[k+2]=1;key[k+3]=1;}
		else if(m[i]=='0'){
			key[k]=0;key[k+1]=0;key[k+2]=0;key[k+3]=0;}
		else if(m[i]=='1'){
			key[k]=0;key[k+1]=0;key[k+2]=0;key[k+3]=1;}
		else if(m[i]=='2'){
			key[k]=0;key[k+1]=0;key[k+2]=1;key[k+3]=0;}
		else if(m[i]=='3'){
			key[k]=0;key[k+1]=0;key[k+2]=1;key[k+3]=1;}
		else if(m[i]=='4'){
			key[k]=0;key[k+1]=1;key[k+2]=0;key[k+3]=0;}
		else if(m[i]=='5'){
			key[k]=0;key[k+1]=1;key[k+2]=0;key[k+3]=1;}
		else if(m[i]=='6'){
			key[k]=0;key[k+1]=1;key[k+2]=1;key[k+3]=0;}
		else if(m[i]=='7'){
			key[k]=0;key[k+1]=1;key[k+2]=1;key[k+3]=1;}
		else if(m[i]=='8'){
			key[k]=1;key[k+1]=0;key[k+2]=0;key[k+3]=0;}
		else{
			key[k]=1;key[k+1]=0;key[k+2]=0;key[k+3]=1;}
		k = k+4;
	}
}
void converthex(bool roundkey[16][48],char hexkeys[16][16]){
	int k;	
	for(int i=0;i<16;i++)
	{
		k=0;
		for(int j=0;j<48;j=j+4){
			if(roundkey[i][j]==1 && roundkey[i][j+1]==0 && roundkey[i][j+2]==1 && roundkey[i][j+3]==0){
				hexkeys[i][k]='A';			
			}
			else if(roundkey[i][j]==1 && roundkey[i][j+1]==0 && roundkey[i][j+2]==1 && roundkey[i][j+3]==1){
				hexkeys[i][k]='B';			
			}
			else if(roundkey[i][j]==1 && roundkey[i][j+1]==1 && roundkey[i][j+2]==0 && roundkey[i][j+3]==0){
				hexkeys[i][k]='C';			
			}
			else if(roundkey[i][j]==1 && roundkey[i][j+1]==1 && roundkey[i][j+2]==0 && roundkey[i][j+3]==1){
				hexkeys[i][k]='D';			
			}
			else if(roundkey[i][j]==1 && roundkey[i][j+1]==1 && roundkey[i][j+2]==1 && roundkey[i][j+3]==0){
				hexkeys[i][k]='E';			
			}
			else if(roundkey[i][j]==1 && roundkey[i][j+1]==1 && roundkey[i][j+2]==1 && roundkey[i][j+3]==1){
				hexkeys[i][k]='F';			
			}
			else if(roundkey[i][j]==0 && roundkey[i][j+1]==0 && roundkey[i][j+2]==0 && roundkey[i][j+3]==0){
				hexkeys[i][k]='0';			
			}
			else if(roundkey[i][j]==0 && roundkey[i][j+1]==0 && roundkey[i][j+2]==0 && roundkey[i][j+3]==1){
				hexkeys[i][k]='1';			
			}
			else if(roundkey[i][j]==0 && roundkey[i][j+1]==0 && roundkey[i][j+2]==1 && roundkey[i][j+3]==0){
				hexkeys[i][k]='2';			
			}
			else if(roundkey[i][j]==0 && roundkey[i][j+1]==0 && roundkey[i][j+2]==1 && roundkey[i][j+3]==1){
				hexkeys[i][k]='3';			
			}
			else if(roundkey[i][j]==0 && roundkey[i][j+1]==1 && roundkey[i][j+2]==0 && roundkey[i][j+3]==0){
				hexkeys[i][k]='4';			
			}
			else if(roundkey[i][j]==0 && roundkey[i][j+1]==1 && roundkey[i][j+2]==0 && roundkey[i][j+3]==1){
				hexkeys[i][k]='5';			
			}
			else if(roundkey[i][j]==0 && roundkey[i][j+1]==1 && roundkey[i][j+2]==1 && roundkey[i][j+3]==0){
				hexkeys[i][k]='6';			
			}
			else if(roundkey[i][j]==0 && roundkey[i][j+1]==1 && roundkey[i][j+2]==1 && roundkey[i][j+3]==1){
				hexkeys[i][k]='7';			
			}
			else if(roundkey[i][j]==1 && roundkey[i][j+1]==0 && roundkey[i][j+2]==0 && roundkey[i][j+3]==0){
				hexkeys[i][k]='8';			
			}
			else if(roundkey[i][j]==1 && roundkey[i][j+1]==0 && roundkey[i][j+2]==0 && roundkey[i][j+3]==1){
				hexkeys[i][k]='9';			
			}
			k = k+1;	
		}
	}
}
