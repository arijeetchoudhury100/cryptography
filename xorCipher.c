#include<stdio.h>
#include<string.h>

char* encrypt(char*,char);
char* decrypt(char*,char);

int main()
{
	char msg[100],*c,*p,key;
	int i;
	printf("Enter the XOR key\n");
	scanf("%c",&key);

	printf("Enter the message\n");
	scanf("%s",msg);

	c = encrypt(msg,key);
	//printf("Encrypted text is: %s\n",c);
	for(i=0;i<strlen(c);i++)
		printf("%d",c[i]);
	printf("\n");
	p = decrypt(c,key);
	printf("Decrypted text is: %s\n",p);

	return 0;
}

char *encrypt(char *msg,char key)
{
	int l = strlen(msg);
	int i,val;
	for(i=0;i<l;i++)
	{
		val = msg[i]^key;
		msg[i] = val;
	}
	return msg;
}
char *decrypt(char *msg,char key)
{
        int l = strlen(msg);
        int i,val;
        for(i=0;i<l;i++)
        {
                val = msg[i]^key;
                msg[i] = val;
        }
        return msg;
}

