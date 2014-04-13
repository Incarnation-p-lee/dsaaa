/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                             */
/*-DATE:        10272013                                                      */
/*-WHAT:        Homework chapter 1.4                                          */
/*-REVISION:                                                                  */
/*- DATE ------------------------ DESCRIPTION --------------------------------*/
/*- 10272013    CHAPTER 1-4                                                  -*/
/*----------------------------------------------------------------------------*/
void
chapt_1_4(void)
{
  ENTER("chapt_1_4");

  print_report_header(stdout, "Expanding Header Files", 1, 4);
  print_report_header(dsaaa_report, "Expanding Header Files", 1, 4);
  dochapt_1_4();

  LEAVE;
  return;
}


static void
dochapt_1_4(void)
{
  register char **filename;
  char *sourcefiles[] = {
    "main.m",
    "chapter_1.m",
    "defs.h",
    "externals.h",
  };
  ENTER("dochapt_1_4");

  filename = sourcefiles;
  while(filename < sourcefiles + sizeof(sourcefiles) / sizeof(sourcefiles[0]))
  {
    print_expand_report("\n>>>>>>>> %s <<<<<<<<\n", *filename);
    expand_file(*filename++);
  }

  LEAVE;
  return;
}

static void
expand_file(char *filename)
{
  FILE *fd;
  char each_line[MAX_WIDTH_OF_LINE];
  char name[MAX_WIDTH_OF_LINE];
  char *current;
  ENTER("expand_file");

  depth++;
  fd = open_included_file(filename);
  if(NULL == fd)
  {
    print_expand_report("%.*s=No Such[%s] File.\n", depth, blank, filename);
    goto EXIT_NOFILE;
  }

  memset(each_line, 0, MAX_WIDTH_OF_LINE);
  if(NULL == fgets(each_line, MAX_WIDTH_OF_LINE, fd))
    warning_prompt(ADD_TRACE(warning_digest[5]));

  while(!feof(fd))
  {
    if(!depth)
      print_expand_report("%s", each_line);

    current = include_line(each_line);
    if(current)
    {
      include_filename(name, current);
      print_expand_report(" %.*s+%s\n", depth, blank, name);
      if(expand_file_filter(name))
        expand_file(name);
    }
    memset(each_line, 0, MAX_WIDTH_OF_LINE);
    if(NULL == fgets(each_line, MAX_WIDTH_OF_LINE, fd))
      ;
  }

  fclose(fd);

EXIT_NOFILE:
  depth--;
#ifdef NO_STD_HEAD_FILE
  pop_expand_stack();
#endif

  LEAVE;
  return;
}

static FILE *
open_included_file(const char *filename)
{
  FILE *fd;
  char **paths;
  char fullname[FULL_NAME_LENGTH];
  ENTER("find_quote_file");

  fd = NULL;
  paths = include_path;
  while(paths < include_path + sizeof(include_path) / sizeof(include_path[0]))
  {
    memset(fullname, 0, FULL_NAME_LENGTH);
    memcpy(fullname, *paths, strlen(*paths));
    strcat(fullname, filename);
    fd = fopen(fullname, "r");
    if(NULL != fd)
      break;
    paths++;
  }

  LEAVE;
  return fd;
}

static char *
include_line(char *line)
{
  char *index;
  register char *start;
  ENTER("include_line");

  assert(NULL != line);
  start = line;
  index = NULL;
  while(start < line + MAX_WIDTH_OF_LINE)
  {
    if('#' == *start++)
    {
      index = start;
      if(!isvalid_include(index))
        index = NULL;
      break;
    }
  }

  LEAVE;
  return index;
}

static int
isvalid_include(char *index)
{
  char line[MAX_WIDTH_OF_LINE];
  char *key_word;
  int valid;
  ENTER("isvalid_include");

  memset(line, 0, MAX_WIDTH_OF_LINE);
  memcpy(line, index, strlen(index));
  while(isblank(*index))
    index++;

  key_word = strtok(line, FILENAME_SPLITER);
  if(!strcmp(key_word, "include"))
    valid = 1;
  else
    valid = 0;

  LEAVE;
  return valid;
}

static void
include_filename(char *filename, char *start)
{
  char *index;
  char raw[MAX_WIDTH_OF_LINE];
  ENTER("include_filename");

  memset(raw, 0, MAX_WIDTH_OF_LINE);
  memcpy(raw, start, strlen(start));

  strtok(raw, FILENAME_SPLITER);
  index = strtok(NULL, FILENAME_SPLITER);

  memset(filename, 0, MAX_WIDTH_OF_LINE);
  memcpy(filename, index, strlen(index));

  LEAVE;
  return;
}

#ifdef STD_HEAD_FILE
static int
expand_file_filter(const char *filename)
{
  register char **stdname;
  int standard;
  ENTER("expand_file_filter");

  standard = 0;
  stdname = std_head;
  while(stdname < std_head + sizeof(std_head) / sizeof(std_head[0]))
  {
    if(!strcmp(filename, *stdname++))
    {
      standard = 1;
      break;
    }
  }

  LEAVE;
  return !standard;
}
#endif

#ifdef NO_STD_HEAD_FILE
static int
expand_file_filter(const char *filename)
{
  register char (*stack_top)[FILENAME_LENGTH];
  int repeated;
  ENTER("expand_file_filter");

  repeated = 0;
  stack_top = expand_stack;
  while(stack_top < expand_stack + exstack_top)
  {
    if(!strcmp(filename, *stack_top++))
    {
      repeated = 1;
      break;
    }
  }

  if(!repeated)
    memcpy(expand_stack[exstack_top++], filename, strlen(filename));

  LEAVE;
  return !repeated;
}

static void
pop_expand_stack(void)
{
  ENTER("pop_expand_stack");

  memset(expand_stack[--exstack_top], 0, FILENAME_LENGTH);

  LEAVE;
  return;
}
#endif

static void
print_expand_report(char *fmt, ...)
{
  va_list vl;
  va_list vl_cp;
  ENTER("print_expand_report");

  va_start(vl, fmt);
  va_copy(vl_cp, vl);
  vfprintf(stdout, fmt, vl);
  vfprintf(dsaaa_report, fmt, vl_cp);
  va_end(vl);
  va_end(vl_cp);

  LEAVE;
  return;
}
