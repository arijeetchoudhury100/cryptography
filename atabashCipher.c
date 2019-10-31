#include<stdio.h>
#include<string.h>

char* encrypt(char*);
char* decrypt(char*);

int main()
{
	char msg[100],*c,*p;
	printf("Enter the message\n");
	scanf("%s",msg);

	c = encrypt(msg);
	printf("Encrypted message is: %s\n",c);

	p = decrypt(c);
	printf("Decrypted message is: %s\n",p);

	return 0;
}

char* encrypt(char *msg)
{
	int l = strlen(msg);
	int i,val,newval;
	for(i=0;i<l;i++)
	{
		val = msg[i] - 'A';
		newval = 25 - val;
		msg[i] = newval + 'A';
	}
	return msg;
}
char* decrypt(char *msg)
{
        int l = strlen(msg);
        int i,val,newval;
        for(i=0;i<l;i++)
        {
                val = msg[i] - 'A';
                newval = 25 - val;
                msg[i] = newval + 'A';
        }
        return msg;
}

