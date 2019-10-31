#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char* encrypt(char*,int,int);
char* decrypt(char*);
int inverse(int);

int main(){
	char msg[100],*cipher,*plain;
	srand(time(NULL));
	int key1 = rand()%26;	//multiplicative
	int key2 = rand()%26;	//additive
	if(key1 == 0)
		key1++;
	if(key2 == 0)
		key2++;
	printf("Generated key1=%d\n",key1);
	printf("Generated key2=%d\n",key2);
	int key_inv = inverse(key1);
	if(key_inv == -1){
		printf("Inverse of key doesn't exist");
		exit(0);
	}
	printf("Enter the message to be sent\n");
	scanf("%s",msg);
	
	printf("ENCRYPTING...\n");
	cipher = encrypt(msg,key1,key2);
	printf("Encrypted message: %s\n",cipher);

	printf("DECRYPTING...\n");
	plain = decrypt(cipher);
	printf("Decrypted message: %s\n",plain);

	return 0;
}

char* encrypt(char message[],int key1,int key2){
	int l = strlen(message),i;
	for(i=0;i<l;i++)
	{
		int val = message[i]-65;
		val = (val*key1)%26;
		val = (val+key2)%26;
		message[i] = val+65;
	}
	message[i] = key1+65;
	message[i+1] = key2+65;
	message[i+2]='\0';
	return message;
}
char *decrypt(char emessage[]){
	int l = strlen(emessage),i;
	char key2 = emessage[l-1];
	char key1 = emessage[l-2];
	key1 = key1-65;
	key2 = key2-65;
	int key_inv = inverse(key1);
	for(i=0;i<l-2;i++)
	{
		int val = emessage[i]-65;
		val = ((val-key2)+26)%26;
		val = (val*key_inv)%26;
		emessage[i] = val+65;
	}
	emessage[l-1]='\0';
	emessage[l-2]='\0';
	return emessage;
}
int inverse(int key){
	int q,r1=26,r2=key,t,r,t1=0,t2=1;
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
		if(t1<0){
			t1 += 26;
		}
		return t1;		
	}
	else
		return -1;
}
