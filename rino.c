/*

Copyright (c) 2015 Michel Martens

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

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
