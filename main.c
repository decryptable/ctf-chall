#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define XOR_KEY 0x42

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

unsigned char enc1[] = {0x04, 0x0e, 0x03, 0x05, 0x39};
unsigned char enc2[] = {0x23, 0x30, 0x23, 0x1d, 0x23, 0x30, 0x23, 0x1d};
unsigned char enc3[] = {0x7c, 0x6d, 0x6d, 0x7e};
unsigned char enc4[] = {0x3f};

const char* decoys[] = {
    "FLAG{fake_flag_123}",
    "CTF{not_the_flag}",
    "PASSWORD_HERE",
    "SECRET_KEY_456"
};

void clear_screen() {
    printf("\033c");
}

void loading_animation() {
    printf(CYAN BOLD "\n  CTF REVERSE ENGINEERING CHALLENGE\n" RESET);
    printf(YELLOW "  [");
    for(int i = 0; i < 45; i++) {
        printf("=");
        fflush(stdout);
        usleep(25000);
    }
    printf("]\n\n" RESET);
}

void system_check() {
    printf(CYAN "  System Security Check\n" RESET);
    printf(CYAN "  ---------------------\n" RESET);
    
    const char* checks[] = {
        "Checking memory integrity",
        "Scanning for debuggers",
        "Verifying system state",
        "Initializing encryption"
    };
    
    for(int i = 0; i < 4; i++) {
        printf(WHITE "  > %s", checks[i]);
        fflush(stdout);
        for(int j = 0; j < 3; j++) {
            printf(".");
            fflush(stdout);
            usleep(200000);
        }
        printf(GREEN BOLD " [OK]\n" RESET);
        usleep(100000);
    }
    printf("\n");
}

int check_debugger() {
    clock_t start = clock();
    for(volatile int i = 0; i < 1000000; i++);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    return (time_taken > 0.5);
}

void decode(unsigned char* data, int len, unsigned char key) {
    for(int i = 0; i < len; i++) {
        data[i] ^= key;
    }
}

void assemble_flag(char* buffer) {
    unsigned char part1[6], part2[9], part3[5], part4[2];
    
    memcpy(part1, enc1, sizeof(enc1));
    memcpy(part2, enc2, sizeof(enc2));
    memcpy(part3, enc3, sizeof(enc3));
    memcpy(part4, enc4, sizeof(enc4));
    
    decode(part1, sizeof(enc1), XOR_KEY);
    decode(part2, sizeof(enc2), XOR_KEY);
    decode(part3, sizeof(enc3), XOR_KEY);
    decode(part4, sizeof(enc4), XOR_KEY);
    
    int pos = 0;
    memcpy(buffer + pos, part1, sizeof(enc1)); pos += sizeof(enc1);
    memcpy(buffer + pos, part2, sizeof(enc2)); pos += sizeof(enc2);
    memcpy(buffer + pos, part3, sizeof(enc3)); pos += sizeof(enc3);
    memcpy(buffer + pos, part4, sizeof(enc4)); pos += sizeof(enc4);
    buffer[pos] = '\0';
    
    memset(part1, 0, sizeof(part1));
    memset(part2, 0, sizeof(part2));
    memset(part3, 0, sizeof(part3));
    memset(part4, 0, sizeof(part4));
}

int verify_input(const char* input) {
    char flag[256] = {0};
    assemble_flag(flag);
    int result = strcmp(input, flag);
    memset(flag, 0, sizeof(flag));
    return (result == 0);
}

void success_animation() {
    clear_screen();
    printf("\n\n");
    printf(GREEN BOLD "  ========================================\n");
    printf("           SUCCESS! FLAG VERIFIED!        \n");
    printf("  ========================================\n\n" RESET);
    
    printf(WHITE "  You successfully reversed the challenge!\n\n");
    printf("  Skills demonstrated:\n" RESET);
    printf(GREEN "    * Binary analysis\n");
    printf("    * XOR decryption\n");
    printf("    * Memory forensics\n");
    printf("    * Debugging techniques\n\n" RESET);
}

void fail_animation() {
    printf("\n");
    printf(RED BOLD "  ========================================\n");
    printf("            X ACCESS DENIED X            \n");
    printf("  ========================================\n\n" RESET);
    
    printf(YELLOW "  Hint: Try analyzing the binary with:\n" RESET);
    printf(WHITE "    * gdb / radare2 / ghidra\n");
    printf("    * strings / hexdump\n");
    printf("    * ltrace / strace\n\n" RESET);
}

int main() {
    clear_screen();
    loading_animation();
    
    if(check_debugger()) {
        printf(RED BOLD "\n  ! DEBUGGER DETECTED !\n" RESET);
        printf(RED "  System compromised. Exiting...\n\n" RESET);
        return 1;
    }
    
    system_check();
    
    printf(CYAN "  Enter Access Code\n" RESET);
    printf(CYAN "  -----------------\n" RESET);
    printf(WHITE "  FLAG >> " RESET);
    
    char input[256];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    
    printf(YELLOW "\n  Verifying" RESET);
    for(int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        usleep(300000);
    }
    printf("\n");
    
    if(verify_input(input)) {
        success_animation();
        return 0;
    } else {
        fail_animation();
        return 1;
    }
}