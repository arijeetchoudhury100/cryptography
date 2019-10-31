#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char* encrypt(char*,char*);
char* decrypt(char*,char*);

int main(){
	char msg[100],key[100],*cipher,*plain;
	srand(time(NULL));
	int initialKey = rand()%26,i;	
	if(initialKey == 0)
		initialKey++;
	printf("Initial key=%d\n",initialKey);
	printf("Enter the message to be sent\n");
	scanf("%s",msg);
	key[0] = initialKey + 65;
	for(i=1;i<strlen(msg);i++)
		key[i]=msg[i-1];
	key[i]='\0';
	printf("Keys used:\n");
	for(i=0;i<strlen(key);i++)
		printf("%c ",key[i]); 
	printf("ENCRYPTING...\n");
	cipher = encrypt(msg,key);
	printf("Encrypted message: %s\n",cipher);

	printf("DECRYPTING...\n");
	plain = decrypt(cipher,key);
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

