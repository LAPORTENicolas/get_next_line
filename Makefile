SOURCES = main.c get_next_line.c get_next_line_utils.c
OBJECT	= ${SOURCES:.c=.o}
CC			= cc
FLAGS		= -Wall -Wextra -Werror -g3 -D BUFFER_SIZE=10
NAME		= get_next_line

all: ${NAME}

${NAME}: ${OBJECT}
	${CC} ${FLAGS} ${OBJECT} -o ${NAME}

${OBJECT}:
	${CC} ${FLAGS} -c ${SOURCES}

fclean: clean
	rm -rf ${NAME}

clean: 
	rm -rf ${OBJECT}

re: fclean all

.PHONY: all re clean fclean
