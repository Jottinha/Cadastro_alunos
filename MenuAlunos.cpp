#include <iostream>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define UP_ARROW 72
#define DOWN_ARROW 80
#define ENTER_KEYBOARD 13
#define ESC_KEYBOARD 27
#define QUANTIDADE_TOTAL_PROVAS 3
#define QUANTIDADE_TOTAL_TRABALHOS 4
#define QUANTIDADE_TOTAL_PASSAR_PROVAS 6
#define QUANTIDA_MINIMA_PONTOS_SEMESTRE 6
#define QUANTIDADE_MINIMA_FRQUENCIA 75


struct Alunos
{
	char nome[30];
	float media_provas, media_trabalhos, porcentagem_aulas_presentes, media_final_semestre;
	int id_aluno;
	bool situacao_final = false;
	bool notas_alunos_aplicadas_pelo_usuario = false;
	struct Alunos *proximo;
};

void gotoxy(int x,int y){
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void menu_creation();
void line_creation();
int keyboard_interection();
int confirming_choice(int linha);
Alunos* cadastrando_aluno_sistema(Alunos *alunos_cadastrados);
char verificando_existencia_id(int id, Alunos *alunos_cadastrados);
void listando_alunos_cadastrados(Alunos *alunos_cadastrados);
void aplicando_notas_alunos(Alunos *alunos_cadastrados);
float notas_das_provas();
float notas_trabalhos();
float frequencia_nas_aulas();
void situacao_final_alunos_cadastrados(Alunos *alunos_cadastrados);
void media_final_dos_alunos(Alunos* alunos_cadastrados);
void aprovados_ou_nao(Alunos* alunos_cadastrados);

int main(int argc, char const* argv[ ])
{
	//setando idioma protugues
	setlocale(LC_ALL, "Portuguese");
	
	//variaveis
	float media_final;
	int user_chosen_option;
	Alunos *alunos_cadastrados = NULL;
	
	while(1)
	{
		menu_creation();
	
		user_chosen_option = keyboard_interection();
	
		switch(user_chosen_option)
		{
			// 1 ==  CADASTRAR ALUNO - 2 == ALUNOS CADASTRADOS - 3 == APLICAR NOTAS - 4 == APROVADOS
			case 1:
				fflush(stdin);
				system("cls");
				alunos_cadastrados = cadastrando_aluno_sistema(alunos_cadastrados);
				break;
			case 2:
				system("cls");
				listando_alunos_cadastrados(alunos_cadastrados);
				break;
			case 3:
				system("cls");
				aplicando_notas_alunos(alunos_cadastrados);
				break;
			case 4: 
				system("cls");
				situacao_final_alunos_cadastrados(alunos_cadastrados);
				break;
			default: 
				break;
		}
	}
}

void menu_creation()
{
	system("cls");
	int coluna = 26, linha = 6;
	
	line_creation();
	
	gotoxy(coluna, linha);
	printf("CADASTRAR ALUNO");
	
	gotoxy(coluna, linha+2);
	printf("ALUNOS CADASTRADOS");
	
	gotoxy(coluna, linha+4);
	printf("APLICAR NOTAS");
	
	gotoxy(coluna, linha+6);
	printf("APROVADOS\n\n\n\n");
	
}
void line_creation()
{
	int linha, coluna;
	
	//linha superior do quadrado
	for(coluna = 20, linha = 3; coluna <= 80; coluna++)
	{
		gotoxy(coluna, linha);
		printf("*");
	}
	
	//coluna superior esquerda
	for(coluna = 20, linha = 4; linha <= 15; linha++)
	{
		gotoxy(coluna, linha);
		printf("*");
	}
	
	//linha inferior do quadrado
	for(coluna = 20, linha = 15; coluna <= 80; coluna++)
	{
		gotoxy(coluna, linha);
		printf("*");
	}
	
	//coluna inferior direita
	for(coluna = 80, linha = 4; linha <= 15; linha++)
	{
		gotoxy(coluna, linha);
		printf("*");
	}
}
int keyboard_interection()
{
	int coluna = 23, linha = 6, cursor_deleted = linha, chosen_option = 0, i;
	char tecla_apertada;
	do
	{
		tecla_apertada = getch();
		
		switch(tecla_apertada)
		{
			case UP_ARROW:
				
				linha -= 2;
				if(linha < 6 )
				{
					linha = 12;
				}
				
				break;
				
			case DOWN_ARROW:
				linha += 2;
				
				if(linha > 12)
				{
					linha = 6;
				}
				break;
				
			case ESC_KEYBOARD:
				
				system("cls");
				printf("Exit ");
				for(i = 0; i < 10; i++)
				{
					gotoxy(i,1);
					printf(".");
					Sleep(250);
				}
				exit(1);
				break;
			default:
				break;
		}
		//eliminando seta duplicada	
		if(cursor_deleted != linha)
		{
			gotoxy(coluna, cursor_deleted);
			printf("  ");
			cursor_deleted = linha;
		}
		gotoxy(coluna, linha);
		printf("-%c",16);
		
		//Se a opção foi escolhida
		if(tecla_apertada == ENTER_KEYBOARD)
		{
			chosen_option = confirming_choice(linha);
		}
		
	}while(tecla_apertada != ENTER_KEYBOARD);
	
	return chosen_option;
};
int confirming_choice(int linha)
{	
	int option_choice_value = 0;
	
	if(linha == 6)// = CADASTRAR ALUNO
	{
		option_choice_value = 1;
	}
	else if(linha == 8)// = ALUNOS CADASTRADOS
	{
		option_choice_value = 2;
	}
	else if(linha == 10)// = APLICAR NOTAS
	{
		option_choice_value = 3;
	}
	else if(linha == 12)// = APROVADOS
	{
		option_choice_value = 4;
	}
	return option_choice_value;
}

Alunos* cadastrando_aluno_sistema(Alunos *alunos_cadastrados)
{
	Alunos dados_digitados_pelo_usuario;
	char verificador_id = 'f'; //verificador pode receber f(falso) OU v(verdadeiro)
	
	printf("Digite o nome do aluno: ");
	fgets(dados_digitados_pelo_usuario.nome, 30, stdin);
	fflush(stdin);
	
	printf("Digite a identificação do aluno (SUGESTÃO: N° CHAMADA): ");
	scanf("%d", &dados_digitados_pelo_usuario.id_aluno);
	fflush(stdin);
	
	verificador_id = verificando_existencia_id(dados_digitados_pelo_usuario.id_aluno ,alunos_cadastrados);
	
	if(verificador_id != 'v' && strlen(dados_digitados_pelo_usuario.nome) > 1)
	{
		Alunos *salvando_dados_sistema = (Alunos*)malloc(sizeof(Alunos));
		
		strcpy(salvando_dados_sistema -> nome, dados_digitados_pelo_usuario.nome);
		salvando_dados_sistema -> id_aluno = dados_digitados_pelo_usuario.id_aluno;
		salvando_dados_sistema -> proximo = alunos_cadastrados;
		
		printf("\n\n\nCADASTRO REALIZADO\n\n\nPRESSIONE QUALQUER TECLA PARA CONTINUAR ");
		getch();
		return salvando_dados_sistema;
	}
	else
	{
		printf("NOME INVALIDO/ID EXISTENTE");
		printf("\n\n\nPRESSIONE QUALQUER TECLA PARA CONTINUAR ");
		getch();
		return alunos_cadastrados;
	}
}
char verificando_existencia_id(int id, Alunos *alunos_cadastrados)
{
	Alunos *id_aluno_criado = alunos_cadastrados;
	char verificando_id;
	
	for(id_aluno_criado = alunos_cadastrados; id_aluno_criado != NULL; id_aluno_criado = id_aluno_criado -> proximo)
	{
		if(id_aluno_criado -> id_aluno == id)
		{
			verificando_id = 'v';
			break;
		}
	}
	return verificando_id;
}
void listando_alunos_cadastrados(Alunos *alunos_cadastrados)
{
	Alunos *alunos_a_serem_listados = alunos_cadastrados;
	
	for(alunos_a_serem_listados = alunos_cadastrados; alunos_a_serem_listados != NULL; alunos_a_serem_listados = alunos_a_serem_listados -> proximo)
	{
		printf("-----------------------------------\n");
		printf("Nome: %s", alunos_a_serem_listados -> nome);
		printf("ID:%d", alunos_a_serem_listados -> id_aluno);
		printf("\n-----------------------------------\n");
	}
	if(alunos_cadastrados == NULL)
	{
		printf("NENHUM ALUNO ENCONTRADO\n\n");
	}
	
	printf("\n\n\n\nPRESSIONE QUALQUER TECLA PARA CONTINUAR");
	getch();	
}
void aplicando_notas_alunos(Alunos *alunos_cadastrados)
{
	Alunos *alunos_que_receberao_notas = alunos_cadastrados;
	Alunos *alunos_anterior_da_lista = NULL;
	Alunos dados_usuario_para_alunos;
	int id, aulas_presentes_indicado_pelo_usuario;
		
	printf("Qual é o ID do aluno: ");
	scanf("%d", &id);
	fflush(stdin);
	
	while(alunos_que_receberao_notas != NULL && alunos_que_receberao_notas -> id_aluno != id)
	{
		alunos_que_receberao_notas = alunos_que_receberao_notas -> proximo;
	}
	if(alunos_que_receberao_notas != NULL)
	{
		printf("Nome: %s\n", alunos_que_receberao_notas -> nome);
		alunos_que_receberao_notas -> media_provas = notas_das_provas();
		alunos_que_receberao_notas -> media_trabalhos = notas_trabalhos();
		alunos_que_receberao_notas -> porcentagem_aulas_presentes = frequencia_nas_aulas();
		alunos_que_receberao_notas -> notas_alunos_aplicadas_pelo_usuario = true;
		printf("NOTAS APLICADAS");
	}
	else
	{
		printf("ID NÃO ENCONTRADO");
	}
		
	printf("\n\n\n\nPRESSIONE QUALQUER TECLA PARA CONTINUAR");
	getch();	
}
float notas_das_provas()
{	
	int i, nota[QUANTIDADE_TOTAL_PROVAS];
	float media = 0;
	for(i = 0; i < QUANTIDADE_TOTAL_PROVAS; i++)
	{
		printf("Digite a nota da %d° prova: ", i+1);
		scanf("%d", &nota[i]);
		media += nota[i];
	}
	media /= QUANTIDADE_TOTAL_PROVAS;
	return media;
}
float notas_trabalhos()
{
	int i, nota[QUANTIDADE_TOTAL_TRABALHOS];
	float media = 0;
	for(i = 0; i < QUANTIDADE_TOTAL_TRABALHOS; i++)
	{
		printf("Digite a nota do %d° trabalho: ", i+1);
		scanf("%d", &nota[i]);
		media += nota[i];
	}
	media /= QUANTIDADE_TOTAL_TRABALHOS;
	return media;
}

float frequencia_nas_aulas()
{
	int aulas_assistidas, aulas_total_semestre;
	float frequencia_aulas;
	
	printf("Quantas aulas o professor passou: ");
	scanf("%d", &aulas_total_semestre);
	
	printf("Quantas aulas o aluno participou: ");
	scanf("%d", &aulas_assistidas);
	
	frequencia_aulas = aulas_assistidas * 100 / aulas_total_semestre;
	return frequencia_aulas;
}
void situacao_final_alunos_cadastrados(Alunos *alunos_cadastrados)
{
	float media_geral_alunos_aprovados = 0;
	float total_media_alunos = 0;
	float total_alunos = 0;
	float total_alunos_aprovado = 0;
	
	media_final_dos_alunos(alunos_cadastrados);
	aprovados_ou_nao(alunos_cadastrados);
	Alunos *situacao_aluno = alunos_cadastrados;
	
	for(situacao_aluno = alunos_cadastrados; situacao_aluno != NULL; situacao_aluno = situacao_aluno -> proximo)
	{

		printf("--------------------------\n");
		printf("Nome: %s\n", situacao_aluno -> nome);
		
		printf("ID:%d\n", situacao_aluno -> id_aluno);
		
		//verifica se as notas já foram ou não aplicadas pelo usuario (Para não ter bug de visualização)
		if(situacao_aluno -> notas_alunos_aplicadas_pelo_usuario == false)
		{
			printf("Frequencia: 0%% de aulas vistas\n");
		}
		else 
		{
			printf("Frequencia:%.2f%% de aulas vistas\n", situacao_aluno -> porcentagem_aulas_presentes);
		}
		
		printf("Media final: %.2f\n", situacao_aluno -> media_final_semestre);
		
		total_media_alunos += situacao_aluno -> media_final_semestre; //pegando o total de todas as medias
		total_alunos++;//total de todos os alunos
		
		
		if(situacao_aluno -> situacao_final == true)
		{
			printf("Situação final: APROVADO\n");
			total_alunos_aprovado++;//total de alunos aprovados
		}
		else
		{
			printf("Situação final: REPROVADO\n");
		}
		
		printf("--------------------------\n");
	}
	
	media_geral_alunos_aprovados = total_alunos_aprovado * 100 / total_alunos;
	printf("Percentual de alunos aprovados: %.2f%%\n", media_geral_alunos_aprovados);
	printf("Media Geral dos alunos: %.2f\n", total_media_alunos / total_alunos);
	printf("--------------------------\n");
	printf("\n\n\n\nPRESSIONE QUALQUER TECLA PARA CONTINUAR");
	getch();
}

void media_final_dos_alunos(Alunos* alunos_cadastrados)
{
	Alunos *alunos_nota_final_calculo = alunos_cadastrados;
	
	while(alunos_nota_final_calculo != NULL)
	{
		if((alunos_nota_final_calculo -> media_provas) >= QUANTIDADE_TOTAL_PASSAR_PROVAS)
		{
			alunos_nota_final_calculo -> media_final_semestre = 0.8 * alunos_nota_final_calculo -> media_provas + 0.2 * alunos_nota_final_calculo -> media_trabalhos;
		}
		else
		{
			alunos_nota_final_calculo -> media_final_semestre = 0,6 * alunos_nota_final_calculo -> media_provas;
		}
		alunos_nota_final_calculo = alunos_nota_final_calculo -> proximo;
	}
	
}
void aprovados_ou_nao(Alunos *alunos_cadastrados)
{
	Alunos *aprovacao = alunos_cadastrados;
	
	while(aprovacao != NULL)
	{
		if((aprovacao -> porcentagem_aulas_presentes) > QUANTIDADE_MINIMA_FRQUENCIA && (aprovacao -> media_final_semestre) > QUANTIDA_MINIMA_PONTOS_SEMESTRE)
		{
			aprovacao -> situacao_final = true;
		}
		aprovacao = aprovacao -> proximo;
	}
}
