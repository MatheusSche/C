#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* CABEÇALHO */

struct nodoParticipante *inicioP;
struct nodoParticipante *fimP;
struct nodoFigurinha *fimF;
struct nodoFigurinha *fimFR;

int quantidadeFig = 0;
int quantidadeFigRep = 0;
int quantidadePart = 10;
int quantidadeTrocas = 0;




/* FIM CABEÇALHO*/

struct nodoParticipante{
	char nome[30];
	char numero[10];
	int id;
	struct nodoParticipante *prox;
	struct nodoParticipante *ant;
	struct nodoFigurinha *proxFig;
	struct nodoFigurinha *proxFigRep;
};

struct nodoFigurinha{
	char nome[30];
	int fig;
	struct nodoFigurinha *prox;
	struct nodoFigurinha *ant;
	
};

// Procedimento para inserção no fim da lista
void insereParticipante(int id, char nome[], char numero[]){
  struct nodoParticipante *pnovo;

  pnovo=(struct nodoParticipante*)malloc(sizeof(nodoParticipante));
  pnovo->id = id;
  strcpy(pnovo->nome, nome);
  strcpy(pnovo->numero, numero);
  pnovo->prox=NULL;  
  pnovo->proxFig=NULL;
  pnovo->proxFigRep=NULL;

  struct nodoParticipante *atual = inicioP;
  if(inicioP == NULL){
     inicioP = pnovo;
     fimP = pnovo;
  }
  else{
       fimP->prox = pnovo;
       pnovo->ant=fimP;
       fimP=pnovo;  
  }
}

int verificaValor(int fig, int id){
	
	struct nodoParticipante *auxP = inicioP;
	
	
	
	
	while(auxP->id!=id){
		auxP = auxP->prox;
	}
	
	if (auxP->proxFig==NULL){
		return 0;
	}
	
	
	struct nodoFigurinha *inicioF = auxP->proxFig;
		while(inicioF!=NULL){
			if(inicioF->fig==fig){
				return 1;
			}
			inicioF = inicioF->prox;
		}
			return 0;
	
}

void insereFigurinha(int fig, int id){
	quantidadeFig=quantidadeFig + 1;	
	struct nodoParticipante *auxP = inicioP;
	
	while(auxP->id!=id){
		auxP = auxP->prox;
	}
	
	struct nodoFigurinha *inicioF = auxP->proxFig;
	
	struct nodoFigurinha *auxF; 
	auxF = (struct nodoFigurinha *)malloc(sizeof(struct nodoFigurinha));
	auxF->fig = fig;
	if (auxP->proxFig== NULL || (auxP->proxFig->fig>auxF->fig)) {
		auxF -> prox = auxP->proxFig ;
		auxF -> ant = NULL ;
	if (auxP->proxFig != NULL ) auxP->proxFig -> ant = auxF ;
	else fimF = auxF ;
	auxP->proxFig = auxF ;
	return ;
  }
	struct nodoFigurinha * ptaux2 = auxP->proxFig ;
	while ( ptaux2 -> prox != NULL &&(ptaux2->prox->fig < auxF->fig) ) ptaux2 = ptaux2 -> prox ;
		auxF -> prox =ptaux2 -> prox;
		auxF -> ant = ptaux2;
		ptaux2 -> prox = auxF ;
		if (auxF -> prox == NULL ) // inserção no final da lista
		( fimF )= auxF ;
		else
		auxF ->prox -> ant = auxF ;
return ;
	
	
	
}

void insereFigurinhaRepetida(int fig, int id){
	quantidadeFig=quantidadeFig + 1;
	quantidadeFigRep = quantidadeFigRep + 1;
	struct nodoParticipante *auxP = inicioP;
	
	while(auxP->id!=id){
		auxP = auxP->prox;
	}
	
	struct nodoFigurinha *auxF; 
	auxF = (struct nodoFigurinha *)malloc(sizeof(struct nodoFigurinha));
	auxF->fig = fig;
	if (auxP->proxFigRep == NULL || (auxP->proxFigRep->fig>auxF->fig)) {
		auxF -> prox = auxP->proxFigRep ;
		auxF -> ant = NULL ;
	if (auxP->proxFigRep != NULL ) auxP->proxFigRep -> ant = auxF ;
	else fimFR = auxF ;
	auxP->proxFigRep = auxF ;
	return ;
  }
	struct nodoFigurinha * ptaux2 = auxP->proxFigRep ;
	while ( ptaux2 -> prox != NULL &&(ptaux2->prox->fig < auxF->fig) ) ptaux2 = ptaux2 -> prox ;
		auxF -> prox =ptaux2 -> prox;
		auxF -> ant = ptaux2;
		ptaux2 -> prox = auxF ;
		if (auxF -> prox == NULL ) // inserção no final da lista
		( fimFR )= auxF ;
		else
		auxF ->prox -> ant = auxF ;
return ;
	
}

void escreveListaParticipante () {
  struct nodoParticipante  *aux = inicioP;
  printf ("-------------------------------\n");
  printf("Participantes\n");
  if(aux == NULL){
     printf("Lista Vazia\n");
  }
  else{
     while(aux != NULL){
     	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
     	printf("ID: [%d]\n", aux->id ); 
		printf("NOME: [%s]\n", aux->nome ); 
		printf("NUMERO: [%s]\n", aux->numero ); 
		printf("\n"); 
		printf("[Figurinhas]\n"); 
		struct nodoFigurinha *inicioF = aux->proxFig;
			while(inicioF!=NULL){
				printf("[%d] ", inicioF->fig);
				inicioF = inicioF->prox;
			}
		printf("\n"); 	
		printf("\n"); 
		printf("[Figurinhas Repetidas]\n");	
		struct nodoFigurinha *inicioFRep = aux->proxFigRep;
			while(inicioFRep!=NULL){
				printf("[%d] ", inicioFRep->fig);
				inicioFRep = inicioFRep->prox;
			}
		printf("\n");
		printf("\n"); 	
		printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");	
	    aux=aux->prox;
	    printf("\n"); 
     }
   }
   printf ("-------------------------------\n");
}

void escreve () {
  struct nodoParticipante  *aux = inicioP;
  printf ("-------------------------------\n");
  printf("[ID] [Participantes]\n");
  if(aux == NULL){
     printf("Lista Vazia\n");
  }
  else{
     while(aux != NULL){
     	printf("[%d][%s]\n", aux->id, aux->nome ); 
	    aux=aux->prox;
     }
   }
   printf ("-------------------------------\n");
}

void mostraUmParticipante(int id){
	
	struct nodoParticipante *aux = inicioP;
	
	while(aux->id!=id){
		aux = aux->prox;
	}
		printf("\n");
		printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	    printf("[ID: %d]\n", aux->id);
		printf("[Nome: %s]\n", aux->nome);
		printf("[Telefone: %s]\n",aux->numero );   
		printf("\n"); 
		printf("[Figurinhas]\n");
		struct nodoFigurinha *inicioF = aux->proxFig;
			while(inicioF!=NULL){
				printf("[%d] ", inicioF->fig);
				inicioF = inicioF->prox;
			}
		printf("\n");
		printf("\n");	
		printf("[Figurinhas Repetidas]\n");	
		struct nodoFigurinha *inicioFRep = aux->proxFigRep;
			while(inicioFRep!=NULL){
				printf("[%d] ", inicioFRep->fig);
				inicioFRep = inicioFRep->prox;
			}
	printf("\n");
	printf("\n");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	
}

void excluiValor(int fig, int id){
    quantidadeFig = quantidadeFig-1;
    quantidadeFigRep = quantidadeFigRep-1;
   struct nodoParticipante *auxP = inicioP;
   
   while(auxP->id!=id){
   	auxP=auxP->prox;
   } 
  struct nodoFigurinha *atual = auxP->proxFigRep;
  struct nodoFigurinha *ant = NULL;
  
  if(auxP->proxFigRep != NULL){
            if(auxP->proxFigRep->prox == NULL){ //testa se a lista só possui um elemento
          // Valor existe na lista, mas a lista só possui um elemento
             auxP->proxFigRep=NULL;
             fimFR=NULL;
             free(atual);
          }
          else{
               if(atual->fig == fig){ //Lista possui vários elementos e o elemento a ser excluido é o primeiro
                  auxP->proxFigRep = auxP->proxFigRep->prox;
                  auxP->proxFigRep->ant=NULL;
                  free(atual);
               }
               else{ //acha o valor a ser excluído
                  while(atual->fig != fig){
                     ant = atual;
                     atual = atual->prox;
                    
                  }
                  if(atual->prox==NULL) {//ULTIMO VALOR DA LISTA
                  	fimFR = atual->ant;
                    ant->prox=NULL;
                    free(atual);
				  } else{
				  	ant->prox = atual->prox;
                    atual->prox->ant = ant;
                    free(atual);
				  }
                  
                  
               }
          }  
     
  }
  else{
     printf("Lista Vazia\n");  
  }
}

void trocaFigurinhas(){
	int achouFigPai = 1;
	int achouFigFilho = 1;
	int teste=0;
	int recipienteAuxiliarPai;
	int recipienteAuxiliarFilho;

// OS FLAGS SÃO OS achouPai e achouFilho;	
// FLAG 0 == NÃO TEM, PODE TROCAR
// FLAG 1 == TEM, NÃO PODE TROCAR
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("Trocando Figurinhas\n");
	
	struct nodoParticipante *participantePai = inicioP;
	struct nodoParticipante *participanteFilho;
	struct nodoFigurinha *figurinhaRepPai;
	struct nodoFigurinha *figurinhaRepFilho;
//	struct nodoFigurinha *figurinhaPai = participantePai->proxFig;
//	struct nodoFigurinha *figurinhaFilho = participanteFilho->proxFig;
	
	while(participantePai->prox!=NULL){
		participanteFilho = participantePai->prox;//DEFINIU O PARTICIPANTE QUE ESTÁ TROCANDO COM O PAI QUE É SEMPRE O PRÓXIMO
		while(participanteFilho!=NULL) {
			
			figurinhaRepFilho = participanteFilho->proxFigRep;//DEFINIU O INICIO DA LISTA DE FIGURINHAS REPETIDAS DAQUELE QUE ESTÁ TROCANDO COM O PAI
			while(figurinhaRepFilho!=NULL){
				achouFigFilho = verificaValor(figurinhaRepFilho->fig, participantePai->id );
				teste=1;
				if(achouFigFilho==0){
					figurinhaRepPai = participantePai->proxFigRep;//DEFINIU O VALOR INICIAL DA LISTA DE FIGURINHAS REPETIDAS
					 
					while(figurinhaRepPai!=NULL && achouFigFilho==0){
						achouFigPai = verificaValor(figurinhaRepPai->fig, participanteFilho->id);
						
						if(achouFigPai==0){//VAI TROCAR POIS ENCONTROU VALORES QUE PODEM SER TROCADOS PARA OS DOIS PARTICIPANTES
							recipienteAuxiliarPai = figurinhaRepPai->fig;
							recipienteAuxiliarFilho = figurinhaRepFilho->fig;
						
							insereFigurinha(recipienteAuxiliarFilho, participantePai->id);//PAI
							insereFigurinha(recipienteAuxiliarPai, participanteFilho->id);//FILHO	
							printf("[%s]<->[%s]\n", participantePai->nome, participanteFilho->nome ); 
							printf("[%d]<->[%d]\n", recipienteAuxiliarPai, recipienteAuxiliarFilho );
							excluiValor(recipienteAuxiliarPai, participantePai->id);//PAI
							
							quantidadeTrocas=quantidadeTrocas+1;
							excluiValor(recipienteAuxiliarFilho, participanteFilho->id);//FILHO
							
							
						
							printf("\n");
								achouFigPai = 1;
								achouFigFilho = 1;
						
						}

						figurinhaRepPai = figurinhaRepPai->prox;
						
					}	
				}
				achouFigFilho = 1;
				
				figurinhaRepFilho = figurinhaRepFilho->prox;
			}
		   participanteFilho = participanteFilho->prox;
		   
	   }
		participantePai = participantePai->prox;
	}	
		printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		printf("\n");
}

void menu(){
	printf("\n");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("+++        ALBUM DE FIGURINHAS                      ++++\n");
	printf("+++   1. Cadastrar Participante                     ++++\n");
	printf("+++   2. Inserir Figurinha                          ++++\n");
	printf("+++   3. Trocar Figurinhas                          ++++\n");
	printf("+++   4. Total de Figurinhas                        ++++\n");
	printf("+++   5. Total de Figurinhas Repetidas              ++++\n");
	printf("+++   6. Mostrar dados de um Participante           ++++\n");
	printf("+++   7. Mostrar dados de todos os Participantes    ++++\n");
	printf("+++   8. Mostra lista de Participantes              ++++\n");
	printf("+++   9. Mostra quantidade de Trocas                ++++\n");
	printf("+++   10. Limpar Terminal                           ++++\n");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");		
	
}

int main(){
    
    char nome[30], numero[15], c;
    int fig, id, i, flag=0, opcao;
    
	FILE *dados;
    dados = fopen ("dadosLinha.txt", "r");
    if (dados == NULL) {
       printf ("Houve um erro ao abrir o arquivo.\n");
       return 1;
    }
   
   
   while(!feof(dados)) {
   	//for ( i = 0; i < 3; i++){
   		fscanf (dados, "%d", &id);
   		fscanf (dados, "%s", nome);
   		fscanf (dados, "%s", numero);
	  // }
	   
	   insereParticipante (id, nome, numero);
	   do{
	   		fscanf (dados, "%d", &fig);
	   		if (fig==0){
			   break;
			   }
			
			flag = verificaValor(fig, id);
			if (flag==0){
				insereFigurinha(fig, id);
			} 
			if(flag==1){
				insereFigurinhaRepetida(fig, id);
			}
	   		
	   } while(fig!=0);
   }

   
   
  system("cls"); 
  menu(); 
  printf("Digite sua opcao:\n");
  scanf ("%d", &opcao);
  while(opcao!=0){
     switch(opcao){
        case 1:   printf("Digite o nome:\n");
                  fflush(stdin);
                  gets(nome);
                  printf("Digite o telefone:\n");
                  fflush(stdin);
                  gets(numero);
                  quantidadePart=quantidadePart+1;
                  insereParticipante (quantidadePart, nome, numero);
                  printf("Participante inserido com Sucesso:\n");
                  break;
                  
        case 2: 
        		printf("Digite o numero da figurinha a inserir\n");
        		scanf("%d", &fig);
        		printf("Para qual Participante? Selecione pelo ID\n");
        		escreve();
        		scanf("%d", &id);
        		flag = verificaValor(fig, id);
			    if (flag==0){
					insereFigurinha(fig, id);
				} 
				if(flag==1){
					insereFigurinhaRepetida(fig, id);
				}
				printf("Figurinha inserida com Sucesso");
				printf("\n");
				
                  break;
            case 3:
            	trocaFigurinhas();
            	break;
			case 4:
				printf("\n");
            	printf("Total de Figurinhas em Jogo: [%d]\n", quantidadeFig);
            	printf("\n");
            	break;
			case 5:
				printf("\n");
            	printf("Total de Figurinhas Repetidas em Jogo: [%d]\n", quantidadeFigRep);
            	printf("\n");
            	break;
			case 6:
            	printf("Selecionar qual Participante? Selecione pelo ID\n");
        		escreve();
        		scanf("%d", &id);
        		mostraUmParticipante(id);
            	break;			      
            case 7:
            	escreveListaParticipante();
            	break;
            case 8:
            	escreve();
            	break;
            case 9:
            	printf("\n");
            	printf("Total de Figurinhas Trocadas em Jogo: [%d]\n", quantidadeTrocas);
            	printf("\n");
			    break;	
			case 10:
            	system("cls"); 
			    break;    
                         
     }                            
     menu();           
	 printf("Digite sua opcao:\n");
	 scanf("%d", &opcao); 
	
  }
   
   
}

