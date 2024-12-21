#include <iostream>
#include <pthread.h>
#include <unistd.h> // ��� sleep()

// ���������� ����������
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int ready = 0; // ���� ��������� ������� (0 - ������� �����������, 1 - ������� ������)

// ������� provide (������ producer)
void synchronized_provide() {
    pthread_mutex_lock(&lock); // ����������� �������
    if (ready == 1) {          // ���� ������� ��� ������
        pthread_mutex_unlock(&lock);
        return;                // �������, �� �������� ����� �������
    }
    ready = 1;                 // ������������� ����
    std::cout << "Event provided" << std::endl;
    pthread_cond_signal(&cond1); // ���������� �����������
    pthread_mutex_unlock(&lock); // ����������� �������
}

// ������� consume (������ consumer)
void synchronized_consume() {
    pthread_mutex_lock(&lock); // ����������� �������
    while (ready == 0) {       // ���� ������� �� ������
        pthread_cond_wait(&cond1, &lock); // ������� �����������
        std::cout << "Awoke from wait" << std::endl;
    }
    ready = 0;                 // ���������� ����
    std::cout << "Event consumed" << std::endl;
    pthread_mutex_unlock(&lock); // ����������� �������
}

// ����� ����������
void* producer_thread(void* arg) {
    while (true) {
        synchronized_provide(); // ������ �������
        sleep(1);               // �������� 1 �������
    }
    return nullptr;
}

// ����� �����������
void* consumer_thread(void* arg) {
    while (true) {
        synchronized_consume(); // ���������� �������
    }
    return nullptr;
}

int main() {
    pthread_t producer, consumer;

    // ������ ������
    pthread_create(&producer, nullptr, producer_thread, nullptr);
    pthread_create(&consumer, nullptr, consumer_thread, nullptr);

    // ������� ���������� �������
    pthread_join(producer, nullptr);
    pthread_join(consumer, nullptr);

    return 0;
}