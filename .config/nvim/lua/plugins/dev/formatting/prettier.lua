local M = {}

M.format = function()
	local script_path = debug.getinfo(1, "S").source:sub(2):match("(.*/)")
	local config_path = script_path .. ".config/.djlintrc"

	return {
		exe = "prettier",
		args = { "--config", config_path, vim.api.nvim_buf_get_name(0) },
		stdin = true,
	}
end

return M
