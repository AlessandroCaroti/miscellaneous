#include<stdio.h>
#include<stdlib.h>

main(){
	int i;
	char c;
	printf("#include<stdio.h>\n#include<stdlib.h>\n#include<string.h>\n#include<time.h>\nchar\ts[]={\n");
	for(i=0; (c = getchar()) != EOF ; i++)
		switch(c){
		case'\n':printf("\t\'\\n\',\n");break;
		case'\t':printf("\t\'\\t\',\n");break;
		case'\\':printf("\t\'\\\\\',\n");break;
		case'\'':printf("\t\'\\'\',\n");break;
		case'\"':printf("\t\'\\\"\',\n");break;
		case'\?':printf("\t\'\\?\',\n");break;
		case'\v':printf("\t\'\\v\',\n");break;
		case'\r':printf("\t\'\\r\',\n");break;
		default:printf("\t\'%c\',\n",c);break;
		}
	exit(0);
}
