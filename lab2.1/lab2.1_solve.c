// handle for hexa and it represents any string that doesn't display digits as 0
// handles floats too, can handle negative hex too 
// Usage: 
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

float parse_value(const char *optarg) {
    //hexa checking 
    if (optarg[0] == '0' && (optarg[1] == 'x' || optarg[1] == 'X')) {
        return (float)strtol(optarg, NULL, 16);
    } 
    return atof(optarg);
}

int main(int argc, char **argv) {

    opterr = 0;
    float sum = 0;

    int aflag = 0;
    int bflag = 0;
    int cflag = 0;
    float avalue = 0;
    float bvalue = 0;
    float cvalue = 0;
    int index;
    int c;

    // usage info for the user that executed the program withotu any args
    if (argc == 1) {
        printf("Usage: %s -a <value> -b <value> -c <value>\n", argv[0]);
        printf("Example: %s -a 12 -b 24 -c 12\n", argv[0]);
        return 1; 
    }

    while ((c = getopt(argc, argv, "a:b:c:")) != -1) {
        switch (c) {
            case 'a':
                aflag = 1;
                avalue = parse_value(optarg);
                break;
            case 'b':
                bflag = 1;
                bvalue = parse_value(optarg);
                break;
            case 'c':
                cflag = 1;
                cvalue = parse_value(optarg);
                break;
            case '?':
                if (optopt == 'a' || 
                    optopt == 'b' || 
                    optopt == 'c')
                    // in case of no number provided after flag. 
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort();
        }
    }

    sum = avalue + bvalue + cvalue;
    printf("aflag = %d, avalue = %.2f\n", aflag, avalue);
    printf("bflag = %d, bvalue = %.2f\n", bflag, bvalue);
    printf("cflag = %d, cvalue = %.2f\n", cflag, cvalue);
    printf("sum = %.2f\n", sum);

    for (index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);

    return 0;
}
