-- Load live-share.nvim
require("live-share").setup({
	-- Optional configurations
	server = "serveo.net", -- Use serveo.net for tunneling
	tunnel_port = 2222, -- Default port for the server
	username = "maaru", -- Replace with your SSH username
})
