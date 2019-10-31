#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char* encrypt(char*);
char* decrypt(char*);

int main(){
    char *msg = (char *)malloc(sizeof(char)*100);
    char *cipher,*plain;

    scanf("%s",msg);
    cipher = encrypt(msg);
    printf("%s\n",cipher);

    plain = decrypt(cipher);
    printf("%s\n",plain);

    return 0;
}
char* encrypt(char *m){
    for(int i=0;i<strlen(m);i++){
        char ch = *(m+i);
        int val = ch - 65;
        val = (val+3)%26;
        *(m+i) = val+65;
    }
    return m;
}
char* decrypt(char *m){
    for(int i=0;i<strlen(m);i++){
        char ch = *(m+i);
        int val = ch - 65;
        val = (val-3)%26;
        *(m+i) = val+65;
    }
    return m;
}