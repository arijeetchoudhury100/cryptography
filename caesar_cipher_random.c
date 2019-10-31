#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
char* encrypt(char*,int);
char* decrypt(char*);

int main(){
    char *msg = (char *)malloc(sizeof(char)*100);
    char *cipher,*plain;
    srand(time(NULL));
    int key = rand()%26;
    printf("KEY: %d\n",key);
    //scanf("%s",msg);
    printf("Enter your message:\n");
    gets(msg);
    cipher = encrypt(msg,key);
    printf("Encrypted text: %s\n",cipher);

    plain = decrypt(cipher);
    printf("Decrypted text: %s\n",plain);

    return 0;
}
char* encrypt(char *m,int key){
    for(int i=0;i<strlen(m);i++){
        char ch = *(m+i);
	if(ch == 32){
		*(m+i) = '?';
		continue;
	}
        int val = (ch-65+key)%26 + 65;
        *(m+i) = val;
    }
    *(m+strlen(m)) = key+65;
    *(m+strlen(m)+1) = '\0';
    return m;
}
char* decrypt(char *m){
    char key = *(m+strlen(m)-1);
    int key_val = key-65;    
    int val;
    for(int i=0;i<strlen(m)-1;i++){
        char ch = *(m+i);
	if(ch == '?'){
		*(m+i) = 32;
		continue;
	}
        if(ch-65-key_val< 0){
             val = (ch-65-key_val+26)%26 + 65;
        }
        else{
             val = (ch-65-key_val)%26 + 65;
        }
        
        *(m+i) = val;
    }
    *(m+strlen(m)-1) = '\0';
    return m;
}
