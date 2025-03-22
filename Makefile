default: dbgc
.PHONY: default relb relc dbgb dbgc compt comp

include _mk/Colours.mk
include _mk/Settings.mk
include _mk/Env.mk
include _mk/Commands.mk

# Release build target
relc:
	@$(MAKE) -s BUILD_MODE=RELEASE comp

# Debug build targets
dbgc:
	@$(MAKE) -s BUILD_MODE=DEBUG comp

# Compilation target
compt:
	@printf "\n$(BLUE)Compiling with flags: $(CFLAGS)\n$(DEFCOL)"
	@printf "$(MAGENTA)$(BUILD_MODE) compilation started\n\n$(DEFCOL)"
comp: compt $(PROJECT_NAME)
# @$(MAKE) $(MAKEFILE_PARAMS) # NOTE: Enable this to compile on Android
	@printf "\n$(GREEN)$(BUILD_MODE) compilation finished\n\n$(DEFCOL)"