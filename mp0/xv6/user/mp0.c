#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int count_occurrence(char* path, char key) {
  int count = 0;
  int i;
  for (i = 0; i < strlen(path); i++) {
    if (path[i] == key) count++;
  }
  return count;
}

void traverse(char* path, char key, int* file_num, int* dir_num) {
  // Utility variables
  // MYDIRSIZ == 10
  int fd;
  struct dirent de;

  char npath[128]; // buffer for the new path
  char* p;
  struct stat nst;

  if ((fd = open(path, 0)) < 0) {
    fprintf(2, "mp0: cannot open %s\n", path);
    exit(1);
  }

  strcpy(npath, path);
  p = npath + strlen(npath);
  *(p++) = '/';

  while (read(fd, &de, sizeof(de)) == sizeof(de)) {
    if (de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) continue;
    // make the whole new path
    memmove(p, de.name, DIRSIZ);
    p[DIRSIZ] = 0;
    // read new path stat
    if (stat(npath, &nst) < 0) {
      fprintf(2, "mp0: cannot stat %s\n", npath);
      exit(1);
    }
    
    // Count occurrence and print
    int count = count_occurrence(npath, key);
    printf("%s %d\n", npath, count);
    // check stat
    switch (nst.type) {
      case T_FILE:
        *file_num = *file_num + 1;
        break;
      case T_DIR:
        *dir_num = *dir_num + 1;
        traverse(npath, key, file_num, dir_num);
        break;
    }
  }

  close(fd);
}

int* mp0(char* path, char key) {
  char* err_msg = "[error opening dir]";
  // initial variables for return
  int file_num = 0;
  int dir_num = 0;

  // file variables
  int fd;
  struct stat st;
  // open file -> read file stats -> check that path is a directory
  if (((fd = open(path, 0)) < 0) || (fstat(fd, &st) < 0) || (st.type != T_DIR)) {
    fprintf(2, "%s %s\n", path, err_msg);
    close(fd);
  } else {
    // Recursive traversal
    int count = count_occurrence(path, key);
    printf("%s %d\n", path, count);
    close(fd);
    traverse(path, key, &file_num, &dir_num);
  }

  // allocate memory on the heap for return
  int* res = malloc(2 * sizeof(int));
  res[0] = dir_num;
  res[1] = file_num;
  return res;
}

int main(int argc, char* argv[]) {
  // Exception handling
  if (argc != 3) {
    fprintf(2, "Usage: mp0 <root_directory> <key>\n");
    exit(1);
  }

  // Create a pipe
  int fds[2];
  if (pipe(fds) < 0) {
    fprintf(2, "mp0: pipe failed\n");
    exit(1);
  }

  // Fork a child
  int pid = fork();
  if (pid == 0) { // child process
    // Traverse dirs and files
    int* res = mp0(argv[1], argv[2][0]);
    // Write to the pipe
    close(fds[0]);
    if (write(fds[1], res, 2 * sizeof(int)) != 2 * sizeof(int)) {
      fprintf(2, "mp0: pipe write failed\n");
      exit(1);
    }
    free(res);
    exit(0);
  } else if (pid < 0) {
    fprintf(2, "mp0: fork failed\n");
    exit(1);
  } else { // parent process
    // Read from the pipe
    close(fds[1]);
    int res[2];
    if (read(fds[0], res, 2 * sizeof(int)) != 2 * sizeof(int)) {
      fprintf(2, "mp0: pipe read failed\n");
      exit(1);
    }
    printf("\n%d directories, %d files\n", res[0], res[1]);
  }

  exit(0);
}