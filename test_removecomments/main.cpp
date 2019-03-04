/*		Program to remove single line comment from any text file
		made by :	rakesh kumar
*/
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
using namespace std;

// global function to remove single line comment
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
		else
			fout<<ch;

	}

	fin.close();
	fout.close();
}
int main()
{
	char source[]="program.txt";
	char dest[]="temp.txt";
	remove_single_comment(source,dest);
	ifstream fin(dest);
	char ch;
	while(fin.get(ch))
		cout<<ch;
	fin.close();
	return 0;
}
