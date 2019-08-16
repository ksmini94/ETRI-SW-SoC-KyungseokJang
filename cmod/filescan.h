#include <cstdio>
#include <cstdlib>

double ****conv1_scan(void)
{
    FILE *fp;
    char temp_one;
    char temp[30] = {0};

    fp = fopen("weight.txt","r");
    for(int i=0;i<7;i++)
    {
        fscanf(fp,"%s",temp);
    }
    for(int j=0;j<5;j++)
    {
        fscanf(fp,"%c",&temp_one);
    }

    double ****Filter_input;

    Filter_input=(double ****)malloc(20*sizeof(double ***));
    for(int num=0; num<20; num++)
    {
        *(Filter_input+num)=(double ***)malloc(1*sizeof(double **));
        for(int channel=0;channel<1;channel++)
        {
            *(*(Filter_input+num)+channel)=(double **)malloc(5*sizeof(double *));
            for(int rows=0;rows<5;rows++)
            {
                *(*(*(Filter_input+num)+channel)+rows)=(double *)malloc(5*sizeof(double));
            }
        }    
    }

    for(int m=0;m<20;m++)
    {
        for(int l=0;l<5;l++)
        {
            for(int k=0;k<5;k++)
            {
                fscanf(fp,"%lf",&Filter_input[m][0][l][k]);
                fscanf(fp,"%c",&temp_one);
                fscanf(fp,"%c",&temp_one);
            }

        fscanf(fp,"%c",&temp_one);
        fscanf(fp,"%c",&temp_one);
        fscanf(fp,"%c",&temp_one);
        }

    fscanf(fp,"%c",&temp_one);
    fscanf(fp,"%c",&temp_one);
    fscanf(fp,"%c",&temp_one);
    fscanf(fp,"%c",&temp_one);
    }

    fclose(fp);

    return Filter_input;
}

double ****conv2_scan(void)
{
    FILE *fp;
    char temp_one;
    char temp[30] = {0};
    double weight=0;
    fp = fopen("weight.txt","r");
    for(int i=0;i<514;i++)
    {
        fscanf(fp,"%s",temp);
    }
    
    for(int j=0;j<5;j++)
    {
        fscanf(fp,"%c",&temp_one);
    }

    double ****Filter_input;

    Filter_input=(double ****)malloc(50*sizeof(double ***));
    for(int num=0; num<50; num++)
    {
        *(Filter_input+num)=(double ***)malloc(20*sizeof(double **));
        for(int channel=0;channel<20;channel++)
        {
            *(*(Filter_input+num)+channel)=(double **)malloc(5*sizeof(double *));
            for(int rows=0;rows<5;rows++)
            {
                *(*(*(Filter_input+num)+channel)+rows)=(double *)malloc(5*sizeof(double));
            }
        }    
    }
    for(int l=0;l<50;l++)
    {
    for(int k=0;k<20;k++)
    {
    for(int j=0;j<5;j++)
    {
    for(int i=0;i<5;i++)
    {
        fscanf(fp,"%lf",&Filter_input[l][k][j][i]);
        fscanf(fp,"%c",&temp_one);
        fscanf(fp,"%c",&temp_one);
    } 
    fscanf(fp,"%c",&temp_one);
    fscanf(fp,"%c",&temp_one);
    }
    fscanf(fp,"%c",&temp_one);
    fscanf(fp,"%c",&temp_one);
    }   

    fscanf(fp,"%c",&temp_one);
    fscanf(fp,"%c",&temp_one);
    }

    return Filter_input;
}

double **ip1_scan(void)
{
    FILE *fp;
    char temp_one;
    char temp[30] = {0};
    double weight=0;
    fp = fopen("weight.txt","r");

    double **Filter_input;

    Filter_input=(double **)malloc(500*sizeof(double *));
    for(int i=0;i<500;i++)
    {
        *(Filter_input+i)=(double *)malloc(800*sizeof(double));
    }

    for(int i=0;i<25519;i++)
    {
        fscanf(fp,"%s",temp);
    }

    for(int i=0;i<3;i++)
    {
        fscanf(fp,"%c",&temp_one);
    }
    
    for(int j=0;j<500;j++)
    {
        for(int k=0;k<800;k++)
        {
            fscanf(fp,"%lf",&Filter_input[j][k]);
            fscanf(fp,"%c",&temp_one);
            fscanf(fp,"%c",&temp_one);
        }
    fscanf(fp,"%c",&temp_one);
    fscanf(fp,"%c",&temp_one);
    fscanf(fp,"%c",&temp_one);
    }

    return Filter_input;
}

double **ip2_scan(void)
{
    FILE *fp;
    char temp_one;
    char temp[30] = {0};
    double weight=0;
    fp = fopen("weight.txt","r");

    double **Filter_input;

    Filter_input=(double **)malloc(10*sizeof(double *));
    for(int i=0;i<10;i++)
    {
        *(Filter_input+i)=(double *)malloc(500*sizeof(double));
    }

    for(int i=0;i<425519;i++)
    {
        fscanf(fp,"%s",temp);
    }

    for(int i=0;i<5;i++)
    {
        fscanf(fp,"%s",temp);
    }

    for(int i=0;i<3;i++)
    {
        fscanf(fp,"%c",&temp_one);
    }

    for(int j=0;j<10;j++)
    {
        for(int k=0;k<500;k++)
        {
            fscanf(fp,"%lf",&Filter_input[j][k]);          
            fscanf(fp,"%c",&temp_one);
            fscanf(fp,"%c",&temp_one);
        }
    fscanf(fp,"%c",&temp_one);
    fscanf(fp,"%c",&temp_one);
    }

    return Filter_input;
}