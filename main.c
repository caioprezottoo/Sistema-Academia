//CAIO BATISTA PREZOTTO

//PROTÓTIPO DO PROGRAMA
//NOTA: IMPORTEI A BIBLIOTECA DISPONIBILIZADA, MAS ACABEI NÃO UTILIZANDO
/*
1. PROGRAMA ABRE, RECONHECER DATA, MENU ABRE
  1.1 CASO QUEIRA FAZER CADASTRO DE ALUNO, PROFESSOR E TURMA, RECOMENDO SEGUIR O FORMATO JÁ EXEMPLIFICADO NOS ARQUIVOS ABERTOS

2. ESCOLHER OPÇÃO 8
  2.1 CASO QUEIRA SE INSCREVER EM AULAS DENTRO DE 30 MINUTOS
    1. DIGITE O HORÁRIO E IRÁ APARECER AS AULAS DISPONÍVEIS
      1.1 CASO NÃO TENHA AULAS, O SISTEMA IRÁ NOTIFICAR
      1.2 PARA FACILITAR ABRA O ARQUIVO "turmas.csv", PARA VERIFICAR OS HORÁRIOS DE AULAS EXISTENTES
    2. O ARQUIVO "participacao.csv" ABRE
    3. ASSIM QUE FEITA A INSCRIÇÃO, AS INFORMAÇÕES PARTEM PARA O ARQUIVO
      3.1 CASO OCORRA ALGUM PROBLEMA NA INSCRIÇÃO, O SISTEMA ABRIRÁ UM ARQUIVO QUE NOTIFICA FALHA
      3.1.1 QUERIA CRIAR UMA DINÂMICA DIFERENTE, NO CASO QUERIA UMA CAIXA DE NOTIFICAÇÃO MAS ACHEI ESSA "SOLUÇÃO"
    4. DESTA FORMA, TODA VEZ QUE ALGUEM SE INSCREVER, IRÁ APARECER NO ARQUIVO
    
  2.2 CASO QUEIRA MOSTRAR RANKING
    1. A FUNÇÃO "mostrar_ranking" ABRE O ARQUIVO "participacao.csv" E RETIRA AS INFORMAÇÕES NECESSÁRIAS
    2. ASSIM QUE RANKING FOR SELECIONADO, VAI APARECER UM RANKING, OBVIAMENTE, DE ALUNOS QUE MAIS PARTICIPARAM DE AULAS NO DIA
    
3. APÓS AS VERIFICAÇÕES NA PARTE DO SUBMENU 8, CASO QUEIRA GERAR OS RELATÓRIOS, BASTA CLICAR NA OPÇÃO 9
  3.1 CLICANDO NESTA OPÇÃO, OS RELATÓRIOS SERÃO GERADOS, O ARQUIVO "participacao.csv" DEIXA DE EXISTIR E PROGRAMA FECHA
*/

//INÍCIO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prog2Utils.h"
#include <errno.h>
#define CAPACIDADE_MAXIMA 100 

//STRUCTS

//STRUCT UTILIZADA PARA DEFINIR AS INFORMAÇÕES DOS ALUNOS
typedef struct aluno{
	int id_aluno;
	char nome[300];
	char cpf[15];
	char telefone[50];
	char email[100];
  struct aluno* proximo;
}aluno;
//

//STRUCT UTILIZADA PARA DEFINIR AS INFORMAÇÕES DOS PROFESSORES
typedef struct professor {
  int id_prof;
  char nome_prof[300];
  char cpf[15];
  char telefone[50];
  char email[30];
}professor;
//

//STRUCT UTILIZADA PARA DEFINIR AS INFORMAÇÕES DAS TURMAS
typedef struct turma {
  int id_turma;
  int dia;  
  int id_prof;
  int numero_minimo_alunos;
  int numero_maximo_alunos;
  char tipo;
  char horario[6];
  char faixa_etaria[8];
  
}turma;
//

//STRUCT UTILIZADA PARA GUARDAR AS INFORMAÇÕES DE INSCRIÇÃO
typedef struct inscricao {
  int id_aluno;
  int id_aula;
}inscricao;
//

//STRUCT PARTICIPANTE
typedef struct participante{
  int id_aluno; 
  char nome[30];
  int participacoes;
}participante;
//

//FUNÇÕES

//EDITFILE
int editFile(char path[],char delim[],int id,int pos, char newVal[]){
  const int MAX_ID = 10;
  const int MAX_BUFFER = 500;
  char res[MAX_BUFFER];
  int foundId = 0;
  int err=0;

  FILE *fp;
  fp = fopen(path,"r");
  if(fp==NULL){
    printf("Erro de acesso ao arquivo \"%s\" : ",path);
    printf("%s\n", strerror(errno));
    return 0;
  }
  FILE *ftemp;
  char tempPath[MAX_BUFFER];
  strcpy(tempPath,path);
  strcat(tempPath,".tmp");
  ftemp = fopen(tempPath,"w");
  if(fp==NULL){
    printf("Erro de criação de arquivo temporário\n");
    printf("%s\n", strerror(errno));
    return 0;
  }



  while(fgets(res,MAX_BUFFER,fp)!=NULL){
    int i=0;
    int found = 0;
    char str[MAX_BUFFER];
    char *tempstr = calloc(MAX_BUFFER+1, sizeof(char));
    char *basestr = calloc(MAX_BUFFER+1, sizeof(char));
    strcpy(basestr,res);

    // o primeiro token é o ID
    char *token = strtok(basestr, delim);

    if(strtol(token,NULL,MAX_ID) == id){
      foundId = 1;

      while(token != NULL) {
        // se não chegou na posição correta, use o valor antigo
        if(i!=pos){ 
          strcat(tempstr,token);     
        }else{ // se chegou, salve o novo valor
          strcat(tempstr,newVal);  
          found = 1;
        }
        i++;

        //printf("%s\n", token);
        token = strtok(NULL, delim);
        // adicionar delimitador entre os valores
        if(token) strcat(tempstr,delim);
        
      }

      if(!found){
        printf("Posicao %d nao encontrada no id %d\n",pos,id);
        err=1;
      }
      //printf("----- %s",tempstr);
    }
    
    // salva valores no arquivo temporário
    if(found){
      // se a linha antiga tinha newline, essa deverá ter também
      if(strchr(res,'\n') != NULL)
        strcat(tempstr,"\n");
      fputs(tempstr,ftemp);
      }
    else
      fputs(res,ftemp);
  }
  if(!foundId){
    printf("Id: %d não encontrado\n",id);
    err = 1;
  }


  fclose(fp);
  fclose(ftemp);

  if (!err){
    int ret = remove(path);
    if(ret !=0){
      printf("Erro ao deletar o arquivo \"%s\" : ",path);
      printf("%s\n", strerror(errno));
      err = 1;
    }
    rename(tempPath, path);
    return 1;
 }else{
    remove(tempPath);
    return 0;
  }
}
//

//FUNÇÃO PARA EXIBIR MENU
int exibirMenu() {
  int opcao;
  printf("\n--- MENU ---\n");
  printf("1. Cadastrar aluno\n");
  printf("2. Cadastrar professor\n");
  printf("3. Cadastrar turma\n");
  printf("4. Inscrever aluno\n");
  printf("5. Cancelar inscrição\n");
  printf("6. Fechar turmas\n");
  printf("7. Confirmar turmas\n");
  printf("8. Inscrição em aula\n");
  printf("9. Fechar programa\n");
  printf("Escolha uma opção: ");
  scanf("%d", &opcao);
  system("clear");
  return opcao;
}
//

//CADASTRO ALUNO
void cadastro_aluno(){
  aluno aluno;

  FILE*fp_aluno=fopen("alunos.csv","a");

  if (fp_aluno == NULL) {
    printf("Não foi possível abrir o arquivo.\n");
    exit(0);
  }
  
  printf("ID: ");
  scanf(" %d", &aluno.id_aluno);
               
  int c;
  while((c=getchar()!='\n' && c!=EOF));
  printf("NOME: ");
  gets(aluno.nome);
                
  printf("CPF:");
  gets(aluno.cpf);

  printf("TELEFONE:");
  gets(aluno.telefone);
               
  printf("EMAIL: ");
  gets(aluno.email);
  fprintf(fp_aluno,"\n%d,%s,%s,%s,%s", aluno.id_aluno, aluno.nome, aluno.cpf, aluno.telefone, aluno.email);
  
  fclose(fp_aluno);
}
//

//CADASTRO PROFESSOR
void cadastro_professor(){
  professor professor;

  FILE*fp_professor=fopen("professores.csv","a");
  
  if (fp_professor == NULL) {
    printf("Não foi possível abrir o arquivo.\n");
    exit(0);
  }

  printf("ID: ");
  scanf(" %d", &professor.id_prof);

  int c;
  while((c=getchar()!='\n' && c!=EOF));
  printf("NOME: ");
  gets(professor.nome_prof);

  printf("CPF: ");
  gets(professor.cpf);

  printf("TELEFONE:");
  gets(professor.telefone);
               
  printf("EMAIL: ");
  gets(professor.email);
  fprintf(fp_professor,"\n%d,%s,%s,%s,%s", professor.id_prof, professor.nome_prof, professor.cpf, professor.telefone, professor.email);
    
  fclose(fp_professor);
}
//

//CADASTRO TURMA
void cadastro_turma(){
  turma turma;
  
  FILE*fp_turma=fopen("turmas.csv","a");

  if (fp_turma == NULL) {
    printf("Não foi possível abrir o arquivo.\n");
    exit(0);
  }

  printf("ID: ");
  scanf(" %d", &turma.id_turma);

  printf("DIA DA AULA: ");
  scanf(" %d", &turma.dia);
    
  printf("ID PROFESSOR: ");
  scanf(" %d", &turma.id_prof);
    
  printf("NÚMERO MÍNIMO DE ALUNOS (*MÍN: NÚMERO MÍNIMO DE ALUNOS REGISTRADOS): ");
  scanf(" %d", &turma.numero_minimo_alunos);

  printf("NÚMERO MÁXIMO DE ALUNOS (*MÁX: NÚMERO MÁXIMO DE ALUNOS REGISTRADOS): ");
  scanf(" %d", &turma.numero_maximo_alunos);

  printf("TIPO DE AULA: ");
  scanf(" %c", &turma.tipo);
  
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
  printf("HORÁRIO DA AULA: ");
  gets(turma.horario);
    
  printf("FAIXA ETÁRIA: ");
  gets(turma.faixa_etaria);
  fprintf(fp_turma, "\n%d,%d,%d,%d,%d,%c,%5s,%7s", turma.id_turma, turma.dia, turma.id_prof, turma.numero_minimo_alunos, turma.numero_maximo_alunos, turma.tipo, turma.horario, turma.faixa_etaria);
    
  fclose(fp_turma);
}
//

//INSCREVER ALUNO
void inscrever_aluno(){
  inscricao inscricao;

  FILE*fp_inscricao=fopen("inscricoes.csv","a");

  if (fp_inscricao == NULL) {
    printf("Não foi possível abrir o arquivo.\n");
  }

  printf("ID ALUNO: ");
  scanf(" %d", &inscricao.id_aluno);

  printf("ID AULA: ");
  scanf(" %d", &inscricao.id_aula);

  fprintf(fp_inscricao,"\n%d,%d", inscricao.id_aluno, inscricao.id_aula);

  fclose(fp_inscricao);
}
//

//MOSTRAR AULAS EM 30 MINUTOS
int mostrar_aulas_proximos_30Minutos(char horario[6]) {
    //ABRIR ARQUIVO
    FILE* fp_turmas = fopen("turmas.csv", "r");
    //VERIFICAR ABERTURA DE ARQUIVO
    if (fp_turmas == NULL) {
        printf("Erro ao abrir o arquivo turmas.csv\n");
        return;
    }

    char linha[100];
    char horarioTurma[6];
    char tipo;
    //INFORMAÇÕES SOBRE HORÁRIO RETIRADO NA FUNÇÃO PARTICIPAR AULA
    int horaAtual, minutoAtual, horaTurma, minutoTurma, x=0, id_turma;
  
    //CÓPIA DO HORÁRIO INSERIDO PELO USUÁRIO
    sscanf(horario, "%d:%d", &horaAtual, &minutoAtual);

    printf("AULAS NOS PRÓXIMOS 30 MINUTOS:\n");

    while (fgets(linha, sizeof(linha), fp_turmas) != NULL) {
        sscanf(linha, "%d,%*d,%*d,%*d,%*d,%c,%[^,]", &id_turma, &tipo, horarioTurma);
        sscanf(horarioTurma, "%d:%d", &horaTurma, &minutoTurma);

        //CONVERTE AS HORAS PARA MINUTOS 
        int totalMinutosAtual = (horaAtual * 60) + minutoAtual;
        int totalMinutosTurma = (horaTurma * 60) + minutoTurma;
        int diff = totalMinutosTurma - totalMinutosAtual;

        //VERIFICA A DIFERENÇA DE MINUTOS
        if(diff < 0){
          if (totalMinutosAtual - totalMinutosTurma <= 30 && diff > 0) {
            printf("ID: %d, TIPO: %c, HORÁRIO: %s\n", id_turma, tipo, horarioTurma);
            x=1;
          }
        } 
        else if (diff <= 30 && diff > 0) {
          printf("ID: %d, TIPO: %c, HORÁRIO: %s\n", id_turma, tipo, horarioTurma);
          x=1;
        } 
    }

    if(x==0){
     printf("\nNÃO HÁ AULAS DISPONÍVEIS\n"); 
    }
  
    //FECHAR ARQUIVO
    fclose(fp_turmas);
    return x;
}
//

//BUSCA ALUNO
aluno buscar_aluno_por_id(int id_aluno) {
  //ABRIR ARQUIVO
  FILE *fp_alunos = fopen("alunos.csv", "r");
  //VERIFICAR ARQUIVO
  if (fp_alunos == NULL) {
    printf("Deu merda!\nErro ao abrir o arquivo alunos.csv\n");
    exit(1);
  }
  
  aluno a;
  a.id_aluno = -1;
  char linha[100];

  //COPIAR O NOME DO ALUNO
  while (fgets(linha, sizeof(linha), fp_alunos) != NULL) {
    int id;
    char nome[50], email[50];
    char cpf[12], telefone[12];
    if (sscanf(linha, "%d,%[^,],%[^,],%[^,],%s", &id, nome, cpf, telefone, email) == 5) {
      if (id == id_aluno) {
        a.id_aluno = id;
        strcpy(a.nome, nome);
        fclose(fp_alunos);
        return a;
      }
    }
  }

  //FECHAR ARQUIVO
  fclose(fp_alunos);
  //RETORNAR O VALOR NECESSÁRIO
  return a;
}
//

//BUSCA PROFESSOR
professor buscar_professor_por_id(int id_prof) {
  FILE *fp = fopen("professores.csv", "r");
  if (fp == NULL) {
    printf("ERRO AO ABRIR O AQRUIVO\n");
    exit(1);
  }
  
  professor p;
  p.id_prof = -1;
  char linha[100];
  
  while (fgets(linha, sizeof(linha), fp) != NULL) {
    int id;
    char nome[300], email[100];
    char cpf[15], telefone[50];
    if (sscanf(linha, "%d,%[^,],%[^,],%[^,],%s", &id, nome, cpf, telefone, email) == 5) {
      if (id == id_prof) {
        p.id_prof = id;
        strcpy(p.nome_prof, nome);
        strcpy(p.cpf, cpf);
        strcpy(p.telefone, telefone);
        strcpy(p.email, email);
        fclose(fp);
        return p;
      }
    }
  }
  fclose(fp);
  return p;
} 
//

//PARTICIPAR AULA
void participar_aula(){
  char hora[6];
  turma turma;

  //PEDIR HORÁRIO
  printf("HORÁRIO (HH:MM): ");
  scanf("%5s", hora);
  
  //VALIDAÇÃO DO HORÁRIO (HH:MM)
  if(strlen(hora) != 5 || hora[2] != ':') {
    printf("DIGITE NO FORMATO EXEMPLIFICADO!\n");
    exit(0);
  }

  //FUNÇÃO QUE VERIFICA AS AULAS EM 30 MINUTOS
  int x=mostrar_aulas_proximos_30Minutos(hora);

  //ABRIR ARQUIVOS
  FILE*fp_inscricao=fopen("inscricoes.csv","r");
  FILE*fp_temp=fopen("participacao.csv","a");

  //VERIFICAR ARQUIVOS
  if(fp_inscricao==NULL || fp_temp==NULL){
    printf("ERRO!");
    exit(0);
  }

  //INSERIR INFORMAÇÕES NO NOVO ARQUIVO
  //CASO ALUNO JÁ PARTICIPE DA AULA
  if(x==1){ 
    int id_aluno, id_turma;

    printf("ID ALUNO E ID TURMA: ");
    scanf("%d %d", &id_aluno, &id_turma);

    aluno a = buscar_aluno_por_id(id_aluno);

    int aluno, turma, temp=0;
    while (fscanf(fp_inscricao, "%d,%d", &aluno, &turma) == 2) {
        if(aluno == id_aluno && turma == id_turma) {
          fprintf(fp_temp,"\n%d,%s,%d", id_aluno, a.nome, id_turma);
          printf("\nINSCRITO COM SUCESSO!\n\n");
          temp=1;
        }
    }
    if(temp==0){
      //QUERIA NOTIFICAR DE ALGUMA FORMA, NO CASO QUERIA UM CAIXA DE NOTIFICAÇÃO
      //MAS ACHEI ESSA SOLUÇÃO
      //ABRE UM NOVO ARQUIVO "TEMPORÁRIO" PARA NOTIFICAR O ERRO
      FILE*fp_erro=fopen("ERRO_INSCRICAO.csv","a");
      fprintf(fp_erro,"FALHA NA INSCRIÇÃO!\n");
      fclose(fp_erro);
      //REMOVE O ARQUIVO "participacao.csv" QUE FOI ABERTO
      remove("participacao.csv");
    } 
  }

  professor p;
  aluno a;
  
  //FECHAR ARQUIVOS
  fclose(fp_inscricao);
  fclose(fp_temp);
}
//

//MOSTRAR RANKING
void mostrar_ranking() {
  //ABRIR ARQUIVO
  FILE* fp_participacao = fopen("participacao.csv", "r");
  
  //VERIFICAR ARQUIVO
  if (fp_participacao == NULL) {
    printf("Erro ao abrir o arquivo participacao.csv\n");
    exit(1);
  }

  int capacidade = 10; //INICIAR CAPACIDADE DO VETOR
  int tamanho = 0; //TAMANHO ATUAL DO VETOR
  participante* participantes = malloc(capacidade * sizeof(participante));

  int id_aluno, id_turma;
  char nome[30];

  while (fscanf(fp_participacao, "%d,%[^,],%d", &id_aluno, nome, &id_turma) == 3) {
    //VERIFICAR SE O ALUNO JÁ EXISTE NO VETOR
    int existe = 0;
    for (int i = 0; i < tamanho; i++) {
      if(participantes[i].id_aluno == id_aluno) {
        participantes[i].participacoes++;
        existe = 1;
        break;
      }
    }

    //SE EXISTE == 0, ENTAO ADICIONA NO VETOR
    if (!existe) {
      //VERIFICAR TAMANHO DO VETOR
      //CASO PRECISE REALOCAR O TAMANHO
      if (tamanho >= capacidade) {
        capacidade *= 2; //DOBRAR A CAPACIDADE
        participantes = realloc(participantes, capacidade * sizeof(participante));
      }

      participantes[tamanho].id_aluno = id_aluno;
      strcpy(participantes[tamanho].nome,nome);
      participantes[tamanho].participacoes = 1;
      tamanho++;
    }
  }

    //FECHAR ARQUIVO
    fclose(fp_participacao);

  //ORDENAR VETOR
  for (int i = 0; i < tamanho - 1; i++) {
    for (int j = 0; j < tamanho - i - 1; j++) {
      if (participantes[j].participacoes < participantes[j + 1].participacoes) {
        participante temp = participantes[j];
        participantes[j] = participantes[j + 1];
        participantes[j + 1] = temp;
      }
    }
  }

  printf("RANKING:\n\n");
  for (int i = 0; i < tamanho; i++) {
    printf("%d. NOME %s, ID %d, PARTICIPAÇÕES %d\n\n", i + 1, participantes[i].nome, participantes[i].id_aluno, participantes[i].participacoes);
  }

  free(participantes);
  
}
//

//GERAR RELATÓRIOS
void gerar_relatorios(int dia, int mes, int ano) {
  //ABRIR ARQUIVO
  FILE* fp_turmas = fopen("turmas.csv", "r");
  //VERIFICAR ARQUIVO
  if (fp_turmas == NULL) {
    printf("Erro ao abrir o arquivo turmas.csv\n");
    return;
  }

  char linha[100];
  int id_turma;
  char id_prof;

  //VERIFICAR DATA
  if(dia <= 0 || dia >= 32){
    printf("FALHA NA VERIFICAÇÃO DE DATA!");
  } else if(dia>=29 && mes == 2){
    printf("FALHA NA VERIFICAÇÃO DE DATA!");
  } else if(mes<=0 || mes >=13){
    printf("FALHA NA VERIFICAÇÃO DE DATA!");
  } else if(ano<=0 || ano<=2022){
    printf("FALHA NA VERIFICAÇÃO DE DATA!");
  }

  int existe=0;

  while (fgets(linha, sizeof(linha), fp_turmas) != NULL) {
    sscanf(linha, "%*d,%*d,%d", &id_prof);
    professor p = buscar_professor_por_id(id_prof);

    //TIVE QUE SEPARAR A COPIA DO ID TURMA E ID PROF
    //FUNÇÃO BUSCAR PROFESSOR ESTAVA DANDO ERRO NA COPIA DO ID TURMA
    sscanf(linha, "%d,%*d,%*d", &id_turma);

    //CRIAR ARQUIVO
    char nomeArquivo[100];
    sprintf(nomeArquivo, "%d_%d_%d_%d.csv", id_turma, dia, mes, ano);

    FILE* fp_relatorio = fopen(nomeArquivo, "w");
    if (fp_relatorio == NULL) {
      printf("ERRO AO CRIAR RELATÓRIO: %s\n", nomeArquivo);
      continue;
    }

    //ESCREVER ID TURMA E NOME PROFESSOR NO RELATÓRIO
    fprintf(fp_relatorio, "ID PROFESSOR: %d, NOME PROFESSOR: %s\n", id_prof, p.nome_prof);

    //BUSCAR ALUNOS QUE PARTICIPARAM DA TURMA
    FILE* fp_participacao = fopen("participacao.csv", "r");
    if (fp_participacao == NULL) {
      printf("ERRO NA VERIFICAÇÃO DO ARQUIVO\n");
      fclose(fp_relatorio);
      continue;
    }

    int id_turma_participacao, id_aluno;
    char nome_aluno[100];

    while (fscanf(fp_participacao, "%d,%[^,],%d", &id_aluno, nome_aluno, &id_turma_participacao) == 3) {
      if (id_turma_participacao == id_turma) {
        //ID E NOME DO ALUNO NO RELATÓRIO
        fprintf(fp_relatorio, "ID ALUNO: %d, NOME ALUNO: %s\n", id_aluno, nome_aluno);
      }
    }

    fclose(fp_participacao);
    fclose(fp_relatorio);
  }

  fclose(fp_turmas);
}
//

//SUBMENU INSCRICAO EM AULA
void subMenu(){
  int opcao;
  printf("1. Participar em Aula\n");
  printf("2. Mostrar Ranking\n");
  printf("Escolha a opção: ");
  scanf(" %d",&opcao);
  system("clear");

  if(opcao==1){
    participar_aula();
  } else if(opcao==2){
    mostrar_ranking();
  } else{
    printf("ERRO NA ESCOLHA DE OPÇÃO");
    exit(0);
  }
}
//

//FIM DAS FUNÇÕES

//MAIN
int main(){

  int dia, mes, ano;

  //PEDIR DATA
  printf("DIA: ");
  scanf("%d", &dia);
  
  printf("MÊS: ");
  scanf("%d", &mes);
  
  printf("ANO: ");
  scanf("%d", &ano);

  system("clear");
  
  int opcao=1;
    
  do{
    puts("Academia superação\nDigite a opcao: ");
    opcao = exibirMenu();
    switch (opcao){
      case 1: // 1- CADASTRAR ALUNO
        cadastro_aluno();
        break;

      case 2: // 2-  CADASTRAR PROFESSOR
        cadastro_professor();
        break;

			case 3: // 3- CADASTRAR TURMA
        cadastro_turma();
        break;
             
      case 4:  // 4- INSCREVER ALUNO
        inscrever_aluno();
        break;
            
      case 5:  // 5- CANCELAR INSCRIÇÃO
        printf("FUNÇÃO DESATIVADA PARA REALIZAÇÃO DO DESAFIO ADICIONAL");
        break;
       
      case 6:  // 6- FECHAR TURMAS
        printf("FUNÇÃO DESATIVADA PARA REALIZAÇÃO DO DESAFIO ADICIONAL");
        break;
           
      case 7:  // 7- CONFIRMAR TURMAS
        printf("FUNÇÃO DESATIVADA PARA REALIZAÇÃO DO DESAFIO ADICIONAL");
        break;
      case 8:  // 8 - INSCRIÇÃO EM AULA
        subMenu(dia, mes, ano);
        break;

      case 9:  // 9 - FECHAR O PROGRAMA, DELETAR ARQUIVO E GERAR RELATÓRIOS
        gerar_relatorios(dia, mes, ano); 
        remove("participacao.csv");
        remove("ERRO_INSCRICAO.csv");
        exit(0);
      default:
        printf("INVÁLIDO, TENTE NOVAMENTE.\n");
        break;
                      
    }
  }while (opcao>0 && opcao<10);


} 
//FIM