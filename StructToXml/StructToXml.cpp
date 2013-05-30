#include <stdio.h>
#include <locale.h>

#include "utypes.h"

#include "str_fun.h"

#define TYPE_SIZE 3

// Запись комментария
void WriteComment(FILE *pFile);
// Запись структуры
void WriteStruct(FILE	*pStructFile, FILE	*pXmlFile);

int main(int argc, char **argv)
{
	char	*pStructFileName;	// Название файла, содержащего структуру
	char	sXmlFileName[4096];	// Название xml-файла
	FILE	*pStructFile;		// Указатель на файл, содержащий структуру
	FILE	*pXmlFile;			// Указатель на xml-файл

	setlocale( LC_CTYPE, "Russian" );

	if(argc == 1)
		// Аргумент отсутствует
		return 0;

	pStructFileName = argv[1];

	STR_Left(pStructFileName, sXmlFileName, STR_IndexOf(pStructFileName, "."));
	
	strcat(sXmlFileName, ".xml");

	pStructFile = fopen(pStructFileName, "r");
	pXmlFile    = fopen(sXmlFileName, "w");

	WriteComment(pXmlFile);

	fprintf(pXmlFile, "<icr>\n"
		"\t<dev name=\"\" type=\"\" base=\"\"/>\n\n");

	while(!feof(pStructFile))
		WriteStruct(pStructFile, pXmlFile);

	fprintf(pXmlFile, "</icr>");

	fclose(pStructFile);
	fclose(pXmlFile);

	return 0;
}

// Запись комментария
void WriteComment(FILE *pFile)
{
	fprintf(pFile, 
		"<!--\n"
		"\t<dev name=\"\" type=\"\" base=\"\"/>\n\n"
		"\t<struct tag=\"\" size=\"\">\n"
		"\t</struct>\n\n"
		"\t<field name=\"\" offset=\"\" size=\"\" default=\"\"/>\n\n"
		"\t<field name=\"\" offset=\"\" size=\"\" default=\"\" type=\"int\" min=\"\" max=\"\"/>\n\n"
		"\t<field name=\"\" offset=\"\" size=\"\" default=\"\" type=\"spin-int\" min=\"\" max=\"\" inc=\"\"/>\n\n"
		"\t<field name=\"\" offset=\"\" size=\"\" default=\"\" type=\"double\" min=\"\" max=\"\" prec=\"\"/>\n\n"
		"\t<field name=\"\" offset=\"\" size=\"\" default=\"\" type=\"spin-double\" min=\"\" max=\"\" prec=\"\" inc=\"\"/>\n\n"
		"\t<field name=\"\" offset=\"\" size=\"\" default=\"\" type=\"hex\" min=\"\" max=\"\" />\n\n"
		"\t<field name=\"\" offset=\"\" size=\"\" default=\"\" type=\"bin\" min=\"\" max=\"\" />\n\n"
		"\t<field name=\"\" offset=\"\" size=\"\" default=\"\" type=\"list\">\n"
		"\t\t<item val=\"\" descr=\"\"/>\n"
		"\t\t.......................\n"
		"\t\t<item val=\"\" descr=\"\"/>\n"
		"\t</field>\n"
		"-->\n\n");
}

// Запись структуры
void WriteStruct(FILE	*pStructFile, FILE	*pXmlFile)
{
	char	str[4096];
	U08		isFindStruct = 0;	// Найдена ли структура
	U32		i;
	U32		nFieldSize;			// Размер поля структуры
	U32		nOffset = 0;		// Смещение

	char	asType[TYPE_SIZE][256] =   {"U08", "U16", "U32"};
	int		anTypeSize[TYPE_SIZE] = {1, 2, 4};

	while(!feof(pStructFile))
	{
		fgets(str, 4096, pStructFile);

		STR_Trimmed(str, 0);

		if((str[0] == '/') || (str[0] == '#') || (str[0] == '\0'))
			continue;

		if(str[0] == '}')
			break;

		if(!isFindStruct)
		{	// Структура не найдена
			if((STR_IndexOf(str, "typedef struct") == 0) ||
				(STR_IndexOf(str, "struct") == 0))
			{	// Структура найдена
				isFindStruct = 1;
				fwrite("\t<struct tag=\"\" size=\"\">\n", strlen("\t<struct tag=\"\" size=\"\">\n"), 1, pXmlFile);
			}
		}
		else 
		{
			for(i = 0; i < TYPE_SIZE; i++)
			{
				if(strstr(str, asType[i]) == str)
				{
					nFieldSize = anTypeSize[i];
					STR_Remove(str, 0, asType[i]);
				}	
			}

			STR_Trimmed(str, 0);
			STR_Left(str, 0, STR_IndexOf(str, ";"));
			STR_Trimmed(str, 0);

			fprintf(pXmlFile, "\t\t<field name=\"%s\" offset=\"%d\" size=\"%d\"/>\n", str, nOffset, nFieldSize);

			nOffset += nFieldSize;
		}
	}

	if(isFindStruct)
	{
		fprintf(pXmlFile, "\n\t<!-- <struct tag=\"\" size=\"%d\"> -->\n", nOffset);

		fwrite("\t</struct>\n\n", strlen("\t</struct>\n\n"), 1, pXmlFile);
	}
}