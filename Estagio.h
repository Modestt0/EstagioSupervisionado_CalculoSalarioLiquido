using namespace std;

#ifndef ESTAGIO_H
#define ESTAGIO_H

const float InssFaixa_1 = 1212;
const float InssFaixa_2 = 2427.35;
const float InssFaixa_3 = 3641.03;
const float InssFaixa_4 = 7087.22;

const float IrrfDependente = 189.59;
const float IrrfFaixa_1 = 1903.98;
const float IrrfFaixa_2 = 2826.65;
const float IrrfFaixa_3 = 3751.05;
const float IrrfFaixa_4 = 4664.68;
const float IrrfFaixa_1_Deducao = 142.80;
const float IrrfFaixa_2_Deducao = 354.80;
const float IrrfFaixa_3_Deducao = 636.13;
const float IrrfFaixa_4_Deducao = 869.36;
//Variáveis para guardar os valores de descontos

struct Dados{
    char Nome[101];
    char Cpf[12];
    float Salario_Liq = 0;
    float Salario_Brt = 0;
    int Dependente = 0;
    float Fgts = 0;
    float Inss = 0;
    float Irrf = 0;
    float Proventos = 0; 
    float Bonificacao = 0;
    float Faltas = 0; 
    float Adiantamento = 0;
    float Transporte = 0;
    float Alimentacao = 0;
    float Saude = 0;
};
//Struct para salvar os dados de um funcionário

class List{

    public:
        List();
        ~List();
        bool Full();
        bool Empty();
        void AbreArquivo(Dados Funcionario);
        void AdicionarFunc(Dados Funcionario);
        void Calcular();
        void Falta_Adiantamento();
        void ListarFuncionarios();
        void Delete();
        void Search();
        void Editar();

    private:
        struct ListNode{
            Dados Func;
            ListNode *NextNode;
            ListNode *PrevNode;
        };

        typedef ListNode *ListPointer;

        int Count;
        ListPointer Head;
    
        void Calcular_INSS(ListPointer &Funcionario);
        void Calcular_IRRF(ListPointer &Funcionario);
        void Calcular_FGTS(ListPointer &Funcionario);
};

#endif