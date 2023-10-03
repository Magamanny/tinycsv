#include "tinycsv.h"
#include "stdint.h"
// private defines
#define TCSV_DEBUG(...) printf(__VA_ARGS__, "")
// Return the number of field readed
// The data is readed line by line, each call to this function
// return the next line, the fields are loaded to csv.field[] array
// the return value is to be used to detect end of file.
int csv_read(csv_st *csv)
{
    int numFields=0;
    int i=csv->raddr,j=0,k=0;
    char csv_ch;
    //TCSV_DEBUG("Csv Readed call iter=%d\r\n",csv->iter);
    for(;i<(csv->raddr+CSV_LINE_LEN);i++)
    {
        if(csv->rrow >= csv->rows)
        {
            break;
        }
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
            k=(k+1)%5; // max field 5
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
            csv->rrow++;
            csv->raddr = csv->rrow * CSV_LINE_LEN;
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
// read a row from the csv file, i is 0 to CSV_MAX_ROWS
int csv_read_row(csv_st *csv, int index)
{
    int addr;
    csv->raddr = index * CSV_LINE_LEN;
    //TCSV_DEBUG("row = %d\r\n",csv->raddr);
    return csv_read(csv);
}
// reset iter so that read can reiter over it
int csv_open(csv_st *csv)
{
    csv->raddr=0;
    csv->rrow = 0;
    csv->wrow = csv_count_rows(csv);
    csv->rows = csv->wrow;
    return 0;
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
    csv->waddr = csv->wrow*CSV_LINE_LEN;
    for(i=0;i<k+1;i++)
    {
        if(csv->wfile!=0)
        {
            csv->wfile(csv->waddr,wData[i]);
            csv->waddr++;
        }
    }
    csv->wrow++;
    csv->rows++;
    //strcat(csv->file, wData);
}
// This function determines the number of rows in the csv file
// it return the rows, and it does this by iterating over the file till 'null'
int csv_count_rows(csv_st *csv)
{
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
            rows++;
            i = rows*CSV_LINE_LEN-1; // next line
            //TCSV_DEBUG("%d %d ",i+1,rows);
        }
    }
    return rows;
}