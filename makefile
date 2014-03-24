# taken from http://ubuntuforums.org/showthread.php?t=1204739
app = main

srcExt = cpp
srcDir = src
objDir = out/obj
binDir = .
inc = .

debug = 1

CFlags = -Wall -Wextra -std=gnu++11
LDFlags =
libs = GL glfw3 X11 Xxf86vm pthread Xrandr Xi
libDir =

#************************ DO NOT EDIT BELOW THIS LINE! ************************

ifeq ($(debug),1)
	CFlags += -g3 -O2
	LDFlags +=
else
	CFlags += -g0 -O3 -flto -fno-fat-lto-objects 
	LDFlags += -flto -O3
endif
inc := $(addprefix -I,$(inc))
libs := $(addprefix -l,$(libs))
libDir := $(addprefix -L,$(libDir))
CFlags += -c $(inc) $(libDir) $(libs)
sources := $(shell find $(srcDir) -name '*.$(srcExt)')
srcDirs := $(shell find . -name '*.$(srcExt)' -exec dirname {} \; | uniq)
objects := $(patsubst %.$(srcExt),$(objDir)/%.o,$(sources))
LDFlags += $(libs)

includes_ := $(CFlags) -c -M

ifeq ($(srcExt), cpp)
	CC = $(CXX)
	# CC = clang++
else
	CFlags += -std=gnu99
endif

version_ = $(CC) --version 


dependencies := $(objects:.o=.d)

.phony: all clean distclean include_files

all: version distclean $(binDir)/$(app)

version: 
		@$(version_)

include_files: 
	@$(CC) $(includes_) $(sources)

$(binDir)/$(app): buildrepo $(objects)
	@echo ""
	@echo "Linking Flags:"
	@echo "	" $(LDFlags)

	@mkdir -p `dirname $@`
	@echo ""
	@echo "Linking $@..."
	@echo "	"$(objects) $(LDFlags) -o $@
	@$(CC) $(objects) $(LDFlags) -o $@

	@echo ""

$(objDir)/%.o: %.$(srcExt)
	@echo ""
	@echo "Compiler Flags:"
	@echo "	" $(CFlags) $<

	@echo ""
	@echo "Generating dependencies for $<..."
	@$(call make-depend,$<,$@,$(subst .o,.d,$@))
	@echo "Compiling $<..."
	@$(CC) $(CFlags) $< -o $@

clean:
	$(RM) -R -v $(objDir)
	$(RM) -v $(binDir)/$(app)

distclean:
	$(RM) $(binDir)/$(app)

buildrepo:
	@$(call make-repo)

define make-repo
	for dir in $(srcDirs); \
	do \
		mkdir -p $(objDir)/$$dir; \
	done
endef


# usage: $(call make-depend,source-file,object-file,depend-file)
define make-depend
  $(CC) -MM       \
        -MF $3    \
        -MP       \
        -MT $2    \
        $(CFlags) \
        $1
endef

# needed to notice changes in header and recompile all dependent sources
-include $(dependencies)
