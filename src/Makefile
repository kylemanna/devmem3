PROG := devmem3
OBJS := main.o DeviceMemory.o

CXXFLAGS := -I. -I../include

# Support cross compilers
CC := $(CROSS_COMPILE)-gcc
CXX := $(CROSS_COMPILE)-g++

MAKEDEPEND = $(CPP) $(CPPFLAGS) $< \
			 | sed -n 's/^\# *[0-9][0-9]* *"\([^"]*\)".*/$*.o: \1/p' \
			 | sort | uniq > $*.d

all: $(PROG)

# Pull in dependency info for existing obj files
-include $(OBJS:.o=.d)

# Link the main program
$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG)

# Compile object files
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -MMD -MF $(patsubst %.o,%.d,$@) -o $@ $<

# Clean up output
clean:
	$(RM) $(PROG) *.o *.d
