
# Defines executable file name
PROJECT_NAME	= ToyEngine

# Build mode for project: DEBUG or RELEASE
BUILD_MODE		= DEBUG

# Define all source files required
INC_DIR = incs
SRC_DIR = srcs
OBJ_DIR = objs
LOG_DIR = logs

# Defines the path for raylib, if different than /usr/local
# comment out if uneeded
CUSTOM_RALIB_PATH = /home/.brew

# Defines compiler flags:
#  -O0									defines optimization level (no optimizations, better for debugging)
#  -O1									defines optimization level (basic optimizations)
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
