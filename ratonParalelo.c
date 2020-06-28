/*
 ==================================================================================================================================
    Nombre      : ratonParalelo.c
    Autor       : Eduardo Mayen
    Version     : 1.0.0
    Copyright   : GNU 3.0
    Descripcion : El programa hace una simulación de un ratón que quiere llegar a su queso a traves del recorrido de un laberinto.
 ==================================================================================================================================
*/



#include <stdio.h>
#include <string.h>
#include <mpi.h>

static int posRatonX = 0;       /* Posicion del raton en el eje X */
static int posRatonY = 0;       /* Posicion del raton en el eje Y */
static int posQuesoX = 8;       /* Posicion del queso en el eje X */
static int posQuesoY = 8;       /* Posicion del queso en el eje Y */
//int tam1 = 10;            /* Indica el tamaño de la primera posicion del arreglo */
//int tam2 = 10;            /* Indica el tamaño de la segunda posicion del arreglo */
int raton = 8;           /* Es el raton y el recorrido que este va realizando */
int queso = 3;           /* Es el queso */
int pared = 1;           /* Es la pared */

/*
    Desarrollo de las funciones a utilizar 
*/


/* Esta funcion copia el contenido de el laberinto original a el laberinto de conocimiento */
void copiarLab(int labOr[10][10], int labCono[10][10])
{
    int i, j;
    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            labOr[i][j] = labCono[i][j];
        }
    }
}


/* Esta funcion crea el laberinto*/
void crearLab(int lab[10][10])
{
    int i, j;
    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            if(i == posRatonX && j == posRatonY)
            {
                lab[i][j] = raton;
            }
            else if (i == posQuesoX && j == posQuesoY)
            {
                lab[i][j] = queso;
            }
            else if(i == 0 && j == 1)
            {
                lab[i][j] = pared;
            }
            else if(i == 3 && j == 1)
            {
                lab[i][j] = pared;
            }
            else if(i == 4 && j == 1)
            {
                lab[i][j] = pared;
            }
            else if(i == 2 && j == 2)
            {
                lab[i][j] = pared;
            }
            else if(i == 0 && j == 4)
            {
                lab[i][j] = pared;
            }
            else if(i == 6 && j == 4)
            {
                lab[i][j] = pared;
            }
            else if(i == 0 && j == 7)
            {
                lab[i][j] = pared;
            }
            else if(i == 4 && j == 9)
            {
                lab[i][j] = pared;
            }
            else if(i == 5 && j == 5)
            {
                lab[i][j] = pared;
            }
            else
            {
                lab[i][j] = 0;
            }
            
        }
    }
}

/* Esta funcion crea y dibuja(imprime) el laberinto*/
void crearDibujarLab(int lab[10][10])
{
    int i, j;
    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            if(i == posRatonX && j == posRatonY)
            {
                lab[i][j] = raton;
            }
            else if (i == posQuesoX && j == posQuesoY)
            {
                lab[i][j] = queso;
            }
            else if(i == 0 && j == 1)
            {
                lab[i][j] = pared;
            }
            else if(i == 3 && j == 1)
            {
                lab[i][j] = pared;
            }
            else if(i == 4 && j == 1)
            {
                lab[i][j] = pared;
            }
            else if(i == 2 && j == 2)
            {
                lab[i][j] = pared;
            }
            else if(i == 0 && j == 4)
            {
                lab[i][j] = pared;
            }
            else if(i == 6 && j == 4)
            {
                lab[i][j] = pared;
            }
            else if(i == 0 && j == 7)
            {
                lab[i][j] = pared;
            }
            else if(i == 4 && j == 9)
            {
                lab[i][j] = pared;
            }
            else if(i == 5 && j == 5)
            {
                lab[i][j] = pared;
            }
            else
            {
                lab[i][j] = 0;
            }
            printf("%d\t", lab[i][j]);
        }
        printf("\n");
    }
}


/* Funcion que dibuja(imprime) el laberinto*/
void dibujarLab(int lab[10][10])
{
    int i, j;
    printf("\n");
    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            printf("%d\t", lab[i][j]);
        }
        printf("\n");
    }
}


/* Funcion que realiza el recorrido general del laberinto */
void recorrerLaberinto(int lab[10][10], int labCono[10][10], int exito, int i, int izquierda, int derecha, int arriba, int abajo, int posX, int posY, int numProceso)
{
    /* asignacion de valores actuales a variables locales */
    posX = posRatonX;
    posY = posRatonY;
    i = 0;
    exito = 0;
    int arr, abj, der, izq;
    arr = arriba;
    abj = abajo;
    der = derecha;
    izq = izquierda;

    /* EL while se utiliza para saber cundo el raton ha llegado a su objetivo*/
    while(exito == 0)
    {
        /* Este if se utiliza para saber si el movimiento del raton sera hacia abajo */
        if (abj == 1 && arr == 0 && der == 0 && izq == 0)
        {
            if((posX+1 >= 10) ||  (lab[posX+1][posY] == pared) || (lab[posX+1][posY] == raton))
            {
                /* Este if evalua si el raton puede seguir bajando */
                if((posY-1 < 0) || (lab[posX][posY-1] == pared) || (lab[posX][posY-1] == raton))
                {
                    if((posY+1 >= 10) || (lab[posX][posY+1] == pared) || (lab[posX][posY+1] == raton))
                    {
                        /* Se ha llegado a la orilla del laberinto, hay que bloquear el punto */
                        printf("Ya no hay mas camino, hay que bloquear \n");
                        lab[posX][posY] = raton;
                        dibujarLab(lab);
                        lab[posX][posY] = pared;
                        dibujarLab(lab);
                        labCono[posX][posY] = pared;
                        printf("\n Empieza de nuevo \n");
                        copiarLab(lab, labCono);
                        posX = posRatonX;
                        posY = posRatonY;
                        abj = 1;
                        arr = 0;
                        der = 0;
                        izq = 0;
                    }
                    else
                    {
                        /* El raton giro a la derecha */
                        der = 1;
                        abj = 0;
                    }
                }
                else
                {
                    /* El raton giro a la izquierda */
                    izq = 1;
                    abj = 0;
                }                
            }
            else
            {
                /* El raton puede seguir bajando */
                posX++;
                lab[posX][posY] = raton;
            }    
                  
        }


        /* Este if se utiliza para saber si el movimiento del raton sera hacia arriba */
        else if(arr = 1 && abj == 0 && der == 0 && izq == 0)
        {
            if((posX-1 < 0) || (lab[posX-1][posY] == pared) || (lab[posX-1][posY] == raton))
            {
                /* Este if evalua si el raton puede seguir subiendo */
                if((posY+1 >= 10) || (lab[posX][posY+1] == pared) || (lab[posX][posY+1] == raton))
                {
                    if((posY-1 < 0) || (lab[posX][posY-1] == pared) || (lab[posX][posY-1] == raton))
                    {
                        /* Se ha llegado a la orilla del laberinto, hay que bloquear el punto */
                        printf("Ya no hay mas camino, hay que bloquear \n");
                        lab[posX][posY] = raton;
                        dibujarLab(lab);
                        lab[posX][posY] = pared;
                        dibujarLab(lab);
                        labCono[posX][posY] = pared;
                        printf("\n Empieza de nuevo \n");
                        copiarLab(lab, labCono);
                        posX = posRatonX;
                        posY = posRatonY;
                        abj = 1;
                        arr = 0;
                        der = 0;
                        izq = 0;
                    }
                    else
                    {
                        /* El raton giro a la izquierda */
                        izq = 1;
                        arr = 0;
                    }
                }
                else
                {
                    /* El raton giro a la derecha */
                    der = 1;
                    arr = 0;
                }                
            }
            else
            {
                /* El raton puede seguir subiendo */
                posX--;
                lab[posX][posY] = raton;
            }   
        }


        /* Este if se utiliza para saber si el movimiento del raton sera hacia la derecha */
        else if(der == 1 && abj == 0 && arr == 0 && izq == 0)
        {
            if((posY+1 >= 10) || (lab[posX][posY+1] == pared) || (lab[posX][posY+1] == raton))
            {
                /* Este if evalua si el raton puede seguir yendo a la derecha */
                if((posX+1 >= 10) || (lab[posX+1][posY] == pared) || (lab[posX+1][posY] == raton))
                {
                    if((posX-1 < 0) || (lab[posX-1][posY] == pared) || (lab[posX-1][posY] == raton))
                    {
                        /* Se ha llegado a la orilla del laberinto, hay que bloquear el punto */
                        printf("Ya no hay mas camino, hay que bloquear \n");
                        lab[posX][posY] = raton;
                        dibujarLab(lab);
                        lab[posX][posY] = pared;
                        dibujarLab(lab);
                        labCono[posX][posY] = pared;
                        printf("\n Empieza de nuevo \n");
                        copiarLab(lab, labCono);
                        posX = posRatonX;
                        posY = posRatonY;
                        abj = 1;
                        arr = 0;
                        der = 0;
                        izq = 0;
                    }
                    else
                    {
                        /* El raton giro hacia arriba */
                        arr = 1;
                        der = 0;
                    }
                }
                else
                {
                    /* El raton giro hacia abajo */
                    abj = 1;
                    der = 0;
                }
            }
            else
            {
                /* El raton puede seguir hacia la derecha */
                posY++;
                lab[posX][posY] = raton;
            }
        }


        /* Este if se utiliza para saber si el movimiento del raton sera hacia la izquierda */
        else if(izq == 1 && arr == 0 && abj == 0 && der == 0)
        {
            if((posY-1 < 0) || (lab[posX][posY-1] == pared) || (lab[posX][posY-1] == raton))
            {
                /* Este if evalua si el raton puede seguir yendo a la izquierda */
                if((posX-1 < 0) || (lab[posX-1][posY] == pared) || (lab[posX-1][posY] == raton))
                {
                    if((posX+1 >= 10) || (lab[posX+1][posY] == pared) || (lab[posX+1][posY] == raton))
                    {
                        /* Se ha llegado a la orilla del laberinto, hay que bloquear el punto */
                        printf("Ya no hay mas camino, hay que bloquear \n");
                        lab[posX][posY] = raton;
                        dibujarLab(lab);
                        lab[posX][posY] = pared;
                        dibujarLab(lab);
                        labCono[posX][posY] = pared;
                        printf("\n Empieza de nuevo \n");
                        copiarLab(lab, labCono);
                        posX = posRatonX;
                        posY = posRatonY;
                        abj = 1;
                        arr = 0;
                        der = 0;
                        izq = 0;
                    }
                    else
                    {
                        /* El raton giro hacia abajo */
                        abj = 1;
                        izq = 0;
                    }
                }
                else
                {
                    /* El raton giro hacia arriba */
                    arr = 1;
                    izq = 0;
                }
            }
            else
            {
                /* El raton puede seguir hacia la izquierda */
                posY--;
                lab[posX][posY] = raton;
            }
        }
        dibujarLab(lab);

        /* Este if valida si el raton ha llegado a su objetivo */
        if (posX == posQuesoX && posY == posQuesoY)
        {
            exito = 1;
        }
        else
        {
            exito = 0;
        }
        
        printf("En el intento numero %d el raton del proceso %d se encuentra en la cordenada x = %d y en la cordenada y = %d\n\n\n", i, numProceso, posX, posY);
        
        /* Contador utilizado para saber el numero de intentos en el que el raton logro llegar a su objetivo */ 
        i++;
    }
    printf("\n El raton ha llegado al queso en el intento numero: %d ", i);
    printf("\nEn el proceso numero: ", numProceso);
}


int main(void)
{
    int posX, posY, i, exito;
    int rank;
    int size;
    posX = 0;
    posY = 0;
    i = 0;
    exito = 0;

    /* Inicializa la estructura de comunicacion de MPI entre los procesos */
    MPI_Init(NULL, NULL);
    /* Determina el numero de procesos que estan actualmente asociados a este */
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    /* Determina el rango del proceso que lo llama dentro del comunicador seleccionado */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0)
    {
        int lab[10][10];
        int labCono[10][10];

        crearDibujarLab(lab);
        crearLab(labCono);

        /* Llamado a funcion que baja */
        printf("\n\n\n\n Primer movimiento hacia abajo \n\n\n\n");
        posX = posRatonX;
        posY = posRatonY;
        recorrerLaberinto(lab, labCono, exito, i, 0, 0, 0, 1, posX, posY, rank);
    }
    else if (rank == 1)
    {
        int lab1[10][10];
        int labCono1[10][10];

        crearDibujarLab(lab1);
        crearLab(labCono1);

        /* Llamado a funcion que sube */
        printf("\n\n\n\n Primer movimiento hacia arriba \n\n\n\n");
        posX = posRatonX;
        posY = posRatonY;
        recorrerLaberinto(lab1, labCono1, exito, i, 1, 0, 0, 0, posX, posY, rank);
    }
    else if (rank == 2)
    {
        int lab2[10][10];
        int labCono2[10][10];

        crearDibujarLab(lab2);
        crearLab(labCono2);

        /* Llamado a funcion que va a la derecha */
        printf("\n\n\n\n Primer movimiento hacia la derecha \n\n\n\n");
        posX = posRatonX;
        posY = posRatonY;
        recorrerLaberinto(lab2, labCono2, exito, i, 0, 1, 0, 0, posX, posY, rank);
    }
    else
    {
        int lab4[10][10];
        int labCono4[10][10];

        crearDibujarLab(lab4);
        crearLab(labCono4);

        /* Llamado a funcion que va a la izquierda */
        printf("\n\n\n\n Primer movimiento hacia la izquierda \n\n\n\n");
        posX = posRatonX;
        posY = posRatonY;
        recorrerLaberinto(lab4, labCono4, exito, i, 0, 0, 1, 0, posX, posY, rank);
    }

    /* Finaliza la comunicacion paralela entre los procesos */
    MPI_Finalize();
    return 0;
}


