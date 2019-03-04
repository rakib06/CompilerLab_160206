#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
using namespace std;
void keyw(char *p);
int i=0,id=0,kw=0,num=0,op=0;
char keys[32][10]= {"auto","break","case","char","const","continue","default",
                    "do","double","else","enum","extern","float","for","goto",
                    "if","int","long","register","return","short","signed",
                    "sizeof","static","struct","switch","typedef","union",
                    "unsigned","void","volatile","while"
                   };


string removeComments(string prgm)
{
	int n = prgm.length();
	string res;

	// Flags to indicate that single line and multpile line comments
	// have started or not.
	bool s_cmt = false;
	bool m_cmt = false;


	// Traverse the given program
	for (int i=0; i<n; i++)
	{
		// If single line comment flag is on, then check for end of it
		if (s_cmt == true && prgm[i] == '\n')
			s_cmt = false;

		// If multiple line comment is on, then check for end of it
		else if (m_cmt == true && prgm[i] == '*' && prgm[i+1] == '/')
			m_cmt = false, i++;

		// If this character is in a comment, ignore it
		else if (s_cmt || m_cmt)
			continue;

		// Check for beginning of comments and set the approproate flags
		else if (prgm[i] == '/' && prgm[i+1] == '/')
			s_cmt = true, i++;
		else if (prgm[i] == '/' && prgm[i+1] == '*')
			m_cmt = true, i++;

		// If current character is a non-comment character, append it to res
		else res += prgm[i];
	}
	return res;
}

void remove_single_comment(char source[], char dest[]){
	ifstream fin(source);
	ofstream fout(dest);
	char ch;
	char temp;

	while(!fin.eof())
	{
		fin.get(ch);
		if(ch=='/')
		  {
		  	 fin.get(ch);
		  	 if(ch=='/')
		  	    {	while(!fin.eof())
				   {
				   	fin.get(ch);
				   	if(ch=='\n'||ch=='\r')  // remove all until end of line from the output file
				   		break;
				   }
			    }
			  else
			    fout<<"/"<<ch;
		  }

		 else if (temp!=ch ){
			fout<<ch;
		}

          if (ch == '}'){
            temp = '}';

		  }
		  else
            temp = '$';
	}

	fin.close();
	fout.close();
}

int main()
{
    char ch,str[25],seps[20]=" \t\n,;(){}[]#\"<>",oper[]="!%^&*-+=~|.<>/?";
    int j;
    char source[]="program.txt";
	char dest[]="temp.txt";
	remove_single_comment(source,dest);
    char fname[50] = "temp.txt";
    FILE *f1;
    f1 = fopen(fname,"r");

    if(f1==NULL)
    {
        printf("file not found");
    }
ifstream t("temp.txt");
string str1((istreambuf_iterator<char>(t)),
                 istreambuf_iterator<char>());
    cout << "After Removing Comments Source Program : "<<endl;

    cout <<  removeComments(str1)<<endl;
    cout << endl;

    cout << "Lexical Analyzer : "<<endl;
    cout << endl;
    while((ch=fgetc(f1))!=EOF)
    {
        for(j=0; j<=14; j++)
        {

            if(ch==oper[j])
            {
                printf("%c  ---> operator\n",ch);
                op++;
                str[i]='\0';
                keyw(str);
            }
        }
        for(j=0; j<=14; j++)
        {
            if(i==-1)
                break;
            if(ch==seps[j])
            {
                if(ch=='#')
                {
                    while(ch!='>')
                    {
                        printf("%c",ch);
                        ch=fgetc(f1);
                    }
                    printf("%c   ---> header file\n",ch);
                    i=-1;
                    break;
                }
                if(ch=='"')
                {
                    do
                    {
                        ch=fgetc(f1);
                        printf("%c",ch);
                    }
                    while(ch!='"');
                    printf("\b  ---> argument\n");
                    i=-1;
                    break;
                }
                str[i]='\0';
                keyw(str);
            }
        }
        if(i!=-1)
        {
            str[i]=ch;
            i++;
        }
        else
            i=0;
    }
    printf("\nKeywords: %d\nIdentifiers: %d\nOperators: %d\nNumbers: %d\n",kw,id,op,num);

}


void keyw(char *p)
{
    int k,flag=0;
    for(k=0; k<=31; k++)
    {
        if(strcmp(keys[k],p)==0)
        {
            printf("%s  ---> keyword\n",p);
            kw++;
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        if(isdigit(p[0]))
        {
            printf("%s  ---> number\n",p);
            num++;
        }
        else
        {
            if(p[0]!='\0')
            {
                printf("%s  --->  identifier\n",p);
                id++;
            }
        }
    }
    i=-1;
}
