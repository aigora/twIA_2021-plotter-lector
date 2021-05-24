#include <stdio.h>
#include <malloc.h>
#include <string>
#include <iostream>

#define OUTLEN 7
using namespace std;
string convertir_notas(char notas);
void notas2char();
void fileprint(char  data[], const char con[]);
void callNotas();
int main()
{
	callNotas();
}
void callNotas()
{
	fileprint(NULL, "\n------NUEVA TRADUCCION------\n");

	printf("Si quiere pasar de notas a numeros, pulse A.");
	printf("\n\nSi quiere pasar de numeros a notas,pulse B.\n");
	char a;
	scanf_s("%c", &a);
	switch (a)
	{
	case 'A':
		char* notas;
		int numerodelusuario;

		printf("Sea la longitud de la cancíon:");
		scanf_s("%d", &numerodelusuario);
		notas = (char*)malloc((sizeof(char) * numerodelusuario) + 1);
		if (notas != NULL)
		{
			printf("Introduce las notas:");

			getchar();
			gets_s(notas, numerodelusuario + 1);
			fileprint(notas, NULL);
			fileprint(NULL, "\n------SE TRADUCE A------\n");
			for (int i = 0; i < numerodelusuario; i++)
			{
				string out = convertir_notas(*(notas + i));
				cout << out;
				cout << "\n";
			}
		}
		break;
	case 'B':
		notas2char();
		break;
	}
}
string convertir_notas(char notas)
{
	string out0 = "0000000";
	string out1 = "1000000";
	string out2 = "0100000";
	string out3 = "0010000";
	string out4 = "0001000";
	string out5 = "0000100";
	string out6 = "0000010";
	string out7 = "0000001";
	switch (notas)
	{
	case 'D':
		fileprint(NULL, "1000000");
		return out1;
		break;
	case 'R':
		fileprint(NULL, "0100000");
		return out2;
		break;
	case 'M':
		fileprint(NULL, "0010000");
		return out3;
		break;
	case 'F':
		fileprint(NULL, "0001000");
		return out4;
		break;
	case 'S':
		fileprint(NULL, "0000100");
		return out5;
		break;
	case 'L':
		fileprint(NULL, "0000010");
		return out6;
		break;
	case 'I':
		fileprint(NULL, "0000001");
		return out7;
		break;
	default:
		fileprint(NULL, "0000000");
		return out0;
		break;
	}
}
void notas2char() 
{
	int len = 0,i=0;
	char* frase;
	printf("\nIntroduce la longitud de tu canción\n");
	scanf_s("%d",&len);
	frase = (char*)malloc((len * 7) + 1);
	printf("\nIntroduce una frase formada por 0s y 1s\n");
	if (frase != NULL)
	{
		getchar();
		gets_s(frase, ((len * 7) + 1));
		fileprint(frase, NULL);
		fileprint(NULL, "\n------SE TRADUCE A------\n");
	}
	while (*(frase +i) != '\0') 
	{
		if (*(frase + i) == '1')
		{
			switch (i%7)
			{
			default:
				break;
			case 0:
				printf("do ");
				fileprint(NULL,"do ");
				break;
			case 1:
				printf("re ");
				fileprint(NULL, "re ");
				break;
			case 2:
				printf("mi ");
				fileprint(NULL, "mi ");
				break;
			case 3:
				printf("fa ");
				fileprint(NULL, "fa ");
				break;
			case 4:
				printf("sol ");
				fileprint(NULL, "sol ");
				break;
			case 5:
				printf("la ");
				fileprint(NULL, "la ");
				break;
			case 6:
				printf("si ");
				fileprint(NULL, "si ");
				break;
			}
		}
		i++;
	}
}
void fileprint(char data[], const char con[]) 
{
	FILE* fichero;
	fopen_s(&fichero,"movimientos.txt","a");
	if (fichero != NULL)
	{
		if (data != NULL)
		{
			fputs(data, fichero);
		}
		else if (con != NULL)
		{
			fputs(con, fichero);
		}
		fclose(fichero);
	}
}
