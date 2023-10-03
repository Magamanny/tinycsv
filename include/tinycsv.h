#ifndef TINYCSV
#define TINYCSV
// make sure this is above the expected max lenght
// max legthn of a single filed
#define CSV_FIELD_LEN 30
// max length of line in the csv
#define CSV_LINE_LEN 150
// max lenght of csv file
#define CSV_FILE_LEN 1024
typedef struct csv_st{
    int raddr;
    int rrow;
    int waddr;
    int wrow;
    
    int len;
    int cols;
    int rows;
    char (*rfile)(int);// file read function
    int (*wfile)(int,char); // file write byte to file
    int (*afile)(char); // file append data function
    char field[5][CSV_FIELD_LEN];
} csv_st;
// Iterative read
int csv_read(csv_st *csv);
int csv_open(csv_st *csv);
int csv_write(csv_st *csv);
int csv_read_row(csv_st *csv, int index);
int csv_count_rows(csv_st *csv);
#endif