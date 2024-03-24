#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#define MAX_LINE_LENGTH 256
#define MAX_IMPORTED_FUNCTIONS 100

// Define a structure to hold information about imported C functions
typedef struct {
    const char* name;  // Function name
    void* function;    // Pointer to the C function
} ImportedFunction;

// Array to store imported C functions
ImportedFunction importedFunctions[MAX_IMPORTED_FUNCTIONS];
int numImportedFunctions = 0;

void Print(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void input(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vscanf(format, args);
    va_end(args);
}

void dia_print(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void var(const char* varname, const char* value) {
    // No message printing for variable declaration
}

void editvar(const char* varname, const char* value) {
    // No message printing for variable modification
}

void function_declaration(const char* function_name, const char* parameters) {
    // No message printing for function declaration
}

void function_call(const char* function_name, const char* arguments) {
    // No message printing for function call
}

void include_module(const char* module_filename);

// Function to evaluate arithmetic expressions
double evaluate_expression(const char* expression) {
    double result = 0.0;
    // Use library function like sscanf or implement expression parsing and evaluation
    sscanf(expression, "%lf", &result);
    return result;
}

void calculate(const char* expression) {
    double result = evaluate_expression(expression);
    printf("Result: %.2f\n", result);
}

void execute_module(FILE* module_file) {
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), module_file)) {
        char* token = strtok(line, " \n");
        if (token == NULL) continue; // Skip empty lines

        if (strcmp(token, "use") == 0) {
            char* module_filename = strtok(NULL, " \n");
            include_module(module_filename);
        }
        else if (strcmp(token, "Print") == 0) {
            char format[MAX_LINE_LENGTH];
            char* fmt = strtok(NULL, "\"");
            if (fmt != NULL) {
                strncpy(format, fmt, sizeof(format));
                Print(format);
            }
        }
        else if (strcmp(token, "input") == 0) {
            char format[MAX_LINE_LENGTH];
            char* fmt = strtok(NULL, "\"");
            if (fmt != NULL) {
                strncpy(format, fmt, sizeof(format));
                input(format);
            }
        }
        else if (strcmp(token, "dia_print") == 0) {
            char format[MAX_LINE_LENGTH];
            char* fmt = strtok(NULL, "\"");
            if (fmt != NULL) {
                strncpy(format, fmt, sizeof(format));
                dia_print(format);
            }
        }
        else if (strcmp(token, "var") == 0) {
            char* varname = strtok(NULL, ":");
            char* value = strtok(NULL, ":");
            var(varname, value);
        }
        else if (strcmp(token, "Editvar") == 0) {
            char* varname = strtok(NULL, ":");
            char* value = strtok(NULL, ":");
            editvar(varname, value);
        }
        else if (strcmp(token, "function") == 0) {
            char* function_name = strtok(NULL, " \n");
            char* parameters = strtok(NULL, " \n");
            function_declaration(function_name, parameters);
        }
        else if (strcmp(token, "calculate") == 0) {
            char expression[MAX_LINE_LENGTH];
            char* expr = strtok(NULL, "\"");
            if (expr != NULL) {
                strncpy(expression, expr, sizeof(expression));
                double result = evaluate_expression(expression);
                printf("Result: %.2f\n", result);
            }
        }
        else if (strcmp(token, "execute") == 0) {
            char* module_filename = strtok(NULL, " \n");
            FILE* nested_module_file = fopen(module_filename, "r");
            if (nested_module_file != NULL) {
                execute_module(nested_module_file);
                fclose(nested_module_file);
            }
            else {
                perror("Error opening nested module file");
            }
        }
        else if (strcmp(token, "if") == 0) {
            // Implement securely
            char* condition = strtok(NULL, "\n");
            if (condition) {
                // implement securely
            }
            else {
                printf("Missing condition for if statement\n");
            }
        }
        else if (strcmp(token, "for") == 0) {
            // Implement securely
            char* loop_variable = strtok(NULL, " \n");
            char* range = strtok(NULL, " \n");
            if (loop_variable && range) {
                // implement securely
            }
            else {
                printf("Missing loop variable or range for for loop\n");
            }
        }
        else if (strcmp(token, "breakif") == 0) {
            // Implement securely
            char* condition = strtok(NULL, "\n");
            if (condition) {
                // implement securely
            }
            else {
                printf("Missing condition for breakif statement\n");
            }
        }
        else if (strcmp(token, "forever") == 0) {
            // Implement securely
            // This is an infinite loop
        }
        else {
            // Check if it's an attempt to call an imported C function
            for (int i = 0; i < numImportedFunctions; i++) {
                if (strcmp(token, importedFunctions[i].name) == 0) {
                    // Call the imported C function with provided arguments
                    // Example: ((void (*)())importedFunctions[i].function)();
                    break;
                }
            }
            printf("Unrecognized command from module: %s\n", token);
        }
    }
}

// Function to include and execute another module
void include_module(const char* module_filename) {
    if (!module_filename) return;

    FILE* module_file = fopen(module_filename, "r");
    if (module_file == NULL) {
        perror("Error opening module file");
        return;
    }

    execute_module(module_file);

    fclose(module_file);
}

// Function to import a C function
void import_function(const char* name, void* function) {
    if (numImportedFunctions < MAX_IMPORTED_FUNCTIONS) {
        importedFunctions[numImportedFunctions].name = name;
        importedFunctions[numImportedFunctions].function = function;
        numImportedFunctions++;
    }
    else {
        printf("Maximum number of imported functions reached.\n");
    }
}

// Function to call an imported C function
void call_imported_function(const char* name) {
    // Find the imported function by name
    for (int i = 0; i < numImportedFunctions; i++) {
        if (
            strcmp(importedFunctions[i].name, name) == 0) {
            // Call the imported C function
            // Example: ((void (*)())importedFunctions[i].function)();
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    printf("Welcome to Dia Runtime!\n");
    if (argc < 2) {
        printf("Usage: %s <filename.dia>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    execute_module(file);

    fclose(file);
    return 0;
}
