-- Load linting plugin
local lint = require("lint")

-- Configure linters for each file type
lint.linters_by_ft = {
	cpp = { "cpplint" }, -- For C++
	django = { "djlint" }, -- For Django templates
	javascript = { "eslint_d" }, -- For JavaScript
	typescript = { "eslint_d" }, -- For TypeScript
	html = { "htmlhint" }, -- For HTML
	markdown = { "markdownlint" }, -- For Markdown
	python = { "ruff" }, -- For Python
	lua = { "selene" }, -- For Lua
	sh = { "shellcheck" }, -- For Shell
	css = { "stylelint" }, -- For CSS/SCSS
	yaml = { "yamllint" }, -- For YAML
}

-- Automatically trigger linting on file read and write
vim.api.nvim_create_autocmd({ "BufReadPost" }, {
	callback = function()
		require("lint").try_lint()
	end,
})

-- Display diagnostics in a floating window on CursorHold
vim.o.updatetime = 250 -- Set delay for CursorHold
vim.api.nvim_create_autocmd("CursorHold", {
	callback = function()
		vim.diagnostic.open_float(nil, { focusable = false })
	end,
})

-- Diagnostic display configuration
vim.diagnostic.config({
	virtual_text = {
		prefix = "   ", -- Marker symbol for virtual text
		spacing = 4, -- Space between the marker and the text
	},
	signs = true, -- Show signs in the gutter
	underline = true, -- Underline diagnostic text
	severity_sort = true, -- Sort diagnostics by severity
	float = {
		border = "rounded", -- Rounded border for floating windows
		source = "always", -- Show source of diagnostics
		header = "", -- No header for floating windows
		prefix = "", -- No prefix for floating window messages
	},
})

-- Define diagnostic signs in the gutter
local signs = { Error = " ", Warn = " ", Hint = " ", Info = " " }
for type, icon in pairs(signs) do
	local hl = "DiagnosticSign" .. type
	vim.fn.sign_define(hl, { text = icon, texthl = hl, numhl = "" })
end

-- Отправка диагностик в Quickfix
vim.keymap.set("n", "<leader>dq", function()
	local diagnostics = vim.diagnostic.get()
	vim.fn.setqflist({}, "r", { title = "Diagnostics", items = vim.diagnostic.toqflist(diagnostics) })
	vim.cmd("copen")
end, { noremap = true, silent = true })
local lint_enabled = true

vim.keymap.set("n", "<leader>dl", function()
	if lint_enabled then
		vim.diagnostic.reset(nil, vim.api.nvim_get_current_buf())
		lint_enabled = false
		print("Linting disabled")
	else
		require("lint").try_lint()
		lint_enabled = true
		print("Linting enabled")
	end
end, { desc = "Toggle nvim-lint" })
