#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
int Tablero[8][8];
int posiciones[2][100]; //Guarda las posiciones de los movimientos del caballo 0 para las filas 1 para las columnas.
void limpiar() //Limpia el tablero y el array
{
	int i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			Tablero[i][j]=0;
		}
	}
	for(i=0;i<100;i++)
	{
		posiciones[0][i]=0;
		posiciones[1][i]=0;
	}
	
}
void imprimir() //imprime la matriz o tablero
{
	int i,j;
	for(i=0;i<8;i++)
	{
		cout<<"\n";
		for(j=0;j<8;j++)
		{
			if((Tablero[i][j]<10) && (Tablero[i][j]>0))
			{
				cout<<" "<<Tablero[i][j]<<" ";
			}
			else
			{
				cout<<" "<<Tablero[i][j];
			}
		}
	}
	cout<<"\n";
}
void movimiento_caballo(int fila_inicial,int colum_inicial,int *cont,int *movimientos,int fantes,int cantes)
{
	if(*movimientos<60) //solo acepta 60 movimientos, igual a la cantidad de ceros en el tablero.
	{
	if((colum_inicial>=0 && colum_inicial<8)&&(fila_inicial>=0 && fila_inicial<8)) //filtra las posiciones del tablero.
	{
		if((Tablero[fila_inicial][colum_inicial]!=-1)&&(!Tablero[fila_inicial][colum_inicial])) 
		{//Solo acepta movimientos que sena iguales a cero y distintas de las posiciones de los peones.
			    Tablero[fila_inicial][colum_inicial]=*cont;
			    posiciones[0][*cont]=fila_inicial; //guardo las respectivas posiciones
			    posiciones[1][*cont]=colum_inicial;
				*cont=*cont+1; //sumo uno al contador
				*movimientos=*movimientos+1; //sumo uno al contador de ceros en el tablero
				movimiento_caballo(fila_inicial+2,colum_inicial+1,cont,movimientos,fila_inicial,colum_inicial);
				movimiento_caballo(fila_inicial+2,colum_inicial-1,cont,movimientos,fila_inicial,colum_inicial);
				movimiento_caballo(fila_inicial-2,colum_inicial+1,cont,movimientos,fila_inicial,colum_inicial);
				movimiento_caballo(fila_inicial-2,colum_inicial-1,cont,movimientos,fila_inicial,colum_inicial);
				movimiento_caballo(fila_inicial+1,colum_inicial+2,cont,movimientos,fila_inicial,colum_inicial);
				movimiento_caballo(fila_inicial-1,colum_inicial+2,cont,movimientos,fila_inicial,colum_inicial);
				movimiento_caballo(fila_inicial+1,colum_inicial-2,cont,movimientos,fila_inicial,colum_inicial);
				movimiento_caballo(fila_inicial-1,colum_inicial-2,cont,movimientos,fila_inicial,colum_inicial);
			
		}
		else
		{
			//Si el movimiento es en una posicion ya marcada...
			if(Tablero[fantes][cantes]<(*cont-1)) // verifica que el movimiento anterior sea menor que el contador -1
			{ //Sabiendo que por la recursividad, si en algun momento no encuentra movimiento va a comenzar a recorrer las funciones con movimientos mas pequeños (cont).
				cout<<"-----------------------------------------"<<endl;
				cout<<"Movimiento sobre una posicion anterior: "<<endl;
				cout<<"-----------------------------------------"<<endl;
				cout<<"movimiento desde la posicion : "<<*cont-1<<endl;
				cout<<"movimiento "<<*cont-1<<" ubicada en la fila: "<<posiciones[0][*cont-1]<<" y la columna: "<<posiciones[1][*cont-1]<<endl;
				cout<<"movimiento hacia la posicion: "<<Tablero[fantes][cantes]<<endl;
				cout<<"movimiento "<<Tablero[fantes][cantes]<<" ubicado en la fila: "<<fantes<<endl<<" y la columna: "<<cantes<<endl;
	            imprimir();
				cout<<"-----------------------------------------"<<endl;
				cout<<"Resultado: "<<endl;
				cout<<"movimiento numero: "<<*cont<<endl;
	            cout<<"ubicado en fila: "<<fantes<<" y columna: "<<cantes<<endl;
				Tablero[fantes][cantes]=*cont;
				posiciones[0][*cont]=fantes;
				posiciones[1][*cont]=cantes;
				*cont=*cont+1;
				imprimir();
				movimiento_caballo(fantes+2,cantes+1,cont,movimientos,fantes,cantes);
				movimiento_caballo(fantes+2,cantes-1,cont,movimientos,fantes,cantes);
				movimiento_caballo(fantes-2,cantes+1,cont,movimientos,fantes,cantes);
				movimiento_caballo(fantes-2,cantes-1,cont,movimientos,fantes,cantes);
				movimiento_caballo(fantes+1,cantes+2,cont,movimientos,fantes,cantes);
				movimiento_caballo(fantes-1,cantes+2,cont,movimientos,fantes,cantes);
				movimiento_caballo(fantes+1,cantes-2,cont,movimientos,fantes,cantes);
				movimiento_caballo(fantes-1,cantes-2,cont,movimientos,fantes,cantes);
			}	
		}
	}
	}			
}

int main()
{
	limpiar();
	int ultimo=0; //contador de posiciones utilizadas en el tablero, osea posiciones != 0
	int contador=1; // contador de movimientos en el tablero
	Tablero[2][2]=-1; //posiciones reservadas para los peones
	Tablero[2][5]=-1;
	Tablero[5][5]=-1;
	Tablero[5][2]=-1;
	cout<<"\nTablero inicial:\n"<<endl;
	imprimir();
	movimiento_caballo(7,0,&contador,&ultimo,0,0);
	cout<<"\n\nresultado final:\n"<<endl;
	imprimir();
	
	return 0;
}
