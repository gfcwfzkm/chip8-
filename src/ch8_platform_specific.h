#ifdef _WIN32
	#include <conio.h>

	#define CH8_KBHIT   kbhit
	#define CH8_GETCH   getch

	// Fancy characters from IBM Codepage 437
	// https://de.wikipedia.org/wiki/Codepage_437
	// Arrow Symbol
	#define CH8_ARROW	"\x1A"
	// Display Pixel
	#define CH8_NOPIXEL		" "
	#define CH8_UPPERPIXEL	"\xDF"
	#define CH8_LOWERPIXEL	"\xDC"
	#define CH8_BOTHPIXEL	"\xDB"
	// Display Beep Frame
	#define CH8_FRAMEB_UPL	"\xC9"
	#define CH8_FRAMEB_UP	"\xCD"
	#define CH8_FRAMEB_UPR	"\xBB"
	#define CH8_FRAMEB_LEFT	"\xBA"
	#define CH8_FRAMEB_RGHT	"\xBA"
	#define CH8_FRAMEB_DNL	"\xC8"
	#define CH8_FRAMEB_DOWN	"\xCD"
	#define CH8_FRAMEB_DNR	"\xBC"
	// Display Normal Frame
	#define CH8_FRAME_UPL	"\xDA"
	#define CH8_FRAME_UP	"\xC4"
	#define CH8_FRAME_UPR	"\xBF"
	#define CH8_FRAME_LEFT	"\xB3"
	#define CH8_FRAME_RGHT	"\xB3"
	#define CH8_FRAME_DNL	"\xC0"
	#define CH8_FRAME_DOWN	"\xC4"
	#define CH8_FRAME_DNR	"\xD9"

	#define CH8_SYMBOL_TYPE	char
#else
	// Unix & Linux should be able to handle fancy characters directly
	#define CH8_ARROW	"→"
	// Display Pixel
	#define CH8_NOPIXEL		" "
	#define CH8_UPPERPIXEL	"▀"
	#define CH8_LOWERPIXEL	"▄"
	#define CH8_BOTHPIXEL	"█"
	// Display Beep Frame
	#define CH8_FRAMEB_UPL	"╔"
	#define CH8_FRAMEB_UP	"═"
	#define CH8_FRAMEB_UPR	"╗"
	#define CH8_FRAMEB_LEFT	"║"
	#define CH8_FRAMEB_RGHT	"║"
	#define CH8_FRAMEB_DNL	"╚"
	#define CH8_FRAMEB_DOWN	"═"
	#define CH8_FRAMEB_DNR	"╝"
	// Display Normal Frame
	#define CH8_FRAME_UPL	"┌"
	#define CH8_FRAME_UP	"─"
	#define CH8_FRAME_UPR	"┐"
	#define CH8_FRAME_LEFT	"│"
	#define CH8_FRAME_RGHT	"│"
	#define CH8_FRAME_DNL	"└"
	#define CH8_FRAME_DOWN	"─"
	#define CH8_FRAME_DNR	"┘"
	#define CH8_SYMBOL_TYPE	int
	#ifdef __linux__
		/**
		 Linux (POSIX) implementation of _kbhit().
		 Morgan McGuire, morgan@cs.brown.edu
		 */
		#include <stdio.h>
		#include <termios.h>
		#include <unistd.h>
		#include <fcntl.h>

		static int CH8_KBHIT()
		{
    		struct termios oldt, newt;
  			int ch;
  			int oldf;

  			tcgetattr(STDIN_FILENO, &oldt);
  			newt = oldt;
  			newt.c_lflag &= ~(ICANON | ECHO);
  			tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  			oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  			fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  			ch = getchar();

  			tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  			fcntl(STDIN_FILENO, F_SETFL, oldf);

  			if(ch != EOF)
  			{
  			  ungetc(ch, stdin);
  			  return 1;
  			}

  			return 0;
		}

		#define CH8_GETCH	getchar
	#elif __apple_build_version__
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
	#else
		#error "Unknown platform!"abort
	#endif
#endif 