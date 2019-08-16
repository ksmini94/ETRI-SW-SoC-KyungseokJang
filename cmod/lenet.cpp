#include <opencv2/opencv.hpp>
#include <cstdio>
#include <cstdlib>
#include "convolution.h"
#include "pooling.h"
#include "filescan.h"
#include "fullyconnect.h"

using namespace cv;

int main(void)
{
    Mat image;

    image = imread("9.jpg", IMREAD_GRAYSCALE);
    if(image.empty())
    {
        printf("Could not open or find the image\n");
        return -1;
    }

    // Mat image -> 3 dimension pointer (channel - rows -cols)
    double ***jpg=(double ***)malloc(image.channels()*sizeof(double **));
    for(int i=0;i<image.channels();i++)
    {
        *(jpg+i)=(double **)malloc(image.rows*sizeof(double *));
        for(int j=0;j<image.rows;j++)
        {
            *(*(jpg+i)+j)=(double *)malloc(image.cols*sizeof(double));
            for(int k=0;k<image.cols;k++)
            {
                *(*(*(jpg+i)+j)+k)=image.at<uchar>(j,k);    
            }        
        }    
    }

    // 1st convolution size (3 dimension) (number - rows -cols)
    double ***conv1=(double ***)malloc(20*sizeof(double **));
    for(int i=0;i<20;i++)
    {
        *(conv1+i)=(double **)malloc(24*sizeof(double *));
        for(int j=0;j<24;j++)
        {
            *(*(conv1+i)+j)=(double *)malloc(24*sizeof(double));        
        } 
    }

    // 1st convolution filter size (4 dimension) (number - channel - rows- cols)
    double ****conv1_Filter=(double ****)malloc(20*sizeof(double ***));
    for(int num=0; num<20; num++)
    {
        *(conv1_Filter+num)=(double ***)malloc(1*sizeof(double **));
        for(int channel=0;channel<1;channel++)
        {
            *(*(conv1_Filter+num)+channel)=(double **)malloc(5*sizeof(double *));
            for(int rows=0;rows<5;rows++)
            {
                *(*(*(conv1_Filter+num)+channel)+rows)=(double *)malloc(5*sizeof(double));
            }
        }    
    }

    // 1st pooling size (3 dimension) (number - rows - cols)
    double ***pool1=(double ***)malloc(20*sizeof(double **));
    for(int i=0;i<20;i++)
    {
        *(pool1+i)=(double **)malloc(12*sizeof(double *));
        for(int j=0;j<12;j++)
        {
            *(*(pool1+i)+j)=(double *)malloc(12*sizeof(double));        
        } 
    }

    // 2nd convolution size (3 dimension) (number - rows - channel)
    double ***conv2=(double ***)malloc(50*sizeof(double **));
    for(int i=0;i<50;i++)
    {
        *(conv2+i)=(double **)malloc(8*sizeof(double *));
        for(int j=0;j<8;j++)
        {
            *(*(conv2+i)+j)=(double *)malloc(8*sizeof(double));        
        } 
    }

    // 2nd convolution filter size (4 dimension) (number - channel - rows - cols)
    double ****conv2_Filter=(double ****)malloc(50*sizeof(double ***));
    for(int num=0; num<50; num++)
    {
        *(conv2_Filter+num)=(double ***)malloc(20*sizeof(double **));
        for(int channel=0;channel<20;channel++)
        {
            *(*(conv2_Filter+num)+channel)=(double **)malloc(5*sizeof(double *));
            for(int rows=0;rows<5;rows++)
            {
                *(*(*(conv2_Filter+num)+channel)+rows)=(double *)malloc(5*sizeof(double));
            }
        }    
    }

    // 2nd pooling size (3 dimension) (number - rows - cols)
    double ***pool2=(double ***)malloc(50*sizeof(double **));
    for(int i=0;i<50;i++)
    {
        *(pool2+i)=(double **)malloc(4*sizeof(double *));
        for(int j=0;j<4;j++)
        {
            *(*(pool2+i)+j)=(double *)malloc(4*sizeof(double));        
        } 
    }

    // 1st fully connected filter size (2 dimension) (rows - cols)
    double **ip1_weight=(double**)malloc(500*sizeof(double *));
    for(int i=0;i<500;i++)
    {
        *(ip1_weight+i)=(double *)malloc(800*sizeof(double));
    }

    // 1st fully connected size (1 dimension) 
    double *ip1_input=(double *)malloc(50*4*4*sizeof(double));     
    double *ip1_output=(double *)malloc(500*sizeof(double));

    // 2nd fully connected filter size (2 dimension) (rows - cols)
    double **ip2_weight=(double**)malloc(10*sizeof(double *));
    for(int i=0;i<10;i++)
    {
        *(ip2_weight+i)=(double *)malloc(500*sizeof(double));
    }

    // 2nd fully connected size (1 dimension)
    double *ip2_output=(double *)malloc(10*sizeof(double));

    // EXECUTE
    conv1_Filter = conv1_scan();
    conv1 = convolution(jpg, conv1_Filter, image.channels(), image.rows, image.cols,5,1,20);
    pool1 = max_pooling(conv1,24,24,2,2,20);

    conv2_Filter = conv2_scan();
    conv2 = convolution(pool1,conv2_Filter,20,12,12,5,1,50);   
    pool2 = max_pooling(conv2,8,8,2,2,50);

    ip1_input = ip1_change(pool2);
    ip1_weight = ip1_scan();
    ip1_output = ip1_exe(ip1_input,ip1_weight);

    ReLU(ip1_output);

    ip2_weight = ip2_scan();
    ip2_output = ip2_exe(ip1_output,ip2_weight);

    // print result
    for(int i=0;i<10;i++)
    {
        printf("%d: %lf\n",i,ip2_output[i]);
    } 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for(int channel=0;channel<image.channels();channel++)           // jpg memory allocation Free
    {
        for(int rows=0;rows<image.rows;rows++)
        {
            free(*(*(jpg+channel)+rows));
        }
        free(*(jpg+channel));
    }

    free(jpg);

    for(int num=0;num<20;num++)         // conv1_Filter memory allocation Free
    {
        for(int channel=0;channel<1;channel++) 
        {
            for(int rows=0;rows<5;rows++)
            {
                free(*(*(*(conv1_Filter+num)+channel)+rows));
            }
            free(*(*(conv1_Filter+num)+channel));
        }
        free(*(conv1_Filter+num));
    }

    free(conv1_Filter);

    for(int channel=0;channel<20;channel++)         // conv1 memory allocation Free
    {
        for(int rows=0;rows<24;rows++)
        {
            free(*(*(conv1+channel)+rows));
        }
        free(*(conv1+channel));
    }

    free(conv1);


    for(int channel=0;channel<20;channel++)         // pool1 memory allocation Free
    {
        for(int rows=0;rows<12;rows++)
        {
            free(*(*(pool1+channel)+rows));
        }
        free(*(pool1+channel));
    }

    free(pool1);

    for(int num=0;num<50;num++)         // conv2_Filter memory allocation Free
    {
        for(int channel=0;channel<20;channel++) 
        {
            for(int rows=0;rows<5;rows++)
            {
                free(*(*(*(conv2_Filter+num)+channel)+rows));
            }
            free(*(*(conv2_Filter+num)+channel));
        }
        free(*(conv2_Filter+num));
    }

    free(conv2_Filter);

    for(int channel=0;channel<50;channel++)         // conv2 memory allocation Free
    {
        for(int rows=0;rows<8;rows++)
        {
            free(*(*(conv2+channel)+rows));
        }
        free(*(conv2+channel));
    }

    free(conv2);

    for(int channel=0;channel<50;channel++)         // pool2 memory allocation Free
    {
        for(int rows=0;rows<4;rows++)
        {
            free(*(*(pool2+channel)+rows));
        }
        free(*(pool2+channel));
    }

    free(pool2);

    free(ip1_input);            // ip1_input memory allocation Free  

    for(int channel=0;channel<500;channel++)            // ip1_weight memory allocation Free
    {
        free(*(ip1_weight+channel));   
    }

    free(ip1_weight);

    free(ip1_output); 

    for(int channel=0;channel<10;channel++)            // ip1_weight memory allocation Free
    {
        free(*(ip2_weight+channel));   
    }

    free(ip2_weight);
    
    free(ip2_output);

    return 0;
}