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
    char nroTelefono[15];
    char email[50];
    char contrasenia[10];
    int alta;
    dir direccion;

} cliente;

void menuInicio();
void mainMenu();
void accesoCliente();
void menuClientes();
void menuAddCliente();
void menuAddUser(cliente c);
void altaUsuario(cliente c);
void menuAltaCliente();
void menuListaClientes();
int generateID();
int ultimoId();
cliente altaCliente();
cliente modificarCliente(cliente c);
void bajaCliente(cliente c);
void reactivarCliente(cliente c);
int verificaCliente (int dni);
void guardarClienteEnArchivo(cliente c);
cliente buscarClientePorApellido(char apellido[]);
void printCliente(cliente c);
int cargarArregloClientesActivos(cliente clientesActivos[], int dim);
void mostrarArregloClientes(cliente clientesActivos[], int validos);
void intercambiaClientes(cliente *a, cliente *b);
void ordPorSelApellido(cliente c[], int v);


int main()
{
    int option, cantidad, usuarioValido;
    char continuar,aceptar;

    cliente c, clienteAux;
    cliente clientes[100];
    cliente clientesActivos[100];
    char apellido[30];
    char mail[30];
    char contrasenia[10];

    //////////////////////////// AREA DE PRUEBAS  //////////////////////////////////
    menuClientes();
    printf("\n\n\tSELECCIONE UNA OPCION: ");
    fflush(stdin);
    option = getch();
    ////////////////////////////////////////////////////////////////////////////////

    /*
    menuInicio(); ///// INICIO DEL PROGRAMA

    printf("\n\n\tSELECCIONE UNA OPCION: ");

    fflush(stdin);
    option = getch();

    switch(option)
    {
    case '1':
        system("cls");
        accesoCliente(); ///// MENU DE ACCESO CLIENTE
        printf("\n\n\tSELECCIONE UNA OPCION: ");
        fflush(stdin);
        option = getch();
        printf("\n\n");
        system("cls");

        switch (option)
        {
        case '1':    ///// INGRESO CON USUARIO(MAIL) Y CONTRASEÑA /////
            printf("INGRESE MAIL: ");
            scanf("%s", mail);
            printf("\nINGRESE CONTRASE%cA: ",165);
            scanf("%s", contrasenia);
            usuarioValido = validaUsuario(contrasenia);

            if (usuarioValido == 1)
            {
                printf("\n\t\tACCESO CON EXITO!\n");
                option = 1;
            }
            else
            {
                printf("\n\t\t|-----------------------------------------------------------|");
                printf("\n\t\t|   *** ERROR: USUARIO O CONTRASEÑA INVALIDOS INVALIDA ***  |");
                printf("\n\t\t|-----------------------------------------------------------|");
                break;
            }

    */

    switch(option)
    {
    case 'a':  ///// ALTA DE CLIENTE ///////
        do
        {
            system("cls");
            menuAltaCliente();
            printf("\n\n\tSELECCIONE UNA OPCION: ");
            fflush(stdin);
            option = getch();

            switch(option)
            {
                case '1':   ///// ALTA MANUAL ///////
                system("cls");
                altaCliente();
                printf("\nDesea cargar otro cliente? s/n\n");
                fflush(stdin);
                scanf("%c", &continuar);
                break;

            case '2':   ///// REACTIVAR CLIENTE ///////
                system("cls");
                printf("\nIngrese apellido del cliente: ");
                fflush(stdin);
                scanf("%s", &apellido);

                clienteAux = buscarClientePorApellido(apellido);
                printCliente(clienteAux);

                printf("\nDesea dar de alta el cliente? s/n\n");
                scanf("%c", &aceptar);

                if(aceptar == 's' || aceptar == 'S')
                {
                    reactivarCliente(clienteAux);
                    printf("\nCLIENTE REACTIVADO CON %cXITO", 133);
                }
            }


            }
                while (continuar == 's');
        default:
            printf("\n\t|---------------------------------|");
            printf("\n\t|  *** ERROR: OPCION INVALIDA *** |");
            printf("\n\t|---------------------------------|\n");
            system("pause");
            break;



    case 'b':  ///// BAJA DE CLIENTE /////
        do
        {
            system("cls");
            printf("\nIngrese apellido del cliente: ");
            fflush(stdin);
            scanf("%s", &apellido);

            clienteAux = buscarClientePorApellido(apellido);
            printCliente(clienteAux);

            printf("\nDesea dar de baja el cliente? s/n\n");
            fflush(stdin);
            scanf("%c", &aceptar);

            if(aceptar == 's' || aceptar == 'S')
            {
                bajaCliente(clienteAux);
                printf("\nCLIENTE MODIFICADO CON %cXITO", 133);
            }

            printf("\nDesea dar de baja otro cliente? s/n\n");
            scanf("%c", &continuar);

        }
        while (continuar == 's');


    case 'c': //// MODIFICACIÓN DE CLIENTE /////
        do
        {
            system("cls");
            printf("\nIngrese apellido del cliente: ");
            fflush(stdin);
            scanf("%s", &apellido);
            clienteAux = buscarClientePorApellido(apellido);
            printCliente(clienteAux);
            modificarCliente(clienteAux);
            overwriteCliente(clienteAux);
        }
        while (continuar == 's');

        break;

    case 'd' : /////// LISTA DE CLIENTES ////////
        do
        {
            system("cls");
            menuListaClientes();
            printf("\n\n\tSELECCIONE UNA OPCION: ");
            option = getch();

            switch (option)
            {
            case '1': /////// BUSCAR UN CLIENTE ///////
                system("cls");
                printf("Ingrese apellido: ");
                fflush(stdin);
                scanf("%s", apellido);
                clienteAux = buscarClientePorApellido(apellido);
                printCliente(clienteAux);

                break;

            case '2': /////// MOSTRAR CLIENTES ACTIVOS ///////
                cantidad = cargarArregloClientesActivos(clientesActivos, 100);
                mostrarArregloClientes(clientesActivos, cantidad);
                printf("\nDesea VOLVER AL MENU PRINCIPAL? s/n\n");
                option = getch();

                break;

            case '3': /////// MOSTRAR CLIENTES INACTIVOS ///////
                cantidad = cargarArregloClientesInactivos(clientesActivos, 100);
                mostrarArregloClientes(clientesActivos, cantidad);
                printf("\nDesea VOLVER AL MENU PRINCIPAL? s/n\n");
                option = getch();
            }
        }
        while (continuar == 's');

    }


    /*

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



     */


    return 0;
}


void menuInicio()
{
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|*******************  BIENVENIDO A PEDIDOS C  ********************|");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|------------------   SELECCIONE UNA OPCI%cN:   -------------------|", 224);
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|                      [1] - ACCESO CLIENTE                       |");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|                      [2] - ACCESO ADMINISTRADOR                 |");
    printf("\n\t|-----------------------------------------------------------------|");
}

void accesoCliente()
{
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|*******************  BIENVENIDO A PEDIDOS C  ********************|");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|                     [1] - YA TENGO CUENTA                       |");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|                     [2] - CREAR CUENTA                          |");
    printf("\n\t|-----------------------------------------------------------------|");
}

void altaUsuario(cliente c)
{
    system("cls");
    printf("\n\t|---------------------------------|");
    printf("\n\t|    **** ALTA DE USUARIO ****    |");
    printf("\n\t|---------------------------------|\n");

    altaCliente();

    printf("\n\n\t INGRESE SU CONTRASEÑA(MAXIMO 8 CARACTERES): ");
    fflush(stdin);
    scanf("%s", &c.contrasenia);
    if (&c.contrasenia != NULL && 1<c.contrasenia && c.contrasenia>=8)
    {
        printf("\nContraseña almacenada exitosamente!\n");
    }
    else
    {
        printf("CONTRASEÑA INVALIDA, INGRESE UNA NUEVA CONTRASEÑA\n");
        printf("\n\n\t INGRESE SU CONTRASEÑA(MAXIMO 8 CARACTERES): ");
        fflush(stdin);
        scanf("%s", &c.contrasenia);
    }

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
    printf("\n\t|                    [d] - Lista de clientes.                     |");
    printf("\n\t|-----------------------------------------------------------------|");
}

void menuAltaCliente()
{
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|                     **** ALTA DE CLIENTE ****                   |");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|                    [1] - Nuevo Cliente                          |");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t|                    [2] - Reactivar cliente inactivo             |");
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
    printf("\n\t| [1] - Buscar un cliente                                         |");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t| [2] - Ver lista de clientes activos                             |");
    printf("\n\t|-----------------------------------------------------------------|");
    printf("\n\t| [3] - Ver lista de clientes inactivos                           |");
    printf("\n\t|-----------------------------------------------------------------|");
}

int verificaUsuario(char contrasenia[])
{
    cliente c;
    int flag=0;

    FILE *archClient = fopen(AR_CLIENTS,"rb");

    if(archClient!=NULL)
    {
        while(flag == 0 && fread(contrasenia, sizeof(cliente), 1, archClient) > 0)
        {
            if(strcmpi(c.contrasenia, contrasenia) == 0)
            {
                flag=1;
            }
        }
        fclose(archClient);
    }
    return flag;
}

int generateID()
{
    int idCliente = rand();
}

int ultimoId()
{
    cliente c;
    int id = -1;

    FILE *archClient = fopen(AR_CLIENTS,"rb");

    if(archClient)
    {
        fseek(archClient, sizeof (cliente)*(-1), SEEK_END);

        if(fread(&c,sizeof(cliente),1,archClient) > 0)
        {
            id = c.idCliente;
        }
        fclose(archClient);
    }
    return id;
}

cliente altaCliente()
{
    cliente c;
    int valido = 0;
    c.idCliente = ultimoId() + 1;

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
    scanf("%ld", &c.dni);

    printf("\n\n*DOMICILIO: ");
    printf("\n**CALLE: ");
    fflush(stdin);
    scanf("%s", &c.direccion.calle);

    printf("\n**NRO: ");
    fflush(stdin);
    scanf("%d", &c.direccion.numero);

    printf("\n\*E-MAIL: ", 144);
    fflush(stdin);
    scanf("%s", &c.email);

    printf("\n\nNUMERO DE T%cLEFONO: ", 144);
    fflush(stdin);
    scanf("%s", &c.nroTelefono);

    valido = verificaCliente(c.dni);

    if(valido = 1)
    {
        guardarClienteEnArchivo(c);

        printf("\n\nEl cliente se ha guardado exitosamente!");
    }
    else
    {
        printf("\n\nERROR: EL CLIENTE YA SE ENCUENTRA REGISTRADO");
    }
    c.alta = 1;

    return c;
}

void guardarClienteEnArchivo(cliente c)
{
    FILE *archClient = fopen(AR_CLIENTS,"ab");

    if(archClient != NULL)
    {
        fwrite(&c,sizeof(cliente),1,archClient);
    }
    else
    {
        printf("\n\n** ERROR: EL CLIENTE YA SE ENCUENTRA REGISTRADO! **");
    }
    fclose(archClient);
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

    printf("\n\t-----------------------------------------------------------------");
    printf("\n\t *ID: %d", c.idCliente);
    printf("\n\t-----------------------------------------------------------------");
    printf("\n\t *NOMBRE: %s", c.nombre);
    printf("\n\t-----------------------------------------------------------------");
    printf("\n\t *APELLIDO: %s", c.apellido);
    printf("\n\t-----------------------------------------------------------------");
    printf("\n\t *D.N.I.: %ld", c.dni);
    printf("\n\t-----------------------------------------------------------------");
    printf("\n\t *DOMICILIO %s %d", c.direccion.calle, c.direccion.numero);
    printf("\n\t-----------------------------------------------------------------");
    printf("\n\t *EMAIL: %s", c.email);
    printf("\n\t-----------------------------------------------------------------");
    printf("\n\t *TEL%cFONO: %s", 144, c.nroTelefono);
    printf("\n\t-----------------------------------------------------------------");
}

void bajaCliente(cliente c)
{
    c.alta = 0;
    overwriteCliente(c);
}

void reactivarCliente(cliente c)
{
    c.alta = 1;
    overwriteCliente(c);
}

int verificaCliente (int dni)    /// recibe como parámetro el dni
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

/*
int buscaPos(int id){
    int pos = -1;
    cliente c;

    FILE *archClient = fopen(AR_CLIENTS, "rb");

    if(archClient){
        while(pos==-1 && fread(&c, sizeof(cliente), 1, archClient) > 0){
            if(c.id == id)
                {
                pos = ftell(archClient)/sizeof(stCliente)-1;
                }
        }
        fclose(archClient);
    }
    return pos;
}*/

int buscaPosMenorDni (cliente c[], int v, int inicio)
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
            printf("\n\n");
        }
        fclose(archClient);
    }
}


int cargarArregloClientesActivos(cliente clientesActivos[], int dim)
{
    FILE * archClient = fopen(AR_CLIENTS, "rb");
    cliente c;

    int i=0;

    if(archClient!=NULL)
    {

        while(fread(&c,sizeof(cliente), 1, archClient)>0 && i<dim )
        {
            if(c.alta = 1)
            {
                clientesActivos[i] = c;
                i++;
            }
        }

        fclose(archClient);
    }

    return i;   //// CLIENTES ACTIVOS VALIDOS
}

void mostrarArregloClientes(cliente c[], int validos)
{
    int i = 0;

    for(i=0; i<validos; i++)
    {
        printf("\n\t-----------------------------------------------------------------");
        printf("\n\t %s", c[i]);
        printf("\n\t-----------------------------------------------------------------");
    }
}

cliente modificarCliente(cliente c)
{
    int option;
    char continuar;
    cliente d;
    menuModificarCliente();
    printf("\n\n\tSELECCIONE UNA OPCION: ");
    option = getch();
    printf("\n");

    switch (option)
    {
    case '1':
        printf("\n*INGRESE NUEVO NOMBRE: ");
        fflush(stdin);
        scanf("%s", &d.nombre);
        strcpy(c.nombre, d.nombre);
        break;
    case '2':
        printf("\n*INGRESE NUEVO APELLIDO: ");
        fflush(stdin);
        scanf("%s", &d.apellido);
        strcpy(c.apellido, d.apellido);
        break;
    case '3':
        printf("\n*INGRESE NUEVO DNI: ");
        fflush(stdin);
        scanf("%ld", &d.dni);
        c.dni = d.dni;
        break;
    case '4':
        printf("\n*INGRESE NUEVO EMAIL: ");
        fflush(stdin);
        scanf("%s", &d.email);
        strcpy(c.email, d.email);
        break;
    case '5':
        printf("\n*INGRESE NUEVO DOMICILIO");
        printf("\n**CALLE: ");
        scanf("%s", &d.direccion.calle);
        printf("\n**NUMERO: ");
        scanf("%d", &d.direccion.numero);
        strcpy(c.direccion.calle, d.direccion.calle);
        c.direccion.numero = d.direccion.numero;
        break;
    case '6':
        printf("\n*INGRESE NUEVO TEL%cFONO:",144);
        fflush(stdin);
        scanf("%s", &d.nroTelefono);
        strcpy(c.nroTelefono, d.nroTelefono);
        break;
    }

    printf("\nCLIENTE MODIFICADO CON %cXITO\n", 144);
    fflush(stdin);

    return c;
}

void overwriteCliente(cliente c)
{
    int pos = 0;
    pos = buscaPosCliente(c.idCliente);
    FILE *archClient = fopen(AR_CLIENTS, "r+b");
    if(archClient)
    {
        fseek(archClient, sizeof(cliente)*pos, SEEK_SET);
        fwrite(&c, sizeof(cliente), 1, archClient);
        fclose(archClient);
    }
}

int buscaPosCliente(int id)
{
    int pos = -1;
    cliente c;
    FILE *archClient = fopen(AR_CLIENTS, "rb");
    if(archClient)
    {
        while(pos == -1 && fread(&c, sizeof(cliente), 1, archClient)>0)
        {
            if(c.idCliente == id)
            {
                pos = ftell(archClient)/sizeof(cliente)-1;
            }
        }
        fclose(archClient);
    }
    return pos;
}

int cargarArregloClientesInactivos(cliente inactivos[], int dimension)
{
    cliente c;
    int i=0;

    FILE *archClient = fopen(AR_CLIENTS, "rb");
    if(archClient!=NULL)
    {
        while(fread(&c, sizeof(cliente), 1, archClient) > 0)
        {
            if(c.alta==0)
            {
                inactivos[i] = c;
                i++;
            }
        }
        fclose(archClient);
    }
    return i; /// VALIDOS CLIENTES INACTIVOS
}
