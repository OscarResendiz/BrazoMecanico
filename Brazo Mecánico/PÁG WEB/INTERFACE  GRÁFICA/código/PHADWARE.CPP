#include<stdio.h>
#include<ctype.h>
#include<conio.h>
#include"a:\hardware.h"
void main()
{
	char txt[256];
	char c;
	hardware h;
	clrscr();
	printf("DETECTANDO EL ROBOT...");
	printf("\nPORFABOR ESPERE UN MOMENTO...");
	if(h.puerto(0))
	{
		h.error(txt); //obtengo el error
		printf("\n%s",txt); //y lo muestro
		getch();
		return;
	}
	else
		printf("\nROBOT EN LINEA");
	getch();
	do
	{
		clrscr();
		printf("menu");
		printf("\n1 mover motor1");
		printf("\n2 mover motor1 del aldo contrario");
		printf("\n3 parar motor1");

		printf("\n4 mover motor2");
		printf("\n5 mover motor2 del aldo contrario");
		printf("\n6 parar motor2");

		printf("\n7 mover motor3");
		printf("\n8 mover motor3 del aldo contrario");
		printf("\n9 parar motor3");

		printf("\na mover motor4");
		printf("\nb mover motor4 del aldo contrario");
		printf("\nc parar motor4");

		printf("\nd mover motor5");
		printf("\ne mover motor5 del aldo contrario");
		printf("\nf parar motor5");
		printf("\ns parar salir");
		c=tolower(getch());
		switch(c)
		{
			case '1':
				h.motor1(1);
				break;
			case '2':
				h.motor1(2);
				break;
			case '3':
				h.motor1(0);
				break;

			case '4':
				h.motor2(1);
				break;
			case '5':
				h.motor2(2);
				break;
			case '6':
				h.motor2(0);
				break;
			case '7':
				h.motor3(1);
				break;
			case '8':
				h.motor3(2);
				break;
			case '9':
				h.motor3(0);
				break;

			case 'a':
				h.motor4(1);
				break;
			case 'b':
				h.motor4(2);
				break;
			case 'c':
				h.motor4(0);
				break;

			case 'd':
				h.motor5(1);
				break;
			case 'e':
				h.motor5(2);
				break;
			case 'f':
				h.motor5(0);
				break;

		}
	}while(c!='s');
}