CC := clang
CFLAGS := -O3 -Wpedantic
LFLAGS := -shared $(CFLAGS)

SRC_D := src
OBJ_D := obj
OBJS  := obj/ringbuffer.o obj/test.o
LIBOS := $(filter-out obj/test.o, $(OBJS))


lib: librb.dylib

clean:
	$(RM) -r obj/
	$(RM) librb.dylib
	$(RM) test

$(OBJ_D)/ringbuffer.o: $(SRC_D)/ringbuffer.c $(SRC_D)/ringbuffer.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_D)/test.o: $(SRC_D)/test.c $(SRC_D)/ringbuffer.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

librb.dylib: $(LIBOS)
	$(CC) $(LFLAGS) -o $@ $<

test: $(OBJS)
	$(CC) $(CFLAGS) -Isrc/ -o $@ $(OBJS)

.PHONY: clean