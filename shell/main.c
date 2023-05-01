#include "main.h"

int shell_start() {
	char **env_copy = get_environment_copy();
	char *path_value;
	char **paths;
	size_t i;
	int existcomd;


	path_value = get_path_variable(env_copy);
	paths = tokenize_path(path_value);

	for (i = 0; paths[i] != NULL; i++) {
		printf("%s\n", paths[i]);
	}

	existcomd = find_executable("caca", paths);

	printf("\n\n%d\n\n", existcomd);
	/*recuerda liberar la memoria*/
	for (i = 0; env_copy[i] != NULL; i++) {
		free(env_copy[i]);
	}
	free(env_copy);

	for (i = 0; paths[i] != NULL; i++) {
		free(paths[i]);
	}
	free(paths);

	return 0;
}
int main() {
	return shell_start();
}
