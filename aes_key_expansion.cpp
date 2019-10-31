#include<string>
#include<cmath>
#include<iostream>
using namespace std;
void key_expand(bool*,bool(*)[32]);
void rotword(bool*);
void subword(bool*);
void convert_to_binary(string,bool*);
void convert_to_hex(bool(*)[32],char(*)[8]);
int convert_to_decimal(bool*);
string subbytes[16] = { "637C777BF26B6FC53001672BFED7AB76",
                        "CA82C97DFA5947F0ADD4A2AF9CA472CO",
                        "B7FD9326363FF7CC34A5E5F171D83115",
                        "04C723C31896059A071280E2EB27B275",
                        "09832C1A1B6E5AA0523BD6B329E32F94",
                        "53D100ED20FCB15B6ACBBE394A4C58CF",
                        "D0EFAAFB434D338545F9027F503C9FA8",
                        "51A3408F929D38F5BCB6DA2110FFF3D2",
                        "CD0C13EC5F974417C4A77E3D645D1973",
                        "60814FDC222A908846EEB814DE5E0BDB",
                        "E0323A0A4906245CC2D3AC629195E479",
                        "E7CB376D8DD54EA96C56F4EA657AAE08",
                        "BA78252E1CA6B4C6E8DD741F4BBD8B8A",
                        "703EB5664803F60E613557B986C11D9E",
                        "E1F8981169D98E949B1E87E9CE5528DF",
                        "8CA1890DBFE6426841992D0FB054BB16" };
bool rcon[10][8] = {0,0,0,0,0,0,0,1,
                    0,0,0,0,0,0,1,0,
                    0,0,0,0,0,1,0,0,
                    0,0,0,0,1,0,0,0,
                    0,0,0,1,0,0,0,0,
                    0,0,1,0,0,0,0,0,
                    0,1,0,0,0,0,0,0,
                    1,0,0,0,0,0,0,0,
                    0,0,0,1,1,0,1,1,
                    0,0,1,1,0,1,1,0};
int main(){
    string hexkey;
    bool key[128] = {0},w[44][32] = {0};
    char hexw[44][8];
    cout<<"enter the key:"<<endl;
    getline(cin,hexkey);
    convert_to_binary(hexkey,key);
    key_expand(key,w);
    convert_to_hex(w,hexw);
    for(int i=0;i<44;i++){
        for(int j=0;j<8;j++)
            cout<<hexw[i][j];
        cout<<" ";
        if( (i+1)%4 == 0)
            cout<<endl;
    }
}
void key_expand(bool* key,bool w[44][32]){
    int k=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<32;j++)
            w[i][j] = key[k++]; 
    }
    for(int i=4;i<44;i++){
        if(i%4 !=0){
            for(int j=0;j<32;j++)
                w[i][j] = w[i-1][j] ^ w[i-4][j];
        }
        else{
            bool t[32]={0};
            bool wi1[32]={0};
            for(int j=0;j<32;j++)
                wi1[j] = w[i-1][j];
            rotword(wi1);
            subword(wi1);
            for(int j=0;j<8;j++)
                t[j] = wi1[j] ^ rcon[(i/4)-1][j];
            for(int j=8;j<32;j++)
                t[j] = wi1[j];
            for(int j=0;j<32;j++)
                w[i][j] = t[j] ^ w[i-4][j];
        }
    }
}
void rotword(bool* ptr){
    for(int i=1;i<=8;i++){
        bool temp = ptr[0];
        for(int j=1;j<32;j++)
            ptr[j-1] = ptr[j];
        ptr[31] = temp;
    }
}
void subword(bool *ptr){
    bool first[4] = {0},second[4] = {0},b[8] = {0};
    int r,c,k;
    string row,sub;
    for(int i=0;i<32;i+=8){
        sub = "";
        k = 0;
        for(int j=i;j<i+4;j++)
            first[k++] = ptr[j];
        k = 0;
        for(int j=i+4;j<i+8;j++)
            second[k++] = ptr[j];
        r = convert_to_decimal(first);
        c = convert_to_decimal(second);
        row = subbytes[r];
        sub = sub+row[2*c]+row[2*c+1];
        convert_to_binary(sub,b);
        k=0;
        for(int j=i;j<i+8;j++)
            ptr[j] = b[k++];
    }   
}
int convert_to_decimal(bool* ptr){
    int k=3,d=0;
    for(int i=0;i<4;i++)
        d = d+ptr[i]*pow(2,k--);
    return d;
}
void convert_to_binary(string hexkey,bool* binkey){
    int k = 0;
    for(int i=0;i<hexkey.length();i++){
        switch(hexkey[i]){
            case '0': binkey[k]=0;binkey[k+1]=0;binkey[k+2]=0;binkey[k+3]=0;break;
            case '1': binkey[k]=0;binkey[k+1]=0;binkey[k+2]=0;binkey[k+3]=1;break;
            case '2': binkey[k]=0;binkey[k+1]=0;binkey[k+2]=1;binkey[k+3]=0;break;
            case '3': binkey[k]=0;binkey[k+1]=0;binkey[k+2]=1;binkey[k+3]=1;break;
            case '4': binkey[k]=0;binkey[k+1]=1;binkey[k+2]=0;binkey[k+3]=0;break;
            case '5': binkey[k]=0;binkey[k+1]=1;binkey[k+2]=0;binkey[k+3]=1;break;
            case '6': binkey[k]=0;binkey[k+1]=1;binkey[k+2]=1;binkey[k+3]=0;break;
            case '7': binkey[k]=0;binkey[k+1]=1;binkey[k+2]=1;binkey[k+3]=1;break;
            case '8': binkey[k]=1;binkey[k+1]=0;binkey[k+2]=0;binkey[k+3]=0;break;
            case '9': binkey[k]=1;binkey[k+1]=0;binkey[k+2]=0;binkey[k+3]=1;break;
            case 'A': binkey[k]=1;binkey[k+1]=0;binkey[k+2]=1;binkey[k+3]=0;break;
            case 'B': binkey[k]=1;binkey[k+1]=0;binkey[k+2]=1;binkey[k+3]=1;break;
            case 'C': binkey[k]=1;binkey[k+1]=1;binkey[k+2]=0;binkey[k+3]=0;break;
            case 'D': binkey[k]=1;binkey[k+1]=1;binkey[k+2]=0;binkey[k+3]=1;break;
            case 'E': binkey[k]=1;binkey[k+1]=1;binkey[k+2]=1;binkey[k+3]=0;break;
            case 'F': binkey[k]=1;binkey[k+1]=1;binkey[k+2]=1;binkey[k+3]=1;break;
            default: cout<<"Invalid character"<<endl;
        }
        k = k+4;
    }
}
void convert_to_hex(bool w[44][32],char hexw[44][8]){
    for(int i=0;i<44;i++){
        int k=0;
        for(int j=0;j<32;j+=4){
            if(w[i][j] == 0 && w[i][j+1] == 0 && w[i][j+2] == 0 && w[i][j+3] == 0){
                hexw[i][k]='0';
            }
            else if(w[i][j] == 0 && w[i][j+1] == 0 && w[i][j+2] == 0 && w[i][j+3] == 1){
                hexw[i][k]='1';
            }
            else if(w[i][j] == 0 && w[i][j+1] == 0 && w[i][j+2] == 1 && w[i][j+3] == 0){
                hexw[i][k]='2';
            }
            else if(w[i][j] == 0 && w[i][j+1] == 0 && w[i][j+2] == 1 && w[i][j+3] == 1){
                hexw[i][k]='3';
            }
            else if(w[i][j] == 0 && w[i][j+1] == 1 && w[i][j+2] == 0 && w[i][j+3] == 0){
                hexw[i][k]='4';
            }
            else if(w[i][j] == 0 && w[i][j+1] == 1 && w[i][j+2] == 0 && w[i][j+3] == 1){
                hexw[i][k]='5';
            }
            else if(w[i][j] == 0 && w[i][j+1] == 1 && w[i][j+2] == 1 && w[i][j+3] == 0){
                hexw[i][k]='6';
            }
            else if(w[i][j] == 0 && w[i][j+1] == 1 && w[i][j+2] == 1 && w[i][j+3] == 1){
                hexw[i][k]='7';
            }
            else if(w[i][j] == 1 && w[i][j+1] == 0 && w[i][j+2] == 0 && w[i][j+3] == 0){
                hexw[i][k]='8';
            }
            else if(w[i][j] == 1 && w[i][j+1] == 0 && w[i][j+2] == 0 && w[i][j+3] == 1){
                hexw[i][k]='9';
            }
            else if(w[i][j] == 1 && w[i][j+1] == 0 && w[i][j+2] == 1 && w[i][j+3] == 0){
                hexw[i][k]='A';
            }
            else if(w[i][j] == 1 && w[i][j+1] == 0 && w[i][j+2] == 1 && w[i][j+3] == 1){
                hexw[i][k]='B';
            }
            else if(w[i][j] == 1 && w[i][j+1] == 1 && w[i][j+2] == 0 && w[i][j+3] == 0){
                hexw[i][k]='C';
            }
            else if(w[i][j] == 1 && w[i][j+1] == 1 && w[i][j+2] == 0 && w[i][j+3] == 1){
                hexw[i][k]='D';
            }
            else if(w[i][j] == 1 && w[i][j+1] == 1 && w[i][j+2] == 1 && w[i][j+3] == 0){
                hexw[i][k]='E';
            }
            else if(w[i][j] == 1 && w[i][j+1] == 1 && w[i][j+2] == 1 && w[i][j+3] == 1){
                hexw[i][k]='F';
            }
            k++;
        }
    }
}