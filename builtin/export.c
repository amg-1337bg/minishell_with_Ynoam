/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:22:11 by ynoam             #+#    #+#             */
/*   Updated: 2021/04/17 15:08:46 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	dup_env(t_env *head, int *fd)
{
	int		i;
	int		j;
	t_env	**arr;

	i = list_size(head) - 1;
	j = 0;
	arr = malloc(sizeof(t_env *) * i);
	head = head->next;
	while (j < i)
	{
		arr[j] = head;
		j++;
		head = head->next;
	}
	sort_env(arr, i, fd);
	free(arr);
}

int	there_is_an_error(char *argv)
{
	char	*join;
	char	*join2;

	join = ft_strjoin(argv, "'");
	join2 = ft_strjoin("export: `", join);
	put_error("not a valid identifier", join2);
	ft_free(&join);
	ft_free(&join2);
	return (1);
}

void	variable_assign(t_env *head, char *argv[], int i, int j)
{
	char	*str;

	str = ft_substr(argv[j], 0, i);
	if (!search_env_for_node(head, str))
		crt_env(head, ft_strdup(str), \
				ft_strdup(&(argv[j][i + 1])));
	else
		mdf_env(head, str, ft_strdup(&(argv[j][i + 1])));
	free(str);
}

int	thereis_some_args(t_env *head, char *argv[], int j)
{
	int	i;
	int	ret;

	ret = 0;
	while (argv[j])
	{
		i = 0;
		if ((ft_isalpha(argv[j][i]) || argv[j][i] == '_') && ++i)
			while (ft_isalnum(argv[j][i]) || argv[j][i] == '_')
				i++;
		if (argv[j][i] != '=' && argv[j][i] != 0)
			ret = there_is_an_error(argv[j]);
		else if (argv[j][i] == '=' || argv[j][i] == 0)
		{
			if (argv[j][i] == 0 && !search_env_for_node(head, argv[j]))
				crt_env(head, ft_strdup(argv[j]), NULL);
			else if (argv[j][i] == '=')
				variable_assign(head, argv, i, j);
		}
		j++;
	}
	return (ret);
}

int	export(t_env *head, char *argv[], int *fd)
{
	int		ret;
	int		j;

	ret = 0;
	j = 1;
	if (argv && argv[j] != NULL)
		ret = thereis_some_args(head, argv, j);
	else
		dup_env(head, fd);
	return (ret);
}
