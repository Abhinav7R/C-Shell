#ifndef HEADERS_H_
#define HEADERS_H_

#define _GNU_SOURCE 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <termios.h>
#include <ctype.h>
#include <fcntl.h>


#include "queue.h"

#include "prompt.h"
#include "input.h"
#include "warp.h"
#include "peek.h"
#include "seek.h"
#include "proclore.h"
#include "fgbg.h"
#include "pastevents.h"
#include "execute.h"
#include "activities.h"
#include "ping.h"
#include "fg.h"
#include "bg.h"
#include "iMan.h"
#include "neonate.h"
#include "iopipe.h"

#endif