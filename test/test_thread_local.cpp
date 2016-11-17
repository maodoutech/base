#include "threading/thread_local.h"
#include <pthread.h>
#include <string>

void* route1(void*);
void* route2(void*);

struct Word {
    uint64_t wordid;
    std::string word;
};

int main(int argc, const char *argv[])
{
    pthread_t pid[2] = {0};
    pthread_create(&pid[0], NULL, route1, NULL);
    pthread_create(&pid[1], NULL, route2, NULL);

    printf("main thread id = %d\n", pthread_self());
    route2(NULL);

    pthread_join(pid[0], NULL);
    pthread_join(pid[1], NULL);
    return 0;
}

void* route1(void*) {
    Word* data = base::get_thread_local<Word>();
    data->wordid = 1000;

    Word* local_data = base::get_thread_local<Word>();
    fprintf(stdout, "route1 data=%lu\n", local_data->wordid);
}

void* route2(void*) {
    sleep(1);
    Word* data = base::get_thread_local<Word>();
    fprintf(stdout, "thrad %d data=%lu\n", pthread_self(), data->wordid);
}
