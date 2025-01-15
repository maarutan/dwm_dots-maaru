local M = {}

local last_notification_id = nil

function M.show_file_path()
	local file_path = vim.fn.expand("%:p")
	if file_path == "" then
		file_path = "File does't exist"
	else
		file_path = file_path:gsub(vim.env.HOME, "~")
	end

	last_notification_id = vim.notify(file_path, vim.log.levels.WARN, {
		title = "Текущий файл",
		replace = last_notification_id,
		timeout = 3000,
	})
end

vim.keymap.set("n", "<leader>sf", M.show_file_path, { noremap = true, silent = true })

return M
