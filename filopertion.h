struct file_operations fops={
	open:open_dev,
	release:close_dev,
	write:write_dev,
	read:reader_dev,
	llseek:lseek_dev
};
