#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

struct dis{
   double val;
   double out;

};

void fi(double **a,double *b,dis *res,int r, int col, int tr,FILE *fout){

    for(int i=0;i<r;i++){
          double pro=1.0;
        for(int j=0;j<col-1;j++){
            pro+=((b[j]-a[i][j])*(b[j]-a[i][j]));
        }
         res[i].val=pro;
         res[i].out=a[i][4];
}
    int c1=0,c2=0;
    for(int h=0;h<col;h++){
        double mi=1000000000.0,in=-1;
        for(int k=0;k<r;k++)
        {
            if(res[k].val>=0&&res[k].val<mi){
                mi=res[k].val;
                in=res[k].out;
                res[k].val=-1;
            }
        }
        if(in==1)
           c1+=1;
        else
           c2+=1;
    }

    if(c1>c2)
        fprintf(fout, "1\t");
    else
        fprintf(fout, "0\t");
}

void getDim(char *d,int &r,int &col){
  
  int temp;
  char z;
  FILE *fd;
  fd=fopen(d,"r");
  r = 0;
  for(z=fgetc(fd),col=0;(z!=EOF)&&(z!='\n');z=fgetc(fd))
  {
      if(z==',')
      {
          col++;
      }
  }
  r = col;
  for(;(z!=EOF);z=getc(fd))
    {
        if(z==',')
        {
            col = col+1;
        }
    }

    temp = col;
    col = r+1;
    r = temp/r;    

    fclose(fd);
}

void getDim1(char *T,int &tr){

    int col,t;
    char z;
    FILE *ft;
    ft=fopen(T,"r");

    for(z=fgetc(ft),col=0;((z!=EOF)&&(z!='\n'));z=fgetc(ft))
      {
          if(z==',')
          {
              col++;
          }
      }
      tr = col;
      for(;z!=EOF;z=getc(ft))
        {
            if(z==',')
            {
                col = col+1;
            }
        }
        t = col;
        col = tr+1;
        tr = t/tr;

    fclose(ft);
}

int main()
{
    int i=0,j=0,r,col,tr;
    char d_name[25],str[1000],*p,t_name[25],z;
    double **data,**test;
    dis *res;

    FILE *fd;
    FILE *ft;
    FILE *fout;

    strcpy(d_name,"data4.csv");
    strcpy(t_name,"test4.csv");

    getDim(d_name,r,col);
    getDim1(t_name,tr);

    fd = fopen(d_name,"r");
    ft = fopen(t_name,"r");
    
    data = (double**)malloc(r*sizeof(double *));
    for(i=0;i<r;i++)
    {
        data[i] = (double*)malloc(col*sizeof(double));
    }

    test = (double**)malloc(tr*sizeof(double *));
    for(i=0;i<tr;i++)
    {
        test[i] = (double*)malloc((col-1)*sizeof(double));
    }

    res = new dis[r];

    i=0;
    while((i<r)&&!feof(fd))
    {

        fgets(str,1000,fd);

        p = strtok(str,",");

        for(j=0;(p!=0)&&(p!=NULL);)
        {

            data[i][j] = atof(p);
            p = strtok(NULL,",");
            j++;
        }
        i++;
    }

    i=0;
    while((i<tr)&&!feof(ft))
    {

        fgets(str,1000,ft);

        p = strtok(str,",");

        for(j=0;(p!=0)&&(p!=NULL);)
        {

            test[i][j] = atof(p);
            p = strtok(NULL,",");
            j++;
        }
        i++;
    }

    fout = fopen("16EE10037_6.out","w");

    for(int v=0;v<tr;v++){
        fi(data,test[v],res,r,col,tr,fout);
    }
    fclose(fout);
    return 0;
}
