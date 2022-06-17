 #include<ctype.h>
 #include<stdio.h>
 #include<conio.h>
 #include<stdlib.h>
 #include<stdarg.h>
 #include<graphics.h>
 #include<math.h>
 #include<dos.h>
 #include<bios.h>
 #include<iostream.h>
 #define MAXTRIZ 6
 #include"a:\hardware.h"

 void ActivRaton();               //inicia controladores del raton
 void dibpuntero();               //muestra la imagen del raton
 void Posraton();                 //indica la posicion del raton
 char Seleccion(void);            //regresa una opcion si se presiona el raton
 void InicGraf(); 		          //inicia el control del video
 void window();                   //crea el cuadro de inicio
 void Botones(int a); 	          //dibuja las opciones principales
 void fonopc(int x,int y, int a); //crea un fondo de una sola opcion
											 // a=0 sobrerrelieve  a=1 bajorelieva
 void fonsubo(int x,int y);       //crea un sub boton
 void movbot(int n, int x, int y);
 void GIRAR();                    //despliega barra para girar los ejes
 void BRAZO();                    //despliega barra para rotar articulaciones
 void OPCION();                   //despliega barra de opciones
 void Salir();
 void bome1();                    //borra GIRAR
 void bome2();                    //borra BRAZO
 void bome3();                    //borra OPCION
 void foncir(int x,int y, int c);
 void preinc();
 void inipuerto();
 void barrawin(int x, int y, int lx, int ly, int as);

class Matrices
		{
		public:
		void AxB(float A[MAXTRIZ][MAXTRIZ],float B[MAXTRIZ][MAXTRIZ]); //producto de dos matrices
		float RP[MAXTRIZ][MAXTRIZ]; //Resultado de la multiplicaci¢n de las matrices echa por la funcion AxB()
		float RT[MAXTRIZ][MAXTRIZ]; //Resultado de la transformacion a matriz de articulaciones giratorias
		void Forma_Gral_AG(float Alfa,float Teta,float Ai,float Di);
		};

void Matrices::Forma_Gral_AG(float Alfa,float Teta,float Ai,float Di)
  {
	Teta=Teta/57.3;
	Alfa=Alfa/57.3;
	RT[0][0]=cos(Teta);
	RT[1][0]=sin(Teta);
	RT[2][0]=0;
	RT[3][0]=0;

	RT[0][1]=-cos(Alfa)*sin(Teta);
	RT[1][1]=cos(Alfa)*cos(Teta);
	RT[2][1]=sin(Alfa);
	RT[3][1]=0;

	RT[0][2]=sin(Alfa)*sin(Teta);
	RT[1][2]=-sin(Alfa)*cos(Teta);
	RT[2][2]=cos(Alfa);
	RT[3][2]=0;

	RT[0][3]=Ai*cos(Teta);
	RT[1][3]=Ai*sin(Teta);
	RT[2][3]=Di;
	RT[3][3]=1;

  }

void Matrices::AxB(float A[MAXTRIZ][MAXTRIZ],float B[MAXTRIZ][MAXTRIZ])
	{
	int i=0,j=0;
	for(j=0;j<4;j++)
		for(i=0;i<4;i++)
		RP[i][j]=A[i][0]*B[0][j] + A[i][1]*B[1][j] + A[i][2]*B[2][j] + A[i][3]*B[3][j];
}

float seno[361];
float coseno[361];

void cal_senycos()
	{
	  int i;
	  for(i=0;i<361;i++)
		{
			coseno[i]=cos(i/57.3);
			seno[i]=sin(i/57.3);
		}
	}

class Vertices3D
	{
	int Ox,Oy; 	//Coordenadas en pantalla del origen del sistema 3D de coordenadas
	int vx,vy; 	//Posici¢n real (X,Y) en la pantalla
	int DIST;   //Profundidad de visualizacion

	public:
	//Constructor que inicializa las principales variables
	Vertices3D() {    DIST=450; //Distancia del observador al plano
							Ox=220;	//Posicion en pantalla del simulador
							Oy=190;
					 }

	void _3Da2D(int bx,int by,int bz,int Ax,int Ay,int Az,float Zoom);

	//retorna las conversiones 3D echas por _3Da2D() en coordenadas de pantalla 2D
	int PX(void) { return(vx); }
	int PY(void) { return(vy); }

	};


//Esta funcion rota un las coordenas de un punto 3D y lo transforma en 2D
void Vertices3D::_3Da2D(int bx,int by,int bz,int Ax,int Ay,int Az,float Zoom)
{
	long int rx,ry,rz;
	long int X,Y,Z;

	//Conversion de un sistema 3D en un 2D
	//Rotaci¢n sobre el eje X
	ry = coseno[Ax] * -by - seno[Ax] * bz;
	rz = seno[Ax] * -by + coseno[Ax] * bz;

	//Rotaci¢n sobre el eje Y
	rx =  coseno[Ay] * bx + seno[Ay] * rz;
	Z = -seno[Ay] * bx + coseno[Ay] * rz;

	//Rotaci¢n sobre el eje Z
	X = coseno[Az] * rx - seno[Az] * ry;
	Y = seno[Az] * rx + coseno[Az] * ry;

	//Transformaci¢n 3D a 2D
	vx = DIST * X / (DIST + Z);
	vy = DIST * Y / (DIST + Z);

	//Aplicaci¢n del Zoom
	vx=vx*Zoom+Ox;  //coordena X de pantalla
	vy=vy*Zoom+Oy;  //coordena Y de pantalla
}

void mesa(int Ax,int Ay,int Az,float zoom)
{ int g,k,l,ba=0;
  Vertices3D V1,V2,V3,V4,V5,V6,V7,V8;
for(k=0;k<3;k++)
 {if(k==1) ba=1;
  if(k==2) ba=0;

  for(g=0;g<2;g++)
  {  V1._3Da2D(-110+(k*80),0-(g*40),-40,Ax,Ay,Az,zoom);
	  V2._3Da2D(-110+(k*80),0-(g*40),40,Ax,Ay,Az,zoom);
	  V3._3Da2D(-30+(k*80),0-(g*40),40,Ax,Ay,Az,zoom);
	  V4._3Da2D(-30+(k*80),0-(g*40),-40,Ax,Ay,Az,zoom);
	  if(ba==0 || k==1 )
	  {	line(V1.PX(),V1.PY(),V2.PX(),V2.PY());
			line(V4.PX(),V4.PY(),V3.PX(),V3.PY());
			line(V3.PX(),V3.PY(),V2.PX(),V2.PY());
			line(V4.PX(),V4.PY(),V1.PX(),V1.PY());
			if(g==0) ba=1;
	  }
  }
 }
for(l=0;l<2;l++)
for(k=1;k<2;k++)
 for(g=0;g<2;g++)
  {	V1._3Da2D(-130+(k*100)+(l*75),0,-40+(g*75),Ax,Ay,Az,zoom);
		V2._3Da2D(-125+(k*100)+(l*75),0,-40+(g*75),Ax,Ay,Az,zoom);
		V3._3Da2D(-125+(k*100)+(l*75),0,-35+(g*75),Ax,Ay,Az,zoom);
		V4._3Da2D(-130+(k*100)+(l*75),0,-35+(g*75),Ax,Ay,Az,zoom);
		V5._3Da2D(-130+(k*100)+(l*75),-70,-40+(g*75),Ax,Ay,Az,zoom);
		V6._3Da2D(-125+(k*100)+(l*75),-70,-40+(g*75),Ax,Ay,Az,zoom);
		V7._3Da2D(-125+(k*100)+(l*75),-70,-35+(g*75),Ax,Ay,Az,zoom);
		V8._3Da2D(-130+(k*100)+(l*75),-70,-35+(g*75),Ax,Ay,Az,zoom);
		line(V1.PX(),V1.PY(),V5.PX(),V5.PY());
		line(V2.PX(),V2.PY(),V6.PX(),V6.PY());
		line(V3.PX(),V3.PY(),V7.PX(),V7.PY());
		line(V4.PX(),V4.PY(),V8.PX(),V8.PY());
		}
  }


 int boton,x,y,gart=1,gxyz=1,sino=1,acma=0;
 int Tecla;
 int bopr=1;
 int sip=0,acp=0;

void main(void)
{

InicGraf();

int AnguloX=45,AnguloY=330,AnguloZ=0;
int five=0,ccon=0, mis;
float zoom=1.3;
char h,opc;
int Rotar=0;    		//base del brazo
int Art_1=60;        //elemento 1
int Art_2=60;        //elemento 2
int Art_12=-40;
int Art_3=60;        //elemento 3
int Pinza_A=0;
int Pinza_B=0;

int X0,Y0,Z0;
int X1,Y1,Z1;
int X2,Y2,Z2;
int X3,Y3,Z3;
int X4,Y4,Z4;
int X5,Y5,Z5;
int X6,Y6,Z6;
int X7,Y7,Z7;

int A,B,C;
int D,E,F;
int G,H,I;
int J,K,L;
int Ay1,Ay2,Ay3;
int Ay4,Ay5,Ay6;
int P1,P2,P3;
int P4,P5,P6;
int P7,P8,P9;

int inc=1;   // velocidad de las articulaciones

int Teta1=90,Teta2=0,Teta3=90,Teta4=0,Teta5=0,Teta6=0;
int Alfa1=0,Alfa2=-90,Alfa3=0,Alfa4=0,Alfa5=0,Alfa6=0;
int a1=0,a2=70,a3=20,a4=0,a5=-20,a6=0;
int d1=0,d2=20,d3=0,d4=40,d5=0,d6=15;

	 //a2 es el tama¤o de articulacion 1
	 //d4 es el tama¤o de articulacion 2
	 //a3 es separacion entre 1,2
	 //a5 es separacion entre 3,4
	 //d6 es el tama¤o de la mu¤eca

cal_senycos();

Vertices3D punto[20];

Matrices Mat1,Mat2,MATX,MATX2,MATX3,MATX4,MATY1,MATY2;
Matrices R1,R2,R3,R4,R5,RMAT,RMAT2,RMAT3,RMATY1,RMATY2,MNA,MNB,MNC;

hardware mot;
	window();
////////     //deteccion del puerto
	int mas;
	char txt[256];
	barrawin(150,150,300,150,0);
	setcolor(31);
	outtextxy(180,191,"DETECTANDO EL ROBOT");
	outtextxy(180,210,"POR FAVOR ESPERE UN MOMENTO...");
	if(mot.puerto(0))
	 {
		mot.error(txt);
		//setcolor(4);
		outtextxy(200,250,txt);
		barrawin(getmaxx()-410,getmaxy()-15,150,13,1);
		outtextxy(getmaxx()-400,getmaxy()-12,"ROBOT SIN CONECC");
		sip=0;  acp=0;
	 }
	else
	 { barrawin(160,230,280,10,1);
		setfillstyle(1,4);
		for(mas=0;mas<=275;mas++)
		  { bar(161,232,164+mas,238);
			 delay(8);
		  }
		setcolor(4);
		outtextxy(180,250,"ROBOT EN LINEA");
		barrawin(getmaxx()-410,getmaxy()-15,150,13,1);
		outtextxy(getmaxx()-400,getmaxy()-12,"ROBOT CONECTADO");
		sip=1;  acp=1;
	 }
	getch();
	setfillstyle(1,0);
	bar(150,150,450,300);
	if(acma==0)
	  { barrawin(getmaxx()-210,getmaxy()-15,70,13,1);
		 setcolor(0);
		 outtextxy(getmaxx()-200,getmaxy()-12,"MANUAL");
	  }
	else
	  { barrawin(getmaxx()-210,getmaxy()-15,70,13,1);
		 setcolor(4);
		 outtextxy(getmaxx()-200,getmaxy()-12,"AUTOMT");
	  }
	if(sip==1)
	  { barrawin(getmaxx()-90,getmaxy()-15,80,13,1);
		 setcolor(0);
		 outtextxy(getmaxx()-80,getmaxy()-12,"SIMULADO");
	  }
	else
	  { barrawin(getmaxx()-90,getmaxy()-15,80,13,1);
		 setcolor(4);
		 outtextxy(getmaxx()-80,getmaxy()-12,"MDO REAL");
	  }

////////     //fin de la deteccion del puerto

  //preinc();
  Botones(0);
  ActivRaton();
  dibpuntero();
  for(;;)
	{
		Posraton();
		opc=Seleccion();
		switch(opc)
		{
			case 'A':GIRAR(); break;
			case 'B':BRAZO(); break;
			case 'C':Tecla=1;
						bopr=0;
						break;
			case 'D':Tecla=2;
						bopr=0;
						break;
			case 'E':Tecla=3;
						bopr=0;
						break;
			case 'F':Tecla=4;
						bopr=0;
						break;
			case 'G':Tecla=5;
						bopr=0;
						break;
			case 'H':Tecla=6;
						bopr=0;
						break;
			case 'I':Tecla=7;
						bopr=0;
						break;
			case 'J':Tecla=8;
						bopr=0;
						break;
			case 'K':Tecla=16;
						bopr=0;
						break;
			case 'L':Tecla=17;
						bopr=0;
						break;
			case 'M':Tecla=10;
						bopr=0;
						break;
			case 'N':Tecla=11;
						bopr=0;
						break;
			case 'O':Tecla=12;
						bopr=0;
						break;
			case 'P':Tecla=13;
						bopr=0;
						break;
			case 'Q':Tecla=14;
						bopr=0;
						break;
			case 'R':Tecla=15;
						bopr=0;
						break;
			case 'T':Tecla=18;
						bopr=0;
						break;
			case 'U':Tecla=19;
						bopr=0;
						break;
			case 'V':Botones(1);
						acma=0;
						bopr=0;
						barrawin(getmaxx()-210,getmaxy()-15,70,13,1);
						setcolor(0);
						outtextxy(getmaxx()-200,getmaxy()-12,"MANUAL");
						OPCION();
						break;
			case 'X':Botones(0);
						acma=1;
						sip=1;
						barrawin(getmaxx()-210,getmaxy()-15,70,13,1);
						barrawin(getmaxx()-90,getmaxy()-15,80,13,1);
						setcolor(4);
						outtextxy(getmaxx()-200,getmaxy()-12,"AUTOMT");
						outtextxy(getmaxx()-80,getmaxy()-12,"MDO REAL");
						OPCION();
						bopr=0;
						break;
			case 'Y':
						if(acp==1 && acma==0)
						  {   if(sip==1)  { sip=0;
												  barrawin(getmaxx()-90,getmaxy()-15,80,13,1);
												  setcolor(0);
												  outtextxy(getmaxx()-80,getmaxy()-12,"SIMULADO");
												  OPCION();
												}
								else        { sip=1;
												  barrawin(getmaxx()-90,getmaxy()-15,80,13,1);
												  setcolor(4);
												  outtextxy(getmaxx()-80,getmaxy()-12,"MDO REAL");
												  OPCION();
												}
						  }
						break;

			case 'S':Salir();
						getch();
						closegraph();
						exit(0);

			case 'Z':OPCION(); break;

			case 'q':if(acp==0)
						  {
							barrawin(150,150,300,150,0);
							setcolor(31);
							outtextxy(180,191,"DETECTANDO EL ROBOT");
							outtextxy(180,210,"POR FAVOR ESPERE UN MOMENTO...");
							if(mot.puerto(0))
								{
									mot.error(txt);
									setcolor(4);
									outtextxy(200,250,txt);
									sip=0;  acp=0;
								}
							else
								{ 	barrawin(160,230,280,10,1);
									setfillstyle(1,4);
									for(mas=0;mas<=275;mas++)
										{ 	bar(161,232,164+mas,238);
											delay(8);
										}
									barrawin(getmaxx()-410,getmaxy()-15,150,13,1);
									setcolor(4);
									outtextxy(180,250,"ROBOT EN LINEA");
									outtextxy(getmaxx()-400,getmaxy()-12,"ROBOT CONECTADO");
									sip=1;  acp=1;
								}
							getch();
							setfillstyle(1,0);
							bar(150,150,450,300);
						  }
						break;
		 }

setcolor(4);
mesa(AnguloX,AnguloY,AnguloZ,zoom);

//parametros de funcion Forma_Gral_AG(Alfa,Teta,Ai,di)
//Ai - tama¤o elemento
//Di - separacion del elemento
//Alfa -  ngulo del siguiente elemento
//Teta -  ngulo del elemento

MATX.Forma_Gral_AG(Rotar+Alfa1,Teta1,a1,d1);
A=RMAT.RT[0][3];
B=RMAT.RT[1][3];
C=RMAT.RT[2][3];

MATX2.Forma_Gral_AG(-90,90,0,20);
RMAT.AxB(MATX.RT,MATX2.RT);
D=RMAT.RP[0][3];                      //brazo 1A
E=RMAT.RP[1][3];
F=RMAT.RP[2][3];


MATY1.Forma_Gral_AG(-90,0,-25,0);
RMATY1.AxB(RMAT.RP,MATY1.RT);
Ay1=RMATY1.RP[0][3];
Ay2=RMATY1.RP[1][3];
Ay3=RMATY1.RP[2][3];

MATY2.Forma_Gral_AG(0,0,0,20);
RMATY2.AxB(RMATY1.RP,MATY2.RT);
Ay4=RMATY2.RP[0][3];
Ay5=RMATY2.RP[1][3];
Ay6=RMATY2.RP[2][3];


MATX3.Forma_Gral_AG(Art_1+Alfa1,-90,0,0);
RMAT2.AxB(RMAT.RP,MATX3.RT);
G=RMAT2.RP[0][3];
H=RMAT2.RP[1][3];
I=RMAT2.RP[2][3];

MATX4.Forma_Gral_AG(90,0,0,80);
RMAT3.AxB(RMAT2.RP,MATX4.RT);
J=RMAT3.RP[0][3];
K=RMAT3.RP[1][3];
L=RMAT3.RP[2][3];

Mat1.Forma_Gral_AG(Rotar+Alfa1,Teta1,a1,d1);
X1=Mat1.RT[1][3];
Y1=Mat1.RT[1][3];
Z1=Mat1.RT[2][3];

Mat2.Forma_Gral_AG(Alfa2,Art_1+Teta2,a2,d2);
R1.AxB(Mat1.RT,Mat2.RT);
X2=R1.RP[0][3];
Y2=R1.RP[1][3];
Z2=R1.RP[2][3];


Mat1.Forma_Gral_AG(Art_2+Alfa3,Teta3,a3,d3);    //brazo 1A
R2.AxB(R1.RP,Mat1.RT);
X3=R2.RP[0][3];
Y3=R2.RP[1][3];
Z3=R2.RP[2][3];

Mat1.Forma_Gral_AG(Art_12+Alfa4,Teta4,a4,d4);
R3.AxB(R2.RP,Mat1.RT);
X4=R3.RP[0][3];
Y4=R3.RP[1][3];
Z4=R3.RP[2][3];

Mat1.Forma_Gral_AG(Art_3+Alfa5,Teta5,a5,d5);
R4.AxB(R3.RP,Mat1.RT);
X5=R4.RP[0][3];
Y5=R4.RP[1][3];
Z5=R4.RP[2][3];

Mat1.Forma_Gral_AG(Alfa6,Teta6,a6,d6);
R5.AxB(R4.RP,Mat1.RT);
X6=R5.RP[0][3];
Y6=R5.RP[1][3];
Z6=R5.RP[2][3];

Mat1.Forma_Gral_AG(0,0,20,15); //reduce la mu¤eca
MNA.AxB(R4.RP,Mat1.RT);
P1=MNA.RP[0][3];
P2=MNA.RP[1][3];
P3=MNA.RP[2][3];

Mat1.Forma_Gral_AG(0,0,Pinza_A,7);  //reduce la pinza
MNB.AxB(MNA.RP,Mat1.RT);
P4=MNB.RP[0][3];
P5=MNB.RP[1][3];
P6=MNB.RP[2][3];

Mat1.Forma_Gral_AG(0,0,Pinza_B,7);  //reduce la pinza
MNC.AxB(R5.RP,Mat1.RT);
P7=MNC.RP[0][3];
P8=MNC.RP[1][3];
P9=MNC.RP[2][3];

					//conversion 3D a 2D
punto[0]._3Da2D(X1,Y1,Z1,AnguloX,AnguloY,AnguloZ,zoom);
punto[1]._3Da2D(X2,Y2,Z2,AnguloX,AnguloY,AnguloZ,zoom);
punto[2]._3Da2D(X3,Y3,Z3,AnguloX,AnguloY,AnguloZ,zoom);
punto[3]._3Da2D(X4,Y4,Z4,AnguloX,AnguloY,AnguloZ,zoom);
punto[4]._3Da2D(X5,Y5,Z5,AnguloX,AnguloY,AnguloZ,zoom);
punto[5]._3Da2D(X6,Y6,Z6,AnguloX,AnguloY,AnguloZ,zoom);
punto[6]._3Da2D(A,B,C,AnguloX,AnguloY,AnguloZ,zoom);
punto[7]._3Da2D(D,E,F,AnguloX,AnguloY,AnguloZ,zoom);
punto[8]._3Da2D(G,H,I,AnguloX,AnguloY,AnguloZ,zoom);
punto[9]._3Da2D(J,K,L,AnguloX,AnguloY,AnguloZ,zoom);
punto[10]._3Da2D(Ay1,Ay2,Ay3,AnguloX,AnguloY,AnguloZ,zoom);
punto[11]._3Da2D(Ay4,Ay5,Ay6,AnguloX,AnguloY,AnguloZ,zoom);
punto[12]._3Da2D(P1,P2,P3,AnguloX,AnguloY,AnguloZ,zoom);
punto[13]._3Da2D(P4,P5,P6,AnguloX,AnguloY,AnguloZ,zoom);
punto[14]._3Da2D(P7,P8,P9,AnguloX,AnguloY,AnguloZ,zoom);


{
setcolor(34);
					  //brazo 1A
line(punto[7].PX(),punto[7].PY(),punto[1].PX(),punto[1].PY());
					  //brazo 1B
line(punto[0].PX(),punto[0].PY(),punto[2].PX(),punto[2].PY());
					  //brazo 2A
line(punto[1].PX(),punto[1].PY(),punto[4].PX(),punto[4].PY());
					  //brazo 2B
line(punto[2].PX(),punto[2].PY(),punto[3].PX(),punto[3].PY());
					  //brazo 3A
line(punto[4].PX(),punto[4].PY(),punto[5].PX(),punto[5].PY());
					  //brazo 3B
line(punto[3].PX(),punto[3].PY(),punto[12].PX(),punto[12].PY());
					  //brazo 4A
line(punto[5].PX(),punto[5].PY(),punto[14].PX(),punto[14].PY());
					  //brazo 4B
line(punto[12].PX(),punto[12].PY(),punto[13].PX(),punto[13].PY());
					  //union de 1,2
line(punto[1].PX(),punto[1].PY(),punto[2].PX(),punto[2].PY());
					  //union de 2,3
line(punto[3].PX(),punto[3].PY(),punto[4].PX(),punto[4].PY());

setcolor(43);
					  //base de 1A
line(punto[0].PX(),punto[0].PY(),punto[11].PX(),punto[11].PY());
					  //base  de 1B
line(punto[7].PX(),punto[7].PY(),punto[0].PX(),punto[0].PY());
					  //base  de 1C
line(punto[7].PX(),punto[7].PY(),punto[10].PX(),punto[10].PY());
					  //base de 1D
line(punto[10].PX(),punto[10].PY(),punto[11].PX(),punto[11].PY());

					  //brazo 222
//line(punto[8].PX(),punto[8].PY(),punto[9].PX(),punto[9].PY());
					  //brazo 1aa
//line(punto[10].PX(),punto[10].PY(),punto[2].PX(),punto[2].PY());
}

if(bopr==0)
 { boton=0;
	bopr=1;
	if(ccon>=10)
	  { ccon=0; five=5; }
	else ccon++;
 }
if(five==5)
  {
delay(5);
five=0;
setcolor(0);
					  //brazo 1A
line(punto[7].PX(),punto[7].PY(),punto[1].PX(),punto[1].PY());
					  //brazo 1B
line(punto[0].PX(),punto[0].PY(),punto[2].PX(),punto[2].PY());
					  //brazo 2A
line(punto[1].PX(),punto[1].PY(),punto[4].PX(),punto[4].PY());
					  //brazo 2B
line(punto[2].PX(),punto[2].PY(),punto[3].PX(),punto[3].PY());
					  //brazo 3A
line(punto[4].PX(),punto[4].PY(),punto[5].PX(),punto[5].PY());
					  //brazo 3B
line(punto[3].PX(),punto[3].PY(),punto[12].PX(),punto[12].PY());
					  //brazo 4A
line(punto[5].PX(),punto[5].PY(),punto[14].PX(),punto[14].PY());
					  //brazo 4B
line(punto[12].PX(),punto[12].PY(),punto[13].PX(),punto[13].PY());
					  //union de 1,2
line(punto[1].PX(),punto[1].PY(),punto[2].PX(),punto[2].PY());
					  //union de 2,3
line(punto[3].PX(),punto[3].PY(),punto[4].PX(),punto[4].PY());

					  //base de 1A
line(punto[0].PX(),punto[0].PY(),punto[11].PX(),punto[11].PY());
					  //base  de 1B
line(punto[7].PX(),punto[7].PY(),punto[0].PX(),punto[0].PY());
					  //base  de 1C
line(punto[7].PX(),punto[7].PY(),punto[10].PX(),punto[10].PY());
					  //base de 1D
line(punto[10].PX(),punto[10].PY(),punto[11].PX(),punto[11].PY());

					  //brazo 222
//line(punto[8].PX(),punto[8].PY(),punto[9].PX(),punto[9].PY());
					  //brazo 1aa
//line(punto[10].PX(),punto[10].PY(),punto[2].PX(),punto[2].PY());

mesa(AnguloX,AnguloY,AnguloZ,zoom);

/*************************************************************************/

  switch(Tecla)
	{
	case 1: 		if(Art_1>=90)   Art_1=90;
					else { if(sip==1)
								{ mot.motor2(1); delay(10); mot.motor2(0);}
							 Art_1+=inc;
						  }
					break;

	case 2: 		if(Art_1<=45) Art_1=45;
					else { if(sip==1)
								{ mot.motor2(2);  delay(10); mot.motor2(0);  }
							 Art_1-=inc;
						  }
					break;

	case 3:  	if(Art_2>=90) Art_2=90;
					else { if(sip==1)
								{ mot.motor3(1);  delay(10); mot.motor3(0);  }
							 Art_2+=inc;
						  }
					break;

	case 4: 	   if(Art_2<=45) Art_2=45;
					else { if(sip==1)
								{ mot.motor3(2);  delay(10); mot.motor3(0);  }
							 Art_2-=inc;
						  }
					break;

	case 5:     if(Art_3<=45) Art_3=45;
					else { if(sip==1)
								{ mot.motor4(1);  delay(10); mot.motor4(0);  }
							 Art_3-=inc;
						  }
					break;

	case 6:    	if(Art_3>=90) Art_3=90;
					else { if(sip==1)
								{ mot.motor4(2);  delay(10); mot.motor4(0);  }
							 Art_3+=inc;
						  }
					break;

	case 7: if(Pinza_A>-10) { Pinza_A-=inc; Pinza_B+=inc;
									  if(sip==1)
										  { mot.motor5(1);  delay(10); mot.motor5(0);  }
									}  break;

	case 8: if(Pinza_A<10)  { Pinza_A+=inc; Pinza_B-=inc;
									  if(sip==1)
										  { mot.motor5(2);  delay(10); mot.motor5(0);  }
									}  break;

	case 10: AnguloX+=inc;   break;

	case 11: AnguloX-=inc;   break;

	case 12: AnguloY+=inc;   break;

	case 13: AnguloY-=inc;   break;

	case 14: AnguloZ+=inc;   break;

	case 15: AnguloZ-=inc;   break;

	case 16:  	if(Rotar>=135) Rotar=135;
					else { if(sip==1)
								{ mot.motor1(1); delay(10); mot.motor1(0);}
							 Rotar+=inc;
						  }
					break;

	case 17:    if(Rotar<=0) Rotar=0;
					else { if(sip==1)
								{ mot.motor1(2); delay(10); mot.motor1(0);}
							 Rotar-=inc;
						  }
					break;

	case 18: zoom+=0.05;   break;

	case 19: zoom-=0.05;   break;

	}

	if(AnguloX>360) AnguloX=0;
	if(AnguloX<0) AnguloX=360;
	if(AnguloY>360) AnguloY=0;
	if(AnguloY<0) AnguloY=360;
	if(AnguloZ>360) AnguloZ=0;
	if(AnguloZ<0) AnguloZ=360;

if(zoom>=1.5) zoom=1.5;

if(zoom<0.05) zoom=0.05;
}
}
}

void InicGraf()
{
  int IG=DETECT,gmode,gerror;
  initgraph(&IG,&gmode,"C:\\tc\\BGI") ;
  gerror=graphresult();
  if(gerror!=grOk)
	  {
		cout<<"\nError en la inicializaci¢n de los gr ficos\n";
		cout<<"\n "<<grapherrormsg(gerror);
		getch();
	  }
}

void window()
{
 setfillstyle(1,7);
 bar(1,1,getmaxx()-1,16);
 bar(1,getmaxy(),getmaxx()-1,getmaxy()-18);
 bar(1,1,4,getmaxy()-1);
 bar(getmaxx()-5,1,getmaxx()-1,getmaxy()-1);
 setcolor(0);
 line(4,17,4,getmaxy()-18);
 line(4,17,getmaxx()-4,17);
 setcolor(31);
 line(getmaxx()-5,17,getmaxx()-5,getmaxy()-18);
 line(4,getmaxy()-18,getmaxx()-5,getmaxy()-18);

}

void Botones(int a)
{
  int ax=getmaxx()-160, ay=2;
  int bx=getmaxx()-80, by=2;
  int cx=1, cy=getmaxy()-15;
  int dx=5, dy=2;
  int sa;
  if(a==1) sa=0;
  else     sa=7;
  fonopc(ax,ay,a);   //esquina superior izquierda
  fonopc(bx,ay,a);
  fonopc(cx,cy,1);
  fonopc(dx,dy,1);
  setcolor(sa);
  outtextxy(ax+9,by+3,"GIRAR");
  outtextxy(bx+9,by+3,"BRAZO");
  setcolor(31);
  outtextxy(cx+9,cy+3,"SALIR");
  setcolor(0);
  outtextxy(dx+9,dy+3,"OPCION");
}

void fonopc(int x,int y, int q)
 {
  int d,s,m;
  if(q==1) { d=31; s=0; m=1; }
  else     { d=0; s=31; m=0; }
  int xf, yf;
  xf=x+67; yf=y+13;
  setcolor(d);
  line(x,y,xf,y);
  line(x,y,x,yf);
  setcolor(7+m);
  line(x+1,yf-1,xf-1,yf-1);
  line(xf-1,y+1,xf-1,yf-1);
  setcolor(s);
  line(x,yf,xf,yf);
  line(xf,y,xf,yf);
 }

void ActivRaton()
 {
  union REGS in,out;
  in.x.ax=0;
  int86(0x33, &in, &out);
 }

void dibpuntero()
 {
  union REGS in,out;
  in.x.ax=1;
  int86(0x33, &in, &out);
 }

void Posraton()
 {
  union REGS in,out;
  in.x.ax=3;
  int86(0x33, &in, &out);
  x=out.x.cx;
  y=out.x.dx;
  boton=out.x.bx;
 }

char Seleccion(void)
{
  int xm,ym;
  char op;
  long int far *imagen,tamano;
  xm=getmaxx();
  ym=getmaxy();

  if(boton==1)
  {  Tecla=0;
	  if(x>=xm-160 && x<=xm-13 && y>=2 && y<=14 & acma==0)
	  {   if(x<=xm-93)
				{  op='A';
					if(gart==0) { gart=1; bome2(); }
					if(sino==0) { gart=1; bome3(); }
					return(op);
				}
			else
				{  op='B';
					if(gxyz==0) {gxyz=1; bome1(); }
					if(sino==0) {sino=1; bome3(); }
					return(op);
				}
	  }
	  else
		 {  if(x>=xm-80 && x<=xm-13 && y>=15 && y<=164)
				{ if(gart==0)
				  {
					 if(y<=30)
						{  op='D'; return(op); }
					 else
						{ if(y<=45)
							 { op='C'; return(op); }
						  else
							 { if(y<=60)
								  { op='E'; return(op); }
								else
								  { if(y<=75)
										{ op='F'; return(op); }
									 else
										{ if(y<=90)
											 { op='H'; return(op); }
										  else
											 { if(y<=105)
												  { op='G'; return(op); }
												else
												  { if(y<=120)
														{ op='J'; return(op); }
													 else
														{ if(y<=135)
															 { op='I'; return(op); }
														  else
															 { if(y<=150)
																  { op='K'; return(op); }
																else
																  {
																	 op='L'; return(op);
																  }
															 }
														}
												  }
											 }
										}
								  }
							 }
						}
				  }
				else
					{
						if(gxyz==0) bome1();
						if(sino==0) bome3();
						sino=1;  gxyz=1;
						op='W';  return(op);
					}
				}
			 else
				{ if(x>=xm-160 && x<=xm-93 && y>=15 && y<=134)
					  { if(gxyz==0)
						 {
						 if(y<=30)
							{ op='M'; return(op); }
						 else
							{ if(y<=45)
								 { op='N'; return(op); }
							  else
								 { if(y<=60)
									  { op='O'; return(op); }
									else
									  { if(y<=75)
											{ op='P'; return(op); }
										 else
											{ if(y<=90)
												 { op='Q'; return(op); }
											  else
												 { if(y<=105)
													  { op='R'; return(op); }
													else
													  { if(y<=120)
															{ op='T'; return(op); }
														 else
															{
															  op='U'; return(op);
															}
													  }
												 }
											}
									  }
								 }
							}
						 }
					  else
						 {
						  if(gart==0) bome2();
						  if(sino==0) bome3();
						  gart=1;  sino=1;
						  op='W';  return(op);
						 }
					  }
				  else
					 { if(x>=5 && x<=71 && y>=2 && y<=14)
						  { if(gart==0)
								{ gart=1; bome2(); }
							 if(gxyz==0)
								{ gxyz=1; bome1();}
							 op='Z'; return(op);
						  }
						else
						  { if(x>=5 && x<=71 && y>=15 && y<=75)
								{ if(sino==0)
									 { if(y<=30)
										  { op='V'; return(op); }
										else
										  { if(y<=45)
												{ op='X'; return(op); }
											 else
												{ if(y<=60)
													 { op='Y'; return(op); }
												  else
													 { op='q'; return(op); }
												}
										  }
									 }
								  else
									 { if(gart==0) bome2();
										if(gxyz==0) bome1();
										gart=1;  gxyz=1;
										op='W';  return(op);
									 }
								}
							 else
								{  if(x>=2 && x<=68 && y>=ym-15 && y<=ym)
									  { op='S';  return(op);   }
									else
									  {
										if(gxyz==0) { gxyz=1; bome1(); }
										if(gart==0) { gart=1; bome2(); }
										if(sino==0) { sino=1; bome3(); }

									  }
								}
						  }
					 }
				}
		 }
  }
return 0;
}

void bome1 ()
  {  setfillstyle(1,0);
	 bar(getmaxx()-160,15,getmaxx()-93,133);
	 setcolor(7);
	 line(getmaxx()-160,16,getmaxx()-93,16);
  }

void bome2 ()
  {
	 setfillstyle(1,0);
	 bar(getmaxx()-80,15,getmaxx()-13,164);
	 setcolor(7);
	 line(getmaxx()-80,16,getmaxx()-13,16);
  }

void bome3 ()
  {
	 setfillstyle(1,0);
	 bar(5,15,71,74);
	 setcolor(7);
	 line(5,16,72,16);
  }

 void fonsubo(int x,int y)
 {
  int xf=x+67, yf=y+14;   //Tama¤o del boton
  setfillstyle(1,7);
  bar(x,y,xf,yf-1);
  setcolor(31);
  line(x,y,xf,y);
  line(x,y,x,yf);
  setcolor(0);
  line(xf,y,xf,yf);
  line(x,yf,xf,yf);
 }

 void foncir(int x,int y, int c)
 {
  int a;
  if(c==0) a=14;
  else     a=28;
  setcolor(14);
  setfillstyle(1,14);
  fillellipse (x,y,4,4);
  setfillstyle(1,a);
  fillellipse (x,y,2,2);

  }

 void GIRAR()
 {
  int x, y, lx, ly;
  lx=getmaxx()-160; ly=15;       //esquina superior izquierda   97 39
  x=lx+9; y=ly+5;
  gxyz=0;
  movbot(8,lx,ly);
  setcolor(0);
  outtextxy(x,y,"EJE X I");
  outtextxy(x,y+15,"EJE X D");
  outtextxy(x,y+30,"EJE Y I");
  outtextxy(x,y+45,"EJE Y D");
  outtextxy(x,y+60,"EJE Z I");
  outtextxy(x,y+75,"EJE Z D");
  outtextxy(x,y+90,"ZOOM +");
  outtextxy(x,y+105,"ZOMM -");
 }

 void OPCION()
 {
  int x, y, lx, ly;
  lx=5; ly=15;       //esquina superior izquierda   97 39
  x=lx+9; y=ly+5;
  sino=0;
  movbot(4,lx,ly);
  setcolor(0);
  outtextxy(x,y,"MANUAL");
  outtextxy(x,y+15,"AUTOMAT");
  outtextxy(x,y+45,"DETECC");
  if(acp==1)
	 { if(acma==0)
		{ if(sip==1)  { setcolor(31); outtextxy(x,y+30,"DESACTI"); }
		  else        { setcolor(4);  outtextxy(x,y+30,"ACTIVAR"); }
		}
		else   { setcolor(47); outtextxy(x,y+30,"NO VALI");   }
	 }
  else  { setcolor(47); outtextxy(x,y+30,"NO VALI");   }


  }

  void BRAZO()
 {
  int x, y, lx, ly;
  lx=getmaxx()-80; ly=15;
  x=lx+9; y=ly+5;
  gart=0;
  movbot(10,lx,ly);
  setcolor(0);
  outtextxy(x,y,"1 Arr");
  outtextxy(x,y+15,"1 Aba");
  outtextxy(x,y+30,"2 Arr");
  outtextxy(x,y+45,"2 Aba");
  outtextxy(x,y+60,"3 Arr");
  outtextxy(x,y+75,"3 Aba");
  outtextxy(x,y+90,"Pz Abr");
  outtextxy(x,y+105,"Pz Cer");
  outtextxy(x,y+120,"Rotar D");
  outtextxy(x,y+135,"Rotar I");
 }

 void movbot(int n, int x, int y)
 {
  int i,c,a;
  c=n-1;
  for(i=0;i<(c*15)+1;i++)
  {
	 fonsubo(x,y+i);     //15 tama¤o de filas
	 delay(1);
	 for(a=0;a<=n;a++)
	 {
	 if(y+i>=(y+a*15))
		fonsubo(x,y+a*15);     //15 tama¤o de filas
	 }
  }
 }

void Salir()
{
 int x,y,a,va,my,mx;
 my=getmaxy()/2;
 mx=getmaxx()/2;
 for(x=0,a=0;x<mx;x++)
	{ if(a==1) { va=1; a=0; }
	  else     { va=0; a=1; }
	  for(y=va;y<my;y=y+2)
		 { putpixel(x,y,0);
			putpixel(x,getmaxy()-y,0);
			putpixel(getmaxx()-x,y,0);
			putpixel(getmaxx()-x,getmaxy()-y,0);
		 }
	}
 barrawin(150,150,200,150,0);
 outtextxy(180,191,"SALIR");
 fonopc(180,250,1);
 outtextxy(183,252,"ACEPTAR");
 fonopc(260,250,1);
 outtextxy(263,252,"CANCELAR");
}

void preinc()
{
  int Ax=0,Ay=0,Az=0;
  float zoom=1.0;
  int g,k,l;
  Vertices3D V1,V2,V3,V4,V5,V6,V7,V8,V9,V10,V11,V12;
  Vertices3D F1,F2,F3,F4,F5,F6,F7,F8,F9,F10;
  Vertices3D B1,B2,B3,B4,B5,B6,B7,B8,B9,B10;
  Vertices3D C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14;

for(g=0;g<90;g++)
  {
	  V1._3Da2D(-90,0,0,Ax+g,Ay,Az,zoom);
	  V2._3Da2D(-90,50,0,Ax+g,Ay,Az,zoom);
	  V3._3Da2D(-130,50,0,Ax+g,Ay,Az,zoom);
	  V4._3Da2D(-130,60,0,Ax+g,Ay,Az,zoom);
	  V5._3Da2D(-90,60,0,Ax+g,Ay,Az,zoom);
	  V6._3Da2D(-90,80,0,Ax+g,Ay,Az,zoom);
	  V7._3Da2D(-150,80,0,Ax+g,Ay,Az,zoom);
	  V8._3Da2D(-150,40,0,Ax+g,Ay,Az,zoom);
	  V9._3Da2D(-110,40,0,Ax+g,Ay,Az,zoom);
	  V10._3Da2D(-110,20,0,Ax+g,Ay,Az,zoom);
	  V11._3Da2D(-150,20,0,Ax+g,Ay,Az,zoom);
	  V12._3Da2D(-150,0,0,Ax+g,Ay,Az,zoom);
	  B1._3Da2D(150,0,0,Ax+g,Ay,Az,zoom);
	  B2._3Da2D(150,20,0,Ax+g,Ay,Az,zoom);
	  B3._3Da2D(130,20,0,Ax+g,Ay,Az,zoom);
	  B4._3Da2D(130,40,0,Ax+g,Ay,Az,zoom);
	  B5._3Da2D(110,40,0,Ax+g,Ay,Az,zoom);
	  B6._3Da2D(110,60,0,Ax+g,Ay,Az,zoom);
	  B7._3Da2D(150,60,0,Ax+g,Ay,Az,zoom);
	  B8._3Da2D(150,80,0,Ax+g,Ay,Az,zoom);
	  B9._3Da2D(90,80,0,Ax+g,Ay,Az,zoom);
	  B10._3Da2D(90,0,0,Ax+g,Ay,Az,zoom);
	  F1._3Da2D(-10,0,0,Ax+g,Ay,Az,zoom);
	  F2._3Da2D(-10,20,0,Ax+g,Ay,Az,zoom);
	  F3._3Da2D(-30,20,0,Ax+g,Ay,Az,zoom);
	  F4._3Da2D(-30,40,0,Ax+g,Ay,Az,zoom);
	  F5._3Da2D(-50,40,0,Ax+g,Ay,Az,zoom);
	  F6._3Da2D(-50,60,0,Ax+g,Ay,Az,zoom);
	  F7._3Da2D(-10,60,0,Ax+g,Ay,Az,zoom);
	  F8._3Da2D(-10,80,0,Ax+g,Ay,Az,zoom);
	  F9._3Da2D(-70,80,0,Ax+g,Ay,Az,zoom);
	  F10._3Da2D(-70,0,0,Ax+g,Ay,Az,zoom);
	  setcolor(43);
	  line(V1.PX(),V1.PY(),V2.PX(),V2.PY());
	  line(V2.PX(),V2.PY(),V3.PX(),V3.PY());
	  line(V3.PX(),V3.PY(),V4.PX(),V4.PY());
	  line(V4.PX(),V4.PY(),V5.PX(),V5.PY());
	  line(V5.PX(),V5.PY(),V6.PX(),V6.PY());
	  line(V6.PX(),V6.PY(),V7.PX(),V7.PY());
	  line(V7.PX(),V7.PY(),V8.PX(),V8.PY());
	  line(V8.PX(),V8.PY(),V9.PX(),V9.PY());
	  line(V9.PX(),V9.PY(),V10.PX(),V10.PY());
	  line(V10.PX(),V10.PY(),V11.PX(),V11.PY());
	  line(V11.PX(),V11.PY(),V12.PX(),V12.PY());
	  line(V12.PX(),V12.PY(),V1.PX(),V1.PY());
	  line(B1.PX(),B1.PY(),B2.PX(),B2.PY());
	  line(B2.PX(),B2.PY(),B3.PX(),B3.PY());
	  line(B3.PX(),B3.PY(),B4.PX(),B4.PY());
	  line(B4.PX(),B4.PY(),B5.PX(),B5.PY());
	  line(B5.PX(),B5.PY(),B6.PX(),B6.PY());
	  line(B6.PX(),B6.PY(),B7.PX(),B7.PY());
	  line(B7.PX(),B7.PY(),B8.PX(),B8.PY());
	  line(B8.PX(),B8.PY(),B9.PX(),B9.PY());
	  line(B9.PX(),B9.PY(),B10.PX(),B10.PY());
	  line(B10.PX(),B10.PY(),B1.PX(),B1.PY());
	  line(F1.PX(),F1.PY(),F2.PX(),F2.PY());
	  line(F2.PX(),F2.PY(),F3.PX(),F3.PY());
	  line(F3.PX(),F3.PY(),F4.PX(),F4.PY());
	  line(F4.PX(),F4.PY(),F5.PX(),F5.PY());
	  line(F5.PX(),F5.PY(),F6.PX(),F6.PY());
	  line(F6.PX(),F6.PY(),F7.PX(),F7.PY());
	  line(F7.PX(),F7.PY(),F8.PX(),F8.PY());
	  line(F8.PX(),F8.PY(),F9.PX(),F9.PY());
	  line(F9.PX(),F9.PY(),F10.PX(),F10.PY());
	  line(F10.PX(),F10.PY(),F1.PX(),F1.PY());
		delay(40);

	  setcolor(0);
	  line(V1.PX(),V1.PY(),V2.PX(),V2.PY());
	  line(V2.PX(),V2.PY(),V3.PX(),V3.PY());
	  line(V3.PX(),V3.PY(),V4.PX(),V4.PY());
	  line(V4.PX(),V4.PY(),V5.PX(),V5.PY());
	  line(V5.PX(),V5.PY(),V6.PX(),V6.PY());
	  line(V6.PX(),V6.PY(),V7.PX(),V7.PY());
	  line(V7.PX(),V7.PY(),V8.PX(),V8.PY());
	  line(V8.PX(),V8.PY(),V9.PX(),V9.PY());
	  line(V9.PX(),V9.PY(),V10.PX(),V10.PY());
	  line(V10.PX(),V10.PY(),V11.PX(),V11.PY());
	  line(V11.PX(),V11.PY(),V12.PX(),V12.PY());
	  line(V12.PX(),V12.PY(),V1.PX(),V1.PY());
	  line(B1.PX(),B1.PY(),B2.PX(),B2.PY());
	  line(B2.PX(),B2.PY(),B3.PX(),B3.PY());
	  line(B3.PX(),B3.PY(),B4.PX(),B4.PY());
	  line(B4.PX(),B4.PY(),B5.PX(),B5.PY());
	  line(B5.PX(),B5.PY(),B6.PX(),B6.PY());
	  line(B6.PX(),B6.PY(),B7.PX(),B7.PY());
	  line(B7.PX(),B7.PY(),B8.PX(),B8.PY());
	  line(B8.PX(),B8.PY(),B9.PX(),B9.PY());
	  line(B9.PX(),B9.PY(),B10.PX(),B10.PY());
	  line(B10.PX(),B10.PY(),B1.PX(),B1.PY());
	  line(F1.PX(),F1.PY(),F2.PX(),F2.PY());
	  line(F2.PX(),F2.PY(),F3.PX(),F3.PY());
	  line(F3.PX(),F3.PY(),F4.PX(),F4.PY());
	  line(F4.PX(),F4.PY(),F5.PX(),F5.PY());
	  line(F5.PX(),F5.PY(),F6.PX(),F6.PY());
	  line(F6.PX(),F6.PY(),F7.PX(),F7.PY());
	  line(F7.PX(),F7.PY(),F8.PX(),F8.PY());
	  line(F8.PX(),F8.PY(),F9.PX(),F9.PY());
	  line(F9.PX(),F9.PY(),F10.PX(),F10.PY());
	  line(F10.PX(),F10.PY(),F1.PX(),F1.PY());

  }
}

void barrawin(int x, int y, int lx, int ly, int as)
{  int a,b;
	if(as==0) { a=31; b=8; }
	else      { a=8; b=31; }
	setfillstyle(1,7);
	bar(x,y,x+lx,y+ly);
	setcolor(a);
	line(x,y,x+lx,y);
	line(x,y,x,y+ly);
	setcolor(b);
	line(x,ly+y,lx+x,ly+y);
	line(lx+x,y,lx+x,ly+y);
}