#include <iostream>
#include <pthread.h>
#include <unistd.h> // Äëÿ sleep()

// Ãëîáàëüíûå ïåðåìåííûå
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int ready = 0; // Ôëàã ñîñòîÿíèÿ ñîáûòèÿ (0 - ñîáûòèå îòñóòñòâóåò, 1 - ñîáûòèå ãîòîâî)

// Ôóíêöèÿ provide (àíàëîã producer)
void synchronized_provide() {
    pthread_mutex_lock(&lock); // Çàõâàòûâàåì ìüþòåêñ
    if (ready == 1) {          // Åñëè ñîáûòèå óæå ãîòîâî
        pthread_mutex_unlock(&lock);
        return;                // Âûõîäèì, íå ñîçäàâàÿ íîâîå ñîáûòèå
    }
    ready = 1;                 // Óñòàíàâëèâàåì ôëàã
    std::cout << "Event provided" << std::endl;
    pthread_cond_signal(&cond1); // Óâåäîìëÿåì ïîòðåáèòåëÿ
    pthread_mutex_unlock(&lock); // Îñâîáîæäàåì ìüþòåêñ
}

// Ôóíêöèÿ consume (àíàëîã consumer)
void synchronized_consume() {
    pthread_mutex_lock(&lock); // Çàõâàòûâàåì ìüþòåêñ
    while (ready == 0) {       // Ïîêà ñîáûòèå íå ãîòîâî
        pthread_cond_wait(&cond1, &lock); // Îæèäàåì óâåäîìëåíèÿ
        std::cout << "Awoke from wait" << std::endl;
    }
    ready = 0;                 // Ñáðàñûâàåì ôëàã
    std::cout << "Event consumed" << std::endl;
    pthread_mutex_unlock(&lock); // Îñâîáîæäàåì ìüþòåêñ
}

// Ïîòîê ïîñòàâùèêà
void* producer_thread(void* arg) {
    while (true) {
        synchronized_provide(); // Ñîçäà¸ì ñîáûòèå
        sleep(1);               // Çàäåðæêà 1 ñåêóíäà
    }
    return nullptr;
}

// Ïîòîê ïîòðåáèòåëÿ
void* consumer_thread(void* arg) {
    while (true) {
        synchronized_consume(); // Ïîòðåáëÿåì ñîáûòèå
    }
    return nullptr;
}

int main() {
    pthread_t producer, consumer;

    // Ñîçäà¸ì ïîòîêè
    pthread_create(&producer, nullptr, producer_thread, nullptr);
    pthread_create(&consumer, nullptr, consumer_thread, nullptr);

    // Îæèäàåì çàâåðøåíèÿ ïîòîêîâ
    pthread_join(producer, nullptr);
    pthread_join(consumer, nullptr);

    return 0;
}
