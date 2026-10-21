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
struct Fila
{
    Node *frente = nullptr;
    Node *tras = nullptr;

    void enqueue(int id, int urgencia, string nome)
    {
        Node *novo = new Node(id, urgencia, nome);

        if (!tras)
            frente = tras = novo;
        else
        {
            tras->prox = novo;
            tras = novo;
        }
    }

    Node *dequeue()
    {
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
