#include <stdio.h>
#include <poll.h>

int main() {
    struct pollfd pfd;
    char input[100];
    
    pfd.fd = 0;  // stdin (keyboard)
    pfd.events = POLLIN;
    
    printf("Type something (5 sec timeout):\n");
    
    if (poll(&pfd, 1, 5000) > 0) {
        fgets(input, 100, stdin);
        printf("You typed: %s", input);
    } else {
        printf("Timeout! No input.\n");
    }
    
    return 0;
}
/*
Start
  ↓
Print "Type something (5 sec timeout):"
  ↓
Create pollfd structure:
  pfd.fd = 0;        // Watch stdin (keyboard)
  pfd.events = POLLIN;  // Wait for readable
  ↓
poll(&pfd, 1, 5000);  // ⏸️ BLOCKING HAPPENS HERE
  ↓
  ╔════════════════════════════════╗
  ║   ⏸️ PROGRAM PAUSED HERE       ║
  ║   Waiting for 5000 ms (5 sec)..║
  ║   OR keyboard input...         ║
  ╚════════════════════════════════╝
  ↓
5000 ms passed? ←──Yes──→ Print "Timeout! No input."
  ↓ No              ↓
Keyboard input?     End
  ↓
Yes
  ↓
pfd.revents contains POLLIN
  ↓
Read with fgets(input, 100, stdin);
  ↓
Print "You typed: ..."
  ↓
End
*/