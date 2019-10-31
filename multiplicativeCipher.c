#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char* encrypt(char*,int);
char* decrypt(char*);
int inverse(int);

int main(){
	char msg[100],*cipher,*plain;
	srand(time(NULL));
	int key = (1+rand())%26;
	printf("Generated key=%d\n",key);
	int key_inv = inverse(key);
	if(key_inv == -1){
		printf("Inverse of key doesn't exist");
		exit(0);
	}
	printf("Enter the message to be sent\n");
	scanf("%s",msg);
	
	printf("ENCRYPTING...\n");
	cipher = encrypt(msg,key);
	printf("Encrypted message: %s\n",cipher);

	printf("DECRYPTING...\n");
	plain = decrypt(cipher);
	printf("Decrypted message: %s\n",plain);

	return 0;
}

char* encrypt(char message[],int key){
	int l = strlen(message),i;
	for(i=0;i<l;i++)
	{
		int val = message[i]-65;
		val = (val*key)%26;
		message[i] = val+65;
	}
	message[i] = key+65;
	message[i+1]='\0';
	return message;
}
char *decrypt(char emessage[]){
	int l = strlen(emessage),i;
	char key = emessage[l-1];
	key = key-65;
	int key_inv = inverse(key);
	printf("%d\n",key_inv);
	for(i=0;i<l-1;i++)
	{
		int val = emessage[i]-65;
		val = (val*key_inv)%26;
		emessage[i] = val+65;
	}
	emessage[l-1]='\0';
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
