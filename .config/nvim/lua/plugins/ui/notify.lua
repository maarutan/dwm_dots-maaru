require("notify").setup({
	stages = "fade_in_slide_out", -- Этапы анимации
	background_colour = "NotifyBackground",
	timeout = 1000, -- Время отображения уведомления (в миллисекундах)
	minimum_width = 20, -- Минимальная ширина уведомления
	max_width = 40, -- Максимальная ширина уведомления
	max_height = 10, -- Максимальная высота уведомления
	render = "default", -- Стиль отображения уведомления
	top_down = true,
	fps = 144,
	time_formats = {
		notification = "  %I:%M %p", -- 12-часовой формат с AM/PM
		notification_history = "  %Y-%m-%d %I:%M %p", -- Дата и время в 12-часовом формате с AM/PM
	},
	icons = {
		ERROR = "", -- Иконка для ошибок
		WARN = "", -- Иконка для предупреждений
		INFO = "", -- Иконка для информации
		DEBUG = "", -- Иконка для отладочных сообщений
		TRACE = "✎", -- Иконка для трассировки
	},
	level = vim.log.levels.WARN, -- Показывать только ERROR и WARN
})
