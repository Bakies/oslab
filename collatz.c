#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main() { 
	int n; 
	printf("Enter the number to start with: ");
	scanf("%d", &n);

	pid_t pid = fork();

	if (pid == 0) { 
		// This is the child process
		printf("%d ", n);
		while (n != 1) {
			if (n % 2 == 0) { 
				n = n / 2;
			} else { 
				n = 3 * n + 1; 
			}
			printf("%d ", n);
		}
	} else { 
		// This is the parent process
		wait(); // This will block until child is terminated

	}

}
