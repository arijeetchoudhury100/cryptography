#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
char* encrypt(char*,int*);
char* decrypt(char*,int*);

int main(){
    char msg[100],*cipher,*plain;
    int ekey[5],dkey[5],i,j;
    printf("Enter the encryption key\n");
    for(i=0;i<5;i++)
        scanf("%d",&ekey[i]);
    printf("Enter the decryption key\n");
    for(i=0;i<5;i++)
        scanf("%d",&dkey[i]);
    printf("Enter the message:\n");
    scanf("%s",msg);
    cipher = encrypt(msg,ekey);
    printf("Encypted message: %s\n",cipher);
    plain = decrypt(cipher,dkey);
    printf("Decypted message: %s\n",plain);
    return 0;
}

char* encrypt(char msg[],int key[]){
    int num_rows = ceil(strlen(msg)/5.0);
    int msgmatrix[num_rows][5],i=0,j=0;
    int ciphermatrix[num_rows][5];
    int keymatrix[5][5];
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            keymatrix[i][j]=0;
    for(int i=0;i<5;i++)
        keymatrix[key[i]-1][i]=1;        
    for(int k=0;k<strlen(msg);k++)
    {   
        msgmatrix[i][j] = msg[k]-'A';
        j = j+1;
        if(j == 5)
        {
            i = i+1;
            j = 0;
        }
    }
    if(j != 0)
    {
        while(j != 5)
            msgmatrix[i][j++] = 25;
    }
    printf("The message matrix is:\n");
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<5;j++){
            printf("%d ",msgmatrix[i][j]);
        }
        printf("\n");
    }
    printf("The key matrix is:\n");
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            printf("%d ",keymatrix[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<5;j++){
            ciphermatrix[i][j]=0;
            for(int k=0;k<5;k++){
                ciphermatrix[i][j] += msgmatrix[i][k] * keymatrix[k][j];
            }
            ciphermatrix[i][j] %= 26;
        }
    }
    printf("The cipher matrix is:\n");
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<5;j++){
            printf("%d ",ciphermatrix[i][j]);
        }
        printf("\n");
    }
    int in = 0;
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<5;j++){
            msg[in++] = ciphermatrix[i][j] + 'A';
        }
    }
    msg[in] = '\0';
    return msg;
}
char* decrypt(char msg[],int key[]){
    int num_rows = ceil(strlen(msg)/5.0);
    int msgmatrix[num_rows][5],i=0,j=0;
    int ciphermatrix[num_rows][5];
    int keymatrix[5][5];
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            keymatrix[i][j]=0;
    for(int i=0;i<5;i++)
        keymatrix[key[i]-1][i]=1;        
    for(int k=0;k<strlen(msg);k++)
    {   
        ciphermatrix[i][j] = msg[k]-'A';
        j = j+1;
        if(j == 5)
        {
            i = i+1;
            j = 0;
        }
    }
    if(j != 0)
    {
        while(j != 5)
            ciphermatrix[i][j++] = 25;
    }
    printf("The Cipher matrix is:\n");
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<5;j++){
            printf("%d ",ciphermatrix[i][j]);
        }
        printf("\n");
    }
    printf("The key matrix is:\n");
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            printf("%d ",keymatrix[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<5;j++){
            msgmatrix[i][j]=0;
            for(int k=0;k<5;k++){
                msgmatrix[i][j] += ciphermatrix[i][k] * keymatrix[k][j];
            }
            msgmatrix[i][j] %= 26;
        }
    }
    printf("The message matrix is:\n");
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<5;j++){
            printf("%d ",msgmatrix[i][j]);
        }
        printf("\n");
    }
    int in = 0;
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<5;j++){
            msg[in++] = msgmatrix[i][j] + 'A';
        }
    }
    msg[in] = '\0';
    return msg;
}