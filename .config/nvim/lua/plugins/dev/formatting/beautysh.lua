local M = {}

M.format = function()
	return {
		exe = "beautysh",
		args = { "--indent-size", "4", vim.api.nvim_buf_get_name(0) },
		stdin = false,
	}
end

return M
