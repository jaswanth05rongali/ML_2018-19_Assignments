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
    char d_name[25],str[1000],*p,t_name[25],z;
    int i=0,j,r=0,c=0,tr=0,a[20][9],t[4][8];
    int b[C-1];
    FILE *fd;
    FILE *ft;

    strcpy(d_name,"data3.csv");
    strcpy(t_name,"test3.csv");

    fd = fopen(d_name,"r");
    ft = fopen(t_name,"r");

    for(z=getc(fd);z!=EOF;z=getc(fd))
    {
        if(z=='\n')
        {
            r = r+1;
        }
        c = c+1;
    }
    c = c/(r*2);

    for(z=getc(ft);z!=EOF;z=getc(ft))
    {
        if(z=='\n')
        {
            tr = tr+1;
        }
    }

    a = (int **)malloc(r*sizeof(int *));
    for(i=0;i<r;i++)
    {
        a[i] = (int *)malloc(c*sizeof(int));
    }

    t = (int **)malloc(tr*sizeof(int *));
    for(i=0;i<tr;i++)
    {
        t[i] = (int *)malloc((c-1)*sizeof(int));
    }

    /*
    for(i=0;i<r;i++){
        for(j=0;j<c;j++) a[i][j]=1;
    }

    for(i=0;i<tr;i++){
        for(j=0;j<c-1;j++) t[i][j]=1;
    }*/

    // for(i=0;i<r;i++){
    //     for(j=0;j<c;j++){
    //         cout<<a[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    // for(int f=0;f<tr;f++){
    //     for(int e=0;e<c-1;e++){
    //         cout<<t[f][e]<<" ";
    //     }
    //     cout<<endl;
    // }

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
  double k,s;
  k=pp(0,inf);
  s=pp(1,inf);
  cout <<k<<endl;
  cout <<s<<endl;
  // checking total probability
  for(int i=0;i<4;i++){
  double r1,r2;
  r1=r*pop(t[i],inf,0);
  r2=s*pop(t[i],inf,1);
  cout<<r1<<endl<<r2<<endl;
  if(r1>r2)
    cout <<0<<endl;
  else
    cout <<1<<endl;
  }
    return 0;
}
















