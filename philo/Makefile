SRCS	= main.c program.c str_utils.c utils.c
OBJS	= ${SRCS:.c=.o}
FLAGS	= -Wall -Wextra -Werror
NAME	= philo

all: ${NAME}

${NAME} : ${OBJS}
	cc ${OBJS} ${FLAGS} -o ${NAME}

%.o:%.c philo.h
	cc -c ${FLAGS} $< -o $@

clean :
	rm -rf ${OBJS}

fclean : clean
	rm -rf ${NAME}

re : fclean all
