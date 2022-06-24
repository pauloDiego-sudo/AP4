#ifndef funcoes
#define funcoes

void limpa_linha(void){
  int i, c=50;
  printf("\r");
  for(i=0;i<c;i++){
    printf(" ");
  }
  printf("\r");
}
void carregamento(void){ //função da tela de carregamento, aparece se o arquivo não existir :)
  int i, j,c=50;
  system("clear");//limpa tela
  printf("\nInstalando o programa: \n"); //desculpa para criar o arquivo :v (o usuário não precisa saber disso)      
  for(i=0;i<=100;i++){
    printf ("%d%% ",i);      
    fflush (stdout);
    for(j=0;j<i%10;j++){
        printf(".");
     }
    fflush(stdout);
    usleep(50000);
    limpa_linha();                    
  }
 printf("\n\n Programa instalado! \n Rode o programa novamente!\n\n");       
}


int contaLinhas(FILE *arq){
  int linhas=0;
  char txt[100];
  rewind(arq);     
  do{ //conta a quantidade de linhas do arquivo
    linhas++;
  } while( fgets(txt,100,arq) != NULL );
  linhas--;
  return linhas;
}

int confereCad(FILE *arq,int id){
  rewind(arq); //volta para o começo do arquivo
  char txt[100];
  int flag=0,id2;
  do{ //confere se o id já existe
      fscanf(arq,"%d",&id2);
      if(id==id2){
          flag = 0; //se existir, ele retorna 0 como flag
        break;
         }
      else{
        flag=1;
      }
    }while( fgets(txt,100,arq) != NULL );
    return flag;
}

void cadastro(FILE *arq){
  int checkid,*v,i; //talvez usar malloc
  int id,idade;
  char nome[32];
  printf("Digite o ID do cidadão: "); 
  scanf("%d",&id);
  if(id>0){
    checkid = confereCad(arq,id); 
    if(checkid==0){ //verifica se o cara tá cadastrado
       printf("\nCidadão já cadastrado no Sistema! \n");
    }
    else if(checkid==1){
       __fpurge(stdin); //limpando o buffer antes de pegar o nome
      fflush(stdin); //para windows
      printf("Nome Completo: ");
      scanf("%32[^\n]",nome); //expressão regular para pegar 32 carateres para nome e até o usuário apertar enter
      printf("Idade: ");
      scanf("%d",&idade);
      int v[4]={0,0,0,0};//independente da idade, há possibilidade de ter 4 dose no futuro
      char vac[5]={'f','f','f','f'}; //f de falta
      if(idade>39 && idade<135){
        for(i=0;i<4;i++){
          printf("Já tomou a vacina %d? (s ou n)  ",i+1);
          scanf("%s",&vac[i]); //só funionou com "s" no replit
          if(vac[i]=='n' || vac[i]=='N'){
            v[i]=0;
            break;
          }
          else if(vac[i]=='s' || vac[i]=='S'){
            v[i]=1;
          }
          else if (v[i]!='f' || v[i]!='F' || v[i]!='s' || v[i]!='S' || v[i]!='n' || v[i]!='N' ){
            printf("Opção inválida!\n");
            i--; //pede a opção até ser uma válida
          }
      }
         fprintf(arq,"\n%d %s %d %d %d %d %d",id,nome,idade,v[0],v[1],v[2],v[3]);
        }
      else if(idade<39 && idade>0){
        for(i=0;i<3;i++){
          printf("Já tomou a vacina %d? (s ou n) ",i+1);
          scanf("%s",&vac[i]);
          if(vac[i]=='n' || vac[i]=='N'){
            v[i]=0;
            break;
          }
          else if(vac[i]=='s' || vac[i]=='S'){
            v[i]=1;
          }
          else if (v[i]!='f' || v[i]!='F' || v[i]!='s' || v[i]!='S' || v[i]!='n' || v[i]!='N' ){
            printf("Opção inválida! \n");
            i--;
          }
      }
      fprintf(arq,"\n%d %s %d %d %d %d",id,nome,idade,v[0],v[1],v[2]);
        }
      else{printf("Idade inválida!!");}
    }
  }
  else{
    printf("\nID inválido!\n"); //valores negativos não são aceitos
    }
}

void listar(FILE *arq){
  int id,v[4],idade,soma=0,qtd=0;
  char aux[100],nome[32];
  rewind(arq);
    do
    {
      fscanf(arq,"%d",&id);
      fscanf(arq,"%[^0123456789]",nome); //usando Regex para não pegar numero
      fscanf(arq,"%d",&idade);
      if(idade>39){
        fscanf(arq,"%d %d %d %d",&v[0],&v[1],&v[2],&v[3]);
        soma=v[0]+v[1]+v[2]+v[3];
        qtd=4;
        }
      else{
        fscanf(arq,"%d %d %d",&v[0],&v[1],&v[2]);
        soma=v[0]+v[1]+v[2];
        qtd=3;
        }
      
      printf("Nome: %s \n",nome);
      printf("Idade: %d \n",idade);
      printf("Vacinas Tomadas: %d/%d \n",soma,qtd);
      
      //printf("Dia: %s \n",data); 
      printf("\n");
    
    }while(fgets(aux,100,arq) != NULL);
}
void atualizarVac2(FILE *arq,int id){
  int idade,v[4],id2,i;
  char txt[100],nome[32],rsp;
  fscanf(arq,"%d",&idade);
  if(idade>39){
    for(i=0;i<4;i++){
      fscanf(arq,"%d",&v[i]);
      if(v[i]==0){
      printf("Atualizar vacina %d ? ",i+1);
      scanf("%s",&rsp);
        if(rsp=='s' || rsp=='S'){
          fseek(arq,-1,SEEK_CUR);
          fprintf(arq,"%d",1);
          printf("\nConfirmada dose %d da vacina!",i+1);
          break;
          }
        else if(rsp=='n' || rsp=='N'){
          printf("\n\n");
          break;
        }
        }
      }
    }
    else if(idade<39){
    for(i=0;i<3;i++){
      fscanf(arq,"%d",&v[i]);
      if(v[i]==0){
      printf("Atualizar vacina %d ?",i+1);
      scanf("%s",&rsp);
        if(rsp=='s' || rsp=='S'){
          fseek(arq,-1,SEEK_CUR);
          fprintf(arq,"%d",1);
          printf("\nConfirmada dose %d da vacina!\n",i+1);
          break;
          }
        else if(rsp=='n' || rsp=='N'){
          printf("\n\n");
          break;
        }
        }
      }
    }
}

void atualizarVac(FILE *arq){
  int id,id2,check;
  char aux[100],nome[32],op;
  printf("Qual o ID do cidadão que irá atualizar?: ");
  scanf("%d",&id);
  check=confereCad(arq,id);
  if(check==1){ //se não estiver cadastrado
    printf("Cidadão não cadastrado!");
  }
  else{
    rewind(arq);
    do{
      fscanf(arq,"%d",&id2);
      fscanf(arq,"%[^0123456789]",nome);
      if(id==id2){
          printf("Atualizar vacina de %s ? ",nome);
          scanf("%s",&op);
        if(op=='s' || op =='S'){
          atualizarVac2(arq,id2);
        }
        else if(op=='n' || op =='n'){
          printf("\n\nOK\n\n");
          break;
          }
        }
    }while( fgets(aux,100,arq) != NULL );
    
  }
}


#endif
