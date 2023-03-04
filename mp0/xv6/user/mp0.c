#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int* mp0(char* path, char key) {
  char* err_msg = "[error opening dir]";
  // initial variables for return
  int file_num = 0;
  int dir_num = 0;

  // // XXX: sanity check
  // printf("mp0 executed!\n");
  // printf("<root_directory>: %s\n", path);
  // printf("<key>: %c\n", key);

  // traversal
  // Open the file
  // file variables
  int fd;
  struct stat st;
  // open file -> read file stats -> check that path is a directory
  if (((fd = open(path, 0)) < 0) || (fstat(fd, &st) < 0) || (st.type != T_DIR)) {
    fprintf(2, "%s %s\n", path, err_msg);
    close(fd);
  } else {
    // Traversal (recursive?)
    printf("Traversing %s and search for %c...\n", path, key);
    file_num++;
    dir_num++;
  }

  // allocate memory on the heap for return
  int* res = malloc(2 * sizeof(int));
  res[0] = file_num;
  res[1] = dir_num;
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