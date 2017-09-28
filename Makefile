EXE_ONE = mp1

OBJS_DIR = .objs

OBJS = search.o solution.o

CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -msse2 -c -L/usr/include/
CXXFLAGS_PROVIDED = -O2
CXXFLAGS_STUDENT = -O0
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread -L/usr/include/
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all: mp1.1 #mp1.2
mp1.1: $(EXE_ONE)

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_STUDENT) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(EXE_ONE):
	$(LD) $^ $(LDFLAGS) -o $@

$(EXE_ONE):               $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	rm -rf $(EXE) $(OBJS_DIR)

.PHONY: all mp1.1 mp1.2 clean