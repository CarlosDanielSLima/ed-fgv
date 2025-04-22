#include <iostream>
#include <cstring>
#include "WaitingQueue.h"

using namespace WaitingQueueTAD;
using std::cin, std::cout, std::endl;

int main(){
    /*
        Testes:
        Iinicalizacao:
            - Checar se a variavel existe e
            - Checar se os arrays de heads e tails existem
            - Checar se os tamanhos das filas estao zerados e se o deficit de idosos eh 2

        Insercao:
            - Checar se o ultimo adicionado esta no final da sua fila
            - Checar se o os tamanhos das filas, a quantidade de elderlyPossibles e o deficit de idosos foram atualizados corretamente

        Peek:
            - Checar se ela retora o idoso1 da fila de exemplo
            - Checar se, numa fila vazia, ele retorna 0 e salva um nullptr como proximo cliente (nao ha um proximo)
            - Checar se ela ignora a fila de idosos quando ela esta vazia
            - Checar se ela ignora um idoso quando 2 ja foram atendidos
            - Checar se ela ignora a fila de geral quando ela esta vazia
        
        Dequeue:
            - Checar se o proximo da fila apos o dequeue eh o que vem depois do atual
        
        Remove:
            - Checar se o removido nao esta mais na fila
            - Checar se remover um idoso altera o deficit de idosos e o elderlyPossibles

        QueueOrder:
            - Checar se a ordem esta certa
        
        
    */

    cout << "------------------------------------ Testes da inicializacao ------------------------------------" << endl;
    WaitingQueue* queue = createQueue();
    cout << "Endereco da fila: " << queue << endl << endl;
    if (!queue) {
        cout << "Fila nao foi inicializada.";
        return 0;
    }

    cout << "Enderecos das heads (valid ptr):  | " << queue->heads << " | " << &queue->heads[1] << endl;
    if (queue->heads) {
        cout << "Valores das heads (nullptr ou 0): |       " << queue->heads[0]  << "       |       " << queue->heads[1] << endl << endl;
    } else {
        cout << "Array de tails ou de heads não foi inicializado corretamente." << endl;
        return 0;
    }

    cout << "Enderecos das tails (valid ptr):  | " << queue->tails << " | " << &queue->tails[1] << endl;
    if (queue->tails) {
        cout << "Valores das tails (nullptr ou 0): |       " << queue->tails[0] << "       |       " << queue->tails[1] << endl << endl;
    } else {
        cout << "Array de tails ou de heads não foi inicializado corretamente." << endl;
        return 0;
    }

    cout << "Tamanhos e deficit: " << endl;
    cout << "Tamanho da fila de nao idosos (deve ser 0):   " << queue->generalCount << endl;
    cout << "Tamanho da fila de idosos (deve ser 0):       " << queue->elderlyCount << endl;
    cout << "Idosos possiveis e deficit de idosos (0 e 2): " << queue->elderlyPossibles << " e " << queue->deficitElderly << endl;
    if (queue->elderlyCount || queue->elderlyCount || queue->elderlyPossibles || (queue->deficitElderly != 2)) {
        cout << "Tamanhos ou deficit inicializados incorretamente" << endl;
        return 0;
    }


    cout << endl << endl << "-------------------------------------- Testes da insercao ---------------------------------------" << endl;
    enqueue(queue, Client{"idoso1", 1});
    enqueue(queue, Client{"idoso2", 1});
    enqueue(queue, Client{"idoso3", 1});

    if (strcmp(queue->tails[1]->client.name, "idoso3")) {
        cout << "idoso3 nao foi adicionado ao fim da fila de idosos. (Erro)" << endl;
        return 0;
    }
    cout << "idoso3 foi corretamente adicionado no fim da fila de idosos." << endl;
    enqueue(queue, Client{"geral1", 0});
    if (strcmp(queue->tails[0]->client.name, "geral1")) {
        cout << "geral1 nao foi adicionado ao fim da fila de gerais. (Erro)" << endl;
        return 0;
    }
    cout << "geral1 foi corretamente adicionado no fim da fila de gerais." << endl << endl;

    cout << "Tamanhos e difict supostamente atualizados: " << endl;
    cout << "Tamanho da fila de  nao idosos (1):             " << queue->generalCount << endl;
    cout << "Tamanho da fila de idosos (3):                  " << queue->elderlyCount << endl;
    cout << "Quantidade de idosos priorizados possiveis (2): " << queue->elderlyPossibles << endl;
    cout << "Deficit de idosos priorizados possiveis (0):    " << queue->deficitElderly << endl;

    if ((queue->elderlyCount != 3) || (queue->generalCount != 1) || (queue->elderlyPossibles != 2) || (queue->deficitElderly != 0)) {
        cout << "Atualizacao incorreta do tamanho das filas ou das quantidades de idosos possives ou deficit de idosos." << endl;
        return 0;
    }
    cout << "Atualizacao correta de tamanhos e deficit." << endl << endl;
    for (int priority = 0; priority < 2; priority++) {
        cout << "Fila de priority: " << priority << ":   |";
        QueueNode* current = queue->heads[priority];
        while (current != nullptr){
            cout << current->client.name << " | ";
            current = current->next;
        }
        cout << endl;
    }


    cout << endl << endl << "---------------------------------------- Testes da peek -----------------------------------------" << endl;
    WaitingQueue* peekTestQueue = createQueue();
    Client peekTestClient;

    cout << "Peek deve retornar o primeiro da fila: "<< endl;
    int peekTestReturn = peek(queue, &peekTestClient);
    if (peekTestReturn) {
        if (strcmp(peekTestClient.name, queue->heads[1]->client.name)){
            cout << "Peek encontrou um cliente que nao eh o proximo. (Erro)" << endl;
            return 0;
        }
        cout << "Peek encontrou o proximo cliente a ser atendido (idoso1)." << endl;
        cout << "Nome: " << peekTestClient.name << " --- Prioridade: " << peekTestClient.priority << endl;
    } else {
        cout << "Peek nao encontrou nada numa lista nao vazia. (Erro)" << endl;
        return 0;
    }

    cout << endl << "Peek nao deve encotrar nada numa fila vazia";
    peekTestReturn = peek(peekTestQueue, &peekTestClient);
    if (peekTestReturn) {
        cout << "Peek encontrou o proximo numa lista vazia (Erro). ";
        return 0;
    } else {
        cout << "Peek nao encontra nada numa lista vazia. (Correto)" << endl;
    }

    cout << endl;
    cout << "Peek deve ignorar a fila de idosos quando ela estiver vazia e a de gerais nao: "<< endl;
    enqueue(peekTestQueue, Client{"geral1", 0});
    peekTestReturn = peek(peekTestQueue, &peekTestClient);
    if (peekTestReturn) {
        if (strcmp(peekTestClient.name, peekTestQueue->heads[0]->client.name)){
            cout << "Peek encontrou um cliente que nao eh o proximo. (Erro)" << endl;
            return 0;
        }
        cout << "Peek encontrou o proximo cliente a ser atendido (geral1)." << endl;
        cout << "Nome: " << peekTestClient.name << " --- Prioridade: " << peekTestClient.priority << endl;
    } else {
        cout << "Peek nao encontrou nada numa lista nao vazia. (Erro)" << endl;
        return 0;
    }

    cout << endl;
    cout << "Peek deve ignorar a fila de idosos quando 2 idosos ja tiverem sido atendidos: "<< endl;
    enqueue(peekTestQueue, Client{"idoso1", 1});
    peekTestQueue->elderlyPossibles = 0;
    peekTestQueue->deficitElderly= 0;

    peekTestReturn = peek(peekTestQueue, &peekTestClient);
    if (peekTestReturn) {
        if (strcmp(peekTestClient.name, peekTestQueue->heads[0]->client.name)){
            cout << "Peek encontrou um cliente que nao eh o proximo. (Erro)" << endl;
            return 0;
        }
        cout << "Peek encontrou o proximo cliente a ser atendido (geral1)." << endl;
        cout << "Nome: " << peekTestClient.name << " --- Prioridade: " << peekTestClient.priority << endl;
    } else {
        cout << "Peek nao encontrou nada numa lista nao vazia. (Erro)" << endl;
        return 0;
    }

    cout << endl;
    cout << "Peek deve ignorar a fila de gerais quando ela esta vazia, mesmo quando 2 idosos ja tiverem sido atendidos: "<< endl;
    char clientName[7] = "geral1";
    removeClient(peekTestQueue, clientName);
    peekTestReturn = peek(peekTestQueue, &peekTestClient);
    if (peekTestReturn) {
        if (strcmp(peekTestClient.name, peekTestQueue->heads[1]->client.name)){
            cout << "Peek encontrou um cliente que nao eh o proximo. (Erro)" << endl;
            return 0;
        }
        cout << "Peek encontrou o proximo cliente a ser atendido (idoso1)." << endl;
        cout << "Nome: " << peekTestClient.name << " --- Prioridade: " << peekTestClient.priority << endl;
    } else {
        cout << "Peek nao encontrou nada numa lista nao vazia. (Erro)" << endl;
        return 0;
    }

    deleteQueue(peekTestQueue);


    cout << endl << endl << "--------------------------------------- Testes da dequeue ---------------------------------------" << endl;
    cout << "O proximo da fila deve ser o seguinte ao atendido:" << endl;
    Client dequeueTestClient, dequeuedNext;
    peek(queue, &dequeueTestClient);
    QueueNode* removed = queue->heads[dequeueTestClient.priority];
    dequeuedNext = removed->next->client;

    int dequeueTestReturn = dequeue(queue, &dequeueTestClient);
    if (!dequeueTestReturn) {
        cout << "Nao conseguiu remover. (Erro)" << endl;
        return 0;
    }
    cout << "Proximo do atendido:                           " << dequeuedNext.name << endl;
    cout << "Novo proximo da fila (deve ser o mesmo acima): " << queue->heads[dequeueTestClient.priority]->client.name << endl;

    cout << endl << endl << "--------------------------------------- Testes da remove ----------------------------------------" << endl;

    dequeue(queue, &dequeueTestClient);
    dequeue(queue, &dequeueTestClient);
    enqueue(queue, Client{"idoso4", 1});
    enqueue(queue, Client{"geral1", 0});
    for (int priority = 0; priority < 2; priority++) {
        cout << "Fila de priority: " << priority << ":   |";
        QueueNode* current = queue->heads[priority];
        while (current != nullptr){
            cout << current->client.name << " | ";
            current = current->next;
        }
        cout << endl;
    }
    cout << "Quantidade de idosos priorizados possiveis (2): " << queue->elderlyPossibles << endl;
    cout << "Deficit de idosos priorizados possiveis (0):    " << queue->deficitElderly << endl << endl;

    cout << "Caso o idoso4 desista, a quantidade de idosos que ao chegarem podem pular (deficit) aumenta, pois nao tem idosos suficientes para que dois possam pular a fila. Enquanto a quanditidade de elderlyPossibles deve diminuir, pois eh o min(elderlyCount, 2) que sera min(1, 2) = 1." << endl;
    char clientNameRemoved[7] = "idoso4";
    int removeTestReturn = removeClient(queue, clientNameRemoved);
    if (!removeTestReturn) {
        cout << "Nao conseguiu remover. (Erro)" << endl;
        return 0;
    }
    for (int priority = 0; priority < 2; priority++) {
        cout << "Fila de priority: " << priority << ":   |";
        QueueNode* current = queue->heads[priority];
        while (current != nullptr){
            cout << current->client.name << " | ";
            current = current->next;
        }
        cout << endl;
    }
    cout << "Quantidade de idosos priorizados possiveis (1): " << queue->elderlyPossibles << endl;
    cout << "Deficit de idosos priorizados possiveis (1):    " << queue->deficitElderly << endl << endl;

    enqueue(queue, Client{"idoso5", 1});
    enqueue(queue, Client{"idoso6", 1});
    cout << "Ao ter 3 ou mais idosos na fila, caso o idoso6 desista, nem a quantidade de idosos que ao chegarem podem pular (deficit) a fila aumenta, nem quanditidade de elderlyPossibles aumenta, pois ainda tem idosos o suciente para manter a proporcao." << endl;
    char clientNameRemoved2[7] = "idoso6";
   removeTestReturn = removeClient(queue, clientNameRemoved2);
    for (int priority = 0; priority < 2; priority++) {
        cout << "Fila de priority: " << priority << ":   |";
        QueueNode* current = queue->heads[priority];
        while (current != nullptr){
            cout << current->client.name << " | ";
            current = current->next;
        }
        cout << endl;
    }
    if (!removeTestReturn) {
        cout << "Nao conseguiu remover. (Erro)" << endl;
        return 0;
    }
    cout << "Quantidade de idosos priorizados possiveis (2): " << queue->elderlyPossibles << endl;
    cout << "Deficit de idosos priorizados possiveis (0):    " << queue->deficitElderly << endl << endl;

    
    cout << endl << endl << "------------------------------------- Testes da QueueOrder --------------------------------------" << endl;
    for (int priority = 0; priority < 2; priority++) {
        cout << "Fila de priority: " << priority << ":   | ";
        QueueNode* current = queue->heads[priority];
        while (current != nullptr){
            cout << current->client.name << " | ";
            current = current->next;
        }
        cout << endl;
    }
    cout << "A fila de atendimento deve ser: | idoso3 | idoso5 | geral1 |" << endl;
    int numClients;
    Client* queueOrder = getQueueOrder(queue, &numClients);
    cout << "Queue Order:                   ";
    for (int eachClient = 0; eachClient < numClients; eachClient++) {
        cout << " | " << queueOrder[eachClient].name;
    }
    cout << " |" << endl;

    enqueue(queue, Client{"idoso7", 1});
    enqueue(queue, Client{"idoso8", 1});
    enqueue(queue, Client{"idoso9", 1});
    enqueue(queue, Client{"geral2", 0});
    enqueue(queue, Client{"geral3", 0});

    cout << "A nova fila de atendimento deve ser: | idoso3 | idoso5 | geral1 | idoso7 | idoso8 | geral2 | idoso9 | geral3 |" << endl;
    queueOrder = getQueueOrder(queue, &numClients);
    cout << "Queue Order:                        ";
    for (int eachClient = 0; eachClient < numClients; eachClient++) {
        cout << " | " << queueOrder[eachClient].name;
    }
    cout << " |" << endl;

    deleteQueue(queue);
    return 0;
}