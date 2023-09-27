#include "unity.h"

#include "tinycsv.h"
int eof=0;
char file[1024]=
"Name,Age,Gender,Email\r\n\
Adam Johnson,30,Male,johndoe@example.com\r\n\
Jane Smith,25,Female,jsmith2022@fake.com\r\n\
Adam Smith,40,Male,adamsmith@example.com\r\n\
Yuli,20,Female,yoyo20@example.com\r\n";
csv_st csv_s;
int afile(char ch)
{
    file[eof++] = ch;
    file[eof] = 0;
    return 0;
}
char rfile(int a)
{
    return file[a];
}

void setUp(void)
{
    csv_s.iter = 0;
    csv_s.cols = 4;
    csv_s.afile = afile;
    csv_s.rfile = rfile;
    for(int i=0;i<1024;i++)
    {
        if(file[i]==0)
        {
            eof=i;
            break;
        }
    }
}

void tearDown(void)
{
}
void test_csv_read_1()
{
    int count=0;
    int numHeader;
    csv_open(&csv_s);
    numHeader = csv_read(&csv_s); // number of header/fields
    TEST_ASSERT_EQUAL_INT (4,numHeader);
    TEST_ASSERT_EQUAL_STRING("Name",csv_s.field[0]);
    TEST_ASSERT_EQUAL_STRING("Age",csv_s.field[1]);
    TEST_ASSERT_EQUAL_STRING("Gender",csv_s.field[2]);
    TEST_ASSERT_EQUAL_STRING("Email",csv_s.field[3]);
    for(int i=0;i<50;i++)
    {
        // csv_read return 0 if no filed is read, otherwise the number of fields read
        if(csv_read(&csv_s))
        {
            count++;
        }
        else
        {
            break;
        }
    }
    TEST_ASSERT_EQUAL_INT (4,count);
}
void test_csv_read_2()
{
    csv_open(&csv_s);
    csv_read(&csv_s); // number of header/fields
    TEST_ASSERT_EQUAL_STRING("Name",csv_s.field[0]);
    TEST_ASSERT_EQUAL_STRING("Age",csv_s.field[1]);
    TEST_ASSERT_EQUAL_STRING("Gender",csv_s.field[2]);
    TEST_ASSERT_EQUAL_STRING("Email",csv_s.field[3]);

    csv_read(&csv_s);
    TEST_ASSERT_EQUAL_STRING("Adam Johnson",csv_s.field[0]);
    TEST_ASSERT_EQUAL_STRING("30",csv_s.field[1]);
    TEST_ASSERT_EQUAL_STRING("Male",csv_s.field[2]);
    TEST_ASSERT_EQUAL_STRING("johndoe@example.com",csv_s.field[3]);
    
    csv_read(&csv_s);
    TEST_ASSERT_EQUAL_STRING("Jane Smith",csv_s.field[0]);
    TEST_ASSERT_EQUAL_STRING("25",csv_s.field[1]);
    TEST_ASSERT_EQUAL_STRING("Female",csv_s.field[2]);
    TEST_ASSERT_EQUAL_STRING("jsmith2022@fake.com",csv_s.field[3]);

    csv_read(&csv_s);
    TEST_ASSERT_EQUAL_STRING("Adam Smith",csv_s.field[0]);
    TEST_ASSERT_EQUAL_STRING("40",csv_s.field[1]);
    TEST_ASSERT_EQUAL_STRING("Male",csv_s.field[2]);
    TEST_ASSERT_EQUAL_STRING("adamsmith@example.com",csv_s.field[3]);
}
void test_csv_count_rows()
{
    int fileRow;
    fileRow = csv_count_rows(&csv_s);
    TEST_ASSERT_EQUAL_INT (4,fileRow);

    fileRow = csv_count_rows(&csv_s);
    TEST_ASSERT_EQUAL_INT (4,fileRow);
}
void test_tinycsv(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement bit_manipulation");
}