#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct tree* newNode(int attr);
int nplus(int **A,int r,int c);
double log_2(double p);
double entropy(int **set,int row,int col);
double info_gain(int **data,int row,int col,int a,int *p,int *q,int **set1,int **set0);
void implement_dtree(struct tree *root,int **data,int r,int c);
void test_dtree(struct tree *root, int **test,int row,int col);
int test_case(struct tree *root,int *a,int col);
// int* num_r_c(char *fname);
// void inputcsv(int r,char *fname, int **data);

// struct tree{
//     int val;
//     struct tree *left;
//     struct tree *right;
// };

// struct tree* newNode(int attr)
// {
//     struct tree *node;

//     node = (struct tree*)malloc(sizeof(struct tree));

//     node -> val = attr;
//     node -> left = NULL;
//     node -> right = NULL;

//     return(node);
// }

int nplus(int A[24][9],int r,int c)
{
	int i,j;

	for (i = 0,j=0; i < r; ++i)
	{
		if(A[i][c-1]==1)
		{
			j++;
		}
	}

	// printf("%d\n", j);

	return j;
}

double log_2(double p)
{
	double val,n,d;

	if (p==0.0)
	{
		return 0.0;
	}

	n = log10(p);
	d = log10(2.0);

	val = (n/d);
	return val;
}

double entropy(int set[24][9],int row,int col){

	double e,p1,p2,m,n;
	int i,j;

	j = nplus(set,row,col);
	i = row - j;

	m = (double)i;
	n = (double)j;

	p1 = (n/(m+n));
	p2 = (m/(m+n)); 

	e = -(p1*log_2(p1))-(p2*log_2(p2));

	// printf("%lf\n",e);

	return e;
}

double info_gain(int **data,int row,int col,int a){

	int i,j,p,q,set1[24][9],set0[24][9];
	double e0,e1,e2,ig,m,n;	

	e0 = entropy(data,row,col);
	// printf("%lf\n",e0);

	for (i = 0,(p) = 0,(q) = 0; i < row; ++i)
	{
		if(data[i][a]==1)
		{
			for (j = 0; j < col; ++j)
			{
				set1[(p)][j] = data[i][j];
			}
			(p)++;
		}
		else
		{
			for (j = 0; j < col; ++j)
			{
				set0[(q)][j] = data[i][j];
			}
			(q)++;
		}
	}

	e1 = entropy(set1,(p),col);
	e2 = entropy(set0,(q),col);

	m = (double)(p);
	n = (double)(q);

	ig = e0 - (m/(m+n))*e1 - (n/(m+n))*e2;

	printf("%lf\n",ig );

	return ig;
}

// void implement_dtree(struct tree *root,int **data,int r,int c)
// {
// 	int i,a,p,q,**set1,**set0,*m,*n;
// 	double igain,max=-1.0;

// 	m = &p;
// 	n = &q;

// 	// printf("hiii\n");

// 	if(entropy(data,r,c)==0.0)
// 	{
// 		if(data[0][c-1]==1)
// 		{
// 			root = newNode(500);
// 			return;
// 		}
// 		else
// 		{
// 			root = newNode(-500);
// 			return;
// 		}
// 	}
// 	else
// 	{
// 		set1 = (int **)malloc(r*(sizeof(int *)));
// 		set0 = (int **)malloc(r*(sizeof(int *)));
// 		for (i = 0; i < r; ++i)
// 		{
// 			set1[i] = (int *)malloc(c*sizeof(int));
// 			set0[i] = (int *)malloc(c*sizeof(int));
// 		}

// 		// printf("hiii\n");

// 		for (i = 0; i < c-1; ++i)
// 		{
// 			igain = info_gain(data,r,c,i,m,n,set1,set0);

// 			if (igain>max)
// 			{
// 				max = igain;
// 				a = i+1;
// 			}
// 			else if(igain == max)
// 			{
// 				if(a-1>i)
// 				{
// 					a = i+1;
// 				}
// 			}
// 		}

// 		root = newNode(a);
// 		// printf("%lf\n",max);

// 		implement_dtree(root->left,set1,p,c);
// 		implement_dtree(root->right,set0,q,c);
// 	}

// 	for (i = 0; i < r; ++i)
// 	{
// 		free(set1[i]);
// 		free(set0[i]);
// 	}

// 	free(set1);
// 	free(set0);

//     return;
// }

// void test_dtree(struct tree *root, int **test,int row,int col)
// {
// 	int *a,*p;
// 	a = (int *)malloc(row*sizeof(int));
// 	p = (int *)malloc(col*sizeof(int));

// 	for (int i = 0; i < row; ++i)
// 	{
// 		for (int j = 0; j < col; ++j)
// 		{
// 			p[j] = test[i][j]; 
// 		}

// 		a[i] = test_case(root,p,col); 
// 	}

// 	for (int i = 0; i < row; ++i)
// 	{
// 		printf("%d\n",a[i]);
// 	}

// 	free(a);
// 	free(p);

// 	return;
// }

// int test_case(struct tree *root,int *a,int col)
// {
// 	if(((root -> val) == 500)||((root -> val) == -500))
// 	{
// 		if((root->val)==500)
// 		{
// 			return 1;
// 		}
// 		else
// 		{
// 			return 0;
// 		}	
// 	}
// 	else
// 	{
// 		if(a[(root->val)-1]==1)
// 		{
// 			test_case(root->left,a,col);
// 		}
// 		else
// 		{
// 			test_case(root->right,a,col);
// 		}
// 	}
// }

// int* num_r_c(char *fname)
// {
//     int r=0,col, *p;
//     char c;
//     FILE *fp;
//     fp = fopen(fname, "r");

//     p = (int *)malloc(2*sizeof(int));

//     for (c = getc(fp),col=0; c != EOF; c = getc(fp))
//     {
//         if (c == '\n') 
//         {
//             r = r + 1;
//         }
//         col = col + 1;
//     }  

//     col = col/(r*2);

//     p[0] = r;
//     p[1] = col;

//     fclose(fp);

//     return p;
// }

// void inputcsv(int r,char *fname, int **data)
// {
//     int i = 0,j = 0;
//     char line[2000];
//     const char *m;

//     FILE *fp;
//     fp = fopen(fname, "r");

//     for (i = 0;((i < r)&&(fgets(line,2000,fp))); ++i)
//     {
//         m = strtok(line,",");

//         for (j = 0;(m && *m); ++j)
//         {
//             data[i][j] = atof(m);
//             m = strtok(NULL, ",");
//         }
//     }

//     fclose(fp);
// }

int main()
{
	int **data,row,col,i,**test,*p,t_row,t_col,j;
	struct tree *root,*current_node;
	// char f_name[50];

	// if (argc < 1){
 //        printf("Give proper input accordingly.\n");
 //        exit(0);
 //    }

 //    strcpy(f_name, argv[1]);
 //    p = num_r_c(f_name);
 //    row = p[0];
 //    col = p[1];

	data = (int **)malloc(24*(sizeof(int *)));
	for (i = 0; i < 24; ++i)
	{
		data[i] = (int *)malloc(9*sizeof(int));
	}

	// inputcsv(row,f_name, data);

	// strcpy(f_name, argv[2]);
 //    p = num_r_c(f_name);
 //    t_row = p[0];
 //    t_col = p[1];

    test = (int **)malloc(4*(sizeof(int *)));
	for (i = 0; i < 4; ++i)
	{
		test[i] = (int *)malloc(8*sizeof(int));
	}

	for (i = 0; i < 24; ++i)
	{
		/* code */
		for (j = 0; j < 9; ++j)
		{
			/* code */
			scanf("%d",&data[i][j]);
		}
	}

	for (i = 0; i < 4; ++i)
	{
		/* code */
		for (j = 0; j < 8; ++j)
		{
			/* code */
			scanf("%d",&test[i][j]);
		}
	}

	// inputcsv(t_row,f_name, test);

	root = newNode(0);
	current_node = root;

	info_gain(data,24,9,0);

	test_dtree(root,test,4,8);
    
    return 0;
}
