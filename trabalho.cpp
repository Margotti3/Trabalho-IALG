#include <iostream>
#include <fstream>

using namespace std;

// Mateus Margotti Pereira Cunha

// especificações do trabalho
// tema: rodovias
// busca: busca sequencial
// ordenação: selection sort
// gravação: texto

// o código utiliza de system("clear") para melhorar a visualização
// existe alguns getchar() espalhados q eu indicarei com um comentário ***
// eles são usados para impedir q o system execute antes da saída desejada

// registro com os dados da data
struct Data{
    int dia;
    int mes;
    int ano;
};

// registro com os dados da rodovia q utilizam do registro data
struct Rodovia{
    int id;
    string nome;
    float tam;
    Data criacao;
    string desc;
};

void ordena(Rodovia rodovias[], int tam){
    // selection sort
    int posicao, menor;
    Rodovia aux;
    for(int x = 0; x < tam-1; x++){
        menor = rodovias[x].id;
        posicao = x;

        // busca um a um para achar a menor id
        for(int y = x+1; y < tam; y++){
            if(menor > rodovias[y].id){
                menor = rodovias[y].id;
                posicao = y;
            }
        }

        // utiliza do aux para fazer a troca entre o registro de menor id
        // com o registro da posicao x
        aux = rodovias[x];
        rodovias[x] = rodovias[posicao];
        rodovias[posicao] = aux;
    }
}

int busca(int id, Rodovia rodovias[], int tam){
    // busca sequencial

    //busca um a um do último ao primeiro a rodovia com a id
    while(rodovias[tam].id != id && tam >= 0){
        tam--;
    }
    // return = -1 se n encontrar nenhuma rodovia com a id requerida
    // se encontrar retornar a posicao do mesmo
    return tam;
}

void incluir(Rodovia rodovias[],int posicao){
    // série de entradas e saídas para criar um novo registro
    cout << endl << "Vou pedir para você digitar algumas informações" << endl;
    cout << endl << "Identificação (ex. 1012): ";
    cin >> rodovias[posicao].id;

    // faz a verificação se já existe um registro com a id requerida
    // se houver ele pede um novo
    while(busca(rodovias[posicao].id, rodovias, posicao-1) != -1){
        cout << endl << "Identificação existente, digite outro: ";
        cin >> rodovias[posicao].id;
    }

    // utilizei de getline para pegar ate espaços
    // e o getchar para evitar dar problemas como o enter em cin
    cout << endl << "Nome ou código (ex. rodovia legal): ";
    getchar();
    getline(cin, rodovias[posicao].nome);
    cout << endl << "Extensão em km (ex. 2.3): ";
    cin >> rodovias[posicao].tam;
    cout << endl << "Data de criação (ex. 20 02 2020): ";
    cin >> rodovias[posicao].criacao.dia
        >> rodovias[posicao].criacao.mes
        >> rodovias[posicao].criacao.ano;
    cout << endl << "Descriação em uma linha (ex. texto): ";
    getchar();
    getline(cin, rodovias[posicao].desc);
}

void excluir(int auxId, Rodovia rodovias[], int &tam){

    // faço a busca da id requerida
    int posicao = busca(auxId, rodovias, tam-1);
    if(posicao == -1){
        cout << endl << "Registro não encontrado!";
    }
    else{
        // se ela existir é passado os dados do registro posterior
        // para a posicao em questão e assim sucessívelmente até o fim 
        for(int x = posicao; x < tam-1; x++){
            rodovias[x] = rodovias[x+1];
        }

        // -1 na quantidade de registros = var posicao
        tam--;
        cout << endl << "Registro excluído com sucesso!";
    }
}

void listar(Rodovia rodovias[], int tam){
    system("clear");

    // apenas a saída dos dados de cara registro junto a quantidade de cadastrados
    cout << "Existem " << tam << " rodovias cadastradas" << endl << endl;
    for(int x = 0; x < tam; x++){
        cout << "identificação:" << rodovias[x].id << endl
            << "nome: " << rodovias[x].nome << endl
            << "extensão: " << rodovias[x].tam << "km" << endl
            << "criação: " << rodovias[x].criacao.dia << "/" << rodovias[x].criacao.mes << "/" << rodovias[x].criacao.ano << endl
            << "descrição: " << rodovias[x].desc << endl << endl;
    }

}

void alterar(int auxId, Rodovia rodovias[], int tam){
    system("clear");

    // busca a id requerida
    int posicao = busca(auxId, rodovias, tam-1);
    int escolha;

    if(posicao == -1){
        cout << endl << "Registro não encontrado!";
        getchar();
    }
    else{
        // se encontrar é apresentado um menu de possíveis alterações
        cout << "------------------------------" << endl
             << "|Escolha algo para alterar:  |" << endl
             << "|1 - nome                    |" << endl
             << "|2 - extensão                |" << endl
             << "|3 - data                    |" << endl
             << "|4 - descrição               |" << endl
             << "------------------------------" << endl << endl
             << "Digite o número da opção: " ;
        cin >> escolha;

        // uma série de entrada e saídas para a alteração do compo desejado
        switch(escolha){
            case 1:

                cout << "Nome ou código (ex. rodovia legal): ";
                getchar();
                getline(cin, rodovias[posicao].nome);
                break;

            case 2:

                cout << "Extensão em km (ex. 2.3): ";
                cin >> rodovias[posicao].tam;
                getchar(); // ***
                break;

            case 3:

                cout << "Data de criação (ex. 20 02 2020): ";
                cin >> rodovias[posicao].criacao.dia
                    >> rodovias[posicao].criacao.mes
                    >> rodovias[posicao].criacao.ano;
                getchar(); // ***
                break;

            case 4:

                cout << "Descriação em uma linha (ex. texto): ";
                getchar();
                getline(cin, rodovias[posicao].desc);
                break;

        }

        cout << endl << "Registro alterado com sucesso";
    }
}

void gravar(Rodovia rodovias[], int tam){
    // como pedido, antes da gravação dos dados eles devem ser ordenados
    ordena(rodovias, tam);
    // aqui é aberto o arquivo de modo q possamos gravar
    ofstream arquivo("dados.txt");

    // verifica se o arquivo foi aberto corretamente
    if(arquivo){

        // insere os dados como é feito a listagem do menu
        for(int x=0; x<tam; x++){
            arquivo << "identificação:" << rodovias[x].id << endl
                << "nome: " << rodovias[x].nome << endl
                << "extensão: " << rodovias[x].tam << "km" << endl
                << "criação: " << rodovias[x].criacao.dia << "/" << rodovias[x].criacao.mes << "/" << rodovias[x].criacao.ano << endl
                << "descrição: " << rodovias[x].desc << endl << endl;
        }

        cout << "Seus dados foram gravados com sucesso no arquivo dados.txt" << endl << endl;

        // fecha o arquivo
        arquivo.close();
    }
    else{
        cout << "Infelizmente não conseguimos gravar seus dado :(" << endl << endl;
    }
}

int main(){
    // limpar tudo para facilitar visualização
    system("clear");
    // declaração de variáveis muito utilizados
    int escolha, posicao = 0, auxId;
    // inclusive a declaração dinâmica dos registros
    Rodovia *rodovias = new Rodovia[100];

    do{
        // listagem de opções
        cout << "------------------------------" << endl
             << "|Escolha algo para fazer:    |" << endl
             << "|1 - incluir                 |" << endl
             << "|2 - excluir                 |" << endl
             << "|3 - listar                  |" << endl
             << "|4 - alterar                 |" << endl
             << "|5 - gravar                  |" << endl
             << "|0 - sair                    |" << endl
             << "------------------------------" << endl << endl
             << "Digite o número da opção: " ;

        cin >> escolha;

        switch(escolha){
            case 1:

                // if para n permitir mais de 100 rodovias cadastradas
                if(posicao < 100){
                    // se ainda n tiver 100 ele faz processo de inclusão
                    // e soma +1 posicao pelo novo registro
                    incluir(rodovias, posicao);
                    cout << endl << "Registro incluído com sucesso!";
                    posicao++;
                }
                else{
                    cout << endl << "Não é possível inserir novo registro";
                    getchar(); // ***
                }


                break;

            case 2:

                // pede a id do registro a ser excluído e chama a função de exclusão
                cout << endl << "Digite a identificação do registro (ex. 1012): ";
                cin >> auxId;
                getchar(); // ***
                excluir(auxId, rodovias, posicao);
                break;

            case 3:

                // ordena primeiro pela id e depois lista
                ordena(rodovias, posicao);
                listar(rodovias, posicao);
                getchar(); // ***
                break;

            case 4:

                // pede a id do registro a ser alterado e chamar a função de alteração
                cout << endl << "Digite a identificação do registro (ex. 1012): ";
                cin >> auxId;
                alterar(auxId, rodovias, posicao);
                break;

            case 5:

                gravar(rodovias, posicao);
                getchar(); // ***
                break;

            default:

                // vem para cá caso o usuário queira sair ou digite opção inválida
                getchar(); // ***
        }

        // apresenta esse comando para q o usuário possa visualizar todas as saídas
        // antes do system("clear") limpar tudo
        cout << endl << endl << "Pressione a tecla enter para continuar...";
        getchar();
        system("clear");

        // se a opção for diferente de 0 ele vai persistir em apresentar o menu
    }while(escolha);

    // deixa q o usuário escolha entre gravar os dados em um arquivo
    char escolha2;
    cout << "Deseja gravar os dados inseridos em um arquivo? [s/n]: ";
    cin >> escolha2;
    system("clear");

    if(escolha2 == 's'){
        // se a resposta for 's' é chamado a função de gravação
        gravar(rodovias, posicao);
    }

    // aqui deslocamos da memória os registros de rodovias e encerramos o trabalho
    delete[] rodovias;
    cout << "Agradecemos o uso de nosso sistema ;)" << endl;

    return 0;
}