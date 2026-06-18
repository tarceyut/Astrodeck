#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ----------------------------
ASTRODECK
Terminal astronómica portable
---------------------------- */


// ----- Definición de struct -----

typedef struct Observacion{
    char nombre[50]; // Nombre de objeto observado. Ejemplo: Saturno.
    char tipo[50]; // Tipo de objeto observado. Ejemplo: planeta.
    char fecha[50]; // Fecha de la observación. Ejemplo: 24/05/2026.
    char hora[50]; // Hora de la observación. Ejemplo: 19:05.
    char ubicacion[50]; // Ubicación de la observación. Ejemplo: Sabanilla, Montes de Oca.
    char notas[200]; // Notas de la observación. Ejemplo: alta nubosidad.
    struct Observacion *siguiente; // Puntero al siguiente nodo (observación) de la lista enlazada.
} Observacion;


// ----- Prototipo de funciones -----

void mostrar_menu ();
void registrar_observacion (Observacion **cabeza); // ** = modificar lista. Puedo modificar la cabeza.
void ver_observaciones (Observacion *cabeza); // * = solo leer lista
void buscar_objeto (Observacion *cabeza); // * = solo leer lista
void liberar_observaciones (Observacion **cabeza); // ** = modificar lista. Puedo modificar la cabeza.


// ----- Main -----

int main(){
    int opcion; // Creo variable llamada opción.
    Observacion *cabeza = NULL; // Mi lista inicia vacía.
    do {
        mostrar_menu();
        printf("Seleccione una opción: ");
        scanf("%d", &opcion); // scanf va a la dirección de memoria de 'opción' y guarda ahí el número que escriba el usuario.

        // Opción 1
        if (opcion == 1){
            registrar_observacion(&cabeza);
        }
        // Opción 2
        else if (opcion == 2){
            ver_observaciones(cabeza);
        }
        // Opción 3
        else if (opcion == 3){
            buscar_objeto(cabeza);
        }
        // Opción 4
        else if (opcion == 4){
            printf("\nSaliendo de AstroDeck...\n");
        }
        // Opción inválida
        else{
            printf("\nOpción inválida.\n");
        }
        printf("\n");
    } while (opcion != 4); // Mientras el usuario no quiera salir de AstroDeck, sigo ejecutando el menú.
    
    // Libero memoria antes de salir de main.
    liberar_observaciones(&cabeza);
    
    // Salgo de main.
    return 0;
}


// ----- Funciones -----


// Mostrar menú
void mostrar_menu(){
    printf("====================================\n");
    printf("            ASTRODECK              \n");
    printf("====================================\n");

    printf("1. Registrar observacion.\n");
    printf("2. Ver observaciones.\n");
    printf("3. Buscar objeto celeste.\n");
    printf("4. Salir.\n");

    printf("====================================\n");
}


// Registrar una observación: recorro hasta el final para insertar.
void registrar_observacion (Observacion **cabeza){
    // Reservo memoria para una nueva observación.
    Observacion *nueva = malloc(sizeof(Observacion));

    // Caso: si hay un error al reservar memoria, salgo con un return.
    if (nueva == NULL){
        printf("Error al reservar memoria.\n");
        return;
    }

    // Si la memoria se reservó exitosamente, continúo.
    printf("Ingrese el nombre del objeto: ");
    scanf("%s", nueva -> nombre);

    printf("Ingrese el tipo de objeto: ");
    scanf("%s", nueva -> tipo);

    printf("Ingrese la fecha de la observación: ");
    scanf("%s", nueva -> fecha);

    printf("Ingrese la hora de la observación: ");
    scanf("%s", nueva -> hora);

    printf("Ingrese la ubicación de la observación: ");
    scanf(" %[^\n]", nueva -> ubicacion); // "[^\n]" significa “leer todo hasta encontrar ENTER”. Esto me permite ingresar, por ejemplo "Montes de Oca", y guardarlo completo

    printf("Ingrese notas de la observación: ");
    scanf(" %[^\n]", nueva -> notas);

    // Mi nueva observación aún no apunta a otra observación.
    nueva -> siguiente = NULL;

    // Si aún no existe ninguna observación.
    if (*cabeza == NULL){
        // Entonces convierto esta observación en el primer nodo (cabeza).
        *cabeza = nueva;
    }
    else{ // Si ya existe una observación en mi lista, recorro hasta el final:

        // Temporal apunta a cabeza. Uso temp para no perder mi cabeza original.
        Observacion *temp = *cabeza;
        
        // Mientras no llegue al final de la lista.
        while (temp -> siguiente != NULL){
            // Paso a la siguiente observación/nodo.
            temp = temp -> siguiente;
        }
        
        // Agrego mi nueva observación al final de mi lista.
        temp -> siguiente = nueva;
    }
    printf("\n====== OBSERVACIÓN REGISTRADA ======\n");
}

// Ver mis observaciones registradas. Recorro hasta el final para mostrar.
void ver_observaciones (Observacion *cabeza){
    // Uso temp para recorrer la lista sin perder ni modificar la cabeza.
    Observacion *temp = cabeza;

    // Si la lista está vacía, me salgo ya que no tengo nada que mostrar.
    if (temp == NULL){
        printf("\nNo hay observaciones registradas.\n");
        return;
    }

    printf("\n==== OBSERVACIONES REGISTRADAS =====\n");

    // Mientras que la lista no esté vacía:
    while (temp != NULL){
        // Imprimo la información de la observación.
        printf("Objeto: %s\n", temp -> nombre);
        printf("Tipo: %s\n", temp -> tipo);
        printf("Fecha: %s\n", temp -> fecha);
        printf("Hora: %s\n", temp -> hora);
        printf("Ubicacion: %s\n", temp -> ubicacion);
        printf("Notas: %s\n", temp -> notas);
        printf("------------------------------------\n");
        // Me muevo a la siguiente observación.
        temp = temp -> siguiente;
    }
}

// Buscar un objeto por el nombre. Recorro hasta el final para encontrar. 
void buscar_objeto (Observacion *cabeza){ 
    char nombre_buscado[50];
    // Creo un puntero 'actual' que apunta a la cabeza.
    Observacion *actual = cabeza;
    int encontrado = 0;

    // Si mi lista está vacía
    if (cabeza == NULL){
        printf("\nNo hay observaciones registradas.\n");
        // Salgo con return.
        return;
    }

    printf("Ingrese el nombre del objeto que desea buscar: ");
    scanf("%s", nombre_buscado);

    // Mientras hayan observaciones en mi lista:
    while (actual != NULL){
        /*
        'strcmp' compara dos textos. 
        Si devuelve 0: los textos son iguales.
        Si devuelve otro valor: los textos son diferentes.
        */

        // Si el nombre guardado en el nodo coincide con el nombre ingresado por el usuario:
       if (strcmp(actual-> nombre, nombre_buscado) == 0){
            printf("\n======= OBSERVACIÓN ENCONTRADA =======\n");

            printf("Objeto: %s\n", actual -> nombre);
            printf("Tipo: %s\n", actual -> tipo);
            printf("Fecha: %s\n", actual -> fecha);
            printf("Hora: %s\n", actual -> hora);
            printf("Ubicacion: %s\n", actual -> ubicacion);
            printf("Notas: %s\n", actual -> notas);

            printf("====================================\n");

            encontrado = 1;
        }
        // Paso a la siguiente observación.
        actual = actual -> siguiente;
    }
    // Si recorrí toda la lista, y no encontré coincidencias
    if (encontrado == 0){
        printf("\nNo se encontró ninguna observación con ese nombre...\n");
    }
}


// Liberar memoria para que no haya fugas (memory leaks). Recorro hasta el final para liberar memoria.
void liberar_observaciones (Observacion **cabeza){
    // Creo temporal.
    Observacion *temp;

    // Mientras haya una observación/nodo en mi lista.
    while (*cabeza != NULL){
        // Mi temporal apunta a cabeza.
        temp = *cabeza;
        // Muevo la cabeza a la observación/nodo siguiente.
        *cabeza = (*cabeza) -> siguiente;
        // Libero temporal.
        free(temp);
    }
    *cabeza = NULL;
}
