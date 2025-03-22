
# Defines executable file name
PROJECT_NAME	= ToyEngine

# Define all source files required
INC_DIR = incs
SRC_DIR = srcs
OBJ_DIR = objs
LOG_DIR = logs

# Defines the path for raylib, if different than /usr/local
# comment out if uneeded
CUSTOM_RALIB_PATH = /home/.brew

# Defines compiler flags:
#  -O0									no optimization
#  -Og									optimization level for debugging
#  -O1									optimization level 1 (basic)
#  -O2									optimization level 2 (medium)
#  -O3									optimization level 3 (maximum)
#  -Os									optimization for program size
#  -Ofast								optimization for program speed
#  -g										include debug information on compilation
#  -s										strip unnecesiary data from build -> do not use in debug builds
#  -Wall								turns on most, but not all, compiler warnings
#  -std=c99							defines C language mode (standard C from 1999 revision)
#  -std=gnu99						defines C language mode (GNU C from 1999 revision)
#  -Wno-missing-braces	ignore invalid warning (GCC bug 53119)
#  -D_DEFAULT_SOURCE		use with -std=c99 on Linux and PLATFORM_WEB, required for timespec
CFLAGS +=	-Wall \
					-Werror \
					-Wextra \
					-Wshadow \
					-std=c++14 \
					-D_DEFAULT_SOURCE \
					-Wno-missing-braces \
