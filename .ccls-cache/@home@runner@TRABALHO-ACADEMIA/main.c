#include <stdio.h>
#include <stdlib.h>
#define CAPACIDADE_MAXIMA 100 

//STRUCTS
typedef struct aluno{
	int id;
	char nome[300];
	char cpf[15];
	char telefone[50];
	char email[100];
}aluno;


typedef struct professor {
  int id;
  char nome[300];
  char cpf[15];
  char telefone[50];
  char email[30];
}professor;

typedef struct turma {
  int id;
  int dia;  
  int id_prof;
  int numero_minimo_alunos;
  int numero_maximo_alunos;
  char tipo;
  char horario[6];
  char faixa_etaria[8];
  
}turma;

typedef struct inscricao {
  int id_aluno;
  int id_aula;
}inscricao;
//

//FUNÇÕES
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
  printf("8. Fechar programa\n");
  printf("Escolha uma opção: ");
  scanf("%d", &opcao);
  system("clear");
  return opcao;
}

//CADASTRO ALUNO
void cadastro_aluno(){
  aluno aluno;

  FILE*fp_aluno=fopen("alunos.csv","a");
  
  printf("ID: ");
  scanf(" %d", &aluno.id);
               
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
  fprintf(fp_aluno,"\n%d %s %s %s %s", aluno.id, aluno.nome, aluno.cpf, aluno.telefone, aluno.email);
  
  fclose(fp_aluno);
}

//CADASTRO PROFESSOR
void cadastro_professor(){
  professor professor;

  FILE*fp_professor=fopen("professores.csv","a");

  printf("ID: ");
  scanf(" %d", &professor.id);

  int c;
  while((c=getchar()!='\n' && c!=EOF));
  printf("NOME: ");
  gets(professor.nome);

  printf("CPF: ");
  gets(professor.cpf);

  printf("TELEFONE:");
  gets(professor.telefone);
               
  printf("EMAIL: ");
  gets(professor.email);
  fprintf(fp_professor,"\n%d %s %s %s %s", professor.id, professor.nome, professor.cpf, professor.telefone, professor.email);
    
  fclose(fp_professor);
}

//CADASTRO TURMA
void cadastro_turma(){
  turma turma;
  
  FILE*fp_turma=fopen("turmas.csv","a");

  printf("ID: ");
  scanf(" %d", &turma.id);

  printf("DIA DA AULA: ");
  scanf(" %d", &turma.dia);
    
  printf("ID PROFESSOR: ");
  scanf(" %d", &turma.id_prof);
    
  printf("NÚMERO MÍNIMO DE ALUNOS: ");
  scanf(" %d", &turma.numero_minimo_alunos);

  printf("NÚMERO MÁXIMO DE ALUNOS: ");
  scanf(" %d", &turma.numero_maximo_alunos);

  printf("TIPO DE AULA: ");
  scanf(" %c", &turma.tipo);
  
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
  printf("HORÁRIO DA AULA: ");
  gets(turma.horario);
    
  printf("FAIXA ETÁRIA: ");
  gets(turma.faixa_etaria);
  fprintf(fp_turma, "\n%d %d %d %d %d %c %s %s", turma.id, turma.dia, turma.id_prof, turma.numero_minimo_alunos, turma.numero_maximo_alunos, turma.tipo, turma.horario, turma.faixa_etaria);
    
  fclose(fp_turma);
}

//INSCREVER ALUNO
void inscrever_aluno(){
  inscricao inscricao;

  FILE*fp_inscricao=fopen("inscricoes.csv","a");

  printf("ID ALUNO: ");
  scanf(" %d", &inscricao.id_aluno);

  printf("ID AULA: ");
  scanf(" %d", &inscricao.id_aula);

  fprintf(fp_inscricao,"\n%d %d", inscricao.id_aluno, inscricao.id_aula);

  fclose(fp_inscricao);
}
//

//MAIN
int main(){
  
    int opcao=1;
    
    do{
        system("clear");
        puts("Academia superação\nDigite a opcao: ");
        opcao = exibirMenu();
        switch (opcao){
           case 1: // 1- Cadastra aluno
             cadastro_aluno();
             break;

           case 2: // 2-  Cadastrar professor
             cadastro_professor();
             break;

					 case 3: // 3- Cadastrar turma
             cadastro_turma();
             break;
             
           case 4:  // 4- Inscrever aluno
             inscrever_aluno();
             break;
             
           case 5:  // 5- Cancelar inscrição
             break;
       
           case 6:  // 6- Fechar turmas
             break;
           
           case 7:  // 7- Confirmar turmas
             break;

					 case 8:  // 8- Fechar o programa
              
						exit(0);

					 default:
						  printf("Opcao invalida, tente novamente.\n");
							break;
                      
        }
    }while (opcao>0 && opcao<9);


} //FIM DO MAIN