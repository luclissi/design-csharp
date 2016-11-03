#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Salário-de-contribuição (R$): até 1.556,94 – Alíquota para fins de recolhimento ao INSS (%) = 8,00;
Salário-de-contribuição (R$): de 1.556,95  até 2.594,92– Alíquota para fins de recolhimento ao INSS (%) = 9,00;
Salário-de-contribuição (R$): de 2.594,93 até 5.189,82 – Alíquota para fins de recolhimento ao INSS (%) = 11,00;
Salário-de-contribuição (R$): maior que 5.189,82(Teto) – Alíquota para fins de recolhimento ao INSS = R$ 570,88;

*/
#define INSS1 0.08 
#define INSS2 0.09 
#define INSS3 0.11


/*
O Fundo de Garantia por Tempo de Serviço tem porcentagem única de 8%, calculada sobre o salário bruto 
(com exceção do salário-família, caso esse seja um direito do funcionário em questão). 
Ao contrário do INSS, quem arca com o depósito do FGTS é o empregador.
*/
#define FGTS 0.08 

/*
1º faixa: parcela a deduzir 0,00, 0% sobre bases até  R$ 1.903,98;
2ª faixa: parcela a deduzir 142,80, 7,5% sobre bases entre R$ 1.903,99 e R$ 2.826,65;
3ª faixa: parcela a deduzir 354,80, 15% sobre bases entre R$ 2.826,66 e R$ 3.751,05;
4ª faixa: parcela a deduzir 636,13, 22,5% sobre bases entre R$ 3.751,06 e R$ 4.664,68;
5ª faixa: parcela a deduzir 869,36, 27,5% sobre bases iguais a R$ 4.664,69 ou acima desse número.
Para quem possui dependentes, a dedução é de R$ 189,59 no desconto apurado.
*/
//Parcelas
#define IRRFP1 142.80
#define IRRFP2 354.80
#define IRRFP3 636.13
#define IRRFP4 869.36
//Porcentagens 
#define IRRF1 0.075
#define IRRF2 0.15
#define IRRF3 0.225
#define IRRF4 0.275
//dependente
#define DEPE 189.59


/*
Trabalhadores cuja base de cálculo não ultrapassa R$ 806,80 têm direito a R$ 41,37. 
Na 2ª faixa, cujo ganho é de R$ 29,16, constam funcionários que o rendimento se encontra entre R$ 806,80 e R$ 1.212,64.
*/
#define SF1 41.37
#define SF2 29.16


char nome[1024];
char *cargo;

float salarioBruto,salarioL;

float inss = 1.00,irrf = 0.00;// descontos

float fgts = 1.00,sf = 0.00;//acrecimos

int dependente,idadeFilho;

FILE *f;
int main(){
		
	int opt;
	do{
		menu();
		printf("\n  Infomer a opcao: ");
		scanf("%d",&opt);
		switch(opt){
			case 1:
				cadastrar(0);
				break;
			case 2:
				read();
				break;
			case 3:
				cadastrar(1);
				break;
			case 4:
				printf(" Ate Logo!!");
				break;
			default:
				break;
		}
		
		
	}
	while(opt != 4);
	return 0;
}
menu(){
	system("cls");
	printf("------------------------------------------------------------\n");
	printf("----------------ONG----BOLHA---DE---SABAO-------------------\n");
	printf("------------------------------------------------------------\n");
	printf("-   1 -  Cadastro de Funcionario                           -\n");
	printf("-   2 -  Folha de Pagamento                                -\n");
	printf("-   3 -  Holerite                                          -\n");
	printf("-   4 -  Sair                                              -\n");
	printf("------------------------------------------------------------\n");
}

cadastrar(int tcad){
	int opt;
	printf("Informe o nome: ");
	scanf("%s",&nome);
	do{
		printf(" \n\n   Cargos: \n");
		printf("            1 - Monitores \n");
		printf("            2 - Estagiario \n");
		printf("  			3 - Voluntario \n");	
		printf("Informe o cargo: ");
		scanf("%d",&opt);
		switch(opt){
			case 1:
				cargo = "Monitor";
				break;
			case 2:
				cargo = "Estagiario";
				break;
			case 3:
				cargo = "Voluntario";
				break;
			default:
				printf("\n	CARGO INVALIDO! POR FAVOR INFORME UMA OPCAO VALIDA! ");
				break;
		}
	}while(opt<1&&opt>3);
	printf("Informe o Salario Bruto Ex. 420.00: ");
	scanf("%f",&salarioBruto);
	printf("Quantos dependentes possui: ");
	scanf("%d",&dependente);
	printf("Possui filho 1 - Sim, 2 - Nao: ");
	scanf("%d",&idadeFilho);
	if(idadeFilho==1){
		printf("Informe a idade do filho: ");
		scanf("%d",&idadeFilho);
	}
	if(tcad==0){
		save();
	}else{
		holerite();
	}
}
holerite(){
	calculoInss();
	calculoFgts();	
	calculoIrrf();
	calculoSf();
	salarioL = salarioBruto - inss - irrf + fgts+sf;
	printf("\nO Salario Bruto eh: R$ %.2f",salarioBruto);
	printf("\nO Salario Liquido eh: R$ %.2f",salarioL);
	printf("\nO Desconto de INSS eh: R$ %.2f",inss);
	printf("\nO Desconto de IRRF eh: R$ %.2f",irrf);
	printf("\nO Acrescimo de FGTS eh: R$ %.2f",fgts);
	printf("\nO Acrescimo de Salario Familia eh: R$ %.2f\n",sf);
	system("pause");
}

calculoInss(){
	if(salarioBruto<= 1556.94){
		inss = salarioBruto*INSS1;
	}else if(salarioBruto<= 2594.92){
		inss = salarioBruto*INSS2;
	}else if(salarioBruto<= 5189.82){
		inss = salarioBruto*INSS3;
	}else{
		inss = salarioBruto - 570.88;
	}
}

calculoFgts(){
	fgts = salarioBruto*FGTS;
}

calculoIrrf(){
	if(salarioBruto <= 1903.98){
		irrf = 	DEPE*dependente;
	}else if(salarioBruto <= 2826.65){
		irrf = 	(salarioBruto-inss-(DEPE*dependente))*IRRF1-IRRFP1;
	}else if(salarioBruto <= 3751.05){
		irrf = 	(salarioBruto-inss-(DEPE*dependente))*IRRF2-IRRFP2;
	}else if(salarioBruto <= 4664.68){
		irrf = 	(salarioBruto-inss-(DEPE*dependente))*IRRF3-IRRFP3;
	}else if(salarioBruto <= 4664.69){
		irrf = 	(salarioBruto-inss-(DEPE*dependente))*IRRF4-IRRFP4;
	}
}

calculoSf(){
	if(idadeFilho <= 14){
		if(salarioBruto <= 806.80){
			sf = SF1;
		}else if(salarioBruto <= 1212.64){
			sf = SF2;
		}
	}
}


save(){
	char conver[sizeof(float)];
	f = fopen("cadastro.csv","ab");
	fputs(nome,f);
	fputc(';',f);
	fputs(cargo,f);
	fputc(';',f);
	sprintf(conver, "%.2f", salarioBruto);
	fputs(conver,f);
	fputc(';',f);
	sprintf(conver, "%d", dependente);
	fputs(conver,f);
	fputc(';',f);
	sprintf(conver, "%d", idadeFilho);
	fputs(conver,f);
	fputs("\n",f);
	fclose(f);
	
	printf(" Cadastro realizado com sucesso!\n");
	system("pause");
}

read(){
	f = fopen("cadastro.csv","rb");
	char line[1024],*token;
	int cod = 1;
	printf("------------------------------------------------\n");
	printf("-- 1-CODIGO -- 2-NOME -- 3-CARGO -- 4-SALARIO --\n");
    while(fgets(line, sizeof line, f) != NULL){
    	printf("-- 1-%d ",cod);
        token = strtok(line, ";");
        printf("-- 2-%s ",token);
        token = strtok(NULL,";");
        printf("-- 3-%s ",token);
        token = strtok(NULL,";");    	
        printf("-- 4-%.2f ",strtod(token,NULL));
        token = strtok(NULL,";");
        printf("-- 5-%d ",atoi(token));
        token = strtok(NULL,";");
        printf("-- 6-%d --\n",atoi(token));
        cod = cod + 1;
    }
    printf("------------------------------------------------\n");
	fclose(f);
	system("pause");
}

