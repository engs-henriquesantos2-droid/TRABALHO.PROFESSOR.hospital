// atividade hospital usando fila, pilha e lista encadeada
#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int valor;
    int urgencia;
    string nome;
    Node *prox;

    Node(int v, int u = 1, string n = "")
        : valor(v), urgencia(u), nome(n), prox(nullptr) {}
};

// R1 - Fila de pacientes
struct Fila {
    Node *frente = nullptr;
    Node *tras = nullptr;

    void enqueue(int id, int urgencia, string nome)
    {
      Node *novo = new Node(id, urgencia, nome);

     if (!frente){
            frente = tras = novo;
            return;
     }
    

    if (urgencia > frente->urgencia) {
        novo->prox = frente;
        frente = novo;
        return;
    }

    Node *atual = frente;
    while (atual->prox && atual->prox->urgencia >= urgencia) {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;

    if (!novo->prox) {
        tras = novo;
    }

    Node *dequeue() {
        if (!frente)
            return nullptr;

        Node *p = frente;
        frente = frente->prox;

        if (!frente)
            tras = nullptr;

        p->prox = nullptr;
        return p;
    }
};

// R2 - Historico em pilha
struct Pilha {
    Node* topo = nullptr;

    bool isEmpty() {
        return topo == nullptr;
    }

    void push(int id, int urgencia, string nome) {
        Node* novo = new Node(id, urgencia, nome);
        novo->prox = topo;
        topo = novo;
    }

    Node* pop() {
        if (isEmpty()) return nullptr;

        Node* p = topo;
        topo = topo->prox;
        p->prox = nullptr;
        return p;
    }
};

// R3 - Lista de medicos
struct Medicos {
    Node* inicio = nullptr;
    Node* fim = nullptr;

    void adicionar(string nome) {
    Node* novo = new Node(0, 1, nome);

        if (!fim)
            inicio = fim = novo;
        else {
            fim->prox = novo;
            fim = novo;
        }
    }

    Node* chamar() {
        if (!inicio) return nullptr;

        Node* p = inicio;
        inicio = inicio->prox;

        if (!inicio) fim = nullptr;

        p->prox = nullptr;
        return p;
    }

    void retornar(Node* medico) {
        if (!medico) return;

        if (!fim)
            inicio = fim = medico;
        else {
            fim->prox = medico;
            fim = medico;
        }
    }
};

// R4 - Imprimir historico preservando a pilha
void ImprimirHistorico(Pilha& historico) {
    Pilha aux;

    while (!historico.isEmpty()) {
        Node* p = historico.pop();

        cout << "Paciente: " << p->nome
             << " | ID: " << p->valor
             << " | Urgencia: " << p->urgencia << endl;

        aux.push(p->valor, p->urgencia, p->nome);
        delete p;
    }

    while (!aux.isEmpty()) {
        Node* p = aux.pop();
        historico.push(p->valor, p->urgencia, p->nome);
        delete p;
    }
}

int main() {
    Fila fila;
    Pilha historico;
    Medicos medicos;

    // Medicos de plantao
    medicos.adicionar("Dr.Julio");
    medicos.adicionar("Dr.Marcos");

    // Cadastro de pacientes
    fila.enqueue(1, 2, "Ana");
    fila.enqueue(2, 1, "Joao");
    fila.enqueue(3, 3, "Maria");

    // Atendimento
    while (fila.frente && medicos.inicio) {
        Node* paciente = fila.dequeue();
        Node* medico = medicos.chamar();

        cout << paciente->nome
             << " atendido pelo medico "
             << medico->nome << endl;

        // Registra o atendimento
        historico.push(
            paciente->valor,
            paciente->urgencia,
            paciente->nome
        );

        delete paciente;

        // Medico retorna ao final da lista
        medicos.retornar(medico);
    }

    // Relatorio final
    cout << "\n=== HISTORICO ===\n";
    ImprimirHistorico(historico);

    return 0;
}
