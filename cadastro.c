#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USER 1000
#define MAX_NOME 50
#define MAX_EMAIL 50
#define MAX_END 50
#define MAX_SEXO 10

typedef struct{

    int id;
    char nome[MAX_NOME];
    char email[MAX_EMAIL];
    char sexo[MAX_SEXO];
    char end[MAX_END];
    double altura;
    int vacina;

}Usuario;

Usuario usuarios[MAX_USER];
int totalUsuarios = 0; 

int gerarId() {
    int numAleatorio = rand() % 20000 + 1;
    return numAleatorio;

}
int verificaEmail (char *email) {

    int * aux = strchr(email, '@');
    return aux != NULL;
}

int validarSexo (char *sexo) {
    const char * strFem = "FEM";
    const char * strMas = "MASC";
    const char * strInd = "IND";


    if (strcmp (sexo,strFem) == 0 || strcmp (sexo, strMas) || strcmp (sexo, strInd)) {
        return 0;
    }
}

void validarAltura (double altura) {
    if (altura > 1.0 || altura < 2.0) {
        return 0;
    }
}

void cadastrarUsuario() {

    Usuario novoUsuario;

    novoUsuario.id = gerarId (); 

    printf ("Digite o nome: ");
    scanf ("%s", novoUsuario.nome);
    fflush (stdin);

    //email ]
    printf ("Digite o email -nome@email-: ");
    scanf ("%s", novoUsuario.email);

    while (verificaEmail(novoUsuario.email) == NULL) {
        printf ("Formato invalido. Digite o email novamente.");
        scanf ("%s", novoUsuario.email);
    }
    fflush (stdin);

    printf ("Digite o sexo: F --> Feminino || M --> Masculino || I --> Indiferente ");
    scanf ("%s", novoUsuario.sexo);

    while (validarSexo(novoUsuario.sexo) != 0) {
        printf ("Formato invalido. Digite o sexo novamente.");
        scanf ("%s", novoUsuario.sexo);
    }
    fflush (stdin);

    printf ("Digite o endereco: ");
    scanf ("%s", novoUsuario.end);

    printf ("Digite a altura entre 1 e 2 metros:" );
    scanf ("%lf", &novoUsuario.altura);

    while (validarAltura(novoUsuario.altura) != NULL) {
        printf ("Digite uma altura valida!");
        scanf ("%lf", &novoUsuario.altura);
    }

    printf ("Vacina 1 = SIM 0 = NAO");
    scanf ("%d", &novoUsuario.vacina);

    usuarios[totalUsuarios++] = novoUsuario;

}

void imprimirListaUsuario () {
    for (int i = 0; i < totalUsuarios; i++) {
        printf ("\nNome: %s,", usuarios[i].nome);
        printf ("\nEmail: %s,", usuarios[i].email);
        printf ("\nID: %d,", usuarios[i].id);
        printf ("\nSexo: %s,", usuarios[i].sexo);
        printf ("\nEndereco: %s,", usuarios[i].end);
        printf ("\nAltura: %.2lf,", usuarios[i].altura);
        printf ("\n ________________________________");
    }
}

void buscarUsuario () {
    char buscarEmail [MAX_EMAIL];
    printf ("Digite o email que deseja buscar: ");
    scanf ("%s", &buscarEmail);

    int validado = 0;
    int i;

    for (i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuarios[i].email, buscarEmail) == 0) {
            validado = 1;
            break;
        }
    }
    if (validado) {
        printf ("Encontrado na base");
        printf ("\nNome: %s,", usuarios[i].nome);
        printf ("\nEmail: %s,", usuarios[i].email);
        printf ("\nID: %d,", usuarios[i].id);
    } else  {
        printf ("Email nao encontrado");
    }
}

void alterarDadoUsuario () {
    int buscarID;
    printf ("Digite o identificador do usuario que deseja alterar: ");
    scanf ("%d", &buscarID);

    int validado = 0;
    int i;

    for (i = 0; i < totalUsuarios; i++) {
        if (usuarios[i].id == buscarID ) {
            validado = 1;
            break;
        }
    }
    if (validado == 1) {

        int buscarID; 

        printf ("Digite o nome: ");
        scanf ("%s", usuarios[i].nome);
        fflush (stdin);

        printf ("Digite o email -nome@email-: ");
        scanf ("%s", usuarios[i].email);

        while (verificaEmail(usuarios[i].email) == NULL) {
            printf ("Formato invalido. Digite o email novamente.");
            scanf ("%s", usuarios[i].email);
        }
        fflush (stdin);

        printf ("Digite o sexo: F --> Feminino || M --> Masculino || I --> Indiferente ");
        scanf ("%s", usuarios[i].sexo);

        while (validarSexo(usuarios[i].sexo) != 0) {
            printf ("Formato invalido. Digite o sexo novamente.");
            scanf ("%s", usuarios[i].sexo);
        }
        fflush (stdin);

        printf ("Digite o endereco: ");
        scanf ("%s", usuarios[i].end);

        printf ("Digite a altura entre 1 e 2 metros:" );
        scanf ("%lf", &usuarios[i].altura);

        while (validarAltura(usuarios[i].altura)) {
            printf ("Digite uma altura valida!");
            scanf ("%lf", &usuarios[i].altura);
        }

        printf ("Vacina 1 = SIM 0 = NAO");
        scanf ("%d", &usuarios[i].vacina);
        }
}
void excluirUsuario () {
    int buscarID;
    printf ("Digite o identificador do usuario que deseja alterar: ");
    scanf ("%d", &buscarID);

    int validado = 0;
    int i;

    for (i = 0; i < totalUsuarios; i++) {
        if (usuarios[i].id == buscarID ) {
            validado = 1;
            break;
        }
    }
    if (validado) {
        for (int j = i;j < totalUsuarios-1; j++) {
            usuarios[j] = usuarios [j + 1];
        }
    }
    totalUsuarios--;
}

void realizarBackup (){
    
    FILE *backup = fopen ("backup.txt", "w");
    if (backup == NULL) {
        printf ("Erro ao abrir o arquivo");
    }

    for (int i = 0; i < totalUsuarios; i++){
        fprintf (backup, "\nNome: %s", usuarios[i].nome);
        fprintf (backup, "\nEmail: %s", usuarios[i].email);
        fprintf (backup, "\nSexo: %s", usuarios[i].sexo);
        fprintf (backup, "\nID: %d", usuarios[i].id);
        fprintf (backup, "\nAltura: %.lf", usuarios[i].altura);
        fprintf (backup, "\nVacina: %d", usuarios[i].vacina);
    }
    fclose (backup);
    printf ("Backup realizado");
}

void restaurarBackup () {
    FILE *backup = fopen ("backup.txt", "r");
    if (backup == NULL) {
        printf ("Erro ao abrir arquivo");
    }
    for (int i = 0; i < totalUsuarios; i++){
        fscanf (backup, "%d\n", &usuarios[i].id);

        fgetc (backup);
        fgets (usuarios[i].nome, sizeof(usuarios[i].nome), backup); 
        fgets (usuarios[i].email, sizeof(usuarios[i].email), backup); 
        fgets (usuarios[i].sexo, sizeof(usuarios[i].sexo), backup); 
        fgets (usuarios[i].end, sizeof(usuarios[i].end), backup);
        fscanf(backup, "%lf", &usuarios[i].altura);
        fscanf(backup, "%d", &usuarios[i].vacina);
        fgetc(backup);
    }

    fclose (backup);
    printf ("\nResturacao dos dados realizadas com sucesso!");
}

main () {
    char opcao;

    do {
    printf ("\n-----------------------------------------\n");
    printf ("\n\t\t | Opcoes do Sistema |");
    printf ("\n-----------------------------------------\n");
    printf ("\n1 - Cadastrar usuario");
    printf ("\n2 - Alterar dados de usuario");
    printf ("\n3 - Excluir usuario");
    printf ("\n4 - Buscar usuario por email");
    printf ("\n5 - Imprimir todos os registros");
    printf ("\n6 - Realizar backup de usuarios");
    printf ("\n7 - Restaurar backup");

    printf ("\nDefina a operacao: ");
    scanf ("%c", &opcao);

    switch (opcao) {
        case '1':
            cadastrarUsuario();
            break;
        case '2': 
            alterarDadoUsuario();
            break;
        case '3':
            excluirUsuario();
            break;
        case '4': 
            buscarUsuario();
            break;
        case '5':
            imprimirListaUsuario();
            break;
        case '6':
            realizarBackup();
            break;
        case '7':
            restaurarBackup();
           break;
        default:
            printf ("Opcao invalida");
            break;

    }
    } while (opcao != '0');
    getchar ();
}