# Names and Paths
BUILD_DIR    := build
CONFIG_DIR   := config
TOOLS_DIR    := tools
OBJDIFF_DIR  := $(TOOLS_DIR)/objdiff
EXPECTED_DIR := expected
DOCKERFILE   := ./Dockerfile
DOCKER       := $(shell sh -c 'command -v docker || true')
OBJDIFF      := $(OBJDIFF_DIR)/objdiff
PYTHON       := python3

# Detect host OS and architecture
uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')
uname_M := $(shell sh -c 'uname -m 2>/dev/null || echo not')

# Tools
# The binary tools in this repo require linux/x86_64 -- if we're on that platform,
# use prebuilt Gears and do build directly on the host.
# Edge-cases may require building Gears from source on linux/x86_64 (ex: mismatched GLIBC version)
# so we default to the locally built binary if it is present
ifeq ($(uname_S)-$(uname_M),Linux-x86_64)
	GEARS_LOCAL  := $(TOOLS_DIR)/gears/target/release/gears
ifneq (,$(shell sh -c '$(GEARS_LOCAL) --version 2>/dev/null || true'))
	GEARS        := $(GEARS_LOCAL)
ifneq (,$(shell sh -c 'command -v cargo || true'))
	# keeps the local build up to date with its "sources" for convenience, if cargo is available
	# (not actual versioning, just file mod_date for now)
	NEED_GEARS := true
else
	NEED_GEARS := false
endif
else
	GEARS        := $(TOOLS_DIR)/gears/prebuilt/gears
	NEED_GEARS := false
endif
	NEED_DOCKER := false
else
	# Use the compiled version of Gears
	GEARS        := $(TOOLS_DIR)/gears/target/release/gears
	# flag used below to run build in a docker container
	NEED_DOCKER := true
	# flag used below to trigger gears build automatically
	NEED_GEARS := true
endif

# Settings
ifeq ($(uname_S),Linux)
	NUMPROC ?= $(shell nproc)
endif
ifeq ($(uname_S),Darwin)
	NUMPROC ?= $(shell sysctl -n hw.logicalcpu)
endif

# Rules
default: all

all: build

ifeq ($(NEED_GEARS),true)
# add make targets to build Gears, and add dependencies.
GEARS_SRC := $(TOOLS_DIR)/gears/Cargo.toml $(TOOLS_DIR)/gears/Cargo.lock $(wildcard $(TOOLS_DIR)/gears/src/*.rs)
$(GEARS): $(GEARS_SRC)
	cd $(TOOLS_DIR)/gears && cargo build --release
	#timestamp trick (sorry, have not yet found a better way to do this)
	touch $@

ifneq ($(NEED_DOCKER), true)
build: $(GEARS)
endif
clean: $(GEARS)
endif

ifeq ($(NEED_DOCKER),true)
# provide a useful error for non-linux/x86_64 platforms
ifeq (,$(DOCKER))
$(error Docker is required for platform $(uname_S)/$(uname_M))
endif

# make target to build the container
docker:
	docker buildx build --platform linux/amd64 . -t ethos:latest --quiet
# build target runs build in the container. note that files get written to the
# host filesystem, not the container filesystem.
build: docker
	docker run --rm -it --platform=linux/amd64 -v$(PWD):/xenogears-decomp ethos:latest /bin/bash -c '. /.venv/bin/activate && make build'
else
build:
	$(MAKE) clean; \
	$(GEARS) matching; \
	ninja -t clean; \
	ninja -j$(NUMPROC)
endif

check: clean build
	@sha256sum --check $(CONFIG_DIR)/checksum.sha

objdiff-config:
	$(MAKE) clean; \
	$(GEARS) report; \
	ninja -t clean; \
	ninja -j$(NUMPROC); \
	mkdir -p $(EXPECTED_DIR); \
	mv build/asm $(EXPECTED_DIR)/asm; \
	$(PYTHON) $(OBJDIFF_DIR)/objdiff_generate.py $(OBJDIFF_DIR)/config.yaml

report: objdiff-config
	@$(OBJDIFF) report generate > $(BUILD_DIR)/progress.json

clean:
	@$(GEARS) clean; \
	rm -rf $(EXPECTED_DIR)

### Settings
.SECONDARY:
.PHONY: all clean default
SHELL = /bin/bash -e -o pipefail
