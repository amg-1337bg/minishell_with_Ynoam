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
#define Minishell "minishell > "

#include "parsing.h"
#include "../executing/executing.h"