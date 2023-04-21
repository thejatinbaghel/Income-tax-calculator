#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
 
#define FILENAME "taxpayers.txt" 
 
struct taxpayer { 
    char name[100]; 
    int income; 
    float tax; 
}; 
 
// Function prototypes 
void add_new_record(); 
void list_all_records(); 
void search_record(); 
void edit_record(); 
void delete_record(); 
 
int main() { 
    int choice; 
 
    while (1) { 
        printf("\nIncome Tax Calculator\n"); 
        printf("1. Add new record\n"); 
        printf("2. List all records\n"); 
        printf("3. Search record\n"); 
        printf("4. Edit record\n"); 
        printf("5. Delete record\n"); 
        printf("6. Exit\n"); 
        printf("Enter your choice: "); 
        scanf("%d", &choice); 
 
        switch (choice) { 
            case 1: 
                add_new_record(); 
                break; 
            case 2: 
                list_all_records(); 
                break; 
            case 3: 
                search_record(); 
                break; 
            case 4: 
                edit_record(); 
                break; 
            case 5: 
                delete_record(); 
                break; 
            case 6: 
                exit(0); 
            default: 
                printf("Invalid choice\n"); 
        } 
    } 
 
    return 0; 
} 
 
void add_new_record() { 
    struct taxpayer tp; 
 
    printf("Enter name: "); 
    scanf(" %[^\n]s", tp.name); 
 
    printf("Enter income: "); 
    scanf("%d", &tp.income); 
 
    // Calculate tax based on income 
    if (tp.income <= 250000) { 
        tp.tax = 0; 
    } else if (tp.income <= 500000) { 
        tp.tax = (tp.income - 250000) * 0.05; 
    } else if (tp.income <= 1000000) { 
        tp.tax = 12500 + (tp.income - 500000) * 0.2; 
    } else { 
        tp.tax = 112500 + (tp.income - 1000000) * 0.3; 
    } 
 
    FILE *fp = fopen(FILENAME, "a"); 
    fprintf(fp, "%s,%d,%.2f\n", tp.name, tp.income, tp.tax); 
    fclose(fp); 
 
    printf("\n--------------------------------\nRecord added successfully.\n--------------------------------\n"); 
} 
 
void list_all_records() { 
    struct taxpayer tp; 
    FILE *fp = fopen(FILENAME, "r"); 
 
    printf("\n-----------------------------------------------\n%-20s %-20s %-20s\n-----------------------------------------------\n", "Name", "Income", "Tax"); 
    while (fscanf(fp, "%[^,],%d,%f\n", tp.name, &tp.income, &tp.tax) != EOF) { 
        printf("%-20s %-20d %-20.2f\n-----------------------------------------------\n\n", tp.name, tp.income, tp.tax); 
    } 
 
    fclose(fp); 
} 
void search_record() { 
    char name[100]; 
    struct taxpayer tp; 
    int found = 0; 
    printf("\nEnter name to search: "); 
scanf(" %[^\n]s", name); 
 
FILE *fp = fopen(FILENAME, "r"); 
 
while (fscanf(fp, "%[^,],%d,%f\n", tp.name, &tp.income, &tp.tax) != EOF) { 
    if (strcmp(tp.name, name) == 0) { 
        printf("\n-----------------------------------------------\n%-20s %-20s %-20s\n-----------------------------------------------\n", "Name", "Income", "Tax"); 
        printf("%-20s %-20d %-20.2f\n-----------------------------------------------\n\n", tp.name, tp.income, tp.tax); 
        found = 1; 
        break; 
    } 
} 
 
fclose(fp); 
 
if (!found) { 
    printf("Record not found\n"); 
} 
} 
 
void edit_record() { 
char name[100]; 
struct taxpayer tp; 
int found = 0; 
printf("\nEnter name to edit: "); 
scanf(" %[^\n]s", name); 
 
FILE *fp = fopen(FILENAME, "r"); 
FILE *fp_tmp = fopen("temp.txt", "w"); 
 
while (fscanf(fp, "%[^,],%d,%f\n", tp.name, &tp.income, &tp.tax) != EOF) { 
    if (strcmp(tp.name, name) == 0) { 
        printf("Enter new income: "); 
        scanf("%d", &tp.income); 
 
        // Calculate new tax based on new income 
        if (tp.income <= 250000) { 
            tp.tax = 0; 
        } else if (tp.income <= 500000) { 
            tp.tax = (tp.income - 250000) * 0.05; 
        } else if (tp.income <= 1000000) { 
            tp.tax = 12500 + (tp.income - 500000) * 0.2; 
        } else { 
            tp.tax = 112500 + (tp.income - 1000000) * 0.3; 
        } 
 
        fprintf(fp_tmp, "%s,%d,%.2f\n", tp.name, tp.income, tp.tax); 
        found = 1; 
    } else { 
        fprintf(fp_tmp, "%s,%d,%.2f\n", tp.name, tp.income, tp.tax); 
    } 
} 
 
fclose(fp); 
fclose(fp_tmp); 
 
if (!found) { 
    printf("-------------------Record not found.\n-------------------\n\n"); 
} else { 
    remove(FILENAME); 
    rename("temp.txt", FILENAME); 
    printf("--------------------------------------\nRecord updated successfully.\n--------------------------------------\n\n"); 
} 
} 
 
void delete_record() { 
char name[100]; 
struct taxpayer tp; 
int found = 0; 
printf("\nEnter name to delete: "); 
scanf(" %[^\n]s", name); 
 
FILE *fp = fopen(FILENAME, "r"); 
FILE *fp_tmp = fopen("temp.txt", "w"); 
 
while (fscanf(fp, "%[^,],%d,%f\n", tp.name, &tp.income, &tp.tax) != EOF) { 
    if (strcmp(tp.name, name) == 0) { 
        found = 1; 
    } else { 
        fprintf(fp_tmp, "%s,%d,%.2f\n", tp.name, tp.income, tp.tax); 
    } 
} 
 
fclose(fp); 
fclose(fp_tmp); 
 
if (!found) { 
    printf("\n-------------------Record not found.\n-------------------\n\n"); 
} else { 
    remove(FILENAME); 
    rename("temp.txt", FILENAME); 
    printf("\n-------------------------------\nRecord deleted successfully.\n-------------------------------\n\n"); 
    } 
}