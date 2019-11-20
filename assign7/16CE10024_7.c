/*
# 16CE10024

# R.K.S.Jaswanth

# Assignment-7

# While executing the file,
  Please use the following command for compliation --> gcc 16CE10024_7.c -lm 
    &
  Use the following command for execution - ./a.out 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int* numof_r_c(char *fname);
void input_csv(int r,char *fname,int **data);

int* numof_r_c(char *fname)
{
    int r=0,col, *p;
    char c;
    FILE *fp;
    fp = fopen(fname, "r");

    p = (int *)malloc(2*sizeof(int));

    for(c = fgetc(fp),r=0,col=0;(c != '\n')&&(c != EOF); c = fgetc(fp)){
        if(c == ','){
            col++;
        }
    }
    r=col;
    for (;(c != EOF); c = fgetc(fp))
    {     
        if(c == ',')
        {
            col = col + 1;
        }
    }  

    p[1] = r+1;
    r = col/r;

    p[0] = r;
    

    fclose(fp);

    return p;
}

void input_csv(int r,char *fname,int **data)
{
    int i = 0,j = 0;
    char line[2000];
    const char *m;
    FILE *fp;
    fp = fopen(fname, "r");

    for (i = 0;((i < r)&&(fgets(line,2000,fp))); ++i)
    {
        m = strtok(line,",");

        for (j = 0;(m && *m); ++j)
        {
            data[i][j] = atof(m);
            m = strtok(NULL, ",");
        }
    }

    fclose(fp);

    return;
}

int main()
{
	int **data,row,col,i,j,*a;
	int n,p;
	double **mean;
	double dist1,dist2;
	char df_name[50];
	FILE *f_out;

	strcpy(df_name, "data7.csv");

	a = numof_r_c(df_name);
    row = a[0];
    col = a[1];

    data = (int **)malloc(row*sizeof(int *));
    for(i=0;i<row;i++)
    {
        data[i] = (int *)malloc((col+1)*sizeof(int));
    }

    mean = (double **)malloc(2*sizeof(double *));
    for(i=0;i<2;i++)
    {
        mean[i] = (double *)malloc(col*sizeof(double));
    }

    input_csv(row,df_name,data);

    srand(time(0));

    a[0] = rand()%20;
    a[1] = rand()%20;

    if(a[0]==a[1])
    {
    	a[1] = (row-1) - a[0];
    }

    for (i = 0; i < 2; ++i)
    {
       	for (j = 0; j < col; ++j)
       	{
            mean[i][j] = data[a[i]][j];        		
     	}
    }

    for (int m = 0; m < 10; ++m)
    {
    	n = 0;
        p = 0;
        for (i = 0; i < row; ++i)
        {
        	dist1 = 0;
        	dist2 = 0;

        	for (j = 0; j < col; ++j)
        	{
        		dist1 += (data[i][j]-mean[0][j]) * (data[i][j]-mean[0][j]);
        		dist2 += (data[i][j]-mean[1][j]) * (data[i][j]-mean[1][j]);
        	}

            if (sqrt(dist1)<=sqrt(dist2))
            {
            	data[i][col] = 1;            	
            }
            else
            {
            	data[i][col] = 2;
            }        	
        }

        if(m!=9)
        {
        	for (i = 0; i < row; ++i)
        	{
        		if (data[i][col]==1)
        		{
        			for (j = 0; j < col; ++j)
        			{
        				mean[0][j] += data[i][j];        				
        			}
        			p++;
        		}
        		else
        		{
        			for (j = 0; j < col; ++j)
        			{
        				mean[1][j] += data[i][j];        				
        			}
        			n++;
        		}        		
        	}

        	if(p!=0)
        	{
        		for (j = 0; j < col; ++j)
        		{
        			mean[0][j] /= p;
        		}
        	}

        	if(n!=0)
        	{
        		for (j = 0; j < col; ++j)
        		{
        			mean[1][j] /= n;
        		}
        	}
        }    	
    }

    f_out = fopen("16CE10024_7.out","w");

    for (i = 0; i < row; ++i)
    {
    	fprintf(f_out, "%d\t",data[i][col]);
    }
    fclose(f_out);
    free(a);
    free(data);
    free(mean);
	
	return 0;
}
