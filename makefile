CC=gcc
OUT=ap
IN= \
	src/main.c \
	src/utils.c \
	src/maker.c \
	src/taker.c \
	src/viewer.c \

default:
	$(CC) -o $(OUT) $(IN)
