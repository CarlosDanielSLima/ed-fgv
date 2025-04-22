#include <iostream>
#include <cstring>
#include "WaitingQueue.h"
using namespace std;

namespace WaitingQueueTAD{

    WaitingQueue* createQueue(){
        WaitingQueue* queue = new WaitingQueue{};
        queue->generalCount = 0;
        queue->elderlyCount = 0;
        queue->elderlyPossibles = 0;
        queue->deficitElderly = 2;
        // Create empty arrays of pointers to heads and tails of priority queues
        queue->heads = new QueueNode*[2];
        queue->tails= new QueueNode*[2];
        queue->heads[0] = nullptr;
        queue->heads[1] = nullptr;
        queue->tails[0] = nullptr;
        queue->tails[1] = nullptr;
        return queue;
    }

    void enqueue(WaitingQueue* queue, Client client){
        if (queue == nullptr) { return; }
        if ((queue->heads == nullptr) || (queue->tails == nullptr)) { return; }
        if ((client.priority != 0) && (client.priority != 1)) { return; }

        QueueNode* newNode = new QueueNode{};
        newNode->client = client;
        newNode->next = nullptr;

        // Define his priority's queue
        QueueNode* head = queue->heads[client.priority];
        QueueNode* tail = queue->tails[client.priority];

        // Insert in the tail of queue
        if (!head) {
            queue->heads[client.priority] = newNode;
            newNode->previous = nullptr;
        } else if (tail) {
            tail->next = newNode;
            newNode->previous = tail;
            
        }
        queue->tails[client.priority] = newNode;

        if (client.priority){
            // Increment elderlyPossibles if possible
            if ((queue->elderlyPossibles < 2) && queue->deficitElderly){
                queue->elderlyPossibles++;
                queue->deficitElderly--;
            }
            queue->elderlyCount++;
        } else {
            queue->generalCount++;
        }
        
    }


    int peek(const WaitingQueue* queue, Client* returnClient){
        if (queue == nullptr) { return 0; }
        if (queue->heads == nullptr) { return 0; }
        if ((queue->elderlyCount + queue->generalCount) < 1) { return 0;}

        // Call elderly if is possible call a elderly or there are't generals
        int priority = ((queue->elderlyPossibles > 0) || (queue->generalCount == 0));

        // Save the head from priority's queue
        if (!queue->heads[priority]) {
            return 0; 
        } else {
            *returnClient = queue->heads[priority]->client;
            return 1;
        }
    }

    int dequeue(WaitingQueue* queue, Client* returnClient){
        if (queue == nullptr) { return 0; }
        if (queue->heads == nullptr) { return 0; }
        if ((queue->elderlyCount + queue->generalCount) < 1) { return 0; }
        // Get client to be removed
        if (!peek(queue, returnClient)){ return 0; }
        int priority = returnClient->priority;
        QueueNode* removed = queue->heads[priority];
        QueueNode* tail = queue->tails[priority];
        
        // Update Counts and elderlyPossibles
        if (priority){
            // Decrement elderlyPossibles until 0
            queue->elderlyPossibles -= (queue->elderlyPossibles > 0);
            queue->elderlyCount--;
        } else {
            queue->generalCount--;
            updateDefict(queue);
        }
    
        // Remove he from the queue
        if (!strcmp(tail->client.name, returnClient->name)){ // Removed is last client from his queue
            queue->tails[priority] = nullptr;
            queue->heads[priority] = nullptr;
        } else {
            queue->heads[priority] = removed->next;
            queue->heads[priority]->previous = nullptr;
        }

        delete removed;
        return 1;
    }


    void updateDefict(WaitingQueue* queue){
        // Define deficit of elderly to complete a sequence of 2 elderly and restart elderlyPossibles
        if (queue->elderlyCount >= 2){
            queue->elderlyPossibles = 2;
            queue->deficitElderly = 0;
        } else {
            queue->elderlyPossibles = queue->elderlyCount;
            queue->deficitElderly = 2 - queue->elderlyCount;
        }
    }

    int removeClient(WaitingQueue* queue, char* name){
        if (queue == nullptr) { return 0; }
        if ((queue->heads == nullptr) || (queue->tails == nullptr)) { return 0; }
        if (name == nullptr) { return 0; }
        
        // Linear search in two queues to find client with name
        QueueNode* current;
        for (int priority = 0; priority < 2; priority++) {
            current = queue->heads[priority];
            while (current) {
                // Remove client from their queue
                if (!strcmp(current->client.name, name)){
                    if (current->previous) {
                        current->previous->next = current->next;
                    }
                    if (current->next) {
                        current->next->previous = current->previous;
                    }
                    break;
                }
                current = current->next;
            }
            if (current != nullptr) { break; }
        }

        if (current) {
            int priority = current->client.priority;
            if (priority){
                queue->elderlyCount--;
                // If one elderly leaves and there are not enough for the proportion of the queue, the deficit increases and elderlyPossibles decreases
                if (queue->elderlyCount < queue->elderlyPossibles) {
                    queue->elderlyPossibles -= (queue->elderlyPossibles > 0);
                    queue->deficitElderly += (queue->deficitElderly < 2);
                }
                
            } else {
                queue->generalCount--;
            }

            // Check if removed is head or tail
            if (current == queue->heads[priority]){
                queue->heads[priority] = current->next;
            }
            if (current == queue->tails[priority]){
                queue->tails[priority] = current->previous;
            }
            delete current;
            return 1;
        }
        return 0;
    }


    Client* getQueueOrder(const WaitingQueue* queue, int* numClients){
        if (queue == nullptr) { return nullptr; }
        if (numClients == nullptr) { return nullptr; }
        // Copy queue
        *numClients = queue->elderlyCount + queue->generalCount;
        if (*numClients == 0) { return nullptr; }
        WaitingQueue* queueCopy = createQueue();
        queueCopy->deficitElderly = queue->deficitElderly;
        queueCopy->elderlyCount = queue->elderlyCount;
        queueCopy->elderlyPossibles = queue->elderlyPossibles;
        queueCopy->generalCount = queue->generalCount;
        queueCopy->heads[0] = queue->heads[0];
        queueCopy->heads[1] = queue->heads[1];
        queueCopy->tails[0] = queue->tails[0];
        queueCopy->tails[1] = queue->tails[1];
        Client* queueOrder = new Client[*numClients];

        // Peek next client in order, updating heads from queue copy
        for (int each_client = 0, priority = 1; each_client < *numClients; each_client++) {
            peek(queueCopy, &queueOrder[each_client]);
            priority = queueOrder[each_client].priority;
            // Update Counts and elderlyPossibles
            if (priority){
                queueCopy->elderlyPossibles -= (queue->elderlyPossibles > 0);
                queueCopy->elderlyCount--;
            } else {
                queueCopy->generalCount--;
                // Update defict and elderlyPossibles
                updateDefict(queueCopy);
            }

            QueueNode* head = queueCopy->heads[priority];
            if (head->next) {
                queueCopy->heads[priority] = head->next;
            } else {
                queueCopy->heads[priority] = nullptr;
            }
        }
        deleteQueue(queueCopy);
        return queueOrder;
    }

    void deleteQueue(WaitingQueue* queue) {
        if (queue == nullptr) { return; }
        if ((queue->heads == nullptr) || (queue->tails == nullptr)) { return; }

        // Delete all queuenodes
        QueueNode* current;
        for (int priority = 0; priority < 2; priority++) {
            current = queue->heads[priority];
            if (current == nullptr) { continue; }
            while (current->next) {
                current = current->next;
                delete current->previous;
            }
            delete current;
        }
        
        delete queue;
    }

}