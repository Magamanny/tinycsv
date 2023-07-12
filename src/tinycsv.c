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
    //TCSV_DEBUG("Csv Readed call iter=%d\r\n",csv->iter);
    // clear fields
    for(int i=0;i<5;i++)
    {
        //csv->field[i][0]=0;
    }
    for(;i<(csv->iter+CSV_LINE_LEN);i++)
    {
        //TCSV_DEBUG("f=%c %d",csv->file[i],i);
        // field completed
        if(csv->file[i]==',')
        {
            csv->field[k][j]=0;
            //TCSV_DEBUG("field=%s,index=%d\r\n",csv->field[k],k);
            j=0;
            k=(k+1)%5;
        }
        else if(csv->file[i]=='\r')
        {
            // ignore this character
            // do nothing, \n is used as terminator
        }
        else if(csv->file[i]=='\0')
        {
            //TCSV_DEBUG("End iter=%d",i);
            numFields=0;
            // end of file
            break;
        }
        // line complete
        else if(csv->file[i]=='\n')
        {
            //TCSV_DEBUG("Break\r\n");
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
// This function determines the number of rows in the csv file
// it return the rows, and it does this by iterating over the file till 'null'
int csv_count_rows(csv_st *csv)
{
    int hasrow=0;
    int rows=0;
    for(int i=0;i<CSV_FILE_LEN;i++)
    {
        if(csv->file[i]=='\0')
        {
            break;
        }
        else if(csv->file[i]=='\n')
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