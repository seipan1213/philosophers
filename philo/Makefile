NAME		=	philo
SRCSDIR		=	./srcs

SRCS_NAME	=	main.c utils.c
SRCS		=	${addprefix ${SRCSDIR}/, ${SRCS_NAME}}
OBJS		=	${SRCS:.c=.o}
DEPS		=	${OBJS:%.o=%.d}

INCLUDES	=	-I ./includes
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -MMD -MP -pthread

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${INCLUDES} -o $@

.c.o:
	${CC} ${CFLAGS} $< -c ${INCLUDES} -o $@

clean:
	${RM} ${OBJS} ${DEPS}

fclean: clean
	${RM} ${NAME}

re: fclean all

debug: CFLAGS += -g -fsanitize=address
debug: re

-include $(DEPS)

.PHONY: all clean fclean re