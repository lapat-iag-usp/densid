#include<stdio.h> 
#include<stdlib.h> 
#include<conio.h> 
#include<string.h> 
#include<ctype.h>
#define LMAX 80
//LIMITE MÁXIMO DE 500 .TXT

// Corrigir erros reportados para o Rio de Janeiro - 26/07/2013
// Descobri que no primeiro arquivo que dá pau, a partir de um certo elemento, seus dados são transladados para as demais colunas
// O Luis descobriu que se a parte 1 da amostra com defeito na apresentação dos dados tiver o mesmo número de elementos da parte 2 (Importante: do elemento 11 ao elemento 21), então o erro deixa de existir

// Correção do dia 02/08/2013 realizada pro Atenágoras Souza Silva
// Nas linhas (841(5) e 850(5) alterado o for de (p=vmin; p<=vmax1; p++) para (p=elemento[k-1]+1;p<=vmax;p++

// ÚLTIMA ALTERAÇÃO EM 04/07/2012
// Incluído erro no volume
//////////////////////////////// ALTERAÇÂO EM 19/06/2012, REALIZADA POR Atenágoras Souza Silva
// incerteza11 e incerteza13 foram criadas para corrigir o valor da incerteza nos elementos de Z=11 ou Z=13 19/06/2012
// incertzinco e incertbromo criadas 19/06/2012
// 
///////////////////////////////////////////////////////////////////////////////athenagoras@gmail.com///////////
////////////////////////VARIÁVEIS GERAIS DO PROGRAMA//////////////////////////////////////////////////////////
char nomevolume[500][80], ftrk[80], ftrl[80];
float guarda_volume[500], conv, ft_resposta[150][3];
/*Alterando os índices de contagem, energia, e incerteza para que sejam fixos.
A matriz elemento[30] já existia. Foi alterado o número de elementos dos
vetores contagem e incerteza (de 30 para 119). Os valores de 0-10 não serão lidos, nem para
Z >83. 118 é o número de elementos da tabela periódica
*/
int elemento[30],contagem[119],energia[119],incerteza[119], corrente, tempo, ind;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)//PROGRAMA PRINCIPAL, O QUAL CHAMA TODAS AS FUNÇÕES///////////////
{
    

   int num; // VARIAVEL QUE RECEBE O VALOR DO MENU
   num = 0;
   while(num != 2)
   {     
      system("cls"); //COMANDO QUE LIMPA A TELA//
      printf("--------------------------------------------------------------------------------");
      printf("                    DENSIDADE 2.8.4 - Pega Inseto (DEBUG MODE = ON)\n"); 
      printf("--------------------------------------------------------------------------------\n\n");
      printf("                        1---Calculos\n"); 
      printf("                        2---Sair\n\n\n\n"); 
      printf("Opcao ---> ");
      scanf("%d",&num); 
      switch(num) 
      { 
         case 1:
           calculos(); 
           break; 
         case 2: exit(0); 
         default: puts("                 OPCAO INVALIDA!!!! TENTE NOVAMENTE");fflush(stdin);getchar();
      }                 
   } 
} 
////////////////////////////////////////////////////////////////////////////////////                
////////////////////////////////////////////////////////////////////////////////////                
void calculos()//FUNÇÃO QUE REALIZA OS TRABALHOS RELACIONADOS COM A PARTE DE CALCULOS 
{ 
         FILE *arq, *arq2, *arq3, *arq4, *farea, *fbromo, *fzinco, *fteste, *arq5, *arq6,*fpteste /*para debug 26-07-2013*/,*fpteste2/*Para debug 30-07-2013*/;
         char nome_arq[100], nome_arq_2[100], caracter[500][500], caracter2[500][500], caracter3[500][500] ,ajuda[2], nome[10], volume[80], volumeb[80], ajuda2[80], imprime[90], rp[2], tst[2], nomeint[80], branco_aux[80];
         int VolAns,i, k, x, y, cont, conta, cont_aux, j, g, t, z, f, p, n, vmin1, vmin2, vmin3, vmax1, vmax2, vmax3, vminatual, vmaxatual, n_int, a_int, bn_int, ba_int, ma, contador, czinco, cbromo,Nvol, Ivol;//24/12/2011 Nvol armazena o número de arquivos que contem volumes para serem colocados nos índices. Obtida a partir de recortavolumes
         float fator11, fator13, matriz_media[500][220],matriz_erro_branco[500][220], aux, area,aux2,cont2,erro,aux3,pl, bromo, incertbromo, zinco, incertzinco, cont11, incerteza11, cont13, incerteza13,desvio_padraopc[119]/*20/10/2011*/, desvio_padraoi[500][220], aux4, aux5, vol,errovol=0;
         //07/08/2012 - Correção das incertezas percentuais no cálculo dos erros
         //04/07/2012 - introduzido erro no volume
          //Variáveis provisórias para debug
         int TamanhoString;
         fpteste = fopen("debugresultado.txt","w");
         fpteste2 = fopen("debugElementoZerado.txt","w");
         system("cls");
         printf("--------------------------------------------------------------------------------");
         printf("                         OPCAO (2) ---> CALCULOS\n");
         printf("--------------------------------------------------------------------------------\n\n");
         tst[1] = '*';
         while (tst[1] == '*')
         {
            farea = fopen("area.dat","r");
            fbromo = fopen("bromo.dat","r");
            fzinco = fopen("zinco.dat","r");
            fscanf(farea,"%f",&area);
            fscanf(fbromo,"%f",&bromo);
            fscanf(fzinco,"%f",&zinco);
            printf("\nO valor usado para a area do filtro e %f.\nDeseja altera-lo? (S/N)", area);
            fflush(stdin);
            scanf("%c",&rp[1]);
            while ((rp[1] != 'S') && (rp[1] != 's') && (rp[1] != 'N') && (rp[1] != 'n'))
            {
              printf("\nOpcao invalida!! Digite novamente!!");
              fflush(stdin);
              scanf("\n%c",&rp[1]);
            }
            if ((rp[1] == 'S') || (rp[1]=='s'))
            {
               printf("\nNova area:  ");
               scanf("%f",&area);
               fclose(farea);
               farea = fopen("area.dat","w");
               fprintf(farea,"%f",area);
               fclose(farea);
               printf("\nO valor da Area foi alterado com sucesso!");
            }
            else printf("\n\nO valor padrao sera utilizado.");
            printf("\n\nA correcao da relacao K, L usada para o Bromo e %f.\nDeseja altera-lo? (S/N)", bromo); 
            fflush(stdin);
            scanf("%c",&rp[1]);
            while ((rp[1] != 'S') && (rp[1] != 's') && (rp[1] != 'N') && (rp[1] != 'n'))
            {
              printf("\nOpcao invalida!! Digite novamente!!");
              fflush(stdin);
              scanf("\n%c",&rp[1]);
            }
            if ((rp[1] == 'S') || (rp[1]=='s'))
            {
               printf("\nNovo valor para a correcao do Bromo:  ");
               scanf("%f",&bromo);
               fclose(fbromo);
               fbromo = fopen("bromo.dat","w");
               fprintf(fbromo,"%f", bromo);
               fclose(fbromo);
               printf("\nO valor da correcao do Bromo foi alterado com sucesso!");
            }
            else printf("\n\nO valor padrao sera utilizado.");
            printf("\n\nA correcao da relacao K, L usada para o Zinco e %f.\nDeseja altera-lo? (S/N)", zinco); 
            fflush(stdin);
            scanf("\n%c",&rp[1]);
            while ((rp[1] != 'S') && (rp[1] != 's') && (rp[1] != 'N') && (rp[1] != 'n'))
            {
              printf("\nOpcao invalida!! Digite novamente!!");
              fflush(stdin);
              scanf("\n%c",&rp[1]);
            }
            if ((rp[1] == 'S') || (rp[1]=='s'))
            {
               printf("\nNovo valor para a correcao do Zinco:  ");
               scanf("%f",&zinco);
               fclose(fzinco);
               fzinco = fopen("zinco.dat","w");
               fprintf(fzinco,"%f", zinco);
               fclose(fzinco);
               printf("\nO valor da correcao do Zinco foi alterado com sucesso!");
            }
            else printf("\n\nO valor padrao sera utilizado.");
            La:
             fflush(stdin);
             printf("\n\nDigite o nome do arquivo que contem os Brancos: "); 
             scanf("%s",&nome_arq);
/////////////////////////////////////////////////////RECORTA OS NOMES DOS BRANCOS
            strcat(nome_arq,".txt"); // Os brancos contem o espectro (contagens) de amostras não utilizadas para descontar seus efeitos das amostras reais
            arq = fopen(nome_arq,"r"); // poderia-se abrir o arquivo dentro do if
            if (!arq)
            {
               printf("\nFalha ao abrir o arquivo %s", nome_arq);
               printf("\nDeseja digitar um novo nome para o arquivo? (S/N)");
               fflush(stdin);
               scanf("%c",&rp[1]);
               while ((rp[1] != 'S') && (rp[1] != 's') && (rp[1] != 'N') && (rp[1] != 'n'))
               {
                 printf("\nOpcao invalida!! Digite novamente!!");
                 fflush(stdin);
                 scanf("\n%c",&rp[1]);
               }
               if  ((rp[1] == 'S') || (rp[1] == 's'))  goto La;
               else printf("\nTecle <ENTER> para encerrar o programa");
               goto AKI;
            }
            else tst[1] = '+';// Talvez, corrigir.
            printf("\nDigite o nome do arquivo dos FATORES DE RESPOSTA de linha K: "); 
            scanf("%s",&ftrk);
            strcat(ftrk,".txt");
            printf("\nDigite o nome do arquivo dos FATORES DE RESPOSTA de linha L: "); 
            scanf("%s",&ftrl);
            strcat(ftrl,".txt");
         } 
         i = 0;
         k = 0;
         bn_int = 4; // Para entrar no looping
         vmin1 = 0;
         vmax1 = 0;
         vmin2 = 0;
         vmax2 = 0;
         vmin3 = 0;
         vmax3 = 0;
         printf("\nEm quantos intervalos os brancos serao divididos? ");
         while (bn_int > 3)
         {
           fflush(stdin);
           scanf("%d",&bn_int);
           if (bn_int > 3) printf("\nO numero de intervalos nao pode exceder o valor 3!!Digite novamente: "); // Talvez fazer um switch case aqui
         }  
         printf("\nDigite o valor MINIMO valor para o Elemento analizado no 1 Intervalo: ");
         n1:      
         fflush(stdin);
         scanf("%d",&vmin1);
         if ((vmin1 == 0 ) && (vmin1 != 1 ) && (vmin1 != 2 ) && (vmin1 != 3 ) && (vmin1 != 4) && (vmin1 != 5 ) && (vmin1 != 6 ) && (vmin1 != 7 ) && (vmin1 != 8 ) && (vmin1 != 9 ))
         {
           printf("\nPor favor, digite um numero:");
           goto n1;
         }  
         printf("\nDigite o valor MAXIMO valor para o Elemento analizado no 1 Intervalo: ");
         while (vmax1 <= vmin1)
         {
            n2:
            fflush(stdin);
            scanf("%d",&vmax1);
            if ((vmax1 == 0 ) && (vmax1 != 1 ) && (vmax1 != 2 ) && (vmax1 != 3 ) && (vmax1 != 4) && (vmax1 != 5 ) && (vmax1 != 6 ) && (vmax1 != 7 ) && (vmax1 != 8 ) && (vmax1 != 9 ))
            {
               printf("\nPor favor, digite um numero:");
               goto n2;
            }
            if (vmax1 <= vmin1) printf("\nO valor MAXIMO deve ser maior que o MINIMO, digite novamente:");
         }  
         if (bn_int >= 2)
         {
            printf("\nDigite o valor MINIMO valor para o Elemento analizado no 2 Intervalo: ");
            while (vmin2 <= vmax1)
            { 
               n3:
               fflush(stdin);
               scanf("%d",&vmin2);
               if ((vmin2 == 0 ) && (vmin2 != 1 ) && (vmin2 != 2 ) && (vmin2 != 3 ) && (vmin2 != 4) && (vmin2 != 5 ) && (vmin2 != 6 ) && (vmin2 != 7 ) && (vmin2 != 8 ) && (vmin2 != 9 ))
               {
                  printf("\nPor favor, digite um numero:");
                  goto n3;
               }
               if (vmin2 <= vmax1) printf("\nO valor MINIMO 2 deve ser maior que o MAXIMO 1, digite novamente:");            
            }  
            printf("\nDigite o valor MAXIMO valor para o Elemento analizado no 2 Intervalo: ");
            while (vmax2 <= vmin2)
            {
               n4:
               fflush(stdin);
               scanf("%d",&vmax2);
               if ((vmax2 == 0 ) && (vmax2 != 1 ) && (vmax2 != 2 ) && (vmax2 != 3 ) && (vmax2 != 4) && (vmax2 != 5 ) && (vmax2 != 6 ) && (vmax2 != 7 ) && (vmax2 != 8 ) && (vmax2 != 9 ))
               {
                  printf("\nPor favor, digite um numero:");
                  goto n4;
               }
               if (vmax2 <= vmin2) printf("\nO valor MAXIMO deve ser maior que o MINIMO, digite novamente:");            
            }  
         }         
         if (bn_int == 3)
         {
            printf("\nDigite o valor MINIMO valor para o Elemento analizado no 3 Intervalo: ");
            while (vmin3 <= vmax2)
            {
               n5:
               fflush(stdin);   
               scanf("%d",&vmin3);
               if ((vmin3 == 0 ) && (vmin3 != 1 ) && (vmin3 != 2 ) && (vmin3 != 3 ) && (vmin3 != 4) && (vmin3 != 5 ) && (vmin3 != 6 ) && (vmin3 != 7 ) && (vmin3 != 8 ) && (vmin3 != 9 ))
               {
                  printf("\nPor favor, digite um numero:");
                  goto n5;
               }
               if (vmin3 <= vmax2) printf("\nO valor MINIMO 3 deve ser maior que o MAXIMO 2, digite novamente:");            
            }  
            printf("\nDigite o valor MAXIMO valor para o Elemento analizado no 3 Intervalo: ");
            while (vmax3 <= vmin3)
            {
               n6:
               fflush(stdin);
               scanf("%d",&vmax3);
               if ((vmax3 == 0 ) && (vmax3 != 1 ) && (vmax3 != 2 ) && (vmax3 != 3 ) && (vmax3 != 4) && (vmax3 != 5 ) && (vmax3 != 6 ) && (vmax3 != 7 ) && (vmax3 != 8 ) && (vmax3 != 9 ))
               {
                  printf("\nPor favor, digite um numero:");
                  goto n6;
               }
               if (vmax3 <= vmin3) printf("\nO valor MAXIMO deve ser maior que o MINIMO, digite novamente:");                           
            }   
         }
         /*O arquivo de brancos contem os arquivos de espectros de amostras totalmente brancas
         *Este looping serve apenas para armazenar os nomes dos espectros brancos na matriz caracter2[][]
         */
         for (k=0; k<=82;k++) imprime[k] = '0';
         while (!feof(arq)) 
         {
              fgets(caracter2[i], 256, arq);
              if (caracter2[i][strlen(caracter2[i])-1]=='\n') caracter2[i][strlen(caracter2[i])-1]='\0';//Eliminando o caractere \n (pula-linha) para a leitura correta do arquivo em recortaenergia
              i++;
         }// Fim da leitura dos nomes de arquivos contidos no arquivo de brancos
         cont = 0;
         cont_aux=0;
         cont11 = 0;
         cont13 = 0;
         while (cont < i)// 02/01/2012 - Começo do processamento dos dados de cada arquivo lido na matriz caracter2
         {  
           for(ba_int = 1; ba_int <= bn_int; ba_int++)
           { 
             x = 0; 
             while ( x < ((strlen(caracter2[cont])-18)) )// 05/01/2012 (Tamanho da matriz -19) paara descontar a informação de data e hora de geração do arquivo contida em seu nome e o caracter '\n'. Para o caso em que a lista de brancos contiver linhas em branco.
             {
               TamanhoString=strlen(caracter2[cont]);// Variável usada apenas para melhor debugar o programa
               TamanhoString=strlen(caracter2[cont])-18;
               nome[x] = caracter2[cont][x];
               nomevolume[cont][x] = nome[x];
               x++;
             }
             // Já eliminado o problema algumas linhas acima if (caracter2[cont][strlen(caracter2[cont])-1]=='\n') caracter2[cont][strlen(caracter2[cont])-1]='\0';//Eliminando o caractere \n (pula-linha) para a leitura correta do arquivo em recortaenergia
             cont_aux++;
             if (ba_int == 1)
             {
                recortacorrenteetempo(caracter2[cont]);
           ////////INSERE .TXT NO FINAL DO NOME DO ARQUIVO .SPE 
                caracter2[cont][(strlen(caracter2[cont])-3)] = 't';
                caracter2[cont][(strlen(caracter2[cont])-2)] = 'x';
                caracter2[cont][(strlen(caracter2[cont])-1)] = 't';
             }   
             if (ba_int == 1 )// Abre (e fecha) o arquivo que contem a primeira parte do espectro
             {
                  nomeint[0] = '[';
                  nomeint[1] = '1';
                  nomeint[2] = ']';              
                  k=0;  
                  vminatual = vmin1;
                  vmaxatual = vmax1; 
                  for (x=3; x<= 80 ; x++)
                  {
                     nomeint[x] = caracter2[cont][k];
                     k++;
                  }    
                  fteste = fopen(nomeint,"r");
                  if (!fteste) goto FIM2;
                  else fclose(fteste);
             }  
             if (ba_int == 2 )// Mesma coisa que o anterior, mas com a parte 2
             {
                  nomeint[0] = '[';
                  nomeint[1] = '2';
                  nomeint[2] = ']';                 
                  vminatual = vmin2;
                  vmaxatual = vmax2; 
                  k=0;   
                  for (x=3; x<= 80 ; x++)
                  {
                      nomeint[x] = caracter2[cont][k];
                      k++;
                  }    
                  fteste = fopen(nomeint,"r");
                  if (!fteste) goto FIM2;
                  else
                  {
                     fclose(fteste);
                  }  
             }  
             if (ba_int == 3 )// Mesma coisa que oanterior, mas com a parte 3
             {
                  nomeint[0] = '[';
                  nomeint[1] = '3';
                  nomeint[2] = ']';                 
                  vminatual = vmin3;
                  vmaxatual = vmax3; 
                  k=0;   
                  for (x=3; x<= 80 ; x++)
                  {
                     nomeint[x] = caracter2[cont][k];
                     k++;
                  }    
                  fteste = fopen(nomeint,"r");
                  if (!fteste) goto FIM2;
                  else
                  {
                     fclose(fteste);
                  }  
             }  
             recortaenergia(nomeint);//ler recorta energia (27/09/2011 - terça: Parei aqui)
             aux = 0.0;
             aux = tempo*corrente;//aux = I*dt 
             k = 0;
             arq5 = fopen("testeb.txt","w+");////ARQUIVO DE SAIDA DOS RESULTADOS
             ImprimeZsEmLinha(imprime, k, vmin1, vmax1, vmin2, vmax2, vmin3, vmax3, bn_int);// Seleciona em cada amostra de branco os elementos a serem impressos
             x=0;
             for (k=0; k < 31; k++)//Início do código que trata as diferentes partes de espectro (25/10/2011)
             {
                if ((contagem[elemento[k]] > 0) && ((elemento[k] >=vminatual) && (elemento[k] <= vmaxatual)))//19-12-2011: trecho em que quase todas as contas do branco são feitas
                { 
                   fator_de_resposta(elemento[k], k); x++;
                   n = 0;
                   while ((elemento[k] != ft_resposta[n][1]) && (n<= 82)) n++;//19-12-2011 Encontra o fator de resposta do elemento[k]
                  if (elemento[k] == 11){
                     cont11 = contagem[ elemento[k] ];
                     fator11 = ft_resposta[n][2]; // 06/03/2012 Variável criada para armazenar o fator de resposta correto
                  }//04/10/2011
                  if (elemento[k] == 13){
                     cont13 = contagem[ elemento[k] ];//04/10/2011
                     fator13 = ft_resposta[n][2]; // 06/03/2012 Análogo ao caso do sódio
                  }
                  if (elemento[k] == 30) cont11 = (cont11 - ( contagem[ elemento[k] ]*zinco));
                  if (elemento[k] == 35) cont13 = (cont13 - ( contagem[ elemento[k] ]*bromo));//04/10/2011
                  if ((elemento[k] != 11) && (elemento[k] != 13)) matriz_media[cont][elemento[k]] = ((contagem[elemento[k]]*area)/(aux * (ft_resposta[n][2])));// Trecho em que a fórmula é utilizada
                  if (ft_resposta[n][2] != 0)
                  {
                            
                            desvio_padraoi[cont][elemento[k]] =  (contagem[elemento[k]]*area)/(ft_resposta[n][2]*aux);//04/10/2011
                            aux4 = (incerteza[ elemento[k] ]);//20/10/2011
                            aux4 = (aux4/contagem[elemento[k]]);
                            aux4 = (aux4 * aux4);
                            aux5 = ((ft_resposta[n][3] / ft_resposta[n][2])*(ft_resposta[n][3]/ft_resposta[n][2]));
                            matriz_erro_branco[cont][elemento[k]] = (desvio_padraoi[cont][elemento[k]]*sqrt(aux4 + aux5));
                            //matriz_erro_branco[cont][elemento[k]] = (matriz_erro_branco[cont][elemento[k]]*matriz_erro_branco[cont][elemento[k]]);
                  }                                             
               }
               if (contagem[ elemento[k] ] < 0)// ((contagem[k] == 0) && ((elemento[k] >=vminatual) && (elemento[k] <= vmaxatual)))
               {
                 matriz_media[cont][elemento[k]] = 0.0;
                 matriz_erro_branco[cont][elemento[k]] = 0.0;
               }  
             }
           
             cont_aux++;
             FIM2:
             fflush(stdin);     
           }
          if (cont11 > 0) matriz_media[cont][11] = ((cont11*area)/(aux*fator11));// 06/06/2012 uso das variáveis fator 11 e 13 supracitadas.
          if (cont13 > 0) matriz_media[cont][13] = ((cont13*area)/(aux*fator13));
          /*printf("\n -> %d", contagem[k]);
                getchar();*/
          cont11 = 0;
          cont13 = 0;
          cont++;
          if ( (caracter2[cont][0]=='\0') || (caracter2[cont][0]=='\n') ){
               i--;// 24-01-2012 No caso de haver uma linha em branco, além de sair do looping, não contabiliza essa linha
               break;
          }// 05/01/2011 Para o caso em que a lista de brancos contiver linhas em branco.
         }
         fprintf(arq5,"Alvo/");//Início do código para imprimir primeira linha
         for (x=11; x<=90; x++)
         {
            if (imprime[x] == '*') fprintf(arq5,"%d/ERRO/",x);
         }
          fprintf(arq5,"\n");//Fim do código para imprimir primeira linha
         for (x=11; x < 99; x++) 
         {    
              for (cont = 0; cont < i; cont++) 
              {
                 matriz_erro_branco[i+1][x] = (matriz_erro_branco[i+1][x] + (matriz_erro_branco[cont][x]*matriz_erro_branco[cont][x]));
              }
              matriz_erro_branco[i+1][x] = sqrt(matriz_erro_branco[i+1][x]/i);
         }     
         
         for (x=11; x < 99; x++) //19-12-2011 Looping para calcular a média de cada elemento nos brancos e o desvio-padrão
         {
            cont = 0;
            y = 0;
            matriz_media[i+1][x] = 0;
            while (cont < i)
            {
                  y = y + 1;
                  matriz_media[i+1][x] = (matriz_media[i+1][x] + matriz_media[cont][x]);
                  cont++;
            }
            matriz_media[i+1][x]=(matriz_media[i+1][x])/i;//Na última linha de matriz_media[][] é calculada a média.
///Desvio padrão
            desvio_padraopc[x] = 0;
            for (cont = 0; cont < i ; cont++) 
            {
                desvio_padraopc[x] = (desvio_padraopc[x] + ((matriz_media[cont][x] - matriz_media[i+1][x])*(matriz_media[cont][x] - matriz_media[i+1][x])));
            }   
            desvio_padraopc[x] = sqrt(desvio_padraopc[x]/(i-1));
            if (i== 2 ) desvio_padraopc[x] = (desvio_padraopc[x] * 1.84);//Correções do desvio padrão por teste-t de student?
            if (i== 3 ) desvio_padraopc[x] = (desvio_padraopc[x] * 1.32);
            if (i== 4 ) desvio_padraopc[x] = (desvio_padraopc[x] * 1.20);
            if (i== 5 ) desvio_padraopc[x] = (desvio_padraopc[x] * 1.14);
            if (i== 6 ) desvio_padraopc[x] = (desvio_padraopc[x] * 1.12);
            if (i== 7 ) desvio_padraopc[x] = (desvio_padraopc[x] * 1.11);
            if (i== 8 ) desvio_padraopc[x] = (desvio_padraopc[x] * 1.08);
            if (i== 9 ) desvio_padraopc[x] = (desvio_padraopc[x] * 1.09);
            if (i== 10 ) desvio_padraopc[x] = (desvio_padraopc[x] * 1.06);
            matriz_erro_branco[i+1][x] = sqrt((desvio_padraopc[x]*desvio_padraopc[x])+(matriz_erro_branco[i+1][x]*matriz_erro_branco[i+1][x]));
        }
        for (cont = 0; cont < i; cont++)//19-12-2011 Impressão dos resultados de cada branco
        {
             x = 0; 
             while (x < (strlen(nomevolume[cont])))//Impressão do nome do branco na linha cont em nomevolume[][]
             {
               fprintf(arq5,"%c",nomevolume[cont][x]);
               x++;
             }
             fprintf(arq5,"%/");
             for (x =11; x<= 99; x++)//Impressão das concentrações de cada elemento em cada branco. Considerar alterar (02/01/2012)
             {
                if ( imprime[x]== '*' ) fprintf(arq5,"%f/%f/",matriz_media[cont][x], matriz_erro_branco[cont][x]);
             }   
             fprintf(arq5,"\n");
        }//Fim da impressão dos resultados de cada branco
        fprintf(arq5,"MEDIA/");//19-12-2011 Impressão das médias de concentração dos elementos em todos os brancos
        for (x=11; x<99; x++) if (matriz_media[i+1][x] > 0) fprintf(arq5,"%f/%f/",matriz_media[i+1][x], matriz_erro_branco[i+1][x]);
            
        printf("\nComo sera a insercao do VOLUME?");
        printf("\n 1 - Digitar um unico valor     2 - Ler os dados a partir de um arquivo:  ");
        fflush(stdin);  
        scanf("%d",&VolAns);
        while ((VolAns != 1) && (VolAns != 2))
        {
              printf("\nOpcao invalida!! Digite novamente!!");
              fflush(stdin);
              scanf("\n%d",&VolAns);
         }
         printf("\nDigite o erro percentual (%) do volume (0 para nenhum):");
         scanf("%f",&errovol);
         errovol=errovol/100;
         if (VolAns == 1)
         {
           printf("\nDigite o valor para o volume: ");
           fflush(stdin);
           scanf("%f",&vol);
           for(x=0; x < 500; x++) guarda_volume[x] = vol;
         }
         else
         {
            printf("\nDigite o nome do arquivo que contem os VOLUMES :");
            scanf("%s",&volume);
            Nvol = recortavolume(volume);// Retorna a última posição em que podem ser encontrados volumes no vetor guarda_volume
         }   
         vmin1 = 0;
         vmax1 = 0;
         vmin2 = 0;
         vmax2 = 0;
         vmin3 = 0;
         vmax3 = 0;
         printf("\n\nDigite o nome do arquivo que contem os .SPE: "); 
         scanf("%s",&nome_arq_2);
         fflush(stdin);
         printf("\nDigite o nome do arquivo dos FATORES DE RESPOSTA de linha K: "); 
         scanf("%s",&ftrk);
         strcat(ftrk,".txt");
         printf("\nDigite o nome do arquivo dos FATORES DE RESPOSTA de linha L: "); 
         scanf("%s",&ftrl);
         strcat(ftrl,".txt");
         n_int = 4;
         printf("\nEm quantos intervalos voce ira dividir a analise? ");
         while (n_int > 3)
         {
           fflush(stdin);
           scanf("%d",&n_int);
           if (n_int > 3) printf("\nO numero de intervalos nao pode exceder o valor 3!!Digite novamente: ");
         }  
         printf("\nDigite o valor MINIMO valor para o Elemento analizado no 1 Intervalo: ");
         n7:
         fflush(stdin);
         scanf("%d",&vmin1);
         if ((vmin1 == 0 ) && (vmin1 != 1 ) && (vmin1 != 2 ) && (vmin1 != 3 ) && (vmin1 != 4) && (vmin1 != 5 ) && (vmin1 != 6 ) && (vmin1 != 7 ) && (vmin1 != 8 ) && (vmin1 != 9 ))
         {
           printf("\nPor favor, digite um numero:");
           goto n7;
         }  
         printf("\nDigite o valor MAXIMO valor para o Elemento analizado no 1 Intervalo: ");
         while (vmax1 <= vmin1)
         {
            n8:
            fflush(stdin);
            scanf("%d",&vmax1);
            if ((vmax1 == 0 ) && (vmax1 != 1 ) && (vmax1 != 2 ) && (vmax1 != 3 ) && (vmax1 != 4) && (vmax1 != 5 ) && (vmax1 != 6 ) && (vmax1 != 7 ) && (vmax1 != 8 ) && (vmax1 != 9 ))
            {
               printf("\nPor favor, digite um numero:");
               goto n8;
            }
            if (vmax1 <= vmin1) printf("\nO valor MAXIMO deve ser maior que o MINIMO, digite novamente:");
         }  
         if (n_int >= 2)
         {
            printf("\nDigite o valor MINIMO valor para o Elemento analizado no 2 Intervalo: ");
            while (vmin2 <= vmax1)
            { 
               n9:
               fflush(stdin);
               scanf("%d",&vmin2);
               if ((vmin2 == 0 ) && (vmin2 != 1 ) && (vmin2 != 2 ) && (vmin2 != 3 ) && (vmin2 != 4) && (vmin2 != 5 ) && (vmin2 != 6 ) && (vmin2 != 7 ) && (vmin2 != 8 ) && (vmin2 != 9 ))
               {
                  printf("\nPor favor, digite um numero:");
                  goto n9;
               }
               if (vmin2 <= vmax1) printf("\nO valor MINIMO 2 deve ser maior que o MAXIMO 1, digite novamente:");            
            }  
            printf("\nDigite o valor MAXIMO para o Elemento analizado no 2 Intervalo: ");
            while (vmax2 <= vmin2)
            {
               n10:
               fflush(stdin);
               scanf("%d",&vmax2);
               if ((vmax2 == 0 ) && (vmax2 != 1 ) && (vmax2 != 2 ) && (vmax2 != 3 ) && (vmax2 != 4) && (vmax2 != 5 ) && (vmax2 != 6 ) && (vmax2 != 7 ) && (vmax2 != 8 ) && (vmax2 != 9 ))
               {
                  printf("\nPor favor, digite um numero:");
                  goto n10;
               }
               if (vmax2 <= vmin2) printf("\nO valor MAXIMO deve ser maior que o MINIMO, digite novamente:");            
            }  
         }         
         if (n_int == 3)
         {
            printf("\nDigite o valor MINIMO para o Elemento analizado no 3 Intervalo: ");
            while (vmin3 <= vmax2)
            {
               n11:
               fflush(stdin);
               scanf("%d",&vmin3);
                if ((vmin3 == 0 ) && (vmin3 != 1 ) && (vmin3 != 2 ) && (vmin3 != 3 ) && (vmin3 != 4) && (vmin3 != 5 ) && (vmin3 != 6 ) && (vmin3 != 7 ) && (vmin3 != 8 ) && (vmin3 != 9 ))
               {
                  printf("\nPor favor, digite um numero:");
                  goto n11;
               }
               if (vmin3 <= vmax2) printf("\nO valor MINIMO 3 deve ser maior que o MAXIMO 2, digite novamente:");            
            }  
            printf("\nDigite o valor MAXIMO valor para o Elemento analizado no 3 Intervalo: ");
            while (vmax3 <= vmin3)
            {
               n12:
               fflush(stdin); 
               scanf("%d",&vmax3);
               if ((vmax3 == 0 ) && (vmax3 != 1 ) && (vmax3 != 2 ) && (vmax3 != 3 ) && (vmax3 != 4) && (vmax3 != 5 ) && (vmax3 != 6 ) && (vmax3 != 7 ) && (vmax3 != 8 ) && (vmax3 != 9 ))
               {
                  printf("\nPor favor, digite um numero:");
                  goto n12;
               }
               if (vmax3 <= vmin3) printf("\nO valor MAXIMO deve ser maior que o MINIMO, digite novamente:");                           
            }   
         }         
         printf("\nDigite um nome para o arquivo de saida: ");
         if (vmin1 < 11) vmin1 = 11;
         scanf("%s",&volume);
         strcat(volumeb,volume);
         strcat(volume,".txt");
         strcat(volumeb,"_branco.txt");
/////////////RECORTA OS NOMES DOS .SPE///////////////////////////////////////////////
         strcat(nome_arq_2,".txt");
         tst[1] = '*';
         while (tst[1] == '*')
         {
            arq = fopen(nome_arq_2,"r");// 22/12/2011 ponteiro para o nome de arquivo que contem as amostras SPE (espectros)
            if (!arq)
            {
               printf("\nFalha ao abrir o arquivo %s", nome_arq_2);
               printf("\nDeseja digitar um novo nome para o arquivo? (S/N)");
               fflush(stdin);
               scanf("%c",&rp[1]);
               while ((rp[1] != 'S') && (rp[1] != 's') && (rp[1] != 'N') && (rp[1] != 'n'))
               {
                 printf("\nOpcao invalida!! Digite novamente!!");
                 fflush(stdin);
                 scanf("\n%c",&rp[1]);
               }
               if ((rp[1] == 'S') || (rp[1]=='s'))
               {
                 printf("\nNovo nome:  ");
                 scanf("%s",&nome_arq_2);
                 strcat(nome_arq_2,".txt");
               }  
               else
               {
                  printf("A FALTA DO NOME DO ARQUIVO PARA OS .SPE, NAO PERMITE PROSSEGUIR...");
                  fflush(stdin);
                  getchar();
                  goto AKI;
               }      
            }
            else tst[1] = '+';
         }  
         j = 0;
         k = 0;
         while (!feof(arq))
         {
              fscanf(arq,"%c",&ajuda[0]);
              caracter[j][k] = ajuda[0];
              k++;
              if (ajuda[0] == '.') 
              {
                  x = 0;
                  fscanf(arq,"%c",&ajuda[0]);caracter[j][k] = ajuda[0];k++;
                  fscanf(arq,"%c",&ajuda[0]);caracter[j][k] = ajuda[0];k++;
                  fscanf(arq,"%c",&ajuda[0]);caracter[j][k] = ajuda[0];k++;
                  fscanf(arq,"%c",&ajuda[0]);
                  j++;
                  k = 0;
              }
         }
         //Inserir aqui função para verificar existência dos [n]amostra.txt 28-03-2012
         ChecaParametrosIniciais(caracter,n_int);
         arq3 = fopen("teste.txt","w+");////ARQUIVO DE SAIDA DOS RESULTADOS
         cont = 0;
         for (k=0; k<=82;k++) imprime[k] = '0';
         cont_aux = 0;
         while (cont <= j)// j é o índice de caracter, onde são armazenados os nomes dos SPE das amostras. Início do código que processa as diferentes partes de espectros das amostras (25-10-2011) 
         {
            for (a_int =1; a_int <= n_int; a_int++)
            {
               x = 0;
               while (x <= 80)
               {
                  caracter3[cont_aux][x] = ' ';
                  caracter3[cont_aux][x] = caracter[cont][x];
                  x++;
               }      
               caracter3[cont_aux][(strlen(caracter[cont])-3)] = 't';
               caracter3[cont_aux][(strlen(caracter[cont])-2)] = 'x';
               caracter3[cont_aux][(strlen(caracter[cont])-1)] = 't';
               if (a_int == 1 )
               {
                  nomeint[0] = '[';
                  nomeint[1] = '1';
                  nomeint[2] = ']';              
                  k=0;   
                  for (x=3; x<= 80 ; x++)
                  {
                     nomeint[x] = caracter3[cont_aux][k];
                     k++;
                  }    
                  fteste = fopen(nomeint,"r");
                  if (!fteste) goto FIM;
                  else fclose(fteste);
               }  
               if (a_int == 2 )
               {
                  nomeint[0] = '[';
                  nomeint[1] = '2';
                  nomeint[2] = ']';                 
                  k=0;   
                  for (x=3; x<= 80 ; x++)
                  {
                      nomeint[x] = caracter3[cont_aux][k];
                      k++;
                  }    
                  fteste = fopen(nomeint,"r");
                  if (!fteste) goto FIM;
                  else
                  {
                     fclose(fteste);
                  }  
               }  
               if (a_int == 3 )
               {
                  nomeint[0] = '[';
                  nomeint[1] = '3';
                  nomeint[2] = ']';                 
                  k=0;   
                  for (x=3; x<= 80 ; x++)
                  {
                     nomeint[x] = caracter3[cont_aux][k];
                     k++;
                  }    
                  fteste = fopen(nomeint,"r");
                  if (!fteste) goto FIM;
                  else
                  {
                     fclose(fteste);
                  }  
               }  
               for (x=0 ; x<= 80; x++) caracter3[cont_aux][x] = nomeint[x];
               recortaenergia(caracter3[cont_aux]);//Recorta a energia dos elementos contidos em cada arquivo
               for (k=0; k<=30; k++)//(01-11-2011) - USO DOS Zmins E Zmaxs DE CADA PARTE DO ESPECTRO DENTRO DESTE FOR. EM TODOS AS PARTES (ARQUIVOS), TODOS OS ELEMENTOS SÃO LIDOS, MAS APENAS OS QUE ESTÃO DENTRO DE UMA REGIÃO EM CADA PARTE QUE DEVEM SER ANALISADOS SÃO MARCADOS COM UM '*'. ENTÃO AS DEMAIS PARTES DO CÓDIGO PROCESSAM AS INFORMAÇÕES.
               {
                   if (((elemento[k] >= vmin1) && (elemento[k] <= vmax1)) && (elemento[k] != 0)) imprime[elemento[k]] = '*';
                   if ((n_int == 2) && (((elemento[k] >= vmin2) && (elemento[k] <= vmax2)) || ((elemento[k] >= vmin1) && (elemento[k] <= vmax1))&& (elemento[k] != 0))) 
                   {
                            imprime[elemento[k]] = '*';
                   }  
                   if ((n_int == 3) && (((elemento[k] >= vmin3) && (elemento[k] <= vmax3)) || ((elemento[k] >= vmin2) && (elemento[k] <= vmax2)) || ((elemento[k] >= vmin1) && (elemento[k] <= vmax1)) && (elemento[k] != 0)))
                   {
                            imprime[elemento[k]] = '*';
                   }            
               }
               cont_aux++; 
               FIM:
               fflush(stdin);    
           }
           cont++;
          }
          fprintf(arq3,"Alvo/");
          for (x=11; x<=90; x++)
          {
             if (imprime[x] == '*') fprintf(arq3,"%d/ERRO/",x);
          }
          fprintf(arq3,"\n");
          fclose(arq);
          cont = -1;
          cont_aux = -1;
          while (cont <= j)
          {  
             cont++;
             for (a_int = 1; a_int <= n_int; a_int++) 
             {
                cont_aux++;
                if (a_int == 1)
                {
                   vminatual = vmin1;
                   vmaxatual = vmax1;
                }          
                if (a_int == 2)
                {
                   vminatual = vmin2;
                   vmaxatual = vmax2;
                }          
                if (a_int == 3)
                {
                   vminatual = vmin3;
                   vmaxatual = vmax3;
                }           
                t = 0;
                for (x=0; x <= 10; x++) nome[x] = ' ';
                x = 0; 
                while ((x < ((strlen(caracter[cont])-18))) && (caracter[cont][x] != '-'))
                {
                   nome[x] = caracter[cont][x];
                   x++;
                }
                for (z=x; z<=(x+5); z++) nome[z] = ' ';
                t = -1;
                ajuda2[0] = '*';
                while ((t < 199) && (ajuda2[0] == '*' ))
                {
                   t++;
                   z = 0;
                   while (z <= ((strlen(nomevolume[t]))))
                   {
                       if (nome[z] == nomevolume[t][z]) z++;
                       else z = (strlen(nomevolume[t]))+1;
                       if (z == (strlen(nomevolume[t]))) ajuda2[0] = '+';
                   }  
                }
                tempo = 0;
                corrente = 0;
                if (caracter3[cont_aux][0] == '[') 
                {
                    recortacorrenteetempo(caracter[cont]);// 22-12-2011 Colocar função para corrigir índice de volumes depois desta linha. Comparar caracter com nomevolume.
                    if (VolAns == 2) Ivol = IndiceVolumeAtual( Nvol, caracter[cont]);// 24/12/2011 - Seleciona o índice para a matriz de volumes para cada amostra.
                     else Ivol=0; // 20/01/2012 Correção para o caso em que o usuário inserir manualmente o valor do volume
                    for(k=0; k==30;k++) elemento[k] = 0;//13/02/2012 Aparentemente, este looping não funciona
                    recortaenergia(caracter3[cont_aux]);//GERA A TABELA COM AS DENSIDADES E ERROS//
                    if (a_int == 1)
                    {
                          fprintf(arq3,"%s/",nome);
                    }
                    aux = 0.0;
                    aux = tempo*corrente; 
                    p = vminatual;
                    for (k=0; k <= 30; k++)
                    {
                       y = 0;
                       if ((a_int == 1) && (elemento[k] > vmaxatual) && (p < vmax1))
                       {
                          for (p = elemento[k-1]+1; p <= vmax1; p++)
                          {
                               fprintf(fpteste2,"Linha 841 Amostra/Parte:%s Elemento %d Concentracao: 0\n",caracter3[cont_aux],p);
                               if (imprime[p] == '*') fprintf(arq3,"0/0/");        
                          }
                          k = 31;
                       } 
                       if ((a_int == 2) && (elemento[k] > vmaxatual) && (p < vmax2))
                       {
                          for (p = elemento[k-1]+1; p <= vmax2; p++)
                          {
                             fprintf(fpteste2,"Linha 850 Amostra/Parte:%s Elemento %d Concentracao: 0\n",caracter3[cont_aux],p);
                             if (imprime[p] == '*') fprintf(arq3,"0/0/");        
                          }
                          k = 31;
                       }
                       if ((elemento[k] >= vminatual) && (elemento[k] <= vmaxatual))
                       {
                           while  ((p < elemento[k]))
                           {
                               if ((imprime[p] == '*') && (p != elemento[k]))
                               {
                                   fprintf(fpteste2,"Linha 861 Amostra/Parte:%s Elemento %d Concentracao: 0\n",caracter3[cont_aux],p);
                                   fprintf(arq3,"0/0/");
                               }              
                               p++;
                           }
                           p = elemento[k]+1; // 30/07/2013 --> Considerar debugar essa linha com o carregado2 para uma amostra corretamente mostrada e outra incorreta 
                           if (elemento[k] != 0)
                           {   
                              fator_de_resposta(elemento[k], k);
                              if (ind == -2) fprintf (arq3,"nao existe este elemento");
                      // }
                               while ((elemento[k] != ft_resposta[y][1]) && (y <= 149))
                              {
                                 if (elemento[k] != ft_resposta[y][1]) y++;
                                 if (y >= 149)
                                {
                                  fprintf(arq3,"SEM F.R./");
                                  y++;
                                }
                             }
                       conv = 0.0;
                       erro = 0.0;
                       n = 0;
                       while ((elemento[k] != ft_resposta[n][1]) && (n<= 82)) n++;
                       conv = (area/(ft_resposta[n][2]));
                       cont2 = 0.0;
                       czinco = 0;
                       cbromo = 0;
                       if (elemento[k] == 11)
                       {
                         cont11 = contagem[ elemento[k] ];//20/10/2011
                         incerteza11 = incerteza[ elemento[k] ];//19/06/2012 Correção na incerteza do Sódio
                       if (cont11 < 0) 
                       {
                         pl = 0.0;
                         contagem[ elemento[k] ] = 0;//20/10/2011
                         goto final;
                      
                       }                   
                         for (contador = 0; contador < n_int; contador++)
                         {  
                            recortaenergia(caracter3[cont_aux+contador]);
                            for (ma = 0; ma <= 30; ma++)
                            {
                                if (elemento[ma] == 30){
                                   czinco = contagem[elemento [ma] ];
                                   incertzinco = incerteza[ elemento[ma] ];//19/06/2012
                                }
                            }                  
                         } 
                          n = 0;
                          while ((elemento[k] != ft_resposta[n][1]) && (n<= 82)) n++;
                          cont11 = (cont11 - czinco*zinco);
                          cont2 = (cont11/aux);
                          aux4 = sqrt( incerteza11*incerteza11 + (zinco*incertzinco)*(zinco*incertzinco) );//19/06/2012 - Proposta de correção Américo
                          aux4 = (aux4/cont11);//19/06/2012
                          aux4 = (aux4 * aux4);
                          aux5 = ((ft_resposta[n][3] / ft_resposta[n][2])*(ft_resposta[n][3]/ft_resposta[n][2]));
                          erro = ((((cont11*area)/(ft_resposta[n][2]*aux))*(sqrt(aux5 + aux4))));//20/10/2011 19/06/2012
                          erro = (sqrt((erro*erro) + (matriz_erro_branco[i+1][elemento[k]]*matriz_erro_branco[i+1][elemento[k]]))/guarda_volume[Ivol]);
                          pl = 0.0;
                          cont2 = cont2*conv;
                          pl = (cont2 - matriz_media[i+1][elemento[k]]);
                          aux4 = (erro/pl)*guarda_volume[Ivol];//07/08/2012 Correção no erro percentual --> 04/07/2012 --> Conjunto do código para intrudizir erro no volume
                          aux4 = sqrt( aux4*aux4 + errovol*errovol);
                          pl = pl/guarda_volume[Ivol]; //24/12/2011 --> alteração de índice pela função
                          erro = aux4*pl;// 04/07/2012 --> Fim do código
                          recortaenergia(caracter3[cont_aux]);
                       }
                       if (elemento[k] == 13)
                       {
                         cont13 = contagem[ elemento[k] ];//20/10/2011
                         incerteza13 = incerteza[ elemento[k] ];
                         for (contador = 0; contador < n_int; contador++)
                         {  
                            recortaenergia(caracter3[cont_aux+contador]);
                            for (ma = 0; ma <= 30; ma++)
                            {
                                if (elemento[ma] == 35) {
                                   cbromo = contagem[ elemento[ma] ];
                                   incertbromo = incerteza[ elemento[ma] ];//19/06/2012
                                }
                            }                  
                         } 
                         n = 0;
                         recortaenergia(caracter3[cont_aux]);// 24/02/2012 --> Correção necessária por causa da indexação. Afinal, elemento[k] no arquivo caracter3[cont_aux+contador] pode ser diferente 13. E queremos elemento[k]=13 para caracter3[cont_aux].
                         while ((elemento[k] != ft_resposta[n][1]) && (n<= 82)) n++;
                         cont13 = (cont13 - cbromo*bromo);
                         cont2 = (cont13/aux); 
                         aux4 = sqrt( incerteza13*incerteza13 + (bromo*incertbromo)*(bromo*incertbromo) );//19/06/2012 - Proposta de correção de incerteza Américo
                         aux4 = (aux4/cont13);//19/06/2012
                         aux4 = (aux4 * aux4);
                         aux5 = ((ft_resposta[n][3] / ft_resposta[n][2])*(ft_resposta[n][3]/ft_resposta[n][2]));
                         erro = ((((cont13*area)/(ft_resposta[n][2]*aux))*(sqrt(aux5 + aux4))));
                         erro = (sqrt((erro*erro) + (matriz_erro_branco[i+1][elemento[k]]*matriz_erro_branco[i+1][elemento[k]]))/guarda_volume[Ivol]);
                         pl = 0.0;;
                         pl = 0.0;
                         cont2 = cont2*conv;

                         pl = (cont2 - matriz_media[i+1][elemento[k]]);
                         aux4 = (erro/pl)*guarda_volume[Ivol];//07/08/2012 Correção no erro percentual--> 04/07/2012 --> Conjunto do código para intrudizir erro no volume
                         aux4 = sqrt( aux4*aux4 + errovol*errovol);
                         pl = pl/guarda_volume[Ivol]; // 24/12/2011 --> alteração de índice pela função IndiceVolumeAutal()
                         erro = aux4*pl;// 04/07/2012 --> Fim do código
                       }
                       if ((elemento[k] != 11) && (elemento[k] != 13))//20-12-2011 Cálculo de concentrações das amostrar para os elementos diferentes de Na e Al
                       {
                         n = 0;
                         while ((elemento[k] != ft_resposta[n][1]) && (n<= 82)) n++;
                         cont2 = (contagem[ elemento[k] ]/aux);//20/10/2011
                         aux4 = (incerteza[ elemento[k] ]);//20/10/2011
                         aux4 = (aux4/contagem[ elemento[k] ]);//20/10/2011
                         aux4 = (aux4 * aux4);
                         aux5 = ((ft_resposta[n][3] / ft_resposta[n][2])*(ft_resposta[n][3]/ft_resposta[n][2]));
                         erro = ( (((contagem[ elemento[k] ]*area)/(ft_resposta[n][2]*aux))*(sqrt(aux5 + aux4))) );// 07/08/2012 (N*A/(R*aux))*raiz( (delR/R)²+(delN/N)² ), ou m*(erro/m/(R,N)), erro absoluto na massa; aux=I*dt
                         erro =  ((sqrt((erro*erro) + (matriz_erro_branco[i+1][elemento[k]]*matriz_erro_branco[i+1][elemento[k]])))/guarda_volume[Ivol]);// 07/08/2012 erro absoluto na concentração, levando-se em consideração os brancos.
                         pl = 0.0;
                         cont2 = cont2*conv;// 07/08/2012 N*(A/R)=NA/R=m
                         pl = (cont2 - matriz_media[i+1][elemento[k]]);// massa menos a massa nos brancos
                         aux4 = (erro/pl)*guarda_volume[Ivol];//07/08/2012 Correção no erro percentual --> 04/07/2012 --> Conjunto do código para intrudizir erro no volume
                         aux4 = sqrt( aux4*aux4 + errovol*errovol);
                         pl = pl/guarda_volume[Ivol];//24/12/2011 --> alteração de índice feito pela função IndiceVolumeAtual()  
                         erro = aux4*pl;// 04/07/2012 --> Fim do código

                       }  
                       final:
                       if ((y < 149)&&(elemento[k]!=0)&&(contagem[ elemento[k]]>=0))//20/10/2011 
                       {
                         fprintf(fpteste,"%s: Elemento %d>%f\n",caracter[cont],elemento[k],pl); //Para fins de debug 26-07-2013
                         if (pl > 0)  fprintf(arq3,"%f/%f/", pl ,erro);
                         if (pl <= 0)  fprintf(arq3,"0/0/");
                       }
                     
                  }
                } 
               }  
             }
           } 

          fprintf(arq3,"\n"); 
         }
         rewind(arq3);
         arq4 = fopen(volume,"w+"); 
         rewind(arq5);
         arq6 = fopen(volumeb,"w+"); 
         printf("\nQual estilo de planilha voce usara para abrir o arquivo?");
         printf("\n1 - Brasil    ou  2 - USA: ");
         fflush(stdin);
         scanf("%c",&rp[1]);
         while ((rp[1] != '1') && (rp[1] != '2'))
         {
              printf("\nOpcao invalida!! Digite novamente!!");
              fflush(stdin);
              scanf("\n%c",&rp[1]);
         }
         
         if (rp[1] == '1')
         {
           while (!feof(arq3))
           {
              fscanf(arq3,"%c",&ajuda[0]);
              if (ajuda[0] == '.') fprintf(arq4, ",");
              else fprintf(arq4,"%c", ajuda[0]);
           }
           while (!feof(arq5))
           {
              fscanf(arq5,"%c",&ajuda[0]);
              if (ajuda[0] == '.') fprintf(arq6, ",");
              else fprintf(arq6,"%c", ajuda[0]);
           }
         }
         else
         {
           while (!feof(arq3))
           {
              fscanf(arq3,"%c",&ajuda[0]);
              fprintf(arq4,"%c", ajuda[0]);
           }
           while (!feof(arq5))
           {
              fscanf(arq5,"%c",&ajuda[0]);
              fprintf(arq6,"%c", ajuda[0]);
           }
         }  
         fclose(arq3);
         fclose(arq5);
         remove("teste.txt");
         remove("testeb.txt");
         fclose(arq4);
         fclose(arq6);
         fclose(fpteste);
         fclose(fpteste2);
         printf("PROCESSO CONCLUIDO...");
         AKI: fflush(stdin);
         getchar();
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
int recortavolume(char nome_arq[80])//FAZ O RECORTE DO VOLUME DE UM .TXT
{
   FILE  *arq;
   char caracter[10], linha[LMAX], k[0], rp[1], tst[1], nome[80];
   int i, cont, x;
   float aux;
   for (x=0; x<=80; x++) nome[x] = nome_arq[x];
   strcat(nome,".txt");
   tst[1] = '*';
   while (tst[1] == '*')
   {
            arq = fopen(nome,"r");
            if (!arq)
            {
               printf("\nFalha ao abrir o arquivo %s", nome);
               fflush(stdin);
               printf("\nDeseja digitar um novo nome para o arquivo? (S/N)");
               scanf("%c",&rp[1]);
               if ((rp[1] == 'S') || (rp[1]=='s'))
               {
                 printf("\nNovo nome:  ");
                 scanf("%s",&nome);
                 strcat(nome,".txt");
               }  
               else
               {
                     printf("A FALTA DO ARQUIVO DE  VOLUME, NAO PERMITE PROSSEGUIR CORRETAMENTE...");
                     getchar();
                     goto AKI;
               }
            }
            else tst[1] = '+';
   }  
   for(x=0; x < 500; x++) guarda_volume[x] = 0.0;
   x = 0;
   fgets(linha,LMAX,arq);
   while (!feof(arq))
   {
     k[0] = '*';
     i = 0;
     while (k[0] != '\\')
     {
       fscanf(arq,"%c",&k[0]);
       if (k[0] != '\\')
       {
         nomevolume[x][i] = k[0];
         i++;
       }
     }
     cont++; 
     fgets(linha,LMAX,arq);
     i=1;
     aux = 1; 
     while ((isdigit(linha[i])) != 0)
     {
            aux = aux*10;
            i++;
     }
     i = 0;
     while ((isdigit(linha[i])) != 0)
     {
         k[0] = linha[i];
         guarda_volume[x] = (guarda_volume[x] + (atof(k)*aux)); 
         if (linha[i+1] == ',')
         {
                     i++;
                     aux=1;
         }
         aux = aux/10 ;
         i++;
     } 
     x++;
   }
   fclose(arq);
   AKI: fflush(stdin);
   return(x);
}
  
//////////////////////////////////////////////////////////////////////////////////////

recortacorrenteetempo(char nome_arq[80])//FAZ O RECORTE DA CORRENTE E DO TEMPO
{                                       // DE UM .SPE
      FILE *arqui;
      int i,j,k; 
      char caracte[1], ajuda[1], linha[100], tst[1], rp[1], nome[80];
      for (i=0; i<=80; i++) nome[i] = nome_arq[i];//Linha para copiar nome_arq[] para nome[]
      corrente = 0;
      tempo = 0;
      tst[1] = '*';
      while (tst[1] == '*')
      {
            arqui = fopen(nome,"r");
            if (!arqui)
            {
               printf("\nFalha ao abrir o arquivo %s", nome);
               fflush(stdin);
               printf("\nDeseja digitar um novo nome para o arquivo? (S/N)");
               scanf("%c",&rp[1]);
               if ((rp[1] == 'S') || (rp[1]=='s'))
               {
                 printf("\nNovo nome:  ");
                 scanf("%s",&nome);
                 strcat(nome,".txt");
               }  
               else
               {
                     printf("A FALTA DESTE ARQUIVO PODE OCASIONAR ERROS NO PROCESSO...");
                     getchar();
                     goto AKI;
               }
            }
            else tst[1] = '+';
      }  
          caracte[1] = ' ';
        ajuda[1] = ' ';
        i = 0;
        while (i <= 24) //PULA AS 14 VIRGULAS DO CABECARIO
        {
          fgets(linha,LMAX,arqui);
          i++;
        }
        i = 1;
        while (i<=29)
        {
          fscanf(arqui,"%c",&caracte[1]);
          i++;
        } 
        fscanf(arqui,"%c",&caracte);corrente = atoi(caracte)*1000;
        fscanf(arqui,"%c",&caracte);corrente = corrente + atoi(caracte)*100;
        fscanf(arqui,"%c",&caracte);corrente = corrente + atoi(caracte)*10;
        fscanf(arqui,"%c",&caracte);corrente = corrente + atoi(caracte);
        i = 1;
        while (caracte[1] != 'L') fscanf(arqui,"%c",&caracte[1]);
        while (i<=6)
        {
          fscanf(arqui,"%c",&caracte[1]);
          i++;
        }
        if (caracte[1] == ' ')  fscanf(arqui,"%c",&caracte);
        else fscanf(arqui,"%c",&caracte);tempo = atoi(caracte)*1000;
        fscanf(arqui,"%c",&caracte);tempo = tempo + atoi(caracte)*100;
        fscanf(arqui,"%c",&caracte);tempo = tempo + atoi(caracte)*10;
        fscanf(arqui,"%c",&caracte);tempo = tempo + atoi(caracte);
        fclose(arqui);
        AKI: fflush(stdin);
}
///////////////////////////////////////////////////////////////////////////////////////////             
recortaenergia(char nome_arqx[100])//RECORTA: A CONTAGEM, A ENERGIA, 
{                                  // O ELEMENTO E, A INCERTEZA DE UM .TXT
   int picos=0, i,n=0, m, auxi;
   FILE *arqx;
   char linha[LMAX];
   arqx = fopen(nome_arqx,"r"); /*zerando as matrizes*/
   for(i=0;i<=30;i++) elemento[i]=0;
   for(i=0;i<119;i++) contagem[i]=0;// 13/02/2012 alterando o número de repetições do looping para zerar direito este os dois próximos vetores
   for(i=0;i<=119;i++) energia[i]=0;
   for(i=0;i<=119;i++)  incerteza[i]=0;
   if (!arqx)
   {
         printf("Falha ao abrir o arquivo %s",nome_arqx);
         fflush(stdin);
         getchar();
   }
   else
  {
   for (i=0;i<5;i++)/*contando o numero de picos*/
      fgets(linha,LMAX,arqx);
   for(i=0; picos==0; i++)
      if(isdigit(linha[i])!=0)
         picos=atoi(linha+i);//Usando a forma de ponteiro para colocar o índice da célula a ser lida do vetor
   for(m=0;m<picos;m++)/*armazenando nos vetores*/ //04/10/2011 -- Entender esta parte do código para justificar as mundanças feitas acima.
   {fgets(linha,LMAX,arqx);
   for(i=0;elemento[m]==0;i++)// seria como "para i = 0, incremente i enquanto elemento[k] for diferente de zero."
                             {if(isdigit(linha[i])!=0)
                                                                {elemento[m]=atoi(linha+i);
                                                                                           }}
                       i++;
                       while(energia[elemento[m]]==0)// 13/02/2012 Alteração no looping que zera os vetores por causa dessa linha
                                        {if(isdigit(linha[i])!=0)
                                                                {energia[elemento[m]]=atoi(linha+i);
                                                                                          }
                                        i++;}
                       i=i+6;
                       auxi = 0;
                       while(contagem[elemento[m]]==0)// 13/02/2012 Alteração no looping que zera os vetores por causa dessa linha
                       {
                                         if (linha[i] == '-') auxi = 1;
                                         if(isdigit(linha[i])!=0) 
                                         {  
                                               contagem[elemento[m]]=atoi(linha+i);
                                               if (contagem[elemento[m]] == 0) contagem[elemento[m]] = -1;
                                         }
                                         i++;
                       } 
                       //if (auxi == 1) contagem[m] = contagem[m]*(-1);
                       i=i+8;
                       if (contagem[elemento[m]] == 0) contagem[elemento[m]] = -1;
                       while(incerteza[elemento[m]]==0)// 13/02/2012 Alteração no looping que zera os vetores por causa dessa linha
                                        {if(isdigit(linha[i])!=0)
                                                                {incerteza[elemento[m]]=atoi(linha+i);

                                                           }
                                        i++;}}
   
   }
   fclose(arqx);
   return 0;                                     
}// A função com as correções faz o que se espera dela. As energias, contagem e incertezas aparecem no índice correspondente ao índice do elemento químico.
///Olhar agora as variáveis locais e corrigí-las, alterando os índices - 13-10-2011///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
saida()//FUNÇÃO CHAMADA PELA MAIORIA DAS FUNÇÕES, POIS REALIZA O RETORNO PARA O MENU
{        //ANTERIOR
  system("cls");
  return;
}
//////////////////////////////////////////////////////////////////////////////////
convertenumero(char numero[10])//FUNCAO QUE CONVERTE A CHAR DA TABELA PARA FLOAT/////////////////////
{
   int i, x;
   char aux[0];
   float  y,cont;
   i = 0;
   cont = 1;
   x = 1;
   while (numero[i] != ',')//CONTA QTAS CASAS ACIMA DE ZERO O ALGARISMO POSSUI
   {
      cont = cont*10;
      i++;
   }
   i = 0;
   if (numero[0] == '-') ///PROCURA PELO SINAL NEGATIVO
   {
       x = -1;
       cont = cont/10;
       i = 1;
   }   
   y = 0.0;
   while (i <= 10) //GERA O NUMERO CASA A CASA
   {
        fflush(stdin);
        if (numero[i] != ',') aux[0] = numero[i];
        else
        {
           cont = 0.1;
           i++;
           aux[0] = numero[i];
        }  
        y = (y + (atoi(aux)*cont));
        cont = (cont/10);
        i++;
  }
  conv = 0;
  conv = y*x;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
recortafatorderesposta(char nome_arq[80])//RECORTA OS FATORES DE RESPOSTA E OS COLOCA
{                                        /// NA MATRIZ FT_RESPOSTA[][]
      FILE *aq;
      int i,m, d; 
      char linha[LMAX], k[0], tst[1], rp[1], nome[80];
      float cont;
      for (d=0; d<= 80 ;d++) nome[d] = nome_arq[d];
      for(d=0;d < 149;d++)
      {
        ft_resposta[d][1] = 0.0;
        ft_resposta[d][2] = 0.0;
        ft_resposta[d][3] = 0.0;        
      }
      tst[1] = '*';
      while (tst[1] == '*')
      {
            aq = fopen(nome,"r");
            if (!aq)
            {
               printf("\nFalha ao abrir o arquivo %s", nome);
               fflush(stdin);
               printf("\nDeseja digitar um novo nome para o arquivo? (S/N)");
               fflush(stdin);
               scanf("%c",&rp[1]);
               if ((rp[1] == 'S') || (rp[1]=='s'))
               {
                 printf("\nNovo nome:  ");
                 scanf("%s",&nome);
                 strcat(nome,".txt");
                 printf("\nEste arquivo corresponde a qual linha? (K/L)");
                 fflush(stdin);
                 scanf("%c",&rp[1]);
                 while ((rp[1] != 'K') && (rp[1] != 'k') && (rp[1] != 'L') && (rp[1] != 'l'))
                 {
                   printf("\nOpcao invalida!! Digite novamente!!");
                   fflush(stdin);
                   scanf("\n%c",&rp[1]);
                 } 
                 if ((rp[1] == 'L') || (rp[1]=='l'))  for (d=0; d<= 80 ;d++) ftrl[d] = nome[d];
                 if ((rp[1] == 'K') || (rp[1]=='k'))  for (d=0; d<= 80 ;d++) ftrk[d] = nome[d];
               }  
               else
               {
                     printf("A FALTA DESTE ARQUIVO OCASIONA ERROS NO PROCESSO...");
                     getchar();
                     goto AKI;
               }
            }
            else tst[1] = '+';
      }  
      fgets(linha,LMAX,aq);
      d = 0;
      while (!feof(aq))
      {
           m = 1;
           i = 0;
           fgets(linha,LMAX,aq);
           k[0] = linha[i];
           ft_resposta[d][1] = (atof(k)*10);
           i++;
           k[0] = linha[i];
           i++;
           ft_resposta[d][1] = ft_resposta[d][1] + (atof(k));
           i++;
           cont = 100;
           ft_resposta[d][2] = 0;
           if (linha[i] == '-')
           {
             m = -1;
             i++;
           }  
           while ((isdigit(linha[i])) != 0)
           {
                 k[0] = linha[i];
                 ft_resposta[d][2] = (ft_resposta[d][2] + (atof(k)*cont)); 
                 if (linha[i+1] == ',')
                 {
                      i++;
                      cont=1;
                 }
                 cont = cont/10 ;
                 i++;
           } 
           ft_resposta[d][2] = ft_resposta[d][2]*m;
           i++;
           while ((isdigit(linha[i])) != 0)
           {
                 k[0] = linha[i];
                 ft_resposta[d][3] = (ft_resposta[d][3] + (atof(k)*cont)); 
                 if (linha[i+1] == ',')
                 {
                      i++;
                      cont=1;
                 }
                 cont = cont/10 ;
                 i++;
           } 
           ft_resposta[d][3] = ft_resposta[d][3]*m;
           d++;
      }
      fclose(aq); 
      AKI: fflush(stdin);  
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
fator_de_resposta (int n, int k) // Função Corrigida. 20/10/2011
{
                               switch (n)///ANALISE DAS ENERGIAS
                               {
                                  case 11:
                                    recortafatorderesposta(ftrk); 
                            	    break;
                                  case 12:
                                    recortafatorderesposta(ftrk); 
                                 	break;
                                  case 13:
                                    recortafatorderesposta(ftrk); 
                     	            break;       	
                                  case 14:
                                    recortafatorderesposta(ftrk); 
                     	            break;
                                  case 15:
                                    recortafatorderesposta(ftrk); 
                     	            break;
                                  case 16:
                                    recortafatorderesposta(ftrk); 
                    	            break;
                                  case  17:
                                    recortafatorderesposta(ftrk); 
                    	            break;
                 	              case 18:
                                    recortafatorderesposta(ftrk); 
                                    break;
                                  case 19:
                                    recortafatorderesposta(ftrk); 
                        	        break;       	
                                  case 20: 
                                    if(energia[ elemento[k] ]==3) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==0) recortafatorderesposta(ftrl); 
                                    break;
                                  case 21:
                                    if(energia[ elemento[k] ]==4) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==0) recortafatorderesposta(ftrl); 
                                    break;
                                  case 22:
                                    if(energia[ elemento[k] ]==4) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==0) recortafatorderesposta(ftrl); 
                                    break;
                                  case 23:
                                    if(energia[ elemento[k] ]==4) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==0) recortafatorderesposta(ftrl); 
                                    break;
                                  case 24:
                                    if(energia[ elemento[k] ]==5) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==0) recortafatorderesposta(ftrl); 
                                    break;
                                  case 25: 
                                    if(energia[ elemento[k] ]==5) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==0) recortafatorderesposta(ftrl); 
                                    break;
                                  case 26:
                                    if(energia[ elemento[k] ]==6) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==0) recortafatorderesposta(ftrl); 
                                    break;
                                  case 27: 
                                    if(energia[ elemento[k] ]==6) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==0) recortafatorderesposta(ftrl); 
                                    break;
                                  case 28:
                                    if(energia[ elemento[k] ]==7) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==0) recortafatorderesposta(ftrl); 
                                    break;
                                  case 29:
                                    if(energia[ elemento[k] ]==8) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==0) recortafatorderesposta(ftrl); 
                                	break;
                                  case 30:
                                    if(energia[ elemento[k] ]==8) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==1) recortafatorderesposta(ftrl); 
                                    break;
                    	          case 31:
                                    if(energia[ elemento[k] ]==9) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==1) recortafatorderesposta(ftrl); 
                                    break;
                    	          case 32:
                                    if(energia[ elemento[k] ]==9) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==1) recortafatorderesposta(ftrl); 
                           	        break;
                              	  case 33:
                                    if(energia[ elemento[k] ]==10) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==1) recortafatorderesposta(ftrl); 
                                    break;
                           	      case 34:
                                    if(energia[ elemento[k] ]==11) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==1) recortafatorderesposta(ftrl); 
                                    break;
                    	          case 35: 
                                    if(energia[ elemento[k] ]==11) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==1) recortafatorderesposta(ftrl); 
                                    break;
                    	          case 36: 
                                    if(energia[ elemento[k] ]==12) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==1) recortafatorderesposta(ftrl); 
                                    break;
                    	          case 37:
                                    if(energia[ elemento[k] ]==13) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==1) recortafatorderesposta(ftrl); 
                	                break;
                           	      case 38:
                                    if(energia[ elemento[k] ]==14) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==1) recortafatorderesposta(ftrl); 
                                    break;
                    	          case 39: 
                                    if(energia[ elemento[k] ]==14) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==1) recortafatorderesposta(ftrl); 
                                    break;
                    	          case 40: 
                                    if(energia[ elemento[k] ]==15) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==2) recortafatorderesposta(ftrl); 
                           	        break;
                                  case 41: 
                                    if(energia[ elemento[k] ]==16) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==2) recortafatorderesposta(ftrl); 
                	                break;
                    	          case 42: 
                                    if(energia[ elemento[k] ]==17) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==2) recortafatorderesposta(ftrl); 
                           	        break;
                        	      case 43: 
                                    if(energia[ elemento[k] ]==18) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==2) recortafatorderesposta(ftrl); 
                              	    break;
                    	          case 44:
                                    if(energia[ elemento[k] ]==19) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==2) recortafatorderesposta(ftrl); 
                           	        break;
                    	          case 45:
                                    if(energia[ elemento[k] ]==20) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==2) recortafatorderesposta(ftrl); 
                                    break;
                    	          case 46:
                                    if(energia[ elemento[k] ]==21) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==2) recortafatorderesposta(ftrl); 
                                    break;
                    	          case 47: 
                                    if(energia[ elemento[k] ]==22) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==2) recortafatorderesposta(ftrl); 
                                    break;
                    	          case 48:
                                    if(energia[ elemento[k] ]==23) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==3) recortafatorderesposta(ftrl); 
                                    break;
                    	          case 49: 
                                    if(energia[ elemento[k] ]==24) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==3) recortafatorderesposta(ftrl); 
                           	        break;
                    	          case 50: 
                                    if(energia[ elemento[k] ]==25) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==3) recortafatorderesposta(ftrl); 
                           	        break;
                    	          case 51:
                                    if(energia[ elemento[k] ]==26) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==3) recortafatorderesposta(ftrl); 
                           	        break;
                                  case 52:
                                    if(energia[ elemento[k] ]==27) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==3) recortafatorderesposta(ftrl); 
                           	        break;
                       	          case 53:
                                    if(energia[ elemento[k] ]==28) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==3) recortafatorderesposta(ftrl); 
                           	        break;
                       	          case 54:
                                    if(energia[ elemento[k] ]==29) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==4) recortafatorderesposta(ftrl); 
                                    break;
                         	      case 55: 
                                    if(energia[ elemento[k] ]==30) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==4) recortafatorderesposta(ftrl); 
                           	        break;
                       	          case 56:
                                    if(energia[ elemento[k] ]==32) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==4) recortafatorderesposta(ftrl); 
                                    break;
                       	          case 57:
                                    if(energia[ elemento[k] ]==33) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==4) recortafatorderesposta(ftrl); 
                           	        break;
                       	          case 58: 
                                    if(energia[ elemento[k] ]==34) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==4) recortafatorderesposta(ftrl); 
                           	        break;
                       	          case 59:
                                    if(energia[ elemento[k] ]==36) recortafatorderesposta(ftrk); 
                                    if(energia[ elemento[k] ]==5) recortafatorderesposta(ftrl); 
                           	        break;
                       	          case 60:
                                   if(energia[ elemento[k] ]==37) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==5) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 61:
                                   if(energia[ elemento[k] ]==38) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==5) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 62:
                                   if(energia[ elemento[k] ]==40) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==5) recortafatorderesposta(ftrl); 
                                   break;
                       	         case 63:
                                   if(energia[ elemento[k] ]==41) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==5) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 64:
                                   if(energia[ elemento[k] ]==42) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==6) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 65:
                                   if(energia[ elemento[k] ]==44) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==6) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 66:
                                   if(energia[ elemento[k] ]==45) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==6) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 67:
                                   if(energia[ elemento[k] ]==47) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==6) recortafatorderesposta(ftrl); 
                           	       break;
                          	     case 68:
                                   if(energia[ elemento[k] ]==49) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==6) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 69:
                                   if(energia[ elemento[k] ]==50) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==7) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 70:
                                   if(energia[ elemento[k] ]==52) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==7) recortafatorderesposta(ftrl); 
                           	       break;
                          	     case 71: 
                                   if(energia[ elemento[k] ]==54) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==7) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 72: 
                                   if(energia[ elemento[k] ]==55) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==7) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 73:
                                   if(energia[ elemento[k] ]==57) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==8) recortafatorderesposta(ftrl); 
                                   break;
                       	         case 74: 
                                   if(energia[ elemento[k] ]==59) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==8) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 75:
                                   if(energia[ elemento[k] ]==61) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==8) recortafatorderesposta(ftrl); 
                           	       break;
                          	     case 76:
                                   if(energia[ elemento[k] ]==63) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==8) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 77:
                                   if(energia[ elemento[k] ]==64)recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==9) recortafatorderesposta(ftrl); 
                           	       break;
                          	     case 78:
                                   if(energia[ elemento[k] ]==66) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==9) recortafatorderesposta(ftrl); 
                                   break;
                       	         case 79:
                                   if(energia[ elemento[k] ]==68) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==9) recortafatorderesposta(ftrl); 
                           	       break;
                           	     case 80: 
                                   if(energia[ elemento[k] ]==70) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==9) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 81: 
                                   if(energia[ elemento[k] ]==72) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==10) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 82: 
                                   if(energia[ elemento[k] ]==74) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==10) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 83:
                                   if(energia[ elemento[k] ]==77) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==10) recortafatorderesposta(ftrl); 
                           	       break;
                            	 case 84:
                                   if(energia[ elemento[k] ]==79) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==11) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 85: 
                                   if(energia[ elemento[k] ]==81) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==11) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 86:
                                   if(energia[ elemento[k] ]==83) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==11) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 87: 
                                   if(energia[ elemento[k] ]==86) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==12) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 88: 
                                   if(energia[ elemento[k] ]==88) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==12) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 89: 
                                   if(energia[ elemento[k] ]==90) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==12) recortafatorderesposta(ftrl); 
                                   break;
                       	         case 90: 
                                   if(energia[ elemento[k] ]==93) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==12) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 91: 
                                   if(energia[ elemento[k] ]==95) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==13) recortafatorderesposta(ftrl); 
                           	       break;
                       	         case 92: 
                                   if(energia[ elemento[k] ]==98) recortafatorderesposta(ftrk); 
                                   if(energia[ elemento[k] ]==13) recortafatorderesposta(ftrl); 
                           	       break;
                          	     case 93: 
                                   if(energia[ elemento[k] ]==13) recortafatorderesposta(ftrl); 
                                   break;
                       	         case 94:
                                   if(energia[ elemento[k] ]==14) recortafatorderesposta(ftrl); 
                           	       break;
               	                case 95:
                                   if(energia[ elemento[k] ]==14) recortafatorderesposta(ftrl); 
                           	   break;
                    	default:
                            	ind = -2;
                       }
}

int IndiceVolumeAtual(int Imax, char *arquivo){//24/12/2011
    int i=0;
    while( ( strstr(arquivo, nomevolume[i] ) == NULL ) || ( i <= Imax ) ){
           if ( strstr(arquivo, nomevolume[i]) == NULL ) i++;
           else break;
    }
    if ( i > Imax ){
       printf("\nErro!\nNão há volume para esta amostra do arquivo. %s", arquivo);
       exit(1);
    }
    else return(i);
}

ImprimeZsEmLinha(char imprime[], int k, int vmin1, int vmax1, int vmin2, int vmax2, int vmin3, int vmax3, int ndivmax){// ndivmax Número máximo de arquivos em que o espectro está dividido. Esta função pretende substituir o trecho em que são selecionados os elementos a serem impressos no código presente em calculos()

     for (k=0; k<=30; k++)//(01-11-2011) - USO DOS Zmins E Zmaxs DE CADA PARTE DO ESPECTRO DENTRO DESTE FOR. EM TODOS AS PARTES (ARQUIVOS), TODOS OS ELEMENTOS SÃO LIDOS, MAS APENAS OS QUE ESTÃO DENTRO DE UMA REGIÃO EM CADA PARTE QUE DEVEM SER ANALISADOS SÃO MARCADOS COM UM '*'. ENTÃO AS DEMAIS PARTES DO CÓDIGO PROCESSAM AS INFORMAÇÕES.
         {
               if (((elemento[k] >= vmin1) && (elemento[k] <= vmax1)) && (elemento[k] != 0)) imprime[elemento[k]] = '*';
               if ((ndivmax == 2) && (((elemento[k] >= vmin2) && (elemento[k] <= vmax2)) || ((elemento[k] >= vmin1) && (elemento[k] <= vmax1))&& (elemento[k] != 0))) imprime[elemento[k]] = '*';  
               if ((ndivmax == 3) && (((elemento[k] >= vmin3) && (elemento[k] <= vmax3)) || ((elemento[k] >= vmin2) && (elemento[k] <= vmax2)) || ((elemento[k] >= vmin1) && (elemento[k] <= vmax1)) && (elemento[k] != 0))) imprime[elemento[k]] = '*';            
         }
     
}

int ChecaParametrosIniciais(char arquivo[][500], int MaxPartes){
     int parte, i=0, flag=0;
     char Parte[4], arquivotxt[100],coringa[100];
     FILE *fp;
     while ( (arquivo[i][0] != '\0') ^ (arquivo[i][0] != '\n') ){
           for ( parte=1; parte<=MaxPartes; parte++ ){
               sprintf(Parte, "[%d]",parte);
               strcpy( arquivotxt, Parte );
               sscanf(arquivo[i],"%[^.spe]", coringa);//(07/05/2012) Coloca o nome do arquivo sem o SPE
               strcat(coringa,".txt");//(07/05/2012) Adiciona a extensão .txt
               strcat(arquivotxt, coringa);
               if ( (fp=fopen(arquivotxt, "r" )) == NULL ){
                    printf("\nArquivo %s não encontrado.", arquivotxt);
                    flag=1;                    
               }
               fclose(fp);
           }
           i++;
     }
     if (flag){// se flag==1
        printf("\nOs arquivos acima não foram encontrados e o programa será fechado.\n");
        exit(1);
     }
}


////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
