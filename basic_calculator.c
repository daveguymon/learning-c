#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "calculator.h"

#define INPUT_BUFFER_SIZE 256

typedef enum
{
    EXPRESSION_INPUT_OK,
    EXPRESSION_INPUT_INVALID,
    EXPRESSION_INPUT_EOF,
    EXPRESSION_INPUT_ERROR
} ExpressionInputStatus;

int get_choice(char *choice)
{
    while (1)
    {
        printf("Do you want to continue? (y/n): ");
        if (scanf(" %c", choice) != 1)
        {
            return 0;
        }

        int remaining;
        while ((remaining = getchar()) != '\n' && remaining != EOF)
        {
        }

        if (*choice == 'y' || *choice == 'Y' || *choice == 'n' || *choice == 'N')
        {
            return 1;
        }
        printf("Invalid choice. Please enter 'y' or 'n'.\n");
    }
}

int parse_expression(const char *input, int *first_val, char *operator, int *second_val)
{
    char *end;
    errno = 0;
    long parsed_first = strtol(input, &end, 10);
    if (end == input || errno == ERANGE || parsed_first < INT_MIN || parsed_first > INT_MAX)
    {
        return 0;
    }

    while (isspace((unsigned char)*end))
    {
        end++;
    }
    if (*end == '\0')
    {
        return 0;
    }
    *operator = *end++;

    errno = 0;
    char *second_start = end;
    long parsed_second = strtol(second_start, &end, 10);
    if (end == second_start || errno == ERANGE || parsed_second < INT_MIN || parsed_second > INT_MAX)
    {
        return 0;
    }

    while (isspace((unsigned char)*end))
    {
        end++;
    }
    if (*end != '\0')
    {
        return 0;
    }

    *first_val = (int)parsed_first;
    *second_val = (int)parsed_second;
    return 1;
}

ExpressionInputStatus read_expression(int *first_val, char *operator, int *second_val)
{
    char input[INPUT_BUFFER_SIZE];

    printf("Enter an expression (for example, 8 + 2): ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        return ferror(stdin) ? EXPRESSION_INPUT_ERROR : EXPRESSION_INPUT_EOF;
    }

    char *newline = strchr(input, '\n');
    if (newline != NULL)
    {
        *newline = '\0';
    }
    else
    {
        int remaining = getchar();
        if (remaining != '\n' && remaining != EOF)
        {
            while (remaining != '\n' && remaining != EOF)
            {
                remaining = getchar();
            }
            if (ferror(stdin))
            {
                return EXPRESSION_INPUT_ERROR;
            }
            return EXPRESSION_INPUT_INVALID;
        }
        if (ferror(stdin))
        {
            return EXPRESSION_INPUT_ERROR;
        }
    }

    if (!parse_expression(input, first_val, operator, second_val))
    {
        return EXPRESSION_INPUT_INVALID;
    }

    return EXPRESSION_INPUT_OK;
}

void display_result(CalcResult result, char operator)
{
    if (result.status == CALC_OK)
    {
        printf("Result: %d\n", result.value);
    }
    else if (result.status == CALC_DIVISION_BY_ZERO)
    {
        printf("Error: Division by zero.\n");
    }
    else if (result.status == CALC_OVERFLOW)
    {
        printf("Error: Integer overflow.\n");
    }
    else if (result.status == CALC_UNKNOWN_OPERATOR)
    {
        printf("Error: Unknown operator '%c'.\n", operator);
    }
}

int main(void)
{
    int first_val, second_val;
    char operator;
    char choice;

    while (1)
    {
        ExpressionInputStatus input_status = read_expression(&first_val, &operator, &second_val);
        switch (input_status)
        {
        case EXPRESSION_INPUT_OK:
            break;
        case EXPRESSION_INPUT_INVALID:
            printf("Invalid input.\n");
            continue;
        case EXPRESSION_INPUT_EOF:
            fprintf(stderr, "\nInput ended before you entered an expression.\n");
            return 1;
        case EXPRESSION_INPUT_ERROR:
            perror("Error reading expression");
            return 1;
        }

        CalcResult result = calculate(first_val, operator, second_val);
        display_result(result, operator);

        if (!get_choice(&choice))
        {
            fprintf(stderr, "\nInput ended before you entered a choice.\n");
            return 1;
        }

        if (choice == 'n' || choice == 'N')
        {
            break;
        }
    }

    return 0;
}
