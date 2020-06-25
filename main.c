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
void menuAddCliente();
void menuListaClientes();
int generateID();
cliente addCliente();
void bajaCliente();
int verificaCliente (int dni);
void guardarClienteEnArchivo(cliente c);
cliente buscarClientePorApellido(char apellido[]);
void printCliente(cliente c);
void intercambiaClientes(cliente *a, cliente *b);
int clientesActivos(cliente activos[], int dimension);
void ordPorSelApellido(cliente c[], int v);


int main()
{
    int option, cantidad;
    char continuar;

    cliente clientes[100];
    cliente clienteAux;
    char apellido[30];

    mainMenu();
    printf("\n\n\tSELECCIONE UNA OPCION: ");
    option = getch();
    printf("\n\n");
    system("cls");


    switch (option)
    {
    case '1':
        menuClientes();
        printf("\n\n\tSELECCIONE UNA OPCION: ");
        option = getch();

        switch(option)
        {
        case 'a':  ///// ALTA DE CLIENTE ///////
            do
            {
                system("cls");
                menuAddCliente();
                fflush(stdin);
                option = getch();

                switch(option)
                {
                case '1':
                    system("cls");
                    addCliente();
                    printf("\nDesea cargar otro cliente? s/n\n");
                    fflush(stdin);
                    scanf("%c", &continuar);
                }

            default:
                printf("\n\t|---------------------------------|");
                printf("\n\t|  *** ERROR: OPCION INVALIDA *** |");
                printf("\n\t|---------------------------------|\n");
                system("pause");
                option = 'S';
                mainMenu();
            }
            while (continuar == 's');



        case 'b':  ///// BAJA DE CLIENTE /////
            do
            {
                system("cls");
                bajaCliente();
                printf("\nDesea dar de baja otro cliente? s/n\n");
                fflush(stdin);
                scanf("%c", &continuar);
            }
            while (continuar == 's');

            break;

        case 'c': //// MODIFICACIÓN DE CLIENTE /////
            do
            {
                system("cls");
                printf("\nIngrese apellido del cliente: ");
                fflush(stdin);
                scanf("%s", &apellido);
                clienteAux = buscarClientePorApellido(apellido);
                printCliente(clienteAux);
                menuModificarCliente();
                option = getch();
                switch(option)
                {
                case '1':
                    system("cls");

                }
            }
            while (continuar == 's');

            break;

        case 'd' : /////// LISTA DE CLIENTES ACTIVOS ////////
            do
            {
                system("cls");
                menuListaClientes();
                printf("\n\n\tSELECCIONE UNA OPCION: ");
                option = getch();

                switch (option)
                {
                case '1': /////// MOSTRAR CLIENTES ORDENADOS POR APELLIDO, NOMBRE ///////

                    cantidad = clientesActivos(clientes, DIM);
                    ordenarClientePorDni(clientes, cantidad);
                    muestraClientes(clientes, cantidad);

                    break;
                }

            case '2': /////// BUSCAR UN CLIENTE ///////

                cantidad = clientesActivos(clientes, DIM);
                ordPorSelApellido(clientes, cantidad);
                muestraClientes(clientes, cantidad);


            case '3': /////// MOSTRAR CLIENTES ACTIVOS ///////
                mostrarClientes();
                printf("\nDesea VOLVER AL MENU PRINCIPAL? s/n\n");
                option = getch();
            }
            while (continuar == 's');

        }


    case '2':
        system("cls");
        printf("\n\t|---------------------------------|");
        printf("\n\t| ******** MENU PEDIDOS ********* |");
        printf("\n\t|---------------------------------|\n");

        printf("\n\t|---------------------------------|");
        printf("\n\t|**** SECCION EN CONSTRUCCION ****|");
        printf("\n\t|---------------------------------|\n");
        break;
    }


    return 0;
}


void mainMenu()
{
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|********************* BIENVENIDO A PEDIDOS C ********************|");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|------------------------ MENU PRINCIPAL -------------------------|");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|                        [1] - CLIENTES                           |");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|                        [2] - PEDIDOS                            |");
    printf("\n\t|-----------------------------------------------------------------|");
}

void menuClientes()
{
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|************************** PEDIDOS C ****************************|");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|------------------------ MENU CLIENTES --------------------------|");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|                    [a] - Alta                                   |");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|                    [b] - Baja.                                  |");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|                    [c] - Modificaci%cn.                          |",162);
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|                    [d] - Lista de clientes activos.             |");
    printf("\n\t|-----------------------------------------------------------------|");
}

void menuModificarCliente()
{
    printf("\n\n");
    printf("\n|-----------------------------------------------------------------|");
    printf("\n|---------------------- MODIFICAR CLIENTE ------------------------|");
    printf("\n|-----------------------------------------------------------------|");
    printf("\n| SELECCIONE EL CAMPO A MODIFICAR:                                |");
    printf("\n|-----------------------------------------------------------------|");
    printf("\n|                    [1] - Nombre                                 |");
    printf("\n|-----------------------------------------------------------------|");
    printf("\n|                    [2] - Apellido                               |");
    printf("\n|-----------------------------------------------------------------|");
    printf("\n|                    [3] - DNI                                    |");
    printf("\n|-----------------------------------------------------------------|");
    printf("\n|                    [4] - Email                                  |");
    printf("\n|-----------------------------------------------------------------|");
    printf("\n|                    [5] - Domicilio                              |");
    printf("\n|-----------------------------------------------------------------|");
    printf("\n|                    [6] - Tel%cfono                               |",130);
    printf("\n|-----------------------------------------------------------------|\n");
}

void menuListaClientes()
{
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|************************ LISTA DE CLIENTES **********************|");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t| [1] - Mostrar clientes activos en formato 'Apellido, Nombre'    |");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t| [2] - Buscar un cliente                                         |");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t| [3] - Ver listado completo de clientes (activos e inactivos)    |");
    printf("\n\t|-----------------------------------------------------------------|");
}



int generateID()
{
    int idCliente = rand();
}
void menuAddCliente()
{
    printf("\n\t|---------------------------------|");
    printf("\n\t|    **** ALTA DE CLIENTE ****    |");
    printf("\n\t|---------------------------------|");
    printf("\n\t| [1] - Alta Manual               |");
    printf("\n\t|---------------------------------|");
    printf("\n\t| [2] - Reactivar un cliente      |");
    printf("\n\t|---------------------------------|\n\n");
}

cliente addCliente()
{
    cliente c;
    int id = 0;
    c.idCliente = generateID(id) + 1;

    printf("\n\t|---------------------------------|");
    printf("\n\t|    **** ALTA DE CLIENTE ****    |");
    printf("\n\t|---------------------------------|\n");

    printf("*ID CLIENTE: %d", c.idCliente);

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

    guardarClienteEnArchivo(c);

    c.alta = 1;

    id ++;

    return c;
}

void guardarClienteEnArchivo(cliente c)
{
    int clienteValido = verificaCliente(c.dni);

    FILE *archClient = fopen(AR_CLIENTS,"ab");
    if(archClient != NULL)
    {
        if (clienteValido==0)
        {
            fwrite(&c,sizeof(cliente),1,archClient);
        }
        else
        {
            printf("\n\n** ERROR: EL CLIENTE YA SE ENCUENTRA REGISTRADO! **");
        }
        fclose(archClient);
    }
}

cliente buscarClientePorApellido(char apellido[])
{
    int flag=0;
    cliente c;

    FILE *archClient = fopen(AR_CLIENTS,"rb");

    if(archClient)
    {
        while(flag == 0 && fread(&c, sizeof(cliente), 1, archClient) > 0)
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
    printf("\n *ID: %d", c.idCliente);
    printf("\n *NOMBRE: %s", c.nombre);
    printf("\n *APELLIDO: %s", c.apellido);
    printf("\n *D.N.I.: %d", c.dni);
    printf("\n *DOMICILIO");
    printf("\n  -- CALLE: %s", c.direccion.calle);
    printf("\n  -- N%cMERO: %d", 233, c.direccion.numero);
    printf("\n *TEL%cFONO: %l", 144, c.nroTelefono);
    printf("\n  -----------------------------------------------------------------");
}

void bajaCliente()
{
    cliente aux;
    char apellido[20];
    char continuar;

    printf("\n\t|---------------------------------|");
    printf("\n\t|     **** BUSCAR CLIENTE ****    |");
    printf("\n\t|---------------------------------|\n");
    printf("\n\t* Ingrese apellido: ");
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

int verificaCliente (int dni)    /// recibe como parámetro el email
{
    int flag=0;
    cliente c;

    FILE *archClient = fopen(AR_CLIENTS, "rb");
    if (archClient)
    {
        while(flag == 0 && fread(&c, sizeof(cliente), 1, archClient) > 0)
        {
            if(c.dni == dni)
            {
                flag=1;
            }
        }
        fclose(archClient);
    }

    return flag;
}

int clientesActivos(cliente activos[], int dimension)
{
    cliente c;
    int i=0;
    FILE *archClient = fopen(AR_CLIENTS, "rb");
    if(archClient)
    {
        while(fread(&c, sizeof(cliente), 1, archClient) > 0)
        {
            if(c.alta==1)
            {
                c = activos[i];
                i++;
            }
        }
        fclose(archClient);
    }
    return i;
}

int buscaPos(int id){
    int pos = -1;
    cliente c;

    FILE *archClient = fopen(AR_CLIENTS, "rb");

    if(archClient){
        while(pos==-1 && fread(&c, sizeof(cliente), 1, archClient) > 0){
            if(c.id == id){
                pos = ftell(archClient)/sizeof(stCliente)-1;
            }
        }
        fclose(archClient);
    }
    return pos;
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


void mostrarClientes()
{
    cliente c;
    FILE *archClient = fopen(AR_CLIENTS,"rb");

    if(archClient)
    {
        while (fread(&c, sizeof(cliente), 1, archClient) > 0)
        {
            printCliente(c);
        }
        fclose(archClient);
    }
}

int buscaPosMenorApellido(cliente c[], int v, int inicio)
{
    int posMenor = inicio;
    int i = inicio + 1;
    while(i<v)
    {
        if(strcmp(c[i].apellido,c[posMenor].apellido)<0)
        {
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






