require("mini.animate").setup({
	scroll = {
		enable = false, -- Отключить анимацию прокрутки
	},
	cursor = {
		enable = false, -- Отключить анимацию курсора
	},
})

-- No need to copy this inside `setup()`. Will be used automatically.
require("mini.icons").setup({
	-- Icon style: 'glyph' or 'ascii'
	style = "glyph",

	-- Customize per category. See `:h MiniIcons.config` for details.
	default = {},
	directory = {},
	extension = {},
	file = {},
	filetype = {},
	lsp = {},
	os = {},

	-- Control which extensions will be considered during "file" resolution
	use_file_extension = function(ext, file)
		return true
	end,
})
