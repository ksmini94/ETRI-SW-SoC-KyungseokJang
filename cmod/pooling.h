#include <cstdio>
#include <cstdlib>

//pool1 = max_pooling(      conv1,          24,               24,           2,           2,             20      )
//pool2 = max_pooling(      conv2,           8,                8,           2,           2,             50      )

double ***max_pooling(double ***image, int image_rows, int image_cols, int filter, int stride, int image_channel)
{  
    int pooling_rows_size = ((image_rows-filter)/stride) + 1;           // Result rows size
    int pooling_cols_size = ((image_cols-filter)/stride) + 1;           // Result cols size

    double max=INT_MIN;                                                 // Max data initialization

    double ***pooling_result=(double ***)malloc(image_channel*sizeof(double **));           // Pooling Result memory allocation         "result[image_channel][rows][cols]"
    for(int channel=0;channel<image_channel;channel++)
    {
        *(pooling_result+channel)=(double **)malloc(pooling_rows_size*sizeof(double *));
        for(int rows=0;rows<pooling_rows_size;rows++)
        {
            *(*(pooling_result+channel)+rows)=(double *)malloc(pooling_cols_size*sizeof(double));
        }
    }

    for(int channel=0;channel<image_channel;channel++)          // Result initialization            image_channel - pool_rows - pool_cols
    {
        for(int rows=0;rows<pooling_rows_size;rows++)
        {
            for(int cols=0;cols<pooling_cols_size;cols++)
            {
                pooling_result[channel][rows][cols] = 0;
            }
        }
    }

    for(int channel=0;channel<image_channel;channel++)          // Max pooling Activate         image_channel - pool_rows - pool_cols - filter_rows - filter_cols
    {
        for(int rows=0;rows<pooling_rows_size;rows++)
        {
            for(int cols=0;cols<pooling_cols_size;cols++)
            {
                for(int filter_r=0;filter_r<filter;filter_r++)
                {   
                    for(int filter_c=0;filter_c<filter;filter_c++)
                    {
                        // Max data condition
                        if(max<image[channel][filter_r+(rows*stride)][filter_c+(cols*stride)]) max = image[channel][filter_r+(rows*stride)][filter_c+(cols*stride)];
                    }
                }
                // Max data in
                pooling_result[channel][rows][cols] = max;
                max=INT_MIN;

            }
        }
    }

    return pooling_result;
}