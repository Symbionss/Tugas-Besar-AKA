#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Fungsi untuk membalik string secara iteratif
void reverse_iterative(char* str) {
    int length = strlen(str);
    int i, j;
    char temp;
    
    // Tukar karakter dari ujung ke tengah
    for (i = 0, j = length - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

// Fungsi untuk membalik string secara rekursif (helper function)
void reverse_recursive_helper(char* str, int start, int end) {
    // Base case: jika start >= end
    if (start >= end) {
        return;
    }
    
    // Tukar karakter pertama dan terakhir
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    
    // Rekursif dengan substring yang lebih kecil
    reverse_recursive_helper(str, start + 1, end - 1);
}

// Fungsi wrapper untuk rekursif
void reverse_recursive(char* str) {
    int length = strlen(str);
    reverse_recursive_helper(str, 0, length - 1);
}

// Fungsi untuk mengukur waktu eksekusi
double measure_time_iterative(char* str, int iterations) {
    clock_t start, end;
    double total_time = 0;
    char* temp_str = malloc(strlen(str) + 1);
    
    for (int i = 0; i < iterations; i++) {
        strcpy(temp_str, str); // Salin string asli
        
        start = clock();
        reverse_iterative(temp_str);
        end = clock();
        
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    
    free(temp_str);
    return (total_time / iterations) * 1000; // Kembalikan dalam milidetik
}

double measure_time_recursive(char* str, int iterations) {
    clock_t start, end;
    double total_time = 0;
    char* temp_str = malloc(strlen(str) + 1);
    
    for (int i = 0; i < iterations; i++) {
        strcpy(temp_str, str); // Salin string asli
        
        start = clock();
        reverse_recursive(temp_str);
        end = clock();
        
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    
    free(temp_str);
    return (total_time / iterations) * 1000; // Kembalikan dalam milidetik
}

// Fungsi untuk menghasilkan string dengan panjang tertentu
char* generate_string(int length) {
    char* str = malloc(length + 1);
    
    for (int i = 0; i < length; i++) {
        str[i] = 'a' + (i % 26); // Alternatif huruf untuk variasi
    }
    str[length] = '\0';
    
    return str;
}

// Fungsi untuk menampilkan menu
void display_menu() {
    printf("\n==============================================\n");
    printf(" ANALISIS KOMPLEKSITAS ALGORITMA REVERSE STRING\n");
    printf("==============================================\n");
    printf("1. Reverse String Iteratif\n");
    printf("2. Reverse String Rekursif\n");
    printf("3. Analisis Perbandingan Performa\n");
    printf("4. Keluar\n");
    printf("==============================================\n");
}

int main() {
    int choice;
    char input[1000];
    char str_copy[1000];
    
printf("\n==============================================\n");
printf(" ANALISIS PERBANDINGAN WAKTU EKSEKUSI\n");
printf("==============================================\n");
printf("Ukuran | Iteratif (ms) | Rekursif (ms) | Perbedaan\n");
printf("-------+---------------+---------------+----------\n");

// Ukuran input yang akan diuji
int test_sizes[] = {1, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
int num_tests = sizeof(test_sizes) / sizeof(test_sizes[0]);

for (int i = 0; i < num_tests; i++) {
    int size = test_sizes[i];
    
    // Generate test string
    char* test_str = generate_string(size);
    
    // Ukur waktu dengan 1000 iterasi untuk akurasi
    double time_iterative = measure_time_iterative(test_str, 1000);
    double time_recursive = measure_time_recursive(test_str, 1000);
    double difference = time_recursive - time_iterative;
    
    printf("%6d | %13.6f | %13.6f | %+10.6f\n", 
            size, time_iterative, time_recursive, difference);
    
    free(test_str);
    }
    return 0;
}