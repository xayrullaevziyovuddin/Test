#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

typedef struct Students
{
    char *name;
} students;

char *read_line(int fd)
{
    char *full_line = calloc(2, sizeof(char));
    int bytes_read;
    char buff = 0;
    for (int i = 0;; i++)
    {
        bytes_read = read(fd, &buff, 1);
  
        if (bytes_read == 0 || buff == '\n')
        {
            full_line[i] = '\0';
            break;
        }
        full_line[i] = buff;
        full_line = realloc(full_line, (i + 2) * sizeof(char));
    
    }
    return full_line;
}

students *load_to_struct(char *full_line)
{
    students *students1 = malloc(sizeof(students));
    students1->name = strdup(full_line);
    return students1;
}

students **load_txt_data(char *file_name, int *size)
{
    int fd = open(file_name, O_RDONLY);
    int count = 0;
    char *full_line;
    students **students_array = NULL; // Инициализация массива

    while (1)
    {
        full_line = read_line(fd);
        if (full_line == NULL)
        {
            // Ошибка чтения строки
            break;
        }
        if (strlen(full_line) == 0)
        {
            free(full_line);
            break;
        }
        students *students1 = load_to_struct(full_line);
        students_array = realloc(students_array, (count + 1) * sizeof(students *));
        if (students_array == NULL)
        {
            // Обработка ошибки realloc
            free(students1->name);
            free(students1);
            free(full_line);
            break;
        }
        students_array[count++] = students1;
        free(full_line);
    }

    close(fd);
    *size = count;
    return students_array;
}

void swap(students **arr, int i, int j)
{
    students *temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void bubble_sort(students **arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (strcmp(arr[j]->name, arr[j + 1]->name) > 0)
            {
                swap(arr, j, j + 1);
            }
        }
    }
}

int main()
{
    char *file_name = "us_people_names.txt";
    int array_size;
    students **students_array = load_txt_data(file_name, &array_size);

    if (students_array != NULL)
    {
        bubble_sort(students_array, array_size);

        for (int i = 0; i < array_size; i++)
        {
            printf("Name: %s\n", students_array[i]->name);
            free(students_array[i]->name);
            free(students_array[i]);
        }
        free(students_array);
    }
    else
    {
        printf("Failed to load data from file.\n");
    }

    return 0;
}
