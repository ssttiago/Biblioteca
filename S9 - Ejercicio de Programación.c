#include <stdio.h>
#include <string.h>

#define MAX 10

typedef struct {
    int id;
    char titulo[100];
    char autor[50];
    int anio;
    char estado[12];
} Libro;

Libro bib[MAX];
int total = 0;

int buscarId(int id) {
    int i;
    for (i = 0; i < total; i++)
        if (bib[i].id == id) return i;
    return -1;
}

void registrar() {
    int id;
    if (total >= MAX) { printf("Limite alcanzado.\n"); return; }
    printf("ID: "); scanf("%d", &id);
    if (id <= 0 || buscarId(id) != -1) { printf("ID invalido o duplicado.\n"); return; }
    bib[total].id = id;
    printf("Titulo: ");  scanf(" %[^\n]", bib[total].titulo);
    printf("Autor: ");   scanf(" %[^\n]", bib[total].autor);
    printf("Año: ");     scanf("%d", &bib[total].anio);
    strcpy(bib[total].estado, "Disponible");
    total++;
    printf("Libro registrado.\n");
}

void mostrar() {
    int i;
    if (total == 0) { printf("Sin libros.\n"); return; }
    printf("\n%-5s %-30s %-20s %-6s %-12s\n", "ID","Titulo","Autor","Año","Estado");
    for (i = 0; i < total; i++)
        printf("%-5d %-30s %-20s %-6d %-12s\n",
            bib[i].id, bib[i].titulo, bib[i].autor, bib[i].anio, bib[i].estado);
}

void buscar() {
    int op, id, i; char titulo[100];
    printf("1.ID  2.Titulo: "); scanf("%d", &op);
    if (op == 1) {
        printf("ID: "); scanf("%d", &id);
        i = buscarId(id);
    } else {
        printf("Titulo: "); scanf(" %[^\n]", titulo);
        for (i = 0; i < total && strcmp(bib[i].titulo, titulo) != 0; i++);
        if (i == total) i = -1;
    }
    if (i == -1) printf("No encontrado.\n");
    else printf("ID:%d | %s | %s | %d | %s\n",
        bib[i].id, bib[i].titulo, bib[i].autor, bib[i].anio, bib[i].estado);
}

void actualizar() {
    int id, i;
    printf("ID: "); scanf("%d", &id);
    i = buscarId(id);
    if (i == -1) { printf("No encontrado.\n"); return; }
    strcpy(bib[i].estado, strcmp(bib[i].estado,"Disponible")==0 ? "Prestado":"Disponible");
    printf("Estado: %s\n", bib[i].estado);
}

void eliminar() {
    int id, i, j;
    printf("ID: "); scanf("%d", &id);
    i = buscarId(id);
    if (i == -1) { printf("No encontrado.\n"); return; }
    for (j = i; j < total - 1; j++) bib[j] = bib[j+1];
    total--;
    printf("Eliminado.\n");
}

int main() {
    int op;
    do {
        printf("\n1.Registrar 2.Mostrar 3.Buscar 4.Actualizar 5.Eliminar 6.Salir\nOpcion: ");
        scanf("%d", &op);
        if      (op == 1) registrar();
        else if (op == 2) mostrar();
        else if (op == 3) buscar();
        else if (op == 4) actualizar();
        else if (op == 5) eliminar();
        else if (op == 6) printf("Adios.\n");
        else              printf("Opcion invalida.\n");
    } while (op != 6);
    return 0;
}
