#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5 

// Definido como MAX, esse valor limita o número de posts e perfis. Para aumentar a quantidade de perfis ou posts, basta ajustar esse valor.

typedef struct {
    char postagens[MAX][51]; 
    // Armazena as postagens, com limite de 50 caracteres por post.
    int topo; 
    // Indica a posição atual na pilha de postagens.
} Posts;

// Cada perfil possui nome, senha e uma pilha de postagens associada.
typedef struct {
    char nome[30]; 
    char senha[9]; 
    Posts postagens; // Pilha de postagens associada ao perfil.
} Perfil;

// Função para inicializar as postagens. A pilha precisa ser inicializada com o topo em 0.
Posts inicializarPosts() {
    Posts p;
    p.topo = 0; // Inicializa o topo da pilha.
    return p;
}

// Função para criar um perfil. Solicita o nome e a senha do usuário.
Perfil criarPerfil() {
    Perfil p;
    printf("Digite o nome do perfil: ");
    scanf(" %s", p.nome);
    getchar();

    // A senha deve ter exatamente 8 dígitos. Se não for válida, solicita novamente.
    int senhaValida = 0;
    while (!senhaValida){
        printf("Digite sua senha (8 digitos): ");
        scanf(" %s", p.senha);
        getchar();
        if (strlen(p.senha) == 8){
            senhaValida = 1;
        } else {
            printf("A senha deve conter exatamente 8 caracteres\n");
        }
    }

    p.postagens = inicializarPosts(); // Inicializa a pilha de postagens.
    return p;
}

// Função para adicionar um post. Verifica se a pilha de postagens está cheia antes de adicionar.
Posts adicionarPost(Posts p){
    if (p.topo >= MAX) { // Verifica se a pilha de postagens atingiu o limite.
        printf("Limite de posts alcançado\n");
        return p;
    }

    int postvalido = 0;
    while (!postvalido){
        printf("Escreva o post: \n");
        scanf(" %50s", p.postagens[p.topo]); // Limita o post a 50 caracteres para evitar buffer overflow.
        getchar();

        if (strlen(p.postagens[p.topo]) > 50){
            printf("O post deve conter no máximo 50 caracteres\n");
        } else {
            postvalido = 1;
        }
    }

    p.topo++; // Incrementa o topo após adicionar o post.
    return p;
}

// Função para remover o último post. Se a pilha estiver vazia, não faz nada.
Posts removerPost(Posts p) {
    if (p.topo <= 0){ // Verifica se a pilha de postagens está vazia.
        printf("Não há posts para remover.\n");
        return p;
    }

    p.topo--; // Decrementa o topo para "remover" o post.
    strcpy(p.postagens[p.topo], ""); // Limpa o conteúdo do último post.
    return p;
}

// Função para mostrar todos os posts. Se não houver posts, exibe uma mensagem.
void mostrarPosts(Posts p) {
    if (p.topo == 0){
        printf("Nenhum post.\n");
        return;
    }

    printf("Posts:\n");
    for (int i = p.topo - 1; i >= 0; i--) { // Exibe os posts do topo até o fundo da pilha.
        printf("--%s\n", p.postagens[i]);
    }
}

// Função para mostrar todos os perfis cadastrados. Se não houver perfis, exibe uma mensagem.
void mostrarPerfis(Perfil perfis[], int totalPerfis){
    if (totalPerfis == 0){ 
        printf("Nenhum perfil cadastrado.\n");
        return;
    }

    printf("\nPerfis cadastrados:\n");
    for (int i = 0; i < totalPerfis; i++) {
        printf("%d) %s\n", i + 1, perfis[i].nome); // Exibe o nome de cada perfil.
    }
}

// Função para escolher um perfil. Retorna o índice do perfil escolhido ou -1 se não houver perfis.
int escolherPerfil(Perfil perfis[], int totalPerfis){
    if (totalPerfis == 0) {
        printf("Nenhum perfil cadastrado.\n");
        return -1; 
    }

    printf("\nEscolha um perfil:\n");
    for (int i = 0; i < totalPerfis; i++){
        printf("%d) %s\n", i + 1, perfis[i].nome); // Exibe os perfis para escolha.
    }

    int escolha;
    printf("\nDigite o número do perfil: ");
    scanf(" %d", &escolha);
    getchar();
    if (escolha < 1 || escolha > totalPerfis){ // Valida a escolha.
        printf("Opção inválida\n");
        return -1; 
    }

    return escolha - 1; // Retorna o índice do perfil escolhido (ajustado para zero-base).
}

// Função para verificar se a pilha de postagens está cheia.
int postsEstaoCheios(Posts p){
    return (p.topo >= MAX); // Retorna 1 se a pilha estiver cheia, 0 caso contrário.
}

// Função para verificar se a senha fornecida corresponde à senha do perfil.
int verificarsenha(char senha[]){
    char x[9]; // Buffer para garantir a segurança na leitura da senha.
    printf("Digite a senha: ");
    scanf(" %8s", x); 
    getchar();
    if (strcmp(senha, x) == 0) { 
        return 1;
    } else {
        return 0; 
    }
}

int main() {
    Perfil perfis[MAX]; // Array para armazenar os perfis.
    int opcao, perfilAtual = 0; // Variáveis para controle de opções e perfil atual.
    char resposta;

    while (1) {
        printf("\n-----------\nO que deseja fazer?\n1) Criar perfil\n2) Encerrar \n3) Login\n4) Ver posts\n-----------\n");
        scanf(" %d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                if (perfilAtual >= MAX) {
                    printf("Limite de perfis atingido.\n");
                    break;
                }
                perfis[perfilAtual] = criarPerfil(); // Cria o perfil e o armazena.
                perfilAtual++; // Incrementa o índice para o próximo perfil.
                break;

            case 2:
                return 0; // Encerra o programa.

            case 3: {
                int indicePerfil = escolherPerfil(perfis, perfilAtual);
                if (indicePerfil == -1) {
                    printf("\nNão foi possível selecionar um perfil.\n");
                    continue;
                }

                if (!verificarsenha(perfis[indicePerfil].senha)) {
                    printf("\nSenha incorreta.\n");
                    continue;
                }

                // Fluxo para o usuário adicionar ou excluir posts.
                while (1) {
                    if (postsEstaoCheios(perfis[indicePerfil].postagens)) {
                        printf("Não é possível adicionar mais posts.\n");
                        printf("\nDeseja excluir o último post para postar de novo? (s/n): ");
                        scanf(" %c", &resposta);
                        getchar();
                        if (resposta == 's' || resposta == 'S') {
                            perfis[indicePerfil].postagens = removerPost(perfis[indicePerfil].postagens);
                        }
                        break;
                    }

                    printf("\n%s, Deseja postar? (S/N): ", perfis[indicePerfil].nome);
                    scanf(" %c", &resposta);
                    getchar();
                    if (resposta == 'n' || resposta == 'N') break;

                    perfis[indicePerfil].postagens = adicionarPost(perfis[indicePerfil].postagens);
                }

                // Opção de excluir o último post.
                if (!postsEstaoCheios(perfis[indicePerfil].postagens)) {
                    printf("\nDeseja excluir o último post? (S/N): ");
                    scanf(" %c", &resposta);
                    getchar();
                    if (resposta == 's' || resposta == 'S') {
                        perfis[indicePerfil].postagens = removerPost(perfis[indicePerfil].postagens);
                    }
                }
                break;
            }

            case 4:
                if (perfilAtual == 0) {
                    printf("\nNão há perfis cadastrados.\n");
                } else {
                    int resposta;
                    printf("\nDeseja ver os posts de qual perfil? ");
                    mostrarPerfis(perfis, perfilAtual);
                    scanf(" %d", &resposta);
                    getchar();
                    if (resposta >= 1 && resposta <= perfilAtual) {
                        mostrarPosts(perfis[resposta - 1].postagens);
                    } else {
                        printf("Opção inválida.\n");
                    }
                }
                break;

            default:
                printf("Opção inválida.\n");
                break;
        }
    }

    return 0;
}
