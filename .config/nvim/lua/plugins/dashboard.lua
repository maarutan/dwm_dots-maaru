local M = {}
-- Функция для создания нового буфера
function M.create_new_buffer()
	local new_name = vim.fn.input("New file name: ", "")
	if new_name == "" then
		vim.notify("Создание буфера отменено.", vim.log.levels.WARN, {
			icon = "ℹ️",
			title = "NewBuffer",
		})
		return
	end

	if vim.fn.filereadable(new_name) == 1 then
		vim.notify("Ошибка: Файл уже существует.", vim.log.levels.ERROR, {
			icon = "🚨",
			title = "NewBuffer",
		})
		return
	end

	local ok, err = pcall(function()
		vim.cmd("edit " .. new_name)
		vim.cmd("setlocal buftype=")
	end)

	if not ok then
		vim.notify("Ошибка при создании буфера: " .. err, vim.log.levels.ERROR, {
			icon = "🚨",
			title = "NewBuffer",
		})
		return
	end

	vim.notify("Новый буфер успешно создан: " .. new_name, vim.log.levels.INFO, {
		icon = "✅",
		title = "NewBuffer",
	})
end

local function default_header()
	return {
		"",
		"",
		"",
		"",
		"",
		"              ███╗   ██╗███████╗ ██████╗ ██╗   ██╗██╗███╗   ███╗             Z",
		"              ████╗  ██║██╔════╝██╔═══██╗██║   ██║██║████╗ ████║        Z     ",
		"              ██╔██╗ ██║█████╗  ██║   ██║██║   ██║██║██╔████╔██║    z         ",
		"              ██║╚██╗██║██╔══╝  ██║   ██║╚██╗ ██╔╝██║██║╚██╔╝██║ z            ",
		"              ██║ ╚████║███████╗╚██████╔╝ ╚████╔╝ ██║██║ ╚═╝ ██║              ",
		"              ╚═╝  ╚═══╝╚══════╝ ╚═════╝   ╚═══╝  ╚═╝╚═╝     ╚═╝              ",
		"",
		"",
		"",
		"",
	}
end

require("dashboard").setup({
	theme = "doom",
	config = {
		header = default_header(),
		center = {
			{
				icon = "󰉖 ",
				icon_hl = "Title",
				desc = "Open Directory",
				desc_hl = "String",
				key = "d",
				keymap = "              SPC w d",
				key_hl = "Number",
				action = function()
					require("telescope").extensions.file_browser.file_browser({
						prompt_title = "Select Directory",
						cwd = "~", -- Начальная директория
						attach_mappings = function(_, map)
							local actions = require("telescope.actions")
							map("i", "<CR>", function(prompt_bufnr)
								local selected_path = require("telescope.actions.state").get_selected_entry().path
								actions.close(prompt_bufnr)
								vim.cmd("cd " .. selected_path)
								vim.cmd("edit .")
							end)
							return true
						end,
					})
				end,
			},

			{
				icon = "󰈞 ",
				icon_hl = "Title",
				desc = "Find and open file",
				desc_hl = "String",
				key = "f",
				keymap = "SPC f f",
				key_hl = "Number",
				action = function()
					require("telescope.builtin").find_files({
						find_command = { "fd", "--type", "f" },
						attach_mappings = function(_, map)
							local actions = require("telescope.actions")
							local action_state = require("telescope.actions.state")

							map("i", "<CR>", function(prompt_bufnr)
								local selected_entry = action_state.get_selected_entry()

								if not selected_entry then
									print("No file selected!")
									return
								end

								local filepath = selected_entry.path
								actions.close(prompt_bufnr)

								-- Открываем файл
								vim.cmd("edit " .. vim.fn.fnameescape(filepath))

								-- Открываем file_browser в директории файла
								local file_dir = vim.fn.fnamemodify(filepath, ":p:h")
								require("telescope").extensions.file_browser.file_browser({
									cwd = file_dir,
									respect_gitignore = false,
									hidden = true,
								})
							end)
							return true
						end,
					})
				end,
			},

			{
				icon = " ",
				icon_hl = "Title",
				desc = "Git Branches",
				desc_hl = "String",
				key = "b",
				keymap = "              SPC g b",
				key_hl = "Number",
				action = function()
					if vim.fn.isdirectory(".git") == 1 then
						require("telescope.builtin").git_branches()
					else
						vim.notify("У вас нет репозитория", vim.log.levels.WARN, {
							title = "Git",
							icon = "󰊢",
						})
					end
				end,
			},

			{
				icon = "󰄛 ",
				icon_hl = "Title",
				desc = "Recent files",
				desc_hl = "String",
				key = "r",
				keymap = "              SPC f r",
				key_hl = "Number",
				action = ":Telescope oldfiles",
			},
			{
				icon = " ",
				icon_hl = "Title",
				desc = "New file",
				desc_hl = "String",
				key = "n",
				keymap = "            SPC b n",
				key_hl = "Number",
				action = M.create_new_buffer,
			},

			{
				icon = " ",
				icon_hl = "Title",
				desc = "Open Neovim Config",
				desc_hl = "String",
				key = "o",
				keymap = "              SPC o c",
				key_hl = "Number",
				action = ":cd ~/.config/nvim | edit init.lua",
			},
			-- Кнопка Quit [q]
			{
				desc = "                    󰩈 Quit [q]", -- Центрируем текст
				desc_hl = "String",
				key = "q",
				keymap = "            SPC q _",
				key_hl = "Number",
				action = ":qa", -- Команда выхода из Neovim
			},
		},
		-- Запускаем анимацию
		footer = function()
			local pacman = require("pacman").get_pacman_text()
			local text = "Welcome to neovim 🚀 "
			return { text, pacman }
		end,
	},
})
return M
