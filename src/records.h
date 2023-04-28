#pragma once

#define RECORDS_FILENAME "data/records.bin"

typedef struct Record
{
	int rows;
	int cols;
	int secs;
	int moves;
} Record;

typedef struct Records
{
	int size;
	Record* data;
} Records;

void RecordsInit(Records* self);
void RecordsUninit(Records* self);

void RecordsRead(Records* self, const char* filename);
void RecordsWrite(Records* self, const char* filename);

void RecordsAdd(Records* self, Record record);
Record RecordsGet(Records* self, int rows, int cols);