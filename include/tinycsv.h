#ifndef TINYCSV
#define TINYCSV

#define CSV_FIELD_LEN 30
#define CSV_LINE_LEN 100
typedef struct csv_st{
    int iter;
    int num;
    const char *file; // pointer to the file
    char header[5][CSV_FIELD_LEN];
    char field[5][CSV_FIELD_LEN];
} csv_st;

int csv_read(csv_st *csv);
void csv_init(csv_st *csv);
#endif