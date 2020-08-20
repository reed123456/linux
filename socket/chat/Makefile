.PHONY: clean all

TARGET = svr cli

all :  $(TARGET)

svr : chat_svr.o
	gcc $^ -o $@ -lpthread -g
cli : chat_cli.o
	gcc $^ -o $@ -lpthread -g

%.o : %.c
	gcc -c $^ -o $@ -g

clean:
	rm -rf $(TARGET) *.o
