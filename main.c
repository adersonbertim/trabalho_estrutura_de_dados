#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5 // tá tudo utilizando o max como parametro, ent se quiser mais perfis e posts é só aumentar, mas aí vai ser 5 post e 5 perfil

typedef struct {
    char postagens[MAX][51];
    int topo;
} Posts;

typedef struct {
    char nome[30];
    char senha[9];           //cada perfil tem nome senha e uma PILHA, essa pilha é a dos post
    Posts postagens;
} Perfil;

// função para inicializar as postagens, aparentemente toda pilha precisa disso, só por causa do topo
Posts inicializarPosts() {
    Posts p;
    p.topo=0;
    return p;
}

// função para criar um perfil, já pede o nome e a senha
Perfil criarPerfil() {
    Perfil p;
    printf("digite o nome do perfil: ");
    scanf(" %s", p.nome);
    getchar();
// faz a senha obrigatoriamente ter os 8 digitos, pra evitar erro, é mais facil só forçar sempre ser 8 msm
    int senhaValida = 0;
    while (!senhaValida){
        printf("digite sua senha (8 digitos): ");
        scanf(" %s", p.senha);
        getchar();
        if (strlen(p.senha) == 8){
            senhaValida = 1;
        }else{
            printf("a senha deve conter exatamente 8 caracteres\n");
        }
    }

    p.postagens=inicializarPosts();
    return p;
}

// função para adicionar um post
Posts adicionarPost(Posts p){
    //verifica se a pilha de post ta cheia, só compara se o topo ta no  limite do MAX
    if (p.topo>=MAX) {
        printf("limite de posts alcançado\n");
        return p;
    }
    int postvalido = 0;
    while (!postvalido){
        
        printf("escreva o post: ");
        scanf(" %s", p.postagens[p.topo]); // %50 é pro post n passar de 50 char. Limite de leitura para evitar buffer overflow
        getchar();

        if (strlen(p.postagens[p.topo]) > 50){
            printf("o post deve conter no max 50 caracteres\n");
        }else{
            postvalido = 1;
        }
    }

    p.topo++;
    return p;
}

// função para remover um post
Posts removerPost(Posts p) {
    if (p.topo<=0){ // msm logica do topo
        printf("nao ha posts\n");
        return p;
    }
    p.topo--;
    strcpy(p.postagens[p.topo], ""); // Limpa o último post, preenche com espaços vazios
    return p;
}

// função para mostrar posts
void mostrarPosts(Posts p) {
    if (p.topo==0){ // se o topo n mudou é pq ta em zero, ou seja, vazio
        printf("nenhum post\n");
        return;
    }
    printf("posts:\n"); // printa tds os post
    for (int i=p.topo-1; i>=0; i--) {
        printf("--%s\n", p.postagens[i]);
    }
}
// função para mostrar os perfis 
void mostrarPerfis(Perfil perfis[], int totalPerfis){
    /* os parametros q entram sao os perfis da pilha de perfil geral(totalperfis) e os perfis de dentro da pilha(perfis)
    perfil perfis é só a declaração que vai entrar algo desse tipo na função, ent oq ta entrando é um perfil[perfilAtual]
    */
    if (totalPerfis==0){ 
        printf("nenhum perfil cadastrado.\n");
        return;
    }

    printf("\nperfis cadastrados:\n");
    for (int i=0; i<totalPerfis; i++) {
        printf("%d) %s\n", i + 1, perfis[i].nome);
    }
}

int escolherPerfil(Perfil perfis[], int totalPerfis){// msm logica do de cima
    if (totalPerfis==0) {
        printf("nenhum perfil cadastrado.\n");
        return -1; // Indica que não há perfis disponíveis pq é o topo do bagulho abaixo do 0
    }

    printf("\nescolha um perfil:\n");
    for (int i = 0; i<totalPerfis; i++){
        printf("%d) %s\n", i + 1, perfis[i].nome); 
    }

    int escolha;
    printf("\ndigite o numero do perfil: ");
    scanf(" %d", &escolha);
    getchar();
    if (escolha<1 || escolha>totalPerfis){
        printf("opcao invalida\n");
        return -1; 
    }

    return escolha - 1; // retorna com menos um pra bater nos indices do bagulho, por causa do topo, pq aí o indice 0 pode ser modificado 
}
int postsEstaoCheios(Posts p){
    return (p.topo>=MAX);
}

int verificarsenha(char senha[]){
    char x[9];// tem q ser um a mais só pra garantir q n vai dar erro msm
    printf("digite a senha: ");
    scanf(" %8s", x); //sei la pq tem um errinho aq, mas ta funçando ent n tem problema
    getchar();
    if(strcmp(senha,x)==0){//strcmp pra comparar as strings
        return 1;
    }else{
        return 0;
    }
}


int main() {
    Perfil perfis[MAX];
    int opcao;
    int perfilAtual=0;
    int princ=0;
    while(princ!=2) {
        printf("\n-----------\no que deseja fazer?\n1) criar perfil\n2) encerrar \n3) login\n4) ver posts\n-----------  ");
        scanf(" %d", &opcao);
        getchar();

        if(opcao==1){
            if (perfilAtual>=MAX){
                printf("limite de perfis atingido.\n");
                break;
            }
            perfis[perfilAtual]=criarPerfil();//o indice atual da pilha de perfis recebe a criação de um perfil, tipo (pilha de perfil no indice 0) = peril criado na função
            perfilAtual++; //aumenta o indice, sobe a pilha geral de perfis
            

        } else if (opcao==2){// fecha o programa
            break;


        } else if (opcao==3){

    int indicePerfil=escolherPerfil(perfis, perfilAtual); /*escolhe o perfil para realizar o login, passa como parametro a pilha geral de perfis e o atual
                                                          aí o indiceperfil fica com o perfil atual*/
    
    if (indicePerfil==-1){// se n tiver nenhum perfil cadastrado o topo vai ta no 0 e o indice vai ser -1, etn entra nesse if aqui
        printf("\nnao foi possivel selecionar um perfil.\n");
        continue;
    }

    if(!verificarsenha(perfis[indicePerfil].senha)){ //verfifica se a senha ta errada, percebam o ! na condição do if
        printf("\nsenha incorreta\n");
        continue;
    }

    char resposta='s';
    while(resposta!='n' && resposta!='N'){
        if(postsEstaoCheios(perfis[indicePerfil].postagens)){//pega a pilha do perfil atual pra testar se ta cheia
            printf("nao e possivel adicionar mais posts\n");
            printf("\ndeseja excluir ultimo post para postar de novo? (s/n): ");//caso estiver cheio ele pergunta se quer excluir o ultimo post pq se não n da mais pra entrar no perfil,mas aí ele pergunta duas vezes se quer excluir post mas fds
            scanf(" %c", &resposta);
            getchar();
            if (resposta=='s'||resposta=='S'){
            perfis[indicePerfil].postagens=removerPost(perfis[indicePerfil].postagens);
            }
            break;
        }
    printf("\n%s deseja postar? (s/n): ", perfis[indicePerfil].nome);
    
    scanf(" %c", &resposta);
    getchar();
    if(resposta=='n'||resposta=='N'){
        break;
    }
    perfis[indicePerfil].postagens=adicionarPost(perfis[indicePerfil].postagens);// chama a função de adicionar post na pilha de post do perfil atual
    
}
  
    resposta='n';
    if (!postsEstaoCheios(perfis[indicePerfil].postagens)){//testa se a pilha de post ta cheia, percebe o !, pq é o msm de cima
        printf("\ndeseja excluir ultimo post? (s/n): ");
        scanf(" %c", &resposta);
        getchar();
        if (resposta=='s'||resposta=='S'){
        perfis[indicePerfil].postagens=removerPost(perfis[indicePerfil].postagens);
        }
        
    }

}else if(opcao==4){
    if(perfilAtual==0){
        printf("\nnao tem perfis cadastrados \t");
    }else{
    int resposta;
        printf("\ndeseja ver os posts qual perfil? ");
        mostrarPerfis(perfis, perfilAtual);
        scanf(" %d", &resposta);
        getchar();
            mostrarPosts(perfis[resposta-1].postagens);}
}else {
            printf("opcao invalida.\n");
        }
    }


    

    return 0;
}