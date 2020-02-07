/*#########################################################################################
  # Universidade de Brasilia                                                              #
  # Instituto das ciencias exatas                                                         #
  # Departamento de Ciencia da Computacao                                                 #
  # Algoritimos e Programacao de Computadores - 1/2019                                    #
  # Aluno: <Gabriel Faustino Lima da Rocha>                                               #
  # Matricula: <19/0013249>                                                               #
  # Turma: A                                                                              #  
  # Versao do compilador:<C99>                                                            #
  # Descricao: <O programa é um jogo booble shooter cujo objetivo é juntar 4 ou mais      #
  # pecas iguais que irao estourar caso isso ocorra, o tabuleiro desce a    cada  20      #
  # segundos e é posivel mexer a mira com as teclas 'A' e 'D'>                            #
  #########################################################################################
*/
#define _XOPEN_SOURCE 500

#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<termios.h>
#include<fcntl.h>
#include<time.h>
#ifndef _WIN32
int kbhit(){
  struct termios oldt, newt;
  int ch, oldf;
  tcgetattr(STDIN_FILENO,&oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  if(ch != EOF){
    ungetc(ch,stdin); 
    return 1;
  }
  return 0;
}
int getch(void) {
  int ch;
  struct termios oldt;
  struct termios newt;
  tcgetattr(STDIN_FILENO,&oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}
#else
  #include <conio.h>
#endif

#define CLEAR "clear"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
char tabuleiro[10][17], tabuleiro_teste[10][17];//o tabuleiro teste esta explicado na funcao checar
int altura = 9, largura = 16;
char p; //letra que vai ser lancada
int tempo = 0, pontuacao, tempo_comparador = 0; //tempo de jogo decorrido, potuacao total do jogador, compara com o tempo atual na hora de descer o tabuleiro para evitar dele descer de uma vez
int velocidade  = 60, k = 0;//k é usada na funcao de eplodir e sera melhor explicada na funcao checar
int pecas = 4; //salva o numero de pecas necessarias para explodir
int ranqueado = 0; // determina se o modo ranqueado esta ativo, 0 = desativado, 1 = ativado
float angulo = 0;//variavel do coeficiente angular da reta
void menu();
void printar_tabuleiro();
void checar();
void mira();
int cair();

void instrucoes(){//instrucoes do jogo
  int x = 0;
  system(CLEAR);
  printf("1- use a tecla A para mover a mira para a esquerda.\n2- usa a tela D para mover a mira para a direita.\n3- atire a letra com a barra de espaco.\n4- a combinacao de 4 ou mais letras iguais ira estourar as letras e lhe dar pontos correspondentemente ao numero de letras estouradas.\n5- a cada 20 segundos o tabuleiro ira descer uma casa\n");
  printf("Pressione 1 para voltar ao menu.");
  do{
    x = getch();
    if(x == '1'){
      menu();
    }
  } while(x != '1');
}

void perdeu(){//funcao que declara se o jogador perdeu ou nao
  int j, x = 0;
  for(j = 1; j < 15;j++){
    if((tabuleiro[1][j] != ' ' && tabuleiro[1][j] != p && tabuleiro[1][j]!='-') || (tabuleiro[2][8] != ' ' && tabuleiro[2][8] != '-')){
      system(CLEAR);
      printf("voce perdeu, sua pontuacao foi de %d\n", pontuacao);
      printf("precione enter para voltar ao menu principal");
      while(x != '\n'){
        x = getch();
        if(x == '\n'){
          menu();
        }
        else{
          perdeu();
        }
      }
    }
  }
}

void gerarpeca(){
  // pega o mod do rand e soma 'A' pra saber qual letra usar
  int letra;
  letra = rand()%5;
  p = 'A' + letra;
}

void atirar_animacao(){//animacao da peca sendo atirada
  int i, j, aux = 8, altura_peca;// aux serve para guardar o valor de j que q contém o'-', altura_peca vai ser usada na funcao de checar uam possivel explosao
  for(i = 2;i <= 7; i++){
    for(j = 1;j < 15;j++){
      if(tabuleiro[i-1][aux] == p && tabuleiro[i][j] == '-'){
        tabuleiro[i-1][aux] = '-';
      }
      if(tabuleiro[i][j] == '-'){
        tabuleiro[i][j] = p;
        aux = j;
        altura_peca = i;
      }
    }
    usleep(30000);
    printar_tabuleiro();
  }
  for(i = 0;i <= altura;i++){//faz o tabuleiro teste ficar igual o tabuleiro real antes de usa-lo nas funcoes
    for(j = 0;j <= largura; j++){
      tabuleiro_teste[i][j] = tabuleiro[i][j];
    }
    printf("\n");
  }
  checar(aux,altura_peca);//aqui ele checa se pode fazer uma explosao
   if(k >= 4){// se houver mais de 4 letras iguais juntas, ocorrera uma explosao;
    pontuacao += k*10;
    for(i = 2;i < altura - 1;i++){
      for(j = 1;j <= largura - 1; j++){
        tabuleiro[i][j] = tabuleiro_teste[i][j];
      }
    }
    printar_tabuleiro();
    usleep(60000);
    for(i = 2;i < altura-1;i++){//serve tanto pra trocar os * por ' ' como para verificar se nao ha nenhuma peca flutuando
      for(j = 1;j < largura - 1; j++){
        if(tabuleiro[i][j] == '*'){
          tabuleiro[i][j] = ' ';
        }
        if(cair(i, j) == 0){
          if(tabuleiro[i][j] == 'A' || tabuleiro[i][j] == 'B' || tabuleiro[i][j] == 'C' || tabuleiro[i][j] == 'D' || tabuleiro[i][j] == 'E'){
            pontuacao += 10;
          }
          tabuleiro[i][j] = ' ';
        }
      }
    }
    mira();
  }
  k = 0;
  gerarpeca();
  tabuleiro[1][8] = p;
  printar_tabuleiro();
  perdeu();
}

void gera_tabuleiro(){
  int i, j;
  // funcao para gerar a matriz pela primeira vez na partida, tambem reseta a matriz ao iniciar outra partida na mesma execucao do programa
  for(i = 0;i < altura;i++){
    for(j = 0;j < largura; j++){
      tabuleiro[i][j]=' ';
      if(i == 0 || i == 8){
        tabuleiro[i][j] = '#';
      }
      else if(j == 0 || j == 15){
        tabuleiro[i][j] = '#';
      }
      else if(tabuleiro[i][j] != '#'){
        tabuleiro[i][j] = ' ';
      }
    }
  }
}

void checar(int coordenada_x, int coordenada_y){
  // funcao que vai detectar se um conjunto de pecas pode explodir toda vez q uma peca é atirada
  //k é o numero de vezes que a funcao foi chamada e encontrou uma letra
  // O tabuleiro_teste armazena o tabuleiro para testar a explosao e armazenar um * nas pecas ja testadas
  if(p == tabuleiro_teste[coordenada_y][coordenada_x]){
    k++;
    tabuleiro_teste[coordenada_y][coordenada_x] = '*';
    checar(coordenada_x, coordenada_y - 1);
    checar(coordenada_x, coordenada_y + 1);
    checar(coordenada_x - 1, coordenada_y + 1);
    checar(coordenada_x - 1, coordenada_y - 1);
    checar(coordenada_x - 1, coordenada_y);
    checar(coordenada_x + 1, coordenada_y + 1);
    checar(coordenada_x + 1, coordenada_y - 1);
    checar(coordenada_x + 1, coordenada_y);
  }
}

int cair(int i, int j){
  int x = 0;
  //funcao chamada apos uma explosao que checa todas as pecas e remove pecas flutuantes
  // se x for igual a zero quer dizer q a peca nao esta conectada na parede se for igual a 1 ela esta e a funcao acaba
  if(tabuleiro_teste[i][j] == 'A' || tabuleiro_teste[i][j] == 'B' || tabuleiro_teste[i][j] == 'C' || tabuleiro_teste[i][j] == 'D' || tabuleiro_teste[i][j] == 'E'){
    x = cair(i + 1, j + 1);
    if(x == 1){
      return x;
      tabuleiro_teste[i][j] = 'L';
    }
    x = cair(i + 1, j - 1);
        if(x == 1){
      return x;
      tabuleiro_teste[i][j] = 'L';
    }
    x = cair(i + 1, j);
       if(x == 1){
      return x;
      tabuleiro_teste[i][j] = 'L';
    }
    x = cair(i, j - 1);
      if(x == 1){
      return x;
      tabuleiro_teste[i][j] = 'L';
    }
    x = cair(i, j + 1);
      if(x == 1){
      return x;
      tabuleiro_teste[i][j] = 'L';
    }
    x = cair(i - 1, j + 1);
    if(x == 1){
      return x;
      tabuleiro_teste[i][j] = 'L';
    }
    x = cair(i - 1, j - 1);
       if(x == 1){
      return x;
      tabuleiro_teste[i][j] = 'L';
    }
    x = cair(i - 1, j);
       if(x == 1){
      return x;
      tabuleiro_teste[i][j] = 'L';
    }
  }
  else if(tabuleiro[i][j] == '#' ||tabuleiro[i][j] == 'L'){
    return 1;
  }
  return 0;
}

void printar_tabuleiro(){//printa o tabuleiro
  int i,j; // i = altura, j = largura
  system(CLEAR);
  for(i = altura - 1;i >= 0;i--){
    for(j = largura - 1;j >= 0; j--){
      switch(tabuleiro[i][j]){
        case 'A':
          printf(MAGENTA "%c" RESET, tabuleiro[i][j]);
          break;
        case 'B':
          printf(GREEN "%c" RESET, tabuleiro[i][j]);
          break;
        case 'C':
          printf(BLUE "%c" RESET, tabuleiro[i][j]);
          break;
        case 'D':
          printf(YELLOW "%c" RESET, tabuleiro[i][j]);
          break;
        case 'E':
          printf(RED "%c" RESET, tabuleiro[i][j]);
          break;
        default:
          printf("%c", tabuleiro[i][j]);
      }
    }
  printf("\n");
  }
  printf("tempo: %d\n", tempo);
  fflush(stdout);
  printf("pontuacao: %d", pontuacao);
  fflush(stdout);
}

void mira(){//basicamente a mira do jogo
  //f e uma variavel auxiliar usada para armazenar um valor e compara-lo com j
  // flag serve para parar a funcao caso uma letra esteja no caminho da mira.
  int i, j, f, flag = 0;
  for(i = 1;i <= altura - 2 && flag == 0;i++){
    for(j = 1;j <= largura - 2; j++){
      if(tabuleiro[i][j] == '-'){
        tabuleiro[i][j] = ' ';
      }
    }
  }
  for(i = 2;i <= altura - 2 && flag == 0;i++){
    for(j = 1;j <= largura - 2; j++){
      if(angulo > 1.5){
        angulo = 1.5;
      }
      if(angulo < -1.55 ){
        angulo = -1.55;
      }
      f = angulo*i + 8;
      tabuleiro[1][8] = p;
      if(tabuleiro[i][f] == ' '){
        tabuleiro[i][f] = '-';
      }
      else if((tabuleiro[i][f] == 'A' || tabuleiro[i][f] == 'B' || tabuleiro[i][f] == 'C'|| tabuleiro[i][f] == 'D' || tabuleiro[i][f] == 'E')){
        flag = 1;
      }
    }
  }
  printar_tabuleiro();
}

void descer_tabuleiro(){
  //vai descer o tabuleiro apos terem sido decorridos 20 segundos.
  int i, j;
  if(tempo%20 == 0 && tempo != tempo_comparador){
    tempo_comparador = tempo;
    for(i = 1;i < 8;i++){
      for(j = 0;j < 15;j++){
        tabuleiro[i][j] = tabuleiro[i+1][j];
      }
    }
    mira();
    perdeu();//checa se o jogador perdeu apos ter descido o tabuleiro
    printar_tabuleiro();
  }
}

void jogo(){
  gera_tabuleiro();
  gerarpeca();
  mira();
  pontuacao = 0;
  time_t comeco;
  time(&comeco);
  //h é a variavel que faz o jogo continuar
  //tecla serve para guardar o input do teclado
  int h = 0;
  char tecla;
  printar_tabuleiro();
  while(h != 1){
    usleep(6000);
    if(kbhit()){
      tecla = getch();
      if(tecla == 'a' || tecla == 'A' ){
        angulo += 0.05;
        mira();
      }
      else if(tecla == 'D' || tecla == 'd'){
        angulo -= 0.05;
        mira();
      }
      else if(tecla == ' '){
        atirar_animacao();
      }
    }
    if(!kbhit()){
      time_t final;
      time(&final);
      tempo = difftime(final, comeco);
      usleep(60000);
      descer_tabuleiro();
      printar_tabuleiro();
      //printf("tempo: %d", tempo);
    }
  }
}

void tela_inicial(){//tela inicial antes de escolher as opcoes
  system(CLEAR);
  while(!kbhit()){
    printf("pressione uma tecla para iniciar\n\n");
    fflush(stdout);
    printf("BOOBLE SHOOTER");
    fflush(stdout);
    usleep(60000);
    system(CLEAR);
    fflush(stdout);
  }
  if(kbhit()){
    usleep(60000);
    menu();
  }
}
config(){
  system(CLEAR);
  int opcao = 0;
  opcao = getch();
  printf("1 - pecas: %d\n", pecas);
  printf("2 - Modo ranqueado");
  if(ranqueado == 0){
    printf("Desativado\n");
  }
  else{
    printf("Ativado\n");
  }
  printf("3 - voltar\n");
  printf("Digite o numero da opcão correspondente");
  if(opcao == '1'){
    printf("digite o numero de pecas desejadas para serem estouradas, obs: o numero deve estar entre 3 e 10\n");
    scanf("%d", pecas);
    while(pecas > 10 || pecas < 3){
      usleep(60000);
      printf("numero invalido digite novamente\n");
      scanf("%d", pecas);
    }
  }
}

void menu(){
  tempo_comparador = 0;
  int opcao = 0;
  //essa funcao serve para printar o menu inicial 
  system(CLEAR);
  printf("1 - Jogar\n2 - Instrucoes\n3 - Configuracoes\n4 - Raking\n5 - Sair\n"); fflush(stdout);
  printf("Digite o numero correspondente a opcao desejada:"); fflush(stdout);
  opcao = getch();
  if(opcao == '1'){
    jogo();
  }
  else if(opcao == '2'){
    instrucoes();
  }
  else if(opcao == '5'){
    return;
  }
  else if(opcao == '3'){
    Config();
  }
  else{
    menu();
  }
}

int main(){
  srand(time(0));
  tela_inicial();
  usleep(600);
  system(CLEAR);
}