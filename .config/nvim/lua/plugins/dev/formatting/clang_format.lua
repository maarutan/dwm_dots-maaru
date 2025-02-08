local M = {}

M.format = function()
	return {
		exe = "clang-format",
		args = {
			"--assume-filename",
			vim.api.nvim_buf_get_name(0),
			"-style='{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 0}'",
		},
		stdin = true,
	}
end

return M
