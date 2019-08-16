#include <cstdio>
#include <cstdlib>

double *ip1_change(double ***input)
{
    double *ip1 = (double *)malloc(50*4*4*sizeof(double));

    for(int channel=0;channel<50;channel++)
    {
        for(int rows=0;rows<4;rows++)
        {
            for(int cols=0;cols<4;cols++)
            {
                ip1[(channel*4*4)+(rows*4)+cols] = input[channel][rows][cols];
            }
        }
    }

    return ip1;
}

double *ip1_exe(double *input, double **weight)
{
    double *ip1_result=(double *)malloc(500*sizeof(double));

    for(int i=0;i<500;i++)
    {
        for(int j=0;j<800;j++)
        {
            ip1_result[i] += input[j] * weight[i][j]; 
        }
    }

    return ip1_result;
}

double *ReLU(double *input)
{
    for(int activation=0; activation<500; activation++)
    {
        if(input[activation]<=0) input[activation]=0;
    }

    //return input;
}

double *ip2_exe(double *input, double **weight)
{
    double *ip2_result=(double *)malloc(10*sizeof(double));

    for(int i=0;i<10;i++)
    {
        for(int j=0;j<500;j++)
        {
            ip2_result[i] += input[j] * weight[i][j]; 
        }
    }

    return ip2_result;
}