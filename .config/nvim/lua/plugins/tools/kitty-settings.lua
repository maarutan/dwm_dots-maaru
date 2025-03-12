local function is_kitty()
	local kitty_id = os.getenv("KITTY_WINDOW_ID")
	return kitty_id ~= nil and kitty_id ~= ""
end

if is_kitty() then
	vim.api.nvim_create_autocmd("VimEnter", {
		callback = function()
			-- set kitty
			os.execute("kitty @ set-font-size 13.5")
			os.execute("kitty @ set-spacing padding=0")
			-- os.execute("kitty @ set-background-opacity 1")
		end,
	})

	vim.api.nvim_create_autocmd("VimLeave", {
		callback = function()
			-- reset kitty
			os.execute("kitty @ set-font-size 0")
			os.execute("kitty @ set-spacing padding=default")
			-- os.execute("kitty @ set-background-opacity 0.8")
		end,
	})

	-- laod kitty copy mode
	local ok, kitty_scroll = pcall(require, "kitty-scrollback")
	if ok then
		vim.keymap.set({ "n" }, "q", "Plug(KsbCloseOrQuitAll)", {})
		kitty_scroll.setup()
	else
		print("Warning: kitty-scrollback.nvim not found")
	end
end
