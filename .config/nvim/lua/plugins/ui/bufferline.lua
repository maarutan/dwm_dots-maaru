require("bufferline").setup({
	options = {
		numbers = "none",
		close_command = "Bdelete",
		right_mouse_command = "Bdelete!",
		left_mouse_command = "buffer",
		middle_mouse_command = nil,
		pinned = {
			enabled = true,
		},
		indicator = {
			icon = "▎",
			style = "icon",
		},
		buffer_close_icon = "  ",
		modified_icon = "[󰐕]",
		close_icon = "  ",
		left_trunc_marker = "«",
		right_trunc_marker = "»",
		diagnostics = "nvim_lsp",
		diagnostics_update_in_insert = false,
		diagnostics_indicator = function(count, level)
			local icon = level:match("error") and " " or " "
			return icon .. count
		end,
		offsets = {
			{
				filetype = "neo-tree",
				text = function()
					-- return require("pacman").get_pacman_text()
					-- return "Neo-tree ^^"
					return ""
				end,
				text_align = "center",
				separator = true,
			},
		},
		show_buffer_icons = true,
		show_buffer_close_icons = true,
		show_tab_indicators = true,
		enforce_regular_tabs = false,
		always_show_bufferline = true,
		separator_style = "thin",
		custom_areas = {
			right = function()
				local mode = vim.g.is_day_mode and "   󰖨  ▎" or "     ▎"
				local fg = vim.g.is_day_mode and "#ffffff" or "#1e1e2e"
				return {
					{ text = mode, padding = 1 },
					{ text = "🌊🌊🌊 ", fg = fg, bg = bg },
					{
						text = "  ",
						fg = fg,
						bg = "#C75B5F",
					},
				}
			end,
		},
	},
})

vim.keymap.set(
	"n",
	"<leader>bp",
	"<cmd>BufferLineTogglePin<CR>",
	{ noremap = true, silent = true, desc = "Pick Buffer" }
)
