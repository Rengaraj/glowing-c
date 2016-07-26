#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <ctype.h>

/*
 * Trims lead and trailing whitespace, in a string. Returns the
 * pointer that points to an offset within the string. The original
 * string is modified in-place, to trim the trailing whitespace.
 *
 * Derived from http://stackoverflow.com/a/122721/1295013
 */
char *trim(char *str)
{
	char *end;

	/* Trim leading space. */
	while (isspace(*str))
		str++;

	if (*str == 0)  /* All spaces? */
		return str;

	/* Trim trailing space. */
	end = str + strlen(str) - 1;
	while (end > str && isspace(*end))
		end--;

	/* Write new null terminator. */
	*(end + 1) = 0;

	return str;
}

/*
 * Split a string, using the specified delimiter. Returns a array of
 * pointers, to offsets within the provided string. The array of
 * pointers is dynamically allocated. The original string is modified
 * in-place, to insert nul characters to terminate each sub-string.
 *
 * Dervied from http://stackoverflow.com/a/9210560/1295013
 */
char **str_split(char *str, const char delim_ch)
{
	char **result = 0;
	size_t count = 0;
	char *tmp = str;
	char *last_comma = 0;
	char delim[2];

	delim[0] = delim_ch;
	delim[1] = 0;

	/* Count how many elements will be extracted. */
	while (*tmp) {
		if (delim_ch == *tmp) {
			count++;
			last_comma = tmp;
		}
		tmp++;
	}

	/* Add space for trailing token. */
	count += last_comma < (str + strlen(str) - 1);

	/* Add space for terminating null string so caller
	   knows where the list of returned strings ends. */
	count++;

	result = malloc(sizeof(char *) * count);

	if (result) {
		size_t idx = 0;
		char *token = strtok(str, delim);

		while (token) {
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}

	return result;
}

/*
 * Input directory from user, and change current working directory to
 * the user specified directory.
 */
void do_chdir(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t ret;
	int err;
	char *dirname;

	printf("dir: ");

	ret = getline(&line, &len, stdin);
	if (ret == -1) {
		fprintf(stderr, "error reading input\n");
		return;
	}

	dirname = trim(line);

	err = chdir(dirname);
	if (err == -1) {
		fprintf(stderr, "chdir failed: %s", strerror(errno));
		goto err_exit;
	}

err_exit:
	free(line);
}

/*
 * Input command from user, and execute the command in the foreground.
 */
void do_exec_cmd(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t ret;
	pid_t cpid;
	int err;
	char **split;
	char *trimed;

	printf("cmd: ");

	ret = getline(&line, &len, stdin);
	if (ret == -1) {
		fprintf(stderr, "error reading input\n");
		return;
	}

	trimed = trim(line);
	if (strlen(trimed) == 0)
		return;

	split = str_split(trimed, ' ');

	cpid = fork();
	if (cpid == -1) {
		fprintf(stderr, "error creating child: %s\n", strerror(errno));
		goto err_exit;
	}

	if (cpid == 0) {
		execvp(split[0], split);
		fprintf(stderr, "error executing cmd '%s': %s\n",
			split[0], strerror(errno));
		exit(0);
	}

	err = waitpid(cpid, NULL, 0);
	if (err == -1) {
		if (errno != ECHILD)
			fprintf(stderr, "error waiting for child: %s\n",
				strerror(errno));
		goto err_exit;
	}

err_exit:
	free(split);
	free(line);
}

void show_help(char *menu[])
{
	int i;

	for (i = 0; menu[i] != NULL; i++)
		printf("%s\n", menu[i]);
}

/*
 * Print a prompt to the user to select a menu item. If user specifies
 * an invalid option displays the menu.
 */
int do_prompt(char *menu[])
{
	int i;
	char line[8];
	char *retp;

	while (1) {
		char *cwd;

		cwd = get_current_dir_name();
		if (cwd == NULL)
			cwd = "(none)";

		printf("%s$ ", cwd);
		free(cwd);

		retp = fgets(line, sizeof(line), stdin);
		if (retp == NULL)
			return EOF;

		for (i = 0; menu[i] != NULL; i++) {
			if (line[0] == menu[i][0])
				return line[0];
		}

		fprintf(stderr, "unrecognized input: %c\n", line[0]);
		show_help(menu);
	}

	return 0;
}

/*
 * Main application entry point.
 */
int main(int argc, char *argv[])
{
	char *main_menu[] = {
		"c: Change Directory",
		"f: Execute Command",
		"x: Exit",
		"h: Help",
		NULL,
	};


	while (1) {
		int cmd = do_prompt(main_menu);

		switch (cmd) {
		case 'c':
			do_chdir();
			break;
		case 'f':
			do_exec_cmd();
			break;
		case 'h':
			show_help(main_menu);
			break;
		case 'x':
		case EOF:
			return 0;
		}
	}
}
