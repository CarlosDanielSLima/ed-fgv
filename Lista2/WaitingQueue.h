#ifndef WAITINGQUEUE
#define WAITINGQUEUE

namespace WaitingQueueTAD{
    
    struct Client {
        char name[50];
        int priority;  // 0 = Geral; 1 = Idoso
    };
    
    struct QueueNode {
        Client client;
        QueueNode* next;
        QueueNode* previous;
    };
    
    struct WaitingQueue {
        int generalCount;
        int elderlyCount;
        int elderlyPossibles; // Elderly prioritized
        int deficitElderly; // Elderly who can still be prioritized upon arrival
        QueueNode** heads;
        QueueNode** tails;
    };

    /** 
     * @brief Create a empty pair of queue, index 0 to priority 0 and index 1 to priority 1
     * @return Return WaitingQueue created
     */
    WaitingQueue* createQueue();

    /**
     * @brief Insert a new client in the end of his priority's queue
     * @param queue WaitingQueue of clients
     * @param client Client to be insert
     */
    void enqueue(WaitingQueue* queue, Client client);


    /**
     * @brief Find next client without remove
     * @param queue WaitingQueue of clients
     * @param returnClient Pointer to variable that receive next client
     * @return 0 if list is empty, 0 else
     */
    int peek(const WaitingQueue* queue, Client* returnClient);

    /**
     * @brief Update possible elderly and deficitElderly in the queue in the current state
     * @param queue WaitingQueue of clients
     */
    void updateDefict(WaitingQueue* queue);

    /**
     * @brief Remove next client after attend
     * @param queue WaitingQueue of clients
     * @param returnClient Pointer to variable that receive next client
     * @return 0 if list is empty, 0 else
     */
    int dequeue(WaitingQueue* queue, Client* returnClient);


    /**
     * @brief Remove client before quit
     * @param queue WaitingQueue of clients
     * @param name Name of client who quit
     * @return 1 if sucess, 0 else
     */
    int removeClient(WaitingQueue* queue, char* name);


    /**
     * @brief Return the queue in attend order by priority
     * @param queue WaitingQueue of clients
     * @param numClients Adress of variable that storage number of clients
     * @return Array of clients in order by priority
     */
    Client* getQueueOrder(const WaitingQueue* queue, int* numClients);


    /**
     * @brief Delete all data dynamic alocated
     * @param queue WaitingQueue of clients
     */
    void deleteQueue(WaitingQueue* queue);
}

#endif