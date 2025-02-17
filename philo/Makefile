# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dancel <dancel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 13:49:20 by dancel            #+#    #+#              #
#    Updated: 2025/02/17 14:24:48 by dancel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Variables de Compilation
# ============================
PHILO            = philo
CC               = cc
CFLAGS           = -Wall -Werror -Wextra -g3

# Fichiers et bibliothèques
# ============================
INCLUDES   = -Iinclude

# Fichiers source
# ============================
SRC_FILES   = sources/main.c sources/utils_1.c
OBJ_FILES   = $(SRC_FILES:sources/%.c=objects/%.o)

# Cible principale
# ============================
all: create_objects_dirs $(PHILO)

$(PHILO): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

create_objects_dirs: objects

objects:
	mkdir -p objects

objects/%.o: sources/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Nettoyage des fichiers
# ============================
clean:
	@rm -rf objects

fclean: clean
	@rm -f philo

# Rebuild
# ============================
re: fclean all

# Cibles "fantômes"
# ============================
.PHONY: all clean fclean re bonus
