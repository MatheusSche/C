#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int limite, sublimiteI, sublimiteJ, diferemodo, linha, coluna, sol=0; 
int mat_sudoku[9][9]={
                     {0,0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,0},
					 {0,0,0,0,0,0,0,0,0} };
                   
                   //DIFEREMODO=0 EH MODO CRIACAO
                   //DIFEREMODO=1 EH MODO JOGO


HANDLE stdhandle;

int tecla() {
  int c;
  c=getch();
  if(kbhit()&&(c==0||c==224))
    c = getch()*256;  // retorne no segundo byte se for funcao ou seta
  return(c);
}

void gotoxy(int x,int y) {
  COORD p;
  p.X=x;  p.Y=y;
  SetConsoleCursorPosition(stdhandle,p);
}

void cls()
{
   COORD coordScreen = { 0, 0 };    // home for the cursor
   DWORD cCharsWritten;
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   DWORD dwConSize;

   // Get the number of character cells in the current buffer.

   if( !GetConsoleScreenBufferInfo( stdhandle, &csbi ))
   {
      return;
   }

   dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

   // Fill the entire screen with blanks.

   if( !FillConsoleOutputCharacter( stdhandle,       // Handle to console screen buffer
                                    (TCHAR) ' ',     // Character to write to the buffer
                                    dwConSize,       // Number of cells to write
                                    coordScreen,     // Coordinates of first cell
                                    &cCharsWritten ))// Receive number of characters written
   {
      return;
   }

   // Get the current text attribute.

   if( !GetConsoleScreenBufferInfo( stdhandle, &csbi ))
   {
      return;
   }

   // Set the buffer's attributes accordingly.

   if( !FillConsoleOutputAttribute( stdhandle,        // Handle to console screen buffer
                                    csbi.wAttributes, // Character attributes to use
                                    dwConSize,        // Number of cells to set attribute
                                    coordScreen,      // Coordinates of first cell
                                    &cCharsWritten )) // Receive number of characters written
   {
      return;
   }

   SetConsoleCursorPosition( stdhandle, coordScreen ); // Put the cursor at its home coordinates.

}

void exportanomodocriacao () {
 	int vet[81];
 	int i, j, k=0;
 	
 	for (i=0;i<limite;i++){
 		for (j=0;j<limite;j++){
 			vet[k]=mat_sudoku[i][j];
 			k++;
		 }
	 }
	 
 	gotoxy(20,20); printf ("[");
 	for (k=0;k<(limite*limite);k++) {
 		printf ("%d", vet[k]);
	 }
	 printf("]");
 }
 
 void  zera_matriz() {
 	
 	int lin, col;
 	
 	for (lin=0;lin<limite;lin++){
	    		for (col=0;col<limite;col++){
	    			mat_sudoku[lin][col]=0;
				}
			}
 	
 }
 
void DesenhaMenu () { //ESSA FUNÇÃO DESENHA O MENU DO JOGO
                      // DE ACORDO COM O MODO DE JOGO	
	if (diferemodo==1 || diferemodo==2) {
			gotoxy (40, 1);
	SetConsoleTextAttribute(stdhandle,BACKGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_INTENSITY);
             printf ("Modo Jogo");
    SetConsoleTextAttribute(stdhandle,FOREGROUND_BLUE+FOREGROUND_GREEN+FOREGROUND_RED);
    	gotoxy (40, 4);
	SetConsoleTextAttribute(stdhandle,BACKGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_INTENSITY);
             printf ("T=Alterar tamanho do tabuleiro.         ");
             gotoxy (40, 5);
             printf ("I=Carregar tabuleiro                    ");
			 gotoxy (40, 6);
             printf ("C=Alternar para modo criacao.           ");
             gotoxy (40, 7);
             printf ("Pressione ENTER para confirmar a jogada.");
             gotoxy (40, 8);
             printf ("ESC para sair.                          ");
    SetConsoleTextAttribute(stdhandle,FOREGROUND_BLUE+FOREGROUND_GREEN+FOREGROUND_RED);
	}
	else {
			gotoxy (40, 1);
	SetConsoleTextAttribute(stdhandle,BACKGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_INTENSITY);
             printf ("Modo Criacao");
    SetConsoleTextAttribute(stdhandle,FOREGROUND_BLUE+FOREGROUND_GREEN+FOREGROUND_RED);
    	gotoxy (40, 4);
	SetConsoleTextAttribute(stdhandle,BACKGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_INTENSITY);
             printf ("T=Alterar tamanho do tabuleiro.");
             gotoxy (40, 5);
             printf ("E=Exportar tabuleiro.          ");
             gotoxy (40, 6);
             printf ("J=Alternar para modo jogo.     ");
             gotoxy (40, 7);
             printf ("V=validar tabuleiro.           ");
             gotoxy (40, 8);
             printf ("ESC para sair.                 ");
    SetConsoleTextAttribute(stdhandle,FOREGROUND_BLUE+FOREGROUND_GREEN+FOREGROUND_RED);
	
   }

}

void DesenhaQuadro(int DimI, int DimJ, int SubDimI, int SubDimJ) {

  int i,j;

  for(i=0;i<DimI;i++) {
    if(i%SubDimI==0)
      if(i==0) {
        for(j=0;j<DimJ;j++) {
          if(j%SubDimJ==0)
            putchar(j==0?201:203);
          else
            putchar(209);
          putchar(205);putchar(205);putchar(205);
        }
        putchar(187);
        printf("\n");
      }
      else {
        for(j=0;j<DimJ;j++) {
          if(j%SubDimJ==0)
            putchar(j==0?204:206);
          else
            putchar(216);
          putchar(205);putchar(205);putchar(205);
        }
        putchar(185);
        printf("\n");
      }
    else {
      for(j=0;j<DimJ;j++) {
        if(j%SubDimJ==0)
          putchar(j==0?199:215);
        else
          putchar(197);
        putchar(196);putchar(196);putchar(196);
      }
      putchar(182);
      printf("\n");
    }
    for(j=0;j<DimJ;j++) {
      if(j%SubDimJ==0)
        putchar(186);
      else
        putchar(179);
      printf("   ");
    }
    putchar(186);
    printf("\n");
  }
  for(j=0;j<DimJ;j++) {
    if(j%SubDimJ==0)
      putchar(j==0?200:202);
    else
      putchar(207);
    putchar(205);putchar(205);putchar(205);
  }
  putchar(188);
  printf("\n");
}

void escrevenatela () { //MONTA UM JOGO INICIAL NO MODO JOGO
	    int lin, col, posicaovet=0;
	    
		int vet4x4[16]={3,4,1,0,0,2,0,0,0,0,2,0,0,1,4,3};
		int vet6x6[36]={0,0,3,0,1,0,5,6,0,3,2,0,0,5,4,2,0,3,2,0,6,4,5,0,0,1,
		                2,0,4,5,0,4,0,1,0,0}; 
		int vet9x9[81]={8,3,0,0,0,5,6,9,0,0,0,6,0,8,0,0,0,2,0,0,0,6,0,0,0,0,5,
                        6,0,0,0,0,3,0,0,0,3,0,5,0,0,0,9,0,6,0,0,0,9,0,0,0,0,7,
                        4,0,0,0,0,2,0,0,0,5,0,0,0,4,0,1,0,0,0,8,7,1,0,0,0,4,9};
	    
	  if (diferemodo==1) {
	    if (limite==4) {
	    	for (lin=0;lin<limite;lin++){
	    		for (col=0;col<limite;col++){
	    			mat_sudoku[lin][col]=vet4x4[posicaovet];
	    			posicaovet++;
				}
			}
		}
		if (limite==6) {
	    	for (lin=0;lin<limite;lin++){
	    		for (col=0;col<limite;col++){
	    			mat_sudoku[lin][col]=vet6x6[posicaovet];
	    			posicaovet++;
				}
			}
		}
		if (limite==9) {
	    	for (lin=0;lin<limite;lin++){
	    		for (col=0;col<limite;col++){
	    			mat_sudoku[lin][col]=vet9x9[posicaovet];
	    			posicaovet++;
				}
			}
		}
	    
        
		if (diferemodo==1 && limite==9) {		   		           
         for (lin=0;lin<limite;lin++){
         	for (col=0;col<limite;col++) {
         		if (mat_sudoku[lin][col]!=0) {
         			 gotoxy(2+col*4,1+lin*2);
         			 SetConsoleTextAttribute(stdhandle,BACKGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_INTENSITY);
                     printf("%d",mat_sudoku[lin][col]); 
					 SetConsoleTextAttribute(stdhandle,FOREGROUND_BLUE+FOREGROUND_GREEN+FOREGROUND_RED);        			
				 }
			 }
		 }
	}
	
		if (diferemodo==1 && limite==6) {		   		           
         for (lin=0;lin<limite;lin++){
         	for (col=0;col<limite;col++) {
         		if (mat_sudoku[lin][col]!=0) {
         			 gotoxy(2+col*4,1+lin*2);
         			 SetConsoleTextAttribute(stdhandle,BACKGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_INTENSITY);
                     printf("%d",mat_sudoku[lin][col]); 
					 SetConsoleTextAttribute(stdhandle,FOREGROUND_BLUE+FOREGROUND_GREEN+FOREGROUND_RED);        			
				 }
			 }
		 }
	}
	
		if (diferemodo==1 && limite==4) {		   		           
         for (lin=0;lin<limite;lin++){
         	for (col=0;col<limite;col++) {
         		if (mat_sudoku[lin][col]!=0) {
         			 gotoxy(2+col*4,1+lin*2);
         			 SetConsoleTextAttribute(stdhandle,BACKGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_INTENSITY);
                     printf("%d",mat_sudoku[lin][col]); 
					 SetConsoleTextAttribute(stdhandle,FOREGROUND_BLUE+FOREGROUND_GREEN+FOREGROUND_RED);        			
				 }
			 }
		 }
	}
}
		
}

void varios_jogos (int a, int b, int c, int d) {
	
	int escolha, lin, col, k=0;
	int vet1_4x4[16]={0,1,4,0,0,4,2,0,0,2,3,0,0,3,1,0};
	int vet1_6x6[36]={3,0,4,2,0,5,0,2,0,0,6,0,0,0,2,1,0,0,0,0,1,5,0,0,
	                  2,0,3,6,0,1};
	int vet1_9x9[81]={0,0,8,0,1,0,0,0,9,6,0,1,0,9,0,3,2,0,0,4,0,0,3,7,0,0,5,
	                  0,3,5,0,0,8,2,0,0,0,0,2,6,5,0,8,0,0,0,0,4,0,0,1,7,5,0,
					  5,0,0,3,4,0,0,8,0,0,9,7,0,8,0,5,0,6,1,0,0,0,6,0,9,0,0};
	int vet2_4x4[16]={0,4,0,1,3,0,0,0,0,0,0,4,0,0,0,0}; 
	int vet2_6x6[36]={6,4,0,2,0,0,0,5,1,0,0,0,3,6,4,0,0,2,5,0,0,4,3,6,0,0,0,
	                  6,4,0,0,0,6,0,2,5}; 
	int vet2_9x9[81]={3,0,0,2,4,0,0,6,0,0,4,0,0,0,0,0,5,3,1,8,9,6,3,5,4,0,0,
	                  0,0,0,0,8,0,2,0,0,0,0,7,4,9,6,8,0,1,8,9,3,1,5,0,6,0,4,
					  0,0,1,9,2,0,5,0,0,2,0,0,3,0,0,7,4,0,9,6,0,5,0,0,3,0,2};
	int vet3_4x4[16]={0,2,4,0,1,0,0,3,4,0,0,2,0,1,3,0}; 
	int vet3_6x6[36]={0,0,0,0,0,6,2,0,4,0,5,0,0,2,1,0,0,0,0,0,0,4,1,0,0,4,0,
	                  6,0,5,3,0,0,0,0,0};
	int vet3_9x9[81]={8,0,0,0,0,0,0,0,0,0,0,3,6,0,0,0,0,0,0,7,0,0,9,0,2,0,0,
	                  0,5,0,0,0,7,0,0,0,0,0,0,0,4,5,7,0,0,0,0,0,1,0,0,0,3,0,
					  0,0,1,0,0,0,0,6,8,0,0,8,5,0,0,0,1,0,0,9,0,0,0,0,4,0,0};
	
	printf ("Escolha um jogo\n");
     		printf ("1. Jogo 1(Facil)\n");
     		printf ("2. Jogo 2(Medio)\n");
     		printf ("3. Jogo 3(Dificil)\n");
			   scanf ("%d", &escolha);
			      if (escolha>3) {
				   while (escolha>3) {
			       	  printf ("Opcao invalida");
			       	  scanf ("%d", &escolha);
				   } 
		          }
		          cls();
		          DesenhaQuadro(a, b, c, d);
		          DesenhaMenu();
     		switch (escolha) { 
			    case 1:
			    	
			    	if (limite==4) {
	    	        for (lin=0;lin<limite;lin++){
	    		       for (col=0;col<limite;col++){
	    			      mat_sudoku[lin][col]=vet1_4x4[k];
	    			      k++;
			        	}
			        }
		        }
	            	if (limite==6) {
	            	for (lin=0;lin<limite;lin++){
	    		      for (col=0;col<limite;col++){
	    			      mat_sudoku[lin][col]=vet1_6x6[k];
	    			      k++;
			        	}
		        	}
	        	}
	            	if (limite==9) {
	    	        for (lin=0;lin<limite;lin++){
	    	          for (col=0;col<limite;col++){
	    			        mat_sudoku[lin][col]=vet1_9x9[k];
	    		        	k++;
			        	}
		        	}
	        	}
			    	
			    	
			    	break;
			    case  2:
			    	
			    	if (limite==4) {
	    	        for (lin=0;lin<limite;lin++){
	    		       for (col=0;col<limite;col++){
	    			      mat_sudoku[lin][col]=vet2_4x4[k];
	    			      k++;
			        	}
			        }
		        }
	            	if (limite==6) {
	            	for (lin=0;lin<limite;lin++){
	    		      for (col=0;col<limite;col++){
	    			      mat_sudoku[lin][col]=vet2_6x6[k];
	    			      k++;
			        	}
		        	}
	        	}
	            	if (limite==9) {
	    	        for (lin=0;lin<limite;lin++){
	    	          for (col=0;col<limite;col++){
	    			        mat_sudoku[lin][col]=vet2_9x9[k];
	    		        	k++;
			        	}
		        	}
	        	}
			    	
				    break;
				case 3:
					
					if (limite==4) {
	    	        for (lin=0;lin<limite;lin++){
	    		       for (col=0;col<limite;col++){
	    			      mat_sudoku[lin][col]=vet3_4x4[k];
	    			      k++;
			        	}
			        }
		        }
	            	if (limite==6) {
	            	for (lin=0;lin<limite;lin++){
	    		      for (col=0;col<limite;col++){
	    			      mat_sudoku[lin][col]=vet3_6x6[k];
	    			      k++;
			        	}
		        	}
	        	}
	            	if (limite==9) {
	    	        for (lin=0;lin<limite;lin++){
	    	          for (col=0;col<limite;col++){
	    			        mat_sudoku[lin][col]=vet3_9x9[k];
	    		        	k++;
			        	}
		        	}
	        	}
					
				    break;		
			 }
			 
			 if (diferemodo==2 && limite==9) {		   		           
         for (lin=0;lin<limite;lin++){
         	for (col=0;col<limite;col++) {
         		if (mat_sudoku[lin][col]!=0) {
         			 gotoxy(2+col*4,1+lin*2);
         			 SetConsoleTextAttribute(stdhandle,BACKGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_INTENSITY);
                     printf("%d",mat_sudoku[lin][col]); 
					 SetConsoleTextAttribute(stdhandle,FOREGROUND_BLUE+FOREGROUND_GREEN+FOREGROUND_RED);        			
				 }
			 }
		 }
	}
	
		if (diferemodo==2 && limite==6) {		   		           
         for (lin=0;lin<limite;lin++){
         	for (col=0;col<limite;col++) {
         		if (mat_sudoku[lin][col]!=0) {
         			 gotoxy(2+col*4,1+lin*2);
         			 SetConsoleTextAttribute(stdhandle,BACKGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_INTENSITY);
                     printf("%d",mat_sudoku[lin][col]); 
					 SetConsoleTextAttribute(stdhandle,FOREGROUND_BLUE+FOREGROUND_GREEN+FOREGROUND_RED);        			
				 }
			 }
		 }
	}
	
		if (diferemodo==2 && limite==4) {		   		           
         for (lin=0;lin<limite;lin++){
         	for (col=0;col<limite;col++) {
         		if (mat_sudoku[lin][col]!=0) {
         			 gotoxy(2+col*4,1+lin*2);
         			 SetConsoleTextAttribute(stdhandle,BACKGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_INTENSITY);
                     printf("%d",mat_sudoku[lin][col]); 
					 SetConsoleTextAttribute(stdhandle,FOREGROUND_BLUE+FOREGROUND_GREEN+FOREGROUND_RED);        			
				 }
			 }
		 }
	}
}
	
void modocriacao () { //MENU DO MODO CRIAÇÃO
     int escolha;  
 	
 	cls();
 	diferemodo=0;
	printf ("Qual tamanho de tabuleiro vc prefere\n");
     		printf ("1. 4X4 (2X2)\n");
     		printf ("2. 6X6 (2X3)\n");
     		printf ("3. 9X9 (3X3)\n");
     		  scanf ("%d", &escolha);
			    if (escolha>3) {
				 while (escolha>3) {
			       	  printf ("Opcao invalida");
			       	  scanf ("%d", &escolha);
				   }  
			    }
     		switch (escolha) {
     			
     			case 1:
     				cls();
     				DesenhaQuadro (4, 4, 2, 2);
					 limite=4;
					 sublimiteI=2;
					 sublimiteJ=2;	
					 DesenhaMenu();
					 zera_matriz();
					 
     			break;	
     			
				 case 2:
				 	cls();
				 	DesenhaQuadro (6, 6, 2, 3);
					 limite=6;
					 sublimiteI=2;
					 sublimiteJ=3;		
					 DesenhaMenu();
					 zera_matriz();
     			break;
				 	
     			case 3:
     				cls();
     				DesenhaQuadro (9, 9, 3, 3);
					limite=9;
					sublimiteI=3;
					sublimiteJ=3;		
					DesenhaMenu();
					zera_matriz();
     			break;
			 }
	
}

void modojogo () {
	        
	        cls();
	        diferemodo=1; 
	        limite=9;
	        sublimiteI=3;
	        sublimiteJ=3;
	        DesenhaQuadro(9,9,3,3);
            escrevenatela();
			DesenhaMenu();
}

void mudatamanho () { //SEMPRE QUE SOLICITADO MUDANÇA DE TAMANHO DO TABULEIRO 
	int escolha;
	
	cls();
	zera_matriz();
	
	printf ("Qual tamanho de tabuleiro vc prefere\n");
     		printf ("1. 4X4 (2X2)\n");
     		printf ("2. 6X6 (2X3)\n");
     		printf ("3. 9X9 (3X3)\n");
			   scanf ("%d", &escolha);
			      if (escolha>3) {
				   while (escolha>3) {
			       	  printf ("Opcao invalida");
			       	  scanf ("%d", &escolha);
				   } 
		          }
     		switch (escolha) {
     			
     			case 1:
     				cls();
     				DesenhaQuadro (4, 4, 2, 2);
					 limite=4;	
					 sublimiteI=2;
					 sublimiteJ=2;
					 DesenhaMenu();
					 if (diferemodo==1) {
					 	escrevenatela();
					 }
					 if (diferemodo==2) {
					 	cls();
						 varios_jogos(4, 4, 2, 2);
					 	
					 }
				     
					
     			break;	
     			
				 case 2:
				 	cls();
				 	DesenhaQuadro (6, 6, 2, 3);
					 limite=6;	
					 sublimiteI=2;
					 sublimiteJ=3;
					 DesenhaMenu();
					 if (diferemodo==1) {
					 	escrevenatela();
					 }
					  if (diferemodo==2) {
					 	cls();
						 varios_jogos(6, 6, 2, 3);
                      }
					 
     			break;
				 	
     			case 3:
     				cls();
     				DesenhaQuadro (9, 9, 3, 3);
					limite=9;	
					sublimiteI=3;
					sublimiteJ=3;
					DesenhaMenu();
					 if (diferemodo==1) {
					 	escrevenatela();
					 }
					  if (diferemodo==2) {
					 	cls();
						 varios_jogos(9, 9, 3, 3);
                      }
				     
					 
     			break;
			 }
}

int verifica_fim () {
	int i, j;
	
	for (i=0;i<limite;i++) {
		for (j=0;j<limite;j++) {
			if (mat_sudoku[i][j]==0) {
				return 0;
			}
		}
	}
	
	return 1;
}

int validalinha(int lin, int num){
	
	int j;
	
	for (j=0;j<limite;j++) {
		if (mat_sudoku[lin][j]==num)
		return 1;
	}
  return 0;	
	
}

int validacoluna (int col, int num) {
	int i;
	
	for (i=0;i<limite;i++){
		if (mat_sudoku[i][col]==num)
		   return 1;
	}
	return 0;
}

int validaquadrante (int lin, int col, int num) {
	
	int l, c, lr, cr;
	
	 lr = lin / sublimiteI;
     cr = col / sublimiteJ;
  
       for (l = lr * sublimiteI; l < (lr + 1) * sublimiteI; l++) {
           for (c = cr * sublimiteJ; c < (cr + 1) * sublimiteJ; c++) {
               if (mat_sudoku[l][c] == num) {
	              return 1;
                }
            }
        }
	return 0;
}

void imprime() {

  static int solucoes = 0;
  int l, c;

  printf("      Solucao: %d\n", ++solucoes);
  for (l = 0; l < 9; l++) {
    for (c = 0; c < 9; c++) {
      printf(" %d", mat_sudoku[l][c]);
      if (c % 3 == 2) printf("  ");
    }
    printf("\n");
    if (l % 3 == 2) printf("\n");
  }

}

int verifica(int lin, int col, int n) {

  int l, c, lr, cr;

  if (mat_sudoku[lin][col] == n) return 1;
  if (mat_sudoku[lin][col] != 0) return 0;
  for (c = 0; c < limite; c++)
    if (mat_sudoku[lin][c] == n) return 0;
  for (l = 0; l < limite; l++)
    if (mat_sudoku[l][col] == n) return 0;
  lr = lin / sublimiteI;
  cr = col / sublimiteJ;
  for (l = lr * sublimiteI; l < (lr + 1) * sublimiteI; l++)
    for (c = cr * sublimiteJ; c < (cr + 1) * sublimiteJ; c++)
      if (mat_sudoku[l][c] == n) return 0;

  return 1;

}

int resolve(int lin, int col) {

  int n, t;
while (!kbhit()) {
  if (lin == limite){
	sol=sol+1;}
  else
    for (n = 1; n <= limite; n++)
      if ((verifica(lin, col, n))==1) {
        t = mat_sudoku[lin][col];
        mat_sudoku[lin][col] = n;
        if (col == limite-1)
          resolve(lin + 1, 0);
        else
          resolve(lin, col + 1);
        mat_sudoku[lin][col] = t;
      }

 return sol;
   }
}

void TrataTeclas() {
	int lin=0, col=0, num, alerta=0, sol1;
    int t,sair=0, reg=48, valid1, valid2, valid3;
    do {
    	 if (t==20480 || t==18432 || t==19712 || t==19200) { 
				  reg=48;
		}
       gotoxy(2+col*4,1+lin*2);
       t=tecla();
       switch(t) {
         case 20480: // seta para cima
             if(lin+1<limite) lin++;
             break;
         case 18432: // seta para baixo
             if(lin>0) lin--;
             break;
         case 19712:
         	 if (col+1<limite) col++; // seta para direita    
		     break;    
		 case 19200:
	         if (col>0) col--;	// seta para esquerda 	
		     break;   
		 case 43: // +
		 	if (mat_sudoku[lin][col]==0 || mat_sudoku[lin][col]>48) {
			  if (reg>46 && reg<limite+48) {
		 	 	reg++;
		 	 	putchar(reg);
			  }  
		    }
		   	 break;
		 case 45: //-
		 	if (mat_sudoku[lin][col]==0 || mat_sudoku[lin][col]>48) {
			  if (reg>48) {
		 	 	reg--;
		 	 	putchar(reg);
			  }
		   }
			   
		     break;
			 	
		 case 99 : //muda para criaçao C
		       gotoxy(20,20); printf("Deseja mudar para modo criacao? (s/n) ? ");
             do {
                  t=tecla();
             } while(t!='S' && t!='s' && t!='N' && t!='n');
             gotoxy(20,20); printf("                              ");
             if(t=='S' || t=='s'){
                  zera_matriz();
				  modocriacao();
            }
		 break;	
		 
		  case 67: //muda para criaçao c
		       gotoxy(20,20); printf("Deseja mudar para modo criacao? (s/n) ? ");
             do {
                  t=tecla();
             } while(t!='S' && t!='s' && t!='N' && t!='n');
             gotoxy(20,20); printf("                              ");
             if(t=='S' || t=='s') {
                  zera_matriz();
				  modocriacao();
            }
          
		 break;	
		 
		 case 74: //muda para jogo J
		      gotoxy(20,20); printf("Deseja mudar para modo criacao? (s/n) ? ");
             do {
                  t=tecla();
             } while(t!='S' && t!='s' && t!='N' && t!='n');
             gotoxy(20,20); printf("                              ");
             if(t=='S' || t=='s') 
				  modojogo();
		 break;	
		 
		  case 106: //muda para jogo j
		      gotoxy(20,20); printf("Deseja mudar para modo criacao? (s/n) ? ");
             do {
                  t=tecla();
             } while(t!='S' && t!='s' && t!='N' && t!='n');
             gotoxy(20,20); printf("                              ");
             if(t=='S' || t=='s')
				  modojogo();
		
		 break;	
		 
		 case 84: //muda tamanho T
		      gotoxy(20,20); printf("Deseja mudar o tamanho do tabuleiro? (s/n) ? ");
             do {
                  t=tecla();
             } while(t!='S' && t!='s' && t!='N' && t!='n');
             gotoxy(20,20); printf("                              ");
             if(t=='S' || t=='s')
                  mudatamanho();
		 break;	
		 
		 case 116: //muda tamanho t
		      gotoxy(20,20); printf("Deseja mudar o tamanho do tabuleiro? (s/n) ? ");
             do {
                  t=tecla();
             } while(t!='S' && t!='s' && t!='N' && t!='n');
             gotoxy(20,20); printf("                              ");
             if(t=='S' || t=='s') 
				  mudatamanho();
		 break;
		 
		 case 105: // i
		    gotoxy(20,20); printf("Deseja um novo jogo? (s/n) ? ");
             do {
                  t=tecla();
             } while(t!='S' && t!='s' && t!='N' && t!='n');
             gotoxy(20,20); printf("                              ");
             if(t=='S' || t=='s') {
                 diferemodo=2;
				 mudatamanho();    
            }
		 	break;
		 
		 case 73: // I
		    gotoxy(20,20); printf("Deseja um novo jogo? (s/n) ? ");
             do {
                  t=tecla();
             } while(t!='S' && t!='s' && t!='N' && t!='n');
             gotoxy(20,20); printf("                              ");
             if(t=='S' || t=='s') {
                 diferemodo=2;
				 mudatamanho();    
            }      
		 	break;	
		 	
		 	case 101: // e (exporta)
		 	
		 	    gotoxy(20,20); printf("Deseja exportar? (s/n) ? ");
             do {
                  t=tecla();
             } while(t!='S' && t!='s' && t!='N' && t!='n');
             gotoxy(20,20); printf("                              ");
             if(t=='S' || t=='s')
		 		exportanomodocriacao();
		 		break;
		 		
		 	case 69: // E (exporta)
		 	    gotoxy(20,20); printf("Deseja exportar? (s/n) ? ");
             do {
                  t=tecla();
             } while(t!='S' && t!='s' && t!='N' && t!='n');
             gotoxy(20,20); printf("                              ");
             if(t=='S' || t=='s')
			 	exportanomodocriacao();
			 break;	
			case 118: //v valida no modo c
			gotoxy(20,20); printf("Deseja realmente validar o tabuleiro? (s/n) ? ");
             do {
                  t=tecla();
             } while(t!='S' && t!='s' && t!='N' && t!='n');
             gotoxy(20,20); printf("                                             ");
             if(t=='S' || t=='s') {
				 cls();
				 DesenhaMenu();
				 gotoxy(2,8); printf ("Calculando solucoes.....\n");
				 sol1=resolve(0,0);
				 if (sol1!=0) {
				     printf("\nJogo valido\nNumero de solucoes possiveis:%d", sol1);
			     }
			     else {
			     	printf ("Nao foram encontradas solucoes");
				 }
				  gotoxy(20,20); printf("Aperte s para voltar ");
             do {
                  t=tecla();
             } while(t!='S' && t!='s' && t!='N' && t!='n');
             gotoxy(20,20); printf("                              ");
             if(t=='S' || t=='s') {
				 sol=0;
				 modocriacao (); }
             }
			
			 break;
			 
			case 86: //v valida no modo c
			  
			  gotoxy(20,20); printf("Deseja realmente validar o tabuleiro? (s/n) ? ");
             do {
                  t=tecla();
             } while(t!='S' && t!='s' && t!='N' && t!='n');
             gotoxy(20,20); printf("                                             ");
             if(t=='S' || t=='s') {
				 cls();
				 DesenhaMenu();
				 printf ("\n\nCalculando solucoes.....\n");
				 sol1=resolve(0,0);
				 if (sol1!=0) {
				     printf("\nJogo valido\nNumero de solucoes possiveis:%d", sol1);
			     }
			     else {
			     	printf ("Nao foram encontradas solucoes");
				 }
				  gotoxy(20,20); printf("Aperte s para voltar ");
             do {
                  t=tecla();
             } while(t!='S' && t!='s' && t!='N' && t!='n');
             gotoxy(20,20); printf("                              ");
             if(t=='S' || t=='s') {
				 sol=0;
				 modocriacao (); }
             }
			 
	        break;	
	        
		 case 13: //enter
		 	gotoxy(20,20); printf("Deseja realmente validar essa jogada? (s/n) ? ");
             do {
                  t=tecla();
             } while(t!='S' && t!='s' && t!='N' && t!='n');
             gotoxy(20,20); printf("                                             ");
             if(t=='S' || t=='s') {
             	num=(reg-48);
				valid1=validalinha(lin, num);                 
                if (valid1==0) {
                	valid2=validacoluna(col, num);
               }
                if (valid2==0) {
                   valid3=validaquadrante(lin, col, num);
                }
                if (valid1==0 && valid2==0 && valid3==0){
                	gotoxy(20,20); printf ("SUCESSO\n");
					mat_sudoku[lin][col]=num;
				}
				if (valid1==1 || valid2==1 || valid3==1) {
					gotoxy(20,20);printf ("Contra as regras (dois numero iguais)\n");
			   } 
		   }
		    alerta=verifica_fim();
			   if (alerta==1) {
			   	gotoxy(20,20);
				   SetConsoleTextAttribute(stdhandle,BACKGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_INTENSITY);
                                 printf ("           PARABENS!!!!!             ");
				   gotoxy(20,21);printf ("         VOCE VENCEU O JOGO          ");
				   gotoxy(20,22);printf ("Pressione I para carregar novos jogos");
                   SetConsoleTextAttribute(stdhandle,FOREGROUND_BLUE+FOREGROUND_GREEN+FOREGROUND_RED);
			   }  
	     
            break;
		   		 
         case 27: // esc
             gotoxy(20,20); printf("Deseja realmente sair (s/n) ? ");
             do {
                  t=tecla();
             } while(t!='S' && t!='s' && t!='N' && t!='n');
             gotoxy(20,20); printf("                              ");
             if(t=='S' || t=='s')
                  sair=1;
             break;
         default: // após pronto, retirar esta mensagem abaixo
             gotoxy(20,20);
             SetConsoleTextAttribute(stdhandle,BACKGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_INTENSITY);
             printf("codigo tecla pressionada %5d",t);
             SetConsoleTextAttribute(stdhandle,FOREGROUND_BLUE+FOREGROUND_GREEN+FOREGROUND_RED);
       
       }
      
	   
    } while(!sair);

}


int main() { 
    int escolha, escolha2;
    int linha, coluna;
  
  stdhandle=GetStdHandle(STD_OUTPUT_HANDLE);
  srand(time(NULL));
  printf ("----------------------------\n");
  printf ("Bem vindo ao jogo de SUDOKU\n");
  printf ("----------------------------\n");
  printf ("       MENU:\n");
  printf ("1.Modo de Criacao\n");
  printf ("2.Modo de Jogo\n");
     scanf ("%d", &escolha);
       
       if (escolha>2) {
       	  while (escolha>2) {
       	  	printf ("Opcao invalida\n");
       	  	scanf ("%d", &escolha);
			 }
	   }
      
     switch (escolha) {
     	case 1:
     		cls();
     		modocriacao();
		break;
		case 2:
			cls();
			modojogo();
		break;    	 
	 }
  TrataTeclas(); 
}
