/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:22:11 by ynoam             #+#    #+#             */
/*   Updated: 2021/04/11 11:44:52 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"
// export PWD OLDPWD 
// env | grep PWD
// PWD /

// t_env	*create_env_copy(t_env *head)
// {
// 	t_env	*copy;

// 	copy = malloc(sizeof(t_env));
// 	copy->key = NULL;
// 	copy->value = NULL;
// 	copy->next = NULL;
// 	head = head->next;
// 	while (head)
// 	{
// 		crt_env(copy, head->key, head->value);
// 		head = head->next;
// 	}
// 	return (copy);
// }

int		same(char *str1, char *str2)
{
	if (ft_strncmp(str1, str2, ft_strlen(str1)) == 0
		&& ft_strlen(str1) == ft_strlen(str2))
		return (1);
	return (0);
}

void	print(t_env **head, int i, int *fd)
{
	int		j;

	j = 0;
	while (j < i)
	{
		if (head[j]->key && (head[j]->key[0] != '_' || head[j]->key[1] != 0))
		{
			ft_putstr_fd("declare -x ", fd[1]);
			ft_putstr_fd(head[j]->key, fd[1]);
			if (head[j]->value)
			{
				ft_putstr_fd("=", fd[1]);
				ft_putstr_fd("\"", fd[1]);
				ft_putstr_fd(head[j]->value, fd[1]);
				ft_putstr_fd("\"", fd[1]);
				ft_putstr_fd("\n", fd[1]);
			}
			else
				ft_putstr_fd("\n", fd[1]);
		}
		j++;
	}
}

void	swap_env(t_env **arr, int k, int j)
{
	t_env	*tmp;

	tmp = arr[j];
	arr[j] = arr[k];
	arr[k] = tmp;
}

void	sort_env(t_env **arr, int i, int *fd)
{
	int		j;
	int		k;
	int		c;

	j = -1;
	while (++j < i - 1 && (k = j + 1))
		while (k < i)
		{
			c = 0;
			while (arr[j]->key[c] || arr[k]->key[c])
			{
				if (arr[j]->key[c] > arr[k]->key[c])
				{
					swap_env(arr, k, j);
					break ;
				}
				else if (arr[j]->key[c] < arr[k]->key[c] || arr[j]->key[c] == 0)
					break ;
				c++;
			}
			k++;
		}
	print(arr, i, fd);
}

void	dup_env(t_env *head, int *fd)
{
	int		i;
	int		j;
	t_env	**arr;

	i = list_size(head) - 1;
	j = 0;
	arr = malloc(sizeof(t_env*) * i);
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


int		export(t_env *head, char *argv[], int *fd)
{
	int		i;
	char	*join;
	char	*join2;
	int		ret;
	int		j;

	ret = 0;
	j = 1;
	if (argv && argv[j] != NULL)
		while (argv[j])
		{
			i = 0;
			if ((ft_isalpha(argv[j][i]) || argv[j][i] == '_') && ++i)
				while (ft_isalnum(argv[j][i]) || argv[j][i] == '_')
					i++;
			if (argv[j][i] != '=' && argv[j][i] != 0)
			{
				join =  ft_strjoin(*argv, "'");
				join2 = ft_strjoin("export: `", join);
				put_error("not a valid identifier", join2);
				ft_free(&join);
				ft_free(&join2);
				ret = 1;
			}
			else if (argv[j][i] == '=' || argv[j][i] == 0)
			{
				if (argv[j][i] == 0 && !search_env_for_node(head, argv[j]))
						crt_env(head, ft_strdup(argv[j]), NULL);
				else if (argv[j][i] == '=')
				{
					char *str = ft_substr(argv[j], 0, i);
					if (!search_env_for_node(head, str))
						crt_env(head, ft_strdup(str), ft_strdup(&(argv[j][i + 1])));
					else
						mdf_env(head, str, ft_strdup(&(argv[j][i + 1])));
					free(str);
				}
			}
			j++;
		}
	else
		dup_env(head, fd);
	return (ret);
}
