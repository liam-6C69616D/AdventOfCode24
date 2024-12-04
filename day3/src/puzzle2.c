#include "puzzle1.h"
#include "puzzle2.h"
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

char *readFile(char *path) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        // Error if the file cannot be opened
        perror("Error opening file");
        exit;
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);  // Get file size
    fseek(file, 0, SEEK_SET);  // Go back to the beginning of the file

    // Allocate memory to store the file contents
    char *buffer = (char *) malloc(size + 1); // +1 for the null terminator
    size_t bytesRead = fread(buffer, 1, size, file); // read from "file", into "buffer", reading "size" elements, of size 1 (char is 1 byte)#

    buffer[size] = '\0'; // Terminate the string

    fclose(file); // Close the file stream
    return buffer;
}

Match* find_all_matches(const char *text, const char *pattern, size_t* match_count) {
    regex_t regex;
    regmatch_t matches[1];  // To store the start and end positions of the match
    int ret;

    // Compile the regex with extended syntax
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        printf("Could not compile regex\n");
        exit(1);
    }

    // Start from the beginning of the text
    const char *start_ptr = text;

    size_t match_capacity = 10;  // Initial capacity for 10 matches
    Match *match_array = malloc(match_capacity * sizeof(Match));
    int offset = 0; // Keep track of offset from original string (each loop does regex on a substring of the original so the start and ends are wrong)

    while (1) {
        ret = regexec(&regex, start_ptr, 1, matches, 0);
        if (ret == REG_NOMATCH) {
            break;  // No more matches found
        } else if (ret) { // If error
            char error_buf[100];
            regerror(ret, &regex, error_buf, sizeof(error_buf));
            printf("Regex match failed: %s\n", error_buf);
            break;
        }

        if (*match_count >= match_capacity) {
            // If the array is full, resize it to hold more matches
            match_capacity *= 2;  // Double the capacity
            match_array = realloc(match_array, match_capacity * sizeof(Match));
            if (!match_array) {
                printf("Memory reallocation failed\n");
                exit(1);
            }
        }

        // Add the current match to the array
        match_array[*match_count].start = offset + matches[0].rm_so;
        match_array[*match_count].end = offset + matches[0].rm_eo;
        (*match_count)++;

        // Move the start pointer to just after the current match to continue searching
        start_ptr += matches[0].rm_eo;;  // Update the start pointer to search after the last match
        offset += matches[0].rm_eo;
    }

    // Free the compiled regex
    regfree(&regex);
    return match_array;
}

int mul(int a, int b) {
    return a * b;
}

bool enabled(Match* doMatches, size_t doMatchCount, Match* dontMatches, size_t dontMatchCount, int position) {
    int maxFound = 0;
    bool enabled = true;
    for (int i=0; i<doMatchCount; i++) {
        if (doMatches[i].end > maxFound && doMatches[i].end <= position) {
            enabled = true;
            maxFound = doMatches[i].end;
        }
    }

    for (int j=0; j<dontMatchCount; j++) {
        if (dontMatches[j].end > maxFound && dontMatches[j].end <= position) {
            enabled = false;
            maxFound = dontMatches[j].end;
        }
    }

    return enabled;
}

int main() {
    // Sample input string with multiple matches
    char *fileContents = readFile("../src/input.txt");
    
    // Regex pattern to match "mul(num, num)" where num is 1-3 digits
    const char *mulPattern = "mul\\([0-9]{1,3},[[:space:]]*[0-9]{1,3}\\)";  // Match mul(num, num)
    const char* doPattern = "do\\(\\)";
    const char* dontPattern = "don\'t\\(\\)";

    // Call function to find all matches

    size_t mulMatchCount = 0;
    Match* mulMatches = find_all_matches(fileContents, mulPattern, &mulMatchCount);

    size_t doMatchCount = 0;
    size_t dontMatchCount = 0;
    Match* doMatches = find_all_matches(fileContents, doPattern, &doMatchCount);
    Match* dontMatches = find_all_matches(fileContents, dontPattern, &dontMatchCount);
    
    int sum = 0;
    for (int i=0; i<mulMatchCount; i++) {
        if (enabled(doMatches, doMatchCount, dontMatches, dontMatchCount, mulMatches[i].start)) {
            int length = mulMatches[i].end - mulMatches[i].start;

            // Allocate memory for the substring
            char substring[length + 1]; // +1 for the null terminator

            // Copy the substring to the new variable using strncpy
            strncpy(substring, fileContents + mulMatches[i].start, length);

            int num1, num2;
            sscanf(substring, "mul(%d,%d)", &num1, &num2);
            
            sum += mul(num1, num2);
        }
    }

    printf("%d", sum);

    return 0;
}