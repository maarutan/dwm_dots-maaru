local M = {}

function M.Delete()
	local file_path = vim.fn.expand("%:p")
	local buf = vim.fn.bufnr("%")

	if buf == -1 or not vim.fn.bufexists(buf) then
		vim.notify("Buffer does not exist or is already closed.", vim.log.levels.WARN, {
			title = "Delete",
			icon = "⚠️",
		})
		return
	end

	if file_path == "" then
		vim.notify("Buffer is not associated with a file.", vim.log.levels.WARN, {
			title = "Delete",
			icon = "⚠️",
		})
		return
	end

	local file_name = vim.fn.expand("%:t")

	local answer = vim.fn.input("Delete file '" .. file_name .. "'? [y/n]: ")
	if answer:lower() ~= "y" then
		vim.notify("Deletion canceled.", vim.log.levels.WARN, {
			title = "Delete",
			icon = "ℹ️",
		})
		return
	end

	local ok, err = os.remove(file_path)
	if not ok then
		vim.notify("Error deleting file: " .. tostring(err), vim.log.levels.ERROR, {
			title = "Delete",
			icon = "🚨",
		})
		return
	end

	vim.cmd("bwipeout! " .. buf)

	vim.notify("File '" .. file_name .. "' deleted successfully. 💀", vim.log.levels.WARN, {
		title = "Delete",
		icon = "💀",
	})
end

vim.api.nvim_create_user_command("Delete", function()
	M.Delete()
end, { desc = "Delete current file and buffer with confirmation" })

vim.keymap.set("n", "<Leader>bD", function()
	M.Delete()
end, { noremap = true, silent = true, desc = "Delete current file and buffer" })

return M
