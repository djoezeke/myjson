#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define JSON value types
typedef enum
{
    JSON_NULL,
    JSON_BOOL,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JsonType;

// Forward declaration of JsonValue
typedef struct JsonValue JsonValue;

// Define a JSON key-value pair for objects
typedef struct
{
    char *key;
    JsonValue *value;
} JsonKeyValuePair;

// Define a JSON value
struct JsonValue
{
    JsonType type;
    union
    {
        int bool_value;
        double number_value;
        char *string_value;
        struct
        {
            JsonValue **items;
            size_t size;
        } array_value;
        struct
        {
            JsonKeyValuePair **items;
            size_t size;
        } object_value;
    } data;
};

// Function to create a JSON null value
JsonValue *json_create_null()
{
    JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue));
    value->type = JSON_NULL;
    return value;
}

// Function to create a JSON boolean value
JsonValue *json_create_bool(int bool_value)
{
    JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue));
    value->type = JSON_BOOL;
    value->data.bool_value = bool_value;
    return value;
}

// Function to create a JSON number value
JsonValue *json_create_number(double number_value)
{
    JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue));
    value->type = JSON_NUMBER;
    value->data.number_value = number_value;
    return value;
}

// Function to create a JSON string value
JsonValue *json_create_string(const char *string_value)
{
    JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue));
    value->type = JSON_STRING;
    value->data.string_value = strdup(string_value);
    return value;
}

// Function to create a JSON array value
JsonValue *json_create_array()
{
    JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue));
    value->type = JSON_ARRAY;
    value->data.array_value.items = NULL;
    value->data.array_value.size = 0;
    return value;
}

// Function to add an item to a JSON array
void json_array_add(JsonValue *array, JsonValue *item)
{
    if (array->type != JSON_ARRAY)
        return;
    array->data.array_value.items = (JsonValue **)realloc(array->data.array_value.items, (array->data.array_value.size + 1) * sizeof(JsonValue *));
    array->data.array_value.items[array->data.array_value.size] = item;
    array->data.array_value.size++;
}

// Function to create a JSON object value
JsonValue *json_create_object()
{
    JsonValue *value = (JsonValue *)malloc(sizeof(JsonValue));
    value->type = JSON_OBJECT;
    value->data.object_value.items = NULL;
    value->data.object_value.size = 0;
    return value;
}

// Function to add a key-value pair to a JSON object
void json_object_add(JsonValue *object, const char *key, JsonValue *value)
{
    if (object->type != JSON_OBJECT)
        return;
    JsonKeyValuePair *pair = (JsonKeyValuePair *)malloc(sizeof(JsonKeyValuePair));
    pair->key = strdup(key);
    pair->value = value;
    object->data.object_value.items = (JsonKeyValuePair **)realloc(object->data.object_value.items, (object->data.object_value.size + 1) * sizeof(JsonKeyValuePair *));
    object->data.object_value.items[object->data.object_value.size] = pair;
    object->data.object_value.size++;
}

// Function to print a JSON value (for demonstration purposes)
void json_print(JsonValue *value)
{
    switch (value->type)
    {
    case JSON_NULL:
        printf("null");
        break;
    case JSON_BOOL:
        printf(value->data.bool_value ? "true" : "false");
        break;
    case JSON_NUMBER:
        printf("%f", value->data.number_value);
        break;
    case JSON_STRING:
        printf("\"%s\"", value->data.string_value);
        break;
    case JSON_ARRAY:
        printf("[");
        for (size_t i = 0; i < value->data.array_value.size; i++)
        {
            if (i > 0)
                printf(", ");
            json_print(value->data.array_value.items[i]);
        }
        printf("]");
        break;
    case JSON_OBJECT:
        printf("{");
        for (size_t i = 0; i < value->data.object_value.size; i++)
        {
            if (i > 0)
                printf(", ");
            printf("\"%s\": ", value->data.object_value.items[i]->key);
            json_print(value->data.object_value.items[i]->value);
        }
        printf("}");
        break;
    }
}

// Function to free a JSON value
void json_free(JsonValue *value)
{
    if (!value)
        return;
    switch (value->type)
    {
    case JSON_STRING:
        free(value->data.string_value);
        break;
    case JSON_ARRAY:
        for (size_t i = 0; i < value->data.array_value.size; i++)
        {
            json_free(value->data.array_value.items[i]);
        }
        free(value->data.array_value.items);
        break;
    case JSON_OBJECT:
        for (size_t i = 0; i < value->data.object_value.size; i++)
        {
            free(value->data.object_value.items[i]->key);
            json_free(value->data.object_value.items[i]->value);
            free(value->data.object_value.items[i]);
        }
        free(value->data.object_value.items);
        break;
    default:
        break;
    }
    free(value);
}

int main()
{
    // Create a JSON object
    JsonValue *root = json_create_object();
    json_object_add(root, "name", json_create_string("John Doe"));
    json_object_add(root, "age", json_create_number(30));
    json_object_add(root, "is_student", json_create_bool(0));

    // Create a JSON array and add it to the object
    JsonValue *hobbies = json_create_array();
    json_array_add(hobbies, json_create_string("reading"));
    json_array_add(hobbies, json_create_string("swimming"));
    json_array_add(hobbies, json_create_string("coding"));
    json_object_add(root, "hobbies", hobbies);

    // Print the JSON object
    json_print(root);
    printf("\n");

    // Free the JSON object
    json_free(root);

    return 0;
}