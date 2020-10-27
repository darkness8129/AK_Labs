#include <stdio.h>
#include <unistd.h>
#include <map>
#include <string>
#include <getopt.h>

using namespace std;

int main(int argc, char *argv[]) {
    int result = 0;
    map<string, bool> used;

    int option_index = -1;

    // short options 
    const char *short_options = "vhltdV::";

    // long options
    const struct option long_options[] = {
            {"version",  0, NULL, 'v'},
            {"help",  0, NULL, 'h'},
            {"list", 0, NULL, 'l'},  
            {"test", 0, NULL, 't'},    
            {"deploy", 0, NULL, 'd'},  
            {"value", 2, NULL, 'V'},
            {NULL,0,NULL,0}
    };

    while ((result = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (result) {
            // Version key
            case 'v': {
                if (used["v"] == false) {
                    printf("Arg: Version\n");
                    used["v"] = true;
                    break;
                }
                break;
            }
            // Help key
            case 'h': {
                if (used["h"] == false) {
                    printf("Arg: Help\n");
                    used["h"] = true;
                    break;
                }
                break;
            }
            // List key
            case 'l': {
                if (used["l"] == false) {
                    printf("Arg: List\n");
                    used["l"] = true;
                    break;
                }
                break;
            }
            // Test key
            case 't': {
                if (used["t"] == false) {
                    printf("Arg: Test\n");
                    used["t"] = true;
                    break;
                }
                break;
            }
            // Deploy key
            case 'd': {
                if (used["d"] == false) {
                    printf("Arg: Deploy\n");
                    used["d"] = true;
                    break;
                }
                break;
            }
            // Value key
            case 'V': {
		        if (used["V"] == false) {
			        if (optarg == NULL) {
				        printf("Arg: Value without parameter\n"); 
				        used["V"] = true;
			        }
                    else {
				        printf("Arg: Value = %s\n", optarg); 
				        used["V"] = true;
			        }
			        break;
		        }
		        break;
            }
            // Unknown key
            case '?': default: {
                printf("Error: Key %c is unknown!\n", result);
                break;
            }
        }
        option_index = -1;
    }
}

