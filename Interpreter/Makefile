EXEC = test

CC = clang
CFLAGS = -Wall -Werror -Wextra

SOURCE = $(wildcard *.c)
HEADERS = $(wildcard *.h)
LIBS = $(wildcard *.a)
OBJS = $(SOURCE:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)