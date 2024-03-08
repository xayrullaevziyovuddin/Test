#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int fd = open("./us_people_names.txt", O_RDONLY);

    // Создаем буфер и выделяем память на начальные 1024 байта
    char *buff = calloc(1024, sizeof(char));


    size_t total_size = 1024; // Общий размер буфера
    size_t read_size = 0;     // Количество байт, прочитанных из файла
    ssize_t bytes_read;       // Количество байт, прочитанных на этом шаге

    // Читаем данные из файла
    while ((bytes_read = read(fd, buff + read_size, 1024)) > 0) {
        read_size += bytes_read;
        total_size += 1024; // Увеличиваем общий размер буфера
        buff = realloc(buff, total_size); // Увеличиваем размер буфера
   
    }



    // Данные успешно прочитаны, выводим их
    printf("%s\n", buff);

    // Освобождаем память и закрываем файл
    free(buff);
    close(fd);

    return 0;
}