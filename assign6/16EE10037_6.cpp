

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

float func(float x) {
	return 1/(1+exp(-x));		//Write function here
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

int main() {
	int r,c,tr,iterations=10;									// Initialise these all
	int k,i,j;
	char d_name[25],str[1000],*p,t_name[25],z;
	FILE *fd;
    FILE *ft;
    FILE *fout;

    strcpy(d_name,"data6.csv");
    strcpy(t_name,"test6.csv");

    getDim(d_name,r,c);
    getDim1(t_name,tr);

    fd = fopen(d_name,"r");
    ft = fopen(t_name,"r");

	int data[r][c],test[tr][c];
	float w[c],deltaw[c],o[r],eta=0.1;

	for(j=0;j<c;j++) w[j] = 0.5;											// w initialisation

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
		
	cout << endl;
	for(k=0;k<iterations;k++){

		for(i=0;i<r;i++) o[i]=0;
		for (i = 0; i < r; ++i)
		{
			for(j=0;j<c-1;j++) {
				o[i]+=w[j]*data[i][j];
			}
			o[i]=func(o[i])>0.5 ? 1 : 0;  // For each row, 1 or 0?
		}
		for(j=0;j<c-1;j++){
			for(j=0;j<c-1;j++) deltaw[j]=0;
			for(i=0;i<r;i++) {
				deltaw[j] += data[i][j]*(data[i][c-1]-o[i]);
			}
			deltaw[j]*=eta;
			w[j] += deltaw[j];
		}

	}
	for(i=0;i<tr;i++){
		o[i]=0;
		for(j=0;j<c-1;j++){
			o[i]+=w[j]*test[i][j];
		}
		test[i][c-1] = o[i]>0.5 ? 1 : 0;
	}

	for(i=0;i<tr;i++){
		fprintf(fout, "%d \t",test[i][c-1]);
	}
	
	return 0;
}