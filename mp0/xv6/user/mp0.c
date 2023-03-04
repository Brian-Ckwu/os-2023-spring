#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(int argc, char* argv[]) {
  // Exception handling
  if (argc != 3) {
    fprintf(2, "Usage: mp0 <root_directory> <key>\n");
    exit(1);
  }

  char* path = argv[1];
  char* key = argv[2];
  int keylen = strlen(key);

  char* err_msg = "[error opening dir]";
  int fd;
  if ((fd = open(path, 0)) < 0) {
    fprintf(2, "%s %s\n", path, err_msg);
    exit(1);
  }
  

  // XXX: sanity check
  printf("mp0 executed!\n");
  printf("<root_directory>: %s\n", path);
  printf("<key>: %s (%d character(s))\n", key, keylen);
  // Traverse the paths: the traversing order should be the same as the ls command

  exit(0);
}