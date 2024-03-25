#####	VARIABLES   #####
NAME		=	cub3D

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -I./include -g

SRC_DIR		=	src

SRCS		=	main.c parsing/parsing.c

OBJ_DIR		=	obj

OBJ			=	$(SRCS:%.c=%.o)

OBJS		=	$(addprefix $(OBJ_DIR)/, $(OBJ))

OBJ_COUNT	:= 0

########		LIBFT		########

LFT_DIR		=	libft

LIBFT		=	$(LFT_DIR)/libft.a

######	MLX   ######
MLX_FLAGS	=	-lX11 -lXext -lmlx

MLX_PATH	=	./minilibx-linux

MLX			=	$(MLX_PATH)/libmlx.a

########		COLORS		########

COLOR_RESET		=	\033[0m
COLOR_RED		=	\033[1;31m
COLOR_GREEN		=	\033[1;32m
COLOR_YELLOW	=	\033[1;93m
COLOR_BLUE		=	\033[1;94m
COLOR_PINK		=	\033[38;5;206m
COLOR_LBLUE		=	\033[1;94m

########		RULES   	########

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
				@$(CC) $(CFLAGS) -L$(LFT_DIR) -L$(MLX_PATH) $^ $(MLX_FLAGS) -lm -o $@
				@echo "$(COLOR_GREEN)$(NAME) has been successfully built!$(COLOR_RESET)"
				@clear
				@echo "$(COLOR_LBLUE)"
				@echo "		=========================================	"
				@echo "		██████╗██╗   ██╗██████╗ ██████╗ ██████╗  	"
				@echo "		██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗	"
				@echo "		██║     ██║   ██║██████╔╝ █████╔╝██║  ██║	"
				@echo "		██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║	"
				@echo "		╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝	"
				@echo "		 ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ 	"
				@echo "		=========================================	"
				@echo "$(COLOR_RESET)"

$(MLX):
				@echo "\n$(COLOR_YELLOW)making MinilibX...$(COLOR_RESET)"
				@make -sC $(MLX_PATH)
				@echo "$(COLOR_GREEN)MinilibX has been built successfully!$(COLOR_RESET)"

$(LIBFT) :
				@echo "\n$(COLOR_YELLOW)Making libft...$(COLOR_RESET)"
				@make -sC $(LFT_DIR)
				@echo "$(COLOR_GREEN)Libft has been built successfully!$(COLOR_RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@
				@$(eval OBJ_COUNT=$(shell expr $(OBJ_COUNT) + 1))
				@printf "\033[K\r"
				@printf "[$(COLOR_BLUE)%d%%$(COLOR_RESET)] $(notdir $<)" $$(expr $$(($(OBJ_COUNT) * 100)) / $(words $(SRCS)))

clean : 
				@echo "$(COLOR_YELLOW)Cleaning libft...$(COLOR_RESET)"
				@make -sC $(LFT_DIR) clean
				@echo "$(COLOR_RED)Cleaning .o files...$(COLOR_RESET)"
				@rm -f $(OBJS)
				@echo "$(COLOR_GREEN)Project cleaned!$(COLOR_RESET)"

fclean :		clean
				@echo "$(COLOR_YELLOW)Cleaning executable and libft.a...$(COLOR_RESET)"
				@make -sC $(LFT_DIR) fclean
				@rm $(RM_FLAGS) $(NAME)
				@echo "$(COLOR_RED)Project fully cleaned!$(COLOR_RESET)"

re: fclean all

.PHONY: all clean fclean re
