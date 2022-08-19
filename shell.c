#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char whitespace[] = " \t\r\n\v";
char symbols[] = "<>&;()";

struct cmd {
  int type;
};


struct pipecmd {
  int type;
  struct cmd *left;
  struct cmd *right;
};

void firstf(char *buf);
void redire(char *a[50],char *b[50]);
void redirei(char *a[50],char *b[50]);
int parseseq(char *cm,char **arr);

int check(char *buf){
	if(buf[0]=='l' && buf[1] == 's')
		return 1;
	if(buf[0]=='c' && buf[1] == 'a' && buf[2]=='t')
		return 1;
	if(buf[0]=='g' && buf[1] == 'r' && buf[2]=='e' && buf[3]=='p')
		return 1;
	if(buf[0]=='e' && buf[1] == 'c' && buf[2]=='h' && buf[3]=='o')
		return 1;
	if(buf[0]=='w' && buf[1] == 'c')
		return 1;
	return 0;
}

void parse(char *cm,char **arr){
	// char arr[6][50];
	char temp[50];
	// printf(2,"parse%s%d\n",cm,strlen(cm));
	memset(temp,0,50);
	int k=0,l=0;
	for(int i=0;i<strlen(cm);i++)
	{	
		// printf(1,"%c",cm[i]);
		if(cm[i]==' '||cm[i]=='\n'||cm[i]=='\0'){
			if(strlen(temp)!=0){
			arr[k]=(char *)malloc(strlen(temp)+1);
			temp[l]='\0';
			strcpy(arr[k],temp);
			// printf(2,"%s//",temp);
			k++;
			// temp[0]='\0';
			memset(temp,0,50);
		l=0;
			}
	}
	else{
		temp[l++]=cm[i];
	}
	}
	if(strlen(temp)!=0){
		arr[k]=(char *)malloc(strlen(temp)+1);
		// temp[l++]=' ';
		temp[l]='\0';	//recheck

		strcpy(arr[k],temp);
		memset(temp,0,50);
		k++;
	}
	// for(int i=0;i<k;i++)
	// 	printf(2,"+%s+",arr[i]);
	// printf(2,"\n");
	return;
}
int ps(){
	return psinfo();
}
int procinfo(int pid){
		numOpenFiles(pid);
		memAlloc(pid);
	getprocesstimedetails(pid);
	return 0;
	// printf(1,"hey");
}

  int parsepipe(char *cm,char **arr,char deli,int *ct){
  	char temp[50];
  	// printf(2,"%c",deli);
  	// cm=cm+' ';
  	memset(temp,0,50);
	int k=0,l=0,ret=0;
	for(int i=0;i<strlen(cm);i++)
	{if(cm[i]==deli){
		if(strlen(temp)!=0){
		arr[k]=(char *)malloc(strlen(temp)+2);
		ret=1;
		// pipecmd->left
		temp[l++]=' ';
		temp[l]='\0';
		ct++;

		strcpy(arr[k],temp);
		k++;
		// temp[0]='\0';
		memset(temp,0,50);
		l=0;}
	}
	else if(cm[i]=='\n'||cm[i]=='\0'){
		arr[k]=(char *)malloc(strlen(temp)+2);
		temp[l++]=' ';
		temp[l]='\0';	//recheck
		strcpy(arr[k],temp);
		k++;
		// temp[0]='\0';
		memset(temp,0,50);
		l=0;
	}
	else{
		temp[l++]=cm[i];
	}
	}
	if(strlen(temp)!=0){
		arr[k]=(char *)malloc(strlen(temp)+2);
		temp[l++]=' ';
		temp[l]='\0';	//recheck
		strcpy(arr[k],temp);
		k++;
	}
	// for(int i=0;i<k;i++)
	// 	printf(2,"@%s@",arr[i]);
	// printf(2,"\n");
	return ret;
  }
   void executeCommands(char *a){
  	// fd=open(a, O_RDONLY);
  	int n,fd;
  	int ct=0;
  	char cm[512],temp[50];
  	if((fd = open(a, O_RDONLY)) < 0){
      printf(1, "cannot open %s\n", a);
      exit(-1);
    }
    while((n = read(fd, cm, sizeof(cm))) > 0) {
    	char *arr[50];
    	int k=0,l=0;
	for(int i=0;i<strlen(cm);i++)
	{if(cm[i]=='\n'){
		if(strlen(temp)!=0){
		arr[k]=(char *)malloc(strlen(temp)+2);
		temp[l++]=' ';
		temp[l]='\0';
		ct++;
		strcpy(arr[k],temp);
		k++;
		// temp[0]='\0';
		memset(temp,0,50);
		l=0;
		// printf(2,"%s:\n",arr[k-1]);
	}
	}
	else{
		temp[l++]=cm[i];
	}
	}
	if(strlen(temp)!=0){
		arr[k]=(char *)malloc(strlen(temp)+2);
		temp[l++]=' ';
		temp[l]='\0';
		ct++;

		strcpy(arr[k],temp);
		k++;
		// temp[0]='\0';
		memset(temp,0,50);
		// printf(2,"%s:?\n",arr[k-1]);
		l=0;
	}
    	// parsepipe(buf,arr,'\n',&ct);
    	// printf(2,"%d",ct);
    	for(int i=0;i<ct;i++){
    		if(fork()==0){
    		// printf(2,"$%s$:%d\n",arr[i],i);
    		firstf(arr[i]);
    	}
    	else
    	wait(0);
    	}
    	// printf(2,"%s::%d::",buf,sizeof(arr));
  }
  if(n < 0){
    printf(1, "read error\n");
    exit(-1);
  }
  return;
  }
  void runcmd(char **arr){
  	if(arr[0][0]=='p'&&arr[0][1]=='s')
					ps();
		else if(arr[0][0]=='e'&&arr[0][1]=='x'&&arr[0][2]=='i'&&arr[0][3]=='t')
		{
			exit(0);
			return;
		}
		else
		if(arr[0][0]=='p'&&arr[0][1]=='r'&&arr[0][2]=='o'&&arr[0][3]=='c'&&arr[0][4]=='i'&&arr[0][5]=='n'&&arr[0][6]=='f'&&arr[0][7]=='o')
			{int s = atoi( arr[1] );
			// printf(1,"proc %d",s);
			procinfo(s);
			// printf(1,"hii");
		}
			else
			if(check(arr[0])==0){
					printf(1,"%sIllegal command or arguments\n",arr[0]);
					// continue;
					return;
				}
		else
					exec(arr[0],arr);
  }
  void pipe1(char arra[50],char arrb[50]){
	int p[2];
	// pipe(p);
	if(pipe(p) < 0){
		printf(1,"panic");
		exit(-1);
	}
	if(fork()==0){
		close(1);

       dup(p[1]);

       close(p[0]);

       close(p[1]);

       int ct;
  		char *marr[100],*a[50],*b[50];
  		if(parsepipe(arra,marr,'<',&ct)){
				// printf(2,"par#%s#%s#%s#",arrb,marr[0],marr[1]);
				parse(marr[0],a);
				// printf(2,":%s'%s: ",a[0],a[1]);
				parse(marr[1],b);
				// printf(2,":%s: ",b[0]);
				redirei(a,b);
			}
			else{
				parse(arra,a);
       runcmd(a);
     }
	}
	if(fork()==0){
		close(0);

       dup(p[0]);

       close(p[0]);

       close(p[1]);
		int ct;
		char *marr[100],*a[50],*b[50];
		if(parsepipe(arrb,marr,'>',&ct)){
				// printf(2,"redir%s''",marr[0]);
				parse(marr[0],a);
				// printf(2,":%s'%s: ",a[0],a[1]);
				parse(marr[1],b);
				// printf(2,":%s: ",b[0]);
				redire(a,b);
			}
			else{
				parse(arrb,a);
       runcmd(a);
     }
			
	}
	close(p[0]);
    close(p[1]);
    wait(0);
    wait(0);
    // wait(&status1);
    // wait(&status2);
    return;
  }
  void parallee(char arra[50],char arrb[50]){
  	// printf(2,"|%s|\n",arra);

  	if(fork()==0){
  		// firstf(a);
  		// printf(2,"f1%s\n",arra);
  		int ct;
  		char *marr[100],*a[50],*b[50];
  		if(parsepipe(arra,marr,'>',&ct)){
				// printf(2,"par%s''",marr[0]);
				parse(marr[0],a);
				// printf(2,":%s'%s: ",a[0],a[1]);
				parse(marr[1],b);
				// printf(2,":%s: ",b[0]);
				redire(a,b);
			}
			else if(parsepipe(arra,marr,'<',&ct)){
				// printf(2,"par#%s#%s#%s#",arrb,marr[0],marr[1]);
				parse(marr[0],a);
				// printf(2,":%s'%s: ",a[0],a[1]);
				parse(marr[1],b);
				// printf(2,":%s: ",b[0]);
				redirei(a,b);
			}
			else{
				// printf(2,"%s:\n",arra);
				parse(arra,a);
				// printf(2,"gc:%s:%s",a[0],arra);
       runcmd(a);
     }
	}
	if(fork()==0){
		// firstf(b);
		// printf(2,"f1%s\n",arrb);
		int ct;
		char *marr[100],*a[50],*b[50];
		if(parsepipe(arrb,marr,'>',&ct)){
				// printf(2,"redir%s''",marr[0]);
				parse(marr[0],a);
				// printf(2,":%s'%s: ",a[0],a[1]);
				parse(marr[1],b);
				// printf(2,":%s: ",b[0]);
				redire(a,b);
			}
			else if(parsepipe(arrb,marr,'<',&ct)){
				// printf(2,"redir#%s#%s#%s#",arrb,marr[0],marr[1]);
				parse(marr[0],a);
				// printf(2,":%s'%s: ",a[0],a[1]);
				parse(marr[1],b);
				// printf(2,":%s: ",b[0]);
				redirei(a,b);
			}
			else{
				parse(arrb,a);
				// printf(2,"%s\n",arrb);
       runcmd(a);
     }
	}
    wait(0);
    wait(0);
    return;
  }
  void redire(char *a[50],char *b[50]){ //">"
  	// fd = open(b[0], O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
  	int fd;//ret;
  	close(1);
  	if((fd=open(b[0], O_CREATE|O_WRONLY)) < 0){
      printf(2, "open %s failed\n", b[0]);
      exit(-1);
    }
		dup(fd);
		runcmd(a);
		close(fd);
		exit(0);
	// close(fd);
  }
  void redireb(char *a[50],char *b[50],char *c[50]){ //"<"
  	// fd = open(b[0], O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
  	int fd,fd1;//ret;
  	close(0);
  	if((fd=open(b[0], O_RDONLY)) < 0){
      printf(2, "open %s failed\n", b[0]);
      exit(-1);
    }
    close(1);
    if((fd1=open(c[0], O_CREATE|O_WRONLY)) < 0){
      printf(2, "open %s failed\n", b[0]);
      exit(-1);
    }
		dup(fd);
		dup(fd1);
		runcmd(a);
		close(fd);
		close(fd1);
		exit(0);	
  }
    void redirei(char *a[50],char *b[50]){ //"<"
  	// fd = open(b[0], O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
  	int fd;//ret;
  	close(0);
  	if((fd=open(b[0], O_RDONLY)) < 0){
      printf(2, "open %s failed\n", b[0]);
      exit(-1);
    }
		dup(fd);
		runcmd(a);
		close(fd);
		exit(0);	
  }
  void secondf(char * buf){

  		char *arr[50];
			char *marr[100],*a[50],*b[50],*marr1[100],*t1[50],*t2[50];
			int ct;
			
			if(parsepipe(buf,marr,'<',&ct)){
				parse(marr[0],a);
				if(parsepipe(marr[1],marr1,'>',&ct)){
					parse(marr1[0],t1);
					parse(marr1[1],t2);
					redireb(a,t1,t2);
				}
				else{
				// printf(2,"redir#%s#%s#%s#",buf,marr[0],marr[1]);
				// parse(marr[0],a);
				// printf(2,":%s'%s: ",a[0],a[1]);
				parse(marr[1],b);
				// printf(2,":%s: ",b[0]);
				redirei(a,b);
			}
			}
			else if(parsepipe(buf,marr,'>',&ct)){
				// printf(2,"redir%s''",marr[0]);
				parse(marr[0],a);
				// printf(2,":%s'%s: ",a[0],a[1]);
				parse(marr[1],b);
				// printf(2,":%s: ",b[0]);
				redire(a,b);
			}
			else{
				// printf(2,"here");
			parse(buf,arr);

				// printf(2,"here%s\n",arr[0]);
			runcmd(arr);
				}

  }
  void firstf(char *buf){

  	char *arr[50];
			char *marr[100];//*a[50],*b[50];
			int ct=0,status1,status2,ch=0;
  			if(parsepipe(buf,marr,';',&ct)){
				// printf(2,"cmd |%s|%s|",marr[0],marr[1]);
				parallee(marr[0],marr[1]);
			}
			else
				if((ch=parseseq(buf,arr))!=0){
			// printf(2,"%d\n",ch);
			if(fork()==0){	// 2||	1&&
				secondf(arr[0]);
			}
			else{	
				wait(&status1);
				// printf(2,"%d",status1);
				if((status1==0 && ch==1)||(status1==-1 && ch==2)){
					if(fork()==0){
						secondf(arr[1]);
					}
					else wait(&status2);
				}
			}


		}
		else
			if(parsepipe(buf,marr,'|',&ct)!=0)
			{
				pipe1(marr[0],marr[1]);
			}
			

			else{
				// printf(2,"here%s\n",arr[0]);
				secondf(buf);
			// runcmd(arr);
				}
				return;
  }
 int parseseq(char *cm,char **arr){
  	char temp[50];
  	memset(temp,0,50);
	int k=0,l=0,ret=0,i;
	for(i=0;i<strlen(cm)-1;i++)
	{if((cm[i]=='&' && cm[i+1]=='&')||(cm[i]=='|' && cm[i+1]=='|')){
		// deli='&';
		if(cm[i]=='&')		ret=1;
		else ret=2;
		// printf(2,"%d",ret);
		if(strlen(temp)!=0){
		arr[k]=(char *)malloc(strlen(temp)+2);
		// ret=1;
		// pipecmd->left
		temp[l++]=' ';
		temp[l]='\0';
		// ct++;

		strcpy(arr[k],temp);
		k++;
		// temp[0]='\0';
		memset(temp,0,50);
		l=0;
		break;
	}
	}
	else{
		temp[l++]=cm[i];
	}
	}
	l=0;
	for(i=i+2;i<strlen(cm);i++){
		temp[l++]=cm[i];
	}
	arr[k]=(char *)malloc(strlen(temp)+2);
	temp[l++]=' ';
	temp[l]='\0';
	strcpy(arr[k],temp);
	k++;
	// for(int i=0;i<k;i++)
	// 	printf(2,"@%s@",arr[i]);
	// printf(2,"\n");
	return ret;
  }
  int exit1(){
  	exit(2);
  	return 0;
  }
int main(){
	static char buf[100];
	int status;//ch;//status1,status2;
	// int fd;
	while(1){
		printf(2,"MyShell> ");
		memset(buf, 0, 100);
	    gets(buf, 100);
		if(fork()==0){
					char *arr[50];
			// char *marr[100],*a[50],*b[50];
			// int ct=0;
			// printf(2,"in fork"); 
					// executeCommands
			if(buf[0]=='e' && buf[1]=='x'&&buf[2]=='e'&&buf[3]=='c'&&buf[4]=='u'&&buf[5]=='t'&&buf[6]=='e'&&buf[7]=='C'&&buf[8]=='o'&&buf[9]=='m'&&buf[10]=='m'&&buf[11]=='a'&&buf[12]=='n'&&buf[13]=='d'&&buf[14]=='s'){
				parse(buf,arr);
				executeCommands(arr[1]);
			}
			else if(buf[0]=='e'&&buf[1]=='x'&&buf[2]=='i'&&buf[3]=='t')
		{
			exit1();
			return 0;
			// if(r==0)	printf(2,"exit here");	
				// exit(0);

		}
			else	firstf(buf);
		}
		else
		wait(&status);
	// printf(1,"%d\n",status); 
	if(status==2)	break;
	// close(fd);
	}
	exit(0);
	return 0;
}
