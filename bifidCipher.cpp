#include<iostream>
#include<cstdlib>
#include<cstring>

using namespace std;

void encrypt(char*,char[][5]);
void decrypt(char *,char[][5]);

int main(){
    char key[5][5],msg[100];
    cout<<"Enter the key:"<<endl;
    for(int i=0;i<5;i++)
        cin>>key[i];
    cout<<"Enter the message: ";
    cin>>msg;
    encrypt(msg,key);
    cout<<"Encrypted message is: "<<msg<<endl;
    decrypt(msg,key);
    cout<<"Decrypted message is:"<<msg<<endl;
    return 0;
}

void encrypt(char *msg,char key[5][5]){
    int l = strlen(msg);
    int rows[l],cols[l],rowcol[2*l],k=0;;
    for(int i=0;i<l;i++){
        for(int row=0;row<5;row++){
            for(int col=0;col<5;col++){
                if(msg[i] == key[row][col]){
                    rows[k] = row;
                    cols[k] = col;
                    k++;
                }
            }
        }
    }
    k=0;
    for(int i=0;i<l;i++){
        rowcol[k++] = rows[i];
    }
    for(int i=0;i<l;i++){
        rowcol[k++] = cols[i];
    }
    k=0;
    for(int i=0;i<2*l;i+=2){
        msg[k++] = key[rowcol[i]][rowcol[i+1]];
    }
}
void decrypt(char *msg,char key[5][5]){
    int l = strlen(msg);
    int rows[l],cols[l],rowcol[2*l],k=0;
    for(int i=0;i<l;i++){
        for(int row=0;row<5;row++){
            for(int col=0;col<5;col++){
                if(msg[i] == key[row][col]){
                    rowcol[k] = row;
                    rowcol[k+1] = col;
                    k = k+2;
                }
            }
        }
    }
    k=0;
    for(int i=0;i<l;i++)
        rows[i] = rowcol[k++];
    for(int i=0;i<l;i++)
        cols[i] = rowcol[k++];
    for(int i=0;i<l;i++)
        msg[i] = key[rows[i]][cols[i]];
}
