VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 1
NAME = "First edition"

CROSS_COMPILE =

CC = ${CROSS_COMPILE}g++

SRCDIR = src
BINDIR = bin
DOCDIR = doc

INCLUDES = $(SRCDIR) 	   -I$(SRCDIR)/include -I/usr/include/SDL2
CPPFLAGS   = -I$(INCLUDES) -g -O2 -MD -MP -std=c++11

LIBS     = -lSDL2 -lSDL2_image
LDFLAGS  =

#
# Pretty print
#
V             = @
Q             = $(V:1=)
QUIET_CC      = $(Q:@=@echo    '     CC       '$@;)
QUIET_GEN     = $(Q:@=@echo    '     GEN      '$@;)
QUIET_LINK    = $(Q:@=@echo    '     LINK     '$@;)

EXECUTABLE=space-shoot

.PHONY: all clean

SOURCES = $(shell find $(SRCDIR) -name *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo "Finishing..."
	@mkdir -p $(BINDIR)
	$(QUIET_CC) $(CC) $(CPPFLAGS) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(BINDIR)/$@

.cpp.o:
		$(QUIET_CC) $(CC) $(CPPFLAGS) $(LDFLAGS) -c $< -o $@

-include $(SOURCES:%.cpp=%.d)

clean:
	@echo "Cleaning up..."
	@echo "* src"
	-$(shell find . -name *.o -exec rm {} \;)
	-$(shell find . -name *.d -exec rm {} \;)
	-$(shell rm -f $(BINDIR)/$(EXECUTABLE))
	@echo "* docs"
	@rm -rf $(DOCDIR)/html
	@rm -rf $(DOCDIR)/latex
	@echo "Done!"

# If makefile changes, maybe the list of sources has changed, so update doxygens list
doxyfile.inc: Makefile
	echo INPUT += README.md > $(DOCDIR)/doxyfile.inc
	echo USE_MDFILE_AS_MAINPAGE = README.md >> $(DOCDIR)/doxyfile.inc
	echo INPUT		+=  $(SRCDIR) >> $(DOCDIR)/doxyfile.inc
	echo FILE_PATTERNS	=  "*.h *.cpp" >> $(DOCDIR)/doxyfile.inc
	echo OUTPUT_DIRECTORY	= $(DOCDIR)/ >> $(DOCDIR)/doxyfile.inc

docs: doxyfile.inc $(SRCS)
	doxygen $(DOCDIR)/doxyfile.mk
