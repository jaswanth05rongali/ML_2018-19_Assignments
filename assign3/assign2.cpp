//16EE10037

//RAYAVARAPU RAJA INGERSOLL

//PROGRAMMING ASSIGNMENT - 3

//Normal Compilation and Execution of Program i.e. g++ 16EE10037_3.cpp and ./a.out
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#define R 20
#define C 9
using namespace std;
//CREaTING A STRUCTURE
    struct tab{
        int c=0,d=0;
    };
//cal pot prob
  double pop(int b[],tab inf[][C],int s){
      double p1=1;
    for(int i=0;i<(C-1);i++){

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

double pp(int p,tab inf[][C]);
double pp(int p,tab inf[][C]){

     if(p==0){
        double y;
        y=((1.0*inf[p][C-1].c)/(inf[p][C-1].c +inf[p+1][C-1].c));
        return y;
     }
     else{
        double y;
        y=((1.0*inf[p][C-1].c)/(inf[p][C-1].c +inf[p-1][C-1].c));
        return y;
     }

   return 0;

  }
//cal posterio

int main()
{
    //input
    int a[20][9],t[4][8],i,j;
    char d_name[25],str[1000],*p,t_name[25],z;    
    int b[C-1];

    FILE *fd;
    FILE *ft;

    strcpy(d_name,"data3.csv");
    strcpy(t_name,"test3.csv");

    fd = fopen(d_name,"r");
    ft = fopen(t_name,"r");
    
    i=0;
    while(!feof(fd))
    {
        fgets(str,1000,fd);
    
        p = strtok(str,",");

        for(j=0;(p!=0);)
        {
            a[i][j] = atof(p);
            p = strtok(NULL,",");
            j++;
        }
        i++;
    }

    i=0;
    while(!feof(ft))
    {
        fgets(str,1000,ft);
    
        p = strtok(str,",");

        for(j=0;(p!=0);)
        {
            t[i][j] = atof(p);
            p = strtok(NULL,",");
            j++;
        }
        i++;
    }

    //TABULATING TABLE 3
    tab inf[2][C];
    for(int i=0;i<R;i++){
        if(a[i][C-1]==0){
            inf[0][C-1].c+=1;
        }
        else{
            inf[1][C-1].c+=1;
        }
    };
    //tabulating remaining rows
    for(int j=0;j<(C-1);j++){

        for(int k=0;k<R;k++){
            if(a[k][C-1]==0){

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
        for(int j=0;j<C;j++){
            cout<<inf[i][j].c<<endl;
            cout<<inf[i][j].d<<endl;
        }
    }
  //checking condition prior prob
  FILE *op;
  op = fopen("16EE10037_3.out","w");
  double r,s;
  r=pp(0,inf);
  s=pp(1,inf);
  cout <<r<<endl;
  cout <<s<<endl;
  // checking total probability
  for(int i=0;i<4;i++){
  double r1,r2;
  r1=r*pop(t[i],inf,0);
  r2=s*pop(t[i],inf,1);
  cout<<r1<<endl<<r2<<endl;
  if(r1>r2)
    fprintf(op,"0\t");
  else
    fprintf(op,"1\t");
  }

    return 0;
}
















