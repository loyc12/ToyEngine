
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

# Possible compiler flags:

#  -O0									no optimization
#  -Og									optimization level for debugging
#  -O1									optimization level 1 (basic)
#  -O2									optimization level 2 (medium)
#  -O3									optimization level 3 (maximum)
#  -Os									optimization for program size
#  -Ofast								optimization for program speed
#  -g										include debug information on compilation
#  -s										strip unnecesiary data from build -> do not use in debug builds

#  -fsanitize=address		enable address sanitizer
#  -fsanitize=leak			enable leak sanitizer
#  -fsanitize=undefined	enable undefined behavior sanitizer
#  -fsanitize=thread		enable thread sanitizer
#  -fsanitize=memory		enable memory sanitizer
#  -fsanitize=pointer-subtract	enable pointer subtract sanitizer
#  -fsanitize=pointer-compare		enable pointer compare sanitizer
#  -fsanitize=pointer-overflow	enable pointer overflow sanitizer

#  -Wall								turns on most, but not all, compiler warnings
#  -Werror							treats all warnings as errors
#  -Wextra							enables some extra warning flags that are not enabled by -Wall
#  -Wshadow							warns whenever a local variable shadows another local variable
#  -Wno-missing-braces	ignore invalid warning (GCC bug 53119)
#  -std=c++98						defines C++ language mode (standard C++ from 1998 revision)
#  -std=c++11						defines C++ language mode (standard C++ from 2011 revision)
#  -std=c++14						defines C++ language mode (standard C++ from 2014 revision)
#  -std=c++17						defines C++ language mode (standard C++ from 2017 revision)
#  -std=c++20						defines C++ language mode (standard C++ from 2020 revision)
#  -std=gnu++98					defines C++ language mode (GNU C++ from 1998 revision)
#  -std=gnu++11					defines C++ language mode (GNU C++ from 2011 revision)
#  -std=gnu++14					defines C++ language mode (GNU C++ from 2014 revision)
#  -std=gnu++17					defines C++ language mode (GNU C++ from 2017 revision)
#  -std=gnu++20					defines C++ language mode (GNU C++ from 2020 revision)

#  -D_DEFAULT_SOURCE		use with -std=c99 on Linux and PLATFORM_WEB, required for timespec

CFLAGS +=	-std=gnu++20 \
					-Wall \
					-Werror \
					-Wextra \
					-Wshadow \
					-Wno-missing-braces \
