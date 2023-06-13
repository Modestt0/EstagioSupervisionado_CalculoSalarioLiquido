#include<iostream>
#include<math.h>
#include<fstream>
#include<string.h>
#include"Estagio.h"
using namespace std;

List::List(){
    //pré-condição: Nenhuma;
    //pós-condição: A lista é criada e, caso tenha um arquivo com informações de funcionários, ela abre
    //e salva eles na lista. Caso contrário é começada vazia;

    Head = new ListNode;
    Head->PrevNode = Head;
    Head->NextNode = Head;
    Count = 0;

    ifstream inFuncionarios("Funcionario.csv", ios::binary | ios::in);
    //Abre ou cria um arquivo;

    while(inFuncionarios.read((char *) &Head->Func, sizeof(Dados))){
        AbreArquivo(Head->Func);
    }
    //Salva as informações dos funcionário no caso do arquivo existir;

    inFuncionarios.close();
    //fecha o arquivo;

}

List::~List(){
    //pré-condição: A lista ja foi criada;
    //pós-condição: A lista é destruida e caso haja funcionarios salvos nela, eles são transferidos para
    //um arquivo chamado Funcionario.csv;

    ListPointer q;

    ofstream outFuncionarios("Funcionario.csv", ios::binary | ios::out);
    //Abre o arquivo;

    while(Count!=0){
        q = Head;
        Head = Head->NextNode;
        outFuncionarios.write((char *) &Head->Func, sizeof(Dados));
        delete q;
        Count--;
    }
    //Salva os dados dos funcionários e exclui em seguida para destruir a lista e fechar o programa;

    outFuncionarios.close();
    //fecha o arquivo;
    
}

bool List::Full(){
    //pré-condição: lista já tenha sido criada;
    //pós-condição: retorna true caso a lista esteja cheia. Caso contrário, retorna false;

    return false;
}

bool List::Empty(){
    //pré-condição: lista já tenha sido criada;
    //pós-condição: retorna true caso a lista esteja vazia. Caso contrário, retorna false;

    return Count==0;
}

void List::AbreArquivo(Dados Funcionario){
    //pré-condição: lista tenha sido criada;
    //pós-condição: Caso tenha informações guardadas dentro de um arquivo, pega suas informações e coloca
    //dentro da lista;

    ListPointer q, p;

    p = Head;
    q = Head->NextNode;
    Head->Func = Funcionario;
        
    while(q->Func.Salario_Brt < Funcionario.Salario_Brt){
        p = q;
        q = q->NextNode;
    }
    //while para percorrer a lista salvando os funcionarios de acordo com seus salários;

    q = new ListNode;

    if(q==NULL){
        cout << "Memória cheia";
        abort();
    }
    //if para conferir se a memória está cheia ou não;

    q->Func = Funcionario;
    q->NextNode = p->NextNode;
    q->PrevNode = p;
    p->NextNode = q;
    q->NextNode->PrevNode = q;

    Count++;
}

void List::Calcular(){
    //pré-condição: A lista já tenha sido criada e já exista funcionários cadastrados no sistema;
    //pós-condição: Chama todas as funções necessárias para fazer o cálculo do salário líquido do 
    //funcionário;

    if(Count == 0){
        cout << "ERRO!" << endl;
        cout << "Ainda não foi cadastrado um funcionário." << endl;
        cout << "Use a opção (1) para cadastrar um funcionário." << endl << endl;
    }//if para caso a lista esteja vazia;
    else{
    
        ListPointer q;

        q = Head->NextNode;
        while(q != Head){
            float aux=q->Func.Salario_Brt;

            q->Func.Salario_Brt = q->Func.Salario_Brt + q->Func.Proventos;
            q->Func.Salario_Brt = q->Func.Salario_Brt - q->Func.Faltas;
            Calcular_FGTS(q);
            Calcular_INSS(q);
            Calcular_IRRF(q);
            q->Func.Salario_Liq = q->Func.Salario_Liq + q->Func.Bonificacao;
            q->Func.Salario_Liq = q->Func.Salario_Liq - q->Func.Adiantamento;
            q->Func.Salario_Liq = q->Func.Salario_Liq - q->Func.Alimentacao;
            q->Func.Salario_Liq = q->Func.Salario_Liq - q->Func.Transporte;
            q->Func.Salario_Liq = q->Func.Salario_Liq - q->Func.Saude;
            q->Func.Salario_Liq = round(q->Func.Salario_Liq * 100.0f)/100.0f;
            q->Func.Fgts = round(q->Func.Fgts * 100.0f)/100.0f;
            q->Func.Inss = round(q->Func.Inss * 100.0f)/100.0f;
            q->Func.Irrf = round(q->Func.Irrf * 100.0f)/100.0f;
            q->Func.Salario_Brt = aux;
            q = q->NextNode;
        }
        //while para percorrer toda a lista e calcular o salário de todos os funcionários cadastrados;

        ListarFuncionarios();
    }

}

void List::AdicionarFunc(Dados Funcionario){
    //pré-condição: Lista já tenha sido criada;
    //pós-condição: Cadastra os dados de um funcionário no sistema;

    ListPointer q, p;
    int i=0;
    
    while(Funcionario.Nome[i] != '\0'){
        Funcionario.Nome[i] = toupper(Funcionario.Nome[i]);
        i++;
    }
    //while para deixar o nome do funcionário apenas com letras maiúsculas;
    
    p = Head;
    q = Head->NextNode;
    Head->Func = Funcionario;
        
    while(q->Func.Salario_Brt < Funcionario.Salario_Brt){
        p = q;
        q = q->NextNode;
    }
    //while para percorrer a lista;

    q = new ListNode;

    if(q==NULL){
        cout << "Memória cheia";
    }//if para caso a memória esteja cheia;
    else{

        q->Func = Funcionario;
        q->NextNode = p->NextNode;
        q->PrevNode = p;
        p->NextNode = q;
        q->NextNode->PrevNode = q;

        Count++;
    }
    cout << endl;

}


void List::Delete(){
    //pré-condição: A lista já tenha sido criada e não está vazia;
    //pós-condição: Deleta um cadastro da lista;
    
    if(Count==0){
        cout << endl << "ERRO!" << endl;
        cout << "Ainda não foi cadastrado um funcionário." << endl;
        cout << "Use a opção (1) para cadastrar um funcionário." << endl << endl;

    }//if para caso a lista esteja vazia;
    else{

        char NomeFuncionario[101];

        cout << endl << "Digite o Nome do funcionário: ";
        setbuf(stdin, NULL);
        cin.getline(NomeFuncionario, 101);

        int i=0;
        while(NomeFuncionario[i] != '\0'){
            NomeFuncionario[i] = toupper(NomeFuncionario[i]);
            i++;
        }
        //while para deixar o nome do funcionário com todas as letras maiúsculas;
    
        ListPointer p, q;
        p = Head;
        q = Head->NextNode;
        strcpy(Head->Func.Nome, NomeFuncionario);

        while(strcmp(q->Func.Nome, NomeFuncionario)!=0){
            p = q;
            q = q->NextNode;
        }
        //While para procurar o nome do funcionário;

        if(strcmp(q->Func.Nome, NomeFuncionario)!=0 || q == Head){
            cout << endl << "ERRO!" << endl;
            cout << "Cadastro não encontrado." << endl << endl;
            
        }//if para saber se o nome está na lista;
        else{

            p->NextNode = q->NextNode;
            q->NextNode->PrevNode = p;

            delete q;
            Count--;

            cout << endl << "Cadastro deletado com sucesso!" << endl << endl;
        }
        //else para deletar o funcionário"
    }

}


void List::Calcular_FGTS(ListPointer &q){
    //pré-condição: Lista já tenha sido criada e não está vazia;
    //pós-condição: Calcula o FGTS;

    q->Func.Fgts = q->Func.Salario_Brt * (8.0/100);
    
}   

void List::Calcular_INSS(ListPointer &q){
    //pré-condição: Lista já tenha sido criada e não está vazia;
    //pós-condição: Calcula o INSS;

    float aux;

    //Os ifs procuram qual desconto vai ser efetuado de acordo com o salário; 
    if(q->Func.Salario_Brt <= InssFaixa_1){
        q->Func.Inss = (q->Func.Salario_Brt * (7.5/100));
        q->Func.Salario_Liq = q->Func.Salario_Brt - q->Func.Inss;
        return;
    }

    aux = InssFaixa_1 * (7.5/100);

    if(q->Func.Salario_Brt > InssFaixa_1 && q->Func.Salario_Brt <= InssFaixa_2){
        q->Func.Inss = ((q->Func.Salario_Brt - InssFaixa_1) * (9.0/100)) + aux;
        q->Func.Salario_Liq = q->Func.Salario_Brt - q->Func.Inss;
        return;
    }

    aux += (InssFaixa_2 - InssFaixa_1) * (9.0/100);

    if(q->Func.Salario_Brt > InssFaixa_2 && q->Func.Salario_Brt <= InssFaixa_3){
        q->Func.Inss = ((q->Func.Salario_Brt - InssFaixa_2) * (12.0/100)) + aux;
        q->Func.Salario_Liq = q->Func.Salario_Brt - q->Func.Inss;
        return;
    }

    aux += (InssFaixa_3 - InssFaixa_2) * (12.0/100);

    if(q->Func.Salario_Brt > InssFaixa_3 && q->Func.Salario_Brt <= InssFaixa_4){
        q->Func.Inss = ((q->Func.Salario_Brt - InssFaixa_3) * (14.0/100)) + aux;
        q->Func.Salario_Liq = q->Func.Salario_Brt - q->Func.Inss;
        return;
    }

    aux += (InssFaixa_4 - InssFaixa_3) * (14.0/100);

    if(q->Func.Salario_Brt > InssFaixa_4){
        q->Func.Inss = aux;
        q->Func.Salario_Liq = q->Func.Salario_Brt - q->Func.Inss;
        return;
    }

}

void List::Calcular_IRRF(ListPointer &q){
    //pré-condição: Lista já tenha sido criada e não está vazia;
    //pós-condição: Calcula o IRRF;

    float aux = IrrfDependente * q->Func.Dependente;
    float Salario_Dependente = (q->Func.Salario_Liq - aux);

    //Os ifs procuram qual desconto vai ser efetuado de acordo com o salário;
    if(Salario_Dependente <= IrrfFaixa_1){
        q->Func.Irrf = 0;
        return;
    }

    if(Salario_Dependente > IrrfFaixa_1 && Salario_Dependente <= IrrfFaixa_2){
        q->Func.Irrf = ((Salario_Dependente * (7.50/100)) - IrrfFaixa_1_Deducao);
        if(q->Func.Irrf < 10.00){
            q->Func.Irrf = 0;
        }else
            q->Func.Salario_Liq = q->Func.Salario_Liq - q->Func.Irrf;

        return;
    }

    if(Salario_Dependente > IrrfFaixa_2 && Salario_Dependente <= IrrfFaixa_3){
        q->Func.Irrf = ((Salario_Dependente * (15.0/100)) - IrrfFaixa_2_Deducao);
        if(q->Func.Irrf < 10.00){
            q->Func.Irrf = 0;
        }else
            q->Func.Salario_Liq = q->Func.Salario_Liq - q->Func.Irrf;
        return;
    }

    if(Salario_Dependente > IrrfFaixa_3 && Salario_Dependente <= IrrfFaixa_4){
        q->Func.Irrf = ((Salario_Dependente * (22.50/100)) - IrrfFaixa_3_Deducao);
        if(q->Func.Irrf < 10.00){
            q->Func.Irrf = 0;
        }else
            q->Func.Salario_Liq = q->Func.Salario_Liq - q->Func.Irrf;
        return;
    }

    if(Salario_Dependente > IrrfFaixa_4){
        q->Func.Irrf = ((Salario_Dependente * (27.50/100)) - IrrfFaixa_4_Deducao);
        if(q->Func.Irrf < 10.00){
            q->Func.Irrf = 0;
        }else
            q->Func.Salario_Liq = q->Func.Salario_Liq - q->Func.Irrf;
        return;
    }


}

void List::ListarFuncionarios(){
    //pré-condição: Lista já tenha sido criada e não está vazia;
    //pós-condição: Mostra todos os funcionários e sus informações;

    ListPointer p;

    p = Head->NextNode;

    if(Empty()){
        cout << "ERRO!" << endl;
        cout << "Ainda não foi cadastrado um funcionário." << endl;
        cout << "Use a opção (1) para cadastrar um funcionário." << endl << endl;
    }//if usado para saber se a lista está vazia;
    else{

        while(p!=Head){
            cout << "Nome: " << p->Func.Nome << endl;
            cout << "Cpf: " << p->Func.Cpf << endl;
            cout << "Salario líquido: " << p->Func.Salario_Liq << endl;
            cout << "Salário bruto: " << p->Func.Salario_Brt << endl;
            cout << "FGTS: " << p->Func.Fgts << endl;
            cout << "INSS: " << p->Func.Inss << endl;
            cout << "IRRF: " << p->Func.Irrf << endl << endl;
            p = p->NextNode;

        }
        //while para imprimir as informações de todos os funcionários;
    }


}

void List::Search(){
    //pré-condição: Lista já tenha sido criada e não está vazia;
    //pós-condição: Busca um fucionário da lista;

    if(Count==0){
        cout << endl << "ERRO!" << endl;
        cout << "Ainda não foi cadastrado um funcionário." << endl;
        cout << "Use a opção (1) para cadastrar um funcionário." << endl << endl;
        
    }//if para caso a lista esteja vazia;
    else{
        char NomeFuncionario[101];
        cout << endl << "Digite o Nome do funcionário: ";
        setbuf(stdin, NULL);
        cin.getline(NomeFuncionario, 101);
        int i=0;
        while(NomeFuncionario[i] != '\0'){
            NomeFuncionario[i] = toupper(NomeFuncionario[i]);
            i++;
        }
        //while para colocar as letras do nome do funcionário maiúsculas;

        ListPointer q;

        q = Head->NextNode;
        strcpy(Head->Func.Nome, NomeFuncionario);

        while(strcmp(q->Func.Nome, NomeFuncionario)!=0){
            q = q->NextNode;
        }
        //while para procurar o funcionário na lista;

        if(strcmp(q->Func.Nome, NomeFuncionario)!=0 || q == Head){
            cout << endl << "ERRO!" << endl;
            cout << "Cadastro não encontrado." << endl << endl;
            
        }//if para caso o nome não esteja na lista;
        else{

            cout << "Nome: " << q->Func.Nome << endl;
            cout << "Cpf: " << q->Func.Cpf << endl;
            cout << "Salario líquido: " << q->Func.Salario_Liq << endl;
            cout << "Salário bruto: " << q->Func.Salario_Brt << endl;
            cout << "FGTS: " << q->Func.Fgts << endl;
            cout << "INSS: " << q->Func.Inss << endl;
            cout << "IRRF: " << q->Func.Irrf << endl << endl;

        }//Mostrar o nome buscado na tela;
    }

}

void List::Editar(){
    //pré-condição: Lista já tenha sido criada e não esteja vazia;
    //pós-condição: Edita os dados de um funcionário;

    if(Count==0){
        cout << endl << "ERRO!" << endl;
        cout << "Ainda não foi cadastrado um funcionário." << endl;
        cout << "Use a opção (1) para cadastrar um funcionário." << endl << endl;        
    }//if para caso a lista esteja vazia;
    else{

        char NomeFuncionario[101];

        cout << endl << "Digite o Nome do funcionário: ";
        setbuf(stdin, NULL);
        cin.getline(NomeFuncionario, 101);
        
        int i=0;
        while(NomeFuncionario[i] != '\0'){
            NomeFuncionario[i] = toupper(NomeFuncionario[i]);
            i++;
        }
        //while para colcar o nome do funcionário em maiúsculo;
    
        ListPointer q;

        q = Head->NextNode;
        strcpy(Head->Func.Nome, NomeFuncionario);

        while(strcmp(q->Func.Nome, NomeFuncionario)!=0){
            q = q->NextNode;
        }   
        //while para procurar o nome do funcionário;

        if(strcmp(q->Func.Nome, NomeFuncionario)!=0 || q == Head){
            cout << endl << "ERRO!" << endl;
            cout << "Cadastro não encontrado." << endl << endl;
            
        }//if para caso o funcionário não esteja na lista;
        else{
            int op=0;
            
            cout << endl << "Nome: " << q->Func.Nome << endl;
            cout << "Cpf: " << q->Func.Cpf << endl;
            cout << "Salário bruto: " << q->Func.Salario_Brt << endl;
            cout << "Dependentes: " << q->Func.Dependente << endl << endl;

            do{
                cout << "O que deseja editar?" << endl;
                cout << "1 - Nome;" << endl;
                cout << "2 - CPF;" << endl;
                cout << "3 - Salário;" << endl;
                cout << "4 - Quantidade de dependentes;" << endl;
                cin >> op;
            }while(op!=1 && op!=2 && op!=3 && op!=4);
            //do while para caso coloque uma opção inválida;

            int i=0;
            
            switch(op){
            
                case 1:
                    cout << "Digite o novo nome: " << endl;
                    cin >> q->Func.Nome;

                    while(q->Func.Nome[i] != '\0'){
                        q->Func.Nome[i] = toupper(q->Func.Nome[i]);
                        i++;
                    }
                    break;
                
                case 2:
                    cout << "Digite o novo CPF: " << endl;
                    cin >> q->Func.Cpf;
                    break;
                
                case 3:
                    cout << "Digite o novo Salário: " << endl;
                    cin >> q->Func.Salario_Brt;
                    break;

                case 4:
                    cout << "Digite a quantidade de dependentes: " << endl;
                    cin >> q->Func.Dependente;
                    break;
                
                default:
                    break;
            }
            //switch para fazer o comando escolhido;

        }
    }
}

void List::Falta_Adiantamento(){
    //pré-condição: Lista já tenha sido criada e não está vazia;
    //pós-condição: Colocar descontos adicionais caso possua;
    if(Count==0){
        cout << endl << "ERRO!" << endl;
        cout << "Ainda não foi cadastrado um funcionário." << endl;
        cout << "Use a opção (1) para cadastrar um funcionário." << endl << endl;
        
    }else{

        char NomeFuncionario[101];

        cout << endl << "Digite o Nome do funcionário: ";
        setbuf(stdin, NULL);
        cin.getline(NomeFuncionario, 101);

        int i=0;
        while(NomeFuncionario[i] != '\0'){
            NomeFuncionario[i] = toupper(NomeFuncionario[i]);
            i++;
        }
        //while para deixar o nome do funcionário maiúsculo;
    
        ListPointer q;

        q = Head->NextNode;
        strcpy(Head->Func.Nome, NomeFuncionario);

        while(strcmp(q->Func.Nome, NomeFuncionario)!=0){
            q = q->NextNode;
        }
        //while para procurar o nome do funcionário;

        if(strcmp(q->Func.Nome, NomeFuncionario)!=0 || q == Head){
            cout << endl << "ERRO!" << endl;
            cout << "Cadastro não encontrado." << endl << endl;
            
        }//if para caso o nome seja inexistente;
        else{
            cout << "Digite os valores que serão descontados/adicionados:" << endl;
            cout << "Falta: ";
            cin >> q->Func.Faltas;
            cout << "Adiantamento: ";
            cin >> q->Func.Adiantamento;
            cout << "Provento: ";
            cin >> q->Func.Proventos;
            cout << "Bonificação: ";
            cin >> q->Func.Bonificacao;
            cout << "Vale-Transporte: ";
            cin >> q->Func.Transporte;
            cout << "Vale-Alimentação: ";
            cin >> q->Func.Alimentacao;
            cout << "Plano de Saúde: ";
            cin >> q->Func.Saude;

        }
    }
}