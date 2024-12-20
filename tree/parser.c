#include "ft_system.h"



#define TEST_PARSE 1
#if TEST_PARSE
int main() {
    char **argv = {"infile", "ls -l", "cat", "out"};
    t_info *info = system_init(NULL);
    
    
    return 0;
}
#endif