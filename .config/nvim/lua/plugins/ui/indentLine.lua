require("ibl").setup({
	indent = {
		char = "│", -- Символ для отображения линий
	},
	scope = {
		enabled = false, -- Отключаем подсветку области для ibl
	},
	exclude = {
		filetypes = { "dashboard", "NvimTree", "neo-tree", "toggleterm", "terminal", "term" }, -- Исключаем файлы
	},
})
vim.api.nvim_set_hl(0, "IndentBlanklineChar", { fg = "#3e4451", nocombine = true })
require("mini.indentscope").setup({
	draw = {
		delay = 100, -- Задержка перед началом отрисовки индикатора
		animation = require("mini.indentscope").gen_animation.linear({
			easing = "in-out", -- Плавная анимация
			duration = 25, -- Длительность анимации
			unit = "step", -- Шаги анимации
		}),

		priority = 2,
	},

	options = {
		border = "both", -- Отображение верхней и нижней границ области
		indent_at_cursor = true, -- Использовать отступ на позиции курсора
		try_as_border = false, -- Не рассматривать текущую строку как границу области
	},

	symbol = "│",
})

vim.api.nvim_create_autocmd("FileType", {
	pattern = { "dashboard", "help", "neo-tree", "lazy", "terminal", "toggleterm", "term" }, -- Список типов файлов для игнорирования
	callback = function()
		vim.b.miniindentscope_disable = true -- Отключение mini.indentscope для текущего буфера
	end,
})
