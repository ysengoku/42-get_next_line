#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main()
{
	int		fd;
	char	*line;
//	char	*textfile = "tests/test_1char.txt";
//	char	*textfile = "tests/test_empty.txt";
//	char	*textfile = "tests/test_multilines.txt";
//	char	*textfile = "tests/test_nonl.txt";
//	char	*textfile = "tests/test_onlynl.txt";
//	char	*textfile = "tests/test_withnl.txt";
	char	*textfile = "tests/test_2k.txt";

	fd = open(textfile, O_RDONLY);
	while (1)
 	{
 		line = get_next_line(fd);
 		printf("%s", line);
//		printf("\n-------------------------------------------------\n");
	 	free(line);

		if (!line)
 			break ;
 	}
	close(fd);
	return(0);
}

// int open (const char* path, int flags [, int mode ]);
// returns File Descriptor (small nonnegative int) or -1 (error).
