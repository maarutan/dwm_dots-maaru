-- ██╗███╗   ██╗██╗████████╗
-- ██║████╗  ██║██║╚══██╔══╝
-- ██║██╔██╗ ██║██║   ██║
-- ██║██║╚██╗██║██║   ██║
-- ██║██║ ╚████║██║   ██║
-- ╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝
--

require("relative-motions"):setup({ show_numbers = "relative_absolute", show_motion = true })
require("eza-preview"):setup({
	level = 3,
	follow_symlinks = false,
	dereference = false,
})
require("keycalm").setup({
	limit = 10, -- Number of presses before blocking
	delay = 3, -- Block duration in seconds (also notification duration)
	notify_title = "Hold it, {user}!", -- Notification title
	notify_message = "🤠 Take it easy, cowboy!", -- Blocking message
	notify_unblock = "{key} 🥳", -- Unblock message
})

require("full-border"):setup({
	type = ui.Border.ROUNDED,
})
require("smart-enter"):setup({
	open_multi = true,
})
-- if os.getenv("NVIM") then
-- 	require("hide-preview"):entry()
-- end
THEME.git = THEME.git
	or {
		-- Colours
		modified = ui.Style():fg("#0096DB"),
		added = ui.Style():fg("#239549"),
		untracked = ui.Style():fg("#B0B0B0"),
		ignored = ui.Style():fg("#B0B0B0"),
		deleted = ui.Style():fg("#D32752"),

		-- Unmerged
		updated = ui.Style():fg("#CD32C0"),

		-- Icons
		modified_sign = "  ",
		added_sign = "  ",
		untracked_sign = "  ",
		ignored_sign = "  ",
		deleted_sign = "  ",

		-- Unmerged
		updated_sign = "  ",
	}

-- Set up the git plugin
require("git"):setup()

-- local theme = require("yatline-catppuccin"):setup("macchiato") -- "latte" | "frappe" | "macchiato"
local theme = require("yatline-gruvbox"):setup("dark") -- or "light"
require("yatline"):setup({
	theme = theme,
	show_background = false,

	header_line = {
		left = {
			section_a = {
				{ type = "line", custom = false, name = "tabs", params = { "left" } },
			},
			section_b = {},
			section_c = {},
		},
		right = {
			section_a = {
				{ type = "string", custom = false, name = "date", params = { "%A, %d %B %Y" } },
			},
			section_b = {
				{ type = "string", custom = false, name = "date", params = { "%X" } },
			},
			section_c = {},
		},
	},

	status_line = {
		left = {
			section_a = {
				{ type = "string", custom = false, name = "tab_mode" },
			},
			section_b = {
				{ type = "string", custom = false, name = "hovered_size" },
			},
			section_c = {
				{ type = "string", custom = false, name = "hovered_path" },
				{ type = "coloreds", custom = false, name = "count" },
			},
		},
		right = {
			section_a = {
				{ type = "string", custom = false, name = "cursor_position" },
			},
			section_b = {
				{ type = "string", custom = false, name = "cursor_percentage" },
			},
			section_c = {
				{ type = "string", custom = false, name = "hovered_file_extension", params = { true } },
				{ type = "coloreds", custom = false, name = "permissions" },
			},
		},
	},
})
-- local gruvbox_theme = require("yatline-gruvbox"):setup("light") -- or "light"

require("augment-command"):setup({
	smooth_scrolling = true,
})
