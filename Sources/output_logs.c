//
// Created by Valentin on 10/17/2019.
//

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "../Header/core_game.h"

static FILE *output;

static const char format_specifier[6][4] = {
		"c",
		"d",
		"li",
		"lu",
		"lli",
		"llu"
};

static void append_buffer(char *buff, int buff_size, char type[4], va_list *arg_list)
{
	char str_type[5] = {'\0'};
	int i = 0;

	str_type[0] = '%';
	strcat(str_type, type);
	if (strcmp(type, format_specifier[i++]) == 0) { // c
		snprintf(buff, buff_size, str_type, va_arg(*arg_list, int));
	} else if (strcmp(type, format_specifier[i++]) == 0) { // d
		snprintf(buff, buff_size, str_type, va_arg(*arg_list, int));
	} else if (strcmp(type, format_specifier[i++]) == 0) { // li
		snprintf(buff, buff_size, str_type, va_arg(*arg_list, long int));
	} else if (strcmp(type, format_specifier[i++]) == 0) { // lu
		snprintf(buff, buff_size, str_type, va_arg(*arg_list, unsigned long));
	} else if (strcmp(type, format_specifier[i++]) == 0) { // lli
		snprintf(buff, buff_size, str_type, va_arg(*arg_list, long long int));
	} else if (strcmp(type, format_specifier[i++]) == 0) { // llu
		snprintf(buff, buff_size, str_type, va_arg(*arg_list, unsigned long long));
	}
}

void output_logs_str(const char prefix[], const char str[], ...)
{
	va_list arg_list;
	unsigned int cursor = 0, backup = 0;
	char type[4] = {'\0'};
	int BUFF_MAX = 24;
	char *buffer = malloc(sizeof(char) * BUFF_MAX);

	fprintf(output, "%s", prefix);
	va_start(arg_list, str);
	while (str[cursor]) {
		if (str[cursor] == '%') {
			for (int i = 0; i < 6; i++) {
				backup = cursor + 1;
				if (str[backup] == '%')
					break;
				for (int j = 0; j < (int)strlen(format_specifier[i]); j++) {
					if (str[backup] == format_specifier[i][j]) {
						type[j] = str[backup];
						backup++;
					}
				}
				if (strlen(type) == strlen(format_specifier[i])) {
					if (strcmp(type, format_specifier[i]) == 0) {
						cursor = backup - 1;
						break;
					}
				}
			}
			append_buffer(buffer, BUFF_MAX, type, &arg_list);
			for (int i = 0; i < 4; i++)
				type[i] = '\0';
			fprintf(output, "%s", buffer);
		} else {
			fprintf(output, "%c", str[cursor]);
		}
		cursor++;
	}
	va_end(arg_list);
	free(buffer);
}

void close_file(void)
{
	fclose(output);
}

void get_log_file(void)
{
	char log_path[] = "output.log";

	output = fopen(log_path, "w+");
	if (output == NULL) {
		fprintf(stderr, "%s could not be opened.\n", log_path);
		return;
	}
	fprintf(output, "[INFO] Opening file to read/write, setting cursor at initial position.\n");
	fprintf(output, "[INFO] If you're reading this line, please don't mind it. Just some file opening :)\n");
	fprintf(output, "[INFO] Logfile named '%s' opened without issue\n", log_path);
}