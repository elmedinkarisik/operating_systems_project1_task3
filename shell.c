/***************************************************************************//**

  @file         shell.c

  @author       Dinko Omeragic, Elmedin Karisik, Faris Sahovic, Mirza Niksic

  @date         Friday,  24 April 2020

  @brief        LSH (Libstephen SHell)

*******************************************************************************/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
/*
  Function Declarations for additional functions
*/
int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);
int to_upper_case(FILE *file);
int to_lower_case(FILE *file);
int to_initcap_file(FILE *fp);
int del(FILE *fp);
int tolower(int argument);
/*
  Function Declarations for builtin shell commands:
 */
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_countChar(char **args);
int lsh_countLines(char **args);
int lsh_countWords(char **args);
int lsh_camelCase(char **args);
int lsh_countOccur(char **args);
int lsh_toUpperCase(char **args);
int lsh_toLowerCase(char **args);
/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
  "help",
  "exit",
  "countChar",
  "countLines",
  "countWords",
  "camelCase",
  "countOccur",
  "toUpperCase",
  "toLowerCase"
};

int (*builtin_func[]) (char **) = {
  &lsh_help,
  &lsh_exit,
  &lsh_countChar,
  &lsh_countLines,
  &lsh_countWords,
  &lsh_camelCase,
  &lsh_countOccur,
  &lsh_toUpperCase,
  &lsh_toLowerCase
};

int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/

/**
   @brief Bultin command: to lower case.
   @param args List of args.  args[1] is the file.
   @return Always returns 1, to continue executing.
 */
int lsh_toLowerCase(char **args){
  FILE * file;

  /* Open source files in 'r' mode */
  file = fopen(args[1], "r+");

  /* Check if file opened successfully */
  if (file == NULL)
  {
    printf("Cannot open the file or no file was passed");
  }
  
  /* Use the additonal function to change all characters to lower case in the file */
  int k = to_lower_case(file);

  /* Check if the change was successfull */
  if (k == 1)    
  {    
    printf("Successfully executed given command\n");
  }
  else
  {
    printf("Failed to execute command\n");
  }

  /* Close files to release resources */
  fclose(file);
  return 1;
}

/**
   @brief Bultin command: to lower case.
   @param args List of args.  args[1] is the file.
   @return Always returns 1, to continue executing.
 */
int lsh_toUpperCase(char **args){
  FILE * file;

  /* Open source files in 'r+' mode */
  file = fopen(args[1], "r+");

  /* Check if file opened successfully */
  if (file == NULL)
  {
    printf("cannot open the file ");
  }

  /* Use the additonal function to change all characters to upper case in the file */
  int k = to_upper_case(file);

  /* Check if the change was successfull */
  if (k == 1)    
  {    
    printf("Successfully executed given command\n");
  }
  else
  {
    printf("Failed to execute command\n");
  }

  /* Close files to release resources */
  fclose(file);
  return 1;
}

/**
   @brief Bultin command: to count occurences of a word in a file.
   @param args List of args.  args[1] is the file. args[2] is the word.
   @return Always returns 1, to continue executing.
 */
int lsh_countOccur(char **args){
  FILE * file;
  char str[100];
  char *word = args[2];
  char *pos;
  int index, count, j;
  count = 0;
  
  /* Open source files in 'r+' mode */
  file = fopen(args[1], "r+");

  /* Check if file opened successfully */
  if (file == NULL)
  {
    printf("Cannot open the file or no file was passed");
  }

  // Read line from file till end of file.
  while ((fgets(str, 100, file)) != NULL)
  {
    j=0;
    while(j<sizeof(str)){
      if(str[j]>='A' && str[j]<='Z'){
    	str[j] = tolower(str[j]);
        }
      j++; 
    }
    index = 0;

    // Find next occurrence of word in str
    while ((pos = strstr(str + index, word)) != NULL)
    {
      /* Index of word in str is memory address of pos - memory address of str. */
      index = (pos - str) + 1;
      count++;
    }
  }
  /* print the number of occurences found */
  printf("'%s' is found %d times in file.\n", word, count);

  /* Close files to release resources */
  fclose(file);
  return 1;
}

/**
   @brief Builtin command: change all words to camelCase.
   @param args List of args.  args[1] is the file. 
   @return Always returns 1, to continue executing.
 */
int lsh_camelCase(char **args){
  FILE * file;
  int p;

  /* Open source files in 'r+' mode */
  file = fopen(args[1], "r+");

  /* Check if file opened successfully */
  if (file == NULL)
  {
    printf("Cannot open the file or no file was passed");
  }
  
  /* Use the additonal function to change all characters to upper case in the file */
  p= to_lower_case(file);

  /* Close files to release resources */
  fclose(file);

  /* Open source files in 'r+' mode */  
  file = fopen(args[1], "r+");

  /* capitalizes first letter of every word */
  p = to_initcap_file(file);

  /* Close files to release resources */
  fclose(file);

  /* Open source files in 'r+' mode */
  file = fopen(args[1], "r+");

  /* Use the additonal function to delete all non-alphanumeric characters in the file */
  int k = del(file);

  /* Check if the change was successfull */
  if (p == 1 && k==1)    
  {    
    printf("Successfully executed given command\n");
  }
  else
  {
    printf("Failed to execute command\n");
  }

  /* Close files to release resources */
  fclose(file);

  return 1;
}

/**
   @brief Builtin command: count words.
   @param args List of args.  args[1] is the file. 
   @return Always returns 1, to continue executing.
 */
int lsh_countWords(char **args){
  FILE * file;

  char ch;
  int characters, words;

  /* Open source files in 'r' mode */
  file = fopen(args[1], "r");


  /* Check if file opened successfully */
  if (file == NULL)
  {
    printf("\nUnable to open file or no file was passed.\n");
    printf("Please check if file exists and you have read privilege.\n");
   }

  /* Logic to count words */
  words = characters = 0;
  while ((ch = fgetc(file)) != EOF)
  {

  characters++;
    /* Check words */
    if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0') words++;
  }
  /* Increment words */
  if (characters > 0) words++;
  
  /* Print file statistics */
  printf("\n");
  printf("Total number of words in given file = %d\n", words - 1);

  /* Close files to release resources */
  fclose(file);

  return 1;
}

/**
   @brief Builtin command: count lines.
   @param args List of args.  args[1] is the file. 
   @return Always returns 1, to continue executing.
 */
int lsh_countLines(char **args){
  FILE * file;
  char ch;
  int characters, lines;

  /* Open source files in 'r' mode */
  file = fopen(args[1], "r");


  /* Check if file opened successfully */
  if (file == NULL)
  {
    printf("\nUnable to open file or no file was given.\n");
    printf("Please check if file exists and you have read privilege.\n");     	
  }

  /* Logic to count number of lines */
  characters = lines = 0;
  while ((ch = fgetc(file)) != EOF)
  {
    characters++;

    /* Check new line */
    if (ch == '\n' || ch == '\0') lines++;
  }

  /* Increment lines */
  if (characters > 0) lines++;

  /* Print number of lines */
  printf("\n");
  printf("Total number of lines in given file = %d\n", lines - 1);


  /* Close files to release resources */
  fclose(file);
  return 1;
}

/**
   @brief Builtin command: count characters.
   @param args List of args.  args[1] is the file. 
   @return Always returns 1, to continue executing.
 */
int lsh_countChar(char **args){
  FILE * file;

  char ch;
  int characters;

  /* Open source files in 'r' mode */
  file = fopen(args[1], "r");


  /* Check if file opened successfully */
  if (file == NULL)
    {
      printf("\nUnable to open file or no file is passed.\n");
      printf("Please check if file exists and you have read privilege.\n");

       	
     }

  /* Logic to count characters */
  characters = 0;
  while ((ch = fgetc(file)) != EOF)
  {
     characters++;  
   }

  /* Print number of characters */
  printf("\n");
  printf("Total characters in given file = %d\n", characters-1);

  /* Close files to release resources */
  fclose(file);	
  return 1;
}



/**
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
int lsh_help(char **args)
{
  int i;
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < lsh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
int lsh_exit(char **args)
{
  return 0;
}

/*
  Builtin function implementations.
*/

/**
   @brief Additional command: delete all non-alphanumeric characters in a file.
   @param fp fp is the file. 
   @return Always returns 1, to continue executing.
 */
int del(FILE *fp){
  char c;
  int j=0, i=0;
  char aa[1000000];

  c=fgetc(fp);

  /* Logic for searching and deleting non-alphanumeric characters */
  while(c != EOF){ 
  if ((c < 'a' && c > 'Z') || (c < 'A' && c > '9') || (c < '0') || (c > 'z')){
	j++; c = fgetc(fp);
    continue;
  } 
  aa[i++]=c;
  c=fgetc(fp);
  } 
  fseek(fp,0L,0);
  int h=0;

  while(h<i){
    fputc(aa[h++],fp);
  }
  
  /* Delete the unnecessary part of the file */
  int charsToDelete = j;
  fseeko(fp,-charsToDelete,SEEK_END);
  int position = ftello(fp);
  ftruncate(fileno(fp), position);
  return 1;
}

/**
   @brief Additional command: capitalize first letter in each word in a file.
   @param fp fp is the file. 
   @return Always returns 1, to continue executing.
 */
int to_initcap_file(FILE *fp){
  char c;

  c = fgetc(fp);

  /* Check the first character and change if necessary */
  if (c >= 'a' && c <= 'z')
  {
    fseek(fp, -1L, 1);
    fputc(c - 32, fp);
  }

  /* Check the rest of characters in the file */  
  while(c != EOF)    
  {
    if (c == ' ' || c == '\n')
    {
      c = fgetc(fp);
      if (c >= 'a' && c <= 'z')
      {
        fseek(fp, -1L, 1);
        fputc(c - 32, fp);
        }
      }
      else
      {
        c = fgetc(fp);
      }
  }
  return 1;
}

/**
   @brief Additional command: change all characters to lower case in a file.
   @param fp fp is the file. 
   @return Always returns 1, to continue executing.
 */
int to_lower_case(FILE *file){
  char c;

  c = fgetc(file);

  /* Check the first character and change if necessary */
  if (c >= 'A' && c <= 'Z')
  {
    fseek(file, -1L, 1);
    putc(c + 32, file);
  }

  /* Check the rest of characters in the file */
  while(c != EOF){    
    c = fgetc(file);
    if (c >= 'A' && c <= 'Z')
      {
      fseek(file, -1L, 1);
      fputc(c + 32, file);
      }
  }
  return 1;
}

/**
   @brief Additional command: change all characters to upper case in a file.
   @param file File is the file.
   @return Always returns 1, to continue executing.
 */
int to_upper_case(FILE *file){
  char c;
  
  c = fgetc(file);
  
  /* Check the first character and change if necessary */
  if (c >= 'a' && c <= 'z')
  {
    fseek(file, -1L, 1);
    putc(c - 32, file);
  }
  
  /* Check the rest of characters in the file */
  while(c != EOF){    
    c = fgetc(file);
    if (c >= 'a' && c <= 'z')
      {
      fseek(file, -1L, 1);
      fputc(c - 32, file);
      }
  }
  return 1;
}




/**
  @brief Launch a program and wait for it to terminate.
  @param args Null terminated list of arguments (including program).
  @return Always returns 1, to continue execution.
 */
int lsh_launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {

    // Child process
    if (execvp(args[0], args) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {

    // Error forking
    perror("lsh");
  } else {

    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int lsh_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < lsh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return lsh_launch(args);
}

#define LSH_RL_BUFSIZE 1024
/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *lsh_read_line(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **lsh_split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

/**
   @brief Loop getting input and executing it.
 */
void lsh_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);

    free(line);
    free(args);
  } while (status);
}

/**
   @brief Main entry point.
   @param argc Argument count.
   @param argv Argument vector.
   @return status code
 */
int main(int argc, char **argv)
{
  // Load config files, if any.

  // Run command loop.
  lsh_loop();

  // Perform any shutdown/cleanup.

  return EXIT_SUCCESS;
}
