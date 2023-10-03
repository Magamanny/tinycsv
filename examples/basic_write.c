// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>
#include "tinycsv.h"
// these should be above the actual expected lengths, I use +10 above

char file[1024]=
"Name,Age,Gender,Email\r\n";
int afile(char ch)
{
    strncat(file, &ch, 1);
    return 0;
}
char rfile(int a)
{
    return file[a];
}
int main() {
    csv_st csv_s;
    char header[5][CSV_FIELD_LEN]; // to store headers
    int numHeader=0;
    int fileRow=0;
    // Write C code here
    printf("Hello world\r\n");
    // first line is the header
    csv_s.cols = 4;
    csv_s.afile = afile;
    csv_s.rfile = rfile;
    
    csv_open(&csv_s);
    fileRow = csv_count_rows(&csv_s);
    numHeader = csv_read(&csv_s); // number of header/fields
    printf("col=%d, rows=%d\r\n",numHeader,fileRow);
    // copy the header, to a header varialbe for easy use
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<20;j++)
        {
            header[i][j]=csv_s.field[i][j];
        }
    }
    // Write Check
    strcpy(csv_s.field[0],"Sannan");
    strcpy(csv_s.field[1],"22");
    strcpy(csv_s.field[2],"Male");
    strcpy(csv_s.field[3],"sannan2020@gmail.com");

    csv_write(&csv_s);
    strcpy(csv_s.field[0],"Khan");
    csv_write(&csv_s);
    strcpy(csv_s.field[0],"Das");
    csv_write(&csv_s);
    
    fileRow = csv_count_rows(&csv_s);
    printf("col=%d, rows=%d\r\n",numHeader,fileRow);
    // now read file, we can also read by using the 'row' as limit
    for(int i=0;i<50;i++)
    {
        // csv_read return 0 if no filed is read, otherwise the number of fields read
        if(csv_read(&csv_s))
        {
            for(int j=0;j<numHeader;j++)
            {
                printf("%s = %s, ",header[j],csv_s.field[j]);
            }
            printf("----------\r\n");
        }
        else
        {
            printf("No more data to read\r\n");
            break;
        }
    }
    printf("%s",file);
    return 0;
}