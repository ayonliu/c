/*
	process log file into php array
	use: file_to_php_array test.log ^ test.dat
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REC_LEN 1024

int main(int argc, char * argv[])
{
	FILE *fp, *output;
	char buff[MAX_REC_LEN];
	//const char s[2] = "^";
	char *str, *str1;
	int i;

	if ( argc < 4)
	{
		printf("Need at least 3 args: 源文件 分隔符 输出文件\n");
		return 1;
	}
	/* open the file */
	fp = fopen(argv[1], "r");
	output = fopen(argv[3], "w");
	if (fp == NULL) {
		printf("I couldn't open results.dat for reading.\n");
		return 1;
	}
	//fprintf(output, "%s", "<?php");
	while ((fgets(buff, MAX_REC_LEN, fp)) != NULL)
	{
		char dest[MAX_REC_LEN];
		strcpy(dest, "array(\n");
		str1 = strdup(buff);
		while ((str = strsep(&str1, argv[2])) != NULL)
		{
			//printf(" %s\n", str);
			for  (i=0; i<=strlen(str); i++) {
				if (str[i] == '\r' || str[i] == '\n')
				{
				   str[i] = '\0';
				}
				//printf(" %c\n", str[i]);
			}
			if (strlen(str) == 0)
			{
			   str = "''";
			}
			//puts(str);
			strcat(dest, "    ");
			strcat(dest, str);
			strcat(dest, ",\n");
		}
		strcat(dest, "),\n");
		fprintf(output, "%s", dest);
		//puts(dest);
	}
	//fprintf(output, "%s", "?>");
	/* close the file */
	fclose(fp);
	fclose(output);
	free(str1);

	return 0;
}