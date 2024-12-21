#include <pthread.h>
#include <iostream>
#include <unistd.h> // Для sleep()

void* my_thread(void* arg) {
    std::cout << "Hello from thread!" << std::endl;
    return nullptr;
}

int main() {
    pthread_t thread_id; // Переменная для хранения идентификатора потока

    // Создаём поток
    int result = pthread_create(&thread_id, nullptr, my_thread, nullptr);

    if (result == 0) {#include <iostream>
#include <pthread.h>
#include <unistd.h> // Для sleep()

// Глобальные переменные
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int ready = 0; // Флаг состояния события (0 - событие отсутствует, 1 - событие готово)

// Функция provide 
void synchronized_provide() {
    pthread_mutex_lock(&lock); // Захватываем мьютекс
    if (ready == 1) {          // Если событие уже готово
        pthread_mutex_unlock(&lock);
        return;                // Выходим, не создавая новое событие
    }
    ready = 1;                 // Устанавливаем флаг
    std::cout << "Event provided" << std::endl;
    pthread_cond_signal(&cond1); // Уведомляем потребителя
    pthread_mutex_unlock(&lock); // Освобождаем мьютекс
}

// Функция consume 
void synchronized_consume() {
    pthread_mutex_lock(&lock); // Захватываем мьютекс
    while (ready == 0) {       // Пока событие не готово
        pthread_cond_wait(&cond1, &lock); // Ожидаем уведомления
        std::cout << "Awoke from wait" << std::endl;
    }
    ready = 0;                 // Сбрасываем флаг
    std::cout << "Event consumed" << std::endl;
    pthread_mutex_unlock(&lock); // Освобождаем мьютекс
}

// Поток поставщика
void* producer_thread(void* arg) {
    while (true) {
        synchronized_provide(); // Создаём событие
        sleep(1);               // Задержка 1 секунда
    }
    return nullptr;
}

// Поток потребителя
void* consumer_thread(void* arg) {
    while (true) {
        synchronized_consume(); // Потребляем событие
    }
    return nullptr;
}

int main() {
    pthread_t producer, consumer;

    // Создаём потоки
    pthread_create(&producer, nullptr, producer_thread, nullptr);
    pthread_create(&consumer, nullptr, consumer_thread, nullptr);

    // Ожидаем завершения потоков
    pthread_join(producer, nullptr);
    pthread_join(consumer, nullptr);

    return 0;
}
        std::cout << "Thread created successfully!" << std::endl;
    } else {
        std::cerr << "Error creating thread: " << result << std::endl;
    }

    // Ждём завершения потока
    pthread_join(thread_id, nullptr);

    return 0;
}
