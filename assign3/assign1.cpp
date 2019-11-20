//16EE10037

//RAYAVARAPU RAJA INGERSOLL

//PROGRAMMING ASSIGNMENT - 3

//Normal Compilation and Execution of Program i.e. g++ 16EE10037_3.cpp and ./a.out
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

double pp(int p,struct tab **inf,int col);
double pop(int b[],struct tab **inf,int s,int col);
//CREaTING A STRUCTURE
    struct tab{
        int c=0,d=0;
    };
//cal pot prob
  double pop(int b[],struct tab **inf,int s,int col){
      double p1=1;
    for(int i=0;i<(col-1);i++){

        if(b[i]==0){
            double y;
            y=((1.0*inf[s][i].c)+1)/((inf[s][i].c +inf[s][i].d)+2);
            p1*=y;
        }
        else{
            double y;
            y=((1.0*inf[s][i].d)+1)/((inf[s][i].c +inf[s][i].d)+2);
            p1*=y;
        }

    }

   return p1;

  }

double pp(int p,struct tab **inf,int col){

     if(p==0){
        double y;
        y=((1.0*inf[p][col-1].c)/(inf[p][col-1].c +inf[p+1][col-1].c));
        return y;
     }
     else{
        double y;
        y=((1.0*inf[p][col-1].c)/(inf[p][col-1].c +inf[p-1][col-1].c));
        return y;
     }

   return 0;

  }
//cal posterio

void getDim(char *d,int &r,int &col){
  FILE *fd;
  fd=fopen(d,"r");
  for(char z=getc(fd);z!=EOF;z=getc(fd))
    {
        if(z=='\n')
        {
            r = r+1;
        }
        col = col+1;
    }
    col = col/(r*2);
    fclose(fd);
}

void getDim1(char *T,int &tr){
    FILE *ft;
    ft=fopen(T,"r");
    for(char z=getc(ft);z!=EOF;z=getc(ft))
    {
        if(z=='\n')
        {
            tr = tr+1;
        }
    }
    fclose(ft);
}
int main()
{
    //input
    int i=0,j=0,r=0,col=0,tr=0;
    char d_name[25],str[1000],*p,t_name[25],z;    

    FILE *fd,*fd1;
    FILE *ft,*ft1;

    strcpy(d_name,"data3.csv");
    strcpy(t_name,"test3.csv");

    fd = fopen(d_name,"r");
    ft = fopen(t_name,"r");

    getDim(d_name,r,col);
    getDim1(t_name,tr);

     

    int **a = new int*[r];
    for(i=0;i<r;i++)
    {
        a[i] = new int [col];
    }

    int **t = new int*[tr];
    for(i=0;i<tr;i++)
    {
        t[i] = new int[col-1];
    }

    // fd = fopen(d_name,"r");
    // ft1 = fopen(t_name,"r");
    
    i=0;
    while(i<r&&!feof(fd))
    {
         
        fgets(str,1000,fd);
    
        p = strtok(str,",");

        for(j=0;(p!=0)&&(p!=NULL);)
        {
             
            a[i][j] = atof(p);
            p = strtok(NULL,",");
            j++;
        }
        i++;
    }

    i=0;
    while(i<tr&&!feof(ft))
    {
         
        fgets(str,1000,ft);
    
        p = strtok(str,",");

        for(j=0;(p!=0)&&(p!=NULL);)
        {
             
            t[i][j] = atof(p);
            p = strtok(NULL,",");
            j++;
        }
        i++;
    }

    for(i=0;i<r;i++){
        for(j=0;j<col;j++){
             
        }
         
    }

    for(int f=0;f<tr;f++){
        for(int e=0;e<col-1;e++){
             
        }
         
    }

    //TABULATING TABLE 3
    struct tab **inf;
    inf = (tab **)malloc(2*sizeof(tab *));
    for (i = 0; i < 2; ++i)
    {
      inf[i] = (tab *)malloc(col*sizeof(tab));
    }
    for(int i=0;i<r;i++){
        if(a[i][col-1]==0){
            inf[0][col-1].c+=1;
        }
        else{
            inf[1][col-1].c+=1;
        }
    };
    //tabulating remaining rows
    for(int j=0;j<(col-1);j++){

        for(int k=0;k<r;k++){
            if(a[k][col-1]==0){

                  if(a[k][j]==0){
                    inf[0][j].c+=1;
                   }
                  else{
                    inf[0][j].d+=1;
                  }

            }
            else{

                 if(a[k][j]==0){
                    inf[1][j].c+=1;
                   }
                  else{
                    inf[1][j].d+=1;
                  }


            }
        };
    };
  //checking condition for values in table
    for(int i=0;i<2;i++){
        for(int j=0;j<col;j++){
             
             
        }
    }
  //checking condition prior prob
  double k,s;
  k=pp(0,inf,col);
  s=pp(1,inf,col);
   
   
  // checking total probability
  FILE* op;
  op=fopen("16EE10037_3.out","w");
  for(int i=0;i<tr;i++){
  double r1,r2;
  r1=k*pop(t[i],inf,0,col);
  r2=s*pop(t[i],inf,1,col);
   
  if(r1>r2)
     fprintf(op, "0\t" );
  else
     fprintf(op, "1\t" );
  }

    return 0;
}
















