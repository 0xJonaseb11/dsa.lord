CXX ?= g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
BUILD_DIR = build

.PHONY: clean

define compile_rule
$(BUILD_DIR)/$(1): $(2) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $$@ $(2)
endef

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
