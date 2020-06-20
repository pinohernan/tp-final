#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AR_CLIENTS "Clients.dat"
#define AR_ACTIVES "ActiveClients.dat"
#define AR_INACTIVES"InnactiveClients.dat"

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
    dir direccion;

} cliente;

void mainMenu();
cliente addClient();

int main()
{
    int option;
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
        case 'a':
            do
            {
                system("cls");
                addClient();
                printf("\nDesea cargar otro cliente? s/n\n");
                fflush(stdin);
                scanf("%c", &continuar);
            }
            while (continuar == 's');

        case 'b':
            do
            {
                system("cls");
                bajaCliente();

                system("pause");
                printf("\nDesea continuar BAJA DE CLIENTE? s/n\n");
                fflush(stdin);
                scanf("%c", &continuar);


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

int generateID()
{
    int idCliente = 0;
}

cliente addClient()
{
    cliente c;

    printf("**** ALTA CLIENTE ****");
    printf("\n\n");
    printf("*ID CLIENTE: ");

    c.idCliente = generateID();

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

    saveClientToFile(c);

    return c;
}

void saveClientToFile(cliente c)
{
    FILE *archClient = fopen(AR_CLIENTS,"ab");
    if(archClient != NULL)
    {
        fwrite(&c,sizeof(cliente),1,archClient);
        fclose(archClient);
    }
}
void cargaArchivoClientes(cliente clientes[])
{

    char continuar = 's';
    cliente c;	    			/// crea un cliente como variable

    while(continuar == 's') 				/// mientras quiera seguir ingresando clientes
    {
        system("cls");
        printf("\n Carga de Clientes \n");
        c = addClient();			/// reutiliza la función de cargar cliente
//        c.id = buscaUltimoId() + 1;			/// le asigna el ultimo id+1 al nuevo cliente
        //     guardaUnCliente(c);			/// lo guarda en el archivo

        printf("\nDesea continuar con la carga? s/n \n");
        fflush(stdin);
        scanf("%c", &continuar);
    }
}

void bajaCliente()
{
    cliente aux;
    char apellido[20];
    char continuar;

    printf("\n\tIngrese el apellido a buscar:\n");
    fflush(stdin);
    scanf("%s", &apellido);

    aux = buscarClientePorApellido(apellido);

    if (aux.id != -1){
        printf("\nEl cliente existe en el archivo\n");
        muestraUnCliente(aux);
    } else{
        printf("\nEl cliente no existe en el archivo\n");
    }

    printf("\nDesea dar de baja al cliente? s/n \n");
    fflush(stdin);
    scanf("%c", &continuar);

    if (continuar == 's'){
        aux.baja = 2;
    }
    guardaUnCliente(aux);
}

cliente buscarClientePorApellido(char apellido[]) 	/// recibe como parámetro el apellido a buscar
{
    cliente c;
    int flag=0;

    FILE *archClient = fopen(AR_CLIENTES,"rb");	/// abre el archivo en modo binario para operaciones de lectura

    if(archClient) 					/// verifica si abrió sin errores.
    {
        while( flag == 0 && fread(&c, sizeof(stCliente), 1, archClient) > 0)
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





