 	return (pfd[0]);
 }
 
int	open_redirect_file(t_node *node)
 {
	if (node == NULL)
		return (0);
	if (node->type == NODE_PIPELINE)
	{
		if (open_redirect_file(node->command) < 0)
			return (-1);
		if (open_redirect_file(node->next) < 0)
			return (-1);
 		return (0);
	}
	else if (node->type == NODE_COMMAND)
		return (open_redirect_file(node->redirects));
	else if (node->type == NODE_REDIRECT_OUT)
		node->filefd = open(node->filename->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (node->type == NODE_REDIRECT_IN)
		node->filefd = open(node->filename->str, O_RDONLY);
	else if (node->type == NODE_REDIRECT_APPEND)
		node->filefd = open(node->filename->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (node->type == NODE_REDIRECT_HEREDOC)
		node->filefd = read_heredoc(node->delimiter->str);
 	else
 		assert_error("open_redirect_file");
	if (node->filefd < 0)
 	{
		xperror(node->filename->str);
 		return (-1);
 	}
	node->filefd = stashfd(node->filefd);
	return (open_redirect_file(node->next));
 }
 
 bool	is_redirect(t_node *node)