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
    char link[256];
};

struct Serie series[10];
int totalSeries = 0;

void AbrirLink(int id) {
	system("cls");
	
	if (id < 1 || id > totalSeries){
		printf("ID da Série invalido.\n");
		return;
	}
	printf("Abrindo link para a série: %s\n", series[id - 1].nome);
	printf("Link: %s\n", series[id - 1].link);
	
	char comando[512];
	snprintf(comando, sizeof(comando), "start %s", series[id - 1].link);
	system(comando);
}

void salvarSeries() {
    FILE *arquivo = fopen("series.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar as séries.\n");
        return;
    }

    for (int i = 0; i < totalSeries; i++) {
        fprintf(arquivo, "%d|%s|%d|%d|%s\n", series[i].id, series[i].nome, series[i].temporada, series[i].episodio, series[i].link);
    }

    fclose(arquivo);
}

void carregarSeries() {
FILE *arquivo = fopen("series.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo de séries não encontrado. Criando um novo arquivo.\n");
        return;
    }

    while (totalSeries < 10) {
        struct Serie novaSerie;
        int camposLidos = fscanf(arquivo, "%d|%49[^|]|%d|%d|%255[^|\n]\n", &novaSerie.id, novaSerie.nome, &novaSerie.temporada, &novaSerie.episodio, novaSerie.link);

        if (camposLidos != 5) {
            break;
        }

        int serieExistente = 0;
        for (int i = 0; i < totalSeries; i++) {
            if (novaSerie.id == series[i].id) {
                serieExistente = 1;
                break;
            }
        }

        if (!serieExistente) {
            series[totalSeries++] = novaSerie;
        }
    }

    fclose(arquivo);
}

void ListarSeries() {
	system ("cls");
    printf("\n\tLISTA DE SÉRIES\n");
    printf("| %3s| %-36s| %-10s| %-7s| %-20s|\n", "Id", "Nome", "Temporada", "Episódio", "Link");
    printf("------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < totalSeries; i++) {
        printf("| %3d| %-36s| %-10d| %-7d| %-20s|\n", series[i].id, series[i].nome, series[i].temporada, series[i].episodio, series[i].link);
    }
}

void CadastrarSerie() {
	system ("cls");
    if (totalSeries >= 10) {
        printf("A lista de séries está cheia.\n");
        return;
    }

    struct Serie novaSerie;
    novaSerie.id = totalSeries + 1;

    printf("Digite o nome da série: ");
    scanf(" %49[^\n]", novaSerie.nome);

    printf("Digite a Temporada: ");
    scanf("%d", &novaSerie.temporada);

    printf("Digite o episódio: ");
    scanf("%d", &novaSerie.episodio);

    printf("Digite o link da série: ");
    scanf(" %255[^\n]", &novaSerie.link);

    series[totalSeries++] = novaSerie;
    printf("Série cadastrada com sucesso!\n");
}

void EditarSerie() {
    system("cls");
    if (totalSeries == 0) {
        printf("A lista de séries está vazia.\n");
        return;
    }

    int idEditar;
    printf("Digite o ID da série que deseja editar: ");
    scanf("%d", &idEditar);

    int serieEncontrada = 0;

    for (int i = 0; i < totalSeries; i++) {
        if (series[i].id == idEditar) {
            printf("Série encontrada:\n");
            printf("ID: %d\n", series[i].id);
            printf("Nome: %s\n", series[i].nome);
            printf("Temporada: %d\n", series[i].temporada);
            printf("Episódio: %d\n", series[i].episodio);
            printf("Link: %s\n", series[i].link);

	printf("------------------------------------------------------------------------------------------------------\n");

            printf("Deseja editar este campo?\n");
            printf("1 - Nome\n");
            printf("2 - Temporada\n");
            printf("3 - Episódio\n");
            printf("4 - Link\n");
            printf("5 - Cancelar\n");
            int escolha;
            scanf("%d", &escolha);

            switch (escolha) {
                case 1:
                    printf("Digite o novo nome da série: ");
                    scanf(" %49[^\n]", series[i].nome);
                    break;
                case 2:
                    printf("Digite a nova temporada da série: ");
                    scanf("%d", &series[i].temporada);
                    break;
                case 3:
                    printf("Digite o novo episódio da série: ");
                    scanf("%d", &series[i].episodio);
                    break;
                case 4:
                    printf("Digite o novo link da série: ");
                    scanf(" %255[^\n]", series[i].link);
                    break;
                case 5:
                    printf("Edição cancelada.\n");
                    break;
                default:
                    printf("Opção inválida. Tente novamente.\n");
            }

            printf("Série editada com sucesso!\n");
            serieEncontrada = 1;
            break;
        }
    }

    if (!serieEncontrada) {
        printf("Série com o ID %d não encontrada.\n", idEditar);
    }
}


void ExcluirSerie() {
	system ("cls");
    if (totalSeries == 0) {
        printf("A lista de séries está vazia.\n");
        return;
    }

    int idExcluir;
    printf("Digite o ID da série que deseja excluir: ");
    scanf("%d", &idExcluir);

    int serieEncontrada = 0;

    for (int i = 0; i < totalSeries; i++) {
        if (series[i].id == idExcluir) {
            for (int j = i; j < totalSeries - 1; j++) {
                series[j] = series[j + 1];
            }

            totalSeries--;
            printf("Série excluída com sucesso!\n");
            serieEncontrada = 1;
            break;
        }
    }

    if (!serieEncontrada) {
        printf("Série com o ID %d não encontrada.\n", idExcluir);
    }
}

void MenuPrincipal() {
	system ("cls");
    int escolha;

    do {
        printf("\nMENU PRINCIPAL\n");
        printf("1 - Listar séries\n");
        printf("2 - Cadastrar série\n");
        printf("3 - Excluir série\n");
        printf("4 - Editar Série\n");
        printf("5 - Abrir link da série\n");
        printf("6 - Sair\n");
        printf("Escolha uma opção: ");
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
                printf("Digite o ID da série para abrir o link: ");
                int id;
                scanf("%d", &id);
                AbrirLink(id);
                break;
            case 6:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 6);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    carregarSeries();

    MenuPrincipal();

    salvarSeries();

    return 0;
}

