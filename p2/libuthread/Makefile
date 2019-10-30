# Target library
lib		:= libuthread.a
objs		:= queue.o uthread.o context.o preempt.o

CC		:= gcc
CFLAGS		:= -Wall -Werror
CFLAGS		+= -g

# The command 'make V=1' will explicitely print rule commands
ifneq	($(V),1)
Q = @
V = 0
endif


DEPFLAGS = -MMD -MF $(@:.o=.d)

deps	:= $(patsubst %.o,%.d,$(objs))
-include $(deps)

libuthread.a: $(objs)
	@echo "CC	$@"
	$(Q)ar rcs $@ $^	

%.o: %.c %.h
	@echo "CC	$@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $< $(DEPFLAGS)

clean:
	@echo "CLEAN"
	$(Q)rm -f $(lib) $(objs) $(deps)
