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
	opts = {
		file = {
			[".keep"] = { glyph = "󰊢", hl = "MiniIconsGrey" },
			["devcontainer.json"] = { glyph = "", hl = "MiniIconsAzure" },
		},
		filetype = {
			dotenv = { glyph = "", hl = "MiniIconsYellow" },
		},
	},
})
