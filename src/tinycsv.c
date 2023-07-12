#include "tinycsv.h"

// return the number of field readed
int csv_read(csv_st *csv)
{
    int numFields=0;
    int i=csv->iter,j=0,k=0;
    //printf("iter=%d\r\n",csv->iter);
    for(;i<(csv->iter+CSV_LINE_LEN);i++)
    {
        //printf("f=%c ",file[i]);
        // field completed
        if(csv->file[i]==',')
        {
            csv->field[k][j]=0;
            //printf("field=%s,index=%d\r\n",csv->field[k],k);
            j=0;
            k=(k+1)%5;
        }
        // line complete
        else if(csv->file[i]=='\n')
        {
            //printf("Break\r\n");
            csv->iter = i+1;
            numFields=k+1;
            break;
        }
        else
        {
            csv->field[k][j] = csv->file[i];
            j = (j+1)%CSV_FIELD_LEN;
        }
    } // end of for
    return numFields;
}