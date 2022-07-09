NAME		=	philo
SRCSDIR		=	./srcs

SRCS_NAME	=	init.c  main.c  ph_work.c  ph_utils.c  ph_watcher.c  utils_1.c  utils_2.c utils_3.c
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

debug: CFLAGS += -g -fsanitize=thread
debug: re

-include $(DEPS)

.PHONY: all clean fclean re