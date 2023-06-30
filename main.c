#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAXIMODEPASSAGEIROS 15
#define TAMANHO_CPF 15

typedef struct Passageiro{
    char nome[100];
    char cpf[TAMANHO_CPF];
    char endereco[200];
    char telefone[15];
    int numeroPassagem;
    int id;
    int numeroPoltrona;
    int numeroVoo;
    char horarioVoo[5];
}Passageiro;

int carregaBancoDeDadosDoVooSelecionado(int vooSelecionado,Passageiro *listaDePassageiros);
int menuInicial();
int menuVoos(int vooSelecionado);
int mostrarListaDePassageiros(Passageiro *listaDePassageiros, int quantidadeDePassageiros);
int buscarPassageiroPorNome(Passageiro *listaDePassageiros, int quantidadeDePassageiros);
int buscarPassageiroPorCPF(Passageiro *listaDePassageiros, int quantidadeDePassageiros);
int mostrarListaDeEspera(Passageiro *listaDePassageiros, int quantidadeDePassageiros);
int cadastrarPassageiro(Passageiro *listaDePassageiros, int *quantidadeDePassageiros, int vooSelecionado);
int excluirPassageiro(Passageiro *listaDePassageiros, int *quantidadeDePassageiros, int vooSelecionado);
int validarCPF(const char *cpf);

int main()
{
    menuInicial();
    return 0;
}

/* ******************************
Fun��o: menuInicial
Descri��o:
    Exibe o menu inicial, permitindo ao usu�rio selecionar um voo.
    O usu�rio pode escolher entre os voos BH-RIO, BH-SP e BH-BRASILIA.
    � poss�vel fechar o programa digitando 9.

Par�metros:
    Nenhum.

Retorno:
    int - 0 (indicando que a fun��o foi executada com sucesso).
****************************** */
int menuInicial() {
    int vooSelecionado;
    char input[100];

    do {
        printf("---------- EMPRESA AEREA QUEDA LIVRE ----------\n");
        printf("    MENU DE VOOS    \n");
        printf("[1]BH-RIO\n[2]BH-SP\n[3]BH-BRASILIA\n\n[9]Para fechar o programa.\n\n");
        printf("Digite a opcao referente ao voo desejado: ");

        do {
            scanf("%s", input);
            if (sscanf(input, "%d", &vooSelecionado) != 1) {
                printf("Valor invalido. Digite um numero inteiro: ");
            }
        } while (sscanf(input, "%d", &vooSelecionado) != 1);

        switch (vooSelecionado) {
            case 1: {
                menuVoos(1);
                break;
            }
            case 2: {
                menuVoos(2);
                break;
            }
            case 3: {
                menuVoos(3);
                break;
            }
            case 9: {
                return 0;
                break;
            }
            default: {
                printf("Voo invalido.\n\n");
            }
        }
    } while (vooSelecionado != 1 && vooSelecionado != 2 && vooSelecionado != 3);

    return 0;
}

/* ******************************
Fun��o: menuVoos
Descri��o:
    Exibe o menu de op��es para um determinado voo selecionado. Permite ao usu�rio interagir com diferentes funcionalidades do programa,
    como mostrar a lista de passageiros, pesquisar passageiros por CPF ou nome, cadastrar novos passageiros, excluir passageiros da lista e
    mostrar a lista de espera. O usu�rio tamb�m pode selecionar outro voo ou sair do programa.

Par�metros:
    int vooSelecionado - o �ndice do voo selecionado.

Retorno:
    int - 0 (indicando que a fun��o foi executada com sucesso).
****************************** */
int menuVoos(int vooSelecionado) {
    Passageiro listaDePassageiros[MAXIMODEPASSAGEIROS];
    int quantidadeDePassageiros = 0;

    quantidadeDePassageiros = carregaBancoDeDadosDoVooSelecionado(vooSelecionado, listaDePassageiros);
    int *PONTEIROquantidadeDePassageiros = &quantidadeDePassageiros;

    char voos[][20] = {"VOO BH-RIO", "VOO BH-SP", "VOO BH-BRASILIA"};
    int opcaoMenu = 0;

    printf("---------- EMPRESA AEREA QUEDA LIVRE - %s ----------\n", voos[vooSelecionado - 1]);
    printf("  MENU DE OPCOES  \n");
    printf("[1] Mostrar lista de passageiros\n[2] Pesquisar passageiro por CPF\n");
    printf("[3] Pesquisar passageiro por nome\n[4] Cadastrar passageiro\n");
    printf("[5] Excluir passageiro da lista\n[6] Mostrar lista de espera\n");
    printf("\n[9] Sair\n");
    printf("\nDigite sua opcao: ");

    char input[100];
    while (scanf("%s", input) == 1) {
        if (sscanf(input, "%d", &opcaoMenu) != 1) {
            printf("Valor invalido. Digite um numero inteiro: ");
        } else {
            switch (opcaoMenu) {
                case 1: {
                    mostrarListaDePassageiros(listaDePassageiros, quantidadeDePassageiros);
                    break;
                }
                case 2: {
                    buscarPassageiroPorCPF(listaDePassageiros, quantidadeDePassageiros);
                    break;
                }
                case 3: {
                    buscarPassageiroPorNome(listaDePassageiros, quantidadeDePassageiros);
                    break;
                }
                case 4: {
                    cadastrarPassageiro(listaDePassageiros, PONTEIROquantidadeDePassageiros, vooSelecionado);
                    break;
                }
                case 5: {
                    excluirPassageiro(listaDePassageiros, PONTEIROquantidadeDePassageiros, vooSelecionado);
                    break;
                }
                case 6: {
                    mostrarListaDeEspera(listaDePassageiros, quantidadeDePassageiros);
                    break;
                }
                case 9: {
                    menuInicial();
                    return 0;
                }
                default: {
                    printf("Opcao invalida.\n\n");
                }
            }
        }

        printf("\nDigite sua opcao (Voo selecionado no momento: %s): ", voos[vooSelecionado - 1]);
    }

    return 0;
}

/* ******************************
Fun��o: carregaBancoDeDadosDoVooSelecionado
Descri��o:
    Carrega os dados do banco de dados de passageiros correspondente ao voo selecionado.
    Os dados s�o lidos de um arquivo de texto espec�fico para cada voo e s�o armazenados na lista de passageiros fornecida.

Par�metros:
    int vooSelecionado - o �ndice do voo selecionado.
    Passageiro *listaDePassageiros - um ponteiro para a lista de passageiros onde os dados ser�o armazenados.

Retorno:
    int - a quantidade de passageiros carregados do banco de dados.

Observa��es:
    - A fun��o espera que existam arquivos de texto nomeados "BHRIO.txt", "BHSP.txt" e "BHBRASILIA.txt" correspondendo aos voos BH-RIO, BH-SP e BH-BRASILIA, respectivamente.
    - A fun��o assume que a estrutura de dados Passageiro est� corretamente definida e que a
    listaDePassageiros tem capacidade suficiente para armazenar todos os passageiros do banco de dados.
    - A fun��o retorna 0 se ocorrer algum erro ao carregar os dados do voo selecionado.
****************************** */
int carregaBancoDeDadosDoVooSelecionado(int vooSelecionado, Passageiro *listaDePassageiros) {
    FILE *bancoDeDados;
    switch (vooSelecionado) {
        case 1: {
            bancoDeDados = fopen("BHRIO.txt", "r");
            printf("CARREGANDO DADOS DO VOO BHRIO...\n");
            break;
        }
        case 2: {
            bancoDeDados = fopen("BHSP.txt", "r");
            printf("CARREGANDO DADOS DO VOO BHSP...\n");
            break;
        }
        case 3: {
            bancoDeDados = fopen("BHBRASILIA.txt", "r");
            printf("CARREGANDO DADOS DO VOO BHBRASILIA...\n");
            break;
        }
        default: {
            printf("Nao foi possivel carregar o banco de dados do voo selecionado.\n");
            return 1;
        }
    }

    if (bancoDeDados == NULL) {
        printf("Nao foi possivel carregar os dados do voo.\n");
        return 1;
    }

    int quantidadeDePassageiros = 0;

    for (int i = 0; i < MAXIMODEPASSAGEIROS; i++) {
        int result = fscanf(bancoDeDados, "id: %d| cpf: %14[^|]| nome: %99[^|]| endereco: %199[^|]| telefone: %14[^|]| numero da passagem: %d| numero da poltrona: %d| numero do voo: %d| horario: %5[^\n]\n",
            &listaDePassageiros[i].id,
            &listaDePassageiros[i].cpf,
            &listaDePassageiros[i].nome,
            &listaDePassageiros[i].endereco,
            &listaDePassageiros[i].telefone,
            &listaDePassageiros[i].numeroPassagem,
            &listaDePassageiros[i].numeroPoltrona,
            &listaDePassageiros[i].numeroVoo,
            &listaDePassageiros[i].horarioVoo);

        if (result == EOF) {
            break;
        }

        quantidadeDePassageiros++;
    }

    fclose(bancoDeDados);
    return quantidadeDePassageiros;
}

/* ******************************
Fun��o: mostrarListaDePassageiros
Descri��o:
    Mostra a lista de passageiros do voo.
    A fun��o exibe o nome, CPF, n�mero da passagem e n�mero da poltrona de cada passageiro.
    Caso a quantidade de passageiros seja maior que 10, apenas os primeiros 10 passageiros ser�o exibidos.

Par�metros:
    Passageiro *listaDePassageiros - um ponteiro para a lista de passageiros.
    int quantidadeDePassageiros - a quantidade total de passageiros.

Retorno:
    int - 0 (indicando que a fun��o foi executada com sucesso).
****************************** */
int mostrarListaDePassageiros(Passageiro *listaDePassageiros, int quantidadeDePassageiros){
    if(quantidadeDePassageiros<=10){
        for(int i = 0; i<quantidadeDePassageiros; i++){
            printf("Passageiro %d - Nome: %s | cpf: %s | numero da passagem: %d | numero da poltrona: %d\n",
                i+1, listaDePassageiros[i].nome, listaDePassageiros[i].cpf, listaDePassageiros[i].numeroPassagem, listaDePassageiros[i].numeroPoltrona);
        }
    }
    else{
        for(int i = 0; i<10; i++){
            printf("Passageiro %d - Nome: %s | cpf: %s | numero da passagem: %d | numero da poltrona: %d\n",
                i+1, listaDePassageiros[i].nome, listaDePassageiros[i].cpf, listaDePassageiros[i].numeroPassagem, listaDePassageiros[i].numeroPoltrona);
        }
    }
    return 0;
}

/* ******************************
Fun��o: buscarPassageiroPorNome
Descri��o:
    Busca por um passageiro no voo pelo seu nome.
    A fun��o recebe como input do usu�rio uma string e realiza a busca na lista de passageiros do voo.
    Caso o passageiro seja encontrado, s�o exibidos nome, CPF, telefone, n�mero da passagem, n�mero da poltrona, n�mero do voo e hor�rio do voo.
    Caso o passageiro n�o seja encontrado, uma mensagem informando isso � exibida.

Par�metros:
    Passageiro *listaDePassageiros - um ponteiro para a lista de passageiros.
    int quantidadeDePassageiros - a quantidade total de passageiros.

Retorno:
    int - 0 (indicando que a fun��o foi executada com sucesso).
Observa��es:
    - Caso o nome digitado pelo usu�rio seja amb�guo e possa se referir a mais de um passageiro, a fun��o exibir� os detalhes de todos os passageiros encontrados com nomes semelhantes.
    - A fun��o considera a compara��o de nomes em letras min�sculas, ignorando diferen�as de caixa (mai�sculas ou min�sculas). Portanto, a busca n�o � sens�vel a mai�sculas ou min�sculas.
****************************** */
int buscarPassageiroPorNome(Passageiro *listaDePassageiros, int quantidadeDePassageiros){
    char inputNome[100];
    getchar();
    printf("Digite o nome do passageiro: ");
    scanf("%[^\n]",inputNome);
    getchar();
    int passageiroNoVoo = 0;
    for(int i = 0; inputNome[i]; i++){
      inputNome[i] = tolower(inputNome[i]);
    }
    char passageiroAtual[100];
    for(int i = 0; i<quantidadeDePassageiros; i++){
        strcpy(passageiroAtual, listaDePassageiros[i].nome);
        passageiroAtual[strlen(inputNome)] = '\0';
        for(int i = 0; passageiroAtual[i]; i++){
          passageiroAtual[i] = tolower(passageiroAtual[i]);
        }
        if(strcmp(passageiroAtual, inputNome) == 0){
            printf("Passageiro: %s - CPF: %s - Telefone: %s - Numero da passagem: %d - Numero da poltrona: %d - Numero do voo: %d - Horario do voo: %s\n",
                   listaDePassageiros[i].nome,
                   listaDePassageiros[i].cpf,
                   listaDePassageiros[i].telefone,
                   listaDePassageiros[i].numeroPassagem,
                   listaDePassageiros[i].numeroPoltrona,
                   listaDePassageiros[i].numeroVoo,
                   listaDePassageiros[i].horarioVoo
                   );
            passageiroNoVoo = 1;
        }
    }
    if(passageiroNoVoo == 0){
        printf("Passageiro nao consta neste voo.\n");
    }
    return 0;
}

/* ******************************
Fun��o: buscarPassageiroPorCPF
Descri��o:
    Busca por um passageiro no voo pelo seu CPF.
    A fun��o solicita ao usu�rio que digite o CPF do passageiro e realiza a busca na lista de passageiros do voo.
    Caso o passageiro seja encontrado, s�o exibidos nome, CPF, telefone, n�mero da passagem, n�mero da poltrona, n�mero do voo e hor�rio do voo.
    Caso o passageiro n�o seja encontrado, uma mensagem informando isso � exibida.

Observa��es:
    - A fun��o desconsidera caracteres especiais no CPF fornecido pelo usu�rio.
    Isso � feito para facilitar o input do usu�rio, permitindo que ele digite o CPF com ou sem pontua��es.
    Por exemplo, se o CPF do passageiro for "123.456.789-00", o usu�rio pode digitar "12345678900" e o sistema realizar� a busca corretamente.

Par�metros:
    Passageiro *listaDePassageiros - um ponteiro para a lista de passageiros.
    int quantidadeDePassageiros - a quantidade total de passageiros.

Retorno:
    int - 0 (indicando que a fun��o foi executada com sucesso).
****************************** */
int buscarPassageiroPorCPF(Passageiro *listaDePassageiros, int quantidadeDePassageiros) {
    char inputCPF[100];
    getchar();
    printf("Digite o CPF do passageiro: ");
    scanf("%[^\n]", inputCPF);
    getchar();

    char cpfSemCaracteresEspeciais[100];
    int j = 0;
    for (int i = 0; inputCPF[i]; i++) {
        if (isdigit(inputCPF[i])) {
            cpfSemCaracteresEspeciais[j] = inputCPF[i];
            j++;
        }
    }
    cpfSemCaracteresEspeciais[j] = '\0';

    int passageiroNoVoo = 0;
    for (int i = 0; i < quantidadeDePassageiros; i++) {
        char passageiroAtualSemCaracteresEspeciais[100];
        int k = 0;
        for (int j = 0; listaDePassageiros[i].cpf[j]; j++) {
            if (isdigit(listaDePassageiros[i].cpf[j])) {
                passageiroAtualSemCaracteresEspeciais[k] = listaDePassageiros[i].cpf[j];
                k++;
            }
        }
        passageiroAtualSemCaracteresEspeciais[k] = '\0';

        if (strcmp(passageiroAtualSemCaracteresEspeciais, cpfSemCaracteresEspeciais) == 0) {
            printf("Passageiro: %s - CPF: %s - Telefone: %s - Numero da passagem: %d - Numero da poltrona: %d - Numero do voo: %d - Horario do voo: %s\n",
                   listaDePassageiros[i].nome,
                   listaDePassageiros[i].cpf,
                   listaDePassageiros[i].telefone,
                   listaDePassageiros[i].numeroPassagem,
                   listaDePassageiros[i].numeroPoltrona,
                   listaDePassageiros[i].numeroVoo,
                   listaDePassageiros[i].horarioVoo
            );
            passageiroNoVoo = 1;
        }
    }

    if (passageiroNoVoo == 0) {
        printf("Passageiro nao consta neste voo.\n");
    }

    return 0;
}

/* ******************************
Fun��o: mostrarListaDeEspera
Descri��o:
    Exibe a lista de espera de passageiros de um voo.
    A fun��o verifica se o n�mero total de passageiros � maior que 10.
    Caso seja menor ou igual a 10, significa que n�o h� lista de espera e uma mensagem indicando isso � exibida.
    Caso contr�rio, a fun��o exibe os detalhes dos passageiros da lista de espera, incluindo nome, CPF, n�mero da passagem e n�mero da poltrona.

Par�metros:
    Passageiro *listaDePassageiros - um ponteiro para a lista de passageiros.
    int quantidadeDePassageiros - a quantidade total de passageiros.

Retorno:
    int - 0 (indicando que a fun��o foi executada com sucesso).
****************************** */
int mostrarListaDeEspera(Passageiro *listaDePassageiros, int quantidadeDePassageiros){
    if(quantidadeDePassageiros<=10){
        printf("Esse voo esta sem lista de espera.\n");
    }else{
        for(int i = 10; i<=quantidadeDePassageiros-1; i++){
            printf("Passageiro %d - Nome: %s | cpf: %s | numero da passagem: %d | numero da poltrona: %d\n",
            i+1, listaDePassageiros[i].nome, listaDePassageiros[i].cpf, listaDePassageiros[i].numeroPassagem, listaDePassageiros[i].numeroPoltrona);
        }
    }
    return 0;
}

/* ******************************
Fun��o: validarCPF
Descri��o:
    Verifica se um CPF � v�lido, ou seja, verifica a formata��o dele e se � composto apenas por n�meros e os respectivos caracteres especiais.
    Caso o CPF seja v�lido, a fun��o retorna 1. Caso contr�rio, retorna 0.

Observa��o:
    -Essa fun��o � utilizada especificamente para o cadastro de passageiros.

Par�metros:
    const char *cpf - uma string contendo o CPF a ser validado.

Retorno:
    int - 1 se o CPF � v�lido, 0 caso contr�rio.
****************************** */
int validarCPF(const char *cpf) {
    int i;
    int digitos[11];
    int soma = 0;

    if (strlen(cpf) != 14)
        return 0;

    if(cpf[3]!= '.')
        return 0;

    if(cpf[7]!= '.')
        return 0;

    if(cpf[11]!= '-')
        return 0;

    for(int i = 0; i<14; i++){
        if(i==3)i++;
        if(i==7)i++;
        if(i==11)i++;
        if (!(isdigit(cpf[i]))) return 0;
    }

    return 1;
}

/* ******************************
Fun��o: cadastrarPassageiro
Descri��o:
    Realiza o cadastro de um passageiro, recebendo as informa��es necess�rias e armazenando no banco de dados correspondente ao voo selecionado.
    A fun��o tamb�m realiza algumas valida��es, como verificar se o CPF j� est� cadastrado e se a fila de passageiros est� cheia.

Par�metros:
    Passageiro *listaDePassageiros - um array de estruturas Passageiro que armazena os dados dos passageiros.
    int *quantidadeDePassageiros - um ponteiro para a vari�vel que indica a quantidade atual de passageiros cadastrados.
    int vooSelecionado - um valor que representa o voo selecionado para o cadastro do passageiro.

Retorno:
    int - 0 se o cadastro for realizado com sucesso, 1 caso contr�rio.
****************************** */
int cadastrarPassageiro(Passageiro *listaDePassageiros, int *quantidadeDePassageiros, int vooSelecionado) {
    FILE *bancoDeDados;
    switch (vooSelecionado) {
        case 1: {
            bancoDeDados = fopen("BHRIO.txt", "a+");
            break;
        }
        case 2: {
            bancoDeDados = fopen("BHSP.txt", "a+");
            break;
        }
        case 3: {
            bancoDeDados = fopen("BHBRASILIA.txt", "a+");
            break;
        }
        default: {
            printf("Nao foi possivel carregar o banco de dados do voo selecionado.\n");
            return 1;
        }
    }

    if (bancoDeDados == NULL) {
        printf("Nao foi possivel carregar os dados do voo.\n");
        return 1;
    }
    if (*quantidadeDePassageiros >= 15) {
        printf("Fila cheia, a reserva nao pode ser feita.\n");
        return 1;
    }

    int p = *quantidadeDePassageiros;
    int ultimaPoltrona = listaDePassageiros[p-1].numeroPoltrona;
    int ultimaPassagem = listaDePassageiros[p-1].numeroPassagem;

    char input[200];

    printf("----- CADASTRO DE PASSAGEIROS -----\n");
    int nomeValido;
    do{
        nomeValido = 1;
        printf("Digite o nome do passageiro: ");
        getchar();
        scanf("%[^\n]", input);
        getchar();
        for(int i=0; i<strlen(input); i++){
            if(input[i] != ' '){
                if(!(isalpha(input[i]))){
                    printf("Nome invalido. Tente novamente.\n");
                    nomeValido = 0;
                    break;
                }
            }
        }
    }while(!(nomeValido));

    strcpy(listaDePassageiros[*quantidadeDePassageiros].nome, input);


    int cpfValido;
    do {
        cpfValido = 1;
        printf("Digite o CPF do passageiro: ");
        scanf(" %[^\n]", input);
        getchar();

        if (!validarCPF(input)) {
            printf("CPF invalido. Digite o CPF no formato XXX.XXX.XXX-XX. Tente novamente.\n");
            cpfValido = 0;
        }

        for (int i = 0; i < *quantidadeDePassageiros - 1; i++) {
            if (strcmp(input, listaDePassageiros[i].cpf) == 0) {
                printf("CPF j� cadastrado. Tente novamente.\n");
                cpfValido = 0;
                break;
            }
        }

        if (cpfValido) {
            strcpy(listaDePassageiros[*quantidadeDePassageiros].cpf, input);
        }
    } while (!cpfValido);

    printf("Digite o endereco do passageiro: ");
    scanf(" %[^\n]", listaDePassageiros[*quantidadeDePassageiros].endereco);
    getchar();

    printf("Digite o telefone do passageiro: ");
    scanf(" %[^\n]", listaDePassageiros[*quantidadeDePassageiros].telefone);
    getchar();

    strcpy(listaDePassageiros[*quantidadeDePassageiros].horarioVoo, listaDePassageiros[1].horarioVoo);
    listaDePassageiros[*quantidadeDePassageiros].numeroVoo = vooSelecionado;
    listaDePassageiros[*quantidadeDePassageiros].id = *quantidadeDePassageiros+1;
    listaDePassageiros[*quantidadeDePassageiros].numeroPassagem = ultimaPassagem+1;
    listaDePassageiros[*quantidadeDePassageiros].numeroPoltrona = ultimaPoltrona+1;

    fprintf(bancoDeDados, "id: %d| cpf: %s| nome: %s| endereco: %s| telefone: %s| numero da passagem: %d| numero da poltrona: %d| numero do voo: %d| horario: %s\n",
            listaDePassageiros[*quantidadeDePassageiros].id,
            listaDePassageiros[*quantidadeDePassageiros].cpf,
            listaDePassageiros[*quantidadeDePassageiros].nome,
            listaDePassageiros[*quantidadeDePassageiros].endereco,
            listaDePassageiros[*quantidadeDePassageiros].telefone,
            listaDePassageiros[*quantidadeDePassageiros].numeroPassagem,
            listaDePassageiros[*quantidadeDePassageiros].numeroPoltrona,
            listaDePassageiros[*quantidadeDePassageiros].numeroVoo,
            listaDePassageiros[*quantidadeDePassageiros].horarioVoo);
    printf("\n--------CADASTRO COMPLETO--------\n");

    (*quantidadeDePassageiros)++;
    fclose(bancoDeDados);
    return 0;
}

/* ******************************
Fun��o: excluirPassageiro
Descri��o:
    Exclui um passageiro da lista de passageiros do voo selecionado.
    A fun��o recebe o ID do passageiro a ser exclu�do e realiza a exclus�o da lista, atualizando o arquivo de banco de dados do voo.

Par�metros:
    Passageiro listaDePassageiros[] - um array de estruturas Passageiro contendo a lista de passageiros do voo.
    int *quantidadeDePassageiros - um ponteiro para a quantidade total de passageiros.
    int vooSelecionado - um inteiro indicando o voo selecionado.

Retorno:
    int - 0 (indicando que a fun��o foi executada com sucesso).
Observa��es:
    - A fun��o busca o passageiro pelo ID informado e remove o seu registro da lista de passageiros, reescrevendo todos os registros restantes na nova ordem.
    - Caso o ID do passageiro esteja dentro do intervalo de 1 a 9 (inclusivo) e a quantidade de passageiros seja maior que 10,
    � exibida uma mensagem informando que um passageiro saiu da lista de espera e entrou para o voo.
    - A fun��o utiliza arquivos de texto para armazenar os dados do voo. Os nomes dos arquivos s�o formados de acordo com o voo selecionado: "BHRIO.txt", "BHSP.txt" e "BHBRASILIA.txt".
    - Caso n�o seja poss�vel abrir ou carregar os dados do banco de dados do voo selecionado, a fun��o exibe uma mensagem de erro e retorna 1.
    - Os dados dos passageiros s�o armazenados no arquivo de banco de dados no seguinte formato:
    "id: %d| cpf: %s| nome: %s| endereco: %s| telefone: %s| numero da passagem: %d| numero da poltrona: %d| numero do voo: %d| horario: %s\n"
****************************** */
int excluirPassageiro(Passageiro listaDePassageiros[], int *quantidadeDePassageiros, int vooSelecionado) {
    FILE *bancoDeDados;
    switch (vooSelecionado) {
        case 1: {
            bancoDeDados = fopen("BHRIO.txt", "r+");
            break;
        }
        case 2: {
            bancoDeDados = fopen("BHSP.txt", "r+");
            break;
        }
        case 3: {
            bancoDeDados = fopen("BHBRASILIA.txt", "r+");
            break;
        }
        default: {
            printf("Nao foi possivel carregar o banco de dados do voo selecionado.\n");
            return 1;
        }
    }

    if (bancoDeDados == NULL) {
        printf("Nao foi possivel carregar os dados do voo.\n");
        return 1;
    }
    if (*quantidadeDePassageiros == 0) {
        printf("Voo vazio.\n");
        fclose(bancoDeDados);
        return 1;
    }

    int idExcluir;
    printf("Digite o ID do passageiro a ser excluido: ");
    scanf("%d", &idExcluir);

    int indiceExcluir = -1;

    for (int i = 0; i < *quantidadeDePassageiros; i++) {
        if (listaDePassageiros[i].id == idExcluir) {
            indiceExcluir = i;
            break;
        }
    }

    if (indiceExcluir == -1) {
        printf("Passageiro nao encontrado.\n");
        fclose(bancoDeDados);
        return 1;
    }

    for (int i = indiceExcluir; i < *quantidadeDePassageiros - 1; i++) {
        listaDePassageiros[i] = listaDePassageiros[i + 1];
    }

    if(indiceExcluir <= 9 && quantidadeDePassageiros > 10){
        printf("%s saiu da lista de espera e entrou para o voo!\n", listaDePassageiros[9].nome);
    }
    *quantidadeDePassageiros -= 1;

    fclose(bancoDeDados);
    FILE *bancoDeDados2;
    switch (vooSelecionado) {
        case 1: {
            bancoDeDados2 = fopen("BHRIO.txt", "w");
            break;
        }
        case 2: {
            bancoDeDados2 = fopen("BHSP.txt", "w");
            break;
        }
        case 3: {
            bancoDeDados2 = fopen("BHBRASILIA.txt", "w");
            break;
        }
        default: {
            printf("Nao foi possivel carregar o banco de dados do voo selecionado.\n");
            return 1;
        }
    }

    if (bancoDeDados2 == NULL) {
        printf("Nao foi possivel carregar os dados do voo.\n");
        return 1;
    }

    for (int i = 0; i < *quantidadeDePassageiros; i++) {
        fprintf(bancoDeDados, "id: %d| cpf: %s| nome: %s| endereco: %s| telefone: %s| numero da passagem: %d| numero da poltrona: %d| numero do voo: %d| horario: %s\n",
                i+1, listaDePassageiros[i].cpf, listaDePassageiros[i].nome, listaDePassageiros[i].endereco,
                listaDePassageiros[i].telefone, listaDePassageiros[i].numeroPassagem, listaDePassageiros[i].numeroPoltrona,
                listaDePassageiros[i].numeroVoo, listaDePassageiros[i].horarioVoo);
    }

    fclose(bancoDeDados2);
    printf("Passageiro excluido com sucesso.\n");
    return 0;
}
