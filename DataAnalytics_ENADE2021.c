#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int NU_ANO;
    int CO_CURSO;
    int CO_IES;
    int CO_CATEGAD;
    int CO_ORGACAD;
    int CO_GRUPO;
    int CO_MODALIDADE;
    int CO_MUNIC_CURSO;
    int CO_UF_CURSO;
    int CO_REGIAO_CURSO;
} AllCoursesData;

typedef struct {
    int NU_ANO;
    int CO_CURSO;
    int NU_ITEM_OFG;
    int NU_ITEM_OFG_Z;
    float NT_GER;
    float NT_CE;
} CourseDataExtended;

typedef struct {
    float score;
    int courseCode;
    int ies;
} ScoreData;

AllCoursesData *allCoursesData = NULL;
int totalCoursesData = 0;

void loadAllCoursesData() {
    FILE *file = fopen("microdados2021_arq1.txt", "r");

    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer), file); 

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        allCoursesData = (AllCoursesData *)realloc(allCoursesData, (totalCoursesData + 1) * sizeof(AllCoursesData));

        if (!allCoursesData) {
            printf("Erro ao alocar memória!\n");
            fclose(file);
            exit(1);
        }

        sscanf(buffer, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d", 
            &allCoursesData[totalCoursesData].NU_ANO, &allCoursesData[totalCoursesData].CO_CURSO,
            &allCoursesData[totalCoursesData].CO_IES, &allCoursesData[totalCoursesData].CO_CATEGAD,
            &allCoursesData[totalCoursesData].CO_ORGACAD, &allCoursesData[totalCoursesData].CO_GRUPO,
            &allCoursesData[totalCoursesData].CO_MODALIDADE, &allCoursesData[totalCoursesData].CO_MUNIC_CURSO,
            &allCoursesData[totalCoursesData].CO_UF_CURSO, &allCoursesData[totalCoursesData].CO_REGIAO_CURSO
        );

        totalCoursesData++;
    }

    fclose(file);
}

CourseDataExtended *courseDataExtended = NULL;
int totalDataExtended = 0;

void loadCourseExtendedData() {
    FILE *file = fopen("microdados2021_arq3.txt", "r");

    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    char buffer[2048]; 
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file)) {
        courseDataExtended = (CourseDataExtended*) realloc(courseDataExtended, (totalDataExtended + 1) * sizeof(CourseDataExtended));

        if (!courseDataExtended) {
            printf("Erro ao alocar memória!\n");
            fclose(file);
            exit(1);
        }

        sscanf(buffer, "%d;%d;%*d;%*d;%*d;%*d;%*d;%*d;%*d;%*d;%*[^;];%*[^;];%*[^;];%*[^;];%*[^;];%*[^;];%*d;%*d;%*d;%*d;%*d;%*d;%*d;%*d;%*d;%*d;%*d;%f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*f;%*d;%*d;%*d;%*d;%*d;%*d;%*d;%*d;%*d",
               &courseDataExtended[totalDataExtended].NU_ANO,
               &courseDataExtended[totalDataExtended].CO_CURSO,
               &courseDataExtended[totalDataExtended].NT_GER,
               &courseDataExtended[totalDataExtended].NT_CE
        );

        totalDataExtended++;
    }

    fclose(file);
}

void findCourse(int code) {
    int i, found = 0;
    for (i = 0; i < totalCoursesData; i++) {
        if (allCoursesData[i].CO_CURSO == code) {
            printf("Dados do curso %d:\n", code);
            printf("NU_ANO: %d\n", allCoursesData[i].NU_ANO);
            printf("CO_CURSO: %d\n", allCoursesData[i].CO_CURSO);
            printf("CO_IES: %d\n", allCoursesData[i].CO_IES);
            printf("CO_CATEGAD: %d\n", allCoursesData[i].CO_CATEGAD);
            printf("CO_ORGACAD: %d\n", allCoursesData[i].CO_ORGACAD);
            printf("CO_GRUPO: %d\n", allCoursesData[i].CO_GRUPO);
            printf("CO_MODALIDADE: %d\n", allCoursesData[i].CO_MODALIDADE);
            printf("CO_MUNIC_CURSO: %d\n", allCoursesData[i].CO_MUNIC_CURSO);
            printf("CO_UF_CURSO: %d\n", allCoursesData[i].CO_UF_CURSO);
            printf("CO_REGIAO_CURSO: %d\n", allCoursesData[i].CO_REGIAO_CURSO);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Curso não encontrado.\n");
    }
}

int isValidIES(int iesValue) {
    for (int i = 0; i < totalCoursesData; i++) {
        if (allCoursesData[i].CO_IES == iesValue) {
            return 1; 
        }
    }
    return 0;
}

void listByIES(int ies) {
    if (!isValidIES(ies)) {
        printf("CO_IES %d não encontrado nos dados.\n", ies);
        return;
    }
    
    int i, found = 0;

    printf("Cursos pela IES %d:\n", ies);
    for (i = 0; i < totalCoursesData; i++) {
        if (allCoursesData[i].CO_IES == ies) {
            printf("CO_CURSO: %d\n", allCoursesData[i].CO_CURSO);
            found = 1;
        }
    }
    if (!found) {
        printf("Nenhum curso encontrado para esta IES.\n");
    }
}

int isValidUF(int ufValue) {
    for (int i = 0; i < totalCoursesData; i++) {
        if (allCoursesData[i].CO_UF_CURSO == ufValue) {
            return 1;
        }
    }
    return 0;
}


void listByUF(int uf) {
    if (!isValidUF(uf)) {
        printf("CO_UF_CURSO %d não encontrado nos dados.\n", uf);
        return;
    }

    int i, found = 0;
    
    printf("Cursos pela UF %d:\n", uf);
    for (i = 0; i < totalCoursesData; i++) {
        if (allCoursesData[i].CO_UF_CURSO == uf) {
            printf("CO_CURSO: %d\n", allCoursesData[i].CO_CURSO);
            found = 1;
        }
    }
    if (!found) {
        printf("Nenhum curso encontrado para esta UF.\n");
    }
}

int isValidGroup(int grupoValue) {
    for (int i = 0; i < totalCoursesData; i++) {
        if (allCoursesData[i].CO_GRUPO == grupoValue) {
            return 1;  
        }
    }
    return 0;  
}

void listByGroup(int group) {
    if (!isValidGroup(group)) {
        printf("CO_GRUPO %d não encontrado nos dados.\n", group);
        return;
    }

    int i, found = 0;
    printf("Cursos pelo grupo %d:\n", group);
    for (i = 0; i < totalCoursesData; i++) {
        if (allCoursesData[i].CO_GRUPO == group) {
            printf("CO_CURSO: %d\n", allCoursesData[i].CO_CURSO);
            found = 1;
        }
    }
    if (!found) {
        printf("Nenhum curso encontrado para este grupo.\n");
    }
}

void listAndAverageScores(AllCoursesData* data, CourseDataExtended* extendedData, int lengthData, int lengthExtended, int courseCode) {
    float totalGeneral = 0;
    float totalCE = 0;
    int count = 0;

    for (int i = 0; i < lengthData; i++) {
        if (extendedData[i].CO_CURSO == courseCode) {
            printf("NT_GER: %f | NT_CE: %f\n", extendedData[i].NT_GER, extendedData[i].NT_CE);
            totalGeneral += extendedData[i].NT_GER;
            totalCE += extendedData[i].NT_CE;
            count++;
        }
    }
    
    if (count > 0) {
        printf("Média NT_GER: %f | Média NT_CE: %f\n", totalGeneral / count, totalCE / count);
    }
}

int compareScores(const void* a, const void* b) {
    float diff = ((ScoreData*)b)->score - ((ScoreData*)a)->score;
    return (diff > 0) - (diff < 0);
}

void topNScores(AllCoursesData* data, CourseDataExtended* extendedData, int lengthData, int lengthExtended, int n, int isGeneral) {
    ScoreData* scores = malloc(lengthExtended * sizeof(ScoreData));

    for (int i = 0; i < lengthExtended; i++) {
        scores[i].score = isGeneral ? extendedData[i].NT_GER : extendedData[i].NT_CE;
        scores[i].courseCode = extendedData[i].CO_CURSO;
        scores[i].ies = -1;

        for (int j = 0; j < lengthData; j++) {
            if (data[j].CO_CURSO == extendedData[i].CO_CURSO) {
                scores[i].ies = data[j].CO_IES;
                break;
            }
        }
    }

    qsort(scores, lengthExtended, sizeof(ScoreData), compareScores);

    for (int i = 0; i < n && i < lengthExtended; i++) {
        printf("Nota: %f | Curso: %d | IES: %d\n", scores[i].score, scores[i].courseCode, scores[i].ies);
    }

    free(scores);
}

int main() {
    loadAllCoursesData();
    loadCourseExtendedData();

    int choice, code, ies, uf, group, n;

    do {
        printf("\nOpções:\n");
        printf("1. Procurar um curso específico\n");
        printf("2. Listar cursos por IES\n");
        printf("3. Listar cursos por unidade da federação\n");
        printf("4. Listar cursos por área de enquadramento (grupo)\n");
        printf("5. Listar e calcular médias das notas\n");
        printf("6. Mostrar as 'n' maiores notas\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite o código do curso: ");
                scanf("%d", &code);
                findCourse(code);
                break;
            case 2:
                printf("Digite o código da IES: ");
                scanf("%d", &ies);
                listByIES(ies);
                break;
            case 3:
                printf("Digite o código da UF: ");
                scanf("%d", &uf);
                listByUF(uf);
                break;
            case 4:
                printf("Digite o código do grupo: ");
                scanf("%d", &group);
                listByGroup(group);
                break;
            case 5:
                printf("Digite o código do curso: ");
                scanf("%d", &code);
                listAndAverageScores(allCoursesData, courseDataExtended, totalCoursesData, totalDataExtended, code);
                break;
            case 6:
                printf("Digite a quantidade de notas a serem mostradas: ");
                scanf("%d", &n);
                printf("Para qual nota você deseja ver o top N? (1 para NT_GER, 2 para NT_CE): ");
                int type;
                scanf("%d", &type);
                topNScores(allCoursesData, courseDataExtended, totalCoursesData, totalDataExtended, n, type == 1);
                break;
            case 7:
                printf("Encerrando programa.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (choice != 7);

    free(allCoursesData);
    free(courseDataExtended);
    return 0;
}