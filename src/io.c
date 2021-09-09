#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/io.h"

char* read_file(const char* f)
{
	char* buffer	= (char*) calloc(1, sizeof(char));
	buffer[0]		= '\0';
	FILE * fp;
	char * line 	= NULL;
	size_t len		= 0;
	ssize_t read;
	
	fp = fopen(f, "rb");
	if (fp == NULL)
	{
		printf("Could not read file `%s` ...\n", f);
		exit(1);
	};

	while ((read = getline(&line, &len, fp)) != -1)
	{
		buffer	= (char*) realloc(buffer, ((strlen(buffer)+strlen(line)+1))*sizeof(char));
		strcat(buffer, line);
	};
	fclose(fp);
	if (line)	free(line);
	
	return buffer;
};

