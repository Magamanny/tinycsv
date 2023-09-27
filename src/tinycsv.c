#include "tinycsv.h"
// private defines
#define TCSV_DEBUG(...) printf(__VA_ARGS__, "")
// Return the number of field readed
// The data is readed line by line, each call to this function
// return the next line, the fields are loaded to csv.field[] array
// the return value is to be used to detect end of file.
int csv_read(csv_st *csv)
{
    int numFields=0;
    int i=csv->iter,j=0,k=0;
    char csv_ch;
    //TCSV_DEBUG("Csv Readed call iter=%d\r\n",csv->iter);
    for(;i<(csv->iter+CSV_LINE_LEN);i++)
    {
        if(csv->rfile!=0)
        {
            csv_ch = csv->rfile(i);
        }
        //TCSV_DEBUG("f=%c %d",csv->file[i],i);
        // field completed
        if(csv_ch==',')
        {
            csv->field[k][j]=0;
            //TCSV_DEBUG("field=%s,index=%d\r\n",csv->field[k],k);
            j=0;
            k=(k+1)%5;
        }
        else if(csv_ch=='\r')
        {
            // ignore this character
            // do nothing, \n is used as terminator
        }
        else if(csv_ch=='\0')
        {
            //TCSV_DEBUG("End iter=%d",i);
            numFields=0;
            // end of file
            break;
        }
        // line complete
        else if(csv_ch=='\n')
        {
            csv->field[k][j]=0;
            //TCSV_DEBUG("Break\r\n");
            csv->iter = i+1;
            numFields=k+1;
            break;
        }
        else
        {
            csv->field[k][j] = csv_ch;
            j = (j+1)%CSV_FIELD_LEN;
        }
    } // end of for
    return numFields;
}
// Wirte the fields in csv->fileds to csv file, append after last row.
int csv_write(csv_st *csv)
{
    int i=0,j=0,k=0;
    char wData[CSV_LINE_LEN];
    for(i=0; i < csv->cols; i++,k++)
    {
        for(j=0;j<CSV_FIELD_LEN;j++,k++)
        {
            if(csv->field[i][j]==0)
            {
                break;
            }
            else
            {
                wData[k] = csv->field[i][j];
            }
        }
        wData[k] = ',';
    }
    if(k>0)
    {
        wData[k-1] = '\r';
        wData[k] = '\n';
        wData[k+1] = 0;
    }
    //printf("--------\r\n");
    for(i=0;i<k+1;i++)
    {
        if(csv->afile!=0)
        {
            csv->afile(wData[i]);
        }
    }
    //strcat(csv->file, wData);
}
// This function determines the number of rows in the csv file
// it return the rows, and it does this by iterating over the file till 'null'
int csv_count_rows(csv_st *csv)
{
    int hasrow=0;
    int rows=0;
    char csv_ch;
    for(int i=0;i<CSV_FILE_LEN;i++)
    {
        if(csv->rfile!=0)
        {
            csv_ch = csv->rfile(i);
        }
        if(csv_ch=='\0')
        {
            break;
        }
        else if(csv_ch=='\n')
        {
            hasrow=1;
            rows++;
        }
    }
    if(hasrow)
    {
        rows = rows-1;
    }
    return rows;
}