/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:05:17 by kato              #+#    #+#             */
/*   Updated: 2025/11/20 12:00:00 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include "minishell.h"

/* Bonus parser utilities */
int		count_wildcard_matches(char **exp);
int		is_word_with_wildcard(t_token *token);
int		is_quoted_str(char *str);
int		handle_word_exp(char **av, char *exp, t_token **t, int *idx);
int		add_split_words(char **av, char **words, int *idx);
int		process_word_token(t_token **t, char **av, int *idx, t_shell *s);

/* Wildcard expansion API */
char	**expand_wildcard(char *pattern);
int		has_wildcard(char *str);
void	swap_strings(char **a, char **b);
void	sort_matches(char **result, int count);
char	**create_single_result(char *pattern);
char	**init_result_array(int count, DIR **dir);

/* Parse redirection helpers */
int		is_quoted_redir(char *str);
char	*get_redir_filename_bonus(t_token **tok, t_shell *sh,
			t_redir_type type);
int		process_word_token(t_token **t, char **av, int *idx, t_shell *s);
int		count_word_token(t_token *token, t_shell *shell);

#endif
