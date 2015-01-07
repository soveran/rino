#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("usage: rino number\n");
		return 1;
	}

	ino_t ino;
	DIR *dirp;
	struct dirent *dirent;

	sscanf(argv[1], "%llu", &ino);

	dirp = opendir(".");

	if (dirp == NULL) {
		warn("%s", ".");
		return 1;
	}

	while ((dirent = readdir(dirp)) != NULL) {
		if (dirent->d_ino != ino) continue;

		if (unlink(dirent->d_name) != 0) {
			warn("%s", dirent->d_name);
			return 1;
		}
	}

	closedir(dirp);
	return 0;
}
