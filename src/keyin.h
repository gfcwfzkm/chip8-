#ifdef _WIN32
	#include <conio.h>

	#define CH8_KBHIT   kbhit
	#define CH8_GETCH   getch
#elif __linux__
	/**
	 Linux (POSIX) implementation of _kbhit().
	 Morgan McGuire, morgan@cs.brown.edu
	 */
	#include <stdio.h>
	#include <sys/select.h>
	#include <termios.h>
	#include <stropts.h>

	static int CH8_KBHIT()
	{
    	static const int STDIN = 0;
    	static bool initialized = false;

    	if (! initialized) {
    	    // Use termios to turn off line buffering
    	    termios term;
    	    tcgetattr(STDIN, &term);
    	    term.c_lflag &= ~ICANON;
    	    tcsetattr(STDIN, TCSANOW, &term);
    	    setbuf(stdin, NULL);
    	    initialized = true;
    	}

    	int bytesWaiting;
    	ioctl(STDIN, FIONREAD, &bytesWaiting);
    	return bytesWaiting;
	}
	static int CH8_GETCH()
	{
		static int ch = -1, fd = 0;
		struct termios neu, alt;
		fd = fileno(stdin);
		tcgetattr(fd, &alt);
		neu = alt;
		neu.c_lflag &= ~(ICANON|ECHO);
		tcsetattr(fd, TCSANOW, &neu);
		ch = getchar();
		tcsetattr(fd, TCSANOW, &alt);
		return ch;
	}
#elif MAC_OS_X
	/* Codesnippets for getch() and kbhit() from internet */
	/* Source: https://www.c-plusplus.net/forum/39509     */
	/* DrGreenthumb and anonymous, 2001, 2002             */
	#include <termios.h>
	#include <string.h>

	static int CH8_GETCH()
	{
		static int ch = -1, fd = 0;
		struct termios neu, alt;
		fd = fileno(stdin);
		tcgetattr(fd, &alt);
		neu = alt;
		neu.c_lflag &= ~(ICANON|ECHO);
		tcsetattr(fd, TCSANOW, &neu);
		ch = getchar();
		tcsetattr(fd, TCSANOW, &alt);
		return ch;
	}

	static int CH8_KBHIT(void) {
		struct termios term, oterm;
		int fd = 0;
		int c = 0;
		printf("[=]");
		fd = fileno(stdin);
		tcgetattr(fd, &oterm);
		memcpy(&term, &oterm, sizeof(term));
		term.c_lflag = term.c_lflag & (~ICANON);
		term.c_cc[VMIN] = 0;
		term.c_cc[VTIME] = 1;
		tcsetattr(fd, TCSANOW, &term);
		c = getchar();
		tcsetattr(fd, TCSANOW, &oterm);
		printf("[%d, %d]", c, fd );
		if (c != -1)
		ungetc(c, stdin);
		return ((c != -1) ? 1 : 0);
	}
#endif 