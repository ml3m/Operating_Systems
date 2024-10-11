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

int primeChecker(int n) {
    if (n <= 1)
        return 0;
    if (n <= 3)
        return 1;
    if (n % 2 == 0 || n % 3 == 0)
        return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    }
    return 1;
}

double AVG(int n) {
    // returns the avg of the first n nmbrs
    int avg_counter = 0;
    int num = 2;
    int prime_sum = 0;

    while (avg_counter < n) {
        if (primeChecker(num)) {
            prime_sum += num;
            avg_counter++;
        }
        num++;
    }

    return (double)prime_sum/ n;
}

int main(int argc, char **argv) {

    // usage info for the user that executed the program withotu any args
    if (argc == 1) {
        printf("Usage: %s -a -b -c <value> -d -e <value>\n", argv[0]);
        printf("Example: %s -a -b -c5 -d -e 8\n", argv[0]);
        return 1; 
    }

    opterr = 0;

    int aflag = 0;
    int bflag = 0;
    int dflag = 0;
    float cvalue = 0;
    float evalue = 0;
    int index;
    int c;

    while ((c = getopt(argc, argv, "abc:de:")) != -1) {
        switch (c) {
            case 'a':
                aflag = 1;
                break;
            case 'b':
                bflag = 1;
                break;
            case 'c':
                cvalue = parse_value(optarg);
                break;
            case 'd':
                dflag = 1;
                break;
            case 'e':
                evalue = parse_value(optarg);
                break;
            case '?':
                if (optopt == 'c' || optopt == 'e')
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

    printf("aflag = %d, bflag = %d, cvalue = %.2f\n", aflag, bflag, cvalue);

    if (dflag) printf("avg of first 100 primes = %.2f\n", AVG(100));

    if (evalue != 0 && cvalue != 0) {

        double avg_of_avgs = ( AVG(cvalue) + AVG(evalue)) / 2;

        printf("evalue = %.2f\n", evalue);
        printf("AVG(%.4f, %.4f) = %f\n", AVG(cvalue) , AVG(evalue), avg_of_avgs);
    }

    for (index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);

    return 0;
}
