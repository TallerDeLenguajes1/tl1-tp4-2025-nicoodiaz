#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea
{
    int TareaID;//Numerico autoincremental comenzando en 1000
    char *Descripcion;
    int Duracion; //Entre 10-100
    int Estado;

}Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo * siguiente;
}Nodo;

Nodo *CrearListaVacia();
Nodo *CrearNodo(int Id, char *descripcion, int duracion);

void InsertarNodo (Nodo **Start, Nodo *NodoAInsertar);
void CrearTarea (Nodo **Start);
int id();

Nodo *BuscarNodoId(Nodo *Start, int idBuscado);
Nodo *BuscarNodoPalabra(Nodo *Start, char *Palabra);

Nodo *QuitarNodo(Nodo **Start, int id);
Nodo *EliminarNodo(Nodo *NodoAEliminar);

void MostrarTodasTareas(Nodo **nodo);
void MostrarTareaPorID(Nodo *Start, int id);

void CambiarEstado(Nodo **Start, Nodo **Start2, int ID);

int main()
{
    //Creo el comienzo de la lista apuntando a NULL
    Nodo *Start = CrearListaVacia();
    //Creo el comienzo de la lista para las tareas realizadas
    Nodo *StartRealizadas = CrearListaVacia();

    int opciones = 0;
    //Interfaz de Menu
    do
    {
        printf("\n------Lista de Tareas-------\n");
        printf("Elige una de las siguientes opciones: \n");
        printf("1. Listar tareas\n");
        printf("2. Crear una tarea\n");
        printf("3. Cambiar estado de la tarea\n");
        printf("4. Buscar tarea por ID\n");
        printf("5. Buscar tarea por palabra clave\n");
        printf("6. Salir\n");
        scanf("%d", &opciones);
        switch (opciones)
        {
        case 1:
            int opcionTarea = 0;
            printf("Elija una opcion: \n");
            printf("1. Mostrar todas las tareas");
            printf("2. Mostrar las tareas pendientes\n");
            printf("3. Mostrar las Realizadas\n");
            if (opcionTarea == 1)
            {
                MostrarTodasTareas(&Start);
                MostrarTodasTareas(&StartRealizadas);
            }
            else if(opcionTarea == 2)
            {
                MostrarTodasTareas(&Start);
            }
            else
            {
                MostrarTodasTareas(&StartRealizadas);
            }
            break;
        case 2:
            CrearTarea(&Start);
            break;
        case 3:
            int IDTareaACambiar = 0;
            printf("Ingrese el ID de la tarea que quiere cambiar: \n");
            scanf("%d", &IDTareaACambiar);
            CambiarEstado(&Start, &StartRealizadas, IDTareaACambiar);
            break;
        case 4:
            int IDTareaSeleccionar;
            Nodo *Aux;
            Nodo *AuxRealizadas;
            printf("Ingrese el numero de de ID a buscar\n");
            scanf("%d", &IDTareaSeleccionar);
            Aux = BuscarNodoId(Start, IDTareaSeleccionar);
            AuxRealizadas = BuscarNodoId(StartRealizadas, IDTareaSeleccionar);
            if (Aux)
            {
                MostrarTareaPorID(Aux, IDTareaSeleccionar);
            }
            if (AuxRealizadas)
            {
                MostrarTareaPorID(AuxRealizadas, IDTareaSeleccionar);
            }
            if (!Aux && !AuxRealizadas)
            {
                printf("No existe esa tarea");
            }
            break;
        case 5:
            Nodo *AuxP;
            char Palabra[20];
            fflush(stdin);
            printf("A seleccionado \"Buscar tarea por palabra clave\" \n");
            printf("Porfavor ingrese la palabra :  ");
            gets(Palabra);
            fflush(stdin);
            AuxP = BuscarNodoPalabra(Start, Palabra);
            if (AuxP != NULL)
            {
                int ID = AuxP->T.TareaID;
                MostrarTareaPorID(AuxP, ID);
            }
            else
            {
                printf("No se encontró ninguna tarea con esa palabra clave.\n");
            }
            break;
        }

    } while (opciones != 6);
    

    return 0;
}
//Para poder ir incrementando el id
int id()
{
    int id = 1000;
    return id++;
}

//Para poder crear el comienzo de la lista el "Start"
Nodo *CrearListaVacia()
{
    return NULL;
}

//Para crear el nodo con los datos necesarios
Nodo *CrearNodo(int Id, char *descripcion, int duracion)
{
    //Guardo memoria para el nodo
    Nodo *Tarea = (Nodo *) malloc(sizeof(Nodo));
    //Guardo memoria dinamica y luego copio
    Tarea->T.Descripcion = (char *) malloc((strlen(descripcion) + 1) *sizeof(char));
    strcpy(Tarea->T.Descripcion, descripcion);
    //Guardo los demas datos
    Tarea->T.Duracion = duracion;
    Tarea->T.TareaID = Id;
    Tarea->T.Estado = 0;
    //Hago que el siguiente apunte a NULL
    Tarea->siguiente = NULL;

    return Tarea;
}

//Para insertar el Nodo creado al PRINCIPIO de la lista 
void InsertarNodo (Nodo **Start, Nodo *NodoAInsertar)//Start(Cabecera), Nodo(Nuevo que queremos insertar)
{
    //Aqui hago que el nuevo nodo, apunte al comienzo de la lista, seria al nodo anterior a este
    NodoAInsertar->siguiente = *Start;
    //Aqui hago que estar apunte al nuevo nodo
    *Start = NodoAInsertar;
}

//Funcion para pedir los datos necesarios y llamar la funcion para crear la tarea
void CrearTarea(Nodo **Start)
{
    //Datos para pasarle a la funcion para crear el NODO
    int seguirCreando = 0;
    char descripcion[200];
    int duracion;

    do
    {
        fflush(stdin);
        printf("Ingrese los datos para poder crear la tarea: \n");
        printf("Descripcion de la tarea: \n");
        gets(descripcion);
        fflush(stdin);
        printf("Ingrese la duracion (Entre 10 y 100): \n");
        scanf("%d", &duracion);
        Nodo *TareaACrear = CrearNodo(id(), descripcion, duracion);
        InsertarNodo(Start, TareaACrear);
        printf("Quiere agregar otra tarea?: \n1.Si\n2.No");
        scanf("%d", &seguirCreando);
    } while (seguirCreando == 1);
}

//Para poder buscar un nodo mediante un ID
Nodo *BuscarNodoId(Nodo *Start, int idBuscado)
{
    Nodo *Aux = Start; //Guardo la cabecera en un auxiliar
    while (Aux && Aux->T.TareaID != idBuscado)//Mientras q Aux no sea NULL y no sea el IDBuscado
    {
        Aux = Aux->siguiente; //Si no es el id q busco y aux no es null(El final) le asigno el q sigue
    }
    return Aux; //Si se encuentra, se retorna el nodo
}

//Para poder buscar mediante una palabra ingresada
Nodo *BuscarNodoPalabra(Nodo *Start, char *Palabra)
{
    Nodo *Aux = Start; 
    while (Aux && strstr(Aux->T.Descripcion, Palabra) == NULL) //Mientras q Aux no sea NULL y no haya coincidencia con la palabra buscada 
    {
        Aux = Aux->siguiente;//Si no hay, apunto al siguiente y sigo
    }
    return Aux;
}

//Funcion para poder quitar el nodo de la lista mediante el ID
Nodo *QuitarNodo(Nodo **Start, int id)
{
    Nodo **Aux = Start;//Almaceno la direccion de memoria del Start(Comienzo de la lista)
    while (*Aux != NULL && (*Aux)->T.TareaID != id)//Si el Aux no es NULL y no es el ID q busco, apunto al siguiente
    {
        Aux = &(*Aux)->siguiente;
    }
    if (*Aux) //Si encuentro el NODO por el ID
    {
        Nodo *temp = *Aux; //Guardo el nodo a eliminar en un temporal
        *Aux = (*Aux)->siguiente; //Que el aux apunte al siguiente
        temp->siguiente = NULL; // Apunte a NULL, para sacarlo de la lista
        return temp;
    }
    return NULL;//Si no se encuentra se retorna NULL y no cambia nada
}

//Liberar la memoria para eliminar el nodo
Nodo *EliminarNodo(Nodo *NodoAEliminar)
{
    free(NodoAEliminar);
}

//Para mostrar todas las tareas creadas
void MostrarTodasTareas(Nodo **Start)
{
    Nodo *Aux = *Start; //Le asigno el contenido de Start a Aux
    while (Aux)
    {
        printf("\n");
        printf("Id de la tarea: %d \n", Aux->T.TareaID);
        printf("Descripcion: \n ");
        puts(Aux->T.Descripcion);
        printf("Duracion de la tarea: %d \n", Aux->T.Duracion);
        printf("Estado de la tarea: ");
        if (Aux->T.Estado == 1)
        {
            printf("Realizada");
        }
        else
        {
            printf("Pendiente");
        }
        printf("\n----Siguiente tarea----\n");
        Aux = Aux->siguiente;
    }
    printf("Se acabaron las tareas\n");
}


void MostrarTareaPorID(Nodo *Start, int id)
{
    Nodo *Aux = BuscarNodoId(Start, id);
    printf("\n");
    printf("ID de la Tarea: %d\n", Aux->T.TareaID);
    printf("Descripcion: %s\n", Aux->T.Descripcion);
    printf("Duracion de la Tarea: %d\n", Aux->T.Duracion);
    printf("Estado de la tarea: ");
    if (Aux->T.Estado == 1)
    {
        printf("Realizada");
    }
    else
    {
        printf("Pendiente");
    }
}
//Funcion para cambiar el estado de las tareas
void CambiarEstado(Nodo **Start, Nodo **Start2, int ID)
//Star es donde buscamos y Star2 es la lista donde la queremos mover
{
    Nodo *NodoAMover = QuitarNodo(Start, ID);
    if(NodoAMover)
    {
        InsertarNodo(Start2, NodoAMover);
    }
    else
    {
        printf("La tarea con el id %d, no existe", ID);
    }
}