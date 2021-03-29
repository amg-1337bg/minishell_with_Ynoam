#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/errno.h>
#include <termios.h>
#include "../libft/libft.h"

#define binPath "/bin/pwd"
#define Minishell "\033[38;5;6mprompt >\e[m "
#define CMD_NOT_FOUND "command not found"
#define NO_SUCH_FILE_OR_DIR "No such file or directory"

#include "parsing.h"
#include "../executing/executing.h"