 	return (pfd[0]);
 }
 
int	open_redirect_file(t_node *redir)
 {
	if (redir == NULL)
 		return (0);
	if (redir->type == NODE_REDIRECT_OUT)
		redir->filefd = open(redir->filename->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == NODE_REDIRECT_IN)
		redir->filefd = open(redir->filename->str, O_RDONLY);
	else if (redir->type == NODE_REDIRECT_APPEND)
		redir->filefd = open(redir->filename->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (redir->type == NODE_REDIRECT_HEREDOC)
		redir->filefd = read_heredoc(redir->delimiter->str);
 	else
 		assert_error("open_redirect_file");
	if (redir->filefd < 0)
 	{
		xperror(redir->filename->str);
 		return (-1);
 	}
	redir->filefd = stashfd(redir->filefd);
	return (open_redirect_file(redir->next));
 }
 
 bool	is_redirect(t_node *node)