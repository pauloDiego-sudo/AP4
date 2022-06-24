#include <stdio.h>
#include <time.h>
#include <string.h>
#include "funcoes.h"
/*dizer quais doses tomaram, por exemplo, se ele tomou a 2nd dose e não a primeira etc
 0 não tomou, 1 ele tomou
se quiser pode registrar a data exata do cara, para simplificar o código*/

//optei pelo ID porque pode existir pessoas com o mesmo nome no Brasil



int main(void) {
  FILE *arq;
  arq = fopen("vacinados.txt","r");
  if(arq != NULL){
    printf("\nBEM VINDO AO SUDS (Sistema Unificado de Dados Da Saúde)\n"); 
    int opc; 
    while(opc!=0){
      printf("\nEscolha uma opção!\n1-Cadastro de cidadão\n2-Listar cidadãos cadastrados\n3-Adicionar Vacina\n0-Finalizar o Programa\n");
      scanf("%d",&opc);
      switch(opc){
        case 1:
          arq=fopen("vacinados.txt","a+");
          cadastro(arq);
          fclose(arq);
        break;
        case 2:
          arq=fopen("vacinados.txt","r");
          listar(arq);
        break;
        case 3:
          arq=fopen("vacinados.txt","r+");
          atualizarVac(arq);
          fclose(arq);
        break;
        case 0:
          printf("\n#### PROGRAMA FINALIZADO ####\n");
        break;
        default:
          printf("\nEscolha uma opção válida!!\n");
        break;
      }
    }
   // fclose(arq);
  }
  else{
    arq = fopen("vacinados.txt","w");
    if(arq!= NULL){carregamento();}
    fclose(arq);
  }
  
  return 0;
}
