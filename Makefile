NAME = Rush

DEBUG_FLAGS = -fsanitize=address
FLAGS = -g $(DEBUG_FLAGS)
INCLUDES = -I includes/ -I includes/SDL2/ -I includes/SDLX/ -I includes/MT

LIB_DIR = libs/
LIBRARIES = $(LIB_DIR)libSDL2-2.0.0.dylib $(LIB_DIR)libSDL2_image-2.0.0.dylib $(LIB_DIR)libSDL2_ttf-2.0.0.dylib
STATIC_LIB = -L -l $(LIB_DIR)libSDLX.a

MT_DIR = MT/
SDLX_DIR = SDLX/
BUTTON_DIR = buttons/
SCREEN_DIR = screens/
SPELL_DIR = spells/
SRCS_DIR = srcs/

BIN_DIR = bin/


SDLX_NAMES = 			\
	SDLX_anim			\
	SDLX_input			\
	SDLX_LevelManager	\
	SDLX_render			\
	SDLX_UI				\
	SDLX_utils			\
	SDLX				\

MT_NAMES = 				\
	MT_v2				\
	MT					\

BUTTON_NAMES =			\
	b_main_level		\
	b_main_menu			\

SCREEN_NAMES =			\
	main_level			\
	main_menu			\
	test_lvl			\

SPELL_NAMES =			\
	fireball			\
	spells_utils		\

SRCS_NAMES =									\
	$(addprefix $(SDLX_DIR),	$(SDLX_NAMES))	\
	$(addprefix $(MT_DIR),		$(MT_NAMES))	\
	$(addprefix $(BUTTON_DIR),	$(BUTTON_NAMES))\
	$(addprefix $(SCREEN_DIR),	$(SCREEN_NAMES))\
	$(addprefix $(SPELL_DIR),	$(SPELL_NAMES))	\
	debug				\
	init				\
	main 				\
	utils				\

C_FILES =				\
	$(SRCS_NAMES) 		\

C_FILES =				\
	$(addprefix $(SRCS_DIR), $(SRCS_NAMES))		\

SRCS = $(addsuffix .c, $(C_FILES))

OBJS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(BIN_DIR) $(OBJS)
	gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBRARIES)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)%.o: %.c
	mkdir -p $(BIN_DIR)$(dir $<)
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

run: re clean
	./$(NAME)

clean:
	rm -rf $(BIN_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
