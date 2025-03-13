#ifndef LIBS_HPP
# define LIBS_HPP

# include <iostream>
# include <iomanip>
# include <sstream>
# include <fstream>

# include <string>
# include <array>
# include <vector>
# include <list>
# include <map>
# include <iterator>

# include <algorithm>

# include <sys/time.h>
# include <unistd.h>
# include <string.h>

# include <cstdio>
# include <cstdlib>
# include <cstdint>
# include <cmath>

# include <raylib.h>

using std::cout;
using std::cerr;
using std::endl;

using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::ostream;

using std::string;
using std::array;
using std::vector;
using std::list;
using std::map;
using std::pair;
using std::iterator;

// ================================ SHORTHAND

# define elif else if
# define strstr stringstream

typedef bool			bit_t; /// is this even optimized ???
typedef uint8_t		byte_t;
typedef uint16_t	word_t;

#endif // LIBS_HPP
