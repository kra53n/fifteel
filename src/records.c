#include <stdio.h>
#include <malloc.h>

#include "records.h"

void RecordsInit(Records* self)
{
	self->size = 0;
	self->data = 0;
}

void RecordsUninit(Records* self)
{
	if (self->size == 0 || self->data == 0)
		return;
	free(self->data);
}

void RecordsRead(Records* self, const char* filename)
{
	FILE* f;
	if (fopen_s(&f, RECORDS_FILENAME, "rb"))
		return;
	fread(self, sizeof(Records), 1, f);
}

void RecordsWrite(Records* self, const char* filename)
{
	FILE* f;
	int err;
	if ((err = fopen_s(&f, RECORDS_FILENAME, "wb")))
	{
		printf("\nsome problem while trying to write to file %s, error code", filename, err);
		exit(1);
	}
	fwrite(self, sizeof(Records), 1, f);
	fclose(f);
}

void RecordsAdd(Records* self, Record record)
{
	self->size++;
	self->data = (Record*)realloc(self->data, self->size * sizeof(Record));
	self->data[self->size - 1] = record;
}

Record RecordsGet(Records* self, int rows, int cols)
{
	for (int i = 0; i < self->size; i++)
	{
		if (self->data[i].rows != rows || self->data[i].cols != cols)
			continue;
		return self->data[i];
	}
	Record r = { rows, cols, 0, 0 };
	return r;
}