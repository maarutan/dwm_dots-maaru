local M = {}

M.format = function()
	return {
		exe = "black",
		args = { "-" },
		stdin = true,
	}
end

return M
