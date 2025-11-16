#include "../../include/myjson/myjson.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int number;

    if (argc < 2) {
        printf("Usage: %s file.json ...\n", argv[0]);
        return 0;
    }

    for (number = 1; number < argc; number++) {
        FILE *file;
        JsonParser parser;
        JsonDocument document;
        int done = 0;
        int count = 0;
        int error = 0;

        printf("[%d] Loading '%s': ", number, argv[number]);
        fflush(stdout);

        file = fopen(argv[number], "rb");
        assert(file);

        assert(json_parser_initialize(&parser));

        json_parser_set_input_file(&parser, file);

        while (!done) {
            if (!json_parser_load(&parser, &document)) {
                error = 1;
                break;
            }

            done = (!!json_document_get_root_node(&document));

            json_document_delete(&document);

            if (!done) count++;
        }

        json_parser_delete(&parser);

        assert(!fclose(file));

        printf("%s (%d documents)\n", (error ? "FAILURE" : "SUCCESS"), count);
    }

    return 0;
}
