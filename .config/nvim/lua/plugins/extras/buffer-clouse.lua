function CloseBufferWithNoDelay()
	vim.opt.timeoutlen = 0

	local buf_count = 0
	for _, buf in ipairs(vim.api.nvim_list_bufs()) do
		if vim.fn.buflisted(buf) == 1 then
			buf_count = buf_count + 1
		end
	end

	if buf_count > 1 then
		vim.cmd("silent! bnext")
		vim.cmd("silent! bd")
	else
		vim.cmd("quit")
	end

	vim.cmd("redraw")

	vim.opt.timeoutlen = original_timeoutlen
end
