// Online C compiler to run C program online
#include <stdio.h>
#include "tinycsv.h"
// these should be above the actual expected lengths, I use +10 above

const char file[]=
"Name,Age,Gender,Email\r\n\
Adam Johnson,25,Male,johndoe@example.com\r\n\
Jane Smith,30,Female,js.com\r\n\
Adam Johnson,40,Male,adamjohnson@example.com\r\n\
Ali,35,Male,ali@example.com\r\n";
int main() {
    csv_st csv_s;
    char header[5][CSV_FIELD_LEN]; // to store headers
    int numHeader=0;
    int fileRow=0;
    // Write C code here
    printf("Hello world\r\n");
    // first line is the header
    csv_s.iter = 0;
    csv_s.file = file; // assign file pointer used by the csv_read function
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
    // now read file, we can also read by using the 'row' as limit
    for(int i=0;i<50;i++)
    {
        // csv_read return 0 if no filed is read, otherwise the number of fields read
        if(csv_read(&csv_s))
        {
            for(int j=0;j<numHeader;j++)
            {
                printf("%s = %s\r\n",header[j],csv_s.field[j]);
            }
            printf("----------\r\n");
        }
        else
        {
            printf("No more data to read\r\n");
            break;
        }
    }
    return 0;
}
