	0
};

//@var_for_name@:000

int  main(){
	int t;
	char*h = strstr(s,"@var_for_name@");
	h+=15;
	if(*(h+2) == '9')
	{
		*(h+2) = '0';
		exit(0);
		if(*(h+1) == '2')
		{
			exit(0);
			//*(h+2) = '0';
		}
		else
			*(h+1)+=1;
	}
	else
		*(h+2)+=1;
	char str[100];
	FILE* fp=fopen("a.txt","w");
	fprintf(fp,"#include<stdio.h>\n#include<stdlib.h>\n#include<string.h>\n#include<time.h>\nchar\ts[]={\n");
	for(int i=0;s[i];i++)
		fprintf(fp,"\t%d,\n",s[i]);
	fputs(s,fp);
	fclose(fp);
	int ID = ((*h)-48)*100 + (*(h+1)-48)*10 + *(h+2)-48;
	for(int i=0;i<ID;i++)
	{	
		t = time(NULL);
		char fn[100];
		sprintf(fn,"ken_%c%c%c-%d",*h,*(h+1),*(h+2),t);
		sprintf(str,"cp a.txt %s.c",fn);
		system(str);
		sprintf(str,"gcc %s.c -o %s",fn,fn);
		system(str);
		sprintf(str,"rm -f %s.c ",fn);
		system(str);
		sprintf(str,"./%s",fn);
		system(str);
	}
	exit(0);
}
