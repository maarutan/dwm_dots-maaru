local M = {}

M.format = function()
	return {
		exe = "stylua",
		args = { "--stdin-filepath", vim.api.nvim_buf_get_name(0), "-" },
		stdin = true,
	}
end

return M
