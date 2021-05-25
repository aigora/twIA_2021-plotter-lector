#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <malloc.h>

using namespace std;
int compare(char a[], char b[]);
void esp2morse(char l[], char m[][7]);
void morse2esp(char l[], char m[][7]);
void callMorse();

char* cogerTrozo(char frase[], int inicio, int fin);
char bin2ascii(char bin[9]);
char* convertir(int numero);
void callBinario();

#define OUTLEN 7
using namespace std;
string convertir_notas(char notas);
void notas2char();
void fileprint(char  data[], const char con[], char c);
void callNotas();

int main()
{
	int opcion;

	do
	{
		printf("\n-----------------------\nOpciones: \n1.Morse\n2.Binario\n3.Notas\n4.Salir\n-----------------------\nIngresa opcion: ");
		scanf_s("%d", &opcion);
		switch (opcion)
		{
		case 1:
			callMorse();
			break;
		case 2:
			callBinario();
			break;
		case 3:
			callNotas();
			break;
		}
	} while (opcion != 4);

}

void callMorse()
{
	fileprint(NULL, "\n------NUEVA TRADUCCION MORSE------\n", NULL);

	char opcion = 0;
	int i = 0, j = 0, n = 0;
	char* cadena;

	char l[37] = { 'a','b','c','d','e','f','g','h','i',
		'j','k','l','m','n','o','p','q','r','s','t',
		'u','v','w','x','y','z','0','1','2','3','4',
		'5','6','7','8','9',' ' };
	char m[37][7] = { {".-"}, {"-..."}, {"-.-."}, {"-.."},
		{"."}, {"..-."}, {"--."}, {"...."}, {".."},
		{".---"}, {"-.-"}, {".-.."}, {"--"}, {"-."},
		{"---"}, {".--."}, {"--.-"}, {".-." }, { "..." },
		{"-"}, {"..-"}, {"...-"}, {".--"}, {"-..-"},
		{"-.--"}, {"--.."}, {"-----"}, {".----"}, {"..---"},
		{"...--"}, {"....-"}, {"....."}, {"-...."}, {"--..."},
		{"---.."}, {"----."},{"/"} };


	cout << "\n-----------------------\nMenu de Opciones" << endl;
	cout << "a. Espa\xA4ol a morse" << endl;
	cout << "b. Morse a  espa\xA4ol\n-----------------------" << endl;

	cout << "\nIngrese una opcion: ";
	cin >> opcion;

	switch (opcion)
	{
	case 'a': //español a morse;
		esp2morse(l, m);
		break;
	case 'b'://morse a español
		morse2esp(l, m);
		break;
	}



}
int compare(char a[], char b[])
{
	for (int k = 0; a[k] == '.' || a[k] == '-' || b[k] == '.' || b[k] == '-'; k++)
	{
		if (a[k] != b[k])
		{
			return 0;
		}
		else
		{
			continue;
		}
	}
	return 1;
}
void esp2morse(char l[], char m[][7])
{
	char* cadena;
	int len = 0;
	printf("\nIndique la longitud de la cadena:");
	scanf_s("%d", &len);
	if (len != 0)
	{
		cadena = (char*)malloc(sizeof(int) * (len + 1)); //operador para asignar el tamaño exacto
		printf("Escribe un texto u oracion que quieras traducir a codigo morse:\n");
		getchar();
		gets_s(cadena, len + 1);
		fileprint(cadena, NULL, NULL);
		fileprint(NULL, "\n------SE TRADUCE A------\n", NULL);

		for (int i = 0; *(cadena + i) != '\0'; i++) //inicia desde i hasta la cantidad de dígitos que tenga la cadena
		{
			for (int j = 0; j < 37; j++) //una vez que el i llegue a 0, pasa al j que inicia hasta llegar al 37 (número de variables posibles en char) 
				if (*(cadena + i) == l[j]) //compara la cadena introducida con su correspondiente en traducción
				{
					for (int k = 0; m[j][k] != '\0'; k++)
					{
						printf("%c", m[j][k]);
						fileprint(&m[j][k], NULL, NULL);

					}							//una vez que la encuentra, lo imprime
					printf(" ");
					break;
				}
		}
	}

}
void morse2esp(char l[], char m[][7])
{
	int i = 0;
	char* cadena;
	int len;
	printf("\nIndique la longitud de la cadena:");
	scanf_s("%d", &len);
	cadena = (char*)malloc(sizeof(int) * (len + 1)); //operador para asignar el tamaño exacto
	printf("Escribe un texto u oracion que quieras traducir a codigo espa\xA4ol:\n");
	getchar();
	gets_s(cadena, len + 1);
	int distSpacio = 0;

	fileprint(cadena, NULL, NULL);
	fileprint(NULL, "\n------SE TRADUCE A------\n", NULL);
	while (*(cadena + i) != '\0')
	{
		// cuento cuantos caracteres hay entre espacio
		while (*(cadena + i + distSpacio) != ' ' && *(cadena + i + distSpacio) != '\0')
		{
			// si no es espacio continua incrementando, cogera los simbolos morse que correscponde a 1 letra
			distSpacio++;
		}
		// necesitamos una variable temporal para almacenar el morse// + 1 por el '\0'
		char* temp;
		temp = (char*)calloc(distSpacio, 1);
		if (temp != NULL)
		{
			//printf("El tamaño de tem es %d, dist es %d\n", sizeof(temp), distSpacio);
			//volvemos hacia atras capturando el morse que corresponde a 1 letra
			for (int j = distSpacio; j > 0; j--)
			{
				*(temp + distSpacio - j) = *(cadena +i + distSpacio - j);
				//puts(temp);
			}
			// comparamos el obtenido con el que esta ordenado, m
			for (int x = 0; x < 37; x++)
			{
				if (compare(temp, m[x]) == 1)//son iguales
				{
					fileprint(NULL, NULL, l[x]);
					printf("%c", l[x]);
					break;
				}
			}
			i += distSpacio + 1;
			distSpacio = 0;
			free(temp);
		}
		else
		{
			printf("\nERROR NO SE PUEDE ALOCAR MEMORIA\n");
		}
	}
}

void callBinario()
{
	fileprint(NULL, "\n------NUEVA TRADUCCION BINARIO------\n", NULL);

	printf("\n-----------------------\na. binario a texto\n");
	printf("b. texto a binario\n-----------------------\nIngresa opcion: ");
	char a;
	getchar();
	scanf_s("%c", &a, 1);

	switch (a)
	{
	case 'a':
	{
		char* num;
		int resu = 0, len;
		printf("Introduce la longitud de la frase\n");
		scanf_s("%d", &len);
		num = (char*)malloc(7 * len + 1);
		printf("Introduce una frase formados por 0 o 1:\n");
		getchar();
		gets_s(num, 7 * len + 1);
		fileprint(num, NULL, NULL);
		fileprint(NULL, "\n------SE TRADUCE A------\n", NULL);
		for (int i = 0, k = 8; num[i] != '\0' && num[k] != '\0'; i += 7, k += 7)
		{
			char* trozo = cogerTrozo(num, i, k);
			resu = bin2ascii(trozo);
			printf("%c", resu);
		}
	}
	break;
	case 'b':
		char numero;
		char* numBinario;
		char* ASCII;
		int i = 0, len;
		printf("Introduce la longitud de la frase\n");
		scanf_s("%d", &len);
		ASCII = (char*)malloc(len + 1);
		printf("Escribe un texto u oracion con el lenguaje Ascii\n");
		if (len + 1 != 0)
		{
			getchar();
			gets_s(ASCII, len + 1);

			fileprint(ASCII, NULL, NULL);
			fileprint(NULL, "\n------SE TRADUCE A------\n", NULL);
			numBinario = (char*)calloc(9, sizeof(char));

			while (ASCII[i] != '\0')
			{
				numBinario = convertir((int)ASCII[i]);
				puts(numBinario);
				i++;
			}
			free(numBinario);
			break;
		}
		
	}
}
char* cogerTrozo(char frase[], int inicio, int fin)
{
	char* trozo;
	int distancia = fin - inicio;

	trozo = (char*)calloc(distancia + 1, 1);
	if (trozo != NULL)
	{
		for (int i = 0; i < distancia; i++)
		{
			*(trozo + i) = frase[inicio + i];
		}
		return trozo;
		fileprint(trozo, NULL, NULL);

	}
}
char bin2ascii(char bin[9])
{
	int resu = 0, i = 0;
	while (bin[i] != '\0')
	{
		if (bin[i] == '1')
		{
			resu += pow(2, 6 - i);
		}
		i++;
	}
	char c;
	c = resu;
	fileprint(NULL, NULL, c);
	return resu;

}
char* convertir(int numero)
{
	char* out;
	int i = 0;
	out = (char*)calloc(9, sizeof(char*));
	if (out != NULL)
	{
		//inicio a 0s para tener siempre un binario de 8 bits
		for (int i = 0; i < 8; i++)
		{
			*(out + i) = '0';
		}
		//paso de int a binario
		while (numero > 0)
		{
			if (numero % 2 == 0)
			{
				*(out + 7 - i) = '0';
			}
			else
			{
				*(out + 7 - i) = '1';
			}
			numero = numero / 2;
			for (int i = *out - 1; i >= 0; i--);
			{
				i++;
			}
		}
		fileprint(out, NULL, NULL);
		return out;

	}
	else
	{
		printf("No hay memoria suficiente");
	}
}

void callNotas()
{
	fileprint(NULL, "\n------NUEVA TRADUCCION NOTAS------\n", NULL);

	printf("\n-----------------------\nb. notas(0,1) a texto(do,re)\n");
	printf("a. texto(do,re) a notas(0,1)\n-----------------------\nIngresa opcion: ");
	char a;
	getchar();
	scanf_s("%c", &a,1);
	switch (a)
	{
	case 'a':
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
			fileprint(notas, NULL, NULL);
			fileprint(NULL, "\n------SE TRADUCE A------\n", NULL);
			for (int i = 0; i < numerodelusuario; i++)
			{
				string out = convertir_notas(*(notas + i));
				cout << out;
				cout << "\n";
			}
		}
		break;
	case 'b':
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
		fileprint(NULL, "1000000", NULL);
		return out1;
		break;
	case 'R':
		fileprint(NULL, "0100000", NULL);
		return out2;
		break;
	case 'M':
		fileprint(NULL, "0010000", NULL);
		return out3;
		break;
	case 'F':
		fileprint(NULL, "0001000", NULL);
		return out4;
		break;
	case 'S':
		fileprint(NULL, "0000100", NULL);
		return out5;
		break;
	case 'L':
		fileprint(NULL, "0000010", NULL);
		return out6;
		break;
	case 'I':
		fileprint(NULL, "0000001", NULL);
		return out7;
		break;
	default:
		fileprint(NULL, "0000000", NULL);
		return out0;
		break;
	}
}
void notas2char()
{
	int len = 0, i = 0;
	char* frase;
	printf("\nIntroduce la longitud de tu canción\n");
	scanf_s("%d", &len);
	frase = (char*)malloc((len * 7) + 1);
	printf("\nIntroduce una frase formada por 0s y 1s\n");
	if (frase != NULL)
	{
		getchar();
		gets_s(frase, ((len * 7) + 1));
		fileprint(frase, NULL, NULL);
		fileprint(NULL, "\n------SE TRADUCE A------\n", NULL);
	}
	while (*(frase + i) != '\0')
	{
		if (*(frase + i) == '1')
		{
			switch (i % 7)
			{
			default:
				break;
			case 0:
				printf("do ");
				fileprint(NULL, "do ", NULL);
				break;
			case 1:
				printf("re ");
				fileprint(NULL, "re ", NULL);
				break;
			case 2:
				printf("mi ");
				fileprint(NULL, "mi ", NULL);
				break;
			case 3:
				printf("fa ");
				fileprint(NULL, "fa ", NULL);
				break;
			case 4:
				printf("sol ");
				fileprint(NULL, "sol ", NULL);
				break;
			case 5:
				printf("la ");
				fileprint(NULL, "la ", NULL);
				break;
			case 6:
				printf("si ");
				fileprint(NULL, "si ", NULL);
				break;
			}
		}
		i++;
	}
}
void fileprint(char data[], const char con[], char c)
{
	FILE* fichero;
	fopen_s(&fichero, "movimientos.txt", "a");
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
		else if (c != NULL)
		{
			fprintf_s(fichero,"%c",c);
		}
		fclose(fichero);
	}
}
