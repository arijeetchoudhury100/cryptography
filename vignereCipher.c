#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char* encrypt(char*,char*);
char* decrypt(char*,char*);

int main(){
	char msg[100],key[100],genkey[100],*cipher,*plain;
	int i,j;
	srand(time(NULL));
	
	printf("Enter the key\n");
	scanf("%s",key);
	printf("Enter the message to be sent\n");
	scanf("%s",msg);
	for(i=0,j=0;i<strlen(msg);i++,j++){
		if(j == strlen(key))
			j=0;
		genkey[i]=key[j];
	}		
	genkey[i]='\0';
	printf("Key used:\n");
	for(i=0;i<strlen(genkey);i++)
		printf("%c",genkey[i]); 
	printf("\nENCRYPTING...\n");
	cipher = encrypt(msg,genkey);
	printf("Encrypted message: %s\n",cipher);

	printf("DECRYPTING...\n");
	plain = decrypt(cipher,genkey);
	printf("Decrypted message: %s\n",plain);

	return 0;
}

char* encrypt(char message[],char key[]){
	int l = strlen(message),i;
	for(i=0;i<l;i++)
	{
		int val = message[i]-65;
		int k = key[i]-65;
		val = (val+k)%26;
		message[i] = val+65;
	}
	return message;
}
char *decrypt(char emessage[],char key[]){
	int l = strlen(emessage),i;
	for(i=0;i<l;i++)
	{
		int val = emessage[i]-65;
		int k = key[i]-65;
		val = ((val-k)+26)%26;
		emessage[i] = val+65;
	}
	return emessage;
}

