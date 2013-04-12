/* Grupo: Camilo Candia Rubinstein
 *        Madeleine Opazo Cabargas
 *        Maximiliano Meza 
 * 
 * En el programa se asumió que las posibles secciones asociadas a la asignatura de ingeniería de software son las 30411.Esto
 * dio como resultado docente_id 186,183,123,336.
 * 
 * Se uso la librería libpq-dev y el programa fue compilado en gcc.
 * El comando es: gcc -lm -o Tarea03 Tarea03Final.c -Wall -I/usr/include/postgresql  -lpq
 * /usr/include/postgreslq es el path al archivo de libpq-fe.h
 * 
 * 
 * Bibliografía : PostgreSQL Programmer’s Guide The PostgreSQL Development Team
 * 
 * *************************************************************************************************************************/
#include<stdio.h>
#include<libpq-fe.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
void imprimir(PGresult *resultado,PGresult *resultado_docente) //Esta función no corre en el programa.
{//Fue usada para verificar que los datos eran recibidos desde la base de datos,también fue utilizada para corregir las consultas realizadas a la misma.
	    int tuplas_docente,tuplas,campos,i,j;
	    tuplas=PQntuples(resultado);
		tuplas_docente=PQntuples(resultado_docente);
		campos=PQnfields(resultado);
		printf("Docentes que imparten ingenieria de software\n");
		for(i=0;i<tuplas_docente;i++)
		{
			printf(" %s\n",PQgetvalue(resultado_docente,i,0));
		}
		printf("n°|curso_id|docente_id|nota\n");
		for(i=0;i<tuplas;i++)
		{
			printf("%d ",i);
			for(j=0;j<campos;j++)
			{
				printf("     %s",PQgetvalue(resultado,i,j));
			}
			printf("\n");
		}
}
void promedio_desviacion(PGresult *resultado,PGresult *resultado_docente)
{
	int tuplas_docente,tuplas,campos,i,j,cont; //Filas de docentes, filas , columnas, y contador
	float sumap,sumav; //Suma para promedio, suma para varianza
	
	    tuplas=PQntuples(resultado); //retorna cantidada de filas
		tuplas_docente=PQntuples(resultado_docente);
		campos=PQnfields(resultado); //retorna cantidad de columnas
		
		for(i=0;i<tuplas_docente;i++)
		{      
			cont=0;
			sumap=0;
			sumav=0;
			const char* str=PQgetvalue(resultado_docente,i,0); //Guardamos el id_docente
			for(j=0;j<tuplas;j++)
			{
				if(!strncmp(str,PQgetvalue(resultado,j,1),3)) //Comparamos los id de docentes si son iguales...
				{
					float nota=atof(PQgetvalue(resultado,j,2)); //Guardamos las notas de la respectiva docente_id
					sumap=sumap+nota;  //Suma promedio.
					sumav=sumav+(nota*nota); //Suma para desviación.
				    cont++; //Contador de notas.
				}
			}
			float x=sumap/cont; //promedio
			float varianza=(sumav-cont*(x*x))/cont;
			printf("-----------------------------------------------------------------\n");
			printf("Docente: %s promedio: %f \n",PQgetvalue(resultado_docente,i,0),x);
			printf("Varianza: %f Desviacion: %f\n",varianza,sqrt(varianza));
			printf("-----------------------------------------------------------------\n");
		}				
}

int main()
{
	PGconn *conexion; //Conexion a la base de datos
	PGresult *resultado,*resultado_docente; //Variable resultado guardara el retorno de la variable consulta 
	//La variable resultado_docente, guardara los docentes que impartieron ingeniería de software.
    
    const char *consulta="select c.curso_id,c.docente_id,a.nota from cursos as c join asignaturas_cursadas as a on (c.curso_id=a.curso_id and seccion=30411)";
	const char *consulta_docente="select distinct docente_id from cursos where seccion=30411";
	//consultas de sql
	
	const char *pghost="190.100.156.5"; 
	const char *pgport="5432";
	const char *pgoptions=NULL;
	const char *pgtty=NULL;
	const char *dbname="iswdb";
	const char *login="isw";
	const char *pwd="isw";
	
	printf("Conectando a la base de datos...\n");
	conexion=PQsetdbLogin(pghost,pgport,pgoptions,pgtty,dbname,login,pwd); //Función para realizar la conexión
	if(PQstatus(conexion)==CONNECTION_BAD) // Función para verificar el estado de la conexión
	{
		printf("Error al conectar con la base de datos\n");
		printf("%s\n",PQerrorMessage(conexion));		
	}
	else
	{
		printf("Conexion establecida\n");
	}
	resultado=PQexec(conexion,consulta); // Realizamos la consulta
	resultado_docente=PQexec(conexion,consulta_docente); // Realizamos la segundoa consulta
	if((PQresultStatus(resultado)==PGRES_TUPLES_OK) && (PQresultStatus(resultado_docente)==PGRES_TUPLES_OK)) //Verifica que la consulta tenga éxito.
	{
		promedio_desviacion(resultado,resultado_docente); //Llamo a la función para calcular el promedio y la desviacion.
	}
	else
	{
		printf("Error en la consulta\n");
	}
	printf("Saliendo del programa...\n");
	PQfinish(conexion); //cerramos la conexión.
    return 0;
}
