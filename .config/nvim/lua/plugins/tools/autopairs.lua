require("nvim-autopairs").setup({})

local npairs = require("nvim-autopairs")
local Rule = require("nvim-autopairs.rule")

npairs.add_rules({
	Rule("<", ">")
		:with_pair(function(opts)
			return true
		end)
		:replace_endpair(function(opts)
			return ">"
		end)
		:set_end_pair_length(1),
})
