#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int file;

void print_array(int *array, int size){
    int i;
    for(i = 0; i < size; i++){
        printf("\t\tRandom %d: %d\n", i, array[i]);
    }
}

int random_number(){
    int *buffer;
    int file_descriptor = read(file, buffer, sizeof(buffer));
    if(file_descriptor == -1) return -1;
    else return *buffer;
}

int main(void){
    int rand_array[10];
    file = open("/dev/urandom", O_RDONLY);
    if (file == -1) {
        printf("Error: %s \t Error Code: %d\n", strerror(errno), errno);
        return 0;
    }

    //Fill rand_array with generated values
    {
        int i = 0;
        while(i <= 9) {
            int element = random_number();
            if(element == -1) {
                printf("(Failed to get random number) Error: %s \t Error Code: %d\n", strerror(errno), errno);
            }
            rand_array[i] = element;
            i++;
        }
    }

    //Printing rand_array
    printf("Printing array:\n");
    print_array(rand_array, sizeof(rand_array)/sizeof(rand_array[0]));

    //Creating and writing to file.
    printf("\nWriting numbers to file...\n");
    int new_file = open("MamaMia123.txt", O_CREAT | O_WRONLY, 0666);
    if (new_file == -1) {
        printf("Creating file failed. Error: %s   Error Code: %d\n", strerror(errno), errno);
        return 0;
    }
    
    int write_to = write(new_file, rand_array, sizeof(rand_array));
    if (write_to == -1) {
        printf("Writing to file failed. Error: %s   Error Code: %d\n", strerror(errno), errno);
        return 0;
    }

    close(new_file);

    //Reading from file
    int read_nums[10];

    int file_descriptor = open("MamaMia123.txt", O_RDONLY);
    if (file_descriptor == -1) {
        printf("Opening file failed. Error: %s   Error Code: %d\n", strerror(errno), errno);
        return 0;
    }
    int read_code = read(file_descriptor, read_nums, sizeof(read_nums));
    if (file_descriptor == -1) {
        printf("Reading file failed. Error: %s   Error Code: %d\n", strerror(errno), errno);
        return 0;
    }

    close(file);
    close(file_descriptor);
    printf("\nReading numbers from file: \n");
    print_array(read_nums, sizeof(read_nums)/sizeof(read_nums[0]));

}