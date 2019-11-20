/*
# 16CE10024

# R.K.S.Jaswanth

# Assignment-6

# While executing the file,
  Please use the following command for compliation --> gcc 16CE10024_6.c -lm 
    &
  Use the following command for execution - ./a.out 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int* numof_r_c(char *fname);
void input_csv(int r,char *fname,int **data);

struct training_instance
{
	int *x;
	int y;	
};

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
	int **data,**test,row,col,t_row,i,j,*label,*t_label,*a;
	double n,*wt,*dwt,sgm,o,err;
	n = 0.1;	
	struct training_instance *X;
	char df_name[50],tf_name[50];
	FILE *f_out;

	strcpy(df_name, "data6.csv");
    strcpy(tf_name, "test6.csv");

    a = numof_r_c(df_name);
    row = a[0];
    col = a[1];

    a = numof_r_c(tf_name);
    t_row = a[0];

	wt = (double *)malloc((col-1)*sizeof(double));
	dwt = (double *)malloc((col-1)*sizeof(double));

	label = (int *)malloc(row*sizeof(int));
	t_label = (int *)malloc(t_row*sizeof(int));
 
	X = (struct training_instance *)malloc(row*sizeof(struct training_instance));
	for (i = 0; i < row; ++i)
	{
		X[i].x = (int *)malloc((col-1)*sizeof(int));
	}

	data = (int **)malloc(row*sizeof(int *));
    for(i=0;i<row;i++)
    {
        data[i] = (int *)malloc(col*sizeof(int));
    }
    
    test = (int **)malloc(t_row*sizeof(int *));
    for(i=0;i<t_row;i++)
    {
        test[i] = (int *)malloc((col-1)*sizeof(int));
    }

    input_csv(row,df_name,data);
    input_csv(t_row,tf_name,test);

    f_out = fopen("16CE10024_6.out","w");

	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < col-1; ++j)
		{
			X[i].x[j] = data[i][j];
		}

		X[i].y = data[i][col-1];
	}

	for (i = 0; i < col-1; ++i)
		{
			wt[i] = 0.5;
		}

	for (int m = 0; m < 10; ++m)
	{
		for (i = 0; i < row; ++i)
		{
			o = 0.0;
				
			for (j = 0; j < col-1; ++j)
			{
				o += wt[j]*(X[i].x[j]);
			}

			sgm = (1/(1+(exp(-o))));

			if(sgm>0.5)
				label[i] = 1;
			else
				label[i] = 0;
		}

		for (i = 0; i < col-1; ++i)
		{
			err = 0.0;
			for (j = 0; j < row; ++j)
			{
				err += (X[j].y-label[j])*(X[j].x[i]); 
			}

			dwt[i] = n*err;

			wt[i] += dwt[i];
		}	
	}

	for (i = 0; i < t_row; ++i)
	{
		for (j = 0; j < col-1; ++j)
		{
			X[i].x[j] = test[i][j];
		}
	}

	for (i = 0; i < t_row; ++i)
		{
			o = 0.0;
				
			for (j = 0; j < col-1; ++j)
			{
				o += wt[j]*(X[i].x[j]);
			}

			sgm = (1/(1+(exp(-o))));

			if(sgm>0.5)
				t_label[i] = 1;
			else
				t_label[i] = 0;
		}

	for (i = 0; i < t_row; ++i)
	{
		fprintf(f_out,"%d \t",t_label[i]);
	}

	fclose(f_out);

	return 0;
}