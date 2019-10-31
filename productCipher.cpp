#include<bits/stdc++.h>
using namespace std;

int encrypt(bool*,bool*);
int decrypt(bool*,bool*);
int main(){
    char msg;
    bool bin[8] = {0},binkey1[8] = {0},binkey2[8] = {0};
    int k1,k2,val,temp1,temp2,c,p;
    cout<<"enter the message"<<endl;
    cin>>msg;
    val = msg;
    for(int i=7;i>=0;i--){
        bin[i] = val%2;
        val = val/2;
    }
    srand(time(NULL));
    k1 = rand()%256;    //key for round1
    k2 = rand()%256;    //key for round2
    temp1 = k1;
    temp2 = k2;
    for(int i=7;i>=0;i--){
        binkey1[i] = temp1%2;
        temp1 = temp1/2;
    }

    for(int i=7;i>=0;i--){
        binkey2[i] = temp2%2;
        temp2 = temp2/2;
    }
    //round 1 starts
    cout<<"round 1 starts, round key= "<<k1<<endl;
    val = encrypt(bin,binkey1);
    cout<<"After round 1: "<<char(val)<<endl;

    for(int i=7;i>=0;i--){
        bin[i] = val%2;
        val = val/2;
    }
    //round 2 starts
    cout<<"round 2 starts, round key= "<<k2<<endl;
    val = encrypt(bin,binkey2);
    cout<<"After round 2: "<<char(val)<<endl;

    for(int i=7;i>=0;i--){
        bin[i] = val%2;
        val = val/2;
    }
    //round 1 decryption
    cout<<"round 1 decryption starts, round key= "<<k2<<endl;
    val = decrypt(bin,binkey2);
    cout<<"After round 1: "<<char(val)<<endl;

    for(int i=7;i>=0;i--){
        bin[i] = val%2;
        val = val/2;
    }
    //round 2 decryption
    cout<<"round 2 decryption starts, round key= "<<k1<<endl;
    val = decrypt(bin,binkey1);
    cout<<"After round 2: "<<char(val)<<endl;

    return 0;
}
int encrypt(bool* bin,bool* binkey1){
    //step 1. XOR with key
    for(int i=0;i<8;i++)
        bin[i] = bin[i]^binkey1[i];
    cout<<"after xor"<<endl;
    for(int i=0;i<8;i++)
        cout<<bin[i]<<" ";
    cout<<endl;

    //step 2. Pass to SBOX
    bool x1,x2,y1,y2;
    for(int i=0;i<8;i+=2){
         x1 = bin[i];
         x2 = bin[i+1];
        //y1 = x1 xor x2
        //y2 = x1
         y1 = bin[i]^bin[i+1];
         y2 = bin[i+1];

        bin[i] = y1;
        bin[i+1] = y2;
    }
    cout<<"after sbox"<<endl;
    for(int i=0;i<8;i++)
        cout<<bin[i]<<" ";
    cout<<endl;

    //step 3. Pass to DBOX  encryption dbox = {7,5,4,1,2,8,3,6}
    int dbox[] = {7,5,4,1,2,8,3,6};
    bool temp[8];
    for(int i=0;i<8;i++)
        temp[i] = bin[i];
    for(int i=0;i<8;i++)
        bin[i] = temp[dbox[i]-1];

    cout<<"after dbox"<<endl;
    for(int i=0;i<8;i++)
        cout<<bin[i]<<" ";
    cout<<endl;

    int value=0,k=7;
    for(int i=0;i<8;i++){
        value = value + bin[i]*pow(2,k);
        k--;
    }
    return value;
}
int decrypt(bool* bin,bool* binkey1){
    //step 1. Pass to DBOX  decryption dbox = {4,5,7,3,2,8,1,6}
    int dbox[] = {4,5,7,3,2,8,1,6};
    bool temp[8];
    for(int i=0;i<8;i++)
        temp[i] = bin[i];
    for(int i=0;i<8;i++)
        bin[i] = temp[dbox[i]-1];
    cout<<"after dbox"<<endl;
    for(int i=0;i<8;i++)
        cout<<bin[i]<<" ";
    cout<<endl;
    
    //step 2. Pass to SBOX
    bool x1,x2,y1,y2;
    for(int i=0;i<8;i+=2){
         x1 = bin[i];
         x2 = bin[i+1];
        //y1 = x1 xor x2
        //y2 = x1
         y1 = bin[i]^bin[i+1];
         y2 = bin[i+1];

        bin[i] = y1;
        bin[i+1] = y2;
    }
    cout<<"after sbox"<<endl;
    for(int i=0;i<8;i++)
        cout<<bin[i]<<" ";
    cout<<endl;

    //step 3. XOR with key
    for(int i=0;i<8;i++)
        bin[i] = bin[i]^binkey1[i];
    cout<<"after xor"<<endl;
    for(int i=0;i<8;i++)
        cout<<bin[i]<<" ";
    cout<<endl;
    
    int value=0,k=7;
    for(int i=0;i<8;i++){
        value = value + bin[i]*pow(2,k);
        k--;
    }
    return value;
}