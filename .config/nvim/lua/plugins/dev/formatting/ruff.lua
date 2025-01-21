local M = {}

M.format = function()
	return {
		exe = "ruff",
		args = { "format", "--stdin-filename", vim.api.nvim_buf_get_name(0) },
		stdin = true,
	}
end

return M
