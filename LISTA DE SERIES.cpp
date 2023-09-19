#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_SERIES 100

struct Serie {
    int id;
    char nome[50];
    int temporada;
    int episodio;
    int tempo;
};

struct Serie series[MAX_SERIES];
int totalSeries = 0;

void salvarSeries() {
    FILE *arquivo = fopen("series.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar as s�ries.\n");
        return;
    }

    for (int i = 0; i < totalSeries; i++) {
        fprintf(arquivo, "%d|%s|%d|%d|%d\n", series[i].id, series[i].nome, series[i].temporada, series[i].episodio, series[i].tempo);
    }

    fclose(arquivo);
}

void carregarSeries() {
    FILE *arquivo = fopen("series.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo de s�ries n�o encontrado. Criando um novo arquivo.\n");
        return;
    }

    while (!feof(arquivo) && totalSeries < MAX_SERIES) {
        struct Serie novaSerie;
        fscanf(arquivo, "%d|%49[^|]|%d|%d|%d\n", &novaSerie.id, novaSerie.nome, &novaSerie.temporada, &novaSerie.episodio, &novaSerie.tempo);
        series[totalSeries++] = novaSerie;
    }

    fclose(arquivo);
}

void ListarSeries() {
	system ("cls");
    printf("\n\tLISTA DE S�RIES\n");
    printf("| %3s | %-36s | %-10s | %-7s | %-7s |\n", "Id", "Nome", "Temporada", "Epis�dio", "Tempo");
    printf("------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < totalSeries; i++) {
        printf("| %3d | %-36s | %-10d | %-7d | %-7d |\n", series[i].id, series[i].nome, series[i].temporada, series[i].episodio, series[i].tempo);
    }
}

void CadastrarSerie() {
	system ("cls");
    if (totalSeries >= MAX_SERIES) {
        printf("A lista de s�ries est� cheia.\n");
        return;
    }

    struct Serie novaSerie;
    novaSerie.id = totalSeries + 1;

    printf("Digite o nome da s�rie: ");
    scanf(" %49[^\n]", novaSerie.nome);

    printf("Digite a Temporada: ");
    scanf("%d", &novaSerie.temporada);

    printf("Digite o epis�dio: ");
    scanf("%d", &novaSerie.episodio);

    printf("Digite o tempo da s�rie: ");
    scanf("%d", &novaSerie.tempo);

    series[totalSeries++] = novaSerie;
    printf("S�rie cadastrada com sucesso!\n");
}

void EditarSerie() {
	system ("cls");
	
	if (totalSeries == 0) {
		printf("A lista de s�ries est� vazia.\n");
		return;
	}
	
	int idEditar;
	printf("Digite o ID da s�rie que deseja editar: ");
	scanf("%d", &idEditar);
	
	int seriesEncontrada = 0;
	
	for (int i = 0; i < totalSeries; i++) {
		if (series[i].id == idEditar) {
			printf("Digite o novo nome da s�rie: ");
			scanf(" %49[^\n]", series[i].nome);
			
			printf("Digite a nova temporada da s�rie: ");
			scanf("%d", &series[i].temporada);
			
			printf("Digite o novo epis�dio da s�rie: ");
			scanf("%d", &series[i].episodio);
			
			printf("Digite o novo Tempo da s�rie: ");
			scanf("%d", &series[i].tempo);
			
			printf("S�rie editada com sucesso!\n");
			seriesEncontrada = 1;
			break;
		}
		
	}
	if (!seriesEncontrada) {
		printf("S�rie com o ID %d n�o encontado.\n", idEditar);
	}
}

void ExcluirSerie() {
	system ("cls");
    if (totalSeries == 0) {
        printf("A lista de s�ries est� vazia.\n");
        return;
    }

    int idExcluir;
    printf("Digite o ID da s�rie que deseja excluir: ");
    scanf("%d", &idExcluir);

    int serieEncontrada = 0;

    for (int i = 0; i < totalSeries; i++) {
        if (series[i].id == idExcluir) {
            for (int j = i; j < totalSeries - 1; j++) {
                series[j] = series[j + 1];
            }

            totalSeries--;
            printf("S�rie exclu�da com sucesso!\n");
            serieEncontrada = 1;
            break;
        }
    }

    if (!serieEncontrada) {
        printf("S�rie com o ID %d n�o encontrada.\n", idExcluir);
    }
}

void MenuPrincipal() {
	system ("cls");
    int escolha;

    do {
        printf("\nMENU PRINCIPAL\n");
        printf("1 - Listar s�ries\n");
        printf("2 - Cadastrar s�rie\n");
        printf("3 - Excluir s�rie\n");
        printf("4 - Editar S�rie\n");
        printf("5 - Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                ListarSeries();
                break;
            case 2:
                CadastrarSerie();
                break;
            case 3:
                ExcluirSerie();
                break;
            case 4:
                EditarSerie();
                break;
            case 5:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (escolha != 5);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    carregarSeries();

    MenuPrincipal();

    salvarSeries();

    return 0;
}

