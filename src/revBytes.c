#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

// build static 8-bits lookuptable by macro expansion
// this is computed at compile time
// based on the following 2-bits reverse order
// 0, 1, 2, 3 = 00, 01, 10, 11
// 0, 2, 1, 3 = 00, 10, 01, 11
#define R2(n) n, n + 2 * 64, n + 1 * 64, n + 3 * 64
#define R4(n) R2(n), R2(n + 2 * 16), R2(n + 1 * 16), R2(n + 3 * 16)
#define R6(n) R4(n), R4(n + 2 * 4), R4(n + 1 * 4), R4(n + 3 * 4)
unsigned int lookuptable[256] = {R6(0), R6(2), R6(1), R6(3)};

#define LEN 81


char* errorMessage(int e) {
  static char errorMsg[LEN];
  switch (e) {
    case EPERM: snprintf(errorMsg, LEN, "Operation not permitted"); break;
    case ENOENT: snprintf(errorMsg, LEN, "No such file or directory"); break;
    case EACCES: snprintf(errorMsg, LEN, "Permission denied"); break;
    case ENOSPC: snprintf(errorMsg, LEN, "No space left on device"); break;
    case EROFS: snprintf(errorMsg, LEN, "Read-only file system"); break;
    default: snprintf(errorMsg, LEN, "Unknown error: %u", e) ;
  }
  return errorMsg;
}


void printDescription(const char *path)
{
  char *name;
  // extract filename from path
  (name = strrchr((char *)path, '/')) ? ++name : (name = (char *)path);
  printf("\n\033[1m%s\033[22m - a small utility to revert bits\n\n", name);
}

void printUsage(const char *path)
{
  char *name;
  // extract filename from path
  (name = strrchr((char *)path, '/')) ? ++name : (name = (char *)path);
  printf("\033[1musage:\033[22m  %s inputFile [outputFile]\n\n", name);
  printf("%s is a tool to revert bits in a list of 8-bits integer.\nThe data in the input and output files are comma-separated.\n\n", name);
}

int main(int argc, char const *argv[])
{
  FILE *out = stdout;

  if (argc < 2)
  {
    printDescription(argv[0]);
    printUsage(argv[0]);
    exit(EXIT_SUCCESS);
  }

  if (strcmp("-h", argv[1]) == 0 || strcmp("--help", argv[1]) == 0)
  {
    printDescription(argv[0]);
    printUsage(argv[0]);
    exit(EXIT_SUCCESS);
  }

  const char *filename = argv[1];
  printf("Read: %s\n", filename);
  FILE *file = fopen(filename, "rt");
  if (file == NULL)
  {
    fprintf(stderr, "\033[1mError:\033[22m Could not open input file: %s (%s)\n", filename, errorMessage(errno));
    exit(EXIT_FAILURE);
  }

  if (argc == 3)
  {
    const char *output = argv[2];
    out = fopen(output, "w");
    if (out == NULL)
    {
      fprintf(stderr, "\033[1mError:\033[22m Could not open output file: %s (%s)\n", output, errorMessage(errno));
      exit(EXIT_FAILURE);
    }
    printf("Write to: %s\n", output);
  }

  char line[LEN];
  const char *sep = ",";
  char *end;

  while (fgets(line, LEN, file) != NULL)
  {
    char *tok = strtok(line, sep);
    while (tok != NULL)
    {
      int res = strtoul(tok, &end, 10);
      if (tok == end)
        break;
      fprintf(out, "%3u", lookuptable[res]);
      tok = strtok(NULL, sep);
      if (tok != NULL) fprintf(out, ",");
    }
    fprintf(out, "\n");
  }

  fclose(out);

  exit(EXIT_SUCCESS);
}
