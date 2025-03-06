#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to print spaces for indentation
void print_indent(int indent)
{
    for (int i = 0; i < indent; i++)
    {
        printf("  ");
    }
}

// Function to pretty print a JSON string
void json_pretty_print(const char *json)
{
    int indent = 0;
    int in_string = 0;
    int escape = 0;

    for (const char *p = json; *p; p++)
    {
        char ch = *p;

        if (in_string)
        {
            // Inside a string
            if (escape)
            {
                escape = 0;
            }
            else if (ch == '\\')
            {
                escape = 1;
            }
            else if (ch == '"')
            {
                in_string = 0;
            }
            putchar(ch);
        }
        else
        {
            // Outside a string
            switch (ch)
            {
            case '{':
            case '[':
                putchar(ch);
                putchar('\n');
                indent++;
                print_indent(indent);
                break;
            case '}':
            case ']':
                putchar('\n');
                indent--;
                print_indent(indent);
                putchar(ch);
                break;
            case ',':
                putchar(ch);
                putchar('\n');
                print_indent(indent);
                break;
            case ':':
                putchar(ch);
                putchar(' ');
                break;
            case '"':
                in_string = 1;
                putchar(ch);
                break;
            default:
                if (!isspace(ch))
                {
                    putchar(ch);
                }
                break;
            }
        }
    }
    putchar('\n');
}

int main()
{
    const char *json = "{\"name\":\"John Doe\",\"age\":30,\"is_student\":false,\"hobbies\":[\"reading\",\"swimming\",\"coding\"]}";

    printf("Original JSON:\n%s\n\n", json);
    printf("Pretty Printed JSON:\n");
    json_pretty_print(json);

    return 0;
}