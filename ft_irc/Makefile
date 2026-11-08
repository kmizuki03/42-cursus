NAME		:= ircserv
BONUS_NAME	:= ircbot

CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 -Iinclude

SRC_DIR		:= src
BONUS_DIR	:= bonus
OBJ_DIR		:= obj

SRCS		:= main.cpp \
			   Server.cpp \
			   ServerCommands.cpp \
			   ServerChannelCommands.cpp \
			   ServerOperatorCommands.cpp \
			   Client.cpp \
			   Channel.cpp \
			   Message.cpp \
			   Utils.cpp

BONUS_SRCS	:= main_bonus.cpp \
			   Bot.cpp

OBJS		:= $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))
BONUS_OBJS	:= $(addprefix $(OBJ_DIR)/$(BONUS_DIR)/, $(BONUS_SRCS:.cpp=.o)) \
			   $(OBJ_DIR)/Message.o \
			   $(OBJ_DIR)/Utils.o
DEPS		:= $(OBJS:.o=.d) $(BONUS_OBJS:.o=.d)

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CXX) $(CXXFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(OBJ_DIR)/$(BONUS_DIR)/%.o: $(BONUS_DIR)/%.cpp | $(OBJ_DIR)/$(BONUS_DIR)
	$(CXX) $(CXXFLAGS) -I$(BONUS_DIR) -MMD -MP -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/$(BONUS_DIR):
	mkdir -p $(OBJ_DIR)/$(BONUS_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

-include $(DEPS)

.PHONY: all bonus clean fclean re
