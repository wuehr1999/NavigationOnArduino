#include <stdio.h>
#include <stdlib.h>

void printHelp();

int main(int argc, char *argv[])
{



    if(argc == 2)
    {
    FILE * fp;
    FILE *fp2;

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    	fp = fopen(argv[1], "r");
    	if (fp == NULL){
		printHelp();
        	exit(EXIT_FAILURE);}

	char outputFile[80];
	int length = sprintf(outputFile, "String%s", argv[1]);

   	fp2 = fopen(outputFile, "w");
    	if (fp2 == NULL){
		printHelp();
        	exit(EXIT_FAILURE);}


	    while ((read = getline(&line, &len, fp)) != -1) {
		for(int i = 0; i < read - 1; i++)
		{
			fputc (line[i], fp2);
		}
	    }

	    fclose(fp);
	    if (line)
		free(line);
	    exit(EXIT_SUCCESS);
    }
    else
	{
		printHelp();
	}
return 0;
}

void printHelp()
{
   printf("Run as ./osmToString <filename>.osm\n");
}

