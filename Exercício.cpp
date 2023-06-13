#include<iostream>
#include<fstream>
#include<math.h>
#include"Estagio.h"
using namespace std;

int main(){

    List l;
    Dados Funcio;
    int op=1, sair = 1;

    do{
        
        do{
            if(op != 1 && op != 2 && op != 3 && op != 4 && op != 5 && op != 6 && op != 7 && op != 8){
                cout << endl << "Opção inválida!" << endl << endl;
                cout << "Digite uma opção válida." << endl << endl;
            }else{
                cout << "Escolha uma opção" << endl << endl;

            }
            cout << "1 - Cadastrar um funcionário;" << endl;
            cout << "2 - Adicionar ou remover valores em caso de faltas, adiantamentos, bonificações ou proventos;" << endl;
            cout << "3 - Editar dados de um funcionário;" << endl;
            cout << "4 - Deletar o cadastro de um funcionario;" << endl;
            cout << "5 - Procurar por um funcionário;" << endl;
            cout << "6 - Calcular o salário líquido de todos os funcionários;" << endl;
            cout << "7 - Listar todos os funcionários cadastrados;" << endl;
            cout << "8 - Sair do programa;" << endl;
            cin >> op;
            
        }while(op != 1 && op != 2 && op != 3 && op != 4 && op != 5 && op != 6 && op != 7 && op != 8);
        //do while para caso seja escolhida uma opção errada;

        switch(op){
            case 1:
                cout << endl << "Nome do funcionário: ";
                setbuf(stdin, NULL);
                cin.getline(Funcio.Nome, 101);
                cout << "CPF: ";
                setbuf(stdin, NULL);
                cin.getline(Funcio.Cpf, 12);
                cout << "Salário bruto: ";
                cin >> Funcio.Salario_Brt;
                cout << "Dependentes: ";
                cin >> Funcio.Dependente;
                l.AdicionarFunc(Funcio);
                break;

            case 2:
                l.Falta_Adiantamento();
                break;
            
            case 3:
                l.Editar();
                break;
            
            case 4:
                l.Delete();
                break;
            
            case 5:
                l.Search();
                break;
            

            case 6:
                cout << endl;
                l.Calcular();
                break;
            
            case 7:
                cout << endl;
                l.ListarFuncionarios();
                break;
            
            case 8:
                cout << endl;
                sair = 0;
                break;

            default:
                break;
        }
        //switch para fazer o comando escolhido;
        

    }while(sair != 0);
    //do while para deixar o código em loop;

}