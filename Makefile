NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread

SRCPATH = ./src/

SOURCES = $(addprefix $(SRCPATH), main.c utils.c routine.c checker.c print.c parse.c init.c)

OBJECTS = $(SOURCES:.c=.o)

${NAME}: ${OBJECTS}
	${CC} ${CFLAGS} ${SOURCES} -o ${NAME}

clean:
	rm -f ${OBJECTS}

fclean: clean
	rm -f ${NAME}

all: ${NAME}

re: fclean all

.PHONY: all clean fclean re
