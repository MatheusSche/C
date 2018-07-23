//Nome: Matheus Scehnatto
//Data: 07/06/17
//Trabalho de Programação 2 parte 2
//OBS: Não consegui resolver um bug até o momento, ocorre erro ao pesquisar por informações 
//do filme da primeira linha, mas do restante dos filmes é pesquisado normalmente
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>




struct nodoFilme *filmeAtual;
struct nodoAtor *atorAtual;
struct nodoDiretor *diretorAtual;

struct filme {
	char titulo[100];
	char ano[5];
	char diretor[20];
	
};

struct ator {
	char nomeA[100];
	
};

struct diretor {
	char nomeD[100];
};

struct nodoDiretor{
	struct nodoDiretor *prox;
	struct nodoDiretor *ant;
	struct diretor dados;
	struct intermediario *atorx;
	struct intermediario2 *filmex;
};


struct nodoFilme {
	struct nodoFilme *prox;
	struct nodoFilme *ant;
	struct intermediario *ator;
	struct filme dados;
	struct intermediario3 *directorx;

};

struct nodoAtor {
	struct nodoAtor *prox;
	struct nodoAtor *ant;
	struct intermediario2 *filme;
	struct ator dados;
	struct intermediario3 *directorx;

};


struct intermediario {
	struct intermediario *prox=NULL;
	struct nodoAtor *atorz;

	
};

struct intermediario2 {
	struct intermediario2 *prox=NULL;
	struct nodoFilme *filmez;
};

struct intermediario3{
	struct intermediario3 *prox=NULL;
	struct nodoDiretor *diretorx;
	
};


void ajustaPonteirosDiretorFilme() {
	
	struct intermediario2 *ptaux= (struct intermediario2 *)malloc(sizeof(struct intermediario2));
	
	if(diretorAtual->filmex==NULL) {
		diretorAtual->filmex=ptaux;
		ptaux->filmez=filmeAtual;
		ptaux->prox=NULL;
	} else {
		ptaux->filmez=filmeAtual;
		ptaux->prox=diretorAtual->filmex;
		diretorAtual->filmex=ptaux;
		
	}
	
	struct intermediario3 *ptaux2= (struct intermediario3 *)malloc(sizeof(struct intermediario3));
	
		if(filmeAtual->directorx==NULL) {
			filmeAtual->directorx=ptaux2;
	    	ptaux2->diretorx=diretorAtual;
			ptaux2->prox=NULL;
	    } else {
			ptaux2->diretorx=diretorAtual;
			ptaux2->prox=filmeAtual->directorx;
			filmeAtual->directorx=ptaux2;
			
			
				
	}	
	
	
}


void ajustaPonteiros() {
	
	struct intermediario *ptaux= (struct intermediario *)malloc(sizeof(struct intermediario));
	ptaux->prox=NULL;
	if(filmeAtual->ator==NULL) {
		filmeAtual->ator=ptaux;
	    ptaux->atorz=atorAtual;
		ptaux->prox=NULL;
	} else {
		ptaux->atorz=atorAtual;
		ptaux->prox=filmeAtual->ator;
		filmeAtual->ator=ptaux;
		
	}
	
	struct intermediario2 *ptaux2= (struct intermediario2 *)malloc(sizeof(struct intermediario2));
		ptaux2->prox=NULL;
	if(atorAtual->filme==NULL) {
		atorAtual->filme=ptaux2;
	    ptaux2->filmez=filmeAtual;
		ptaux2->prox=NULL;
	} else {
		ptaux2->filmez=filmeAtual;
		ptaux2->prox=atorAtual->filme;
		atorAtual->filme=ptaux2;
		
	}	
}

void ReadString(char *outString, const char *msg, int strSize){
    printf(msg);
    fflush(stdin);
    fgets(outString, strSize, stdin);
    outString[strlen(outString)-1]='\0';
}   


void insereFilmeOrdenado (struct nodoFilme ** inicio , struct nodoFilme ** fim , struct filme movie ) {
	struct nodoFilme * ptaux; 
	ptaux=(struct nodoFilme *)malloc(sizeof(struct nodoFilme));
    ptaux->dados=movie;
    filmeAtual=ptaux;
	if (* inicio == NULL || (strcmp((*inicio)->dados.titulo, movie.titulo)>0)) {
		ptaux -> prox =* inicio ;
		ptaux -> ant = NULL ;
	if (* inicio != NULL ) (* inicio )-> ant = ptaux ;
	else * fim = ptaux ;
	* inicio = ptaux ;
	return ;
  }
	struct nodoFilme * ptaux2 =* inicio ;
	while ( ptaux2 -> prox != NULL && strcmp (ptaux2 ->prox ->dados.titulo, movie.titulo)<0 ) ptaux2 = ptaux2 -> prox ;
		ptaux -> prox =ptaux2 -> prox ;
		ptaux -> ant = ptaux2 ;
		ptaux2 -> prox = ptaux ;
		if (ptaux -> prox == NULL ) // inserção no final da lista
		(* fim )= ptaux ;
		else
		ptaux ->prox -> ant = ptaux ;
return ;
}

void insereAtorOrdenado (struct nodoAtor ** inicio , struct nodoAtor ** fim , struct ator actor ) {
	struct nodoAtor * ptaux; 
	ptaux=(struct nodoAtor *)malloc(sizeof(struct nodoAtor));
    ptaux->dados=actor;
    atorAtual=ptaux;
    ajustaPonteiros();
	if (* inicio == NULL || strcmp((*inicio)->dados.nomeA, actor.nomeA)>0) {
		ptaux -> prox =* inicio ;
		ptaux -> ant = NULL ;
	if (* inicio != NULL ) {
	(* inicio )-> ant = ptaux ;
    } else{
	 * fim = ptaux ;
    }
	* inicio = ptaux ;
	return ;
  }
	struct nodoAtor * ptaux2 =* inicio ;
	while ( ptaux2 -> prox != NULL && strcmp (ptaux2 ->prox ->dados.nomeA, actor.nomeA)<0 ){
	  ptaux2 = ptaux2 -> prox ;
	
	} 
		ptaux -> prox =ptaux2 -> prox ;
		ptaux -> ant = ptaux2 ;
		ptaux2 -> prox = ptaux ;
		if (ptaux -> prox == NULL ) { // inserção no final da lista
		  (* fim )= ptaux ;
		}else {
	    	ptaux ->prox -> ant = ptaux ;
	}
return ;
}

int verificaFilme2 (struct nodoFilme **inicio, struct filme movieh) {
  int posicao=0;	
  struct nodoFilme *atual = *inicio;
  while(atual != NULL){
	 if(strcmp(atual->dados.titulo, movieh.titulo) == 0){
        filmeAtual=atual;
		return 1;
     }
     else{
     	posicao++;
	 }
	 atual = atual->prox;
  }
  return 0;
	
}

int verificaDiretor (struct nodoDiretor **inicio, char *dir) {	
  struct nodoDiretor *atual = *inicio;
  while(atual != NULL){
	 if(strcmp(atual->dados.nomeD, dir) == 0){
        diretorAtual=atual;
		return 1;
     }
     else{
     
	 }
	 atual = atual->prox;
  }
  return 0;
	
}


int verificaSeAtorLista (struct nodoAtor ** inicio, struct ator actor ) {
  int posicao = 0;  
  struct nodoAtor *atual = *inicio;
  while(atual != NULL){
	 if(strcmp(atual->dados.nomeA, actor.nomeA) == 0){
        atorAtual=atual;
		return 1;
     }
     else{
     	posicao++;
	 }
	 atual = atual->prox;
  }
  return 0;
	
}

int verificaSeAtorLista2 (struct nodoAtor * inicio, char ator[] ) {
  int posicao = 0;  
  struct nodoAtor *atual = inicio;
  while(atual != NULL){
	 if(strcmp(atual->dados.nomeA, ator) == 0){
		return 1;
     }
     else{
     	posicao++;
	 }
	 atual = atual->prox;
  }
  return 0;
	
}
void ordena(struct intermediario2 *inicioListaDeFilme){ //Ordena a lista em ordem crescente.
	struct intermediario2 *ant;
	struct intermediario2 *atual;
	struct nodoFilme *aux_filme;
	int trocou=1;
	while(trocou==1){
		trocou=0;
		ant=inicioListaDeFilme;//Primeiro nodo
		atual=inicioListaDeFilme->prox;//Segundo nodo
		while(atual != NULL){
			if(strcmp(ant->filmez->dados.ano,atual->filmez->dados.ano)>0){
				aux_filme = ant->filmez;
				ant->filmez = atual->filmez;
				atual->filmez = (aux_filme);
				trocou=1;
			}
			ant=atual;
			atual=atual->prox;
		}
	}
}

void buscaEPrintaFilmes(struct nodoAtor *inicio, char ator[]) {
  
  struct nodoAtor *atual = inicio;
  struct intermediario2 *atual2;
  while(atual != NULL){
	 if(strcmp(atual->dados.nomeA, ator) == 0){
		atual2=atual->filme;
		ordena(atual2);
		while (atual2!=NULL) {
			printf ("(%s) %s\n", atual2->filmez->dados.ano, atual2->filmez->dados.titulo);
			atual2=atual2->prox;
		}
     }
    
	 atual = atual->prox;
  }	
	
}

void buscaEPrintaFilmesDiretor(struct nodoDiretor *inicio, char *diretor) {
  struct nodoDiretor *atual = inicio;
  struct intermediario2 *atual2;
  while(atual != NULL){
	 if(strcmp(atual->dados.nomeD, diretor) == 0){
		atual2=atual->filmex;
		ordena(atual2);
		while (atual2!=NULL) {
			printf ("(%s) %s\n", atual2->filmez->dados.ano, atual2->filmez->dados.titulo);
			atual2=atual2->prox;
		}
     }
    
	 atual = atual->prox;
  }	
	
}

void escreveDiretor (struct nodoDiretor *fim) {
	struct nodoDiretor  *auxDiretor = fim;
  printf ("-------------------------------\n");
  printf("Ordem Alfabética Reversa\n");
  if(auxDiretor == NULL){
     printf("Lista Vazia\n");
  }
  else{
     while(auxDiretor != NULL){
     	printf("Filme: [%s]\n", auxDiretor->dados.nomeD );  
	    auxDiretor=auxDiretor->prox;
     }
   }
   printf ("-------------------------------\n");
}

	
void escreveEmOrdemAlfabeticaFilme (struct nodoFilme *fim) {
	struct nodoFilme  *auxFilme = fim;
  printf ("-------------------------------\n");
  printf("Ordem Alfabética Reversa\n");
  if(auxFilme == NULL){
     printf("Lista Vazia\n");
  }
  else{
     while(auxFilme != NULL){
     	printf("Filme: [%s]\n", auxFilme->dados.titulo );  
	    auxFilme=auxFilme->prox;
     }
   }
   printf ("-------------------------------\n");
}

void escreveEmOrdemAlfabeticaReversaFilme (struct nodoFilme *fim) {
	struct nodoFilme  *auxFilme = fim;
  printf ("-------------------------------\n");
  printf("Ordem Alfabética Reversa\n");
  if(auxFilme == NULL){
     printf("Lista Vazia\n");
  }
  else{
     while(auxFilme != NULL){
     	printf("Filme: [%s]\n", auxFilme->dados.titulo );  
	    auxFilme=auxFilme->ant;
     }
   }
   printf ("-------------------------------\n");
}

void escreveEmOrdemAlfabeticaAtor (struct nodoAtor *inicio) {
	struct nodoAtor *aux = inicio;
  printf("Ordem Alfabética\n");
  if(aux == NULL){
     printf("Lista Vazia\n");
  }
  else{
     while(aux != NULL){
     	printf("Ator: [%s]\n", aux->dados.nomeA);  
	    aux=aux->prox;
     }
   }
   printf ("---------------------------------\n");
}

void escreveEmOrdemAlfabeticaReversaAtor (struct nodoAtor *fim) {
	struct nodoAtor *aux = fim;
  printf("Ordem Alfabética Reversa\n");
  if(aux == NULL){
     printf("Lista Vazia\n");
  }
  else{
     while(aux != NULL){
     	printf("Ator: %s\n", aux->dados.nomeA);  
	    aux=aux->ant;
     }
   }
   printf ("-------------------------------\n");
}

int verificaFilme (struct nodoFilme **inicio, char *filmex ) {
  int posicao = 0;  
  struct nodoFilme *atual = *inicio;
  while(atual != NULL){
	 if(strcmp(atual->dados.titulo, filmex) == 0){
		filmeAtual=atual;
		return 1;
     }
     else{
     	posicao++;
	 }
	 atual = atual->prox;
  }
  return 0;
	
}

void excluiAtor(struct nodoAtor **inicio, struct nodoAtor **fim){
  int resp = 0;  
  struct nodoAtor *atual = *inicio;
  
  if((*inicio==*fim) && (*inicio!=NULL))//Lista com um elemento
  {  
     *inicio = NULL;
     *fim = NULL;
     free(atual);	
  }  
  else{
  		if(inicio!=NULL){
  			*inicio = (*inicio)->prox;
  			(*inicio)->ant=NULL;
        	free(atual); //libera o espaço ocupado na memória	
		}
  		else{
     		printf("Lista Vazia\n");  
  		}		  	
  }
}

void excluiFimAtor(struct nodoAtor **inicio, struct nodoAtor **fim){
  int resp = 0;  
  struct nodoAtor *atual = *fim;
  if((*inicio==*fim) && (*inicio!=NULL)){ //Lista com um elemento
     *inicio = NULL;
     *fim = NULL;
     free(atual);
  }
  else{
    if(inicio != NULL){//Lista com vários elementos
		*fim=(*fim)->ant;
     	(*fim)->prox = NULL;
     	free(atual);
  	}	
  	else{
    	printf("Lista Vazia\n");  
  	}		
  }
}
void excluiAtorSemFilme(struct nodoAtor **inicio, struct nodoAtor **fim, char *atorx) {  
  struct nodoAtor *atual = *inicio;
  struct nodoAtor *ant = NULL;
          if((*inicio)->prox == NULL){ //testa se a lista só possui um elemento
          // Valor existe na lista, mas a lista só possui um elemento
             free(*inicio);
             *inicio = NULL;
             *fim=NULL;
          }
          else{
               if(strcmp(atual->dados.nomeA, atorx)  == 0){ //Lista possui vários elementos e o elemento a ser excluido é o primeiro
                  excluiAtor(inicio, fim);
               }
               else{ //acha o valor a ser excluído
                  while(strcmp(atual->dados.nomeA, atorx) != 0){
                     ant = atual;
                     atual = atual->prox;
                  }
                  if(atual->prox==NULL){ //Excluir o último
                  	excluiFimAtor(inicio, fim);
				  }
                  else{
                  	ant->prox = atual->prox;
                  	atual->prox->ant = atual->ant;
                    free(atual);	
				  } 
               }
          }
     }
          




void removeFilmeDaListaDoAtor(char *filme, struct nodoAtor **inicio, nodoAtor **fim ) {
	struct intermediario2 *ant;
	struct intermediario2 *ptaux;
	ptaux=atorAtual->filme;
		if((strcmp(ptaux->filmez->dados.titulo, filme)==0)||(ptaux->prox==NULL)) {
			if((strcmp(ptaux->filmez->dados.titulo, filme)==0)&&(ptaux->prox!=NULL)) {
				atorAtual->filme=ptaux->prox;
			    free(ptaux);
			} else {
				if (ptaux->prox==NULL) {
						free(ptaux);
						excluiAtorSemFilme(inicio, fim, atorAtual->dados.nomeA);	
				}
			}
			
			//atorAtual->filme=NULL;
					
		} else {
			ant=ptaux;
			ptaux=ptaux->prox;
			while (strcmp(ptaux->filmez->dados.titulo, filme)!=0) {
				ant=ptaux;
				ptaux=ptaux->prox;
			}
			if (ptaux->prox==NULL) {
				free(ptaux);
				ant->prox=NULL;
			} else {
				ant->prox=ptaux->prox;
				free(ptaux);
			}
		}
}

void excluiFilmeListaDeAtores(char *filme, struct nodoAtor **inicio, struct nodoAtor **fim ) {
	struct intermediario *ptaux;
	ptaux=filmeAtual->ator;
	struct intermediario *noInicial=ptaux;
	while (ptaux!=NULL) {
		atorAtual=ptaux->atorz;
		removeFilmeDaListaDoAtor(filme, inicio, fim);
		ptaux=ptaux->prox;
		if (atorAtual->filme==NULL) {
			excluiAtorSemFilme(inicio, fim, atorAtual->dados.nomeA);
		}
	}
	
	while (noInicial->prox!=NULL) {
		ptaux=noInicial;
		noInicial=noInicial->prox;
		free(ptaux);
	}
	free(noInicial);
	filmeAtual->ator=NULL;
 }
 
 void exclui(struct nodoFilme **inicio, struct nodoFilme **fim){
  int resp = 0;  
  struct nodoFilme *atual = *inicio;
  
  if((*inicio==*fim) && (*inicio!=NULL))//Lista com um elemento
  {  
     *inicio = NULL;
     *fim = NULL;
     free(atual);	
  }  
  else{
  		if(inicio!=NULL){
  			*inicio = (*inicio)->prox;
  			(*inicio)->ant=NULL;
        	free(atual); //libera o espaço ocupado na memória	
		}
  		else{
     		printf("Lista Vazia\n");  
  		}		  	
  }
}

void excluiFim(struct nodoFilme **inicio, struct nodoFilme **fim){
  int resp = 0;  
  struct nodoFilme *atual = *fim;
  if((*inicio==*fim) && (*inicio!=NULL)){ //Lista com um elemento
     *inicio = NULL;
     *fim = NULL;
     free(atual);
  }
  else{
    if(inicio != NULL){//Lista com vários elementos
		*fim=(*fim)->ant;
     	(*fim)->prox = NULL;
     	free(atual);
  	}	
  	else{
    	printf("Lista Vazia\n");  
  	}		
  }
}

void escreveListaDuplicada (struct nodoFilme *fim) {
	struct nodoFilme  *auxFilme = fim;
  printf ("-------------------------------\n");
  printf("Ordem Alfabética Reversa\n");
  if(auxFilme == NULL){
     printf("Lista Vazia\n");
  }
  else{
     while(auxFilme != NULL){
     	printf("Filme: [%s]\n", auxFilme->dados.titulo );  
	    auxFilme=auxFilme->prox;
     }
   }
   printf ("-------------------------------\n");
}


void excluiFilmeDeSuaLista(struct nodoFilme **inicio, struct nodoFilme **fim, char *filme ){
  int resp = 0;  
  struct nodoFilme *atual = *inicio;
  struct nodoFilme *ant = NULL;
  		
  
          if((*inicio)->prox == NULL){ //testa se a lista só possui um elemento
          // Valor existe na lista, mas a lista só possui um elemento
             free(*inicio);
             *inicio = NULL;
             *fim=NULL;
          }
          else{
               if(strcmp(atual->dados.titulo, filme)  == 0){ //Lista possui vários elementos e o elemento a ser excluido é o primeiro
                  exclui(inicio, fim);
               }
               else{ //acha o valor a ser excluído
                  while(strcmp(atual->dados.titulo, filme) != 0){
                     ant = atual;
                     atual = atual->prox;
                  }
                  if(atual->prox==NULL){ //Excluir o último
                  	excluiFim(inicio, fim);
				  }
                  else{
                  	ant->prox = atual->prox;
                  	atual->prox->ant = atual->ant;
                    free(atual);	
				  } 
               }
          }  
}

void insereFimDiretor (struct nodoDiretor **inicio, struct nodoDiretor **fim, struct diretor directorx) {
	struct nodoDiretor *no;
	no = (struct nodoDiretor *)malloc(sizeof(struct nodoDiretor));
	no->dados=directorx;
	no->prox=NULL;
	no->ant = *fim;
	diretorAtual=no;
	if (*fim==NULL) {
		(*fim)=no;
		*inicio=no;
	} else {
		(*fim)->prox=no;
		no->ant=*fim;
		*fim=no;
	}
	
	
	
}

void buscaEPrintaParcerias(struct nodoAtor *inicio, char *ator) {
	struct nodoAtor *atual=inicio;
	struct intermediario2 *auxBuscaFilmes;
	struct intermediario *auxBuscaAtores;
	
	while(atual!=NULL) {
		if (strcmp(atual->dados.nomeA, ator)==0) {
			auxBuscaFilmes=atual->filme;
			while (auxBuscaFilmes!=NULL) {
				if (auxBuscaFilmes->filmez->ator->prox!=NULL) {
					//printf("\n");
					printf("\n[%s]\n", auxBuscaFilmes->filmez->dados.titulo);
					printf("Atores que trabalharam junto de [%s] no filme:\n", ator);
			   }  
				auxBuscaAtores=auxBuscaFilmes->filmez->ator;
				while (auxBuscaAtores!=NULL) {
					if (strcmp(auxBuscaAtores->atorz->dados.nomeA, ator)!=0) {
						printf ("%s\n", auxBuscaAtores->atorz->dados.nomeA);
				    }
					auxBuscaAtores=auxBuscaAtores->prox;
				}
				auxBuscaFilmes=auxBuscaFilmes->prox;
			}
		}
		atual=atual->prox;	
	}
	
	
}

void buscaEPrintaParceriasDiretor(struct nodoDiretor *inicioDiretor, char *diretor) {
	struct nodoDiretor *atual=inicioDiretor;
	struct intermediario2 *auxBuscaFilmes;
	struct intermediario *auxBuscaAtores;
	while(atual!=NULL) {
		if (strcmp(atual->dados.nomeD, diretor)==0) {
			auxBuscaFilmes=atual->filmex;
			while (auxBuscaFilmes!=NULL) {
					printf("\n[%s] foi diretor no filme [%s]\n", diretor, auxBuscaFilmes->filmez->dados.titulo);
					printf("Atores que foram dirigidos pelo diretor:\n");
				auxBuscaAtores=auxBuscaFilmes->filmez->ator;
				while (auxBuscaAtores!=NULL) {
					printf ("%s\n", auxBuscaAtores->atorz->dados.nomeA);
					auxBuscaAtores=auxBuscaAtores->prox;
					
				}
				auxBuscaFilmes=auxBuscaFilmes->prox;
				
			}
			
		}
		atual=atual->prox;	
	}

}


void insereListaDuplicada (struct nodoFilme **inicio, struct nodoFilme **fim, struct filme movie) {
	
	struct nodoFilme *no;
	no = (struct nodoFilme *)malloc(sizeof(struct nodoFilme));
	no->dados=movie;
	no->ant=NULL;
	no->prox=NULL;
	if (*inicio==NULL) {
		*inicio = no;
		*fim = no;
	} else {
		no->prox = *inicio;
		(*inicio)->ant = no;
		(*inicio) = no;
	}
			
}


void menu () {
	printf ("-------------------------------------------------------------------------\n");
	printf ("******************* TRABALHO DE PROGRAMACAO II **************************\n");
	printf ("0.Para sair do Programa\n");
	printf ("1.Listar o nome de todos os atores em ordem alfabetica e ordem reversa\n");
	printf ("2.Listar todos os filmes de um determinado ator em ordem cronologica\n");
	printf ("3.Listar todos os filmes em ordem alfabetica e alfabetica reversa\n");
	printf ("4.Inserir novos filmes\n");				
	printf ("5.Remocao de filmes\n");
	printf ("6.Listar Filmes de um determinado diretor\n");
	printf ("7.Listar atores que trabalharam diretamente com um dado ator\n");
	printf ("8.Listar atores que trabalharam diretamente com um dado Diretor\n");
	printf ("9.Listar os Filmes repetidos no arquivo\n");
	printf ("10.Listar os personagens de um ator\n");
	
	printf ("-------------------------------------------------------------------------\n");
}

int main () {
	FILE *arquivo=NULL;
	struct filme movie;
	struct ator actor;
	struct diretor director;
	char linha[3000], dado[300], ator[100], dados2[100], diretor[100];
	int i, j=0, personagem=0, flag=0, flux=0, flagA=0, opcao, aux, flagB=0, flagC, flagD, auxx;
	struct nodoFilme *inicioFilme=NULL, *fimFilme=NULL, *inicioListaDuplicada=NULL, *fimListaD=NULL;
	struct nodoAtor *inicioAtor=NULL, *fimAtor=NULL;
	struct nodoDiretor *inicioDiretor=NULL, *fimDiretor=NULL;


arquivo = fopen("resumo.txt","rt");
	while (fgets(linha, sizeof(linha), arquivo) != NULL) {

	for (i=0;i<strlen(linha);i++) {
											 //percorre o vetor linha até o fim
		for (j=strlen(dado);j>=0;j--){ // Limpa o vetor de dados
			dado[j]='\0';
		}
		j=0;
		while ((linha[i]!=',')&&(i<strlen(linha)-1) ) { //enquanto não encontra virgula  ou 
			if (linha[i]=='=') { //encontra o igual, é personagem
			    while (linha[i]!=',') {
			    	i++;
				}
			} else {
			  	 
			  	if ((linha[i-1]==',')&&(linha[i]=='d')&& (linha[i+1]=='i') && (linha[i+2]=='r')) {
				 		 flag=3;
				  		 flux=1;
				  		 i=i+4;
			    }
			dado[j]=linha[i];  //é a ultima palavra, copia os dados    
			j++;
			i++;
		  }
     	}
     
		if (flag==0) { //significa que é o título do filme
		   //printf ("O nome do filme é [%s]\n", dado);
		   strcpy(movie.titulo, dado);
		   flag=1;
		} else {
			if (flag==1) {//significa que é o ano do filme
				flag=2;
				if ((linha[i]==',') && (linha[i+1]==',')) {
					//printf ("Data nao inforamada\n");
				} else {
				strcpy (movie.ano,dado);
			   }
					  flag=3;
					  flagC=verificaFilme2(&inicioFilme, movie);
					  if (flagC==0) {
					  	insereFilmeOrdenado(&inicioFilme, &fimFilme, movie);
					  } else {
					  		insereListaDuplicada(&inicioListaDuplicada, &fimListaD, movie);
					  } 		
			
			} else {
				if (flag==3) {//significa que é o diretor do filme
					flag=4;
					if (linha[i]==',' && linha[i+1]==',') {
						//printf ("Diretor nao inforamada\n"
					} else {
						flagD=verificaDiretor(&inicioDiretor, dado);
							if (flagD==0) {
								strcpy(director.nomeD, dado);
								insereFimDiretor(&inicioDiretor, &fimDiretor, director);
								
				    	}
				    	ajustaPonteirosDiretorFilme();
					}
				} else {			
				    if (flag==4) {
				    	strcpy(actor.nomeA, dado);
					    flagA=verificaSeAtorLista(&inicioAtor, actor);
					    if (flagA==0) {		
						     insereAtorOrdenado (&inicioAtor, &fimAtor, actor);
				         }   else {
					           if (flagA==1) {
						         ajustaPonteiros();
						         //ajustaPonteirosDiretorAtor();
					           }
				           }
		               }
				    }
			}
		}	
	}//fim do for principal
	flag=0;
	flux=0;	

}//Fim do while principal
fclose(arquivo);
//INICIO DO MENU DE FUNÇÕES
  menu();
  printf("Digite sua opcao:\n");
  scanf("%d", &opcao);
  while(opcao!=0){
     switch(opcao){
        case 1: 
				printf ("---------------------------\n");  
		        printf ("1. Ordem Alfabetica\n");
        		printf ("2. Ordem Alfabetica Reversa\n");
        		scanf ("%d", &opcao);
        		if (opcao==1) {
        			escreveEmOrdemAlfabeticaAtor(inicioAtor);
				} else {
					escreveEmOrdemAlfabeticaReversaAtor(fimAtor);	
				}
        		  
                  break;
                  
        case 2: 
        		printf ("---------------------------\n");
        		printf ("De Qual Ator Verificar os Filmes\n");
	            ReadString(ator, "Informe o nome do ator: ", 100);
        		aux=verificaSeAtorLista2(inicioAtor, ator);
				if (aux==1) {
						buscaEPrintaFilmes(inicioAtor, ator);
				} else {
					printf ("Ator não encontrado\n");
				}
                  break;
                  
        case 3:
        	    printf ("---------------------------\n");
        		printf ("1. Ordem Alfabetica\n");
        		printf ("2. Ordem Alfabetica Reversa\n");
        		scanf ("%d", &opcao);
        		if (opcao==1) {
        			escreveEmOrdemAlfabeticaFilme(inicioFilme);
				} else {
					escreveEmOrdemAlfabeticaReversaFilme(fimFilme);	
				}
						 		
				 
                  break;
                  
        case 4: 
        		ReadString(dados2, "Informe o titulo do filme: ", 100);
        		strcpy(movie.titulo, dados2);
        		ReadString(dados2, "Informe o ano do filme: ", 100);
        		strcpy(movie.ano, dados2);
        		ReadString(dados2, "Informe o diretor do filme: ", 100);
        		strcpy(movie.diretor, dados2);
        		flagB=verificaFilme2(&inicioFilme, movie);
        			if (flagB==0) {
        				insereFilmeOrdenado(&inicioFilme, &fimFilme, movie);
        				opcao=1;
					} else {
						printf ("*****AVISO******\n");
						printf ("FILME EXISTENTE NA LISTA\n");
						printf ("**NAO SERA CADASTRADO**\n");
						opcao=0;
					}
        		
        		
        		
				while (opcao!=0) {
					ReadString(dados2, "Atores que participaram do filme: ", 100);
					strcpy(actor.nomeA, dados2);
					  flagA=verificaSeAtorLista(&inicioAtor, actor);
					    if (flagA==0) {		
						     insereAtorOrdenado (&inicioAtor, &fimAtor, actor);
				         }   else {
					           if (flagA==1) {
						         ajustaPonteiros();
					           }
				           }
					printf ("\n");
					printf ("0.Para finalizar o cadastro de atores\n");
					printf ("1.Para continuar o cadastro de atores\n");
					scanf ("%d", &opcao);
					printf ("\n");
        		}
        		
        		if (flagB==0) {
        			printf ("*******FILME CADASTRADO COM SUCESSO*******\n");
				}
                  break;
                  
        case 5: 
        		ReadString(dados2, "Qual Filme Remover: ", 100);
        		flagB=verificaFilme (&inicioFilme, dados2);
        		if (flagB==1) {
					excluiFilmeListaDeAtores(dados2, &inicioAtor, &fimAtor);
					excluiFilmeDeSuaLista(&inicioFilme, &fimFilme, dados2);
					//excluiAtorSemFilme(&inicioAtor, &fimAtor);
					printf ("FILME REMOVIDO COM SUCESSO\n");
				} else {
					printf ("Filme nao existe na lista\n");
				}
        		
                  break;
		case 6: 
        	    printf ("---------------------------\n");
        		printf ("De Qual Diretor Verificar os Filmes\n");
	            ReadString(diretor, "Informe o nome do diretor: ", 100);
        		auxx=verificaDiretor(&inicioDiretor, diretor);
				if (auxx==1) {
						buscaEPrintaFilmesDiretor(inicioDiretor, diretor);
				} else {
					printf (" não encontrado\n");
				}
        		
                  break;
        
		case 7: 
        		printf ("---------------------------\n");
        		printf ("De Qual Ator Verificar as Parcerias?\n");
	            ReadString(ator, "Informe o nome do ator: ", 100);
        		aux=verificaSeAtorLista2(inicioAtor, ator);
				if (aux==1) {
						buscaEPrintaParcerias(inicioAtor, ator);
				} else {
					printf ("Ator não encontrado\n");
				}
        		
                  break;
		
		case 8: 
        	    printf ("---------------------------\n");
        		printf ("De Qual Diretor Verificar as Parcerias?\n");
	            ReadString(diretor, "Informe o nome do Diretor: ", 100);
        		aux=verificaDiretor(&inicioDiretor, diretor);
				if (aux==1) {
						buscaEPrintaParceriasDiretor(inicioDiretor, diretor);
				} else {
					printf ("Diretor não encontrado\n");
				}
        		
                  break;
				  
		case 9: 
			printf("\nLista de Filme Repetidos na arquivo\n");
        	escreveListaDuplicada(inicioListaDuplicada);
        		
                  break;
		case 10: 
			printf("\n Nao foi implementado\n");
        	
        		
                  break;		  		  
				  		            
				                
     }              
                   
     menu();           
	 printf("Digite sua opcao:\n");
	 scanf("%d", &opcao);
  }	
}//fim do main
