/*
Author: wangyao
Email: wangyao@cs.hit.edu.cn
*/
#include "acsmx.h"

/*
*  Text Data Buffer
*/
unsigned char text[MAXLEN];
int nline;

int main (int argc, char **argv)
{
	int i, nocase = 0;
	FILE *fd;
	char filename[256];
	ACSM_STRUCT *acsm = NULL;

	if (argc < 3)
	{
		fprintf(stderr, "Usage: acsmx filename pattern1 pattern2 ...  -nocase\n");
		exit (0);
	}

	acsm = acsmNew();

	strncpy(filename, argv[1], sizeof(filename));
	fd = fopen(filename, "r");
	if (fd == NULL)
	{
		fprintf(stderr, "Open file [%s] error! \n", filename);
		exit(1);
	}

	for (i = 1; i < argc; i++)
    {
		if (strcmp(argv[i], "-nocase") == 0)
        {
			nocase = 1;
        }
    }

    for (i = 2; i < argc; i++)
	{
		if (argv[i][0] == '-')
        {
			continue;
        }

        acsmAddPattern(acsm, (unsigned char *)argv[i], strlen(argv[i]), nocase);
	}

	/* Generate GtoTo Table and Fail Table */
	acsmCompile(acsm);

	/*Search Pattern*/
	while (! feof(fd) && fgets((char *)text, MAXLEN, fd))
	{
		acsmSearch(acsm, (unsigned char *)text, strlen((const char *)text), PrintMatch);
		nline++;
	}

	PrintSummary(acsm->acsmPatterns);

	acsmFree(acsm);

	printf("\n### AC Match Finished ###\n");
//	system("pause");

	return (0);
}

