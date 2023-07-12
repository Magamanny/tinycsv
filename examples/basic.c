// Online C compiler to run C program online
#include <stdio.h>
#include "tinycsv.h"
// these should be above the actual expected lengths, I use +10 above

csv_st csv_s;
const char file[]=
"Name,Age,Gender,Email\n\
John Doe,25,Male,johndoe@example.com\n\
Jane Smith,30,Female,janesmith@example.com\n\
Adam Johnson,40,Male,adamjohnson@example.com\n\
Emily Davis,35,Female,emilydavis@example.com\n";
int main() {
    // Write C code here
    printf("Hello world\r\n");
    // first line is the header
    csv_s.file = file; // assign file pointer used by the csv_read function
    csv_s.num = csv_read(&csv_s); // number of header/fields
    // copy the header, to a header varialbe for easy use
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<20;j++)
        {
            csv_s.header[i][j]=csv_s.field[i][j];
        }
    }
    // now read file
    for(int i=0;i<50;i++)
    {
        // csv_read return 0 if no filed is read, otherwise the number of fields read
        if(csv_read(&csv_s))
        {
            for(int j=0;j<csv_s.num;j++)
            {
                printf("%s = %s\r\n",csv_s.header[j],csv_s.field[j]);
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
