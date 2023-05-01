#include "main.h"

int find_executable(const char *cmd, char **path_dirs) {
	struct stat buffer;

	if (strchr(cmd, '/')) {
		if (stat(cmd, &buffer) == 0 && (buffer.st_mode & S_IXUSR)) {
			return 0;
		} else {
			fprintf(stderr, "no such file or directory: %s\n", cmd);
			return -1;
		}
	}

	char full_path[PATH_MAX];
	for (int i = 0; path_dirs[i] != NULL; i++) {
		snprintf(full_path, sizeof(full_path), "%s/%s", path_dirs[i], cmd);
		if (stat(full_path, &buffer) == 0 && (buffer.st_mode & S_IXUSR)) {
			return 0;
		}
	}

	fprintf(stderr, "command not found: %s\n", cmd);
	return -1;
}
