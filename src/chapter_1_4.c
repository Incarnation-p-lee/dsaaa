/*--------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                               */
/*-DATE:        10272013                                        */
/*-WHAT:        Homework chapter 1.4                            */
/*-REVISION:                                                    */
/*- DATE ------------------------ DESCRIPTION ------------------*/
/*- 10272013    CHAPTER 1-4                                    -*/
/*--------------------------------------------------------------*/
void
chapt_1_4(void)
{
  entering_frame("chapt_1_4");

  report_header1_4(stdout);
  report_header1_4(hwork_rept);
  dochapter1_4();

  leaving_frame();
  return;
}


static void
report_header1_4(FILE *fd)
{
  time_t date;
  entering_frame("report_header");

  fprintf(fd, "\n-----------------------------");
  fprintf(fd, "Chapter 1-4");
  fprintf(fd, "-------------------------------\n\n");
  fprintf(fd, 
    "                               Expanding #include\n\n");
  fprintf(fd, "TIME: %s", ctime((const time_t *)&date));
  
  leaving_frame();
  return;
}

static void
dochapter1_4()
{
  register char **filename;
  char *sourcefiles[] = {
    "main.c",
    "chapter_1.c",
    "externals.h",
  };
  entering_frame("dochapter1_4");

  filename = sourcefiles;
  while(filename < 
    sourcefiles + sizeof(sourcefiles) / sizeof(sourcefiles[0]))
  {
	  print_result("\n>>>>>>>> %s <<<<<<<<\n", *filename);
    expand_file(*filename++);
  }
  
  leaving_frame();
  return;
}

static void
expand_file(char *filename)
{
  FILE *fd;
  char each_line[MAX_WIDTH_OF_LINE];
  char name[MAX_WIDTH_OF_LINE];
  char *current;
  entering_frame("expand_file");

  depth++;
  fd = find_quoted_file(filename);
  if(NULL == fd)
  {
    print_result("%.*s=No Such[%s] File.\n", 
      depth, blank, filename);
    goto LEAVE;
  }

  memset(each_line, 0, MAX_WIDTH_OF_LINE);
  fgets(each_line, MAX_WIDTH_OF_LINE, fd);
  while(!feof(fd))
  {
    if(!depth)
      print_result("%s", each_line);

    current = isinclude(each_line);
    if(current)
    {
      include_name(name, current);
      print_result(" %.*s+%s\n", depth, blank, name);
      if(isvalid_headfile(name))
        expand_file(name);
    }
    memset(each_line, 0, MAX_WIDTH_OF_LINE);
    fgets(each_line, MAX_WIDTH_OF_LINE, fd);
  } 
  
  fclose(fd);

LEAVE:
  depth--;
#ifdef NO_STD_HEAD_FILE
  pop_expand_stack();
#endif

  leaving_frame();
  return;
}

static FILE *
find_quoted_file(const char *filename)
{
  FILE *fd;
  char **paths;
  char fullname[FULL_NAME_LENGTH];
  entering_frame("find_quote_file");

  fd = NULL;
  paths = include_path;
  while(paths < include_path + 
    sizeof(include_path) / sizeof(include_path[0]))
  {
    memset(fullname, 0, FULL_NAME_LENGTH);
    memcpy(fullname, *paths, strlen(*paths));
    strcat(fullname, filename);
    fd = fopen(fullname, "r");
    if(NULL != fd)
      break;
    paths++;
  }

  leaving_frame();
  return fd;
}

static char *
isinclude(char *line)
{
  char *index;
  register char *start;
  entering_frame("isinclude");
  
  assert(NULL != line);
  start = line;
  index = NULL;
  while(start < line + MAX_WIDTH_OF_LINE)
  {
    if('#' == *start++)
    {
      index = start;
      if(!keyword_valid(index))
        index = NULL;
      break;
    }
  }

  leaving_frame();
  return index;
}

static int
keyword_valid(char *index)
{
  char line[MAX_WIDTH_OF_LINE];
  char *key_word;
  int valid;
  entering_frame("keyword_valid");

  memset(line, 0, MAX_WIDTH_OF_LINE);
  memcpy(line, index, strlen(index));
  while(isblank(*index))
    index++;

  key_word = strtok(line, FILENAME_SPLITER);
  if(!strcmp(key_word, "include"))
    valid = 1;
  else
    valid = 0;

  leaving_frame();
  return valid;
}

static void
include_name(char *filename, char *start)
{
  char *index;
  char raw[MAX_WIDTH_OF_LINE];
  entering_frame("include_name");

  memset(raw, 0, MAX_WIDTH_OF_LINE);
  memcpy(raw, start, strlen(start));

  strtok(raw, FILENAME_SPLITER);
  index = strtok(NULL, FILENAME_SPLITER);

  memset(filename, 0, MAX_WIDTH_OF_LINE);
  memcpy(filename, index, strlen(index));

  leaving_frame();
  return;
}

#ifdef STD_HEAD_FILE
static int
isvalid_headfile(const char *filename)
{
  register char **stdname;
  int standard;
  entering_frame("isvalid_headfile");

  standard = 0;
  stdname = std_head;
  while(stdname < std_head + 
    sizeof(std_head) / sizeof(std_head[0]))
  {
    if(!strcmp(filename, *stdname++))
    {
      standard = 1;
      break;
    }
  }

  leaving_frame();
  return !standard;
}
#endif

#ifdef NO_STD_HEAD_FILE
static int
isvalid_headfile(const char *filename)
{
  register char (*stack_top)[FILENAME_LENGTH];
  int repeated;
  entering_frame("isvalid_headfile");

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

  leaving_frame();
  return !repeated;
}

static void
pop_expand_stack(void)
{
  entering_frame("pop_expand_stack");

  memset(expand_stack[--exstack_top], 0, FILENAME_LENGTH);
  
  leaving_frame();
  return;
}
#endif

static void
print_result(char *fmt, ...)
{
  va_list vl;
  va_list vl_cp;
  entering_frame("print_result");

  va_start(vl, fmt);
  va_copy(vl_cp, vl);
  vfprintf(stdout, fmt, vl);
  vfprintf(hwork_rept, fmt, vl_cp);
	va_end(vl);
  va_end(vl_cp);

  leaving_frame();
  return;
}
