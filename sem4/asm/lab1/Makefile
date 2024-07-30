#NAME = lab1
#EXE = lab

#all: $(EXE) $(NAME).o

#$(EXE): $(NAME).o
#	gcc -g -no-pie $^ -o $@

#$(NAME).o: $(NAME).s
#	nasm -f elf64 -g $^ -o $@

#clean:
#	rm -f *.o
#	rm -f $(EXE) 

AS = nasm
LD = gcc

ASFLAGS = -g -f elf64
LDFLAGS = -g -no-pie 

SRCS = lab1.s
OBJS = $(SRCS:.s=.o)

EXE = $(SRCS:.s=)

all: $(EXE) $(OBJS)

clean:
	rm -rf $(EXE) $(OBJS)

$(EXE): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

.s.o:
	$(AS) $(ASFLAGS) $^ -o $@