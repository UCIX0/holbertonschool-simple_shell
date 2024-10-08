#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info_shell: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(shell_info *info_shell)
{
	char *buf, *dir;
	char *hist_file = ".simple_shell_history";

	dir = get_env_value(info_shell, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (strlen(dir) + strlen(hist_file) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	strcpy(buf, dir);
	strcat(buf, "/");
	strcat(buf, hist_file);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(shell_info *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_node *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->data, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info_shell: the parameter struct
 *
 * Return: history_count on success, 0 otherwise
 */
int read_history(shell_info *info_shell)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info_shell);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info_shell, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info_shell, buf + last, linecount++);
	free(buf);
	info_shell->history_count = linecount;
	while (info_shell->history_count-- >= HIST_MAX)
		delete_node_at_index(&(info_shell->history), 0);
	renumber_history(info_shell);
	return (info_shell->history_count);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, history_count
 *
 * Return: Always 0
 */
int build_history_list(shell_info *info, char *buf, int linecount)
{
	list_node *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new history_count
 */
int renumber_history(shell_info *info)
{
	list_node *node = info->history;
	int i = 0;

	while (node)
	{
		node->index = i++;
		node = node->next;
	}
	return (info->history_count = i);
}
