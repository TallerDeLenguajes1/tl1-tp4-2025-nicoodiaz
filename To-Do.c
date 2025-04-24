#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct
{
    int TareaID;//Numerico autoincremental comenzando en 1000
    char *Descripcion;
    int Duracion; //Entre 10-100

}typedef Tarea;

struct 
{
    Tarea T;
    TNodo *Siguiente;
}typedef TNodo;

TNodo *CrearListaVacia();
TNodo *CrearNodo(int Id, char *descripcion, int duracion);

int main()
{
    //Creo el comienzo de la lista apuntando a NULL
    TNodo *Start = CrearListaVacia();

    return 0;
}

TNodo *CrearListaVacia()
{
    return NULL;
}

TNodo *CrearNodo(int Id, char *descripcion, int duracion)
{
    //Guardo memoria para el nodo
    TNodo *Tarea = (TNodo *) malloc(sizeof(TNodo));
    //Guardo memoria dinamica y luego copio
    Tarea->T.Descripcion = (char *) malloc((strlen(descripcion) + 1) *sizeof(char));
    strcpy(Tarea->T.Descripcion, descripcion);
    //Guardo los demas datos
    Tarea->T.Duracion = duracion;
    Tarea->T.TareaID = Id;
    //Hago que el siguiente apunte a NULL
    Tarea->Siguiente = NULL;

    return Tarea;
}