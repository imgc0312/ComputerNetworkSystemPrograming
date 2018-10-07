/* shell.h : function prototypes for all functions in shell exercise */

#define FALSE 0
#define TRUE (!FALSE)
#define SIZE 1024

char ** parse(char *);		/* tokenise a string */
void free_argv(char **);	/* free argv array. */
void run_command(char **);	/* do the fork, exec stuff */
int is_background(char **);	/* check for & at end */
int is_builtin(char *);		/* check for in-built keywords */
int do_builtin(char **);	/* and then do them */
int redirect_out(char **);
int redirect_in(char **);
int pipe_present(char **);
void pipe_and_exec(char **);

#include <string.h>
#include <signal.h>
sigset_t oldset;

#include <sys/times.h>
struct tms tms_o;

void set_timer(void);
void stop_timer(void);

