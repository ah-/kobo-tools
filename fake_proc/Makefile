CC=arm-none-linux-gnueabi-gcc
CFLAGS=-Wall -O2 -fPIC -shared -ldl

TARGET=libfakeproc.so

LIBSRCS=fakeproc.c
LIBOBJS=fakeproc.o

$(TARGET)	: $(LIBOBJS)
	$(CC) -o $@ $(LIBOBJS) $(CFLAGS)

clean:
	@/bin		/rm -f $(LIBOBJS) 
