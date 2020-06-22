#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AR_CLIENTS "Clients.dat"
#define AR_ACTIVES "ActiveClients.dat"
#define AR_INACTIVES"InnactiveClients.dat"

#define DIM 50

typedef struct
{
    char calle[25];
    int numero;
    int piso;
    char dpto[4];
} dir;

typedef struct
{
    int idCliente;
    char nombre[30];
    long dni;
    char apellido[30];
    long nroTelefono;
    int alta;
    dir direccion;

} cliente;

void mainMenu();
void menuClientes();
int generateID(int id);
cliente addCliente();
void guardarClienteEnArchivo(cliente c);
void printCliente(cliente c);
void intercambiaClientes(cliente *a, cliente *b);
int clientesActivos(cliente activos[], int dimension);
void ordPorSelApellido(cliente c[], int v);


int main()
{
    int option, cantidad;
    char continuar;

    cliente clientes[100];
    char apellido[30];

    mainMenu();
    option = getch();

    system("cls");


    switch (option)
    {
    case '1':
        menuClientes();
        printf("\n\n");
        option = getch();

        switch(option)
        {
        case 'a':       //agregar cliente
            do
            {
                system("cls");
                addCliente();
                printf("\nDesea cargar otro cliente? s/n\n");
                fflush(stdin);
                scanf("%c", &continuar);
            }
            while (continuar == 's');

        case 'b':  //baja de cliente
            do
            {
                system("cls");
                bajaCliente();
                printf("\nDesea dar de baja otro cliente? s/n\n");
                fflush(stdin);
                scanf("%c", &continuar);
            }
            while (continuar == 's');

        case 'd': /// LISTAR CLIENTES ACTIVOS
            do
            {
                system("cls");
                printf("\t[ 1 ] - Mostrar clientes ordenados por DNI");
                printf("\n\n\t[ 2 ] - Mostrar todos los clientes ordenados por Apellido");
                printf("\n\n\t[ 3 ] - Buscar un cliente en particular y mostrarlo");

                option = getch();

                switch (option)
                {
                case '1': /// MOSTRAR CLIENTES ORDENADOS POR DNI.

                    cantidad = clientesActivos(clientes, DIM);
                    ordenarClientePorDni(clientes, cantidad);
                    muestraClientes(clientes, cantidad);

                    break;
                }

                case '2':
                    cantidad = clientesActivos(clientes, DIM);
                    ordPorSelApellido(clientes, cantidad);
                    muestraClientes(clientes, cantidad);
            }
            while (continuar == 's');
            break;
        }



    }
    return 0;
}


void mainMenu()
{
    printf("\n\t|-------------------------------|");
    printf("\n\t|\tMENU PRINCIPAL  \t|");
    printf("\n\t|-------------------------------|");
    printf("\n\t|\t[ 1 ] - CLIENTES.\t|");
    printf("\n\t|-------------------------------|");
    printf("\n\t|\t[ 2 ] - CONSUMO.\t|");
    printf("\n\t|-------------------------------|\n");
}

void menuClientes()
{
    printf("\n\n\t[ a ] - Alta.");
    printf("\n\n\t[ b ] - Baja.");
    printf("\n\n\t[ c ] - Modificacion.");
    printf("\n\n\t[ d ] - Lista de clientes activos.");
    printf("\n\n\t[ e ] - Listas de clientes inactivos.");
}

int generateID(int id)
{
    int idCliente = id + 1;
}

cliente addCliente()
{
    cliente c;
    int id = 0000;

    printf("**** ALTA CLIENTE ****");
    printf("\n\n");
    printf("*ID CLIENTE: ");

    c.idCliente = generateID(id);

    printf("\n\n*NOMBRE: ");
    fflush(stdin);
    scanf("%s", &c.nombre);

    printf("\n\n*APELLIDO: ");;
    fflush(stdin);
    scanf("%s", &c.apellido);

    printf("\n\n*DNI: ");
    scanf("%l", &c.dni);

    printf("\n\n*DOMICILIO: ");
    printf("\n**CALLE: ");
    fflush(stdin);
    scanf("%s", &c.direccion.calle);

    printf("\n**NRO: ");
    fflush(stdin);
    scanf("%d", &c.direccion.numero);

    printf("\n\nNUMERO DE T%cLEFONO: ", 144);
    fflush(stdin);
    scanf("%l", &c.nroTelefono);

    c.alta = 1;

    guardarClienteEnArchivo(c);

    id ++;

    return c;
}

void guardarClienteEnArchivo(cliente c)
{
    FILE *archClient = fopen(AR_CLIENTS,"ab");
    if(archClient != NULL)
    {
        fwrite(&c,sizeof(cliente),1,archClient);
        fclose(archClient);
    }
}
/*
void cargaArchivoClientes(cliente clientes[])
{

    char continuar = 's';
    cliente c;	    			/// crea un cliente como variable

    while(continuar == 's') 				/// mientras quiera seguir ingresando clientes
    {
        system("cls");
        printf("\n Carga de Clientes \n");
        c = addCliente();			/// reutiliza la función de cargar cliente

        printf("\nDesea continuar con la carga? s/n \n");
        fflush(stdin);
        scanf("%c", &continuar);
    }
}*/

cliente buscarClientePorApellido(char apellido[]) 	/// recibe como parámetro el apellido a buscar
{
    cliente c;
    int flag=0;

    FILE *archClient = fopen(AR_CLIENTS,"rb");	/// abre el archivo en modo binario para operaciones de lectura

    if(archClient) 					/// verifica si abrió sin errores.
    {
        while( flag == 0 && fread(&c, sizeof(cliente), 1, archClient) > 0)
        {
            if(strcmpi(c.apellido, apellido) == 0)
            {
                flag=1;
            }
        }
        fclose(archClient);
    }

    if(flag==0)
    {
        c.idCliente = -1;
    }

    return c;
}

void printCliente(cliente c)
{
    printf("\n  -----------------------------------------------------------------");
    printf("\n  ID: %d", c.idCliente);
    printf("\n  NOMBRE: %s", c.nombre);
    printf("\n  APELLIDO: %s", c.apellido);
    printf("\n  D.N.I.: %d", c.dni);
    printf("\n  DOMICILIO");
    printf("\n  -- CALLE: %s", c.direccion.calle);
    printf("\n  TEL%cFONO %l", 163, c.nroTelefono);
    printf("\n  -----------------------------------------------------------------");
}

void bajaCliente()
{
    cliente aux;
    char apellido[20];
    char continuar;

    printf("\n\tIngrese el apellido a buscar: ");
    fflush(stdin);
    scanf("%s", &apellido);

    aux = buscarClientePorApellido(apellido);

    if (aux.idCliente != -1)
    {
        printf("\nEl cliente existe en el archivo\n");
        printCliente(aux);
        printf("\nDesea dar de baja al cliente? s/n \n");
        fflush(stdin);
        scanf("%c", &continuar);
    }
    else
    {
        printf("\nERROR: El cliente no existe en el archivo\n");
    }



    if (continuar == 's')
    {
        aux.alta = 0;
    }
    guardarClienteEnArchivo(aux);
}

int clientesActivos(cliente activos[], int dimension)
{
    cliente cl;
    int i=0;
    FILE *archClient = fopen(AR_CLIENTS, "rb");
    if(archClient)
    {
        while(fread(&cl, sizeof(cliente), 1, archClient) > 0)
        {
            if(cl.alta==1)
            {
                cl = activos[i];
                i++;
            }
        }
        fclose(archClient);
    }
    return i;
}

int buscaPosMenorDni(cliente c[], int v, int inicio)
{
    int posMenor = inicio;
    int i = inicio + 1;
    while(i<v)
    {
        if(c[i].dni < c[posMenor].dni)
        {
            posMenor=i;
        }
        i++;
    }
    return posMenor;
}

void intercambiaClientes(cliente *a, cliente *b)
{
    cliente aux;
    aux=*a;
    *a=*b;
    *b=aux;
}

void ordenarClientePorDni(cliente c[], int v)
{
    int posMenor;
    int i=0;

    while(i<v-1)
    {
        posMenor=buscaPosMenorDni(c,v,i);
        intercambiaClientes(&c[i],&c[posMenor]);
        i++;
    }
}

void muestraClientes(cliente c[], int v)
{
    printf("\n\tListado de Clientes");
    for(int i=0; i<v; i++)
    {
        printCliente(c[i]);
    }
    printf("\n");
}

int buscaPosMenorApellido(cliente c[], int v, int inicio)
{
    int posMenor = inicio;
    int i = inicio + 1;
    while(i<v){
        if(strcmp(c[i].apellido,c[posMenor].apellido)<0){
            posMenor=i;
        }
        i++;
    }
    return posMenor;
}


void ordPorSelApellido(cliente c[], int v)
{
    int posMenor;
    int i=0;

    while(i<v-1)
    {
        posMenor=buscaPosMenorApellido(c,v,i);
        intercambiaClientes(&c[i],&c[posMenor]);
        i++;
    }
}






