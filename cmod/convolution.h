#include <cstdio>
#include <cstdlib>

//conv1 = convolution(      jpg,           conv1_Filter,       image.channels(),    image.rows,     image.cols,        5,          1,            20      )
//conv2 = convolution(     pool1,          conv2_Filter,              20,                12,            12,            5,          1,            50      )

double ***convolution(double ***image, double ****conv_filter, int image_channel, int image_rows, int image_cols, int filter, int stride, int numofFilter)
{
    int convolution_rows_size = ((image_rows-filter)/stride) + 1;           // Result Rows Size
    int convolution_cols_size = ((image_cols-filter)/stride) + 1;           // Result Cols Size

    double ***image_input=(double ***)malloc(image_channel*sizeof(double **));          // Input image memory allocation "image_input[channel][rows][cols]" 
    for(int channel=0;channel<image_channel;channel++)
    {
        *(image_input+channel)=(double **)malloc(image_rows*sizeof(double *));
        for(int rows=0;rows<image_rows;rows++)
        {
            *(*(image_input+channel)+rows)=(double *)malloc(image_cols*sizeof(double));        
        } 
    }

    for(int channel=0;channel<image_channel;channel++)          // Mat image -> 3 Dimension pointer             image_channel - image_rows - image_cols
    {
        for(int rows=0;rows<image_rows;rows++)
        {
            for(int cols=0;cols<image_cols;cols++)
            {
                image_input[channel][rows][cols] = image[channel][rows][cols];
            }
        }
    }   

    double ****Filter_input=(double ****)malloc(numofFilter*sizeof(double ***));            // Weight data input memory allocation "Filter[numofFilter][depth][rows][cols]" 
    for(int num=0; num<numofFilter; num++)
    {
        *(Filter_input+num)=(double ***)malloc(image_channel*sizeof(double **));
        for(int channel=0;channel<image_channel;channel++)
        {
            *(*(Filter_input+num)+channel)=(double **)malloc(filter*sizeof(double *));
            for(int rows=0;rows<filter;rows++)
            {
                *(*(*(Filter_input+num)+channel)+rows)=(double *)malloc(filter*sizeof(double));
            }
        }    
    }

    for(int num=0; num<numofFilter; num++)          // Weight data text -> filter                               numofFilter - image_channel - filter_rows - filter_cols
    {
        for(int channel=0;channel<image_channel;channel++)
        {
            for(int filter_rows=0;filter_rows<filter;filter_rows++)
            {
                for(int filter_cols=0;filter_cols<filter;filter_cols++)
                {
                    Filter_input[num][channel][filter_rows][filter_cols] = conv_filter[num][channel][filter_rows][filter_cols];
                }
            }
        }
    }

    double ***convolution_output=(double ***)malloc(numofFilter*sizeof(double **));         // Convolution result memory allocation "Convolution_output[numofFilter][rows][cols]"
    for(int channel=0;channel<numofFilter;channel++)
    {
        *(convolution_output+channel)=(double **)malloc(convolution_rows_size*sizeof(double *));
        for(int rows=0;rows<convolution_rows_size;rows++) 
        {
            *(*(convolution_output+channel)+rows)=(double *)malloc(convolution_cols_size*sizeof(double));
        }
    }

    for(int channel=0;channel<numofFilter;channel++)            // Convolution result initialization            numofFilter - conv_rows - conv_cols
    {
        for(int rows=0;rows<convolution_rows_size;rows++)
        {
            for(int cols=0;cols<convolution_cols_size;cols++)
            {
                convolution_output[channel][rows][cols] = 0;
            }
        }
    }

    for(int num=0; num<numofFilter; num++)          // Convolution Calculation                          numofFilter - image_channel - conv_rows - conv_cols - filter_rows - filter_cols
    {
        for(int channel=0;channel<image_channel;channel++)
        {
            for(int rows=0;rows<convolution_rows_size;rows++)
            {
                for(int cols=0;cols<convolution_cols_size;cols++)
                {
                    for(int filter_r=0;filter_r<filter;filter_r++)
                    {
                        for(int filter_c=0;filter_c<filter;filter_c++)
                        {
                            convolution_output[num][rows][cols] += image_input[channel][filter_r+(rows*stride)][filter_c+(cols*stride)] * Filter_input[num][channel][filter_r][filter_c];
                        }
                    }   
                }
            }
        }
    }

    for(int channel=0;channel<image_channel;channel++)          // Input image memory Free          image_channel - image_rows - image_cols 
    {
        for(int rows=0;rows<image_rows;rows++)
        {
            free(*(*(image_input+channel)+rows));
        }
        free(*(image_input+channel));
    }

    for(int num=0;num<numofFilter;num++)            // Weight data input memory Free            numofFilter - image_channel - filter_rows - filter_cols
    {
        for(int channel=0;channel<image_channel;channel++) 
        {
            for(int rows=0;rows<filter;rows++)
            {
                free(*(*(*(Filter_input+num)+channel)+rows));
            }
            free(*(*(Filter_input+num)+channel));
        }
        free(*(Filter_input+num));
    }

    free(image_input);
    free(Filter_input);

    return convolution_output;
}