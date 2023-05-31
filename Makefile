CC = gcc
CFLAGS = -Wall -Wextra

SRC = src
HDR = $(SRC)/headers
ODIR = obj
OBJS = \
	$(ODIR)/assert_equals.o \
	$(ODIR)/utf8_decoder.o

EXEC_FILE = utf8

$(EXEC_FILE): $(OBJS) $(SRC)/main.c
	$(CC) $(SRC)/main.c $(ODIR)/*.o -I $(HDR) $(CFLAGS) -o $@

$(ODIR)/%.o: $(SRC)/%.c $(HDR)/%.h
	$(CC) -c $< -I $(HDR) $(CFLAGS) -o $@

run: $(EXEC_FILE)
	./$(EXEC_FILE)

clean:
	rm -rf $(ODIR)/*.o
	rm ./$(EXEC_FILE)
