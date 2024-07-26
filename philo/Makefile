NAME=philo
BUILD_DIR=build
cflags=-Wall -Wextra -Werror
iflags=-I.
lflags=

all: dirs $(NAME)

sanitizer: cflags+=-g3 -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG
sanitizer: lflags+=-g3 -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG
sanitizer: all

re: fclean all

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

#         __     __    ___   ___  ____  ____ 
#        (  )   /  \  / __) / __)(  __)(  _ \
#        / (_/\(  O )( (_ \( (_ \ ) _)  )   /
#        \____/ \__/  \___/ \___/(____)(__\_)

logger_dir=$(BUILD_DIR)/logger
logger_modules=error logger
logger_obj=$(addprefix $(logger_dir)/, $(addsuffix .o, $(logger_modules)))
$(logger_dir): | $(BUILD_DIR)
	mkdir $@

#         ____   __   ____  ____  ____  ____ 
#        (  _ \ / _\ (  _ \/ ___)(  __)(  _ \
#         ) __//    \ )   /\___ \ ) _)  )   /
#        (__)  \_/\_/(__\_)(____/(____)(__\_)

parser_dir=$(BUILD_DIR)/parser
parser_modules=number
parser_obj=$(addprefix $(parser_dir)/, $(addsuffix .o, $(parser_modules)))
$(parser_dir): | $(BUILD_DIR)
	mkdir $@

#         ____  _  _  __  __     __   ____   __  ____  _  _  ____  ____ 
#        (  _ \/ )( \(  )(  )   /  \ / ___) /  \(  _ \/ )( \(  __)(  _ \
#         ) __/) __ ( )( / (_/\(  O )\___ \(  O )) __/) __ ( ) _)  )   /
#        (__)  \_)(_/(__)\____/ \__/ (____/ \__/(__)  \_)(_/(____)(__\_)

philosopher_dir=$(BUILD_DIR)/philosopher
philosopher_modules=philosopher create_philosophers philosopher_actions philosopher_base
philosopher_obj=$(addprefix $(philosopher_dir)/, $(addsuffix .o, $(philosopher_modules)))
$(philosopher_dir): | $(BUILD_DIR)
	mkdir $@

#         ____  ____  _  _   __   ____ 
#        (  _ \(  __)( \/ ) / _\ (  _ \
#         )   / ) _) / \/ \/    \ ) __/
#        (__\_)(____)\_)(_/\_/\_/(__)  

remap_dir=$(BUILD_DIR)/remap
remap_modules=pthread time
remap_obj=$(addprefix $(remap_dir)/, $(addsuffix .o, $(remap_modules)))
$(remap_dir): | $(BUILD_DIR)
	mkdir $@

#         _  _   __   __  __ _ 
#        ( \/ ) / _\ (  )(  ( \
#        / \/ \/    \ )( /    /
#        \_)(_/\_/\_/(__)\_)__)

obj=$(BUILD_DIR)/main.o $(logger_obj) $(parser_obj) $(philosopher_obj) $(remap_obj)
$(BUILD_DIR):
	mkdir $@

dirs: $(logger_dir) $(parser_dir) $(philosopher_dir) $(remap_dir)

$(NAME): $(obj)
	cc $(iflags) $(cflags) $(lflags) -o $@ $(obj)

depflags = -MT $@ -MMD -MP -MF $(BUILD_DIR)/$*.d

$(BUILD_DIR)/%.o: %.c $(BUILD_DIR)/%.d Makefile
	cc $(cflags) $(iflags) $(depflags) -c $< -o $@

$(obj:.o=.d):
-include $(obj:.o=.d)

.PHONY: all clean fclean re dirs