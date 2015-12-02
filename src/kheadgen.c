/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Kh4L <panev_s@epita.fr> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#ifdef __linux__
# define _XOPEN_SOURCE 700
#endif /* !__linux__ */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

static char *create_def_name(char *name)
{
    size_t son = strlen(name);
    char *def_name = malloc((son + 1) * sizeof (char));
    size_t i;
    for (i = 0; i < son; ++i)
    {
        if (name[i] == '.')
            def_name[i] = '_';
        else if (name[i] >= 97 && name[i] <= 123)
            def_name[i] = name[i] - 32;
        else
            def_name[i] = name[i];
    }
    def_name[i] = '\0';
    return def_name;
}

static char *class_name(char *name)
{
  size_t son = strlen(name);
  if (son == 0)
    exit(2);
  name[0] = name[0] - 32;
  
  for (char *tmp = name; *tmp != '\0'; ++tmp)
  {
    if (*tmp == '.')
      *tmp = '\0';
  }
  return name;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        char *name = basename(argv[0]);
        dprintf(2, "Usage: %s [headername]\n", name);
        return 1;
    }

    printf("Generating the header...\n");

    FILE * header = fopen(argv[1], "w+");
    if (header == NULL)
    {
        perror("could not create the header");
        return 1;
    }

    char *def_name = create_def_name(argv[1]);
    
    if (argc > 2 && !strcmp(argv[2], "-c"))
    {
      char *cname = class_name(argv[1]);
      fprintf(header, "#ifndef %s\n# define %s\n\n"
          "class %s\n{\n\n};\n"
          "\n#endif /* !%s */",
          def_name, def_name, cname, def_name);
    }
    else
    {
      fprintf(header, "#ifndef %s\n# define %s\n\n#endif /* !%s */",
          def_name, def_name, def_name);
    }
    free(def_name);
    fclose(header);
    printf("Header successfully generated: %s\n", argv[1]);
    return 0;
}
