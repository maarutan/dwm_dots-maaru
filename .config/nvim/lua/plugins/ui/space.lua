local M = {}

-- Настройки
M.config = {
	jump_style = "bounce", -- bounce, fade, zoom, etc.
	speed = 10,
}

-- Анимация прыжка
function M.animate_jump(start_pos, end_pos)
	local steps = math.abs(end_pos[1] - start_pos[1])
	local current = start_pos[1]
	for i = 1, steps do
		vim.defer_fn(function()
			current = current + (end_pos[1] > start_pos[1] and 1 or -1)
			vim.api.nvim_win_set_cursor(0, { current, 0 })
		end, i * M.config.speed)
	end
end

-- Подключение команды
function M.setup(user_config)
	M.config = vim.tbl_extend("force", M.config, user_config or {})
	vim.cmd([[ 
        nnoremap <silent> gg :lua require'space'.handle_jump('gg')<CR>
        nnoremap <silent> G :lua require'space'.handle_jump('G')<CR>
    ]])
end

function M.handle_jump(cmd)
	local start_pos = vim.api.nvim_win_get_cursor(0)
	vim.cmd(cmd) -- Выполняем команду
	local end_pos = vim.api.nvim_win_get_cursor(0)
	M.animate_jump(start_pos, end_pos)
end

return M
