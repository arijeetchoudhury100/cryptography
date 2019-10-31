#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX 100
using namespace std;

char* encrypt(char*,char[5][5]);
char* decrypt(char*,char[5][5]);

int main()
{
    char key[5][5],msg[MAX],newmsg[MAX],*cipher,*plain;
    cout<<"enter key matrix"<<endl;
    for(int i=0;i<5;i++)
        scanf("%s",key[i]);
    cout<<"enter plain text"<<endl;
    scanf("%s",msg);
    int l = strlen(msg),k=0;

    //prepare plaintext for encryption
    for(int i=0;i<l;i++)
    {
        newmsg[k++]=msg[i];
        if(newmsg[k-1]=='J')
            newmsg[k-1]='I';
        if(msg[i]==msg[i+1])
        {
            newmsg[k++]='X';
        }
    }
    newmsg[k]='\0';
    if(strlen(newmsg)%2)
    {
        newmsg[k]='X';
        newmsg[k+1]='\0';
    }    
    cout<<newmsg<<endl;
    cipher = encrypt(newmsg,key);
    cout<<"encrypted text is:"<<endl<<cipher<<endl;
    plain = decrypt(cipher,key);
    cout<<"decrypted text is:"<<endl<<plain<<endl;
    return 0;
}
char* encrypt(char nm[MAX],char key[5][5])
{
    int l=strlen(nm);
    int i1,j1,i2,j2;
    for(int i=0;i<l;i=i+2)
    {
        for(int j=0;j<5;j++)
        {
            for(int k=0;k<5;k++)
            {
                if(nm[i] == key[j][k])
                {
                    i1=j;
                    j1=k;
                }
                if(nm[i+1] == key[j][k])
                {
                    i2=j;
                    j2=k;
                }
            }
        }
        if(i1==i2)
        {
            nm[i] = key[i1][(j1+1)%5];
            nm[i+1] = key[i1][(j2+1)%5];
        }
        else if(j1==j2)
        {
            nm[i] = key[(i1+1)%5][j1];
            nm[i+1] = key[(i2+1)%5][j1];
        }
        else
        {
            nm[i] = key[i1][j2];
            nm[i+1] = key[i2][j1];
        }
    }
    return nm;
}
char* decrypt(char em[MAX],char key[5][5])
{
    char nem[MAX];
    int l=strlen(em),k=0;
    int i1,j1,i2,j2;
    for(int i=0;i<l;i=i+2)
    {
        for(int j=0;j<5;j++)
        {
            for(int k=0;k<5;k++)
            {
                if(em[i] == key[j][k])
                {
                    i1=j;
                    j1=k;
                }
                if(em[i+1] == key[j][k])
                {
                    i2=j;
                    j2=k;
                }
            }
        }
        if(i1==i2)
        {
            em[i] = key[i1][((j1-1)+5)%5];
            em[i+1] = key[i1][((j2-1)+5)%5];
        }
        else if(j1==j2)
        {
            em[i] = key[((i1-1)+5)%5][j1];
            em[i+1] = key[((i2-1)+5)%5][j1];
        }
        else
        {
            em[i] = key[i1][j2];
            em[i+1] = key[i2][j1];
        }
    }
    for(int i=0;i<l;i++)
    {
        if(em[i]=='X')
            continue;
        nem[k++] = em[i];
    }
    nem[k]='\0';
    strcpy(em,nem);
    return em;
}